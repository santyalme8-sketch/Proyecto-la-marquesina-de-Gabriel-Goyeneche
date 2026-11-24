#include "Juego.h"
#include <QGraphicsTextItem>
#include <QFont>

Juego::Juego(QWidget* parent) : QGraphicsView(parent) {
    // 'this' es el padre, cuando se cierra la ventana, qt borra la escena
    escena = new QGraphicsScene(0,0, ANCHO, ALTO, this);
    setScene(escena);
    setFixedSize(ANCHO + 2, ALTO + 2);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    escena -> setBackgroundBrush(QColor(30, 30, 50));

    QGraphicsTextItem* texto = escena ->addText("Hola Yuuko!", QFont("TimesNewRoman", 40, QFont::Bold));
    texto -> setDefaultTextColor(Qt::white);
    texto ->setPos(450, 300);
    //un rectangulo se crea en 0,0 y despues se mueve con setPos
    QGraphicsRectItem* cuadro = escena -> addRect(0, 0, 32, 48, QPen(Qt::NoPen), QBrush(QColor(255, 150, 190)));
    cuadro -> setPos(620, 450);


}