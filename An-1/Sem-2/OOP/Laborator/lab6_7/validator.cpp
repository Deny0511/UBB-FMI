#include "validator.h"

void Validator::validateTitlu(const std::string& titlu) {
    if (titlu.empty())
        throw ValidationException("Titlul nu poate fi gol!");
}

void Validator::validateGen(const std::string& gen) {
    if (gen.empty())
        throw ValidationException("Genul nu poate fi gol!");
}

void Validator::validateAn(int an) {
    if (an < 1900 || an > 2100)
        throw ValidationException("Anul trebuie sa fie intre 1900 si 2100!");
}

void Validator::validateActor(const std::string& actor) {
    if (actor.empty())
        throw ValidationException("Actorul principal nu poate fi gol!");
}
