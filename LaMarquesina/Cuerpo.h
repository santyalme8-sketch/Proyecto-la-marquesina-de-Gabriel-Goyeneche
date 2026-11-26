#ifndef CUERPO_H
#define CUERPO_H
class Cuerpo {
protected:
    float x, y;
    float vx, vy;

public:
    Cuerpo(float x = 0, float y = 0, float vx = 0, float vy = 0);
    virtual ~Cuerpo() {};

    virtual void actualizar(float dt) = 0;
    float getX() const {return x;}
    float getY() const {return y;}
    float getVx() const {return vx;}
    float getVy() const {return vy;}
    void setPosicion(float nx, float ny) { x = nx; y = ny; }
    void setVelocidad(float nvx, float nvy) {vx = nvx, vy =nvy;}


};

#endif // CUERPO_H
