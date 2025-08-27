#ifndef FILMTABLEMODEL_H
#define FILMTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "domain.h"  // clasa Film

class FilmTableModel : public QAbstractTableModel {
    Q_OBJECT

private:
    std::vector<Film> filme;

public:
    explicit FilmTableModel(const std::vector<Film>& filme, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setFilme(const std::vector<Film>& newFilme);
    const Film& getFilmAt(int row) const;
};

#endif // FILMTABLEMODEL_H
