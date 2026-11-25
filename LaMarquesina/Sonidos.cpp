#include "Sonidos.h"
#include <QUrl>

Sonidos::Sonidos() {
 //el "qrc:/" es el archivo que esta dentro del ejecutable en recursos.qrc
    //por ahora esta vacio porque si xd
    salto.setSource(QUrl());
    golpe.setSource(QUrl());
    explosion.setSource(QUrl());
    logro.setSource(QUrl());
    musica.setAudioOutput(&salida);
}

//efectos cortos

void Sonidos::reproducir(Efecto e) {
    switch (e) {
    case Salto: salto.play(); break;
    case Golpe: golpe.play(); break;
    case Explosion: explosion.play(); break;
    case Logro: logro.play(); break;
        break;
    }
}

//musica larga

void Sonidos::musicaDeFondo(const QString& ruta) {
    if (ruta.isEmpty()) return; //todavia no hay musica XD
    musica.setSource(QUrl(ruta));
    musica.setLoops(QMediaPlayer::Infinite);
    musica.play();
}

void Sonidos::detenerMusica() {
    musica.stop();
}