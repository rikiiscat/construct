
#include "startup.h"
#include <fstream>
#include "controller.h"
#include <sstream>
#include <iostream>

#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

void loadLayout(Controller& con, ifstream& file, string f) {

    if (!file.is_open()) {

        throw f;
    }

    string str;
    getline(file, str);

    istringstream iss{str};

    for (unsigned int i = 0; i < con.tiles.size(); i++) {

        int type;
        iss >> type;

        if (iss.fail()) {

            throw f;
        }

        int value;
        iss >> value;

        if (iss.fail()) {

            throw f;
        }

        if ((type == 5 && value != 7) || (type != 5 && value == 7)) {

            cerr << "Something went wrong when loading." << endl;
            throw 0;
        }

        if (value > 12 || value < 2) {

            throw f;
        }

        if (type > 5 || type < 0) {

            throw f;
        }

        con.tiles.at(i).type = type;
        con.tiles.at(i).value = value;
    }
}

vector<int> genertateRandom (int setSeed, vector<int>& v) {

	// use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    if (setSeed > 0) {

        seed = setSeed;
    }

	std::default_random_engine rng{seed};

	for ( int i = 0; i < 1000; i++ ) {
		//std::shuffle( v.begin(), v.end(), std::default_random_engine(seed) );
		std::shuffle( v.begin(), v.end(), rng );
			
	} // for

    return v;
}


void Random::generateBoard(Controller& con, std::string f) {

    int goose = -1;
    std::vector<int> val = {2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    std::vector<int> board = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4};

    val = genertateRandom(-1, val);
    board = genertateRandom(-1, board);

    vector<int>::iterator val_it = val.begin();
    vector<int>::iterator board_it = board.begin();

    for (unsigned int i = 0; i < con.tiles.size(); i++) {

        con.tiles.at(i).value = *val_it;

        if (*val_it != 7) {

            con.tiles.at(i).type = *board_it;
            board_it++;
            
        } else {
            goose = i;
            con.tiles.at(i).type = 5;
        }

        val_it++;
    }

    con.gooseLoc = goose;
}

void LoadGame::generateBoard(Controller& con, std::string f) {

    ifstream file{f};

    if (!file.is_open()) {

        throw f;
    }

    string s;

    getline(file, s);

    istringstream iss {s};
    
    int cur;

    iss >> cur;

    if (iss.fail()) {

        throw f;
    } else if (cur < 0 || cur > 3) {
        throw f;
    }

    con.curPlayer = cur;

    for (unsigned int i = 0; i < con.PlayerList.size(); i++) {

        getline(file, s);
        istringstream issp {s};
        int id;
        string building;

        for (int j = 0; j < 5; j++) {

            int resource;
            issp >> resource;

            if (issp.fail()) {

                throw f;
            }

            
            con.PlayerList.at(i).status.at(j) = resource;
        }

        issp >> building;

        if (building != "r") {

            throw f;
        }


        while (true) {

            issp >> id;

            if (id > 71 || id < 0) {

                throw f;
            }
            
            if (issp.fail()) {

                break;
            }
            con.PlayerList.at(i).roads.insert(id);
            con.edges.at(id).owner = i;
            building = issp.peek();
        }

        issp.clear();
        issp >> building;

        if (building != "h") {

            throw f;
        }

        while (true) {

            issp >> id;

            if (issp.fail()) {
                break;
            }

            issp >> building; 

            if (issp.fail()) {

                throw f;
            }

            if (id > 53 || id < 0) {

                throw f;
            }

            if (building == "B") {

               con.PlayerList.at(i).basement.insert(id);
               con.vertices.at(id).owner = i;
               con.vertices.at(id).building = "B";
            } else if (building == "H") {

               con.PlayerList.at(i).house.insert(id);
               con.vertices.at(id).owner = i;
               con.vertices.at(id).building = "H";
            } else if (building == "T") {

               con.PlayerList.at(i).tower.insert(id);
               con.vertices.at(id).owner = i;
               con.vertices.at(id).building = "T";
            } else {

                throw f;
            }
            
            
        }

    }

    loadLayout(con, file, f);

    getline(file, s);

    istringstream issg{s};

    issg >> con.gooseLoc;
    con.tiles.at(con.gooseLoc).geese = true;
}

void Seed::generateBoard(Controller& con, std::string f) {

    unsigned int seed;

    try {
        seed = std::stoi(f);
    } catch( std::invalid_argument & e ) {
			std::cerr << e.what() << std::endl;
			throw f;
	} catch( std::out_of_range & e ) {
			std::cerr << e.what() << std::endl;
			throw f;
	} 

    int goose = -1;
    std::vector<int> val = {2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    std::vector<int> board = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4};

    val = genertateRandom(seed, val);
    board = genertateRandom(seed, board);

    vector<int>::iterator val_it = val.begin();
    vector<int>::iterator board_it = board.begin();

    for (unsigned int i = 0; i < con.tiles.size(); i++) {

        con.tiles.at(i).value = *val_it;

        if (*val_it != 7) {

            con.tiles.at(i).type = *board_it;
            board_it++;
            
        } else {
            goose = i;
            con.tiles.at(i).type = 5;
        }

        val_it++;
    }

    con.gooseLoc = goose;
    
}

void Board::generateBoard(Controller& con, std::string f) {

    ifstream file{f};
    loadLayout(con, file, f);
    
}

