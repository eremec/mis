#include "db.h"
#include <iostream>

void createReadPatient() {
    truncateDb();
    Patient pt;
    pt.name = "Mary";

    bool s1 = (fileRead("db/Patient/last_id") == "0");

    create(pt);

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

void createReadProvider() {
    truncateDb();
    Provider pr;
    pr.name = "Mark";

    bool s1 = (fileRead("db/Provider/last_id") == "0");

    create(pr);

    bool s2 = (fileRead("db/Provider/last_id") == "1");

    Provider created = readProvider(1);

    bool s3 = created.name == "Mark";

    Provider pr2;
    pr2.name = "Kim";

    bool s4 = (fileRead("db/Provider/last_id") == "1");

    create(pr2);

    bool s5 = (fileRead("db/Provider/last_id") == "2");

    Provider created2 = readProvider(2);

    bool s6 = created2.name == "Kim";


    if (s1 and s2 and s3 and s4 and s5 and s6) {
        std::cout <<  "createReadProvider: ok" << std::endl;
    }
    else {
        std::cout <<  "createReadProvider: failed" << std::endl;
    }
}

int main() {
    createReadPatient();
    createReadProvider();
}
