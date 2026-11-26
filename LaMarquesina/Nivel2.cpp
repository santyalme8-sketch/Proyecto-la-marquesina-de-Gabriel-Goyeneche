#include "Nivel2.h"
#include "Juego.h"
#include <QBrush>
#include <QFont>
#include <cstdlib>
#include <QPixmap>
#include <stdexcept>

const float ALTURA_BOMBA = 500;
const float LADO_YUUKO =32;

    Nivel2::Nivel2(QGraphicsScene* escena, QSet<int>* teclas, Sonidos* sonidos) : Nivel(escena, teclas, sonidos) {
    yuuko = nullptr;
    dibujoYuuko = nullptr;
    temblor = nullptr;
    recogidos = 0;
    tiempoRestante = 60;
    esperaBomba = 1.5f;
    esperaTemblor = 4;
    textoInfo = nullptr;
}
    Nivel2::~Nivel2() {
        delete yuuko;
        delete temblor;
        for (int i = 0; i<bombas.size(); i++) delete bombas[i].caida;
    }

    void Nivel2::construir() {
        escena->setBackgroundBrush(QColor(200, 185, 120));
        for (int i = 0; i< 5; i++) {
            QGraphicsEllipseItem* b = escena->addEllipse( 0,0,28,28, QPen(Qt::black), QBrush(QColor(227, 76, 54)));
            float x = 80 + i * 154 + rand() % (ANCHO - 160);
            float y = 120 + rand() % (ALTO - 200);
            b->setPos(x,y);
            bidones.push_back(b);
        }



        yuuko = new Yuuko(ANCHO / 2, ALTO / 2);
        yuuko->setEnSuelo(true);   // desde arriba nunca salta
        dibujoYuuko = escena->addRect(0, 0, LADO_YUUKO, LADO_YUUKO, QPen(Qt::NoPen), QBrush(QColor(255, 150, 190)));
        dibujoYuuko->setZValue(10);
        temblor = new Viga( 0,0, ANCHO, 0, 14.0f, 2.5f);

        textoInfo = escena->addText( "", QFont("Consolas", 14, QFont::Bold));
        textoInfo->setZValue(20);

    }
    void Nivel2::teclaPresionada(int tecla) {
        if (tecla ==Qt::Key_Q) {
            if (yuuko->llamarMalaSuerte()) sonar(Sonidos::Golpe);
        }
    }

    void Nivel2::actualizar(float dt) {
        tiempoRestante -= dt;
    moverYuuko(dt);
        actualizarBombas(dt);
    for (int i = 0; i < bidones.size(); i++) {
            if (bidones[i]->isVisible() && bidones[i]->collidesWithItem(dibujoYuuko)) {
                bidones[i]->hide();
                recogidos++;
                sonar(Sonidos::Logro);
            }
    }

    textoInfo->setPos(escena->sceneRect().left() + 20,15);
    textoInfo->setPlainText("Tiempo: " + QString::number((int)tiempoRestante) + " s"
                            + "    Vida: " + QString::number(yuuko->getPuntosDeSSalud())
                            + "    Bidones: " + QString::number(recogidos) + "/5");
    if (recogidos == 5) {
        fin = true;
        victoria = true;
        victoria = true;
    }
    if (yuuko->getEstado() == false || tiempoRestante <= 0) {
        fin = true;
        victoria = false;

    }

    }

    void Nivel2::moverYuuko(float dt) {
        float vel = yuuko->getVelocidad() * yuuko->multiplicadorVelocidad();
        float vx = 0;
        float vy = 0;
            if (teclas->contains(Qt::Key_A)) vx = -vel;
            if (teclas->contains(Qt::Key_D)) vx = vel;
            if (teclas->contains(Qt::Key_W)) vy = -vel;
            if (teclas->contains(Qt::Key_S)) vy = vel;


            vx += temblor->getVx() * 0.5f;
            yuuko->setVelocidad(vx,vy);
            yuuko->actualizar(dt);

            float x = yuuko->getX();
            float y = yuuko->getY();
            if (x <0 ) x = 0;
            if (x > ANCHO - LADO_YUUKO) x= ANCHO - LADO_YUUKO;
            if (y <50 ) y = 50;
            if (y > ALTO - LADO_YUUKO) y= ALTO - LADO_YUUKO;
            yuuko->setPosicion(x,y);
            dibujoYuuko->setPos(x,y);
            if (yuuko->aturdida()) dibujoYuuko->setBrush(QColor(150, 150, 150));
            else if (yuuko->enPanico()) dibujoYuuko->setBrush(QColor(255, 40, 40));
            else dibujoYuuko->setBrush(QColor(255, 150, 190));
    }
    void Nivel2::actualizarBombas(float dt) {
        esperaBomba -= dt;
        if (esperaBomba <= 0) {
            esperaBomba = 0.9f;
            Bomba b;
            if (rand() % 2 == 0) {
                b.objetivoX = yuuko->getX() + 16 + rand() % 120 - 60;
                b.objetivoY = yuuko->getY() + 16 + rand() % 120 - 60;

            } else  {
                b.objetivoX = rand() % ANCHO;
                b.objetivoY = 60 + rand() % (ALTO - 60);
            }
            b.caida = new Proyectil (0,0,0,0,980, -1, 20);
            b.sombra = escena ->addEllipse(0,0,0,0, QPen(Qt::NoPen), QBrush(QColor(0,0,0,90)));
            b.sombra->setPos(b.objetivoX, b.objetivoY);
            b.viva = true;
            bombas.push_back(b);
        }

        for (int i = 0; i < bombas.size(); i++) {
            if (bombas[i].viva == false) continue;
            bombas[i].caida->actualizar(dt);

            float progreso = bombas[i].caida->getY() / ALTURA_BOMBA;
            float r = 8 + 32 * progreso;
            bombas[i].sombra->setRect(-r, -r, 2 * r, 2 * r);

            if (progreso >= 1) {
                float dx = yuuko->getX() + 16 - bombas[i].objetivoX;
                float dy = yuuko->getY() + 16 - bombas[i].objetivoY;
                if (dx * dx + dy * dy < 45 * 45) {
                    yuuko->recibirDano(bombas[i].caida->getDano());
                    sonar(Sonidos::Golpe);
                }
                sonar(Sonidos::Explosion);
                delete bombas[i].caida;
                delete bombas[i].sombra;
                bombas[i].caida = nullptr;
                bombas[i].viva = false;
            }
        }
    }

    void Nivel2::actualizarTemblor(float dt) {
        esperaTemblor -= dt;
        if (esperaTemblor <= 0) {
            esperaTemblor = 5;
            temblor->empujar(400);
        }
        temblor->actualizar(dt);
        escena->setSceneRect(temblor->desplazamiento(), 0, ANCHO, ALTO);

    }