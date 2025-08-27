#pragma once

#include "domain.h"
#include "observator.h"
#include <vector>
#include <random>


class CosFilm : public Observabil {
  private:
    std::vector<Film> cosFilme;
  public:
    CosFilm() = default;
    void adaugaCosFilme(const Film& filme);
    void golesteCosFilme() ;
    void umpleRandomCosFilme(size_t dimensiune,const std::vector<Film>& listaFilme);
    const std::vector<Film>& getCosFilme() const;
    void exportCSV(const std::string& numeFisier) const;
    ~CosFilm() = default;
};

