#ifndef NIVEL_H
#define NIVEL_H

#include <QGraphicsScene>
#include <QSet>
#include "Sonidos.h"

class Nivel {
protected:
    QGraphicsScene* escena;
    QSet<int>* teclas;
    Sonidos* sonidos;
    bool fin = false;
    bool victoria = false;
public:
    Nivel(QGraphicsScene* escena, QSet<int>*teclas , Sonidos* sonidos)
        : escena(escena), teclas(teclas), sonidos(sonidos) {}

    virtual ~Nivel() {};
    virtual void construir() = 0;
    virtual void actualizar(float dt) = 0;
    virtual void teclaPresionada(int tecla) {}

    bool terminado() const {return fin; }
    bool gano() const {return victoria; }

protected:
    void sonar(Sonidos::Efecto e) { if (sonidos) sonidos->reproducir(e);}



};













#endif // NIVEL_H
