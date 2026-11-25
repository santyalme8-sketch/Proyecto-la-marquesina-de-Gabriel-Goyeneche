#ifndef AGENTEGOYENECHE_H
#define AGENTEGOYENECHE_H

#include "TiposAgente.h"
#include "Aprendizaje.h"
#include "Accion.h"
#include "Razonamiento.h"
#include "Percepcion.h"
#include <map>

//une todas las partes
//el juego solo habla con esta clase
class AgenteGoyeneche {
private:
    ConfigDificultad config;
    Percepcion *percepcion; //el agente es dueño de sus partes
    Razonamiento* razonamiento;
    Accion* accion;
    Aprendizaje* aprendizaje;

    float tiempoDesdeDisparo;
    std::map<int, Tactica> disparosPendientes; //id -> tactica esperando el resultado

public:
    AgenteGoyeneche(const ConfigDificultad& config, unsigned semilla = std::random_device{}());
    ~AgenteGoyeneche();


    //no se copia porque tiene punteros propios
    AgenteGoyeneche(const AgenteGoyeneche&) = delete;
    AgenteGoyeneche& operator=(const AgenteGoyeneche&) = delete;

    //llama en cada framse. si decide disparar vuelve true y llena disparo

    bool actualizar (float dt, const LecturaYuuko& yuuko,
                    float posGoyX, float posGoyY, DatosDisparo& disparo);
    //el juego avisa como termino el proyectil, si pego o salio de la pantalla
    void notificarResultado(int idDisparo, bool acerto, bool yuukoSalto);

    const Aprendizaje& getAprendizaje() const { return *aprendizaje; }
    void reiniciar();

};

#endif // AGENTEGOYENECHE_H
