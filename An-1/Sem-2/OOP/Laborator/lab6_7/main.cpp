#include "teste.h"
#include "ui.h"
#include "validator.h"
#include "CosFilme.h"
#include "gui.h"
#include <fstream>

#include <QApplication>
#include <QWidget>


int main(int argc,char *argv[]) {



    Teste::ruleazaTeste();

    QApplication app(argc, argv);



    Repo repo;
    RepoNou repo_nou{0};
    RepoFile repo_file{"filme1.txt"};
    Validator validator;
    CosFilm cosInchiriei;
    Service service{ repo_file, validator, cosInchiriei };
    // UI ui{ service };
    // ui.run();
    // return 0;
     GUI gui(service);
     gui.setWindowTitle("Film Management");
     gui.show();

    return app.exec();
}
