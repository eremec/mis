#include "db.h"
#include "print.h"
#include "actions.h"

#include <iostream>
#include <functional>
#include <tuple>

#define actionMap std::tuple<std::string, std::function<void()>>
#define strings std::vector<std::string>

std::vector<actionMap> actionMapping;

void println(std::string s) {
    std::cout << s << std::endl;
}

void mapByName (std::string name) {
    std::function<void()> match;
    for (actionMap m : actionMapping) {
        if (std::get<0>(m) == name) {
            match = std::get<1>(m);
        }
    }
    match();
}

void delimit() {println("---------------------------");}

void handleNextInput(strings outcomes) {
    delimit();
    for (int idx = 0; idx < outcomes.size(); idx++) {
        println(std::to_string(idx) + ": " + outcomes[idx]);
    }
    delimit();

    int nextAction;
    std::cin >> nextAction;
    mapByName(outcomes[nextAction]);
}

bool confirm(std::string message) {
    std::string answer;
    while ((answer != "n") && (answer != "y")) {
            println(message + " (y/n)");
            std::cin >> answer;
        }
    return (answer == "y");
}



strings homeOutcomes = {"print", "create", "admin"};

void greetAction() {
    strings outcomes = homeOutcomes;
    handleNextInput(outcomes);
}

void printAction() {
    strings outcomes = {"home", "print patients", "print appointments"};
    handleNextInput(outcomes);
}

void printPatientsAction() {
    strings outcomes = {"home", "print"};
    print(readPatients());
    handleNextInput(outcomes);
}

void printAppointmentsAction () {
    strings outcomes = {"home", "print"};
    print(readAppointments());
    handleNextInput(outcomes);
}

void createAction () {
    strings outcomes = {"home", "create patient", "create appointment"};
    handleNextInput(outcomes);
}

void createPatientAction () {
    strings outcomes = {"home", "print", "print patients"};

    Patient pt;
    println("Enter patient name: ");
    std::cin >> pt.name;

    if (confirm("Save patient? ")) {
        create(pt);
        println("Patient saved");
    };

    handleNextInput(outcomes);
}

void adminAction() {
    strings outcomes = {"home", "insert defaults", "truncate"};
    handleNextInput(outcomes);
}

void insertDefaultsAction() {
    strings outcomes = homeOutcomes;
    insertPatients();
    handleNextInput(outcomes);
}

void truncateAction() {
    strings outcomes = homeOutcomes;
    truncateDb();
    handleNextInput(outcomes);
}

void initMapping() {
    actionMapping = {
        std::make_tuple("home",               greetAction),
        std::make_tuple("print",              printAction),
        std::make_tuple("print patients",     printPatientsAction),
        std::make_tuple("print appointments", printAppointmentsAction),
        std::make_tuple("create",             createAction),
        std::make_tuple("create patient",     createPatientAction),
        std::make_tuple("admin",              adminAction),
        std::make_tuple("insert defaults",    insertDefaultsAction),
        std::make_tuple("truncate",           truncateAction)};
}

void inputLoop() {
    initMapping();
    mapByName("home");
}
