#include "Nivel1.h"
#include "Juego.h"
#include <QBrush>
#include <QFont>
#include <cstdlib>
#include <QPixmap>
#include <stdexcept>

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
    dibujoYuuko = escena->addRect(0,0, ANCHO_YUUKO, ALTO_YUUKO, QPen(Qt::NoPen), QBrush(QColor(225,150, 190)));
    dibujoYuuko->setZValue(10);
    goyeneche = new Goyeneche(616,40,450, dificultad);
    dibujoGoyeneche = escena->addRect(0,0,48,48, QPen(Qt::NoPen), QBrush(QColor(90, 60, 40)));
    dibujoGoyeneche->setPos(616,40);

    escena->addRect(20,20,300,18, QPen(Qt::black));
    barraTension = escena->addRect(20,20,0,18, QPen(Qt::NoPen), QBrush(Qt::red));
    textoInfo = escena->addText("", QFont("Consolas", 12));
    textoInfo->setPos(20,42);
    textoInfo->setZValue(20);

    QPixmap imgYuuko(":/sprites/yuuko.png");
    if (imgYuuko.isNull())
        throw std::runtime_error("No se encontro el sprite");
    dibujoYuuko->setBrush(QBrush(imgYuuko.scaled(ANCHO_YUUKO, ALTO_YUUKO, Qt::IgnoreAspectRatio,  Qt::SmoothTransformation)));

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
    actualizarBalas(dt);
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
if (yuuko->aturdida()) dibujoYuuko->setPen(QPen(QColor(150, 150, 150), 3));
else if (yuuko->enPanico()) dibujoYuuko->setPen(QPen(QColor(255, 40, 40), 3));
else dibujoYuuko->setPen(QPen(Qt::NoPen));
}




void Nivel1::actualizarGoyeneche(float dt){

    goyeneche->actualizar(dt);
    dibujoGoyeneche->setPos(goyeneche->getX(), goyeneche->getY());
    LecturaYuuko lectura;
    lectura.x = yuuko->getX() + ANCHO_YUUKO / 2;
    lectura.y = yuuko->getY() + ALTO_YUUKO / 2;
    lectura.vx = yuuko->getVx();
    lectura.vy = yuuko->getVy();
    lectura.estado = yuuko->estadoActual();

    DatosDisparo d;
    if (goyeneche->ejecutar(dt, lectura, d)) {
        Bala b;
        b.fisica = new Proyectil(d.x0, d.y0, d.vx, d.vy, d.gravedad, d.id, 15);
        b.yuukoSalto = false;
        b.viva = true;

        QColor color =Qt::black; //directo

        if (d.tactica == Tactica::Predictivo) color = QColor(162, 0, 245 ); //morado

        if (d.tactica == Tactica::Aereo) color = QColor(245, 110, 0 ); //naranja

        b.dibujo = escena->addEllipse(-8, -8, 16, 16, QPen(Qt::NoPen), QBrush(color));

        b.dibujo->setPos(d.x0, d.y0);
        balas.push_back(b);
    }
    }

void Nivel1::actualizarBalas(float dt){
    for (int i = 0; i < balas.size(); i++) {
        if (balas[i].viva == false) continue;
        balas[i].fisica->actualizar(dt);
        balas[i].dibujo->setPos(balas[i].fisica->getX(), balas[i].fisica->getY());
        if (yuuko->getEnSuelo() == false) balas [i].yuukoSalto = true;
        bool pego =balas[i].dibujo->collidesWithItem(dibujoYuuko);
        bool salio = balas[i].fisica->getY() > ALTO + 20 || balas[i].fisica->getX() < -50 || balas[i].fisica->getX() > ANCHO + 50;

        if (pego || salio) {
            goyeneche->registrarResultado(balas[i].fisica->getId(), pego, balas[i].yuukoSalto);
            if (pego) {
                yuuko->recibirDano(balas[i].fisica->getDano());
                sonar(Sonidos::Golpe);

            }
            delete balas[i].fisica;
            delete balas[i].dibujo;
            balas[i].fisica = nullptr;
            balas[i].viva = false;
        }
        }

    }



    void Nivel1::actualizarLaminas(float dt) {
        esperaLamina -= dt;
        if (esperaLamina <= 0) {
            esperaLamina = 2.5f;
            LaminaTecho l;
            float x = rand() % (int)(ANCHO - 60);
            l.fisica = new Lamina(x, -20, GRAVEDAD, 2.0f, 10);
            l.dibujo = escena->addRect(0,0,60,10,  QPen(Qt::NoPen), QBrush(QColor( 170, 170, 180)));
            l.viva = true;
            laminas.push_back(l);

        }
        for (int i = 0; i < laminas.size(); i++) {
if (laminas[i].viva == false) continue;
laminas[i].fisica->actualizar(dt);
laminas[i].dibujo->setPos(laminas[i].fisica->getX(), laminas[i].fisica->getY());
bool pego =laminas[i].dibujo->collidesWithItem(dibujoYuuko);
if (pego) {
    yuuko->recibirDano(laminas[i].fisica->getDano());
    sonar(Sonidos::Golpe);

}
if (pego || laminas[i].fisica->getY() > ALTO) {
    delete laminas[i].fisica;
    delete laminas[i].dibujo;
    laminas[i].fisica = nullptr;
    laminas[i].viva = false;


}
}
    }

    void Nivel1::revisarTensores() {
        for (int i = 0; i < tensores.size(); i++ ) {
            if (tensores[i]->isVisible() && tensores[i]->collidesWithItem(dibujoYuuko) ) {
                tensores[i]->hide();
                tensoresQuitados++;
                sonar(Sonidos::Logro);

            }
        }
    }


    void Nivel1::actualizarTexto() {
        float  tension = tiempo / tiempoLimite;
        barraTension->setRect(20,20,300 * tension, 18);
        QString texto = "Tension del techo: " + QString::number((int)(tension *100)) + "%" + " Vida "
                        + QString::number(yuuko->getPuntosDeSSalud()) + " Tensores: "
                        + QString::number(tensoresQuitados) + "/5\n";

        texto += "IA Goyeneche -> Directo " + QString::number(goyeneche->getAprendizaje().peso(Tactica::Directo), 'f', 2)
                 + "  Predictivo " + QString::number(goyeneche->getAprendizaje().peso(Tactica::Predictivo), 'f', 2)
                 + "  Aereo " + QString::number(goyeneche->getAprendizaje().peso(Tactica::Aereo), 'f', 2) + "\n";

        if (tiempoMensaje > 0) texto += "MALA SUERTE!! TE CAYO ALGO EN LA CABEZA! (╯‵□′)╯︵┻━┻ ";
        textoInfo->setPlainText(texto);


    }

























