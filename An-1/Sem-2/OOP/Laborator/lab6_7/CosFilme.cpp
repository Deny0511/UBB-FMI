#include "CosFilme.h"
#include<fstream>
#include <vector>
#include <string>
#include <algorithm>




void CosFilm::adaugaCosFilme(const Film& filme) {
  this->cosFilme.push_back(filme);
  notifica();

}

void CosFilm::golesteCosFilme() {
  this->cosFilme.clear();
  notifica();

}

void CosFilm::umpleRandomCosFilme(size_t dimensiune, const std::vector<Film>& listaFilme) {
  std::vector<Film> listaFilmeAuxiliara = listaFilme;
  std::shuffle(listaFilmeAuxiliara.begin(), listaFilmeAuxiliara.end(), std::default_random_engine(std::random_device{}()));

  this->cosFilme.clear();

  while ((this->cosFilme.size() < dimensiune) && !listaFilmeAuxiliara.empty()) {
    this->cosFilme.push_back(listaFilmeAuxiliara.back());
    listaFilmeAuxiliara.pop_back();

    if (listaFilmeAuxiliara.empty() && this->cosFilme.size() < dimensiune) {
      listaFilmeAuxiliara = listaFilme;
      std::shuffle(listaFilmeAuxiliara.begin(), listaFilmeAuxiliara.end(), std::default_random_engine(std::random_device{}()));
    }
  }
  notifica();

}

const std::vector<Film>& CosFilm::getCosFilme() const {
  return this->cosFilme;
}


void CosFilm::exportCSV(const std::string& numeFisier) const {
  std::ofstream out(numeFisier);

  for (const auto& film : cosFilme) {
    out << film.getTitlu() << ","
        << film.getGen() << ","
        << film.getAn() << ","
        << film.getActor() << "\n";
  }
  out.close();
}






