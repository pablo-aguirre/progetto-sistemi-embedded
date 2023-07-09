#include "MenuLCD.h"

MenuLCD::MenuLCD(LiquidCrystal* lcd, MenuItem* menuItems, int nItems) {
  this->lcd = lcd;
  this->menuItems = menuItems;
  this->numItems = nItems;
  this->selectedItem = 0;
  this->editMode = false;
  this->alertMode = false;
}

void MenuLCD::begin() {
  lcd->begin(16, 2);
  print();
}

void MenuLCD::print() {
  lcd->clear();
  lcd->setCursor(0, 0);
  if (alertMode) {
    lcd->print("ALERT");
    lcd->setCursor(0, 1);
    lcd->print(alertMessage);
  } else {
    lcd->print(editMode ? " " : ">");
    lcd->print(menuItems[selectedItem].label);
    lcd->setCursor(0, 1);
    lcd->print(editMode ? ">" : " ");
    lcd->print(String(menuItems[selectedItem].value) + " " + menuItems[selectedItem].measure);
  }
}

void MenuLCD::next() {
  if (alertMode)
    alertMode = false;
  else if (editMode)
    encreaseValue();
  else
    selectNextItem();
}

void MenuLCD::previous() {
  if (alertMode)
    alertMode = false;
  if (editMode)
    decreaseValue();
  else
    selectPreviousItem();
}

void MenuLCD::confirm() {
  if (alertMode)
    alertMode = false;
  else 
    setEditMode();
  print();
}

void MenuLCD::selectNextItem() {
  selectedItem = (selectedItem + 1) % numItems;
  print();
}

void MenuLCD::selectPreviousItem() {
  selectedItem = (selectedItem - 1 + numItems) % numItems;
  print();
}

void MenuLCD::setEditMode() {
  if (menuItems[selectedItem].modificable)
    this->editMode = !this->editMode;
}

void MenuLCD::modifyValue(float value) {
  if (menuItems[selectedItem].modificable) {
    menuItems[selectedItem].value = value;
    print();
  }
}

void MenuLCD::encreaseValue() {
  if (menuItems[selectedItem].value + menuItems[selectedItem].increment <= menuItems[selectedItem].max) {
    modifyValue(menuItems[selectedItem].value + menuItems[selectedItem].increment);
  } else {
    modifyValue(menuItems[selectedItem].min);
  }
}

void MenuLCD::decreaseValue() {
  if (menuItems[selectedItem].value - menuItems[selectedItem].increment >= menuItems[selectedItem].min) {
    modifyValue(menuItems[selectedItem].value - menuItems[selectedItem].increment);
  } else {
    modifyValue(menuItems[selectedItem].max);
  }
}

void MenuLCD::setAlertMode(String message) {
  alertMode = true;
  alertMessage = message;
  print();
}