#include "Aprendizaje.h"
#include <algorithm>
#include <stdexcept>

//deberia añadir un easteregg? (￣▽￣)ノ

Aprendizaje::Aprendizaje(float tasa, int maxHistorial)
    : maxHistorial(maxHistorial), tasa(tasa) {
    if (tasa <0 || maxHistorial <= 0)
        throw std::invalid_argument("Aprendizaje: parametros invalidos (￣ε￣＠)");
    reiniciar();

}

void Aprendizaje::registrar(const RegistroAtaque& r) {
    historial.push_back(r);
    if ((int)historial.size() > maxHistorial)
        historial.pop_front(); //solo recuerda los ultimos n
    recalcularPesos();
}

//los pesos se calculan desde 0 con el historial actual
//asi lo viejo se olvida solo cuando sale de la ventana de 10
void Aprendizaje::recalcularPesos() {
    pesos[Tactica::Directo] = 1.0f;
     pesos[Tactica::Predictivo] = 1.0f;
     pesos[Tactica::Aereo] = 1.0f;

     for (const RegistroAtaque& r : historial) {
         if (r.acerto) {
             pesos [r.tactica] += tasa; //lo que funciona se repite

         } else {
             pesos [r.tactica] -= tasa * 0.5f; //lo que falla se usa menos
             //regla: si esquivo un tiro rasante saltando
             //el tiro aereo se vuelve mas atractivo
             if (r.yuukoSalto && r.tactica != Tactica::Aereo)
                 pesos [Tactica::Aereo]+= tasa;
         }
     }
     //ningun peso baja de 0.1 para que nunca deje de usar una tactica
     for (auto&par : pesos)
         par.second = std::clamp(par.second, 0.1f, 5.0f);


}

float Aprendizaje::peso(Tactica t) const{
    return pesos.at(t);

}

void Aprendizaje::reiniciar() {
    historial.clear();
    recalcularPesos();

}