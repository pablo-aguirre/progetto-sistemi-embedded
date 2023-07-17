#include "MenuItem.h"

MenuItem::MenuItem(String label, String value, bool modificable, String measure) {
  this->label = label;
  this->value = value;
  this->modificable = modificable;
  this->measure = measure;
}

String MenuItem::getLabel() {
  return label;
}

String MenuItem::getValue() {
  return value;
}

String MenuItem::getValue(bool measure) {
  return measure ? value + " " + this->measure : value;
}

void MenuItem::setValue(int value) {
  this->value = String(value);
}

bool MenuItem::isModificable() {
  return modificable;
}