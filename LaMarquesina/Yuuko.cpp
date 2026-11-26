#include "Yuuko.h"
#include <cmath>

Yuuko::Yuuko(float x, float y) : Persona(x, y, 100), enSuelo(false), tiempoPanico(0), tiempoAturdida(0), esperaMalaSuerte(0), velocidad(260),
    panicoPorVidaUsado(false), aturdirAlTerminar(false) {}

void Yuuko::actualizar(float dt) {
    if (tiempoPanico > 0) {
        tiempoPanico -= dt;
        if (tiempoPanico <= 0 && aturdirAlTerminar) {
            tiempoAturdida = 1.5f;
            aturdirAlTerminar = false;
        }
    }
    if (tiempoAturdida > 0) tiempoAturdida -= dt;
    if (esperaMalaSuerte > 0) esperaMalaSuerte -= dt;

    x += vx * dt;
    y += vy * dt;
}

void Yuuko::recibirDano(int cantidad) {
    Persona::recibirDano(cantidad);

    if (!panicoPorVidaUsado && puntosDeSalud < 0.3f * saludMaxima) {
        tiempoPanico = 8.0f;
        panicoPorVidaUsado = true;
    }
}

bool Yuuko::llamarMalaSuerte() {
    if (esperaMalaSuerte > 0 || aturdida()) return false;
    recibirDano(10);
    if (tiempoPanico < 3.0f) tiempoPanico = 3.0f;
    aturdirAlTerminar = true;
    esperaMalaSuerte = 10.0f;
    return true;
}

float Yuuko::multiplicadorVelocidad() const {
    if (aturdida()) return 0.35f;
    if (enPanico()) return 1.65f;
    return 1.0f;
}

EstadoYuuko Yuuko::estadoActual() const {
    if (enPanico()) return EstadoYuuko::Panico;
    if (!enSuelo) return EstadoYuuko::Saltando;
    if (std::fabs(vx) > 1 || std::fabs(vy) > 1) return EstadoYuuko::Corriendo;
    return EstadoYuuko::Reposo;
}