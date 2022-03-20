#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <memory>

#include "startup.h"
#include "controller.h"
#include "view.h"

using namespace std;

int main(int argc, char **argv) {

    bool playAgain = false;

    while (true) {

        Controller con = Controller();
        shared_ptr<StartTemplate> startUp;
        bool newGame = false;

        try {

            if (argc == 1) {

                startUp = make_shared<Board>();
                newGame = true;

            } else if (argc == 2) {

                string args = argv[1];

                if (args == "-random-board") {
            
                    startUp = make_shared<Random>();
                    newGame = true;
                } else {

                throw args;
                }

            } else if (argc == 3) {

                string args = argv[1];
                string file = argv[2];
                
                if (args == "-seed") {

                    startUp = make_shared<Seed>();
                    newGame = true;

                } else if (args == "-load") {

                    startUp = make_shared<LoadGame>();

                } else if (args == "-board") {

                    startUp = make_shared<Board>();
                    newGame = true;
            
                } else {
                    
                    throw args;
                }

            } else if (argc >= 4) {
                
                string s = argv[3];
                throw s;
            }
            
        } catch(const string s) {
            
            cerr << "ERROR: unrecognized argument " << s << endl;
            return 0;

        } 

        try {

            if (argc == 1) {

            startUp->generateBoard(con, "layout.txt"); 
        

            } else if (argc == 2) {
                
                startUp->generateBoard(con, "");
            } else {
                string args = argv[2];
                startUp->generateBoard(con, args);
            }

        } catch(const string s) {

            cerr << "ERROR: Unable to open file " << s
                << " or file in incorrect format" << endl;
            return 0;
        } catch (int n) {

            return 0;
        }

        string s;

        {
            View board = View(con);
            board.printBoard(con);
        }

        if (newGame) {

            try {

                con.gameInit();
            } catch(int n) {

                con.save("backup.sv");
                return 0;
            }
            
            View board = View(con);
            board.printBoard(con);
        }
        

        while (true) {

            cout << "Builder " << translate(con.curPlayer) << "'s turn." << endl;

            while (getline(std::cin, s)) {

                istringstream iss{s};
                string cmd;
                iss >> cmd;

                if (cmd == "load") {

                    con.setLoadedDie();
                } else if (cmd == "fair") {
        
                    con.setFairDie();
                } else if (cmd == "roll") {
                    
                    try {
                        con.roll();
                    } catch (int n) {

                        con.save("backup.sv");
                        return 0;
                    }
                    
                    break;
                } else if (cmd == "help") {
                    
                    cout << "~ load : changes current builder's dice type to 'loaded'" << endl;
                    cout << "~ fair : changes current builder's dice type to 'fair'" << endl;
                    cout << "~ roll : rolls the dice and distributes resources." << endl;
                    cout << "~ status : prints the current status of all builders in order from builder 0 to 3." << endl;
                    cout << "~ help : prints out the list of commands." << endl;

                } else if (cmd == "status") {

                    con.printStatus();
                } else if (cmd == "board") {

                    View board = View(con);
                    board.printBoard(con);
                    
                } else {

                    cout << "Invalid command." << endl 
                        << "Please enter 'help' for a list of valid commands." << endl;
                }
            }

            if (cin.eof()) {

                con.save("backup.sv");
                return 0;
            }

            cout << "Enter a command:" << endl;

            while (getline(std::cin, s)) {

                istringstream iss{s};
                string cmd;
                iss >> cmd;
                

                if (cmd == "board") {

                    View board = View(con);
                    board.printBoard(con);

                } else if (cmd == "status") {

                    con.printStatus();

                } else if (cmd == "residences") {
        
                    try {
                        con.residences();
                    } catch (...) {

                        con.save("backup.sv");
                        return 0;
                    }
                    
                } else if (cmd == "build-road") {
                    
                    int roadNum;
                    iss >> roadNum;

                    if (iss.fail()) {

                        cerr << "ERROR:  isn't a valid integer." << endl;
                        continue;
                    }

                    try {
                        con.buildRoad(roadNum);
                    } catch (...) {

                        con.save("backup.sv");
                        return 0;
                    }

                } else if (cmd == "build-res") {

                    int resNum;
                    iss >> resNum;

                    if (iss.fail()) {

                        cerr << "ERROR:  isn't a valid integer." << endl;
                        continue;
                    }

                    try {
                        con.buildRes(resNum);
                    } catch (...) {

                        con.save("backup.sv");
                        return 0;
                    }
                } else if (cmd == "improve") {
                    
                    int n;
                    iss >> n;

                    if (iss.fail()) {

                        cerr << "ERROR:  isn't a valid integer." << endl;
                        continue;
                    }

                    try {
                        con.improve(n);
                    } catch (...) {

                        con.save("backup.sv");
                        return 0;
                    }

                } else if (cmd == "trade") {
                    
                    string color;
                    string give;
                    string take;

                    iss >> color;
                    iss >> give;
                    iss >> take;

                    if (iss.fail()) {

                        cerr << "invalid inputs" << endl;
                        continue;
                    }

                    try {
                        con.trade(color, give, take);
                    } catch (int n) {

                        con.save("backup.sv");
                        return 0;
                    }

                } else if (cmd == "next") {
                    
                    con.next();
                    View board = View(con);
                    board.printBoard(con);
                    break;
                } else if (cmd == "save") {
                    
                    string f;
                    iss >> f;

                    if (iss.fail()) {

                        cerr << "need file name" << endl;
                        continue;
                    }

                    con.save(f);
                } else if (cmd == "help") {
                    
                    cout << "~ board : prints the current board." << endl;
                    cout << "~ status : prints the current status of all builders in order from builder 0 to 3." << endl;
                    cout << "~ residences : prints the residences the current builder has currently completed." << endl;
                    cout << "~ build-road <road#> : attempts to builds the road at <road#>." << endl;
                    cout << "~ build-res <housing#> : attempts to builds a basement at <housing#>." << endl;
                    cout << "~ improve <housing#> : attempts to improve the residence at <housing#>." << endl;
                    cout << "~ trade <colour> <give> <take> : attempts to trade with builder <colour>, giving one resource of type <give> and receiving one resource of type <take>." << endl;
                // cout << "~ market <sell> <buy> : attempts to sell resources on the market, giving four resource of type <sell> and receiving one resource of type <buy>." << endl;
                    cout << "~ next : passes control onto the next builder in the game." << endl;
                    cout << "~ save <file> : saves the current game state to <file>." << endl;
                    cout << "~ help : prints out the list of commands." << endl;

                } else {

                    if (cin.eof()) {

                        con.save("backup.sv");
                        return 0;
                    }

                    cout << "Invalid command." << endl 
                        << "Please enter 'help' for a list of valid commands." << endl;
                }

                cout << "Enter a command:" << endl;
            }


            string winner = con.win();
            if (winner != "none") {
                
                cout << "Congratulations!! " << winner << " wins!!" << endl;
                cout << "Would you like to play again? (enter 'yes' or 'no')" << endl;

                string s;

                getline(cin, s);

                while (true) {

                    if (s == "yes") {
                        playAgain = true;
                        break;
                    } else if (s == "no") {

                        return 0;
                    } else {

                        cout << "please enter 'yes' or 'no' only" << endl;
                        getline(cin, s);
                    }
                }
                
            }

            if (playAgain) {

                break;
            }
        }

    }

    

    

    return 0;
}
