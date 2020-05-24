#include "db.h"
#include "print.h"
#include "actions.h"

#include <iostream>
#include <functional>
#include <tuple>

#define strings std::vector<std::string>

void noEffect() {};

struct ActionMap {
    std::string           name;
    strings               outcomes;
    std::function<void()> effect = noEffect;};

std::vector<ActionMap> actionMapping;

void println(std::string s) {
    std::cout << s << std::endl;
}

ActionMap mapByName (std::string name) {
    ActionMap map;
    for (ActionMap m : actionMapping) {
        if (m.name == name) {map = m;}
    }
    return map;
}

void delim() {
    println("");
    println("--------------------------------");
    println("");
}

std::string handleNextInput(std::string name) {
    ActionMap map = mapByName(name);
    map.effect();

    delim();
    for (int idx = 0; idx < map.outcomes.size(); idx++) {
        println(std::to_string(idx) + ": " + map.outcomes[idx]);
    }
    delim();

    int nextAction;
    std::cin >> nextAction;
    return map.outcomes[nextAction];
}

bool confirm(std::string message) {
    std::string answer;
    while ((answer != "n") && (answer != "y")) {
            println(message + " (y/n)");
            std::cin >> answer;
        }
    return (answer == "y");
}


//Effects
void printPatientsEffect() {print(readPatients());}

void printAppointmentsEffect () {print(readAppointments());}

void printInsurersEffect (){print(readInsurers());}

void createPatientEffect () {
    Patient pt;
    println("Enter patient name: ");
    std::cin >> pt.name;

    if (confirm("Save patient? ")) {
        create(pt);
        println("Patient saved");
    };
}

void createAppointmentEffect(){
    Appointment app;
    println("Enter patientId: ");
    std::cin >> app.patientId;

    println("Enter date: ");
    std::cin >> app.date;

    if (confirm("Save appointment? ")) {
        create(app);
        println("appointment saved");
    };
}

void createInsurerEffect(){
    Insurer in;
    println("Enter Insurer name: ");
    std::cin >> in.name;

    if (confirm("Save Insurer? ")) {
        create(in);
        println("Insurer saved");
    };
}

void insertDefaultsEffect() {insertPatients();}

void truncateEffect() {truncateDb();}

void greetEffect() {println("Welcome");}

strings homeOutcomes = {"print", "create", "admin"};


//Init
void initMapping() {
    actionMapping = {

    ActionMap({.name     = "home",
               .outcomes = homeOutcomes,
               .effect   = greetEffect}),

    ActionMap({.name     = "print",
               .outcomes = strings({"home", "print patients", "print appointments", "print insurers"})}),

    ActionMap({.name     = "print patients",
               .outcomes = strings({"home", "print"}),
               .effect   = printPatientsEffect}),

    ActionMap({.name     = "print appointments",
               .outcomes = strings({"home", "print"}),
               .effect   = printAppointmentsEffect}),

    ActionMap({.name     = "print insurers",
               .outcomes = strings({"home", "print"}),
               .effect   = printInsurersEffect}),

    ActionMap({.name     = "create",
               .outcomes = strings({"create patient", "create appointment", "create insurer"})}),

    ActionMap({.name     = "create patient",
               .outcomes = strings({"home", "print", "print patients"}),
               .effect   = createPatientEffect}),
        
    ActionMap({.name     = "create appointment",
               .outcomes = homeOutcomes,
               .effect   = createAppointmentEffect}),

    ActionMap({.name     = "create insurer",
               .outcomes = homeOutcomes,
               .effect   = createInsurerEffect}),

    ActionMap({.name     = "admin",
               .outcomes = strings({"home", "insert defaults", "truncate"})}),

    ActionMap({.name     = "insert defaults",
               .outcomes = homeOutcomes,
               .effect   = insertDefaultsEffect}),

    ActionMap({.name     = "truncate",
               .outcomes = homeOutcomes,
               .effect   = truncateEffect})

    // TODO Добавить Create/Print для Encounter, Coverage
    // Добавить проверку активности страховки (EligibilityCheck)
};
}

void inputLoop() {
    initMapping();
    std::string page = "home";
    while (true) {
       page = handleNextInput(page);
    }
}
