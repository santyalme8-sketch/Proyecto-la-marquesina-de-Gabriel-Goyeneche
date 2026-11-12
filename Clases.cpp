#include "Clases.h"
#include "iostream"

Cuerpo::Cuerpo(float vx, float vy, float ax, float ay)
    : vx(vx), vy(vy), ax(ax), ay(ay) {}
Persona::Persona(int salud, float vx, float vy, float ax, float ay): Cuerpo(vx, vy, ax, ay), puntosDeSalud(salud), estado(true), posicionx(0.0f) {
    this->puntosDeSalud = salud;
    this->estado = true;
}

int Persona::recibirDaño(int cantidad) {
    puntosDeSalud -= cantidad;
    if (puntosDeSalud <= 0) {
        puntosDeSalud = 0;
        estado = false;
        return puntosDeSalud;
    } else {
        return puntosDeSalud;
    }
}
int Persona::getPuntosDeSalud()  {
    return puntosDeSalud; }
bool Persona::getEstado()  {
    return estado; }

Yuuko::Yuuko() : Persona(100,18.5f,5.0f) {
    setposicionx(0.0f);
    setposiciony(0.0f);
}


Goyoneche::Goyoneche(): Persona(150,12.0f,3.0f){

}


void Yuuko::activarPanico() {
    modoPanico = true;
    vx *= 1.5f;
    std::cout << "Yuuko entro en Panico. Velocidad aumentada a: " << vx << "\n";
}


Obstaculo::Obstaculo(int v, bool dest, float vx, float vy, float ax, float ay): Cuerpo(vx, vy, ax, ay), vida(v), destructible(dest) {}

Proyectil::Proyectil(float tam, float d, float vx, float vy)
    : Obstaculo(1, true, vx, vy), tamaño(tam), daño(d) {}



Viga::Viga(float len): Obstaculo(999, false, 0.0f, 0.0f){
    this->longitud=len;
}

void Persona::setposicionx(float posx){
    this->posicionx=posx;
}
void Persona::setposiciony(float posy){
    this->posiciony=posy;
}
