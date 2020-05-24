#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

struct Patient {
    int id;
    std::string name;
};

struct Provider {
    int id;
    std::string name;
};

struct Appointment {
    int id;
    std::string date;
    int patientId;
};

struct Insurer {
    int id;
    std::string name;
};

struct Coverage {
    int id;
    std::string memberId;
    int patientId;
    int insurerId;
};

struct Encounter {
    int id;
    std::string date;
    int patientId;
    int providerId;
    int coverageId;
};

#endif
