#pragma once
#ifndef Filesystem_hpp
#define Filesystem_hpp
#ifndef Objeccts.hpp
#include "Objects.hpp"
#endif // !Objeccts.hpp
#include <fstream>


int split(std::string text, char sep, std::string arr[], int size);

void writeCircs(std::string filename, std::vector<Circ> vec);

void readinCircs(std::string filename, std::vector<Circ> &vec);



#endif