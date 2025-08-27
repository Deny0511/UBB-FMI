
#include "teste.h"
#include "service.h"
#include "validator.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

void Teste::testFilm() {
    Film f("Inception", "SF", 2010, "Leonardo DiCaprio");
    assert(f.getTitlu() == "Inception");
    assert(f.getGen() == "SF");
    assert(f.getAn() == 2010);
    assert(f.getActor() == "Leonardo DiCaprio");
    Film f2("Inception", "SF", 2010, "Leonardo DiCaprio");
    Film f3("Interstellar", "SF", 2014, "Matthew McConaughey");

    assert(f == f2);

    assert(!(f == f3));

}

void Teste::testRepo() {
    Repo repo;
    Film f("Inception", "SF", 2010, "Leonardo DiCaprio");
    repo.adauga(f);
    assert(repo.getAll().size() == 1);
    Film f2("Inception", "SF", 2010, "Leonardo DiCaprio");

    try {
        repo.adauga(f2);
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Filmul exista deja!"); // Verifică mesajul excepției
    }
    repo.sterge("Inception", 2010);
    assert(repo.getAll().empty());
    try {
        repo.sterge("Inception", 2010);
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Filmul nu exista!"); // Verifică mesajul excepției
    }
}

void Teste::testService() {
    Repo repo;
    Service service{ repo };
    service.adaugaFilm("Inception", "SF", 2010, "Leonardo DiCaprio");
    assert(service.getFilme().size() == 1);
    service.stergeFilm("Inception", 2010);
    assert(service.getFilme().empty());
}

void Teste::testRepoModifica() {
    Repo repo;

    Film f1("Inception", "SF", 2010, "Leonardo DiCaprio");
    repo.adauga(f1);

    assert(repo.getAll().size() == 1);

    repo.modifica("Inception", 2010, "SF", 2012, "Matthew McConaughey");

    const std::vector<Film>& filme = repo.getAll();
    assert(filme.size() == 1);
    assert(filme[0].getTitlu() == "Inception");
    assert(filme[0].getAn() == 2012);
    assert(filme[0].getActor() == "Matthew McConaughey");

    try {
        repo.modifica("NonExistent Film", 2020, "Drama", 2021, "Unknown Actor");
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Filmul nu exista!");
    }

}


void Teste::testServiceModificaFilm() {
    Repo repo;

    Service service{ repo };

    service.adaugaFilm("Inception", "SF", 2010, "Leonardo DiCaprio");

    assert(service.getFilme().size() == 1);
    assert(service.getFilme()[0].getTitlu() == "Inception");
    assert(service.getFilme()[0].getAn() == 2010);
    assert(service.getFilme()[0].getActor() == "Leonardo DiCaprio");

    try {
        service.adaugaFilm("Inception", "", 2022, "Matthew McConaughey");  // Gen invalid
        assert(false);  // Nu ar trebui să ajungă aici
    } catch (const ValidationException& ) {
        assert(true);  // Trebuie prinsă excepția
    }


    service.modificaFilm("Inception", 2010, "SF", 2012, "Matthew McConaughey");

    const std::vector<Film>& filme = service.getFilme();
    assert(filme.size() == 1);
    assert(filme[0].getTitlu() == "Inception");
    assert(filme[0].getAn() == 2012);
    assert(filme[0].getActor() == "Matthew McConaughey");

    try {
        service.modificaFilm("NonExistent Film", 2020, "Drama", 2021, "Unknown Actor");
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Filmul nu exista!");
    }

    try {
        service.modificaFilm("Inception", 2012, "", 2022, "Matthew McConaughey");  // Gen invalid
        assert(false);  // Nu ar trebui să ajungă aici
    } catch (const ValidationException& ) {
        assert(true);  // Trebuie prinsă excepția
    }

}

void Teste::testValidator() {
    try {
        Validator::validateTitlu("");
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Titlul nu poate fi gol!");
    }

    try {
        Validator::validateAn(1899);
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Anul trebuie sa fie intre 1900 si 2100!");
    }

    try {
        Validator::validateActor("");
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Actorul principal nu poate fi gol!");
    }

    try {
        Validator::validateGen("");
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Genul nu poate fi gol!");
    }

}


