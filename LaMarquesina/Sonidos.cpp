#include "Sonidos.h"
#include <QUrl>

Sonidos::Sonidos() {
 //el "qrc:/" es el archivo que esta dentro del ejecutable en recursos.qrc
    salto.setSource(QUrl());
    golpe.setSource(QUrl());
    musica.setAudioOutput(&salida);
}
