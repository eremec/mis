#include <iostream>
#include <fstream>
#include "resources.h"

void fileWrite (std::string path, std::string v) {
    std::ofstream f;

    f.open(path);
    f << v;
    f.close();
}

std::string fileRead (std::string path) {
    std::ifstream f;
    std::string s;

    f.open(path);
    f >> s;
    f.close();
    return s;
}

Patient createPatient(Patient pt) {
    return pt;
}

int main() {
    Patient pt;
    pt.id = 2;
    pt.name = "Mary";

  // f.open ("db/Patient/" + std::to_string(pt.id));

    std::cout <<  pt.name << std::endl;
    std::cout <<  pt.id << std::endl;
}
