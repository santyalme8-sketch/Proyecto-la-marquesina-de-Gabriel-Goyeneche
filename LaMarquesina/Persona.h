#ifndef PERSONA_H
#define PERSONA_H
#include "Cuerpo.h"

class Persona : public Cuerpo {
protected:
    int puntosDeSalud;
    int saludMaxima;
    bool estado;

public:
    Persona(float x, float y, int salud);

    virtual void recibirDano(int cantidad);
    int getPuntosDeSSalud() const {return puntosDeSalud;}
    int getSaludMaxima() const {return saludMaxima;}
    bool getEstado() const {return estado; }


};

#endif // PERSONA_H