void Teste::testCautare() {
    Repo repo;
    Service service{ repo };

    service.adaugaFilm("Inception", "SF", 2010, "Leonardo DiCaprio");
    service.adaugaFilm("Interstellar", "SF", 2014, "Matthew McConaughey");
    service.adaugaFilm("The Dark Knight", "Action", 2008, "Christian Bale");

    auto rezultateTitlu = service.cautaFilme("Inception");
    assert(rezultateTitlu.size() == 1);
    assert(rezultateTitlu[0].getTitlu() == "Inception");

    auto rezultateGen = service.cautaFilme("", "SF");
    assert(rezultateGen.size() == 2);

    auto rezultateAn = service.cautaFilme("", "", 2014);
    assert(rezultateAn.size() == 1);
    assert(rezultateAn[0].getAn() == 2014);

    auto rezultateTitluAn = service.cautaFilme("Inception", "", 2010);
    assert(rezultateTitluAn.size() == 1);
    assert(rezultateTitluAn[0].getTitlu() == "Inception");

}

void Teste::testFiltrare() {
    Repo repo;
    Service service{ repo };

    service.adaugaFilm("Inception", "SF", 2010, "Leonardo DiCaprio");
    service.adaugaFilm("Interstellar", "SF", 2014, "Matthew McConaughey");
    service.adaugaFilm("The Dark Knight", "Acțiune", 2008, "Christian Bale");

    auto rezultateTitlu = service.filtrareFilme("Inception", -1);
    assert(rezultateTitlu.size() == 1);
    assert(rezultateTitlu[0].getTitlu() == "Inception");

    auto rezultateAn = service.filtrareFilme("", 2014);
    assert(rezultateAn.size() == 1);
    assert(rezultateAn[0].getAn() == 2014);

    auto rezultateTitluAn = service.filtrareFilme("Inception", 2010);
    assert(rezultateTitluAn.size() == 1);
    assert(rezultateTitluAn[0].getTitlu() == "Inception" && rezultateTitluAn[0].getAn() == 2010);

    auto rezultateInexistente = service.filtrareFilme("Avatar", 2009);
    assert(rezultateInexistente.empty());
}

void Teste::testMyListAdd() {
    MyList<int> list;
    assert(list.size() == 0);  // Lista ar trebui să fie goală la început

    list.add(10);
    assert(list.size() == 1);  // După adăugare, lista ar trebui să conțină un element
    assert(list[0] == 10);     // Elementul adăugat ar trebui să fie 10

    list.add(20);
    assert(list.size() == 2);  // Lista ar trebui să conțină acum 2 elemente
    assert(list[1] == 20);     // Al doilea element ar trebui să fie 20
}

void Teste::testMyListRemove() {
    MyList<int> list;
    list.add(10);
    list.add(20);
    list.add(30);

    list.remove(1);  // Eliminăm elementul de la indexul 1 (20)
    assert(list.size() == 2);  // Lista ar trebui să aibă acum 2 elemente
    assert(list[0] == 10);     // Primul element ar trebui să fie 10
    assert(list[1] == 30);     // Al doilea element ar trebui să fie 30

    try {
        list.remove(5);  // Încercăm să eliminăm un element la un index invalid
        assert(false);    // Ar trebui să arunce o excepție
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Index invalid");
    }
}

void Teste::testMyListUpdate() {
    MyList<int> list;
    list.add(10);
    list.add(20);

    list.update(1, 25);  // Modificăm elementul de la indexul 1
    assert(list[1] == 25);  // Elementul la indexul 1 ar trebui să fie acum 25

    try {
        list.update(5, 30);  // Încercăm să actualizăm un element la un index invalid
        assert(false);        // Ar trebui să arunce o excepție
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Index invalid");
    }
}

