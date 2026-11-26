#include <QApplication>
#include "Juego.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    srand(time(nullptr));
    Juego juego;
    juego.setWindowTitle("Yuuko vs. la marquesina de Goyeneche");
    juego.show();
    return app.exec();
}
