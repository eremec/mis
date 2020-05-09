#include "db.h"
#include "print.h"
#include <iostream>

void insertPatients() {
    std::vector<std::string> names = {"Mary", "Ann", "John", "Ahmet"};
    for (std::string name : names) {
        Patient pt = {.name = name};
        create(pt);
    }
}

void inputLoop() {

}

int main() {
    truncateDb();
    insertPatients();

    print(readPatients());
}
