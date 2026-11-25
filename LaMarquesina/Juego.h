#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>
#include <QSet>
#include <QKeyEvent>
#include "Nivel.h"
#include "Sonidos.h"
#include "TiposAgente.h"

const int ANCHO = 1280;
    const int ALTO = 720;


//la ventana del juego es una QGraphicsView que muestra una QGraphicsScene.
//maneja el menu, el teclado y el reloj
class Juego : public QGraphicsView {
    Q_OBJECT //se usa para las señales y los slots
private:
    QGraphicsScene* escena;
    QTimer* reloj;
    QElapsedTimer cronometro;
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
    void paso(); //un frame del juego

public:
    Juego(QWidget* parent = nullptr);
    ~Juego();
};

#endif // JUEGO_H