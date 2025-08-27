
#ifndef VALIDATOR_H
#define VALIDATOR_H



#include <string>
#include <stdexcept>

class ValidationException : public std::runtime_error {
public:
    explicit ValidationException(const std::string& msg)
        : std::runtime_error(msg) {}
};


class Validator {
public:
    static void validateTitlu(const std::string& titlu);
    static void validateGen(const std::string& gen);
    static void validateAn(int an);
    static void validateActor(const std::string& actor);

};

#endif //VALIDATOR_H
