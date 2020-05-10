#include "resources.h"
#include <string>
#include <vector>

void truncateDb ();

void fileWrite (std::string path, std::string v);

std::string fileRead (std::string path);

std::vector<std::string> splitStr(std::string str, char delim);

int bumpId(std::string resourceType);

std::vector<std::string> readResource(std::string resourceType, int id);

void writeResource (std::string resourceType, int id, std::string value);



Patient create(Patient pt);

Patient readPatient(int id);

std::vector<Patient> readPatients();


Appointment create(Appointment app);

Appointment readAppointment(int id);

std::vector<Appointment> readAppointments();

Provider create(Provider pr);

Provider readProvider(int id);

Insurer create(Insurer in);

Insurer readInsurer(int in);

std::vector<Insurer> readInsurers();

void insertPatients();
