#include <iostream>
#include "fstream"
#include "Clases.h"

float  calcularposicionx(float x0, float vx0, float tiempo, float aceleracion ){
    return x0+vx0*tiempo+((aceleracion)*(tiempo*tiempo))/2;
}
float calcularposiciony(float y0, float vy0, float t){
    return y0+vy0*t-((9.8)*(t*t))/2;
}
float momentolineal(float m1, float v1, float m2, float v2, float elasticidad) {
    return (m1 * v1 + m2 * v2 + m1 * elasticidad * (v1 - v2)) / (m1 + m2);
}
float rebotarpared(float velocidad, float elasticidad) {
    return -velocidad * elasticidad;
}
float calcularvelocidad(float v0, float aceleracion, float t) {
    return v0 + aceleracion * t;
}
int main()
{
    std::ofstream archivo("Datos.txt");
     float duracion_total = 2.0f;
     float fps = 60.0f;
     float dt = 1.0f / fps;
     int total_pasos=duracion_total/dt;
     float x=120.0f,y=120.0f;
     float tx=0.0f,ty=0.0f;
     Yuuko jugadora;
    for (int i = 0; i <= total_pasos; ++i) {
         float posx=calcularposicionx(jugadora.getposicionx(),jugadora.getvx(),tx,5.0f);
         float posy=calcularposiciony(jugadora.getposiciony(),jugadora.getvy(),ty);
        float t = i * dt;
        if(posx>=x){
            jugadora.setvx(rebotarpared(jugadora.getvx(),1));
            jugadora.setposicionx(x);
            posx=x;
            tx=0.0f;
        }
        if (posx < 0.0f) {
            jugadora.setvx(rebotarpared(jugadora.getvx(),1));
            jugadora.setposicionx(0.0f);
            posx=0.0f;
            tx=0.0f;
        }
        if(posy>=y){
            jugadora.setvy(rebotarpared(jugadora.getvy(),1));
            jugadora.setposiciony(y);
            ty=0.0f;

        }
        if(posy<0.0f){
            jugadora.setvy(rebotarpared(jugadora.getvy(),1));
            jugadora.setposiciony(0.0f);
            posy = 0.0f;

        }
        archivo << "la posicion en x es:" << posx;
        archivo << "  la posicion en y es:" << posy;
        archivo << "\n";
        tx += dt;
        ty += dt;
    }
    archivo.close();
    return 0;
    }

