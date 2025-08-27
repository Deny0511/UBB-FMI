#include "domain.h"
#include <iostream>

Film::Film(const std::string& titlu, const std::string& gen, int an, const std::string& actor)
    : titlu{ titlu }, gen{ gen }, an{ an }, actor_principal{ actor } {}

Film::Film(const Film& other)
    : titlu{ other.titlu }, gen{ other.gen }, an{ other.an }, actor_principal{ other.actor_principal } {
    std::cout << "Constructor de copiere apelat. Copiem filmul: "
              << other.titlu << ", " << other.gen << ", " << other.an << ", " << other.actor_principal << std::endl;
}


const std::string& Film::getTitlu() const { return titlu; }
const std::string& Film::getGen() const { return gen; }
int Film::getAn() const { return an; }
const std::string& Film::getActor() const { return actor_principal; }

bool Film::operator==(const Film& other) const {
    return titlu == other.titlu && an == other.an;
}


