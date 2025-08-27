#include "filmtablemodel.h"
#include <QString>

FilmTableModel::FilmTableModel(const std::vector<Film>& filme, QObject* parent)
    : QAbstractTableModel(parent), filme(filme)
{}

int FilmTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid())
        return 0;
    return static_cast<int>(filme.size());
}

int FilmTableModel::columnCount(const QModelIndex& parent) const {
    return 4; // Titlu, Gen, An, Actor
}

QVariant FilmTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto& film = filme.at(index.row());
        switch (index.column()) {
            case 0: return QString::fromStdString(film.getTitlu());
            case 1: return QString::fromStdString(film.getGen());
            case 2: return QString::number(film.getAn());
            case 3: return QString::fromStdString(film.getActor());
        }
    }
    return QVariant();
}

QVariant FilmTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "Titlu";
            case 1: return "Gen";
            case 2: return "An";
            case 3: return "Actor";
        }
    }
    return QVariant();
}

void FilmTableModel::setFilme(const std::vector<Film>& newFilme) {
    beginResetModel();
    filme = newFilme;
    endResetModel();
}

const Film& FilmTableModel::getFilmAt(int row) const {
    return filme.at(row);
}
