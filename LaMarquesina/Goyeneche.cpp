#include "Goyeneche.h"
#include <cmath>

const float LADO_GOYENECHE = 48;

Goyeneche::Goyeneche(float xCentro, float y, float amplitud, const ConfigDificultad& dificultdad)
    : Persona(xCentro, y, 150), agente(new AgenteGoyeneche(dificultdad)),
    xCentro(xCentro), amplitud(amplitud), tiempo(0) {}

Goyeneche::~Goyeneche() {
    delete agente;

}

void Goyeneche::actualizar(float dt) {
    tiempo += dt;
    x = xCentro + amplitud * std::sin(0.5f * tiempo);

}

bool Goyeneche::ejecutar(float dt, const LecturaYuuko& yuuko, DatosDisparo& disparo)
{
    //dispara desdde abajo y al centro de su cuerpo
    return agente->actualizar (dt, yuuko, x + LADO_GOYENECHE / 2, y + LADO_GOYENECHE, disparo);

}

void Goyeneche::registrarResultado(int idDisparo, bool acerto, bool yuukoSalto) {
    agente->notificarResultado(idDisparo, acerto, yuukoSalto);
}