#ifndef CLASES_H
#define CLASES_H

class Cuerpo {
protected:
    float velocidad;
    float aceleracion;
    public:
    Cuerpo();
        Cuerpo(float velocidad, float aceleracion);
};
class Persona : public Cuerpo {
protected:
    int puntosDeSalud;
    bool estado;
    float posicionx;
    float posiciony;
    public:
    Persona();
    Persona(int salud,float velocidad,float aceleracion);
    int recibirDaño(int cantidad);
    int getPuntosDeSalud();
    bool getEstado();
    void setposicionx(float posx);
    void setposiciony(float posy);
};

class Yuuko : public Persona {
private:
    bool modoPanico=false;

    public:
    Yuuko();
    void activarPanico();
    float getVelocidad();
    float getposicionx(){return this->posicionx;}
    float getposiciony(){return this->posiciony;}
};

class Goyoneche : public Persona {
private:
    bool agenteia;
    public:
        Goyoneche();
    float getVelocidad();
    void ejecutar();
};

class Obstaculo : public Cuerpo {
protected:
    int vida;
    bool destructible;

    public:
    Obstaculo(int v, bool dest, float vel, float acel);
};
class Proyectil : public Obstaculo {
private:
    float tamaño;
    float daño;
    public:
     Proyectil(float tam, float d, float vel);
    void actualizar();
    float getvelocidad();
};

class Viga : public Obstaculo {
private:
    float longitud;

    public:
    Viga(float len);
};
#endif // CLASES_H
