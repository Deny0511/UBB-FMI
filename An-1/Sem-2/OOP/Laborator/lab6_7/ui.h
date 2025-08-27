
#ifndef UI_H
#define UI_H
#include "service.h"


class UI {
private:
    Service& service;
    void adaugaFilm()const;
    void stergeFilm()const;
    void afiseazaFilme()const;
    void modificaFilm()const;
    void cautaFilme()const;
    void filtrareFilme()const;
    void sortari();
    void adaugaFilmInCos();
    void umple_random_cos();
    void afiseazaFilmCos(const std::vector<Film>& filme);
    void exportaCos();
    void undo();
public:
    explicit UI(Service& service) noexcept : service{ service } {}
    void run();
};
#endif //UI_H

