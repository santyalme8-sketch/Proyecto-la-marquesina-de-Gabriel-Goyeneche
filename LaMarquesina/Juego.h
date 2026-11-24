#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>

const int ANCHO = 1280;
    const int ALTO = 720;

class Juego : public QGraphicsView {
    Q_OBJECT
private:
    QGraphicsScene* escena;
public:
    Juego(QWidget* parent = nullptr);
};

#endif // JUEGO_H