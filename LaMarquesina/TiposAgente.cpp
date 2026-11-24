#include "TiposAgente.h"

std::string nombreTactica(Tactica t) {
    switch (t) {
    case Tactica::Directo: return "Directo";
    case Tactica::Predictivo: return "Predictivo";
    case Tactica::Aereo: return "Aereo";

    }
    return "?";

}

//dificultad FACIL: mira poco, dispara lentamente, predice mal y no aprende
ConfigDificultad ConfigDificultad::FACIL(){
    return {0.5f, 2.5, 0.0f, 0.6f, false};

}
// dificultad NORMAL: aprende despacio
ConfigDificultad ConfigDificultad::NORMAL() {
    return {0.25f, 1.8f, 0.15f, 0.25f, true};
}
// dificultad DIFICIL: mira seguido, predice casi perfecto y aprende rápido
ConfigDificultad ConfigDificultad::DIFICIL() {
    return {0.1f, 1.2f, 0.35f, 0.05f, true};
}
// SUPER ULTRA GREAT DELICIOUS WONDERFUL YABAI!: SUPER ULTRA GREAT DELICIOUS WONDERFUL YABAI!
ConfigDificultad ConfigDificultad::SUPERULTRA() {
    return {0.05f, 0.8f, 0.5f, 0.0f, true};;
}