void Teste::testMyListOperatorIndex() {
    MyList<int> list;
    list.add(10);
    list.add(20);
    list.add(30);

    // Testează accesul la un index valid
    assert(list[0] == 10);
    assert(list[1] == 20);
    assert(list[2] == 30);

    try {
        // Acces invalid (index 3, dar lista are doar 3 elemente)
        list[3];  // Va arunca o excepție std::out_of_range
        assert(false);  // Dacă ajungi aici, testul a eșuat
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Index invalid");
    }

    // Testează și pentru un obiect const
    const MyList<int> constList = list;

    assert(constList[0] == 10);
    try {
        constList[3];  // Va arunca o excepție std::out_of_range
        assert(false);  // Dacă ajungi aici, testul a eșuat
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Index invalid");
    }
}

void Teste::testMyListCapacity() {
    MyList<int> list(2);  // Setăm capacitatea inițială la 2
    assert(list.size() == 0);

    list.add(10);
    list.add(20);
    assert(list.size() == 2);

    list.add(30);  // Acum lista trebuie să își mărească capacitatea
    assert(list.size() == 3);  // Lista ar trebui să conțină 3 elemente
    assert(list[2] == 30);     // Ultimul element adăugat ar trebui să fie 30
}

void Teste::testMyListCopyConstructor() {
    MyList<int> list;
    list.add(10);
    list.add(20);
    list.add(30);

    // Copiem lista într-o nouă listă
    MyList<int> copiedList = list;

    // Verificăm dacă dimensiunile și elementele sunt aceleași
    assert(copiedList.size() == list.size());
    assert(copiedList[0] == list[0]);
    assert(copiedList[1] == list[1]);
    assert(copiedList[2] == list[2]);

    // Modificăm elementele în lista originală
    list.update(0, 100);

    // Verificăm că lista copiată nu a fost afectată
    assert(copiedList[0] == 10);  // Lista copiată ar trebui să rămână nemodificată
    assert(list[0] == 100);       // Lista originală ar trebui să aibă valoarea modificată
}

void Teste::testConstructorCopiere() {
    // Redirecționăm ieșirea standard pentru a captura mesajul din constructor
    std::stringstream buffer;
    std::streambuf* prev = std::cout.rdbuf(buffer.rdbuf()); // redirecționează std::cout în buffer

    Film f1("Inception", "SF", 2010, "Leonardo DiCaprio");
    Film f2 = f1;  // Apelul constructorului de copiere

    // Verificăm dacă obiectul copiat conține aceleași date
    assert(f2.getTitlu() == "Inception");
    assert(f2.getGen() == "SF");
    assert(f2.getAn() == 2010);
    assert(f2.getActor() == "Leonardo DiCaprio");

    // Verificăm mesajul care a fost afișat
    std::string output = buffer.str();
    assert(output.find("Constructor de copiere apelat. Copiem filmul: Inception, SF, 2010, Leonardo DiCaprio") != std::string::npos);

    std::cout.rdbuf(prev);
}

void Teste::testOperatorAtribuire() {
    MyList<int> l1;
    l1.add(10);
    l1.add(20);
    l1.add(30);

    MyList<int> l2;
    l2 = l1; // folosim operatorul de atribuire

    // verificăm că elementele au fost copiate corect
    assert(l2.size() == 3);
    assert(l2[0] == 10);
    assert(l2[1] == 20);
    assert(l2[2] == 30);

    // modificăm l2 și ne asigurăm că l1 nu e afectat
    l2[0] = 99;
    assert(l1[0] == 10); // l1 rămâne neschimbat
    assert(l2[0] == 99); // doar l2 s-a schimbat
}

void Teste::testMyListIterators() {
    MyList<int> lista;
    lista.add(1);
    lista.add(2);
    lista.add(3);

    int suma = 0;
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        suma += *it;
    }

    assert(suma == 6);  // 1 + 2 + 3
}

