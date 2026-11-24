#include <QApplication>
#include "Juego.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);   // arranca Qt

    Juego juego;                    // nuestra ventana
    juego.setWindowTitle("Yuuko vs. la marquesina de Goyeneche");
    juego.show();

    return app.exec();              // ciclo de eventos
}