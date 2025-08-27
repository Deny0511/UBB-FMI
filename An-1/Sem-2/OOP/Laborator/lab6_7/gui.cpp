#include "gui.h"
#include <QMessageBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QInputDialog>
#include<QFileDialog>

#include <set>

GUI::GUI(Service& srv, QWidget* parent)
    : QWidget(parent), service(srv), cos{srv.getCosInchirieri()}
{


    auto* mainLayout = new QHBoxLayout{this};

    // === Layout stânga (tabelul de filme) ===
    auto* stangaLayout = new QVBoxLayout;
    tableView = new QTableView;


    //film table
    filmTableModel = new FilmTableModel(service.getFilme(), this);
    tableView->setModel(filmTableModel);



    //tableModel = new QStandardItemModel(0, 4, this);
    //tableModel->setHeaderData(0, Qt::Horizontal, "Titlu");
    //tableModel->setHeaderData(1, Qt::Horizontal, "Gen");
    //tableModel->setHeaderData(2, Qt::Horizontal, "An");
    //tableModel->setHeaderData(3, Qt::Horizontal, "Actor principal");
    //tableView->setModel(tableModel);


    stangaLayout->addWidget(new QLabel("Filme disponibile:"));
    stangaLayout->addWidget(tableView);
    mainLayout->addLayout(stangaLayout);


    // === Layout dreapta (inputuri + butoane + genuri) ===
    auto* dreaptaLayout = new QVBoxLayout;
    dreaptaLayout->setSpacing(12);
    dreaptaLayout->setContentsMargins(10, 10, 10, 10);

    // --- Inputuri ---
    auto* formLayout = new QFormLayout;
    titluEdit = new QLineEdit;
    genEdit = new QLineEdit;
    genNouEdit = new QLineEdit;
    anEdit = new QLineEdit;
    anNouEdit = new QLineEdit;
    actorEdit = new QLineEdit;
    actorNouEdit = new QLineEdit;

    formLayout->addRow("Titlu:", titluEdit);
    formLayout->addRow("Gen:", genEdit);
    formLayout->addRow("Gen nou:", genNouEdit);
    formLayout->addRow("An:", anEdit);
    formLayout->addRow("An nou:", anNouEdit);
    formLayout->addRow("Actor:", actorEdit);
    formLayout->addRow("Actor nou:", actorNouEdit);

    auto* inputGroup = new QGroupBox("Date Film");
    inputGroup->setLayout(formLayout);
    dreaptaLayout->addWidget(inputGroup);

    // --- Butoane pe genuri ---
    layoutButoaneGen = new QVBoxLayout;
    auto* genGroup = new QGroupBox("Filme pe gen");
    genGroup->setLayout(layoutButoaneGen);
    layoutButoaneGen->setAlignment(Qt::AlignTop);
    genGroup->setFixedWidth(120);

    // --- Butoane de acțiune verticale ---
    auto* layoutButoaneActiuni = new QVBoxLayout;
    adaugaButton = new QPushButton("Adauga");
    stergeButton = new QPushButton("Sterge");
    modificaButton = new QPushButton("Modifica");
    undoButton = new QPushButton("Undo");

    sortareTitluButton = new QPushButton("Sorteaza dupa Titlu");
    sortareAnGenButton = new QPushButton("Sorteaza dupa An si Gen");
    sortareActorButton = new QPushButton("Sorteaza dupa Actor");
    filtrareButton = new QPushButton("Filtrare Filme");
    adaugaCosButton = new QPushButton("Adauga in Cos");

    layoutButoaneActiuni->addWidget(adaugaButton);
    layoutButoaneActiuni->addWidget(stergeButton);
    layoutButoaneActiuni->addWidget(modificaButton);
    layoutButoaneActiuni->addWidget(undoButton);
    layoutButoaneActiuni->addSpacing(10);
    layoutButoaneActiuni->addWidget(sortareTitluButton);
    layoutButoaneActiuni->addWidget(sortareAnGenButton);
    layoutButoaneActiuni->addWidget(sortareActorButton);
    layoutButoaneActiuni->addSpacing(10);
    layoutButoaneActiuni->addWidget(filtrareButton);
    layoutButoaneActiuni->addWidget(adaugaCosButton);
    layoutButoaneActiuni->addSpacing(10);

    auto* actiuniGroup = new QGroupBox("Butoane actiune");
    actiuniGroup->setLayout(layoutButoaneActiuni);

    QPalette palette;
    palette.setColor(QPalette::Base,QColor(255,105,180,70));
    palette.setColor(QPalette::Window,QColor(255,105,180,108));
    palette.setColor(QPalette::Button,QColor(255,105,180,240));

    titluEdit->setPalette(palette);
    genEdit->setPalette(palette);
    genNouEdit->setPalette(palette);
    anEdit->setPalette(palette);
    actorEdit->setPalette(palette);
    actorNouEdit->setPalette(palette);
    anNouEdit->setPalette(palette);

    adaugaButton->setPalette(palette);
    stergeButton->setPalette(palette);
    modificaButton->setPalette(palette);
    undoButton->setPalette(palette);
    sortareTitluButton->setPalette(palette);
    sortareAnGenButton->setPalette(palette);
    sortareActorButton->setPalette(palette);
    filtrareButton->setPalette(palette);

    tableView->setPalette(palette);


    // --- Grupare finală pe orizontală: genuri + acțiuni ---
    auto* layoutButoaneComplet = new QHBoxLayout;
    layoutButoaneComplet->addWidget(genGroup);
    layoutButoaneComplet->addWidget(actiuniGroup);
    dreaptaLayout->addLayout(layoutButoaneComplet);

    mainLayout->addLayout(dreaptaLayout);

    // --- Connect ---
    connect(adaugaButton, &QPushButton::clicked, this, &GUI::adaugaFilm);
    connect(stergeButton, &QPushButton::clicked, this, &GUI::stergeFilm);
    connect(modificaButton, &QPushButton::clicked, this, &GUI::modificaFilm);
    connect(undoButton, &QPushButton::clicked, this, &GUI::undo);
    connect(sortareTitluButton, &QPushButton::clicked, this, &GUI::sortareDupaTitlu);
    connect(sortareAnGenButton, &QPushButton::clicked, this, &GUI::sortareDupaAnSiGen);
    connect(sortareActorButton, &QPushButton::clicked, this, &GUI::sortareDupaActor);
    connect(filtrareButton, &QPushButton::clicked, this, &GUI::filtrareFilme);
    connect(adaugaCosButton,&QPushButton::clicked,this, &GUI::adaugaCos);

    adaugaCosButton->setPalette(palette);



    cosButton = new QPushButton("Deschide Cos");
    layoutButoaneActiuni->addWidget(cosButton);

    connect(cosButton, &QPushButton::clicked, this, &GUI::deschideCos);
    cosButton->setPalette(palette);




    //cos


    aDouaLinieNouButoane = new QVBoxLayout();

    cosNouButton = new QPushButton("Deschide Cos CRUD");
    adaugaCosNouButton = new QPushButton("Deschide Cos ReadOnly");

    aDouaLinieNouButoane->addWidget(cosNouButton);
    aDouaLinieNouButoane->addWidget(adaugaCosNouButton);
    mainLayout->addLayout(aDouaLinieNouButoane);

    connect(cosNouButton, &QPushButton::clicked, this, &GUI::creeazaCosCrudGUI);
    connect(adaugaCosNouButton, &QPushButton::clicked, this, &GUI::creeazaCosReadOnlyGUI);
    cosNouButton->setPalette(palette);
    adaugaCosNouButton->setPalette(palette);

    layoutButoaneActiuni->addWidget(adaugaCosNouButton);
    layoutButoaneActiuni->addWidget(cosNouButton);


    // --- Inițializări ---
    actualizeazaListaFilme();

}


