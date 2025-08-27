#include "repo.h"
#include<fstream>
#include<iostream>
#include<sstream>

void Repo::adauga(const Film& film) {
    auto it = std::find(filme.begin(), filme.end(), film);

    if (it != filme.end())
        throw RepositoryException("Filmul exista deja!");
    filme.push_back(film);

}


void Repo::sterge(const std::string& titlu, int an) {
    auto it = std::find_if(filme.begin(), filme.end(), [&titlu,an](const Film& f) {
        return f.getTitlu() == titlu && f.getAn() == an;
    });
    if (it == filme.end()) {
        throw RepositoryException("Filmul nu exista!");
    }
    filme.erase(it);

}

void Repo::modifica(const std::string& titlu, int an, const std::string& nouGen, int nouAn, const std::string& nouActor) {
    auto it = std::find_if(filme.begin(),filme.end(),[&titlu,an](const Film& f) {
        return f.getTitlu() == titlu && f.getAn() == an;
    });
    if ( it == filme.end() ) {
        throw RepositoryException("Filmul nu exista!");
    }
    *it = Film{titlu,nouGen,nouAn,nouActor};


}


Repo::~Repo()
{
}




void RepoFile::readAllFromFile() {
    std::ifstream fin(numeFisier);


    std::string linie;
    while (std::getline(fin, linie)) {
        std::stringstream ss(linie);
        std::string titlu, gen, anStr, actor;

        std::getline(ss, titlu, ',');
        std::getline(ss, gen, ',');
        std::getline(ss, anStr, ',');
        std::getline(ss, actor);

        int an = std::stoi(anStr);

        Film film{titlu, gen, an, actor};
        Repo::adauga(film);
    }
    fin.close();
}

void RepoFile::writeAllToFile() {
    std::ofstream fout(numeFisier);

    for (const auto& film : Repo::getAll()) {
        fout << film.getTitlu() << ","
             << film.getGen() << ","
             << film.getAn() << ","
             << film.getActor() << "\n";
    }
    fout.close();
}

const Film& Repo::cauta(const std::string& titlu, int an) const {
    for (const auto& film : this->filme) {
        if (film.getTitlu() == titlu && film.getAn() == an) {
            return film;
        }
    }
    throw RepositoryException("Filmul nu exista!");
}










