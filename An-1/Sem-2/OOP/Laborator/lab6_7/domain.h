

#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>

class Film {
private:
    std::string titlu, gen, actor_principal;
    int an;
public:
    Film() : titlu(""), gen(""), an(0), actor_principal("") {}
    Film(const std::string& titlu, const std::string& gen, int an, const std::string& actor);
    Film(const Film& other);

    const std::string& getTitlu() const;
    void setGen(const std::string& nouGen) { gen = nouGen; }
    const std::string& getGen() const;
    void setAn(const int nouAn) { an = nouAn; }
    int getAn() const;
    void setActor(const std::string& nouActor) { actor_principal = nouActor; }
    const std::string& getActor() const;

    bool operator==(const Film& other) const;
    virtual ~Film() = default;
};









#endif //DOMAIN_H
