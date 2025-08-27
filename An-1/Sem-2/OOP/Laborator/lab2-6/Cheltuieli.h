
#ifndef CHELTUIELI_H
#define CHELTUIELI_H
#define MAX_CHELTUIELI 100

typedef struct {
    int zi;
    float suma;
    char tip[50];
} Cheltuiala;

typedef struct {
    Cheltuiala *cheltuiala;
    int lungime;
    int capacitate;
} ListaCheltuieli;

Cheltuiala creeazaCheltuiala(int zi, float suma, const char *tip);
void DistrugeCheltuiala(Cheltuiala *c);

#endif //CHELTUIELI_H
