#include "db.h"
#include "eligibility_check.h"
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

void checkInNewPatient() {
    //Patient came without appointment for the first time
    truncateDb();

    //TODO insertProviders();
    // Write function which inserts providers for our clinic
   
    insertPatients();
    insertInsurers();

    //Create new patient
    Patient newPt = create(Patient({.name = "Mary"}));

    //Find his insurance company
    Insurer ins = findInsurerByName("fidelis");

    //Check if it exists in our database
    bool s1 = (ins.name == "fidelis");

    //Enter patient coverage to our database
    Coverage ptCoverage =
        create(Coverage({.memberId  = "464TLA",
                         .patientId = newPt.id,
                         .insurerId = ins.id}));

    // Check if coverage is active
    bool s2 = eligibilityCheck(ptCoverage.id);

    // TODO Create encounter for our patient
    // надо добавить функции на Create, Read и Print для визита (Encounter)

    if (s1 and s2) {
        std::cout <<  "checkInNewPatient: ok" << std::endl;
    }
    else {
        std::cout <<  "checkInNewPatient: failed" << std::endl;
    }
}

void checkInExistingPatient() {
    // TODO add scenario when patient came for the second time
    // and already has a coverage. Coverage is inactive
    //
    // TODO Надо добавить функцию поиска пациента по имени, как findInsurerByName
    // TODO Надо добавить функцию поиска страховки по ID пациента
}

int main() {
    createReadPatient();
    createReadProvider();
    checkInNewPatient();
    checkInExistingPatient();
}
