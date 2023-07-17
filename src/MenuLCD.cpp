#include "MenuLCD.h"

// MenuLCD::MenuLCD(LiquidCrystal *lcd, MenuItem* menuItems, int nItems) {
MenuLCD::MenuLCD(LiquidCrystal_I2C* lcd, MenuItem* menuItems, int nItems) {
  this->lcd = lcd;
  this->menuItems = menuItems;
  this->numItems = nItems;
  this->selectedItem = 0;
  this->editMode = false;
  this->alertMode = false;
}

void MenuLCD::begin() {
  // lcd->begin(16, 2);
  lcd->init();
  lcd->backlight();
  // lcd->noBacklight();
  print();
}

void MenuLCD::print() {
  lcd->clear();
  lcd->setCursor(0, 0);
  if (alertMode) {
    lcd->print("Attenzione:");
    lcd->setCursor(0, 1);
    lcd->print(alertMessage);
  } else {
    lcd->print(editMode ? " " : ">");
    lcd->print(menuItems[selectedItem].getLabel());
    lcd->setCursor(0, 1);
    lcd->print(editMode ? ">" : " ");
    lcd->print(menuItems[selectedItem].getValue(true));
  }
}

int MenuLCD::getSelectedItem() {
  return selectedItem;
}

void MenuLCD::next() {
  if (alertMode)
    alertMode = false;
  else if (editMode)
    encreaseValue();
  else
    selectNextItem();
  print();
}

void MenuLCD::previous() {
  if (alertMode)
    alertMode = false;
  if (editMode)
    decreaseValue();
  else
    selectPreviousItem();
  print();
}

void MenuLCD::confirm() {
  if (alertMode)
    alertMode = false;
  else if (editMode)
    editMode = false;
  else if (menuItems[selectedItem].isModificable()) {
    setEditMode();
  } else {
    setAlertMode("Non modificabile!");
  }
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
  if (menuItems[selectedItem].isModificable())
    this->editMode = true;
}

void MenuLCD::modifyValue(int value) {
  if (menuItems[selectedItem].isModificable()) {
    menuItems[selectedItem].setValue(value);
    print();
  }
}

void MenuLCD::encreaseValue() {
  modifyValue(menuItems[selectedItem].getValue(false).toInt() + 1);
}

void MenuLCD::decreaseValue() {
  if (menuItems[selectedItem].getValue(false).toInt() > 0)
    modifyValue(menuItems[selectedItem].getValue(false).toInt() - 1);
}

void MenuLCD::setAlertMode(String message) {
  alertMode = true;
  alertMessage = message;
  print();
}

bool MenuLCD::isAlertMode() {
  return alertMode;
}