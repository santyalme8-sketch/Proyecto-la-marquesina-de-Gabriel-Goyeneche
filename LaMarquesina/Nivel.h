#ifndef NIVEL_H
#define NIVEL_H

#include <QGraphicsScene>
#include <QSet>
#include "Sonidos.h"

//clase base abstracta de los niveles con herencia propia, no hereda nada de qt
//el juego solo conoce un nivel y le dice: constru9ir, actualizar y tecla

class Nivel {
protected:
    QGraphicsScene* escena; //donde se dibuja
    const QSet <int>& teclas; //teclas que estan siendo presionadas
    Sonidos* sonidos;
    bool fin = false;
    bool victoria = false;
public:
    Nivel(QGraphicsScene* escena, const QSet<int>& teclas, Sonidos* sonidos)
        : escena(escena), teclas(teclas), sonidos(sonidos) {}

    virtual ~Nivel() = default;
    virtual void construir() = 0; //crea todo lo del nivel
    virtual void actualizar(float dt) = 0; //un frame del juego
    virtual void teclaPresionada(int tecla) {} //acciones de un solo toque, como saltar

    bool terminado() const {return fin; }
    bool gano() const {return victoria; }

protected:
    void sonar(Sonidos::Efecto e) { if (sonidos) sonidos->reproducir(e);}



};













#endif // NIVEL_H
