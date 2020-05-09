#include "resources.h"
#include <string>
#include <vector>

void fileWrite (std::string path, std::string v);

std::string fileRead (std::string path);

std::vector<std::string> splitStr(std::string str, char delim);

int bumpId(std::string resourceType);

std::vector<std::string> readResource(std::string resourceType, int id);

void writeResource (std::string resourceType, int id, std::string value);



Patient createPatient(Patient pt);

Patient readPatient(int id);


Appointment createAppointment(Appointment app);

Appointment readAppointment(int id);
