#include "Aprendizaje.h"
#include <stdexcept>

Aprendizaje::Aprendizaje(float tasa, int maxHistorial)
    : maxHistorial(maxHistorial), tasa(tasa) {
    if (tasa <0 || maxHistorial <= 0)
        throw std::invalid_argument("Aprendizaje: parametros invalidos (￣ε￣＠)");
    reiniciar();

}

void Aprendizaje::registrar(const RegistroAtaque& r) {
    historial.push_back(r);
    if ((int)historial.size() > maxHistorial)
        historial.pop_front();
    recalcularPesos();
}

float limitar(float valor) {
    if (valor < 0.1f) return 0.1f;
    if (valor > 5.0f) return 5.0f;
    return valor;

}

void Aprendizaje::recalcularPesos() {
    pesos[Tactica::Directo] = 1.0f;
     pesos[Tactica::Predictivo] = 1.0f;
     pesos[Tactica::Aereo] = 1.0f;

     for (int i = 0; i < historial.size(); i++) {
              RegistroAtaque r = historial[i];
              if (r.acerto) {
                  pesos[r.tactica] += tasa;
              } else {
                  pesos[r.tactica] -= tasa * 0.5f;
                  if (r.yuukoSalto && r.tactica != Tactica::Aereo)
                      pesos [Tactica::Aereo] += tasa;
              }
          }

}

float Aprendizaje::peso(Tactica t) const{
    return pesos.at(t);

}

void Aprendizaje::reiniciar() {
    historial.clear();
    recalcularPesos();

}