#ifndef CAPACITIVE_SENSOR_H
#define CAPACITIVE_SENSOR_H

class CapacitiveSensor {
private:
    int pin;        // Il pin di Arduino collegato al pin del sensore.
    int level;      // Il livello dell'acqua.
    int wetLevel;   // Valore di riferimento per il sensore bagnato.
    int dryLevel;   // Valore di riferimento per il sensore asciutto.
public:
    /**
     * @param pin Numero del pin collegato al pin del sensore.
     */
    CapacitiveSensor(int pin, int wet, int dry);

    /**
     * Inizializza il livello dell'acqua.
     */
    void begin();
    
    /**
     * @return Il livello dell'acqua. 
     */
    int getLevel();

    /**
     * @return true se il livello dell'acqua è sotto la soglia, false altrimenti.
     */
    bool isUnderThreshold(int threshold);

    /**
     * @return Il livello dell'acqua in percentuale.
     */
    int getLevelPercentage();

    /**
     * @return true se il livello dell'acqua è sotto la soglia, false altrimenti.
     */
    bool isWet();

    /**
     * @return true se il livello dell'acqua è sopra la soglia, false altrimenti.
     */
    bool isDry();
};

#endif