void Teste::testSortariFilme() {
    Repo repo;
    Service service{repo};

    Film f1{"Film Z", "Drama", 2010, "Actor B"};
    Film f2{"Film A", "Actiune", 2005, "Actor C"};
    Film f3{"Film M", "Comedie", 2005, "Actor A"};
    Film f4{"Film B", "Actiune", 2015, "Actor D"};

    service.adaugaFilm("Film Z", "Drama", 2010, "Actor B");
    service.adaugaFilm("Film A", "Actiune", 2005, "Actor C");
    service.adaugaFilm("Film M", "Comedie", 2005, "Actor A");
    service.adaugaFilm("Film B", "Actiune", 2015, "Actor D");

    // Sortare dupa an si gen
    service.sortareFilmeDupaAnSiGen();
    auto sortedAnGen = service.getFilme();

    assert(sortedAnGen[0] == f2); // 2005, Actiune
    assert(sortedAnGen[1] == f3); // 2005, Comedie
    assert(sortedAnGen[2] == f1); // 2010, Drama
    assert(sortedAnGen[3] == f4); // 2015, Actiune

    // Sortare dupa titlu
    service.sortareFilmeDupaTitlu();
    auto sortedTitlu = service.getFilme();
    assert(sortedTitlu[0] == f2); // "Film A"
    assert(sortedTitlu[1] == f4); // "Film B"
    assert(sortedTitlu[2] == f3); // "Film M"
    assert(sortedTitlu[3] == f1); // "Film Z"

    // Sortare dupa actor
    service.sortareFilmeDupaActor();
    auto sortedActor = service.getFilme();
    assert(sortedActor[0] == f3); // "Actor A"
    assert(sortedActor[1] == f1); // "Actor B"
    assert(sortedActor[2] == f2); // "Actor C"
    assert(sortedActor[3] == f4); // "Actor D"
}

void Teste::test_move_constructor() {
    MyList<int> list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);

    // Move constructor
    MyList<int> list2(std::move(list1));

    assert(list2.size() == 3);
    assert(list2[0] == 1);
    assert(list2[1] == 2);
    assert(list2[2] == 3);

    // După mutare, list1 ar trebui să fie într-o stare validă dar "goală"
    assert(list1.size() == 0);
}

void Teste::test_move_assignment() {
    MyList<int> list1;
    list1.add(10);
    list1.add(20);

    MyList<int> list2;
    list2.add(99);

    list2 = std::move(list1);  // Move assignment

    assert(list2.size() == 2);
    assert(list2[0] == 10);
    assert(list2[1] == 20);

    assert(list1.size() == 0);
}






void testCosFilme() {
    CosFilm cos;

    // Test adaugaCosFilme
    Film f1{"Titanic", "Drama", 1997, "Leonardo DiCaprio"};
    cos.adaugaCosFilme(f1);
    assert(cos.getCosFilme().size() == 1);
    assert(cos.getCosFilme()[0].getTitlu() == "Titanic");

    // Test golesteCosFilme
    cos.golesteCosFilme();
    assert(cos.getCosFilme().empty());

    // Test umpleRandomCosFilme
    std::vector<Film> listaFilme = {
        {"Inception", "Actiune", 2010, "Leonardo DiCaprio"},
        {"Interstellar", "SF", 2014, "Matthew McConaughey"},
        {"The Revenant", "Drama", 2015, "Leonardo DiCaprio"}
    };
    cos.umpleRandomCosFilme(2, listaFilme);
    assert(cos.getCosFilme().size() == 2);
    cos.umpleRandomCosFilme(5, listaFilme);  // lista are 3 filme, cerem 5 => trebuie refolosită
    assert(cos.getCosFilme().size() == 5);



    // Test exportCSV
    std::string numeFisier = "test_cos.csv";
    cos.exportCSV(numeFisier);

    std::ifstream in(numeFisier);
    assert(in.is_open());
    std::string linie;
    int count = 0;
    while (std::getline(in, linie)) {
        assert(!linie.empty());
        count++;
    }
    in.close();
    assert(count == 5);

    // Curăță fișierul după test (opțional)
    std::remove(numeFisier.c_str());
}

