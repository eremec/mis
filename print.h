#include "resources.h"
#include <vector>
#include <iostream>

void print(Patient pt);

void print(std::vector<Patient> patients);

template <class Resource>
void print(Resource resource);

void print(std::vector<Patient> r);

void print(std::vector<Appointment> r);
