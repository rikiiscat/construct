#include "controller.h"
#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <fstream>

using namespace std;

string translate(int id) {

    if (id == 0) {

        return "Blue";
    } else if (id == 1) {

        return "Red";
    } else if( id == 2) {

        return "Orange";
    } else if (id == 3) {

        return "Yellow";
    }

    return "none";
}

int colorToInt(string id) {

    if (id == "Blue" || id == "B" || id == "blue" || id == "BLUE" || id == "b") {

        return 0;
    } else if (id == "Red" || id == "R" || id == "red" || id == "RED" || id == "r") {

        return 1;
    } else if( id == "Orange" || id == "orange" || id == "O" || id == "ORANGE" || id == "o") {

        return 2;
    } else if (id == "Yellow" || id == "Y" || id == "yellow" || id == "YELLOW" || id == "y") {

        return 3;
    }

    return -1;
}

string resTranslate(int id) {

    if (id == 0) {

        return "BRICK";
    } else if (id == 1) {

        return "ENERGY";
    } else if( id == 2) {

        return "GLASS";
    } else if( id == 3) {

        return "HEAT";
    } else if (id == 4) {

        return "WIFI";
    }

    return "none";
    
}

int strToID_res(string id) {

    if (id == "BRICK" || id == "B" || id == "brick" || id == "b" || id == "Brick") {

        return 0;
    } else if (id == "ENERGY" || id == "energy" || id == "E" || id == "e" || id == "Energy") {

        return 1;
    } else if( id == "GLASS" || id =="G" || id == "g" || id == "glass" || id == "Glass") {

        return 2;
    } else if( id == "HEAT" || id == "heat" || id == "H" || id == "h" || id == "Heat") {

        return 3;
    } else if (id == "WIFI" || id == "wifi" || id == "Wifi" || id == "w" || id == "W") {

        return 4;
    }

    return -1;
}

int sum (vector<int> v) {

    int total = 0;

    for (auto& r : v) {

        total += r;
    }

    return total;
}

Controller::Controller() : curPlayer{0} {

    for (int i = 0; i < 19; i++) {

        Tile t;
        t.numb = i;
        tiles.emplace_back(t);
    }

    for (int i = 0; i < 54; i++) {

        Vertex v;
        v.vertex = i;
        vertices.emplace_back(v);
    }

    for (int i = 0; i < 72; i++) {

        Edge e;
        e.edge = i;
        edges.emplace_back(e);
    }

    PlayerList.emplace_back(Player("Blue"));
    PlayerList.emplace_back(Player("Red"));
    PlayerList.emplace_back(Player("Orange"));
    PlayerList.emplace_back(Player("Yellow"));

    gooseLoc = -1;

}

void Controller::printStatus() {

    for (unsigned int i = 0; i < PlayerList.size(); i++) {

        cout << "Builder " << translate(i) << "  has " << PlayerList.at(i).returnPoint() << " building points, "
            << PlayerList.at(i).status.at(0) << " BRICK, " << PlayerList.at(i).status.at(1) << " ENERGY, "
            << PlayerList.at(i).status.at(2) << " GLASS, " << PlayerList.at(i).status.at(3) << " HEAT, "
            << PlayerList.at(i).status.at(4) << " WIFI." << endl;
    }
}

void Controller::residences() {
    
    cout << translate(curPlayer) << " has built:" << endl;

    set<int>::iterator it = PlayerList.at(curPlayer).basement.begin();

    while (it != PlayerList.at(curPlayer).basement.end()) {

        cout << *it << " " << "B" << endl;
        it++;
    }

    it = PlayerList.at(curPlayer).house.begin();

    while (it != PlayerList.at(curPlayer).house.end()) {

        cout << *it << " " << "H" << endl;
        it++;
    }

    it = PlayerList.at(curPlayer).tower.begin();

    while (it != PlayerList.at(curPlayer).tower.end()) {

        cout << *it << " " << "T" << endl;
        it++;
    }
}

string Controller::win() {

    for (unsigned int i = 0; i < PlayerList.size(); i++) {

        if (PlayerList.at(i).returnPoint() >= 10) {

            
            return translate(i);
        }
    }

    return "none";
}

void Controller::setFairDie() {

    PlayerList.at(curPlayer).dice.setFair();
    cout << "Builder " << translate(curPlayer) << " now has fair Dice" << endl;
}

