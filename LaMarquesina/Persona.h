#ifndef PERSONA_H
#define PERSONA_H
#include "Cuerpo.h"

//los datos de los personajes: Yuuko y goyeneche xd
//no implementa actualizar() entonces sigue siendo abstracta

class Persona : public Cuerpo {
protected:
    int puntosDeSalud;
    int saludMaxima;
    bool estado; //true = con vida, false = derrotada

public:
    Persona(float x, float y, int salud);

    //aqui se usa virtual para que yuuko la sobreescriba para activar el modo de panico
    virtual void recibirDano(int cantidad);
    int getPuntosDeSSalud() const {return puntosDeSalud;}
    int getSaludMaxima() const {return saludMaxima;}
    bool getEstado() const {return estado; }


};

#endif // PERSONA_H
