#include "db.h"
#include <fstream>
#include <sstream>

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



Patient createPatient(Patient pt) {
    int id = bumpId("Patient");
    pt.id = id;

    std::string r = std::to_string(pt.id) + "|" + pt.name;
    writeResource("Patient", pt.id, r);
    return pt;
}

Patient readPatient(int id) {
    Patient pt;
    std::vector<std::string> vals = readResource("Patient", id);

    pt.id = std::stoi(vals[0]);
    pt.name = vals[1];
    return pt;
}

Appointment createAppointment(Appointment app) {
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

Provider createProvider(Provider pr) {
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
