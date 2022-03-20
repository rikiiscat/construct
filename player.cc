#include "player.h"
#include <random>
#include <sstream>
#include <iostream>

using namespace std;

bool isint(string s) {

    istringstream iss{s};

    int num;

    iss >> num;

    if (iss.fail()) {

        cout << "ERROR:  isn't a valid integer." << endl;
        return false;
    }

    if (!(2 <= num && num <= 12)) {

        cout << "Input a roll between 2 and 12" << endl;
        return false;
    }
    
    return true;
}

void Player::addBasement(int id) {

    this->basement.insert(id);
}

void Player::UpgradeToHouse(int id) {

    this->basement.erase(id);
    this->house.insert(id);
}

void Player::UpgradeToTower(int id) {

    this->basement.erase(id);
    this->tower.insert(id);
}

Player::Player(string color):
    color{color} {

    for (int i = 0; i < 5; i++) {

        status.emplace_back(0);
    }
}

int Player::returnPoint() {

    return (basement.size()) + (2 * house.size()) + (3 * tower.size());
}

Dice::Dice() : isFair{false} {}

int Dice::getNum() {

    string s;

    if (isFair) {

        return (rand() % 10 + 2);
    }

    cout << "Input a roll between 2 and 12" << endl;
    getline(cin, s);

    if (cin.eof()) {

        throw 0;
    }

    while (!isint(s)) {

        getline(cin, s);
    }

    istringstream iss{s};
    int num;
    iss >> num;
    return num;
}

void Dice::setFair() {

    isFair = true;
}

void Dice::setLoad() {

    isFair = false;
}