void testCosInchirieriService() {
    // Instanțierea obiectelor necesare
    Repo repo;
    Validator val;
    CosFilm cos;
    Service srv{repo, val, cos};

    // Adăugare filme în repo
    srv.adaugaFilm("Matrix", "SF", 1999, "Keanu Reeves");
    srv.adaugaFilm("Avatar", "SF", 2009, "Sam Worthington");
    srv.adaugaFilm("Inception", "Actiune", 2010, "DiCaprio");

    // Test adăugare în coș
    auto& cos1 = srv.adaugaFilmInCosInchirieri("Matrix");
    assert(cos1.size() == 1);
    assert(cos1[0].getTitlu() == "Matrix");

    // Test că nu se adaugă de două ori același film
    auto& cos2 = srv.adaugaFilmInCosInchirieri("Matrix");
    assert(cos2.size() == 1);  // Tot 1

    // Test excepție când filmul nu există
    try {
        srv.adaugaFilmInCosInchirieri("NuExista");
        assert(false);  // Nu trebuie să ajungă aici
    } catch (const RepositoryException&) {
        assert(true);  // Filmul nu există, excepție corectă
    }

    // Test umplere aleatoare
    auto& cos3 = srv.umpleRandomCosInchirieri(5);
    assert(cos3.size() == 5);  // Coșul trebuie să aibă 5 filme

    // Test getAll
    const auto& toate = srv.getAllCosInchirieri();
    assert(toate.size() == 5);  // Ar trebui să fie 5 filme în coș

    // Test golire
    const auto& golit = srv.golesteCosInchirieri();
    assert(golit.empty());  // Coșul ar trebui să fie gol

    // Test export CSV
    srv.adaugaFilmInCosInchirieri("Avatar");
    std::string fisier = "export_cos_test.csv";
    srv.exportaCosCSV(fisier);

    // Verificare că fișierul a fost creat și conținutul său
    std::ifstream in(fisier);
    assert(in.is_open());
    std::string linie;
    int count = 0;
    while (std::getline(in, linie)) {
        count++;
    }
    in.close();
    assert(count == 1);  // Trebuie să fie 1 film în fișier

    // Ștergem fișierul de test
    std::remove(fisier.c_str());
}

void test_readAllFromFile() {
    // Crează un fișier de test cu date valide
    std::ofstream fout("test_filmee.txt");
    fout << "Titanic,Romance,1997,Leonardo DiCaprio\n";
    fout << "Avatar,Sci-Fi,2009,Sam Worthington\n";
    fout.close();

    RepoFile repo_file{"test_filmee.txt"};

    // Verifică dacă fișierul este citit corect
    const auto& filme = repo_file.getAll();
    assert(filme.size() == 2);  // Verifică dacă sunt două filme

    // Verifică dacă datele sunt corecte
    assert(filme[0].getTitlu() == "Titanic");
    assert(filme[0].getGen() == "Romance");
    assert(filme[0].getAn() == 1997);
    assert(filme[0].getActor() == "Leonardo DiCaprio");

    assert(filme[1].getTitlu() == "Avatar");
    assert(filme[1].getGen() == "Sci-Fi");
    assert(filme[1].getAn() == 2009);
    assert(filme[1].getActor() == "Sam Worthington");


}

void test_writeAllToFile() {
    // Creează fișierul test_filmee_output.txt și adaugă filme
    RepoFile repo_file{"test_filmee_output.txt"};
    Film film1{"The Matri", "Sci", 2025, "Reeves"};
    Film film2{"Inceptio", "Sci-Fi", 2030, "Leonardo DiCaprio"};

    // Adaugă filmele
     repo_file.adauga(film1);
     //repo_file.adauga(film2);
    repo_file.modifica("The Matri",2025,"ana",2024,"a");
    // Scrie filmele în fișier
    repo_file.writeAllToFile();

    // Citește fișierul și verifică datele
    std::ifstream fin("test_filmee_output.txt");
    std::string linie;

    std::getline(fin, linie);

    std::getline(fin, linie);

    fin.close();
    repo_file.sterge("The Matri",2024);


}

