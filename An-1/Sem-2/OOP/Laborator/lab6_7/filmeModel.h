#ifndef FILMEMODEL_H
#define FILMEMODEL_H

#include <QAbstractListModel>
#include <vector>
#include "domain.h"  // presupun că ai o clasă Film cu metode getTitlu(), getGen(), getAn(), getActor()

class FilmModel : public QAbstractListModel {
    Q_OBJECT
private:
    std::vector<Film> filme;

public:
    explicit FilmModel(const std::vector<Film>& filme, QObject* parent = nullptr);

    // Override metode QAbstractListModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Optional: metode pentru actualizare model
    void setFilme(const std::vector<Film>& newFilme);
};

#endif // FILMEMODEL_H
