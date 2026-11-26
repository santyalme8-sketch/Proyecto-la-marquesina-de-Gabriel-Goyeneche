#ifndef APRENDIZAJE_H
#define APRENDIZAJE_H

#include <deque>
#include <map>
#include "TiposAgente.h"


struct RegistroAtaque {
    int id;
    Tactica tactica;
    bool acerto;
    bool yuukoSalto;
};
class Aprendizaje {
private :
    std::deque<RegistroAtaque> historial;
    std::map<Tactica, float> pesos;
    int maxHistorial;
    float tasa;

    void recalcularPesos();
public:
    Aprendizaje(float tasa, int maxHistorial = 10);
    void registrar(const RegistroAtaque& r);
    float peso(Tactica t) const;
    const std::deque<RegistroAtaque>& getHistorial() const { return historial; }
    void reiniciar();


};

#endif // APRENDIZAJE_H
