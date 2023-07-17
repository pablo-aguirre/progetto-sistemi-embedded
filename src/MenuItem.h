#ifndef MENUITEM_H
#define MENUITEM_H
#include <Arduino.h>

class MenuItem {
private:
  String label;
  String value;
  bool modificable;
  String measure;
public:
  MenuItem(String, String, bool, String);
  String getLabel();
  String getValue();
  String getValue(bool);
  void setValue(int);
  bool isModificable();
};

#endif