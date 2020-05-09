#include "db.h"
#include <iostream>

int main() {
    Patient pt;
    pt.name = "Mary";

    truncateDb();
   // Patient createdPt = createPatient(pt);

    Appointment app;
    app.date = "2020-05-09";
    app.patientId = 1;

   // Appointment createdApp = createAppointment(app);

   // std::cout <<  "Patient id: " << createdPt.id << std::endl;
   // std::cout <<  "Appointment id: " << createdApp.id << std::endl;
}
