#include "Juego.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QMessageBox>
#include "Nivel1.h"
//#include "Nivel2.h"

Juego::Juego(QWidget* parent) :
    QGraphicsView(parent), nivel(nullptr), dificultdad(ConfigDificultad::NORMAL()), nombreDificultdad("NORMAL"), pantalla(0) {
    escena = new QGraphicsScene(0,0, ANCHO, ALTO, this);
    setScene(escena);
    setFixedSize(ANCHO + 2, ALTO + 2);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);


    sonidos = new Sonidos();
    reloj = new QTimer(this);
    connect(reloj, &QTimer::timeout, this, &Juego::paso);
    reloj->start(16);
    mostrarMenu();
}

Juego::~Juego() {
    delete nivel;
    delete sonidos;

}

void Juego::mostrarMenu() {
    delete nivel;
    nivel = nullptr;
    escena->clear();
    escena->setSceneRect(0, 0, ANCHO, ALTO);
    escena->setBackgroundBrush(QColor(30, 30, 50));
    sonidos->detenerMusica();
    pantalla = 0;

    QGraphicsTextItem* titulo = escena ->addText("Yuuko vs. La marquesina de Goyenehe (*ˊᗜˋ*)", QFont("TimesNewRoman", 32, QFont::Bold));
    titulo -> setDefaultTextColor(Qt::white);
    titulo ->setPos(250, 150);

    QGraphicsTextItem* opciones = escena ->addText(
    "1 - Nivel 1: La gran Marquesina sobre Monserrate\n"
    "2  -  Nivel 2: Ataque a las Nubes desde la Plaza\n"
    "F / N / D / S  -  Dificultad: " + nombreDificultdad + "\n\n"
    "Controles: A/D o flechas para moverse, W o Espacio para saltar,\n"
    "Q para llamar a la mala suerte, Esc para volver al menu",QFont("TimesNewRoman", 18));
    opciones->setDefaultTextColor(Qt::white);
    opciones->setPos(200, 260);

}

void Juego::iniciarNivel(int numero) {
    delete nivel;
    nivel = nullptr;
    escena->clear();
    teclas.clear();
    if (numero == 1) nivel = new Nivel1(escena, &teclas, sonidos, dificultdad);
    if (!nivel) { mostrarMenu(); return;}

    try {
        nivel->construir();
    }   catch (const std::exception& e) {
        QMessageBox::critical(this, "ERROR AL CARGAR EL NIVEL", e.what());
        mostrarMenu();
        return;
    }
    pantalla = numero;
    sonidos->musicaDeFondo("");

}

void Juego::mostrarFin(bool gano) {
    pantalla = -1;
                sonidos->detenerMusica();
    QString texto = gano ? "Felicidades, has ganado el juego! ＼(≧▽≦)／"
                         : "Perdiste... No pudiste contra Goyeneche (╥﹏╥)";
    QGraphicsTextItem* t = escena->addText(texto + "\n\nPresiona la tecla Enter para volver al menu! (づ￣ ³￣)づ", QFont("TimesNewRoman", 28, QFont::Bold));
    t->setDefaultTextColor(gano ? Qt::green : Qt::red);
    t->setPos(escena->sceneRect().left() + 180, 280);
    t->setZValue(100);
}

void Juego::paso() {
    float dt = 0.016;
    if (dt > 0.05f) dt = 0.05f;

    if(pantalla <= 0 || !nivel) return;
    nivel->actualizar(dt);
    if (nivel->terminado()) mostrarFin(nivel->gano());

}

void Juego::keyPressEvent(QKeyEvent* e) {
    if (e->isAutoRepeat()) return;
    int k = e->key();
    teclas.insert(k);
    if (pantalla == 0) {
        if (k == Qt::Key_1) iniciarNivel(1);
        if (k ==Qt::Key_2) iniciarNivel(2);
        if (k ==Qt::Key_F) { dificultdad = ConfigDificultad::FACIL();
            nombreDificultdad = "FACIL"; mostrarMenu(); }
        if (k ==Qt::Key_N) { dificultdad = ConfigDificultad::NORMAL();
            nombreDificultdad = "NORMAL"; mostrarMenu(); }
        if (k ==Qt::Key_D) { dificultdad = ConfigDificultad::DIFICIL();
            nombreDificultdad = "DIFICIL"; mostrarMenu(); }
        if (k ==Qt::Key_S) { dificultdad = ConfigDificultad::SUPERULTRA();
            nombreDificultdad = "SUPER ULTRA GREAT DELICIOUS WONDERFUL YABAI! (つ≧▽≦)つ"; mostrarMenu(); }
    } else if (pantalla == -1) {
        if (k == Qt::Key_Return || k == Qt::Key_Enter) mostrarMenu();
    } else if (nivel) {
        if (k == Qt::Key_Escape) { mostrarMenu(); return; }
        nivel->teclaPresionada(k);
    }
}

void Juego::keyReleaseEvent(QKeyEvent* e) {
    if (e->isAutoRepeat()) return;
    teclas.remove(e->key());
}