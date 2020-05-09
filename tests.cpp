#include "db.h"
#include <iostream>

void createReadPatient() {
    truncateDb();
    Patient pt;
    pt.name = "Mary";

    bool s1 = (fileRead("db/Patient/last_id") == "0");

    createPatient(pt);

    bool s2 = (fileRead("db/Patient/last_id") == "1");

    Patient created = readPatient(1);

    bool s3 = created.name == "Mary";

    if (s1 and s2 and s3) {
        std::cout <<  "createReadPatient: ok" << std::endl;
    }
    else {
        std::cout <<  "createReadPatient: failed" << std::endl;
    }
}

int main() {
    createReadPatient();
}
