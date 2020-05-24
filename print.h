#include "resources.h"
#include <vector>
#include <iostream>

void print(Patient pt);

void print(Appointment app);

void print(Insurer in);

void print(Coverage cov);



template <class Resource>
void print(Resource resource);

void print(std::vector<Patient> r);

void print(std::vector<Appointment> r);

void print(std::vector<Insurer> r);

void print(std::vector<Coverage> r);
