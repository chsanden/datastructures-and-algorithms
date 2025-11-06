#include "TPerson.h"

#include <utility>
#include "Utils.h"


TPerson::TPerson() : firstName("N/A"),lastName("N/A"), status(GUEST), cabinSize(Utils::RandomInt(1, 4)) {}

TPerson::TPerson(std::string f, std::string l, const ENumStatus s) : firstName(std::move(f)), lastName(std::move(l)), status(s), cabinSize(Utils::RandomInt(1, 4)) {}


