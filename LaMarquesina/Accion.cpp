#include "Accion.h"
#include <stdexcept>

Accion::Accion(float gravedad): gravedad(gravedad), contadorId(0) {
    if (gravedad <= 0)
        throw std::invalid_argument( "Accion: la gravedad debe ser pa arriba cabron, positiva");

}

DatosDisparo Accion::disparar(const Decision& d, float origenX, float origenY) {
    float T = d.tiempoVuelo;
    if (T <= 0)
        throw std::invalid_argument("Accion: tiempo de vuelo invalido");
    DatosDisparo p;
    contadorId++;
    p.id = contadorId;
    p.tactica = d.tactica;
    p.x0 = origenX;
    p.y0 = origenY;
    p.gravedad = gravedad;
    p.vx = (d.objetivoX - origenX) / T;
    p.vy = (d.objetivoY - origenY - 0.5f * gravedad * T * T) / T;
    return p;
}
