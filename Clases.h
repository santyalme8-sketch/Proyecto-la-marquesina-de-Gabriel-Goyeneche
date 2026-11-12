#ifndef CLASES_H
#define CLASES_H

class Cuerpo {
protected:
    float vx;
    float vy;
    float ax;
    float ay;
    public:
    Cuerpo();
        Cuerpo(float vx, float vy, float ax = 0.0f, float ay = 0.0f);
    void setvelocidad(float velocidad);
        float getvx()  {
            return vx; }
        float getvy()  {
            return vy; }
        float getax()  {
            return ax; }
        float getay()  {
            return ay; }

        void setvx(float vx) {
            this->vx = vx; }
        void setvy(float vy) {
            this->vy = vy; }
        void setax(float ax) {
            this->ax = ax; }
        void setay(float ay) {
            this->ay = ay; }
};
class Persona : public Cuerpo {
protected:
    int puntosDeSalud;
    bool estado;
    float posicionx;
    float posiciony;
    public:
    Persona();
    Persona(int salud, float vx, float vy, float ax = 0.0f, float ay = 0.0f);
    int recibirDaño(int cantidad);
    int getPuntosDeSalud();
    bool getEstado();
    float getposicionx(){
        return posicionx;}
    float getposiciony(){
        return posiciony;
    }
    void setposicionx(float posx);
    void setposiciony(float posy);
};

class Yuuko : public Persona {
private:
    bool modoPanico=false;

    public:
    Yuuko();
    void activarPanico();
};

class Goyoneche : public Persona {
private:
    bool agenteia;
    public:
        Goyoneche();
    void ejecutar();
};

class Obstaculo : public Cuerpo {
protected:
    int vida;
    bool destructible;

    public:
    Obstaculo(int v, bool dest, float vx, float vy, float ax = 0.0f, float ay = 0.0f);
};
class Proyectil : public Obstaculo {
private:
    float tamaño;
    float daño;
    public:
     Proyectil(float tam, float d, float vx, float vy = 0.0f);
    void actualizar();

};

class Viga : public Obstaculo {
private:
    float longitud;

    public:
    Viga(float len);
};
#endif // CLASES_H
