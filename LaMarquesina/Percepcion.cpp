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
    if (acumulado < intervalo) return false; //todavia no toca mirar
    acumulado = 0;
                lecturas.push_back(lectura);
    if ((int)lecturas.size() > maxLecturas)
        lecturas.pop_front(); //se olvida de la lectura mas vieja
    return true;

}

Observacion Percepcion::observar() const {
    Observacion obs;
    if (lecturas.empty()) return obs; //si es valida = false

    obs.actual =lecturas.back();
    obs.valida =true;

    //promedio de velocidades ym conteo de saltos
    for (const LecturaYuuko& l : lecturas) {
        obs.velPromX += l.vx;
        obs.velPromY += l.vy;
        if (l.estado == EstadoYuuko::Saltando) obs.saltosRecientes++;

    }
    obs.velPromX /= lecturas.size();
    obs.velPromY /= lecturas.size();
    obs.rapidez = std::sqrt(obs.velPromX * obs.velPromX + obs.velPromY * obs.velPromY);
    return obs;
}

void Percepcion::reiniciar() {
    lecturas.clear();
    acumulado = intervalo;

}