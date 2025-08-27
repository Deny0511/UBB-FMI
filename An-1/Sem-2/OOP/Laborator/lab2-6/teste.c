#include<stdio.h>
#include<string.h>
#include<assert.h>
#include <stdlib.h>
#include "Cheltuieli.h"
#include "service.h"
#include "repo.h"


void test_add() {
  ListaCheltuieli lista = {
    .lungime = 0,
    .capacitate = 10,
    .cheltuiala = (Cheltuiala*) malloc(10 * sizeof(Cheltuiala))
};
  int rezultat = add(&lista, 15, 200, "mancare");
  assert(rezultat == 0);
  assert(lista.lungime == 1);
  assert(lista.cheltuiala[0].zi == 15);
  assert(lista.cheltuiala[0].suma == 200);
  assert(strcmp(lista.cheltuiala[0].tip, "mancare") == 0);

  for (int i = 0; i < MAX_CHELTUIELI; i++) {
    add(&lista, 1, 100, "altele");
  }
  rezultat = add(&lista, 1, 100, "altele");
  assert(rezultat == -1);
  free(lista.cheltuiala);
}

void test_modificare() {
  ListaCheltuieli lista = {
    .lungime = 0,
    .capacitate = 10,
    .cheltuiala = (Cheltuiala*) malloc(10 * sizeof(Cheltuiala))
};
  add(&lista, 10, 150, "transport");

  int rezultat = modificare(&lista, 0, 12, 170, "telefon&internet");
  assert(rezultat == 0);
  assert(lista.cheltuiala[0].zi == 12);
  assert(lista.cheltuiala[0].suma == 170);
  assert(strcmp(lista.cheltuiala[0].tip, "telefon&internet") == 0);

  rezultat = modificare(&lista, 10, 15, 180, "imbracaminte");
  assert(rezultat == -2);
  free(lista.cheltuiala);
}


void test_stergere() {
  ListaCheltuieli lista = {
    .lungime = 0,
    .capacitate = 10,
    .cheltuiala = (Cheltuiala*) malloc(10 * sizeof(Cheltuiala))
};
  add(&lista, 25, 200, "mancare");

  int rezultat = stergere(&lista, 0);
  assert(rezultat == 0);
  assert(lista.lungime == 0);

  add(&lista, 25, 200, "mancare");
  add(&lista, 26, 200, "mancare");
  rezultat = stergere(&lista, 0);
  assert(rezultat == 0);
  assert(lista.lungime == 1);

  rezultat = stergere(&lista, 0);
  assert(rezultat == 0);
  assert(lista.lungime == 0);



  rezultat = stergere(&lista, 0);
  assert(rezultat == -2);

  rezultat = stergere(&lista, 10);
  assert(rezultat == -2);
  free(lista.cheltuiala);
}

void test_vizualizare() {

  ListaCheltuieli lista = {
    .lungime = 0,
    .capacitate = 10,
    .cheltuiala = (Cheltuiala*) malloc(10 * sizeof(Cheltuiala))
};

  add(&lista, 15, 100, "mancare");
  add(&lista, 20, 200, "transport");
  add(&lista, 15, 150, "telefon&internet");

  // Test pentru zi
  ListaCheltuieli *lista_filtrata = vizualizare(&lista, "zi", "15");
  assert(lista_filtrata != NULL);
  assert(lista_filtrata->lungime == 2);
  free(lista_filtrata);

  // Test pentru suma
  lista_filtrata = vizualizare(&lista, "suma", "100");
  assert(lista_filtrata != NULL);
  assert(lista_filtrata->lungime == 1);
  free(lista_filtrata);

  // Test pentru tip
  lista_filtrata = vizualizare(&lista, "tip", "telefon&internet");
  assert(lista_filtrata != NULL);
  assert(lista_filtrata->lungime == 1);
  free(lista_filtrata);

  // Test pentru suma inexistenta
  lista_filtrata = vizualizare(&lista, "suma", "999.9");
  assert(lista_filtrata == NULL);

  // Test pentru tip inexistent
  lista_filtrata = vizualizare(&lista, "tip", "altele");
  assert(lista_filtrata == NULL);

  free(lista_filtrata);
  free(lista.cheltuiala);

}

