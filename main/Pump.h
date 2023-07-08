#ifndef PUMP_H
#define PUMP_H

class Pump {
private:
  int pin;  // Il pin di Arduino collegato al pin del relè.

public:
  /**
   * @param pin Numero del pin collegato al pin del relè.
   */
  Pump(int pin);

  /**
   * Inizializza il pin del relè.
   * Da chiamare all'avvio del programma per configurare il pin.
   */
  void begin();

  /**
   * Attiva la pompa.
   */
  void activate();

  /**
   * Disattiva la pompa.
   */
  void deactivate();

  /**
   * Attiva la pompa per un certo numero di secondi.
   * @param seconds Il numero di secondi per cui attivare la pompa.
   */
  void activateFor(int seconds);
};

#endif