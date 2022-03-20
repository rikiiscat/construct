#ifndef CC
#define CC

#include <vector>
#include "player.h"
#include "component.h"
#include <map>

class Controller {

    public:

    std::vector<Tile> tiles;
    std::vector<Edge> edges;
    std::vector<Vertex> vertices;
    

    int curPlayer;
    int gooseLoc;
    std::vector<Player> PlayerList;
    Controller();

    void printStatus();
    void residences();
    std::string win();
    void setFairDie();
    void setLoadedDie();
    void roll();

    void buildRoad(int n);

    void buildRes(int n);

    void improve(int n);

    void next();

    void trade(std::string color, std::string give, std::string take);

    void save(std::string f);

    void gameInit();

    void initHelper();

};

std::string translate(int id);

#endif
