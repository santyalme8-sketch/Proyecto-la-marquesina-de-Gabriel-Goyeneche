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

    public:
    Persona();
    Persona(int salud,float velocidad,float aceleracion);
    int recibirDaño(int cantidad);
    int getPuntosDeSalud();
    bool getEstado();
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
    Obstaculo();
};
class Proyectil : public Obstaculo {
private:
    float tamaño;
    float daño;
    public:
             Proyectil();
    void actualizar();
};

class Viga : public Obstaculo {
private:
    float longitud;

    public:
    Viga();
};
#endif // CLASES_H
