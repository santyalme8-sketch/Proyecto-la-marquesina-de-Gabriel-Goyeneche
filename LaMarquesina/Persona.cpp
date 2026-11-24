#include "Persona.h"
#include <stdexcept>

Persona::Persona(float x, float y, int salud)
    : Cuerpo (x,y), puntosDeSalud(salud), saludMaxima(salud), estado(true) {
    if (salud <= 0)
        throw std::invalid_argument("Persona: la salud inicial debe ser mayor a 0!" );

}
void Persona::recibirDano(int cantidad) {
        if (cantidad < 0 )
        throw std::invalid_argument("Persona: el dano no puede ser negativo, gilipollas XD");
                puntosDeSalud -= cantidad;
        if (puntosDeSalud <- 0){
            puntosDeSalud = 0;
            estado = false;

        }



        }
