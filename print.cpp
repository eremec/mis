#include "print.h"

std::string delimiter = "-------------------------------";

void print(Patient pt) {
    std::cout << delimiter << std::endl;
    std::cout << "id:   " << pt.id << std::endl;
    std::cout << "name: " << pt.name << std::endl;
}

void print(Appointment app) {
    std::cout << delimiter << std::endl;
    std::cout << "id:        " << app.id << std::endl;
    std::cout << "date:      " << app.date << std::endl;
    std::cout << "patientId: " << app.patientId << std::endl;
}

void print(Insurer in) {
    std::cout << delimiter << std::endl;
    std::cout << "id:   " << in.id << std::endl;
    std::cout << "name: " << in.name << std::endl;
}

void print(Coverage cov) {
    std::cout << delimiter << std::endl;
    std::cout << "id:   " << cov.id << std::endl;
    std::cout << "memberId: " << cov.memberId << std::endl;
    std::cout << "patientId: " << cov.patientId << std::endl;
    std::cout << "insurerId: " << cov.insurerId << std::endl;
}


template <class Resource>
void print(std::vector<Resource> resources) {
    for (Resource r : resources) {
        print(r);
    }
}

void print(std::vector<Patient> r) {print<Patient>(r);}

void print(std::vector<Appointment> r) {print<Appointment>(r);}

void print(std::vector<Insurer> r) {print<Insurer>(r);}

void print(std::vector<Coverage> r) {print<Coverage>(r);}
