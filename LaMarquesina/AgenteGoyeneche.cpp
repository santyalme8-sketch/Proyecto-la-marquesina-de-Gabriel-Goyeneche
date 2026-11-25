#include "AgenteGoyeneche.h"

AgenteGoyeneche::AgenteGoyeneche (const ConfigDificultad& config, unsigned semilla)
    : config(config), tiempoDesdeDisparo(0) {
    percepcion = new Percepcion(config.intervaloPercepcion);
    razonamiento = new Razonamiento(config.errorPrediccion, config.usaAprendizaje, semilla);
    accion = new Accion();
    aprendizaje = new Aprendizaje(config.tasaAprendizaje);

}

AgenteGoyeneche::~AgenteGoyeneche(){
    delete percepcion;
    delete razonamiento;
    delete accion;
    delete aprendizaje;

}

bool AgenteGoyeneche::actualizar(float dt, const LecturaYuuko& yuuko,
                                 float posGoyX, float posGoyY, DatosDisparo& disparo)

{
    //percepcion
    percepcion->percibir(dt, yuuko);
    //ya hay que disparar?
   tiempoDesdeDisparo  += dt;
    if (tiempoDesdeDisparo < config.intervaloDisparo) return false;

    Observacion obs = percepcion->observar();
    if (!obs.valida) return false;
    tiempoDesdeDisparo = 0;


    //razonamiento
    Decision d = razonamiento -> decidir(obs, *aprendizaje, posGoyX, posGoyY);

    //accion
    disparo = accion-> disparar (d, posGoyX, posGoyY);
    disparosPendientes[disparo.id] = disparo.tactica;
    return true;

}

void AgenteGoyeneche::notificarResultado(int idDisparo, bool acerto, bool yuukoSalto)
{
    auto it = disparosPendientes.find(idDisparo);
    if (it == disparosPendientes.end()) return; //id desconocido se ignora

    //aprendizaje

    aprendizaje ->registrar({idDisparo, it->second, acerto, yuukoSalto});
    disparosPendientes.erase(it);
}

void AgenteGoyeneche::reiniciar() {
    percepcion ->reiniciar();
    aprendizaje->reiniciar();
    disparosPendientes.clear();
    tiempoDesdeDisparo = 0;

}
