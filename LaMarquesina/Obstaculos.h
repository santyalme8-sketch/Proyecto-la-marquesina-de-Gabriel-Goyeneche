#ifndef OBSTACULOS_H
#define OBSTACULOS_H
#include "Cuerpo.h"

class Obstaculo : public Cuerpo {
protected:
    int dano;
    bool destructible;

public:
    Obstaculo(float x, float y, float vx, float vy, int dano, bool destructible);
    int getDano() const {return dano; }

};

class Proyectil : public Obstaculo {
private:
    float x0, y0, vx0, vy0;
    float g;
    float t;
    int id;

public:
    Proyectil(float x0, float y0, float vx0, float vy0, float g, int id, int dano);
    void actualizar(float dt) override;
    int getId() const {return id; }

};

class Lamina : public Obstaculo {

private:
    float g;
    float k;
public:
    Lamina(float x, float y, float g, float k, int dano);
    void actualizar(float dt) override;
    float velocidadTerminal() const {return g / k;}

};

class Viga : public Obstaculo {

private:
    float longitud;
    float amplitud;
    float xc;
    float w;
    float b;
public:
Viga(float x, float y, float longitud, float amplitud, float w, float b);
    void actualizar(float dt) override;
void empujar(float impulso);
    float desplazamiento() const { return x - xc; }
    float getLongitud() const {return longitud; }
};
#endif // OBSTACULOS_H
