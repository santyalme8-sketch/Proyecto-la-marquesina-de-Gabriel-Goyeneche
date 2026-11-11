#include <iostream>

#include "Clases.h"
float  calcularposicionx(float x0, float vx0, float tiempo, float aceleracion ){
    return vx0*tiempo+((aceleracion)*(tiempo*tiempo))/2;
}
float calcularposiciony(float y0, float vy0, float t){
    return vy0-((9.8)*(t*t))/2;
}
int main()
{
     float duracion_total = 2.0f; // 2 segundos reales
     float fps = 60.0f;
     float dt = 1.0f / fps;
     int total_pasos=duracion_total/dt;
     Yuuko jugadora;
    Goyoneche enemigo;
    Proyectil bala(0.4f, 25.0f, 30.0f);
    Viga obstaculoPared(12.0f);
    std::cout << "Velocidad inicial de Yuuko: " << jugadora.getVelocidad() << "\n";
    std::cout << "Velocidad inicial de Goyoneche: " << enemigo.getVelocidad() << "\n\n";
    jugadora.recibirDaño(30);
    for (int i = 0; i <= total_pasos; ++i) {
        float t = i * dt;
        std::cout<<"la posicion en x es:"<<calcularposicionx(jugadora.getposicionx(),jugadora.getVelocidad(),t,5.0f);
        std::cout<<"  la posicion en y es:"<<calcularposiciony(jugadora.getposiciony(),5.0,t);
        std::cout<<"\n";
    }
    jugadora.activarPanico();
    for (int i = 0; i <= total_pasos; ++i) {
        float t = i * dt;
        std::cout<<"la posicion en x es:"<<calcularposicionx(jugadora.getposicionx(),jugadora.getVelocidad(),t,5.0f);
        std::cout<<"  la posicion en y es:"<<calcularposiciony(jugadora.getposiciony(),5.0,t);
        std::cout<<"\n";
    }
    return 0;
    }

