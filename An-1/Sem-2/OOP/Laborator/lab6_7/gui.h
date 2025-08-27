#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QListView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QMap>
#include <QStringListModel>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QMessageBox>

#include "observator.h"
#include "CosFilme.h"
#include "service.h"
#include "CosReadOnlyGUI.h"
#include "CosCRUDGUI.h"
#include "filmeModel.h"
#include "filmTableModel.h"

class GUI : public QWidget {
    Q_OBJECT

public:
    explicit GUI(Service& srv, QWidget* parent = nullptr);
    void creeazaCosCrudGUI();
    void creeazaCosReadOnlyGUI();
private:
    Service& service;

    // Elemente UI
    QLineEdit *titluEdit, *genEdit, *anEdit, *actorEdit;
    QLineEdit *genNouEdit, *anNouEdit, *actorNouEdit;

    QPushButton *adaugaButton, *stergeButton, *modificaButton, *undoButton;
    QPushButton *sortareTitluButton, *sortareAnGenButton, *sortareActorButton;
    QPushButton *filtrareButton, *cosButton , *adaugaCosButton;

    QPushButton* cosNouButton;
    QPushButton* adaugaCosNouButton;
    QVBoxLayout* aDouaLinieNouButoane;


    QTableView* tableView;
    QStandardItemModel* tableModel;

//film table
    FilmTableModel* filmTableModel; //model personalizat



    QVBoxLayout* layoutButoaneGen;
    QMap<QString, QPushButton*> butoaneGen;

    // Layouturi
    QVBoxLayout* mainLayout;
    QVBoxLayout* butoaneLayout;
    QHBoxLayout* primaLinieButoane;
    QHBoxLayout* aDouaLinieButoane;



    void adaugaFilm();
    void stergeFilm();
    void modificaFilm();
    void actualizeazaListaFilme();
    void undo();
    void regenereazaButoane();

    void sortareDupaTitlu();
    void sortareDupaAnSiGen();
    void sortareDupaActor();
    void filtrareFilme();

    void adaugaCos();
    void deschideCos();


    std::vector<CosCRUDGUI*> ferestreCosCRUD;
    std::vector<CosReadOnlyGUI*> ferestreCosReadOnly;
    CosFilm& cos;




};





class CosGUI : public QWidget {
    Q_OBJECT
public:
    // Constructorul clasei CosGUI, care primește un vector de filme și un obiect Service
    CosGUI(const std::vector<Film>& filmeCos, Service& service);

    private slots:
        // Sloturi pentru diverse acțiuni ale utilizatorului
    void golesteCos();
    void umpleCosAleatoriu();
    void actualizeazaListaCos();
    void exportCSV();

private:
    Service& service;
    QListView* lista;
    FilmModel* filmModel;  // model personalizat
    QLineEdit* editNumeFisier;
};




#endif // GUI_H
