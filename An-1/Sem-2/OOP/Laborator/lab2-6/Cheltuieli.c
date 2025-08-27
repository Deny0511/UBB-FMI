#include "Cheltuieli.h"
#include <string.h>

Cheltuiala creeazaCheltuiala(int zi,float suma,const char* tip) {
    Cheltuiala c;
    c.zi = zi;
    c.suma = suma;
    strcpy(c.tip,tip);
    return c;
}
