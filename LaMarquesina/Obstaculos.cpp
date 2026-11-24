#include "Obstaculos.h"
#include <stdexcept>

// Obstaculo
Obstaculo::Obstaculo(float x, float y, float vx, float vy, int dano, bool destructible)
    : Cuerpo(x, y, vx, vy), dano(dano), destructible(destructible) {}

// proyectil de tiro parabolico
Proyectil::Proyectil(float x0, float y0, float vx0, float vy0, float g, int id, int dano)
    : Obstaculo(x0, y0, vx0, vy0, dano, true),
    x0(x0), y0(y0), vx0(vx0), vy0(vy0), g(g), t(0), id(id) {}

void Proyectil::actualizar(float dt) {
    t += dt;
    //formula
    x = x0 + vx0 * t;
    y = y0 + vy0 * t + 0.5f * g * t * t;
    vy = vy0 + g * t;
}

//lamina caida con resistencia

Lamina::Lamina (float x, float y, float g, float k, int dano)
    : Obstaculo(x, y, 0, 0, dano, true), g(g), k(k){
    if (k <= 0 )
        throw std::invalid_argument("Lamina: k debe ser mayor que 0 bobo");

}

void Lamina::actualizar(float dt) {
    //se integra con euler
    float ay = g - k *vy; //la aceleracion cambia segun la velocidad
    vy += ay *dt;
    y += vy *dt;
}
//viga ocilador amortiguado
    Viga::Viga(float xc, float y, float longitud, float amplitud, float w, float b)
        : Obstaculo (xc + amplitud, y, 0, 0, 0, false), longitud(longitud), xc(xc), w(w), b(b) {
        if (longitud <= 0)
            throw std::invalid_argument("Viga, la longitud debe ser mayor que 0");

    }
    void Viga::actualizar(float dt) {
        float ax = -w * w * (x - xc) - 2 * b * vx;  // resorte + freno
        vx += ax * dt;
        x += vx * dt;

    }
    void Viga::empujar(float impulso) {
        vx += impulso;

    }
