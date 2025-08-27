#include "filmemodel.h"
#include <QString>

FilmModel::FilmModel(const std::vector<Film>& filme, QObject* parent)
    : QAbstractListModel(parent), filme(filme)
{}

int FilmModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return static_cast<int>(filme.size());
}

QVariant FilmModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() < 0 || index.row() >= static_cast<int>(filme.size()))
        return QVariant();

    if (role == Qt::DisplayRole) {
        const Film& film = filme[index.row()];
        return QString::fromStdString(film.getTitlu()) + " - " +
                                QString::fromStdString(film.getGen()) + " - " +
                                QString::number(film.getAn()) + " - " +
                                QString::fromStdString(film.getActor());
    }
    return QVariant();
}

void FilmModel::setFilme(const std::vector<Film>& newFilme) {
    beginResetModel();
    filme = newFilme;
    endResetModel();
}


