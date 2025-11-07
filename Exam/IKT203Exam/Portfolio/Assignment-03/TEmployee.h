#ifndef IKT203_COURSE_ASSIGNMENTS_TEMPLOYEE_H
#define IKT203_COURSE_ASSIGNMENTS_TEMPLOYEE_H
#include <string>
#include <utility>


struct TEmployee {
    std::string firstName;
    std::string lastName;
    int id;

    TEmployee(std::string f, std::string l) : firstName(std::move(f)), lastName(std::move(l)) {};
    ~TEmployee() = default;
};











#endif //IKT203_COURSE_ASSIGNMENTS_TEMPLOYEE_H