void test_ordonare(){
  ListaCheltuieli lista = creeaza_lista(5);

  add(&lista, 15, 100, "mancare");
  add(&lista, 20, 50, "transport");
  add(&lista, 15, 150, "telefon&internet");
  char* criteriu = "suma";
  ordonare(&lista,criteriu,compara_suma);

  assert(lista.cheltuiala[0].suma == 50);
  assert(lista.cheltuiala[1].suma == 100);
  assert(lista.cheltuiala[2].suma == 150);

  criteriu = "tip";
  ordonare(&lista,criteriu,compara_tip);

  assert(strcmp(lista.cheltuiala[0].tip,"mancare")==0);
  assert(strcmp(lista.cheltuiala[1].tip,"telefon&internet" )==0);
  assert(strcmp(lista.cheltuiala[2].tip,"transport")==0);

  distruge_lista(&lista);

}


void test_ordonare_desc(){
  ListaCheltuieli lista = {
    .lungime = 0,
    .capacitate = 10,
    .cheltuiala = (Cheltuiala*) malloc(10 * sizeof(Cheltuiala))
};

  add(&lista, 15, 100, "mancare");
  add(&lista, 20, 50, "transport");
  add(&lista, 15, 150, "telefon&internet");
  char* criteriu = "suma";
  ordonare_desc(&lista,criteriu,compara_suma_desc);

  assert(lista.cheltuiala[0].suma == 150);
  assert(lista.cheltuiala[1].suma == 100);
  assert(lista.cheltuiala[2].suma == 50);

  criteriu = "tip";
  ordonare_desc(&lista,criteriu,compara_tip_desc);

  assert(strcmp(lista.cheltuiala[0].tip,"transport")==0);
  assert(strcmp(lista.cheltuiala[1].tip,"telefon&internet" )==0);
  assert(strcmp(lista.cheltuiala[2].tip,"mancare")==0);
  distruge_lista(&lista);
}

void test_add_service() {
  ListaCheltuieli lista = {
    .lungime = 0,
    .capacitate = 10,
    .cheltuiala = (Cheltuiala*) malloc(10 * sizeof(Cheltuiala))
};

  int rezultat = add_cheltuiala(&lista, 15, 200, "mancare");
  assert(rezultat == 0);
  assert(lista.lungime == 1);
  assert(lista.cheltuiala[0].zi == 15);
  assert(lista.cheltuiala[0].suma == 200);
  assert(strcmp(lista.cheltuiala[0].tip, "mancare") == 0);

  rezultat = add_cheltuiala(&lista, 34, 100, "altele");
  assert(rezultat == 3);

  rezultat = add_cheltuiala(&lista, 4, -4, "altele");
  assert(rezultat == 4);

  rezultat = add_cheltuiala(&lista, 2, 100, "apa");
  assert(rezultat == 5);

  for (int i = 0; i < MAX_CHELTUIELI; i++) {
    add(&lista, 1, 100, "altele");
  }
  rezultat = add_cheltuiala(&lista, 1, 100, "altele");
  assert(rezultat == -1);
  free(lista.cheltuiala);
}

void test_modificare_service() {
  ListaCheltuieli lista = creeaza_lista(10);
  add(&lista, 10, 150, "transport");

  int rezultat = modifica_cheltuiala(&lista, 0, 12, 170, "telefon&internet");
  assert(rezultat == 0);
  assert(lista.cheltuiala[0].zi == 12);
  assert(lista.cheltuiala[0].suma == 170);
  assert(strcmp(lista.cheltuiala[0].tip, "telefon&internet") == 0);

  rezultat = modifica_cheltuiala(&lista, 0, 36, 170, "telefon&internet");
  assert(rezultat == 3);

  rezultat = modifica_cheltuiala(&lista, 0, 12, -170, "telefon&internet");
  assert(rezultat == 4);

  rezultat = modifica_cheltuiala(&lista, 0, 12, 170, "telefon");
  assert(rezultat == 5);

  rezultat = modifica_cheltuiala(&lista, 10, 15, 180, "imbracaminte");
  assert(rezultat == -2);
  free(lista.cheltuiala);
}