void Controller::setLoadedDie() {

    PlayerList.at(curPlayer).dice.setLoad();
    cout << "Builder " << translate(curPlayer) << " now has loaded Dice" << endl;
}

void Controller::roll() {

    int num = PlayerList.at(curPlayer).dice.getNum();

    cout << "The number you rolled is " << num << endl;

    if (num == 7) {

        for (auto& player : PlayerList) {

            int total = 0;
            vector<int> lost;

            for (int j = 0; j < 5; j++) {

                lost.emplace_back(0);
            }

            for (auto& r : player.status) {

                total += r;
            }

            if (total >= 10) {

                int numLost = total / 2;
                int lostres = numLost;

                while (numLost != 0) {

                    int ran = rand() % 5;

                    if (player.status.at(ran) != 0) {

                        player.status.at(ran)--;
                        numLost--;
                        lost.at(ran)++;
                    }

                }

                cout << "Builder " << player.color << " lost " << lostres << " resources to the geese. They lost:" << endl;

                for (int i = 0; i < 5; i++) {

                    if (lost.at(i) > 0) {
                        
                        cout<< lost.at(i) << " " << resTranslate(i) << endl;
                    }
                    
                }
            }
        }

        bool validInput = false;
        int location = -1;

        while (!validInput) {

            cout << "Choose where to place the GEESE" << endl; 

            string s;
            

            getline(cin, s);

            if (cin.eof()) {

                throw;
            }

            istringstream iss{s};

            iss >> location;

            if (iss.fail()) {

                cout << "ERROR: Choose where to place the GEESE. isn't a valid integer." << endl;
                continue;
            }

            if (location == gooseLoc || location < 0 || location > 18) {

                cout << "Geese can't move here." << endl;
                continue;
            }

            validInput = true;
        }

        
        if (gooseLoc >= 0) {
            tiles.at(gooseLoc).geese = false;
        }
        
        gooseLoc = location;
        tiles.at(gooseLoc).geese = true;

        set<int> vertices_num = tiles.at(gooseLoc).returnVertex();
        set<int> owners;
        set<int> ownersID;

        for (auto& v : vertices_num) {

            if (vertices.at(v).owner >= 0 && vertices.at(v).owner != curPlayer &&
                sum(PlayerList.at(vertices.at(v).owner).status) > 0) {

                owners.insert(vertices.at(v).owner);
                ownersID.insert(vertices.at(v).owner);
            }
        }

        if (owners.size() == 0) {

            cout << "Builder " << translate(curPlayer) << " has no builders to steal from." << endl;
            return;

        } else {

            cout << "Builder " << translate(curPlayer) << " can choose to steal from ";

            for (auto& o :owners) {
                cout << translate(o) << " ";
            }

            cout << endl;
        }

        validInput = false;

        while (true) {

            cout << "Choose a builder to steal from" << endl; 
            string s;
            getline(cin, s);
            if (colorToInt(s) < 0) {

                cout << "invalid colour" << endl;
                continue;
            } else if (ownersID.find(colorToInt(s)) == ownersID.end()) {

                cout << "They cannot be stolen from" << endl;
                continue;
            }

            while (true) {

                int res = rand() % 5;

                if (PlayerList.at(colorToInt(s)).status.at(res) > 0) {

                    PlayerList.at(colorToInt(s)).status.at(res) -- ;
                    PlayerList.at(curPlayer).status.at(res)++;

                    cout << "Builder " << translate(curPlayer) << " steals " << resTranslate(res) << " from builder " << translate(colorToInt(s)) << endl;

                    break;
                }
            }
            break;
        }
        

    } else {

        bool gotResource = false;

        for (unsigned int i = 0; i < PlayerList.size(); i++) {

            vector<int> resourse;

            for (int j = 0; j < 5; j++) {

                resourse.emplace_back(0);
            }

            set<int>::iterator it = PlayerList.at(i).basement.begin();

            while (it != PlayerList.at(i).basement.end()) {

                set<int> t = vertices.at(*it).returnTiles();

                set<int>::iterator it_tile = t.begin();

                while (it_tile != t.end()) {

                    if (tiles.at(*it_tile).getVal() == num && tiles.at(*it_tile).hasGeese() == false) {

                        resourse.at(tiles.at(*it_tile).getType())++;
                    }

                    it_tile++;
                }
                
                it ++;
            }

            for (auto & it : PlayerList.at(i).house) {

                set<int> t = vertices.at(it).returnTiles();

                for (auto &t_num : t) {

                    if (tiles.at(t_num).getVal() == num && tiles.at(t_num).hasGeese() == false) {

                        resourse.at(tiles.at(t_num).getType()) += 2;
                    }
                }
            }

            for (auto & it : PlayerList.at(i).tower) {

                set<int> t = vertices.at(it).returnTiles();

                for (auto &t_num : t) {

                    if (tiles.at(t_num).getVal() == num && tiles.at(t_num).hasGeese() == false) {

                        resourse.at(tiles.at(t_num).getType()) += 3;
                    }
                }
            }

            bool noGain = true;

            for(auto& r : resourse) {

                if (r != 0) {

                    noGain = false;
                }
            }

            if (!noGain) {

                cout << "Builder " << translate(i) << " gained:" << endl;

                for (int j = 0; j < 5; j++) {
                
                    if (resourse.at(j) != 0) {

                        cout << resourse.at(j) << " " << resTranslate(j) << endl;
                        PlayerList.at(i).status.at(j) += resourse.at(j);
                    }
                    
                }

                gotResource = true;;
            }

        }

        if (!gotResource) {

            cout << "No builders gained resources." << endl;
        }
    }
}

