#include "Nivel1.h"
#include "Juego.h"
#include <QBrush>
#include <QFont>
#include <cstdlib>

const float GRAVEDAD = 1400;
const float VEL_SALTO = 650;
const float ANCHO_YUUKO = 32;
const float ALTO_YUUKO = 48;

Nivel1::Nivel1(QGraphicsScene* escena, QSet<int>* teclas, Sonidos* sonidos, ConfigDificultad dificultad)
: Nivel(escena, teclas, sonidos), dificultad(dificultad){

    yuuko = nullptr;
    dibujoYuuko = nullptr;
    goyeneche = nullptr;
    dibujoGoyeneche = nullptr;
    tensoresQuitados = 0;
    tiempo = 0;
    tiempoLimite = 120;
    esperaLamina = 3;
    tiempoMensaje = 0;
    barraTension = nullptr;
    textoInfo = nullptr;

}

Nivel1::~Nivel1() {
    delete yuuko;
    delete goyeneche;
    for (int i = 0; i < plataformas.size(); i++) delete plataformas[i].viga;
    for (int i = 0; i < balas.size(); i++) delete balas[i].fisica;
    for (int i = 0; i < laminas.size(); i++) delete laminas[i].fisica;
}
void Nivel1::agregarPlataforma (float x, float y, float ancho, bool oscila) {
    Plataforma p;
    p.x = x;
    p.y  = y;
    p.ancho = ancho;
    p.viga = nullptr;

    QColor color (110, 110, 120);
    if (oscila){
        color = QColor( 180, 120, 60);
        p.viga = new Viga(x, y, ancho, 80, 1.8f, 0.12f);
    }
    p.dibujo = escena->addRect( 0,0, ancho, 16, QPen(Qt::NoPen), QBrush(color));
    p.dibujo->setPos(x,y);
    plataformas.push_back(p);


}

void Nivel1::construir(){
    escena->setBackgroundBrush(QColor(122, 204, 250 ));
    agregarPlataforma( 0, 680, ANCHO, false);
    agregarPlataforma(100, 560, 200, false);
    agregarPlataforma(450, 470, 180, true);
    agregarPlataforma(800, 560, 200, false);
    agregarPlataforma(1000, 430, 200, false);
    agregarPlataforma(650, 350, 160, true);
    agregarPlataforma(250, 330, 200, false);
    agregarPlataforma(60, 210, 180, false);
    agregarPlataforma(900, 250, 200, false);
    float tx[5] = {190, 1090, 340, 140, 990};
    float ty[5] = {536, 406, 306, 186, 226};
    for (int i = 0; i < 5; i++) {
        QGraphicsRectItem* t = escena->addRect(0, 0, 24, 24, QPen(Qt::black), QBrush(QColor(40, 200, 90)));
        t->setPos(tx[i], ty[i]);
        tensores.push_back(t);

    }

    yuuko = new Yuuko(40,680 - ALTO_YUUKO);
    dibujoYuuko = escena->addRect(0,0, ANCHO_YUUKO, ALTO_YUUKO, QPen(Qt::NoPen), QBrush(QColor(225,150,190)));
    dibujoYuuko->setZValue(10);
    goyeneche = new Goyeneche(616,40,450, dificultad);
    dibujoGoyeneche = escena->addRect(0,0,48,48, QPen(Qt::NoPen), QBrush(QColor(90, 60, 40)));
    dibujoGoyeneche->setPos(616,40);

    escena->addRect(20,20,300,18, QPen(Qt::black));
    barraTension = escena->addRect(20,20,0,18, QPen(Qt::NoPen), QBrush(Qt::red));
    textoInfo = escena->addText("", QFont("Consolas", 12));
    textoInfo->setPos(20,42);
    textoInfo->setZValue(20);
}

void Nivel1::teclaPresionada(int tecla) {
    bool teclaSalto = tecla ==Qt::Key_W || tecla == Qt::Key_Space;
    if (teclaSalto && yuuko->getEnSuelo()){
        yuuko->setVelocidad(yuuko->getVx(), -VEL_SALTO);
        yuuko->setEnSuelo(false);
        sonar(Sonidos::Salto);
    }
    if (tecla == Qt::Key_Q) {
        if (yuuko->llamarMalaSuerte()){
            tiempoMensaje = 2;
            sonar(Sonidos::Golpe);

        }
    }
}

void Nivel1::actualizar(float dt) {
    tiempo += dt;
    if (tiempoMensaje > 0) tiempoMensaje -= dt;
    moverYuuko(dt);
    actualizarGoyeneche(dt);
    actualizarLaminas(dt);
    revisarTensores();
    actualizarTexto();
    if (tensoresQuitados == 5) {
        fin = true;
        victoria = true;

    }
    if (yuuko->getEstado() == false || tiempo >= tiempoLimite) {
        fin = true;
        victoria = false;

    }
}

void Nivel1::moverYuuko(float dt) {
    float vel = yuuko->getVelocidad() * yuuko->multiplicadorVelocidad();
    float vx= 0;
    if (teclas->contains(Qt::Key_A)) vx = -vel;
    if (teclas->contains(Qt::Key_D)) vx = vel;

    float vy = yuuko->getVy() + GRAVEDAD *dt;
    yuuko->setVelocidad(vx, vy);

    for (int i = 0; i < plataformas.size(); i++) {
        if (plataformas[i].viga != nullptr) {
            plataformas[i].viga->actualizar(dt);
            plataformas[i].x = plataformas[i].viga->getX();
            plataformas[i].dibujo->setPos(plataformas[i].x, plataformas[i].y);

        }
    }

float piesAntes = yuuko->getY() + ALTO_YUUKO;
bool estabaEnSuelo = yuuko->getEnSuelo();
yuuko->actualizar(dt);
yuuko->setEnSuelo(false);
for (int i = 0; i < plataformas.size(); i++) {
         Plataforma p = plataformas[i];
         float pies = yuuko->getY() + ALTO_YUUKO;

         bool encima = yuuko->getX() + ANCHO_YUUKO > p.x && yuuko->getX() < p.x + p.ancho;
         bool cruzoBorde = piesAntes <= p.y + 1 && pies >= p.y;
         bool cayendo = yuuko->getVy() >= 0;

         if (encima && cruzoBorde && cayendo) {
             float nuevaX = yuuko->getX();
             if (p.viga !=nullptr) {
                 nuevaX += p.viga->getVx() * dt;

                 if(estabaEnSuelo == false) p.viga->empujar(120);
             }
             yuuko->setPosicion(nuevaX, p.y - ALTO_YUUKO);
             yuuko->setVelocidad(yuuko->getVx(), 0);
             yuuko->setEnSuelo(true);

         }


     }

     if (yuuko->getX() < 0 ) yuuko->setPosicion(0, yuuko->getY());
if (yuuko->getX() > ANCHO - ANCHO_YUUKO) yuuko->setPosicion(ANCHO - ANCHO_YUUKO, yuuko->getY());

dibujoYuuko->setPos(yuuko->getX(), yuuko->getY());
if (yuuko->aturdida()) dibujoYuuko->setBrush(QColor(150, 150, 150));
 else if (yuuko->enPanico()) dibujoYuuko->setBrush(QColor(255, 40, 40));
 else dibujoYuuko->setBrush(QColor(255, 150, 190));
}




void Nivel1::actualizarGoyeneche(float dt) {}
void Nivel1::actualizarBalas(float dt) {}
void Nivel1::actualizarLaminas(float dt) {}
void Nivel1::revisarTensores() {}
void Nivel1::actualizarTexto() {}



















