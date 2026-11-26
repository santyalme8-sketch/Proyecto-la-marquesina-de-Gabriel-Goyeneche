#ifndef ACCION_H
#define ACCION_H

#include "TiposAgente.h"

class Accion {
private:
    float gravedad;
    int contadorId;

public:
    Accion(float gravedad = 980.0f);
    DatosDisparo disparar(const Decision&d, float origenX, float origenY);

};

#endif // ACCION_H
