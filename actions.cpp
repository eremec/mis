#include "db.h"
#include "print.h"
#include "actions.h"

#include <iostream>
#include <functional>
#include <tuple>

std::vector<std::tuple<std::string, std::function<void()>>> actionMapping;

void mapByName (std::string name) {
    std::function<void()> match;
    for (std::tuple<std::string, std::function<void()>> m : actionMapping) {
        if (std::get<0>(m) == name) {
            match = std::get<1>(m);
        }
    }
    match();
}

void delimit() {
    std::cout << "---------------------------" << std::endl;
}

void handleNextInput(std::vector<std::string> outcomes) {
    delimit();
    for (int idx = 0; idx < outcomes.size(); idx++) {
        std::cout << std::to_string(idx) + ": " + outcomes[idx] << std::endl;
    }
    delimit();

    int nextAction;
    std::cin >> nextAction;
    mapByName(outcomes[nextAction]);
}

bool confirm(std::string message) {
    std::string answer;
    while ((answer != "n") && (answer != "y")) {
            std::cout << message + " (y/n)" << std::endl;
            std::cin >> answer;
        }
    return (answer == "y");
}




void greetAction() {
    std::vector<std::string> outcomes =
        {"greet", "print", "create", "admin"};

    handleNextInput(outcomes);
}

void printAction() {
    std::vector<std::string> outcomes =
        {"greet", "print patients", "print appointments"};

    handleNextInput(outcomes);
}

void printPatientsAction() {
    std::vector<std::string> outcomes =
        {"greet", "print"};

    print(readPatients());

    handleNextInput(outcomes);
}

void printAppointmentsAction () {
    std::vector<std::string> outcomes =
        {"greet", "print"};

    print(readAppointments());

    handleNextInput(outcomes);
}

void createAction () {
    std::vector<std::string> outcomes =
        {"greet", "create patient", "create appointment"};

    handleNextInput(outcomes);
}

void createPatientAction () {
    std::vector<std::string> outcomes =
        {"greet", "print", "print patients"};

    Patient pt;
    std::cout << "Enter patient name: " << std::endl;
    std::cin >> pt.name;

    if (confirm("Save patient? ")) {
        create(pt);
        std::cout << "Patient saved" << std::endl;
    };

    handleNextInput(outcomes);
}

void adminAction() {
    std::vector<std::string> outcomes =
        {"greet", "insert defaults", "truncate"};

    handleNextInput(outcomes);
}

void insertDefaultsAction() {
    std::vector<std::string> outcomes =
        {"greet"};
    insertPatients();

    handleNextInput(outcomes);
}

void truncateAction() {
    std::vector<std::string> outcomes =
        {"greet"};
    truncateDb();

    handleNextInput(outcomes);
}

void initMapping() {
    actionMapping = {
        std::make_tuple("greet",              greetAction),
        std::make_tuple("print",              printAction),
        std::make_tuple("print patients",     printPatientsAction),
        std::make_tuple("print appointments", printAppointmentsAction),
        std::make_tuple("create",             createAction),
        std::make_tuple("create patient",     createPatientAction),
        std::make_tuple("admin",              adminAction),
        std::make_tuple("insert defaults",    insertDefaultsAction),
        std::make_tuple("truncate",          truncateAction)};
}

void inputLoop() {
    initMapping();
    mapByName("greet");
}
