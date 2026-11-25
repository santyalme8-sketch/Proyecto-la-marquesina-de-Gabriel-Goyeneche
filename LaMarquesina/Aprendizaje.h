#ifndef APRENDIZAJE_H
#define APRENDIZAJE_H

#include <deque>
#include <map>
#include "Tiposagente.h"

//lo que guarda de cada ataque
struct RegistroAtaque {
    int id;
    Tactica tactica;
    bool acerto; // le pego a yuuko? T_T
    bool yuukoSalto; //yuuko salto para esquivarlo? ヽ(°〇°)ﾉ
};

//aprendizaje: guarda los ultimos 10 ataques y con eso calcula un peso para cada tactica
// mas peso = mas probable que la use ˙𐃷˙

class Aprendizaje {
private :
    std::deque<RegistroAtaque> historial; // ultimos n ataques
    std::map<Tactica, float> pesos; // peso de cada tactica
    int maxHistorial;
    float tasa; //tasa de aprendizaje lol (¬_¬")

    void recalcularPesos();
public:
    Aprendizaje(float tasa, int maxHistorial = 10);
//el juego avisa como termino un disparo
    void registrar(const RegistroAtaque& r);
    float peso(Tactica t) const;
    const std::deque<RegistroAtaque>& getHistorial() const { return historial; }
    void reiniciar();


};

#endif // APRENDIZAJE_H
