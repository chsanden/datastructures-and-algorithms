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
    int cabinSize{};

    TPerson();
    TPerson(std::string , std::string , ENumStatus);
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