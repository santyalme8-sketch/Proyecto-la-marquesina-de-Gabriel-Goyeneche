#ifndef PERCEPCION_H
#define PERCEPCION_H

#include <deque>
#include "TiposAgente.h"

class Percepcion {

private:
    std::deque<LecturaYuuko> lecturas;
    int maxLecturas;
    float intervalo;
        float acumulado;

public:
        Percepcion(float intervalo, int maxLecturas = 5);
       bool percibir(float dt, const LecturaYuuko&lectura);
        Observacion observar() const;
        void reiniciar();

};

#endif // PERCEPCION_H
