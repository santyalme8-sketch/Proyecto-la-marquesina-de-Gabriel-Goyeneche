#ifndef RAZONAMIENTO_H
#define RAZONAMIENTO_H

#include <random>
#include "Tiposagente.h"
#include "Aprendizaje.h"

//razonamiento: mira la observacion y los pesos aprendidos
//y luego ddecide que tactica usar y a donde apuntar, easy peasy

class Razonamiento {
private:
    float errorPrediccion;
    bool usaAprendizaje;
    std::mt19937 generador; // hace numeros aleatorios para no ser 100% predecible
    //que tanto conviene cada tactica segun lo que hace yuuko en el momento

    float factorSituacion(Tactica t, const Observacion& obs) const;
    Tactica elegirTactica(const Observacion&obs, const Aprendizaje& apr);

public:
    Razonamiento(float errorPrediccion, bool usarAprendizaje, unsigned semilla = std::random_device{}());

    Decision decidir(const Observacion& obs, const Aprendizaje& apr,
                     float origenX, float origenY);


};

#endif // RAZONAMIENTO_H
