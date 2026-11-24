#include "Yuuko.h"
#include <cmath>

Yuuko::Yuuko(float x, float y)
    : Persona(x, y, 100), enSuelo(false), tiempoPanico(0), tiempoAturdida(0),
    esperaMalaSuerte(0), panicoPorVidaUsado(false), aturdirAlTerminar(false) {}

void Yuuko::actualizar(float dt) {
    // relojes de los estados
    if (tiempoPanico > 0) {
        tiempoPanico -= dt;
        if (tiempoPanico <= 0 && aturdirAlTerminar) {
            tiempoAturdida = 1.5f;   // el golpe de la mala suerte pasa factura
            aturdirAlTerminar = false;
        }
    }
    if (tiempoAturdida > 0) tiempoAturdida -= dt;
    if (esperaMalaSuerte > 0) esperaMalaSuerte -= dt;

    // moverse con la velocidad que puso el nivel
    x += vx * dt;
    y += vy * dt;
}

void Yuuko::recibirDano(int cantidad) {
    Persona::recibirDano(cantidad);   // restar salud

    // PANICO EXTREMO: si baja del 30% de salud entra en panico por 8 s (una sola vez)
    if (!panicoPorVidaUsado && puntosDeSalud < 0.3f * saludMaxima) {
        tiempoPanico = 8.0f;
        panicoPorVidaUsado = true;
    }
}

bool Yuuko::llamarMalaSuerte() {
    if (esperaMalaSuerte > 0 || aturdida()) return false;
    // si le cae algo en la cabeza, pierde salud pero gana 3 s de panico
    recibirDano(10);
    if (tiempoPanico < 3.0f) tiempoPanico = 3.0f;
    aturdirAlTerminar = true;    // despues del panico queda aturdida
    esperaMalaSuerte = 10.0f;
    return true;
}

float Yuuko::multiplicadorVelocidad() const {
    if (aturdida()) return 0.35f;   // aturdida = lenta
    if (enPanico()) return 1.65f;   // panico = 65% mas rapida
    return 1.0f;
}

EstadoYuuko Yuuko::estadoActual() const {
    if (enPanico()) return EstadoYuuko::Panico;
    if (!enSuelo) return EstadoYuuko::Saltando;
    if (std::fabs(vx) > 1 || std::fabs(vy) > 1) return EstadoYuuko::Corriendo;
    return EstadoYuuko::Reposo;
}