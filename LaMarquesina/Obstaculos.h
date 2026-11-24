#ifndef OBSTACULOS_H
#define OBSTACULOS_H
#include "Cuerpo.h"

//todo lo que le hace dano a yuuko viene del obstaculo del momento 2

class Obstaculo : public Cuerpo {
protected:
    int dano; //cuanta salud le quita a yuuko UnU
    bool destructible; //si se rompe cuando choca

public:
    Obstaculo(float x, float y, float vx, float vy, int dano, bool destructible);
    int getDano() const {return dano; }

};

/*fisica de tiro parabolico
x(t) = x0 + vx0*t
y(t) = y0 + vy0*t  + g*t^2/2 (y crece hacia abajo)
*/

class Proyectil : public Obstaculo {
private:
    float x0, y0, vx0, vy0;
    float g;
    float t; //tiempo desde el disparo
    int id; //es para avisarle al agente como termino el disparo

public:
    Proyectil(float x0, float y0, float vx0, float vy0, float g, int id, int dano);
    void actualizar(float dt) override;
    int getId() const {return id; }

};


/* fisica  de caida con resistencia del aire (para las laminas que se desprenden)
 * a = g - k*v    -> la aceleración NO es constante
 * llega a una velocidad terminal v = g/k
*/

class Lamina : public Obstaculo {

private:
    float g; //gravedad
    float k; //coeficiente de arrastre
public:
    Lamina(float x, float y, float g, float k, int dano);
    void actualizar(float dt) override;
    float velocidadTerminal() const {return g / k;}

};

/* fisica de movimiento armonico amortiguado para las vigas colgantes
 * a = -w^2 * (x - xc) - 2*b*v
 * w = qué tan rápido oscila, b = qué tan rápido se frena
*/
class Viga : public Obstaculo {

private:
    float longitud;
    float amplitud;
    float xc; //es el punto de equilibrio
    float w; // frecuencia angular
    float b; // amortiguamiento

public:
Viga(float x, float y, float longitud, float amplitud, float w, float b);
    void actualizar(float dt) override;
void empujar(float impulso);
    float desplazamiento() const { return x - xc; }
    float getLongitud() const {return longitud; }
};
#endif // OBSTACULOS_H
