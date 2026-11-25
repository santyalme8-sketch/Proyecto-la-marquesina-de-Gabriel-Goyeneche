#ifndef GOYENECHE_H
#define GOYENECHE_H
#include "Persona.h"
#include "AgenteGoyeneche.h"

//el jefe es una persona (UML del momento 2) que tiene un agente inteligente
//la herencia de goyeneche ES una persona y la composicion de goyeneche tiene un AgenteGoyeneche.

class Goyeneche : public Persona {
private:
    AgenteGoyeneche* agente; //goyeneche es dueño de su ia
    float xCentro; //se pasea alrededor de este punto vale? xd

    float amplitud;
    float tiempo;

public:
    Goyeneche(float xCentro, float y, float amplitud, const ConfigDificultad& dificultdad);
    ~Goyeneche();

    //nmo se copia porque tiene un puntero propio

    Goyeneche(const Goyeneche&)  = delete;
    void actualizar(float dt) override; // se pasea de lado a lado

    //le pasa la lectura de yuuko a su ia y es true si decidio disparar
    bool ejecutar(float dt, const LecturaYuuko& yuuko, DatosDisparo& disparo);
    void registrarResultado(int idDisparo, bool acerto, bool yuukoSalto);
    const Aprendizaje& getAprendizaje() const { return agente -> getAprendizaje(); }

};

#endif // GOYENECHE_H
