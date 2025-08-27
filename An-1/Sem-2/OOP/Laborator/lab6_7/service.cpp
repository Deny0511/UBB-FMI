#include "service.h"
#include "validator.h"
#include <vector>

Service::Service(AbsRepo& r) : repo{ r },validator{ validator }, cosInchirieri{ cosInchirieri } {}

void Service::adaugaFilm(const std::string& titlu, const std::string& gen, int an, const std::string& actor) {
    try {
        Validator::validateTitlu(titlu);
        Validator::validateAn(an);
        Validator::validateActor(actor);
        Validator::validateGen(gen);
    }catch(const std::runtime_error& e) {
        throw ValidationException{e.what()};
    }

    Film f{ titlu, gen, an, actor };
    repo.adauga(f);
    undoList.push_back(std::make_unique<UndoAdauga>(repo, f));
    }

void Service::stergeFilm(const std::string& titlu, int an) {
    const Film& filmSters = repo.cauta(titlu, an);  // Obține filmul înainte să-l ștergi
    undoList.push_back(std::make_unique<UndoSterge>(repo, filmSters));
    repo.sterge(titlu, an);

}

void Service::modificaFilm(const std::string& titlu, int an, const std::string& nouGen, int nouAn, const std::string& nouActor) {
    Film filmVechi;
    filmVechi = repo.cauta(titlu, an);
    try {
        Validator::validateGen(nouGen);
        Validator::validateAn(nouAn);
        Validator::validateActor(nouActor);
    }catch(const std::runtime_error& e) {
        throw ValidationException{e.what()};
    }

    repo.modifica(titlu, an, nouGen, nouAn, nouActor);
    undoList.push_back(std::make_unique<UndoModifica>(repo, filmVechi, titlu, nouAn));
}

std::vector<Film> Service::cautaFilme(const std::string& titlu, const std::string& gen, int an)const {
    std::vector<Film> rezultate;
    const auto& all = repo.getAll();
    std::copy_if(all.begin(), all.end(),std::back_inserter(rezultate),[&](const Film& f) {
        bool titluOK = titlu.empty() || f.getTitlu() == titlu;
        bool genOK = gen.empty() || f.getGen() == gen;
        bool anOK = (an < 0 || f.getAn() == an);
        return titluOK && genOK && anOK;
    });
    return rezultate;}


void Service::undo() {
    if (undoList.empty()) {
        throw std::runtime_error("Nu exista operatii pentru a fi facute undo.");
    }
    // Apel polimorf pentru a executa undo
    undoList.back()->doUndo();
    undoList.pop_back(); // Elimina ultima actiune din lista
}



const std::vector<Film>& Service::getFilme() const {
    return repo.getAll();
}


std::vector<Film> Service::filtrareFilme(const std::string& titlu, int an) const {
    std::vector<Film> rezultate;
    const auto& all = repo.getAll();
    std::copy_if(all.begin(), all.end(), std::back_inserter(rezultate),
        [&](const Film& f) {
            bool titluOk = titlu.empty() || f.getTitlu() == titlu;
            bool anOk = (an < 0) || f.getAn() == an;
            return titluOk && anOk;
        }
    );
    return rezultate;}





static bool cmpAnGen(const Film& a, const Film& b) {
    if (a.getAn() != b.getAn()) return a.getAn() < b.getAn();
    return a.getGen() < b.getGen();
}

static bool cmpTitlu(const Film& a, const Film& b) {
    return a.getTitlu() < b.getTitlu();
}

static bool cmpActor(const Film& a, const Film& b) {
    return a.getActor() < b.getActor();
}

void Service::sortareFilmeDupaAnSiGen() const {
    auto copy = repo.getAll();
    std::sort(copy.begin(), copy.end(), cmpAnGen);
    repo.setAll(std::move(copy));
}

void Service::sortareFilmeDupaTitlu() const {
    auto copy = repo.getAll();
    std::sort(copy.begin(), copy.end(), cmpTitlu);
    repo.setAll(std::move(copy));
}

void Service::sortareFilmeDupaActor() const {
    auto copy = repo.getAll();
    std::sort(copy.begin(), copy.end(), cmpActor);
    repo.setAll(std::move(copy));
}









const std::vector<Film>& Service::adaugaFilmInCosInchirieri(const std::string& titluFilm) {
    auto rezultate = cautaFilme(titluFilm);
    if (rezultate.empty()) throw RepositoryException("Filmul nu exista!"); ;
    const Film& filmCautat = rezultate.front();
    auto& cos = cosInchirieri.getCosFilme();
    bool deja = std::any_of(cos.begin(), cos.end(), [&](const Film& f) { return f == filmCautat; });
    if (!deja) cosInchirieri.adaugaCosFilme(filmCautat);
    return cosInchirieri.getCosFilme();
}

const std::vector<Film>& Service::golesteCosInchirieri() {
    cosInchirieri.golesteCosFilme();
    return cosInchirieri.getCosFilme();
}

const std::vector<Film>& Service::umpleRandomCosInchirieri(int dimensiune) {
    cosInchirieri.umpleRandomCosFilme(dimensiune, repo.getAll());
    return cosInchirieri.getCosFilme();
}

const std::vector<Film>& Service::getAllCosInchirieri() {
    return cosInchirieri.getCosFilme();
}

void Service::exportaCosCSV(const std::string& numeFisier) const {
    cosInchirieri.exportCSV(numeFisier);
}


int Service::nrFilmeCuGen(const std::string& gen) const {
    int count = 0;
    for (const auto& film : getFilme()) {
        if (film.getGen() == gen) {
            count++;
        }
    }
    return count;
}


