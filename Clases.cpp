#include "Clases.h"
#include "iostream"
Cuerpo::Cuerpo(float velocidad, float aceleracion){
    this->velocidad=velocidad;
    this->aceleracion=aceleracion;
}
Persona::Persona(int salud,float velo,float ace): Cuerpo(velo, ace) {
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
}


Goyoneche::Goyoneche(): Persona(150,12.0f,3.0f){

}

float Goyoneche::getVelocidad(){
    return velocidad;
}
void Yuuko::activarPanico() {
    modoPanico = true;
    velocidad *= 1.5f;
    std::cout << "Yuuko entro en Panico. Velocidad aumentada a: " << velocidad << "\n";
}
float Yuuko::getVelocidad(){
    return velocidad;
}
Obstaculo::Obstaculo(int v, bool dest, float vel, float acel) : Cuerpo(vel, acel), vida(v), destructible(dest) {}

Proyectil::Proyectil(float tam, float d, float vel): Obstaculo(1, true, vel, 0.0f){
    this->tamaño=tam;
    this->daño=d;
}
Viga::Viga(float len): Obstaculo(999, false, 0.0f, 0.0f){
    this->longitud=len;
}