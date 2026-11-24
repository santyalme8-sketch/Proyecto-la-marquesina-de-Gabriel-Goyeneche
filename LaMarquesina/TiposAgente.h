#ifndef TIPOSAGENTE_H
#define TIPOSAGENTE_H


// Tipos compartidos por todas las piezas del agente de Goyeneche.
// Coordenadas como en Qt: x crece a la derecha, y crece hacia ABAJO.

#include <string>
//lo que yuuko hace en ese momento
enum class EstadoYuuko {Reposo, Corriendo, Saltando, Panico};

// tacticas de disparo de goyeneche (3)
enum class Tactica { Directo, Predictivo, Aereo };

//convierte las tacticas a texto
std::string nombreTactica(Tactica t);

//sensmor de yuuko

struct LecturaYuuko {
    float x = 0, y = 0; //posicion
    float vx = 0, vy = 0; //velocidad
    EstadoYuuko estado = EstadoYuuko::Reposo;

};

//resumen que la percepcion le entrega al razonamiento
struct Observacion {
    LecturaYuuko actual;  //ultima lectura
    float velPromX = 0, veloPromY = 0; //velocidad promedio reciente
    float rapidez = 0; //cuantas lecturas recientes estaba saltando
    bool valida = false; //false si todavia no hay lecturas

};

//decision que sale del razonamiento
struct Decision {
    Tactica tactica = Tactica::Directo;
    float objetivoX = 0, objetivoY = 0; // dodne apuntar
    float tiempoVuelo = 1.0f; //cuanto tarda el proyectil en llegar


};

//datos con los que el juego crea el proyectil en la pantalla
struct DatosDisparo {
    int id = 0;
    Tactica tactica = Tactica::Directo;
    float x0 = 0, y0 = 0; //sale desde goyeneche
    float vx = 0, vy = 0; //velocidad inicial calculada
    float gravedad = 0; //gravedad
};

//parametros qe cambian con la dificultadad
//la dificultad lo que hace es que cambia como piensa el agente
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
