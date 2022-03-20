#ifndef SU
#define SU


#include <string>

class Controller;

class StartTemplate {

    public:

    virtual void generateBoard(Controller& con, std::string f) = 0;

};

class Random : public StartTemplate {

    public:

    void generateBoard(Controller& con, std::string f) override;
};

class LoadGame : public StartTemplate {

    public:

    void generateBoard(Controller& con, std::string f) override;
};


class Seed : public StartTemplate {

    public:

    void generateBoard(Controller& con, std::string f) override;
};

class Board : public StartTemplate {

    public:

    void generateBoard(Controller& con, std::string f) override;
};

#endif

