#ifndef MENULCD_H
#define MENULCD_H
// #include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include "MenuItem.h"
#include <Wire.h>

class MenuLCD {
private:
  LiquidCrystal_I2C* lcd;
  // LiquidCrystal *lcd;
  MenuItem* menuItems;
  int numItems;
  int selectedItem;
  bool editMode;
  bool alertMode;
  String alertMessage;

public:
  /**
    * @param lcd lcd object
    * @param items la lista delle voci del menu
    * @param nItems numero di voci del menu
  */
  MenuLCD(LiquidCrystal_I2C* lcd, MenuItem* items, int nItems);
  // MenuLCD(LiquidCrystal *lcd, MenuItem* items, int nItems);

  /**
   * @brief Inizializza il menu.
   */
  void begin();

  /**
   * @brief Stampa il menu a seconda dello stato.
   */
  void print();

  /**
   * @brief Restituisce la voce del menu selezionata.
   */
  int getSelectedItem();

  /**
   * @brief Mostra a schermo la prossima voce / valore del menu.
   */
  void next();
  /**
   * @brief Mostra a schermo la voce / valore precedente del menu.
   */
  void previous();

  /**
   * @brief Entra in modalità di modifica del valore / conferma il valore.
   */
  void confirm();

  /**
   * @brief Mostra a schermo la prossima voce del menu.
   */
  void selectNextItem();

  /**
   * @brief Mostra a schermo la voce precedente del menu.
   */
  void selectPreviousItem();

  /**
   * @brief Modifica la voce del menu selezionata.
   */
  void modifyValue(int value);

  /**
   * @brief Incrementa il valore della voce del menu selezionata.
   */
  void encreaseValue();

  /**
   * @brief Decrementa il valore della voce del menu selezionata.
   * 
   */
  void decreaseValue();

  /**
   * @brief Imposta la modalità di alert (per mostrare un messaggio).
   * @param message Messaggio da mostrare.
   */
  void setAlertMode(String message);

  /**
   * @brief Imposta/resetta la modalità di modifica.
   */
  void setEditMode();

  /**
   * @brief Restituisce true se il menu è in modalità di alert.
   */
  bool isAlertMode();
};
#endif