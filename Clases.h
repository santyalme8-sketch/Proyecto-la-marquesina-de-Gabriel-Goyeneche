#ifndef CLASES_H
#define CLASES_H

class Cuerpo {
protected:
    float peso;
    float velocidad;
    float aceleracion;
    public:
    Cuerpo();
};
class Persona : public Cuerpo {
protected:
    int puntosDeSalud;
    bool estado;

    public:
             Persona();
    void recibirDanio(int cantidad);
};

class Yuuko : public Persona {
private:
    bool modoPanico;

    public:
    Yuuko(int salud = 100);
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
