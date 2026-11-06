#include "Clases.h"
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