void Controller::buildRoad(int n) {


    if(PlayerList.at(curPlayer).status.at(3) < 1 || 
       PlayerList.at(curPlayer).status.at(4) < 1 ) {

        cout << "You do not have enough resources" << endl;
        return;

    } else if (n > 71 || n < 0) {

        cout << "You cannot build there" << endl;
        return;
        
    } else if (edges.at(n).owner != -1) { // has owner

        cout << "You cannot build there" << endl;
        return;
    }

    set<int> v = edges.at(n).returnVertex();

    for (auto &ver : v) {
        
        if (vertices.at(ver).owner == curPlayer) {

            cout << "Builder " << translate(curPlayer) << " successfully built a Road at " << n << "." << endl;
            PlayerList.at(curPlayer).status.at(3) --;
            PlayerList.at(curPlayer).status.at(4) --;
            PlayerList.at(curPlayer).roads.insert(n);
            edges.at(n).owner = curPlayer;
            return;
        }

        set<int> e = vertices.at(ver).returnEdges();

        for (auto &edgeNum : e) {

            if (edges.at(edgeNum).owner == curPlayer && vertices.at(ver).owner == -1) {

                cout << "Builder " << translate(curPlayer) << " successfully built a Road at " << n << "." << endl;
                PlayerList.at(curPlayer).status.at(3) --;
                PlayerList.at(curPlayer).status.at(4) --;
                PlayerList.at(curPlayer).roads.insert(n);
                edges.at(n).owner = curPlayer;
                return;
            }
        }
    }
    
    cout << "You cannot build there" << endl;
    return;
}

void Controller::buildRes(int n) {

    if(PlayerList.at(curPlayer).status.at(0) < 1 || 
       PlayerList.at(curPlayer).status.at(1) < 1 ||
       PlayerList.at(curPlayer).status.at(2) < 1 || 
       PlayerList.at(curPlayer).status.at(4) < 1 ) {

        cout << "You do not have enough resources" << endl;
        return;

    } else if (n > 53 || n < 0) {

        cout << "You cannot build there" << endl;
        return;
        
    } else if (vertices.at(n).owner != -1) { // has owner

        cout << "You cannot build there" << endl;
        return;
    }

    set<int> e = vertices.at(n).returnEdges();

    bool hasRoad = false;

    for (auto edgeNum : e) {

        set<int> adjacentVertices = edges.at(edgeNum).returnVertex();

        for (auto v : adjacentVertices) {

            if (vertices.at(v).owner != -1) {

                cout << "You cannot build there (has adjacent res)" << endl;
                return;
            }
            
        }

        if (edges.at(edgeNum).owner == curPlayer) {

            hasRoad = true;
        }
    }

    if (hasRoad) {

        cout << "Builder " << translate(curPlayer) << " successfully built a Basement at " << n << "." << endl;

        PlayerList.at(curPlayer).status.at(0) --;
        PlayerList.at(curPlayer).status.at(1) --;
        PlayerList.at(curPlayer).status.at(2) --;
        PlayerList.at(curPlayer).status.at(4) --;
       
        vertices.at(n).owner = curPlayer;
        vertices.at(n).building = "B";
        PlayerList.at(curPlayer).basement.insert(n);

    } else {

        cout << "You cannot build there (no adjacent road)" << endl;
    }
}

