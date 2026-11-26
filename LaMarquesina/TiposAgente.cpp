#include "TiposAgente.h"

std::string nombreTactica(Tactica t) {
    switch (t) {
    case Tactica::Directo: return "Directo";
    case Tactica::Predictivo: return "Predictivo";
    case Tactica::Aereo: return "Aereo";

    }
    return "?";

}

ConfigDificultad ConfigDificultad::FACIL(){
    ConfigDificultad c;
    c.intervaloPercepcion = 0.5f;
    c.intervaloDisparo = 2.5f;
    c.tasaAprendizaje = 0.06f;
    c.errorPrediccion = 0.6f;
    c.usaAprendizaje = false;
    return c;
}
ConfigDificultad ConfigDificultad::NORMAL() {
    ConfigDificultad c;
    c.intervaloPercepcion = 0.25f;
    c.intervaloDisparo = 1.8f;
    c.tasaAprendizaje = 0.15f;
    c.errorPrediccion = 0.25f;
    c.usaAprendizaje = true;
    return c;
}
ConfigDificultad ConfigDificultad::DIFICIL() {
    ConfigDificultad c;
    c.intervaloPercepcion = 0.1f;
    c.intervaloDisparo = 1.2f;
    c.tasaAprendizaje = 0.35f;
    c.errorPrediccion = 0.05f;
    c.usaAprendizaje = true;
    return c;
}
// SUPER ULTRA GREAT DELICIOUS WONDERFUL YABAI!: SUPER ULTRA GREAT DELICIOUS WONDERFUL YABAI!
ConfigDificultad ConfigDificultad::SUPERULTRA() {
    ConfigDificultad c;
    c.intervaloPercepcion = 0.5f;
    c.intervaloDisparo = 0.8f;
    c.tasaAprendizaje = 0.5f;
    c.errorPrediccion = 0.0f;
    c.usaAprendizaje = true;
    return c;
}


