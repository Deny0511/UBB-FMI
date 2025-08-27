#include<string.h>
#include "validator.h"
#define ERROR_INVALID_ZI    3
#define ERROR_INVALID_SUMA  4
#define ERROR_INVALID_TIP   5


int valideaza_zi(int zi) {
    /**
     * Functie de validare a zilei cheltuielii.
     * Verifica daca ziua este valida.
     *
     * @param zi Ziua cheltuielii.
     *
     * @return 0 daca ziua este valida,
     *         3 daca nu este valida.
     */
    if (zi < 1 || zi > 31) {
        return ERROR_INVALID_ZI ;
    }
    return 0;
}

int valideaza_suma(float suma) {
    /**
     * Functie de validare a sumei cheltuielii.
     * Verifica daca suma este valida.
     *
     * @param suma Suma cheltuielii.
     *
     * @return 0 daca suma este valida,
     *         4 daca nu este valida.
     */
    if (suma <= 0) {
        return ERROR_INVALID_SUMA;
    }
    return 0;
}

int valideaza_tip(const char *tip) {
    /**
     * Functie de validare a tipului cheltuielii.
     * Verifica daca tipul este valid.
     *
     * @param tip Tipul cheltuielii.
     *
     * @return 0 daca tipul este valid,
     *         5 daca nu este valid.
     */
    const char *tipuri[] = {"mancare", "transport", "telefon&internet", "imbracaminte", "altele"};
    for (int i = 0; i < 5; i++) {
        if (strcmp(tipuri[i], tip) == 0)
            return 0;
    }
    return ERROR_INVALID_TIP;
}

