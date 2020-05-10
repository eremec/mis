#include "db.h"
#include "print.h"
#include "actions.h"

#include <iostream>
#include <functional>
#include <tuple>

std::vector<std::tuple<int, std::string>> actionMapping =
{
std::make_tuple(0, "greet"),
std::make_tuple(1, "print"),
std::make_tuple(2, "print patients"),
std::make_tuple(3, "print appointments"),
std::make_tuple(4, "create"),
std::make_tuple(5, "create patient"),
std::make_tuple(6, "admin"),
std::make_tuple(7, "insert defaults"),
std::make_tuple(8, "truncate")
};

int mapByName (std::string name) {
    int match = -1;
    for (std::tuple<int, std::string> m : actionMapping) {
        if (std::get<1>(m) == name) {
            match = std::get<0>(m);
        }
    }
    return match;
}

void delimit() {
    std::cout << "---------------------------" << std::endl;
}

int handleNextInput(std::vector<std::string> outcomes) {
    delimit();
    for (int idx = 0; idx < outcomes.size(); idx++) {
        std::cout << std::to_string(idx) + ": " + outcomes[idx] << std::endl;
    }
    delimit();

    int nextAction;
    std::cin >> nextAction;
    return mapByName(outcomes[nextAction]);
}

bool confirm(std::string message) {
    std::string answer;
    while ((answer != "n") && (answer != "y")) {
            std::cout << message + " (y/n)" << std::endl;
            std::cin >> answer;
        }
    return (answer == "y");
}




int greetAction() {
    std::vector<std::string> outcomes =
        {"greet", "print", "create", "admin"};

    return handleNextInput(outcomes);
}

int printAction() {
    std::vector<std::string> outcomes =
        {"greet", "print patients", "print appointments"};

    return handleNextInput(outcomes);
}

int printPatientsAction() {
    std::vector<std::string> outcomes =
        {"greet", "print"};

    print(readPatients());

    return handleNextInput(outcomes);
}

int printAppointmentsAction () {
    std::vector<std::string> outcomes =
        {"greet", "print"};

    print(readAppointments());

    return handleNextInput(outcomes);
}

int createAction () {
    std::vector<std::string> outcomes =
        {"greet", "create patient", "create appointment"};

    return handleNextInput(outcomes);
}

int createPatientAction () {
    std::vector<std::string> outcomes =
        {"greet", "print", "print patients"};

    Patient pt;
    std::cout << "Enter patient name: " << std::endl;
    std::cin >> pt.name;

    if (confirm("Save patient? ")) {
        create(pt);
        std::cout << "Patient saved" << std::endl;
    };

    return handleNextInput(outcomes);
}

int adminAction() {
    std::vector<std::string> outcomes =
        {"greet", "insert defaults", "truncate"};

    return handleNextInput(outcomes);
}

int insertDefaultsAction() {
    std::vector<std::string> outcomes =
        {"greet"};
    insertPatients();

    return handleNextInput(outcomes);
}

int truncateAction() {
    std::vector<std::string> outcomes =
        {"greet"};
    truncateDb();

    return handleNextInput(outcomes);
}

std::vector<std::function<int()>> actions =
{greetAction,
 printAction, printPatientsAction, printAppointmentsAction,
 createAction, createPatientAction,
 adminAction, insertDefaultsAction, truncateAction};

void inputLoop() {
    int currentAction = 0;
    while (true) {
        currentAction = actions[currentAction]();
    }
}
