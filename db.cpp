#include "db.h"
#include <fstream>
#include <sstream>

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
    Appointment r;
    std::vector<std::string> vals = readResource("Appointment", id);

    r.id = std::stoi(vals[0]);
    r.date = vals[1];
    r.patientId = std::stoi(vals[2]);
    return r;
}
