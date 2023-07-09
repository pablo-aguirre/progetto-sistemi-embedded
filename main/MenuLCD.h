#ifndef MENULCD_H
#define MENULCD_H
#include <LiquidCrystal.h>

struct MenuItem {
  int id;
  String label;
  bool modificable;
  float value;
  float min;
  float max;
  float increment;
  String measure;
};

class MenuLCD {
private:
  LiquidCrystal* lcd;
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
  MenuLCD(LiquidCrystal* lcd, MenuItem* items, int nItems);
  
  /**
   * @brief Inizializza il menu.
   */
  void begin();

  /**
   * @brief Stampa il menu a seconda dello stato.
   */
  void print();

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
  void modifyValue(float value);

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
};
#endif