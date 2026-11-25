#ifndef PERCEPCION_H
#define PERCEPCION_H

#include <deque>
#include "Tiposagente.h"

//la percepcion hace que cada cierto tiempo lee la posicion, velocidad y estado de yuuko,
//luego guarda las ultimas lecturas para calcular promedios

class Percepcion {

private:
    std::deque<LecturaYuuko> lecturas; //deque se usa para meter atras y sacar adelant
    int maxLecturas;
    float intervalo; //segundos entre cada lectura
        float acumulado; //tiempo desde la ultima lectura\

public:
        Percepcion(float intervalo, int maxLecturas = 5);
    //se llama en cada frame y devuelve true si tomo una lectura nueva

        bool percibir(float dt, const LecturaYuuko&lectura);
        //resume las lecturas guardadsa para el razonamiento;

        Observacion observar() const;
        void reiniciar();

};

#endif // PERCEPCION_H
