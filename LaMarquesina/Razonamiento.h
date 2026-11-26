#ifndef RAZONAMIENTO_H
#define RAZONAMIENTO_H

#include "TiposAgente.h"
#include "Aprendizaje.h"

class Razonamiento {
private:
    float errorPrediccion;
    bool usaAprendizaje;

    float azar(float minimo, float maximo);
    float factorSituacion(Tactica t, const Observacion& obs);
    Tactica elegirTactica(const Observacion& obs, const Aprendizaje& apr);

public:
    Razonamiento(float errorPrediccion, bool usaAprendizaje);
    Decision decidir(const Observacion& obs, const Aprendizaje& apr, float origenX, float origenY);

};

#endif // RAZONAMIENTO_H
