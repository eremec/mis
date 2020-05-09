#include "print.h"

std::string delimiter = "-------------------------------";

void print(Patient pt) {
    std::cout << delimiter << std::endl;
    std::cout << "id:   " << pt.id << std::endl;
    std::cout << "name: " << pt.name << std::endl;
}

void print(std::vector<Patient> patients) {
    for (Patient pt : patients) {
        print(pt);
    }
}

void print(Appointment app) {
    std::cout << delimiter << std::endl;
    std::cout << "id:        " << app.id << std::endl;
    std::cout << "date:      " << app.date << std::endl;
    std::cout << "patientId: " << app.patientId << std::endl;
}

void print(std::vector<Appointment> apps) {
    for (Appointment app : apps) {
        print(app);
    }
}