void Controller::improve(int n) {

    if (n > 53 || n < 0) {

        cout << "Invalid residence." << endl;
        return;
        
    } else if (vertices.at(n).owner != curPlayer) { // has owner

        cout << "Invalid residence." << endl;
        return;
    }

    if (vertices.at(n).building == "B") {
        
        if(PlayerList.at(curPlayer).status.at(2) < 2 || 
            PlayerList.at(curPlayer).status.at(3) < 3) {

            cout << "You do not have enough resources" << endl;
            return;
        } 

        PlayerList.at(curPlayer).status.at(2) -= 2;
        PlayerList.at(curPlayer).status.at(3) -= 3;
        vertices.at(n).building  = "H";
        PlayerList.at(curPlayer).UpgradeToHouse(n);

        cout << "Builder " << translate(curPlayer) << " successfully built a House at " << n << endl;

    } else if (vertices.at(n).building == "H") {

        if(PlayerList.at(curPlayer).status.at(0) < 3 || 
            PlayerList.at(curPlayer).status.at(1) < 2 ||
            PlayerList.at(curPlayer).status.at(2) < 2 || 
            PlayerList.at(curPlayer).status.at(3) < 2 ||
            PlayerList.at(curPlayer).status.at(4) < 1 ) {

            cout << "You do not have enough resources" << endl;
            return;
        } 

        PlayerList.at(curPlayer).status.at(0) -= 3; 
        PlayerList.at(curPlayer).status.at(1) -= 2;
        PlayerList.at(curPlayer).status.at(2) -= 2; 
        PlayerList.at(curPlayer).status.at(3) -= 2;
        PlayerList.at(curPlayer).status.at(4) -= 1;

        vertices.at(n).building  = "T";
        PlayerList.at(curPlayer).UpgradeToTower(n);
        cout << "Builder " << translate(curPlayer) << " successfully built a Tower at " << n << endl;

    } else {

        cout << "You can't improve that building." << endl;
    }
}

void Controller::next() {

    if (curPlayer >= 3) {

        curPlayer = 0;

    } else {

        curPlayer++;
    }
}

void Controller::trade(std::string color, std::string give, std::string take) {

    if (colorToInt(color) < 0) {

        cout << "invalid color" << endl;
        cout << "Tip: write color as Blue Red Orange or Yellow" << endl;
        return;
    }

    if (strToID_res(give) < 0 || strToID_res(give) < 0) {

        cout << "invalid resource" << endl;
        cout << "Tip: enter resources with all Caps, i.e BRICK WIFI HEAT GLASS or ENERGY" << endl;
        return;
    }

    if (color == translate(curPlayer)) {

        cout << "why are you trading with your self" << endl;
        return;
    }

    if (PlayerList.at(curPlayer).status.at(strToID_res(give)) < 1) {

        cout << "you don't have enough " << give << endl;
        return;
    }

    if (PlayerList.at(colorToInt(color)).status.at(strToID_res(take)) < 1) {

        cout << color << " doesn't have enough " << take << endl;
        return;
    }

    if (give == take) {

        cout << "why trade the same resource ?" << endl;
        return;
    }

    cout << translate(curPlayer) << " offers " << translate(colorToInt(color)) << " one " << resTranslate(strToID_res(give)) << " for one " << resTranslate(strToID_res(take)) << endl;
    cout << "Does " << translate(colorToInt(color)) << " accepts the offer?" << endl;

    string s;

    while (true) {

        getline(cin, s);

        if (cin.eof()) {

            throw 0;
        }

        if (s == "yes" || s == "Y" || s == "y" || s == "Yes") {

            PlayerList.at(curPlayer).status.at(strToID_res(give)) --;
            PlayerList.at(curPlayer).status.at(strToID_res(take)) ++;

            PlayerList.at(colorToInt(color)).status.at(strToID_res(take)) --;
            PlayerList.at(colorToInt(color)).status.at(strToID_res(give)) ++;

            cout << translate(curPlayer) << " gains one " << resTranslate(strToID_res(take)) <<  " and loses one " << resTranslate(strToID_res(give)) << endl;
            
            cout << translate(colorToInt(color)) << " gains one " << resTranslate(strToID_res(give)) <<  " and loses one " << resTranslate(strToID_res(take)) << endl;

            break;
        } else if (s == "no" || s == "No" || s == "N" || s == "n") {

            cout <<  "no trade is made" << endl;
            break;
        }

        cout << "please enter 'yes' or 'no'" << endl;
    }
    



    
}

