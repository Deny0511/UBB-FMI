#include "ui.h"
#include <iostream>
#include "validator.h"
#include "repo.h"
#include <string>
#include <vector>



void UI::adaugaFilm()const {
    std::string titlu, gen, actor;
    int an;
    std::cout << "Titlu: ";
    std::cin>>titlu;
    std::cout << "Gen: ";
    std::cin >>gen;
    std::cout << "An: ";
    std::cin >> an;
    std::cout << "Actor principal: ";
    std::cin>>actor;

    try {
        service.adaugaFilm(titlu, gen, an, actor);
        std::cout << "Filmul a fost adaugat cu succes!\n";
    } catch (const ValidationException& e) {
        std::cout << "Eroare validare: " << e.what() << "\n";
    } catch (const RepositoryException& e) {
        std::cout << "Eroare repo: " << e.what() << "\n";
    }catch (const std::exception& ex) {
        std::cout << "Eroare: " << ex.what() << "\n";
    }
}

void UI::stergeFilm()const {

        std::string titlu;
        int an;
        std::cout << "Titlu: ";
        std::cin>> titlu;
        std::cout << "An: ";
        std::cin >> an;

        try {
            service.stergeFilm(titlu, an);
            std::cout << "Filmul a fost sters cu succes!\n";
        } catch (const RepositoryException& e) {
            std::cout << "Eroare repo: " << e.what() << "\n";
        }catch (const std::exception& ex) {
            std::cout << "Eroare: " << ex.what() << "\n";
        }
}

void UI::afiseazaFilme()const {
        const auto& filme = service.getFilme();
        if (filme.empty()) {
            std::cout << "Nu exista filme in lista.\n";
            return;
        }

        for (const auto& film : filme) {
            std::cout << "Titlu: " << film.getTitlu()
                      << ", Gen: " << film.getGen()
                      << ", An: " << film.getAn()
                      << ", Actor: " << film.getActor() << "\n";
        }
}

void UI::modificaFilm()const {
    std::string titlu, nouGen, nouActor;
    int an, nouAn;
    std::cout << "Titlu film de modificat: ";
    std::cin>>titlu;
    std::cout << "Anul filmului: ";
    std::cin >> an;
    std::cout << "Gen nou: ";
    std::cin>> nouGen;
    std::cout << "An nou: ";
    std::cin >> nouAn;
    std::cout << "Actor principal nou: ";
    std::cin>>nouActor;

    try {
        service.modificaFilm(titlu, an, nouGen, nouAn, nouActor);
        std::cout << "Filmul a fost modificat cu succes!\n";
    } catch (const ValidationException& e) {
        std::cout << "Eroare validare: " << e.what() << "\n";
    }catch (const RepositoryException& e) {
        std::cout << "Eroare repo: " << e.what() << "\n";
    }
}

void UI::cautaFilme()const {
    std::string titlu, gen;
    int an;

    std::cout << "Introduceti titlul filmului (sau lasati gol pentru a nu filtra dupa titlu): ";
    std::cin.ignore(); // Curatam bufferul
    std::getline(std::cin, titlu); // Citim titlul (poate fi gol)

    std::cout << "Introduceti genul filmului (sau lasati gol pentru a nu filtra dupa gen): ";
    std::getline(std::cin, gen); // Citim genul (poate fi gol)

    std::cout << "Introduceti anul filmului (sau -1 pentru a nu filtra dupa an): ";
    std::cin >> an;

    // Căutăm filmele folosind funcția din Service
    auto rezultate = service.cautaFilme(titlu, gen, an);

    if (rezultate.empty()) {
        std::cout << "Nu au fost gasite filme care sa corespunda criteriilor!\n";
        return;
    }
    std::cout << "Filme gasite:\n";
    for (const auto& film : rezultate) {
            std::cout << "Titlu: " << film.getTitlu()
                      << ", Gen: " << film.getGen()
                      << ", An: " << film.getAn()
                      << ", Actor principal: " << film.getActor() << "\n";
        }
}


void UI::filtrareFilme()const {

        std::string titlu;
        int an;

        std::cout << "Introduceti titlul filmului (sau lasati gol pentru a nu filtra dupa titlu): ";
        std::cin.ignore(); // Curatam bufferul
        std::getline(std::cin, titlu); // Citim titlul (poate fi gol)

        std::cout << "Introduceti anul filmului (sau -1 pentru a nu filtra dupa an): ";
        std::cin >> an;

        // Filtrăm filmele folosind funcția din Service
        auto rezultate = service.filtrareFilme(titlu, an);

        if (rezultate.empty()) {
            std::cout << "Nu au fost gasite filme care sa corespunda criteriilor!\n";
            return;
        }
        std::cout << "Filme gasite:\n";
        for (const auto& film : rezultate) {
                std::cout << "Titlu: " << film.getTitlu()
                          << ", Gen: " << film.getGen()
                          << ", An: " << film.getAn()
                          << ", Actor principal: " << film.getActor() << "\n";
            }
}


