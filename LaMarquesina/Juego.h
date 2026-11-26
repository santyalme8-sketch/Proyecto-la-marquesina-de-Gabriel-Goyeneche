#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QSet>
#include <QKeyEvent>
#include "Nivel.h"
#include "Sonidos.h"
#include "TiposAgente.h"

const int ANCHO = 1280;
    const int ALTO = 720;

class Juego : public QGraphicsView {
    Q_OBJECT
private:
    QGraphicsScene* escena;
    QTimer* reloj;
    QSet<int> teclas;
    Nivel* nivel;
    Sonidos* sonidos;
    ConfigDificultad dificultdad;
    QString nombreDificultdad;
    int pantalla;
    void mostrarMenu();
    void iniciarNivel(int numero);
    void mostrarFin(bool gano);

protected:
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;

private slots:
    void paso();

public:
    Juego(QWidget* parent = nullptr);
    ~Juego();
};

#endif // JUEGO_H