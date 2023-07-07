#ifndef LED_H
#define LED_H

class Led {
private:
  int pin;
  bool state;

public:
  // @param pin Numero del pin a cui è collegato il LED.
  Led(int pin);

  // Inizializza il LED impostando il pin come OUTPUT.
  void begin();

  // Accende il led.
  void on();

  // Spegne il led.
  void off();

  /**
   * Inverte lo stato attuale del LED.
   * Se è acceso, lo spegne; se è spento, lo accende.
   */
  void toggle();

  /**
   * Fa lampeggiare il LED per la durata specificata.
   * @param duration La durata di ogni singolo lampeggio in millisecondi.
   */
  void blink(int duration);

  /**
   * Verifica se il LED è acceso.
   * @return true se il LED è acceso, false altrimenti.
   */
  bool isOn();
};

#endif
