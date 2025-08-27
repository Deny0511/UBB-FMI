#ifndef UNDO_H
#define UNDO_H

#include "repo.h"
#include "domain.h"
#include <memory>

class ActiuneUndo {
public:
    virtual ~ActiuneUndo() = default;
    virtual void doUndo() = 0;
};

class UndoAdauga : public ActiuneUndo {
private:
    AbsRepo& repo;
    Film filmAdaugat;

public:
    UndoAdauga(AbsRepo& r, const Film& f) : repo(r), filmAdaugat(f) {}

    void doUndo() override {
        repo.sterge(filmAdaugat.getTitlu(), filmAdaugat.getAn());
    }
};

class UndoSterge : public ActiuneUndo {
private:
    AbsRepo& repo;
    Film filmSters;

public:
    UndoSterge(AbsRepo& r, const Film& f) : repo(r), filmSters(f) {}

    void doUndo() override {
        repo.adauga(filmSters);
    }
};

class UndoModifica : public ActiuneUndo {
private:
    AbsRepo& repo;
    Film filmVeche;
    std::string titlu;
    int an;

public:
    UndoModifica(AbsRepo& r, const Film& f, const std::string& t, int a)
        : repo(r), filmVeche(f), titlu(t), an(a) {}

    void doUndo() override {
        repo.modifica(titlu, an, filmVeche.getGen(), filmVeche.getAn(), filmVeche.getActor());
    }
};

#endif // UNDO_H