void GUI::actualizeazaListaFilme() {
    // tableModel->removeRows(0, tableModel->rowCount());
    // const auto& filme = service.getFilme();
    // for (const auto& film : filme) {
    //     QList<QStandardItem*> items;
    //     items.append(new QStandardItem(QString::fromStdString(film.getTitlu())));
    //     items.append(new QStandardItem(QString::fromStdString(film.getGen())));
    //     items.append(new QStandardItem(QString::number(film.getAn())));
    //     items.append(new QStandardItem(QString::fromStdString(film.getActor())));
    //     tableModel->appendRow(items);
    // }

    std::vector<Film> filmeActualizate = service.getFilme();
    filmTableModel->setFilme(filmeActualizate);
    regenereazaButoane();
}

void GUI::adaugaFilm() {
    QString titlu = titluEdit->text();
   QString gen = genEdit->text();
    int an = anEdit->text().toInt();
    QString actor = actorEdit->text();

    try {
        service.adaugaFilm(titlu.toStdString(), gen.toStdString(), an, actor.toStdString());
        QMessageBox::information(this, "Succes", "Film adăugat!");
        actualizeazaListaFilme();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Eroare", e.what());
    }
}

void GUI::stergeFilm() {
    QString titlu = titluEdit->text();
    int an = anEdit->text().toInt();

    try {
        service.stergeFilm(titlu.toStdString(), an);
        QMessageBox::information(this, "Succes", "Film șters!");
        actualizeazaListaFilme();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Eroare", e.what());
    }
}

