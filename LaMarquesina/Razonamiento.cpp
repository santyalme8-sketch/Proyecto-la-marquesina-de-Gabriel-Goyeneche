#include "Razonamiento.h"
#include <algorithm>
#include <cmath>

#include <stdexcept>

Razonamiento::Razonamiento(float errorPrediccion, bool usaAprendizaje, unsigned semilla)
    : errorPrediccion(errorPrediccion), usaAprendizaje(usaAprendizaje), generador(semilla) {}

float Razonamiento::factorSituacion(Tactica t, const Observacion & obs) const {
    bool quieta= obs.rapidez < 40.0f;
    bool rapida = obs.rapidez >200.0f || obs.actual.estado == EstadoYuuko::Panico;
    bool saltona = obs.saltosRecientes >= 2;

    switch  (t) {
    case Tactica::Directo: return quieta ? 1.5f : 0.8f; //quieta: tiro directo
    case Tactica::Predictivo: return rapida ? 1.5f : 1.0f; //corriendo: adelantarse
    case Tactica::Aereo: return saltona ? 1.3f : 1.0f; //saltando tiro alto

        }
    return 1.0f;

}

//ruletaaaa: cada tactica tiene un puntaje y se sortea proporcional a el
Tactica Razonamiento::elegirTactica(const Observacion& obs, const Aprendizaje& apr) {
    Tactica opciones[3] = {Tactica::Directo, Tactica::Predictivo, Tactica::Aereo};
    float puntajes[3];
    float total = 0;

    for (int i = 0; i < 3; i++) {
        float pesoAprendido = usaAprendizaje ? apr.peso(opciones[i]) : 1.0f;
        puntajes[i] = pesoAprendido * factorSituacion(opciones[i], obs);
        total += puntajes[i];
    }

    std::uniform_real_distribution<float> dist(0.0f, total);
    float r = dist(generador);
    for (int i = 0; i < 3; i++) {
        if (r <puntajes[i]) return opciones[i];
        r -= puntajes [i];

    }
    return opciones [2];
}

Decision Razonamiento::decidir(const Observacion& obs, const Aprendizaje & apr,
                               float origenX, float origenY) {
    if (!obs.valida)
        throw std::logic_error("Razonamiento: no hay observacion de Yuuko todavia ( ⁰▿⁰)");
    Decision d;
    d.tactica = elegirTactica(obs, apr);

    //tiempodde vuelo segun la distancia, entre mas lejos mas tiempoo
    float dx =obs.actual.x - origenX;
    float dy =obs.actual.y - origenY;
    float distancia =std::sqrt(dx * dx + dy * dy);
    d.tiempoVuelo = std::clamp(distancia / 400.0f, 0.6f, 2.0f);

    switch (d.tactica) {
    case Tactica::Directo:
        // apunta a donde esta yuuko ahora mismo
        d.objetivoX = obs.actual.x;
        d.objetivoY = obs.actual.y;
        break;

    case Tactica::Predictivo: {
        // apunta a donde yuuko va a estar, posición + velocidad * tiempo.
        //el error de predicción depende de la dificultad.
        std::uniform_real_distribution<float> ruido(1.0f - errorPrediccion, 1.0f + errorPrediccion);
        d.objetivoX = obs.actual.x + obs.velPromX * d.tiempoVuelo * ruido(generador);
        d.objetivoY = obs.actual.y;
        break;
    }

    case Tactica::Aereo:
        // tiro alto y lento que cae casi en vertical y castiga a quien salta
        d.objetivoX = obs.actual.x + obs.velPromX * d.tiempoVuelo * 0.5f;
        d.objetivoY = obs.actual.y;
        d.tiempoVuelo *= 1.6f;
        break;
    }
    return d;
}

