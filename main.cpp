#include <iostream>

#include "Clases.h"
int main()
{
     Yuuko jugadora;
    Goyoneche enemigo;
    Proyectil bala(0.4f, 25.0f, 30.0f);
    Viga obstaculoPared(12.0f);
    std::cout << "Velocidad inicial de Yuuko: " << jugadora.getVelocidad() << "\n";
    std::cout << "Velocidad inicial de Goyoneche: " << enemigo.getVelocidad() << "\n\n";
    jugadora.recibirDaño(30);
    jugadora.activarPanico();
    return 0;
    }

