#include "AgenteGoyeneche.h"

AgenteGoyeneche::AgenteGoyeneche (const ConfigDificultad& config) : config(config), tiempoDesdeDisparo(0) {
    percepcion = new Percepcion(config.intervaloPercepcion);
    razonamiento = new Razonamiento(config.errorPrediccion, config.usaAprendizaje);
    accion = new Accion();
    aprendizaje = new Aprendizaje(config.tasaAprendizaje);

}

AgenteGoyeneche::~AgenteGoyeneche(){
    delete percepcion;
    delete razonamiento;
    delete accion;
    delete aprendizaje;

}

bool AgenteGoyeneche::actualizar(float dt, LecturaYuuko yuuko, float posGoyX, float posGoyY, DatosDisparo& disparo)

{
    percepcion->percibir(dt, yuuko);

   tiempoDesdeDisparo  += dt;
    if (tiempoDesdeDisparo < config.intervaloDisparo) return false;

    Observacion obs = percepcion->observar();
    if (!obs.valida) return false;
    tiempoDesdeDisparo = 0;

    Decision d = razonamiento -> decidir(obs, *aprendizaje, posGoyX, posGoyY);

    disparo = accion-> disparar (d, posGoyX, posGoyY);
    disparosPendientes[disparo.id] = disparo.tactica;
    return true;

}

void AgenteGoyeneche::notificarResultado(int idDisparo, bool acerto, bool yuukoSalto) {

    if (disparosPendientes.count(idDisparo) == 0) return;
    RegistroAtaque r;
    r.id = idDisparo;
    r.tactica = disparosPendientes[idDisparo];
    r.acerto = acerto;
    r.yuukoSalto = yuukoSalto;
    aprendizaje->registrar(r);
    disparosPendientes.erase(idDisparo);
}

void AgenteGoyeneche::reiniciar() {
    percepcion ->reiniciar();
    aprendizaje->reiniciar();
    disparosPendientes.clear();
    tiempoDesdeDisparo = 0;

}
