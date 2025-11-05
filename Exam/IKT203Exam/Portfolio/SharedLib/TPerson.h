#ifndef IKT203_COURSE_ASSIGNMENTS_TPERSON_H
#define IKT203_COURSE_ASSIGNMENTS_TPERSON_H
#include <string>

#include "Utils.h"

enum ENumStatus {
    GUEST,
    EMPLOYEE
};


struct TPerson {
    std::string firstName;
    std::string lastName;
    ENumStatus status;
    int cabinSize = Utils::RandomInt(1, 4);

    TPerson(std::string f, std::string l, ENumStatus s) : firstName(std::move(f)), lastName(std::move(l)), status(s){}
    ~TPerson() = default;

    bool operator<(const TPerson& other) const
    {
        if (lastName < other.lastName) return true;
        if (lastName > other.lastName) return false;
        // same last name → compare first name
        return firstName < other.firstName;
    }
};


#endif //IKT203_COURSE_ASSIGNMENTS_TPERSON_H