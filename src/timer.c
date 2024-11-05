#include <time.h>
#include "timer.h"

int calcularTempoDecorrido(int tempoInicio) {
    return time(NULL) - tempoInicio;
}
