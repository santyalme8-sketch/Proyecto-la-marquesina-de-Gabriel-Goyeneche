#include "Percepcion.h"
#include <cmath>
#include <stdexcept>

Percepcion::Percepcion(float intervalo, int maxLecturas)
    : maxLecturas(maxLecturas), intervalo(intervalo), acumulado(intervalo) {
    if (intervalo <= 0 || maxLecturas <= 0 )
        throw std::invalid_argument("Percepcion: intervalo y maxLecturas deben ser positivos bro");

}

bool Percepcion::percibir(float dt, const LecturaYuuko& lectura) {
    acumulado += dt;
    if (acumulado < 0) return false;
    acumulado = 0;
                lecturas.push_back(lectura);
    if ((int)lecturas.size() > maxLecturas)
        lecturas.pop_front();
    return true;

}

Observacion Percepcion::observar() const {
    Observacion obs;
    if (lecturas.empty()) return obs;

    obs.actual =lecturas.back();
    obs.valida =true;

    for (int i = 0; i < lecturas.size(); i++) {
        obs.velPromX += lecturas[i].vx;
        obs.velPromY += lecturas[i].vy;
        if (lecturas[i].estado == EstadoYuuko::Saltando) obs.saltosRecientes++;
    }


    obs.velPromX /= lecturas.size();
    obs.velPromY /= lecturas.size();
    obs.rapidez = std::sqrt(obs.velPromX * obs.velPromX + obs.velPromY * obs.velPromY);
    return obs;
}

void Percepcion::reiniciar() {
    lecturas.clear();
    acumulado = 0;

}