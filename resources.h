struct Ref {
    int id;
    std::string resourceType;
};

struct Date {
    int y;
    int m;
    int d;
};

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
    Date date;
    Ref patient;
};

struct Insurer {
    int id;
    std::string name;
};

struct Coverage {
    int id;
    Ref patient;
    Ref insurer;
};

struct Encounter {
    int id;
    Date date;
    Ref patient;
    Ref provider;
    Ref coverage;
};
