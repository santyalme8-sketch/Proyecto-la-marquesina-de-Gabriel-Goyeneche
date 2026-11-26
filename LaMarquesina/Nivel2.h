#ifndef NIVEL2_H
#define NIVEL2_H
#include <vector>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include "Nivel.h"
#include "Yuuko.h"
#include "Obstaculos.h"
#include "Goyeneche.h"

struct Bomba {
    Proyectil* caida;
QGraphicsEllipseItem* sombra;
float objetivoX, objetivoY;
bool viva;
};
class Nivel2 : public Nivel {
private:
    Yuuko* yuuko;
QGraphicsRectItem* dibujoYuuko;
    std::vector<QGraphicsEllipseItem*> bidones;
std::vector<Bomba> bombas;
    Viga* temblor;

int recogidos;
    float tiempoRestante;
float esperaBomba;
    float esperaTemblor;
QGraphicsTextItem* textoInfo;

    void moverYuuko(float dt);
void actualizarBombas(float dt);
    void actualizarTemblor(float dt);

public:
    Nivel2(QGraphicsScene* escena, QSet<int>* teclas, Sonidos* sonidos);
    ~Nivel2();
    void construir() override;
    void actualizar(float dt) override;
    void teclaPresionada(int tecla) override;
};

#endif // NIVEL2_H