void GUI::modificaFilm() {
    QString titlu = titluEdit->text();
    int an = anEdit->text().toInt();
    QString nouGen = genNouEdit->text();
    int nouAn = anNouEdit->text().toInt();
    QString nouActor = actorNouEdit->text();

    try {
        service.modificaFilm(titlu.toStdString(), an, nouGen.toStdString(), nouAn, nouActor.toStdString());
        QMessageBox::information(this, "Succes", "Film modificat!");
        actualizeazaListaFilme();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Eroare", e.what());
    }
}

void GUI::undo() {
    try {
        service.undo();
        QMessageBox::information(this, "Succes", "Undo realizat!");
        actualizeazaListaFilme();
    } catch (const std::runtime_error& e) {
        QMessageBox::warning(this, "Eroare", e.what());
    }
}


void GUI::regenereazaButoane() {
    QLayoutItem* item;
    while ((item = layoutButoaneGen->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    QPalette palette;
    palette.setColor(QPalette::Base,QColor(255,105,180,70));
    palette.setColor(QPalette::Window,QColor(255,105,180,108));
    palette.setColor(QPalette::Button,QColor(50,105,180,100));

    std::set<std::string> genuri;
    for (const auto& film : service.getFilme()) {
        genuri.insert(film.getGen());
    }



    for (const auto& gen : genuri) {
        QString qgen = QString::fromStdString(gen);
        auto* buton = new QPushButton(qgen, this);
        layoutButoaneGen->addWidget(buton);
        butoaneGen[qgen] = buton;
        butoaneGen[qgen]->setPalette(palette);

        connect(buton, &QPushButton::clicked, this, [this, qgen]() {
            int nr = service.nrFilmeCuGen(qgen.toStdString());
            QMessageBox::information(this, "Filme cu genul",
                QString("Există %1 filme cu genul %2").arg(QString::number(nr), qgen));
        });
    }
}




void GUI::filtrareFilme() {
    QString titlu = titluEdit->text();
    int an = anEdit->text().toInt();

    auto filmeFiltrate = service.filtrareFilme(titlu.toStdString(), an);

    tableModel->removeRows(0, tableModel->rowCount());
    for (const auto& film : filmeFiltrate) {
        QList<QStandardItem*> items;
        items.append(new QStandardItem(QString::fromStdString(film.getTitlu())));
        items.append(new QStandardItem(QString::fromStdString(film.getGen())));
        items.append(new QStandardItem(QString::number(film.getAn())));
        items.append(new QStandardItem(QString::fromStdString(film.getActor())));
        tableModel->appendRow(items);
    }
}


void GUI::sortareDupaTitlu() {
    service.sortareFilmeDupaTitlu();
    actualizeazaListaFilme();
}

void GUI::sortareDupaAnSiGen() {
    service.sortareFilmeDupaAnSiGen();
    actualizeazaListaFilme();
}

void GUI::sortareDupaActor() {
    service.sortareFilmeDupaActor();
    actualizeazaListaFilme();
}

void GUI::deschideCos() {
    const auto& filmeCos = service.getAllCosInchirieri();
    auto* fereastraCos = new CosGUI(filmeCos, service);
    fereastraCos->setAttribute(Qt::WA_DeleteOnClose);
    fereastraCos->show();  // Afișează fereastra
}

void GUI::adaugaCos() {
    QString titlu = titluEdit->text();

    try {
        service.adaugaFilmInCosInchirieri(titlu.toStdString());
        QMessageBox::information(this, "Succes", "Film adaugat!");
        actualizeazaListaFilme();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Eroare", e.what());
    }
}


CosGUI::CosGUI(const std::vector<Film>& filmeCos, Service& service)
    : service(service) {
    // Layout-ul principal
    auto* layout = new QVBoxLayout(this);

    // Eticheta pentru lista de filme
    auto* label = new QLabel("Filme din cos:");
    layout->addWidget(label);

    filmModel = new FilmModel(filmeCos, this);

    lista = new QListView(this);
    lista->setModel(filmModel);

   // layout->addWidget(lista);

    // Lista de filme adăugate în coș
   // lista = new QListWidget(this);
    // for (const auto& film : filmeCos) {
    //     QString itemText = QString::fromStdString(film.getTitlu()) + " - " +
    //                            QString::fromStdString(film.getGen()) + " - " +
    //                            QString::number(film.getAn()) + " - " +
    //                            QString::fromStdString(film.getActor());
    //     lista->addItem(itemText);
    // }


    layout->addWidget(lista);

    // Buton pentru golirea coșului
    auto* golesteCosBtn = new QPushButton("Goleste Cos", this);
    connect(golesteCosBtn, &QPushButton::clicked, this, &CosGUI::golesteCos);
    layout->addWidget(golesteCosBtn);

    // Buton pentru a adăuga filme aleatorii în coș
    auto* umpleCosBtn = new QPushButton("Umple Cos Aleatoriu", this);
    connect(umpleCosBtn, &QPushButton::clicked, this, &CosGUI::umpleCosAleatoriu);
    layout->addWidget(umpleCosBtn);



    auto* lblNumeFisier = new QLabel("Nume fisier CSV:", this);
    editNumeFisier = new QLineEdit(this);
    layout->addWidget(lblNumeFisier);
    layout->addWidget(editNumeFisier);


    auto* btnExportCSV = new QPushButton("Exporta CSV", this);
    layout->addWidget(btnExportCSV);

    // Conectare
    connect(btnExportCSV, &QPushButton::clicked, this, &CosGUI::exportCSV);


}

void CosGUI::golesteCos() {
    // Apelează funcția de golire coș din serviciu
    service.golesteCosInchirieri();

    // Afișează un mesaj pentru a confirma golirea coșului
    QMessageBox::information(this, "Cos Golit", "Cosul a fost golit cu succes.");
    actualizeazaListaCos();
}

void CosGUI::umpleCosAleatoriu() {
    bool ok;
    int dimensiune = QInputDialog::getInt(this, "Dimensiune Cos",
                                           "Alege dimensiunea cosului:",
                                           5,  // valoare implicită
                                           1,  // valoare minimă
                                           100,  // valoare maximă
                                           1,  // pasul
                                           &ok);

    if (ok) {
        // Dacă utilizatorul a ales o dimensiune validă
        service.umpleRandomCosInchirieri(dimensiune);

        // Afișează un mesaj pentru a confirma umplerea coșului
        QMessageBox::information(this, "Cos Umplut", "Cosul a fost umplut aleatoriu.");
    } else {
        // Dacă utilizatorul a anulat, nu faci nimic
        QMessageBox::warning(this, "Cos Anulat", "Umplerea cosului a fost anulata.");
    }
    actualizeazaListaCos();

}

void CosGUI::actualizeazaListaCos() {
    // Golește lista existentă
    // lista->clear();
    //
    // // Preia filmele din coș
    // const auto& filmeCos = service.getAllCosInchirieri();
    //
    // // Adaugă filmele actualizate în listă
    // for (const auto& film : filmeCos) {
    //     QString itemText = QString::fromStdString(film.getTitlu()) + " - " +
    //                            QString::fromStdString(film.getGen()) + " - " +
    //                            QString::number(film.getAn()) + " - " +
    //                            QString::fromStdString(film.getActor());
    //     lista->addItem(itemText);
    // }


    const auto& filmeCos = service.getAllCosInchirieri();
    filmModel->setFilme(filmeCos);  // actualizează datele din model
}

void CosGUI::exportCSV() {
    QString fileName = editNumeFisier->text().trimmed();
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Eroare", "Introduceti un nume de fisier pentru export.");
        return;
    }

    std::string numeFisier = fileName.toStdString();
    if (numeFisier.find(".csv") == std::string::npos) {
        numeFisier += ".csv";  // Adaugă extensia dacă lipsește
    }

    try {
        service.exportaCosCSV(numeFisier);
        QMessageBox::information(this, "Export reusit", "Fisierul a fost salvat: " + QString::fromStdString(numeFisier));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Eroare la export", QString::fromStdString(e.what()));
    }
}


void GUI::creeazaCosCrudGUI() {
    auto* f = new CosCRUDGUI(service, cos);
    f->show();
    ferestreCosCRUD.push_back(f);
}

void GUI::creeazaCosReadOnlyGUI() {
    auto* f = new CosReadOnlyGUI(cos);
    f->show();
    ferestreCosReadOnly.push_back(f);
}
