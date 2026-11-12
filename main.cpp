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
     Yuuko particula2;
     Yuuko Particula3;
     Yuuko Particula4;
     particula2.setvx(10.4f);
     particula2.setvy(4.4f);
     Particula3.setvy(3.4f);
     Particula3.setvx(30.4f);
     Particula4.setvx(2);
     Particula4.setvy(1);
    for (int i = 0; i <= total_pasos; ++i) {
         float posx=calcularposicionx(jugadora.getposicionx(),jugadora.getvx(),tx,5.0f);
         float posy=calcularposiciony(jugadora.getposiciony(),jugadora.getvy(),ty);
         float posx2=calcularposicionx(particula2.getposicionx(),particula2.getvx(),tx,5.0f);
         float posy2=calcularposiciony(particula2.getposiciony(),particula2.getvy(),ty);
         float posx3=calcularposicionx(Particula3.getposicionx(),Particula3.getvx(),tx,5.0f);
         float posy3=calcularposiciony(Particula3.getposiciony(),Particula3.getvy(),ty);
         float posx4=calcularposicionx(Particula4.getposicionx(),Particula4.getvx(),tx,5.0f);
         float posy4=calcularposiciony(Particula4.getposiciony(),Particula4.getvy(),ty);
        if(posx>=x){
            jugadora.setvx(rebotarpared(jugadora.getvx(),1));
            jugadora.setposicionx(x);
            tx=0.0f;
        }
        if (posx < 0.0f) {
            jugadora.setvx(rebotarpared(jugadora.getvx(),1));
            jugadora.setposicionx(0.0f);
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
            ty=0.0f;
        }

        if(posx2>=x){
            particula2.setvx(rebotarpared(particula2.getvx(),1));
            particula2.setposicionx(x);
            tx=0.0f;
        }
        if (posx2 < 0.0f) {
            particula2.setvx(rebotarpared(particula2.getvx(),1));
            particula2.setposicionx(0.0f);
            tx=0.0f;
        }
        if(posy2>=y){
            particula2.setvy(rebotarpared(particula2.getvy(),1));
            particula2.setposiciony(y);
            ty=0.0f;
        }
        if(posy2<0.0f){
            particula2.setvy(rebotarpared(particula2.getvy(),1));
            particula2.setposiciony(0.0f);
            ty=0.0f;
        }

        if(posx3>=x){
            Particula3.setvx(rebotarpared(Particula3.getvx(),1));
            Particula3.setposicionx(x);
            tx=0.0f;
        }
        if (posx3 < 0.0f) {
            Particula3.setvx(rebotarpared(Particula3.getvx(),1));
            Particula3.setposicionx(0.0f);
            tx=0.0f;
        }
        if(posy3>=y){
            Particula3.setvy(rebotarpared(Particula3.getvy(),1));
            Particula3.setposiciony(y);
            ty=0.0f;
        }
        if(posy3<0.0f){
            Particula3.setvy(rebotarpared(Particula3.getvy(),1));
            Particula3.setposiciony(0.0f);
            ty=0.0f;
        }

        if(posx4>=x){
            Particula4.setvx(rebotarpared(Particula4.getvx(),1));
            Particula4.setposicionx(x);
            tx=0.0f;
        }
        if (posx4 < 0.0f) {
            Particula4.setvx(rebotarpared(Particula4.getvx(),1));
            Particula4.setposicionx(0.0f);
            tx=0.0f;
        }
        if(posy4>=y){
            Particula4.setvy(rebotarpared(Particula4.getvy(),1));
            Particula4.setposiciony(y);
            ty=0.0f;
        }
        if(posy4<0.0f){
            Particula4.setvy(rebotarpared(Particula4.getvy(),1));
            Particula4.setposiciony(0.0f);
            ty=0.0f;
        }
        archivo << "particula1\nla posicion en x es:" << posx;
        archivo << "  la posicion en y es:" << posy;
        archivo << "\nParticula2\n";
        archivo << "la posicion en x es:" << posx2;
        archivo << "  la posicion en y es:" << posy2;
        archivo << "\nParticula3\n";
        archivo << "la posicion en x es:" << posx3;
        archivo << "  la posicion en y es:" << posy3;
        archivo << "\nParticula4\n";
        archivo << "la posicion en x es:" << posx4;
        archivo << "  la posicion en y es:" << posy4;
        archivo << "\n";
        tx += dt;
        ty += dt;
    }
    archivo.close();
    return 0;
    }

