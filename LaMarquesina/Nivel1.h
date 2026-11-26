#ifndef NIVEL1_H
#define NIVEL1_H

#include <vector>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include "Nivel.h"
#include "Yuuko.h"
#include "Obstaculos.h"
#include "Goyeneche.h"

struct Plataforma {
    float x, y, ancho;
    QGraphicsRectItem* dibujo;
    Viga*viga;

};

struct Bala {
    Proyectil*fisica;
    QGraphicsEllipseItem* dibujo;
    bool yuukoSalto;
    bool viva;

};

struct LaminaTecho {
    Lamina* fisica;
    QGraphicsRectItem*dibujo;
    bool viva;
};

class Nivel1 : public Nivel {
private:
    ConfigDificultad dificultad;
    Yuuko*yuuko;
    QGraphicsRectItem* dibujoYuuko;
    Goyeneche* goyeneche;
    QGraphicsRectItem* dibujoGoyeneche;

    std::vector<Plataforma> plataformas;
    std::vector<Bala> balas;
    std::vector<LaminaTecho> laminas;
    std::vector<QGraphicsRectItem*> tensores;

    int tensoresQuitados;
    float tiempo;
    float tiempoLimite;
    float esperaLamina;
    float tiempoMensaje;
    QGraphicsRectItem* barraTension;
    QGraphicsTextItem* textoInfo;

    void agregarPlataforma(float x, float y, float ancho, bool oscila);
    void moverYuuko(float dt);
    void actualizarGoyeneche(float dt);
    void actualizarBalas(float dt);
    void actualizarLaminas(float dt);
    void revisarTensores();
    void actualizarTexto();

public:
    Nivel1(QGraphicsScene* escena, QSet<int>* teclas, Sonidos* sonidos, ConfigDificultad dificultad);
    ~Nivel1();
    void construir() override;
    void actualizar(float dt) override;
    void teclaPresionada (int tecla) override;


};


#endif // NIVEL1_H
