#include "db.h"
#include <fstream>
#include <sstream>

bool contains(std::vector<std::string> seq, std::string s) {
    bool checkResult = false;
    for (std::string el : seq) {
        if (el == s) {checkResult = true;}
    }
    return checkResult;
}

void truncateDb () {
    system("exec rm -r db/");

    system("exec mkdir db/");

    system("exec mkdir db/Patient/");
    system("exec mkdir db/Provider/");
    system("exec mkdir db/Appointment/");
    system("exec mkdir db/Insurer/");
    system("exec mkdir db/Coverage/");
    system("exec mkdir db/Encounter/");

    fileWrite("db/Patient/last_id", "0");
    fileWrite("db/Provider/last_id", "0");
    fileWrite("db/Appointment/last_id", "0");
    fileWrite("db/Insurer/last_id", "0");
    fileWrite("db/Coverage/last_id", "0");
    fileWrite("db/Encounter/last_id", "0");
}

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

std::vector<std::string> splitStr(std::string str, char delim)
{
    std::vector<std::string> splited;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delim)) {
        splited.push_back(token);
    }
    return splited;
}

int bumpId(std::string resourceType) {
    std::string path = "db/" + resourceType + "/last_id";
    int lastId = std::stoi(fileRead(path));
    int newId = lastId + 1;

    fileWrite(path, std::to_string(newId));
    return newId;
}

std::vector<std::string> readResource(std::string resourceType, int id) {
    std::string path = "db/" + resourceType + "/" + std::to_string(id);
    return splitStr(fileRead(path), '|');
}

void writeResource (std::string resourceType, int id, std::string value) {
    std::string path = "db/" + resourceType + "/" + std::to_string(id);
    fileWrite(path, value);
}



Patient create(Patient pt) {
    int id = bumpId("Patient");
    pt.id = id;

    std::string r = std::to_string(pt.id) + "|" + pt.name;
    writeResource("Patient", pt.id, r);
    return pt;
}

Patient readPatient(int id) {
    std::vector<std::string> ids = splitStr(fileRead("db/Patient/deleted"), '|');

    Patient pt;
    if (contains(ids, std::to_string(id))) {
        pt.id = 0;
    }
    else {
        std::vector<std::string> vals = readResource("Patient", id);

        pt.id = std::stoi(vals[0]);
        pt.name = vals[1];
    }

    return pt;
}

void deletePatient(int id) {
    std::string ids = fileRead("db/Patient/deleted");
    fileWrite("db/Patient/deleted", ids + "|" + std::to_string(id));
}

std::vector<Patient> readPatients() {
    std::vector<Patient> patients;
    Patient buff;

    int lastId = std::stoi(fileRead("db/Patient/last_id"));
    if (lastId > 0) {
        for (int id = 1; id <= lastId; id++) {
            buff = readPatient(id);
            if (buff.id != 0) {
                patients.push_back(buff);
            }
        }
    }
    return patients;
}



Appointment create(Appointment app) {
    int id = bumpId("Appointment");
    app.id = id;

    std::string r = std::to_string(app.id) + "|" + app.date + "|" + std::to_string(app.patientId);
    writeResource("Appointment", app.id, r);
    return app;
}

Appointment readAppointment(int id) {
    Appointment app;
    std::vector<std::string> vals = readResource("Appointment", id);

    app.id = std::stoi(vals[0]);
    app.date = vals[1];
    app.patientId = std::stoi(vals[2]);
    return app;
}

std::vector<Appointment> readAppointments() {
    std::vector<Appointment> apps;
    int lastId = std::stoi(fileRead("db/Appointment/last_id"));
    if (lastId > 0) {
        for (int id = 1; id <= lastId; id++) {
            apps.push_back(readAppointment(id));
        }
    }
    return apps;
}


  
Provider create(Provider pr) {
    int id = bumpId("Provider");
    pr.id = id;

    std::string r = std::to_string(pr.id) + "|" + pr.name;
    writeResource("Provider" , pr.id, r);
    return pr;
}

Provider readProvider(int id) {
    Provider pr;
    std::vector<std::string> vals = readResource("Provider", id);

    pr.id = std::stoi(vals[0]);
    pr.name = vals[1];
    return pr;
}



Insurer create(Insurer in) {
    int id = bumpId("Insurer");
    in.id = id;

    std::string r = std::to_string(in.id) + "|" + in.name;
    writeResource("Insurer" , in.id, r);
    return in;
}

Insurer readInsurer(int id) {
    Insurer in;
    std::vector<std::string> vals = readResource("Insurer", id);

    in.id = std::stoi(vals[0]);
    in.name = vals[1];
    return in;
}

std::vector<Insurer> readInsurers() {
    std::vector<Insurer> ins;
    int lastId = std::stoi(fileRead("db/Insurer/last_id"));
    if (lastId > 0) {
        for (int id = 1; id <= lastId; id++) {
            ins.push_back(readInsurer(id));
        }
    }
    return ins;
}

Insurer findInsurerByName(std::string name) {
    Insurer found = {.id = 0, .name = "Not found"};

    for (Insurer ins : readInsurers()) {
        if (ins.name == name) {
            found = ins;
        }
    }
    return found;
}


Coverage create(Coverage cov) {
    int id = bumpId("Coverage");
    cov.id = id;

    std::string r = std::to_string(cov.id) + "|"
        + cov.memberId + "|"
        + std::to_string(cov.patientId) + "|"
        + std::to_string(cov.insurerId);

    writeResource("Coverage" , cov.id, r);
    return cov;
}

Coverage readCoverage(int id) {
    Coverage cov;
    std::vector<std::string> vals = readResource("Coverage", id);

    cov.id = std::stoi(vals[0]);
    cov.memberId = vals[1];
    cov.patientId = std::stoi(vals[2]);
    cov.insurerId = std::stoi(vals[3]);
    return cov;
}

std::vector<Coverage> readCoverages() {
    std::vector<Coverage> covs;
    int lastId = std::stoi(fileRead("db/Coverage/last_id"));
    if (lastId > 0) {
        for (int id = 1; id <= lastId; id++) {
            covs.push_back(readCoverage(id));
        }
    }
    return covs;
}




void insertPatients() { // Setup a few patients
    std::vector<std::string> names = {"Mary", "Ann", "John", "Ahmet"};
    for (std::string name : names) {
        Patient pt = {.name = name};
        create(pt);
    }
}

void insertInsurers() { // Setup a few insurers
    std::vector<std::string> names = {"aetna", "medicare", "fidelis"};
    for (std::string name : names) {
        Insurer ins = {.name = name};
        create(ins);
    }
}
