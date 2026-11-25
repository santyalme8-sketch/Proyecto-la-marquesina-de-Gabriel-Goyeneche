#ifndef ACCION_H
#define ACCION_H

#include "TiposAgente.h"

//la accion convierte la decision en un disparo real
//usa un tiro parabolico al reves, sabiendo de donde sale y a donde llega
//y en cuanto tiempo, calcula la velocidad inicial]

class Accion {
private:
    float gravedad; //tiene que ser positiva porque en qt crece hacia abajo, pora alguna razon que me parece una estupidez XD
    int contadorId;

public:
    explicit Accion(float gravedad = 980.f);

    DatosDisparo disparar(const Decision& d, float origenX, float origenY);
//posicion del proyectil en tiempo t para que el juego lo mueva

    static void posicionEn(const DatosDisparo&, float t, float& x, float& y);

};

#endif // ACCION_H
