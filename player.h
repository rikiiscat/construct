#ifndef P
#define P

#include <vector>
#include <set>
#include <string>

class Dice {

    bool isFair;

    public:

    Dice();
    int getNum();
    void setFair();
    void setLoad();
};


class Player {

    public:

    Dice dice;
    std::string color;

    std::vector<int> status;
    std::set<int> roads;
    std::set<int> basement;
    std::set<int> house;
    std::set<int> tower;

    void addBasement(int id);
    void UpgradeToHouse(int id);
    void UpgradeToTower(int id);
    Player(std::string color);
    int returnPoint();
};

#endif
