#ifndef AGENTEGOYENECHE_H
#define AGENTEGOYENECHE_H

#include "TiposAgente.h"
#include "Aprendizaje.h"
#include "Accion.h"
#include "Razonamiento.h"
#include "Percepcion.h"
#include <map>


class AgenteGoyeneche {
private:
    ConfigDificultad config;
    Percepcion *percepcion;
    Razonamiento* razonamiento;
    Accion* accion;
    Aprendizaje* aprendizaje;

    float tiempoDesdeDisparo;
    std::map<int, Tactica> disparosPendientes;

public:
    AgenteGoyeneche(const ConfigDificultad& config);
    ~AgenteGoyeneche();

    bool actualizar(float dt, LecturaYuuko yuuko, float posGoyX, float posGoyY, DatosDisparo& disparo);
    void notificarResultado(int idDisparo, bool acerto, bool yuukoSalto);
    const Aprendizaje& getAprendizaje() const { return *aprendizaje; }
    void reiniciar();
};

#endif // AGENTEGOYENECHE_H
