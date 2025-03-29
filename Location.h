#ifndef LOCATION_H
#define LOCATION_H

struct Location{
    string name;
    int id;
    string code;
    int parking;

    bool operator==(const Location &other) const {
        return name == other.name && code == other.code && id == other.id;
    }

};

#endif //LOCATION_H
