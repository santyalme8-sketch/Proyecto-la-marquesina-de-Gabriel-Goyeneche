#ifndef GOYENECHE_H
#define GOYENECHE_H
#include "Persona.h"
#include "AgenteGoyeneche.h"

class Goyeneche : public Persona {
private:
    AgenteGoyeneche* agente;
    float xCentro;

    float amplitud;
    float tiempo;

public:
    Goyeneche(float xCentro, float y, float amplitud, ConfigDificultad& dificultdad);
    ~Goyeneche();
    void actualizar(float dt) override;

    bool ejecutar(float dt, LecturaYuuko& yuuko, DatosDisparo& disparo);
    void registrarResultado(int idDisparo, bool acerto, bool yuukoSalto);
    const Aprendizaje& getAprendizaje() const { return agente -> getAprendizaje(); }

};

#endif // GOYENECHE_H