void Controller::save(string f) {

    ofstream file{f};

    file << curPlayer << endl;

    for (auto& p: PlayerList) {

        for (auto stat: p.status) {

            file << stat << " ";
        }

        file << "r ";

        for (auto road: p.roads) {

            file << road << " ";
        }

        file << "h ";

        for (auto b: p.basement) {

            file << b << " B ";
        }

        for (auto h: p.house) {

            file << h << " H ";
        }

        for (auto t: p.tower) {

            file << t << " T ";
        }

        file << endl;
    }

    for (auto& t : tiles) {

        file << t.type << " " << t.value << " ";
    }

    file << endl;

    file << gooseLoc << endl;


}

void Controller::gameInit() {

    set<int> built;
    
    for (unsigned int i = 0; i < PlayerList.size(); i++) {

        while (true) {

            string s;
            cout << "Builder " << translate(i) << " where do yo want to build a basement?" << endl;
            getline(cin, s);

            if (cin.eof()) {
                throw 0;
            }

            istringstream iss{s};

            int basementID;

            iss >> basementID;

            if (iss.fail()) {

                cerr << "ERROR:  isn't a valid integer." << endl;
                continue;
            }

            if (basementID < 0 || basementID > 53) {

                cout << "You cannot build here." << endl;
                continue;
            }

            set<int> e = vertices.at(basementID).returnEdges();

            bool hasOwner = false;

            for (auto edgeNum : e) {

                set<int> adjacentVertices = edges.at(edgeNum).returnVertex();

                for (auto v : adjacentVertices) {

                    if (vertices.at(v).owner != -1) {

                        cout << "You cannot build there" << endl;
                        cout << "Basements already exist as locations:";

                        for (auto b : built) {

                            cout << " " << b;
                        }
                        cout << endl;

                        hasOwner = true;
                        break;
                    }
                    
                }

                if (hasOwner) {

                    break;
                }
            }

            if (!hasOwner) {

                vertices.at(basementID).owner = i;
                vertices.at(basementID).building = "B";
                PlayerList.at(i).basement.insert(basementID);
                built.insert(basementID);
                break;
            }
        }

    }

    for (int i = 3; i >= 0; i--) {

        while (true) {

            string s;
            cout << "Builder " << translate(i) << " where do yo want to build a basement?" << endl;
            getline(cin, s);

            if (cin.eof()) {
                throw 0;
            }

            istringstream iss{s};

            int basementID;

            iss >> basementID;

            if (iss.fail()) {

                cerr << "ERROR:  isn't a valid integer." << endl;
                continue;
            }

            if (basementID < 0 || basementID > 53) {

                cout << "You cannot build here." << endl;
                continue;
            }

            set<int> e = vertices.at(basementID).returnEdges();

            bool hasOwner = false;

            for (auto edgeNum : e) {

                set<int> adjacentVertices = edges.at(edgeNum).returnVertex();

                for (auto v : adjacentVertices) {

                    if (vertices.at(v).owner != -1) {

                        cout << "You cannot build there" << endl;
                        cout << "Basements already exist as locations:";

                        for (auto b : built) {

                            cout << " " << b;
                        }
                        cout << endl;
                        hasOwner = true;
                        break;
                    }
                    
                }

                if (hasOwner) {

                    break;
                }
            }

            if (!hasOwner) {

                vertices.at(basementID).owner = i;
                PlayerList.at(i).basement.insert(basementID);
                vertices.at(basementID).building = "B";
                built.insert(basementID);
                break;
            }
        }

    }
}


