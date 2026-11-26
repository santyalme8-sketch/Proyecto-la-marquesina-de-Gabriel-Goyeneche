#ifndef SONIDOS_H
#define SONIDOS_H

#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>

class Sonidos {
private:
    QSoundEffect salto, golpe, explosion, logro;
    QMediaPlayer musica;
    QAudioOutput salida;

public:
    enum Efecto {Salto, Golpe, Explosion, Logro};

    Sonidos();
    void reproducir(Efecto e);
    void musicaDeFondo(const QString& ruta);
    void detenerMusica();
};

#endif // SONIDOS_H
