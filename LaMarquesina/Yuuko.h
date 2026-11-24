#ifndef YUUKO_H
#define YUUKO_H

#include "Persona.h"
#include "TiposAgente.h" //para yuuko jeje

//la prota hereda salud de Persona y posicion/velocidad de Cuerpo
//las dos caracteristicas: PANICO EXTREMO y MALA SUERTE

class Yuuko : public Persona {
private:
    bool enSuelo;
    float tiempoPanico; // > 0 mientras esta en panico
    float tiempoAturdida; // >0 mientras esta aturdida
    float esperaMalaSuerte; // tiempo para volver a usar la mala suerte
    bool panicoPorVidaUsado; //el panico por vida baja pasa una sola vez
    bool aturdirAlTerminar; //despues del panico voluntario queda aturdida


public:
    static constexpr float VELOCIDAD_BASE = 260.0f;
    Yuuko(float x, float y);
    void actualizar(float dt) override;
    void recibirDano(int cantidad) override;   // agrega el panico a lo de Persona
    bool llamarMalaSuerte();                   // false si todavia no puede
    float multiplicadorVelocidad() const;
    EstadoYuuko estadoActual() const;

    bool enPanico() const { return tiempoPanico > 0; }
    bool aturdida() const { return tiempoAturdida > 0; }
    bool getEnSuelo() const { return enSuelo; }
    void setEnSuelo(bool s) { enSuelo = s; }
};


#endif // YUUKO_H