void test_stergere_service() {
  ListaCheltuieli lista = {
    .lungime = 0,
    .capacitate = 10,
    .cheltuiala = (Cheltuiala*) malloc(10 * sizeof(Cheltuiala))
};
  add(&lista, 25, 200, "mancare");

  int rezultat = sterge_cheltuiala(&lista, 0);
  assert(rezultat == 0);
  assert(lista.lungime == 0);

  rezultat = sterge_cheltuiala(&lista, 10);
  assert(rezultat == -2);
  free(lista.cheltuiala);
}
void test_get_all() {
  ListaCheltuieli lista = creeaza_lista(3);
  add(&lista, 1, 100, "Mancare");
  add(&lista, 2, 200, "Transport");

  ListaCheltuieli *copia = get_all(&lista);
  assert(copia != NULL);
  assert(copia->lungime == lista.lungime);
  assert(copia->capacitate == lista.capacitate);
  assert(copia->cheltuiala != NULL);
  assert(copia->cheltuiala[0].zi == 1);
  assert(copia->cheltuiala[1].suma == 200);

  distruge_lista(copia);
  free(copia);
  distruge_lista(&lista);
}


void test_get_all_service() {
  ListaCheltuieli lista = creeaza_lista(3);
  add(&lista, 1, 100, "Mancare");
  add(&lista, 2, 200, "Transport");

  ListaCheltuieli *copia = get_all_(&lista);
  assert(copia != NULL);
  assert(copia->lungime == lista.lungime);
  assert(copia->capacitate == lista.capacitate);
  assert(copia->cheltuiala != NULL);
  assert(copia->cheltuiala[0].zi == 1);
  assert(copia->cheltuiala[1].suma == 200);

  distruge_lista(copia);
  free(copia);
  distruge_lista(&lista);

}

void test_creeaza_lista() {
  ListaCheltuieli lista = creeaza_lista(10);
  assert(lista.lungime == 0);
  free(lista.cheltuiala);

}

void test_distruge_lista() {
  ListaCheltuieli lista = creeaza_lista(10);
  lista.lungime = 5;
  distruge_lista(&lista);
  assert(lista.lungime == 0);
}

void test_redimensioneaza_lista() {
  ListaCheltuieli lista = creeaza_lista(10);
  lista.lungime = 5;
  redimensioneaza_lista(&lista);

  assert(lista.capacitate == 20);
  assert(lista.lungime == 5);
  free(lista.cheltuiala);

}

void test_micsoreaza_lista() {
  ListaCheltuieli lista1 = creeaza_lista(2);
  micsoreaza_lista(&lista1);
  assert(lista1.capacitate == 2);
  distruge_lista(&lista1);

  ListaCheltuieli lista2 = creeaza_lista(8);
  add(&lista2, 1, 100, "Mancare");
  add(&lista2, 2, 200, "Transport");

  micsoreaza_lista(&lista2);
  assert(lista2.capacitate == 4);
  assert(lista2.lungime == 2);

  distruge_lista(&lista2);

  ListaCheltuieli lista3 = creeaza_lista(8);
  add(&lista3, 1, 100, "Mancare");
  free(lista3.cheltuiala);

}

void test_creeaza_cheltuiala() {

  Cheltuiala c = creeaza1Cheltuiala(12,123,"mancare");
  assert(c.zi == 12);
  assert(c.suma == 123);
  assert(strcmp(c.tip, "mancare") == 0);

}


void ruleaza_toate_testele() {
  test_add();
  test_modificare();
  test_stergere();
  test_vizualizare();
  test_ordonare();
  test_ordonare_desc();
  test_add_service();
  test_modificare_service();
  test_stergere_service();
  test_get_all();
  test_get_all_service();
  test_creeaza_lista();
  test_distruge_lista();
  test_redimensioneaza_lista();
  test_micsoreaza_lista();
  test_creeaza_cheltuiala();
}
