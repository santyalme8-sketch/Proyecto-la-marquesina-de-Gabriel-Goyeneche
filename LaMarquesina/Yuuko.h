#ifndef YUUKO_H
#define YUUKO_H

#include "Persona.h"
#include "TiposAgente.h"

class Yuuko : public Persona {
private:
    bool enSuelo;
    float tiempoPanico;
    float tiempoAturdida;
    float esperaMalaSuerte;
    bool panicoPorVidaUsado;
    bool aturdirAlTerminar;
    float velocidad;

public:
    float getVelocidad() const { return velocidad;}
    Yuuko(float x, float y);
    void actualizar(float dt) override;
    void recibirDano(int cantidad) override;
    bool llamarMalaSuerte();
    float multiplicadorVelocidad() const;
    EstadoYuuko estadoActual() const;

    bool enPanico() const { return tiempoPanico > 0; }
    bool aturdida() const { return tiempoAturdida > 0; }
    bool getEnSuelo() const { return enSuelo; }
    void setEnSuelo(bool s) { enSuelo = s; }

};


#endif // YUUKO_H
