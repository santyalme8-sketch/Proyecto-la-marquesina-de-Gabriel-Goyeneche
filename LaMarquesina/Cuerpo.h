#ifndef CUERPO_H
#define CUERPO_H
//esta es la base de todo lo que se mueve en el juego
class Cuerpo {
protected:
    float x, y; //esta es la posicion de los pixeles (antes estaba en persona)
    float vx, vy; //esta es la velocidad de los pixeles por s

public:
    Cuerpo(float x = 0, float y = 0, float vx = 0, float vy = 0);
    virtual ~Cuerpo() = default; //el virtual es para poder hacer un delete con un Cuerpo*

    //aqui cada hija decide como se mueve, virtual pura = cuerpo no se puede crear solo.

    virtual void actualizar(float dt) = 0;
    float getX() const {return x;}
    float getY() const {return y;}
    float getVx() const {return vx;}
    float getVy() const {return vy;}
    void setPosicion(float nx, float ny) { x = nx; y = ny; }
    void setVelocidad(float nvx, float nvy) {vx = nvx, vy =nvy;}


};

#endif // CUERPO_H
