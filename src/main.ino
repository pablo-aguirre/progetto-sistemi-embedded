#include <TaskScheduler.h>
#include <LiquidCrystal_I2C.h>
// #include <LiquidCrystal.h>
// #include <EEPROM.h>
#include "HC_SR04.h"
#include "MenuLCD.h"
#include "MenuItem.h"

// #define DEBUG
// #define ENABLE_EEPROM

#define X_PIN A0
#define Y_PIN A1
#define WATER_PIN A2
#define ECHO_PIN 2  // interrupt pin
#define YELLOW_LED_PIN 3
#define PUMP_PIN 4
#define RED_LED_PIN 5
#define BUZZER_PIN 6
#define TRIGGER_PIN 7

#define ML_PER_SEC 10
// #define ML_MAX "50"
#define MIN_DISTANCE 2
#define MAX_DISTANCE 5
#define BUZZER_DURATION 1000
#define WATER_LEVEL_THRESHOLD 500

LiquidCrystal_I2C lcd(0x27, 2, 16);
// LiquidCrystal lcd(12, 11, 13, 10, 9, 8);
MenuItem menuItems[] = { MenuItem("Acqua bevuta", "0", false, "ml"), MenuItem("Obiettivo", "0", true, "l"), MenuItem("Reminder", "0", true, "min") };
MenuLCD menu(&lcd, menuItems, sizeof(menuItems) / sizeof(MenuItem));
HC_SR04<ECHO_PIN> distanceSensor(TRIGGER_PIN);
int minuti;
float distance;
int waterLevel;

// Task callbacks
void menuCallback();            // menu
void distanceSensorCallback();  // distance sensor
void pumpCallback();            // pump
void waterCallback();           // water
void ledCallback();             // led
void timerCallback();           // timer
void waterLevelCallback();      // water level

// Tasks
Scheduler scheduler;
Task distanceSensorTask(50, TASK_FOREVER, &distanceSensorCallback);
Task menuTask(200, TASK_FOREVER, &menuCallback);
Task pumpTask(200, TASK_FOREVER, &pumpCallback);
Task waterTask(200, TASK_FOREVER, &waterCallback);
Task ledTask(200, TASK_FOREVER, &ledCallback);
Task timerTask(0, TASK_ONCE, &timerCallback);
Task waterLevelTask(200, TASK_FOREVER, &waterLevelCallback);

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  // buttons
  // pinMode(CLICK_PIN, INPUT_PULLUP);

#ifdef ENABLE_EEPROM
  // load null values to EEPROM
  // for (int x = 0; x < sizeof(menuItems)/sizeof(MenuItem); x++)
  //   EEPROM.put(sizeof(int)*x, 0); // save menuItem value to EEPROM

  for (int i = 0; i < sizeof(menuItems) / sizeof(MenuItem); i++) {  // unload menuItems values from EEPROM
    int tmp;
    EEPROM.get(sizeof(int) * i, tmp);
    menuItems[i].setValue(tmp);
  }
#endif

  // menu
  menu.begin();

  // distance sensor
  distanceSensor.beginAsync();
  distanceSensor.startAsync(100000);  // first measure

  // pump
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  // buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  // LED
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);

  // tasks
  scheduler.init();
  scheduler.addTask(distanceSensorTask);
  scheduler.addTask(pumpTask);
  scheduler.addTask(menuTask);
  scheduler.addTask(waterTask);
  scheduler.addTask(ledTask);
  scheduler.addTask(timerTask);
  scheduler.addTask(waterLevelTask);
  distanceSensorTask.enable();
  pumpTask.enable();
  menuTask.enable();
  ledTask.enable();
  waterLevelTask.enable();
}

void loop() {
  scheduler.execute();
}

void distanceSensorCallback() {
#ifdef DEBUG
  Serial.println("Distance: " + String(distanceSensor.getDist_cm()) + "cm");
#endif
  if (distanceSensor.isFinished()) {
    distance = distanceSensor.getDist_cm();
    distanceSensor.startAsync(100000);
  }
}

void pumpCallback() {
#ifdef DEBUG
  Serial.print("Pump: ");
  Serial.println(pump.isOn() ? "ON" : "OFF");
#endif
  if (MIN_DISTANCE < distance && distance < MAX_DISTANCE) {
    digitalWrite(PUMP_PIN, HIGH);
    waterTask.enable();
  } else {
    digitalWrite(PUMP_PIN, LOW);
    waterTask.disable();
#ifdef ENABLE_EEPROM
    EEPROM.put(sizeof(int) * 0, menuItems[0].getValue(false).toInt());
#endif
  }
}

void waterCallback() {
#ifdef DEBUG
  Serial.println("Water: " + String(menuItems[0].getValue(true).toInt()));
#endif
  menuItems[0].setValue(menuItems[0].getValue().toInt() + ML_PER_SEC / 5);
  if (menuItems[0].getValue().toInt() >= menuItems[1].getValue().toInt() && menuItems[1].getValue().toInt() != 0) {
    menu.setAlertMode("Raggiunti " + menuItems[1].getValue(true) + "!!!");
    menuItems[1].setValue(0);
    waterTask.delay(BUZZER_DURATION * 2);
    tone(BUZZER_PIN, 261, BUZZER_DURATION);
  }
  menu.print();
}

void menuCallback() {
#ifdef DEBUG
  Serial.println("X_PIN: " + String(analogRead(X_PIN)) + " Y_PIN: " + String(analogRead(Y_PIN)));
#endif
#ifdef ENABLE_EEPROM
  EEPROM.put(sizeof(int) * menu.getSelectedItem(), menuItems[menu.getSelectedItem()].getValue(false).toInt());  // save menuItem value to EEPROM
#endif
  if (analogRead(Y_PIN) < 100)
    menu.next();
  else if (analogRead(Y_PIN) > 900)
    menu.previous();
  else if (analogRead(X_PIN) < 100 || analogRead(X_PIN) > 900) {
    minuti = menuItems[2].getValue().toInt();
    menu.confirm();
  }
  if (minuti != 0 && !timerTask.isEnabled()) {
    timerTask.setInterval(minuti * 1000);
    timerTask.restartDelayed();
  }
  if (minuti == 0 && timerTask.isEnabled())
    timerTask.disable();
}

void ledCallback() {
  if (waterTask.isEnabled()) {  // green led
    analogWrite(YELLOW_LED_PIN, 255);
    analogWrite(RED_LED_PIN, 0);
  }
  if (distance < MIN_DISTANCE || distance > MAX_DISTANCE) {  // orange led
    analogWrite(YELLOW_LED_PIN, 255);
    analogWrite(RED_LED_PIN, 20);
  }
  if (menu.isAlertMode()) {  // red led
    analogWrite(YELLOW_LED_PIN, 0);
    analogWrite(RED_LED_PIN, 255);
  }
}

void timerCallback() {
#ifdef DEBUG
  Serial.println("Timer: " + String(minuti));
#endif
  menu.setAlertMode("Bevi!!!");
  tone(BUZZER_PIN, 261, BUZZER_DURATION);
}

void waterLevelCallback() {
  waterLevel = analogRead(WATER_PIN);
#ifdef DEBUG
  Serial.println("Water level: " + String(waterLevel));
#endif
  if (waterLevel > WATER_LEVEL_THRESHOLD) {
    menu.setAlertMode("Riempire acqua!!!");
    tone(BUZZER_PIN, 261, BUZZER_DURATION);
  }
}