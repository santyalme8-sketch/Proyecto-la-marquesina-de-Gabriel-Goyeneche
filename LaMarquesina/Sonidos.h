#ifndef SONIDOS_H
#define SONIDOS_H

#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>

//agrupa todos los sonidos del juego en un solo lugar

class Sonidos {
private:
    QSoundEffect salto, golpe, explosion, logro; //efectos cortos de extesion .wav
    QMediaPlayer musica; //musica larga
    QAudioOutput salida; //por donde suena la musica

public:
    enum Efecto {Salto, Golpe, Explosion, Logro};

    Sonidos();
    void reproducir(Efecto e);
    void musicaDeFondo(const QString& ruta);
    void detenerMusica();
};

#endif // SONIDOS_H


//Se me ocurrio que pude haber heco un timelapse de todo el desarrollo pero ya pa que XD

