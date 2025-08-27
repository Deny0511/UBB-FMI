

#pragma once
#include "service.h"
#include "observator.h"
#include "CosFilme.h"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qtablewidget.h>
#include <qdebug.h>
#include <QInputDialog>
#include <QFormLayout>
#include <qfont.h>
#include <QTextEdit>
#include <vector>
#include <string>

class CosCRUDGUI : public QWidget, public Observator {
public:
    CosCRUDGUI(Service& service, CosFilm& cos) : service { service }, cos { cos } {
        initGUI();
        loadData();
        initConnect();
    }

    void updateaza() override {
        loadData();
    }

private:
    Service& service;
    CosFilm& cos;
    vector<Film> filme;

    QListWidget* listaInchirieri = new QListWidget{};
    QLineEdit* numarAdaugareRandomInCosEdit = new QLineEdit;
    QLineEdit* numeFisierExportEdit = new QLineEdit;
    QPushButton* butonGolireCos = new QPushButton{ "&Goleste cosul" };
    QPushButton* butonAdaugareRandomInCos = new QPushButton{ "&Adauga random in cos" };
    QPushButton* butonExportCSV = new QPushButton{ "&Exporta CSV" };


    void initGUI() {
        auto layoutPrincipalCos = new QVBoxLayout{};
        auto layoutButoaneCosInchirieri = new QHBoxLayout{};
        auto casetaAdaugareRandom = new QFormLayout;

        QLabel* textCosInchirieri = new QLabel("Cos de inchirieri");

        casetaAdaugareRandom->addRow(numarAdaugareRandomInCosEdit);
        numarAdaugareRandomInCosEdit->setPlaceholderText("Introduceti un numar de filme");
        numarAdaugareRandomInCosEdit->setFixedWidth(185);

        casetaAdaugareRandom->addRow(numeFisierExportEdit);
        numeFisierExportEdit->setPlaceholderText("Introduceti numele fisierului");
        numeFisierExportEdit->setFixedWidth(185);

        layoutButoaneCosInchirieri->addWidget(butonAdaugareRandomInCos);
        layoutButoaneCosInchirieri->addWidget(butonGolireCos);

        setLayout(layoutPrincipalCos);

        layoutPrincipalCos->addWidget(textCosInchirieri);
        layoutPrincipalCos->addWidget(listaInchirieri);
        layoutPrincipalCos->addLayout(layoutButoaneCosInchirieri);
        layoutPrincipalCos->addLayout(casetaAdaugareRandom);

        layoutButoaneCosInchirieri->addWidget(butonExportCSV);

    }

    void loadData() {
        listaInchirieri->clear();
        for (const auto& film : cos.getCosFilme()) {
            QString item = QString::fromStdString(film.getTitlu() + ", " + film.getGen() + ", " +
                std::to_string(film.getAn()) + ", " + film.getActor());
            listaInchirieri->addItem(item);
        }
        filme.clear();
    }

    void initConnect() {
        cos.adaugaObservatore(this);
        QObject::connect(butonGolireCos, &QPushButton::clicked, [&]() {
            service.golesteCosInchirieri();
            loadData();
            });

        QObject::connect(butonAdaugareRandomInCos, &QPushButton::clicked, [&]() {
            filme = service.getFilme();
            if (numarAdaugareRandomInCosEdit->text().toStdString() == "")
                QMessageBox::information(this, "Atentie!", "Introduceti un numar de filme pentru inchiriat!");

            cos.umpleRandomCosFilme(numarAdaugareRandomInCosEdit->text().toInt(), filme);

            QObject::connect(butonExportCSV, &QPushButton::clicked, [&]() {
        QString fileName = numeFisierExportEdit->text().trimmed();
        if (fileName.isEmpty()) {
            QMessageBox::warning(this, "Eroare", "Introduceti un nume de fisier pentru export.");
            return;
        }

        std::string numeFisier = fileName.toStdString();
        if (numeFisier.find(".csv") == std::string::npos) {
            numeFisier += ".csv";
        }

        try {
            service.exportaCosCSV(numeFisier);
            QMessageBox::information(this, "Export reusit", "Fisierul a fost salvat: " + QString::fromStdString(numeFisier));
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Eroare la export", QString::fromStdString(e.what()));
        }
    });




            loadData();
            });
    }

    ~CosCRUDGUI() {
        cos.stergeObservatore(this);
    }
};
