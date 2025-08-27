#include <stdio.h>
#include <string.h>
#include "ui.h"
#include <stdlib.h>
#include "cheltuieli.h"
#include "service.h"
#include "validator.h"
#include "repo.h"


int citeste_int() {
    int numar;
    while (1) {
        if (scanf("%d", &numar) == 1) {
            return numar;
        }
        while(getchar() != '\n'){}
        printf("Eroare! Introduceti un numar valid: ");
    }
}

float citeste_float() {
    float numar;
    while (1) {
        if (scanf("%f", &numar) == 1) {
            return numar;
        }
        while(getchar() != '\n'){}
        printf("Eroare! Introduceti o suma valida: ");
    }
}

void get_all_and_print(ListaCheltuieli *lista) {
    if (!lista) {
        printf("Eroare: Lista este NULL!\n");
        return;
    }

    if (lista->lungime == 0) {
        printf("Lista de cheltuieli este goala.\n");
        return;
    }

    for (int i = 0; i < lista->lungime; i++) {
        printf("Zi: %d, Suma: %.2f, Tip: %s\n",
               lista->cheltuiala[i].zi,
               lista->cheltuiala[i].suma,
               lista->cheltuiala[i].tip);
    }
}

void afiseaza_meniu() {
    printf("\n--- Meniu ---\n");
    printf("1. Adaugare cheltuiala\n");
    printf("2. Modificare cheltuiala\n");
    printf("3. Stergere cheltuiala\n");
    printf("4. Vizualizare cheltuieli\n");
    printf("5. Ordonare cheltuieli crescator\n");
    printf("6. Ordonare cheltuieli descrescator\n");
    printf("7. Get all\n");
    printf("0. Iesire\n");
    printf("Optiune: ");
}

void ruleaza() {
    ListaCheltuieli lista = creeaza_lista(10);
    int optiune;
    do {
        afiseaza_meniu();
        scanf("%d", &optiune);

        switch (optiune) {
            case 1: {
                int zi;
                float suma;
                char tip[50];

                do {
                    printf("Introduceti ziua: ");
                    zi = citeste_int();

                    if (valideaza_zi(zi) != 0)
                        printf("Zi invalida! Ziua trebuie sa fie intre 1 si 31.\n");
                } while (valideaza_zi(zi) != 0);
                do {
                    printf("Introduceti suma: ");
                    suma = citeste_float();

                    if (valideaza_suma(suma) != 0)
                        printf("Suma invalida! Suma trebuie sa fie un numar natural.\n");
                    } while (valideaza_suma(suma) != 0);
                while (getchar() != '\n'){}

                do {
                    printf("Introduceti tipul: ");
                    fgets(tip, sizeof(tip), stdin);
                    tip[strcspn(tip, "\n")] = 0;

                    if (valideaza_tip(tip) != 0) {
                        printf("Tip invalid! Tipuri permise: mancare, transport, telefon&internet, imbracaminte, altele.\n");
                    }
                } while (valideaza_tip(tip) != 0);


                int rezultat = add(&lista, zi, suma, tip);
                printf("Here");
                if (rezultat == 0) {
                    printf("Cheltuiala adaugata cu succes!\n");
                }else {
                    printf("Lista este plina! Nu se mai pot adauga cheltuieli.\n");
                }

                break;
            }
            case 2: {
                int zi;
                float suma;
                char tip[50];

                printf("Introduceti indexul cheltuielii de modificat: ");
                int index = citeste_int();
                do {
                    printf("Introduceti ziua: ");
                    zi = citeste_int();

                    if (valideaza_zi(zi) != 0)
                        printf("Zi invalida! Ziua trebuie sa fie intre 1 si 31.\n");
                } while (valideaza_zi(zi) != 0);
                do {
                    printf("Introduceti suma: ");
                    suma = citeste_float();

                    if (valideaza_suma(suma) != 0)
                        printf("Suma invalida! Suma trebuie sa fie un numar natural.\n");
                } while (valideaza_suma(suma) != 0);
                while (getchar() != '\n'){}

                do {
                    printf("Introduceti tipul: ");
                    fgets(tip, sizeof(tip), stdin);
                    tip[strcspn(tip, "\n")] = 0;

                    if (valideaza_tip(tip) != 0) {
                        printf("Tip invalid! Tipuri permise: mancare, transport, telefon&internet, imbracaminte, altele.\n");
                    }
                } while (valideaza_tip(tip) != 0);



                int rezultat = modificare(&lista, index, zi, suma, tip);
                if (rezultat == 0) {
                    printf("Cheltuiala modificata cu succes!\n");
                }else {
                    printf("Index invalid!\n");
                }
                break;
            }
            case 3: {
                printf("Introduceti indexul cheltuielii de sters: ");
                int index = citeste_int();
                int rezultat = stergere(&lista, index);
                if (rezultat == 0) {
                    printf("Cheltuiala stearsa cu succes!\n");
                } else {
                    printf("Index invalid!\n");
                }
                break;
            }
            case 4: {
                char criteriu[20], valoare[20];
                printf("Introduceti criteriul (zi/suma/tip): ");
                scanf("%s", criteriu);
                printf("Introduceti valoarea: ");
                scanf("%s", valoare);
                ListaCheltuieli *lista_filtrata = vizualizare(&lista, criteriu, valoare);

                if (lista_filtrata->lungime == 0) {
                    printf("Nu s-au gasit cheltuieli pentru criteriul %s cu valoarea %s.\n", criteriu, valoare);
                } else {
                    printf("Cheltuieli gasite:\n");
                    for (int i = 0; i < lista_filtrata->lungime; i++) {
                        printf("%d: %.2f %s\n",
                            lista_filtrata->cheltuiala[i].zi,
                            lista_filtrata->cheltuiala[i].suma,
                            lista_filtrata->cheltuiala[i].tip);
                    }
                }

                distruge_lista(lista_filtrata);
                free(lista_filtrata);
                break;
            }
            case 5:
                char criteriu[20];
                printf("Introduceti criteriul (suma/tip): ");
                scanf("%s", criteriu);
            if (strcmp(criteriu, "suma") == 0) {
                ordonare(&lista, criteriu, compara_suma);
            } else if (strcmp(criteriu, "tip") == 0) {
                ordonare(&lista, criteriu, compara_tip);
            } else {
                printf("Criteriu invalid!\n");
            }
                printf("Cheltuielile au fost ordonate!\n");
                break;
            case 6:
                char criteriul[20];
                printf("Introduceti criteriul (suma/tip): ");
                scanf("%s", criteriul);
            if (strcmp(criteriu, "suma") == 0) {
                ordonare(&lista, criteriu, compara_suma_desc);
            } else if (strcmp(criteriu, "tip") == 0) {
                ordonare(&lista, criteriu, compara_tip_desc);
            } else {
                printf("Criteriu invalid!\n");
            }
                break;
            case 7:
                ListaCheltuieli *lista_copie = get_all(&lista);
            if (!lista_copie) {
                printf("Eroare la copierea listei!\n");
            } else {
                get_all_and_print(lista_copie);

                if (lista_copie->cheltuiala) {
                    free(lista_copie->cheltuiala);
                }
                free(lista_copie);
            }
                break;
            case 0:
                break;
            default:
                printf("Optiune invalida! Incercati din nou.\n");
        }
    } while (optiune != 0);
    free(lista.cheltuiala);

}
