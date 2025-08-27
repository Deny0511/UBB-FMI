
#ifndef REPO_H
#define REPO_H

#include "domain.h"
#include "MyList.h"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <map>
#include <string>
#include <functional>
#include <random>


class RepositoryException : public std::runtime_error {
public:
    explicit RepositoryException(const std::string& msg) : std::runtime_error(msg) {}
};


class AbsRepo{
public:
    virtual void adauga(const Film& a)=0;

    virtual void modifica(const std::string& titlu, int an, const std::string& nouGen, int nouAn, const std::string& nouActor)=0;

    virtual void sterge(const std::string& titlu, int an)=0;

    virtual const std::vector<Film>& getAll() const noexcept = 0;
    virtual void setAll(const std::vector<Film>& filmeNoi) noexcept=0;
    virtual const Film& cauta(const std::string& titlu, int an) const =0;

    virtual ~AbsRepo()=default;
};



class Repo : public AbsRepo{
private:
    std::vector<Film> filme;

public:
    Repo() = default;
    virtual void adauga(const Film& film);
    virtual void sterge(const std::string& titlu, int an);
    virtual void modifica(const std::string& titlu, int an, const std::string& nouGen, int nouAn, const std::string& nouActor);
    virtual const Film& cauta(const std::string& titlu, int an) const;
    virtual const std::vector<Film>& getAll() const noexcept {return filme;}
    virtual void setAll(const std::vector<Film>& filmeNoi) noexcept{
        filme = std::move(filmeNoi);
    }
    virtual ~Repo();
};

class RepoFile :public Repo {
private:

    std::string numeFisier;


public:
    void writeAllToFile();

    void readAllFromFile();
    RepoFile(std::string numeFisier) :Repo(), numeFisier{ numeFisier } {
        readAllFromFile();
    }

    void adauga(const Film& film) override {
        Repo::adauga(film);
        writeAllToFile();
    }

    void modifica(const std::string& titlu, int an, const std::string& nouGen, int nouAn, const std::string& nouActor) override {
        Repo::modifica(titlu,an,nouGen,nouAn,nouActor);
        writeAllToFile();
    }

    void sterge(const std::string& titlu, int an) override {
        Repo::sterge(titlu,an);
        writeAllToFile();
    }


    ~RepoFile() override {
    }
};

class RepoNou : public AbsRepo {
private:

	std::map<std::string, Film> filme;
	float probabilitate;
    bool aruncaExceptie() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        float val = dis(gen);
        return val < probabilitate;
    }

public:

	RepoNou() = default;
    explicit RepoNou(float chance) : probabilitate(chance) {
        if (probabilitate < 0.0 || probabilitate > 1.0) {
            throw std::invalid_argument("Probabilitatea trebuie sa fie intre 0 si 1.");
        }
    }

    void adauga(const Film& film) override {
        if (aruncaExceptie()) {
            throw RepositoryException("Eroare: A fost aruncată o excepție la adăugarea unui film.");
        }
        filme[film.getTitlu()] = film;
    }

	void sterge(const std::string& titlu, int an) override {
        if (aruncaExceptie()) {
            throw RepositoryException("Eroare: A fost aruncată o excepție la ștergerea unui film.");
        }
        auto it = filme.find(titlu);
        if (it != filme.end()) {
            filme.erase(it);
        }
	}

	void modifica(const std::string& titlu, int an, const std::string& nouGen, int nouAn, const std::string& nouActor) override {
        if (aruncaExceptie()) {
            throw RepositoryException("Eroare: A fost aruncată o excepție la modificarea unui film.");
        }
        auto it = filme.find(titlu);
        if (it != filme.end()) {
            it->second.setGen(nouGen);
            it->second.setAn(nouAn);
            it->second.setActor(nouActor);
        }
	}

    const Film& cauta(const std::string& titlu, int an) const override {
        auto it = filme.find(titlu);
        if (it != filme.end()) {
            return it->second;}}

    const std::vector<Film>& getAll() const noexcept override {
        static std::vector<Film> listaFilme;
        listaFilme.clear();
        for (const auto& pair : filme) {
            listaFilme.push_back(pair.second);
        }
        return listaFilme;
    }


    void setAll(const std::vector<Film>& filmeNoi) noexcept override {
        filme.clear();
        for (const auto& film : filmeNoi) {
            filme[film.getTitlu()] = film;
        }
    }

	~RepoNou() override {}
};


#endif //REPO_H
