#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

class DistanceSensor {
private:
  int triggerPin;  // Il pin di Arduino collegato al pin Trigger del sensore ad ultrasuoni.
  int echoPin;  // Il pin di Arduino collegato al pin Echo del sensore ad ultrasuoni.

public:
  /**
   * @param triggerPin Numero del pin collegato al pin trigger.
   * @param echoPin Numero del pin collegato al pin echo.
   */
  DistanceSensor(int triggerPin, int echoPin);

  /**
   * Inizializza i pin di trigger ed echo.
   * Da chiamare all'avvio del programma per configurare i pin.
   */
  void begin();

  /**
   * Restituisce la distanza misurata dal sensore ad ultrasuoni.
   * @return La distanza misurata in centimetri.
   */
  float getDistance();

  /**
   * Verifica se un oggetto è rilevato entro una distanza specificata.
   * @param thresholdDistance La distanza soglia in centimetri.
   * @return True se un oggetto è rilevato entro la distanza soglia, False altrimenti.
   */
  bool isObjectDetected(float thresholdDistance);

};

#endif
