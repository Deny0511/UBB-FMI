
#ifndef SERVICE_H
#define SERVICE_H

#include "repo.h"
#include "CosFilme.h"
#include "validator.h"
#include "MyList.h"
#include <vector>
#include <random>
#include <memory>
#include "undo.h"




class Service {
private:
    AbsRepo& repo;
    //Repo& repo;
    Validator& validator;
    CosFilm& cosInchirieri;
    std::vector<std::unique_ptr<ActiuneUndo>> undoList;
public:
    Service(AbsRepo& repository, Validator& validator, CosFilm& cosInchirieri) noexcept : repo{ repository }, validator{ validator }, cosInchirieri{ cosInchirieri } {}
    Service(AbsRepo& r);

    CosFilm& getCosInchirieri() {
        return cosInchirieri;
    }

    void adaugaFilm(const std::string& titlu, const std::string& gen, int an, const std::string& actor);
    void stergeFilm(const std::string& titlu, int an);
    void modificaFilm(const std::string& titlu, int an, const std::string& nouGen, int nouAn, const std::string& nouActor);
    void undo();
    const std::vector<Film>& getFilme() const;
    std::vector<Film> cautaFilme(const std::string& titlu = "", const std::string& gen = "", int an = -1)const;
    std::vector<Film> filtrareFilme(const std::string& titlu, int an) const;
    void sortareFilmeDupaAnSiGen() const;
    void sortareFilmeDupaTitlu() const;
    void sortareFilmeDupaActor() const;


    const std::vector<Film>& adaugaFilmInCosInchirieri(const std::string& titluFilm);

    const std::vector<Film>& golesteCosInchirieri();

    const std::vector<Film>& umpleRandomCosInchirieri(int dimensiune);

    const std::vector<Film>& getAllCosInchirieri();

    void exportaCosCSV(const std::string& numeFisier) const;

    int nrFilmeCuGen(const std::string& gen) const;
};

#endif //SERVICE_H
