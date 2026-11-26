#include "Razonamiento.h"
#include <cmath>
#include <cstdlib>
#include <stdexcept>

Razonamiento::Razonamiento(float errorPrediccion, bool usaAprendizaje)
    : errorPrediccion(errorPrediccion), usaAprendizaje(usaAprendizaje){}
float Razonamiento::azar(float  minimo, float maximo) {
    float entre0y1 = rand() / (float)RAND_MAX;
    return minimo + entre0y1 * (maximo - minimo);
}
 float Razonamiento::factorSituacion(Tactica t, const Observacion & obs) {
     if (t == Tactica::Directo) {
         if (obs.rapidez < 40) return 1.5f;
 }
     if (t == Tactica::Predictivo) {
     if (obs.rapidez > 200 || obs.actual.estado == EstadoYuuko::Panico)
             return 1.5f;
     return 1.0f;

     }
     if (obs.saltosRecientes >= 2) return 1.3f;
     return 1.0f;

}

Tactica Razonamiento::elegirTactica(const Observacion& obs, const Aprendizaje& apr) {
    float pDirecto = factorSituacion(Tactica::Directo, obs);
    float pPredictivo = factorSituacion(Tactica::Predictivo, obs);
    float pAereo = factorSituacion(Tactica::Aereo, obs);
    if (usaAprendizaje) {
        pDirecto *= apr.peso(Tactica::Directo);
        pPredictivo *=apr.peso(Tactica::Predictivo);
        pAereo *=apr.peso(Tactica::Aereo);
    }

    float total = pDirecto + pPredictivo + pAereo;
    float r = azar(0, total);
    if (r < pDirecto) return Tactica::Directo;
    if (r <pDirecto + pPredictivo) return Tactica::Predictivo;
    return Tactica::Aereo;
}


Decision Razonamiento::decidir(const Observacion& obs, const Aprendizaje & apr, float origenX, float origenY) {
    if (!obs.valida)
        throw std::logic_error("Razonamiento: no hay observacion de Yuuko todavia ( ⁰▿⁰)");
    Decision d;
    d.tactica = elegirTactica(obs, apr);
    float dx =obs.actual.x - origenX;
    float dy =obs.actual.y - origenY;
    float distancia =std::sqrt(dx * dx + dy * dy);
    d.tiempoVuelo = distancia / 400;
    if (d.tiempoVuelo < 0.6f) d.tiempoVuelo = 0.6f;
     if (d.tiempoVuelo > 2.0f) d.tiempoVuelo = 2.0;

    d.objetivoY = obs.actual.y;

if (d.tactica == Tactica::Directo) {
     d.objetivoX = obs.actual.x;
     } else if (d.tactica == Tactica::Predictivo) {
     float error = azar(1 - errorPrediccion, 1 + errorPrediccion);
     d.objetivoX = obs.actual.x + obs.velPromX * d.tiempoVuelo * error;
     } else {
     d.objetivoX = obs.actual.x + obs.velPromX * d.tiempoVuelo * 0.5f;
     d.tiempoVuelo = d.tiempoVuelo * 1.6f;
    }
 return d;
}