void testUndo() {
    Repo repo;
    Service service(repo);

    // Adăugăm un film
    service.adaugaFilm("Titanic", "Drama", 1997, "Leonardo DiCaprio");

    service.undo();

    // Adăugăm un alt film
    service.adaugaFilm("Inception", "Sci-Fi", 2010, "Leonardo DiCaprio");

    service.modificaFilm("Inception", 2010, "Sci-Fi", 2012, "Leonardo DiCaprio");
    assert(repo.cauta("Inception", 2012).getAn() == 2012);  // Verificăm că filmul a fost modificat

    service.undo();
    assert(repo.cauta("Inception", 2010).getAn() == 2010);  // Verificăm că filmul a revenit la anul original

    service.stergeFilm("Inception", 2010);

    service.undo();
    try {
        service.undo();
        service.undo();
        service.undo();
        service.undo();
        assert(false);
    }catch (std::exception& e) {
        assert(std::string(e.what()) == "Nu exista operatii pentru a fi facute undo.");
    }

}

void testSetteriFilm() {
    Film f{ "Matrix", "SF", 1999, "Keanu Reeves" };

    f.setGen("Actiune");
    assert(f.getGen() == "Actiune");

    f.setAn(2000);
    assert(f.getAn() == 2000);

    f.setActor("Laurence Fishburne");
    assert(f.getActor() == "Laurence Fishburne");
}

void testRepoNouFaraExceptii() {
    RepoNou repo(0.0f); // Probabilitate 0 => nu se aruncă excepții

    Film f1("Matrix", "SF", 1999, "Keanu Reeves");
    Film f2("Titanic", "Drama", 1997, "Leonardo DiCaprio");

    repo.adauga(f1);
    repo.adauga(f2);

    assert(repo.getAll().size() == 2);
    assert(repo.cauta("Matrix", 1999).getActor() == "Keanu Reeves");

    repo.modifica("Matrix", 1999, "Actiune", 2000, "Laurence Fishburne");
    assert(repo.cauta("Matrix", 2000).getGen() == "Actiune");

    repo.sterge("Titanic", 1997);
    assert(repo.getAll().size() == 1);
}

void testRepoNouCuExceptii() {
    RepoNou repo(1.0f); // Probabilitate 1 => întotdeauna se aruncă excepții

    Film f("Inception", "SF", 2010, "Leonardo DiCaprio");

    try {
        repo.adauga(f);
        assert(false); // Nu ar trebui să ajungă aici
    } catch (const RepositoryException& e) {
        assert(true);  // Excepția a fost aruncată
    }

    try {
        repo.modifica("Inception", 2010, "Thriller", 2011, "Tom Hardy");
        assert(false);
    } catch (const RepositoryException&) {
        assert(true);
    }

    try {
        repo.sterge("Inception", 2010);
        assert(false);
    } catch (const RepositoryException&) {
        assert(true);
    }
}

void testSet(){
    RepoNou repo(0.0f);

    std::vector<Film> filmeNoi = {
        Film("Matrix", "SF", 1999, "Keanu Reeves"),
        Film("Inception", "SF", 2010, "Leonardo DiCaprio")
    };

    try {
        repo.setAll(filmeNoi);
        assert(true);
    } catch (const RepositoryException& e) {
        assert(false);
    }
}

void testconstr(){
    try {
        RepoNou repo(-0.5f); // Probabilitatea este mai mică decât 0 => trebuie să fie aruncată o excepție
        assert(false); // Nu ar trebui să ajungem aici
    } catch (const std::invalid_argument& e) {
        // Excepția a fost aruncată corect, validăm mesajul
        assert(true);
        assert(std::string(e.what()) == "Probabilitatea trebuie sa fie intre 0 si 1.");
    }
}

void Teste::ruleazaTeste() {
    testFilm();
    testRepo();
    testService();
    testRepoModifica();
    testServiceModificaFilm();
    testValidator();
    testCautare();
    testFiltrare();
    testMyListAdd();
    testMyListRemove();
    testMyListUpdate();
    testMyListOperatorIndex();
    testMyListCapacity();
    testMyListCopyConstructor();
    testConstructorCopiere();
    testOperatorAtribuire();
    testMyListIterators();
    testSortariFilme();
    test_move_assignment();
    test_move_constructor();
    testCosFilme();
    testCosInchirieriService();
    test_readAllFromFile();
    test_writeAllToFile();
    testUndo();
    testSetteriFilm();
    testRepoNouFaraExceptii();
    testRepoNouCuExceptii();
    testSet();
    testconstr();

    std::cout << "Toate testele au trecut!\n";
}
