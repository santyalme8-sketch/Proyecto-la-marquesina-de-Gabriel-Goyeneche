#include "Accion.h"
#include <stdexcept>

Accion::Accion(float gravedad): gravedad(gravedad), contadorId(0) {
    if (gravedad <= 0)
        throw std::invalid_argument( "Accion: la gravedad debe ser pa arriba cabron, positiva");

}

DatosDisparo Accion::disparar(const Decision& d, float origenX, float origenY) {
    float T = d.tiempoVuelo;
    if (T <= 0)
        throw std::invalid_argument( "Accion: tiempo de vuelo invalido brother");

    /* ecuaciones del tiro parabolico:
       x(t) = x0 + vx*t
       y(t) = y0 + vy*t + g*t^2/2
     Despejando para que en t = T llegue al objetivo:
       vx = (xf - x0) / T
       vy = (yf - y0 - g*T^2/2) / T
    */

    DatosDisparo p;
    p.id = ++contadorId;
    p.tactica = d.tactica;
    p.x0 = origenX;
    p.y0 = origenY;
    p.gravedad = gravedad;
    p.vx = (d.objetivoX - origenX) / T;
    p.vy = (d.objetivoY - 0.5f *gravedad * T * T) / T;
    return p;
}

void Accion::posicionEn(const DatosDisparo& p, float t, float& x, float& y) {
    x = p.x0 + p.vx * t;
    y = p.y0 + p.vy * t + 0.5f * p.gravedad *t * t;

}