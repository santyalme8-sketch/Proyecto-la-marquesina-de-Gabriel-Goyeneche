#ifndef TIPOSAGENTE_H
#define TIPOSAGENTE_H
#include <string>

enum class EstadoYuuko {Reposo, Corriendo, Saltando, Panico};


enum class Tactica { Directo, Predictivo, Aereo };


std::string nombreTactica(Tactica t);

struct LecturaYuuko {
    float x = 0, y = 0;
    float vx = 0, vy = 0;
    EstadoYuuko estado = EstadoYuuko::Reposo;

};

struct Observacion {
    LecturaYuuko actual;
    float velPromX = 0, velPromY = 0;
    float rapidez = 0;
    bool valida = false;
    int saltosRecientes = 0;
};

struct Decision {
    Tactica tactica = Tactica::Directo;
    float objetivoX = 0, objetivoY = 0;
    float tiempoVuelo = 1.0f;


};

struct DatosDisparo {
    int id = 0;
    Tactica tactica = Tactica::Directo;
    float x0 = 0, y0 = 0;
    float vx = 0, vy = 0;
    float gravedad = 0;
};
struct ConfigDificultad {
    float intervaloPercepcion;
    float intervaloDisparo;
    float tasaAprendizaje;
    float errorPrediccion;
    bool usaAprendizaje;

    static ConfigDificultad FACIL();
    static ConfigDificultad NORMAL();
    static ConfigDificultad DIFICIL();
    static ConfigDificultad SUPERULTRA();

};

#endif // TIPOSAGENTE_H