void UI::sortari() {
    int optiuneSortare;
    std::cout << "Alege criteriul de sortare:\n";
    std::cout << "1. Titlu\n";
    std::cout << "2. Actor principal\n";
    std::cout << "3. Anul aparitiei si gen\n";
    std::cout << "0. Inapoi\n";
    std::cin >> optiuneSortare;

    switch (optiuneSortare) {
        case 1:
            service.sortareFilmeDupaTitlu();
        break;
        case 2:
            service.sortareFilmeDupaActor();
        break;
        case 3:
            service.sortareFilmeDupaAnSiGen();
        break;
        case 0:
            return;
        default:
            std::cout << "Optiune invalida. Incercati din nou.\n";
        break;
    }

}






void UI::adaugaFilmInCos() {
    std::string titluFilm;
    std::cin.ignore();
    std::cout << "Introduceti titlul filmului pentru a-l adauga in cosul de inchirieri: ";
    getline(std::cin, titluFilm);
    service.adaugaFilmInCosInchirieri(titluFilm);
    std::cout << "Total filme in cos: " << service.getAllCosInchirieri().size() << "\n";

}


void UI::umple_random_cos() {
    int dimensiune;
    std::cin.ignore();
    std::cout << "Ibtroduceti numarul de filme de adaugat:";
    std::cin >> dimensiune;
    afiseazaFilmCos(service.umpleRandomCosInchirieri(dimensiune));
    std::cout << "Total filme in cos: " << service.getAllCosInchirieri().size() << "\n";


}

void UI::afiseazaFilmCos(const std::vector<Film>& filme) {
    if (filme.size() == 0) {
        std::cout << "Nu exista filme in lista!";
        return;
    }
    std::cout<<"Filme:\n";
    int i =0;
    for (const auto& filme : filme) {
        i++;
        std::cout << i <<". Titlu:" << filme.getTitlu() <<"; Gen:"<<  filme.getGen() <<"; An:"<<  filme.getAn() << "; Actor principal:" << filme.getActor() << "\n";
    }
    std::cout << "Total filme in cos: " << service.getAllCosInchirieri().size() << "\n";


}

void UI::exportaCos() {
    std::cout << "Introduceti numele fisierului pentru export (ex: cos.csv): ";
    std::string numeFisier;
    std::cin >> numeFisier;

    try {
        service.exportaCosCSV(numeFisier);
        std::cout << "Export realizat cu succes in fisier "<< "\n";
    } catch (const std::exception& ex) {
        std::cout << "Eroare la export: " << ex.what() << "\n";
    }
    std::cout << "Total filme in cos: " << service.getAllCosInchirieri().size() << "\n";
}



void UI::undo() {

    try {
        service.undo();
        std::cout << "Undo efectuat cu succes!" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Eroare: " << e.what() << std::endl;
    }
}

void UI::run() {
    while (true) {
        std::cout << "\n1. Adauga film\n"
                     "2. Sterge film\n"
                     "3. Afiseaza filme\n"
                     "4. Modifica film\n"
                     "5. Cauta filme\n"
                     "6. Filtreaza filme\n"
                     "7. Sorteaza filme\n"
                     "8. Adauga in cos inchirieri\n"
                     "9. Golire cos inchirieri\n"
                     "10. Umple random cos inchiriei\n"
                     "11. Afisare cos inchiriei\n"
                     "12. Exporta film in fisier CSV.\n"
                     "13. Undo.\n"
                     "0. Iesire\nAlege o optiune: ";
        int optiune;
        std::cin >> optiune;

        switch (optiune) {
            case 1: adaugaFilm(); break;
            case 2: stergeFilm(); break;
            case 3: afiseazaFilme(); break;
            case 4: modificaFilm(); break;
            case 5: cautaFilme();break;
            case 6: filtrareFilme();break;
            case 7: sortari();break;
            case 8: adaugaFilmInCos();break;
            case 9: afiseazaFilmCos(service.golesteCosInchirieri());
                    std::cout << "\nCos golit cu succes! ";
                     break;
            case 10: umple_random_cos();break;
            case 11: afiseazaFilmCos(service.getAllCosInchirieri());break;
            case 12: exportaCos() ;break;
            case 13: undo();break;
            case 0: return;
            default: std::cout << "Optiune invalida!\n";
        }
    }
}
