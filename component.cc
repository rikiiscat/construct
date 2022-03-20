#include "component.h"
#include <set>

using namespace std;

Tile::Tile() {

    geese = false;
}

bool Tile::hasGeese() {
    
    return geese;
}

int Tile::getType() {

    return type;

}

int Tile::getVal() {

    return value;
}


set<int> Tile::returnVertex() {

    set<int> s;
    if(numb == 0) {
        s.insert(0);
        s.insert(1);
        s.insert(3);
        s.insert(4);
        s.insert(8);
        s.insert(9);
    } else if(numb == 1) {
        s.insert(2);
        s.insert(3);
        s.insert(7);
        s.insert(8);
        s.insert(13);
        s.insert(14);
    } else if(numb == 2) {
        s.insert(4);
        s.insert(5);
        s.insert(9);
        s.insert(10);
        s.insert(15);
        s.insert(16);
    } else if(numb == 16) {
        s.insert(37);
        s.insert(38);
        s.insert(43);
        s.insert(44);
        s.insert(48);
        s.insert(49);
    } else if(numb == 17) {
        s.insert(39);
        s.insert(40);
        s.insert(45);
        s.insert(46);
        s.insert(50);
        s.insert(51);
    } else if(numb == 18) {
        s.insert(44);
        s.insert(45);
        s.insert(49);
        s.insert(50);
        s.insert(52);
        s.insert(53);
    } else {
        int div = (numb - 3) / 5;
        int mod = (numb - 3) % 5;
        int start_numb1 = 0;
        for (int i = 0; i < div; ++i) {
            ++start_numb1;
        }
        int left_up_v = numb * 2 + start_numb1 * 2;
        if(mod == 3 || mod == 4) {
            left_up_v += 1;
        }
        s.insert(left_up_v);
        s.insert(left_up_v + 1);
        s.insert(left_up_v + 6);
        s.insert(left_up_v + 7);
        s.insert(left_up_v + 12);
        s.insert(left_up_v + 13);
    }
    return s;
}

set<int> Tile::returnEdge() {
    set<int> s;
    if(numb == 0) {
        s.insert(0);
        s.insert(1);
        s.insert(2);
        s.insert(6);
        s.insert(7);
        s.insert(10);
    } else if(numb == 1) {
        s.insert(3);
        s.insert(5);
        s.insert(6);
        s.insert(13);
        s.insert(14);
        s.insert(18);
    } else if(numb == 2) {
        s.insert(4);
        s.insert(7);
        s.insert(8);
        s.insert(15);
        s.insert(16);
        s.insert(19);
    } else if(numb == 16) {
        s.insert(52);
        s.insert(55);
        s.insert(56);
        s.insert(63);
        s.insert(64);
        s.insert(67);
    } else if(numb == 17) {
        s.insert(53);
        s.insert(57);
        s.insert(58);
        s.insert(65);
        s.insert(66);
        s.insert(68);
    } else if(numb == 18) {
        s.insert(61);
        s.insert(64);
        s.insert(65);
        s.insert(69);
        s.insert(70);
        s.insert(71);
    } else {
        int div = (numb - 3) / 5;
        int mod = (numb - 3) % 5;
        int start_numb1 = 0;
        for (int i = 0; i < div; ++i) {
            ++start_numb1;
        }
        int left_up_v = numb * 2 + start_numb1*2;
        int mid_up_v = 0;
        int left_up_v1 = 0;
        if(mod == 0) {
            mid_up_v = left_up_v + left_up_v / 2 - start_numb1;
            left_up_v1 = mid_up_v + 3;
        } else if(mod == 1) {
            mid_up_v = (left_up_v - 2) + (left_up_v - 2)/2 - start_numb1 + 1;
            left_up_v1 = mid_up_v + 4;
        } else if(mod == 2) {
            mid_up_v = (left_up_v - 4) + (left_up_v - 4)/2 - start_numb1 + 2;
            left_up_v1 = mid_up_v + 5;
        } else if(mod == 3) {
            if(numb == 6) {
                s.insert(18);
                s.insert(21);
                s.insert(22);
                s.insert(30);
                s.insert(31);
                s.insert(35);
            } else if(numb == 11) {
                s.insert(35);
                s.insert(38);
                s.insert(39);
                s.insert(47);
                s.insert(48);
                s.insert(52);
            }
            return s;
        } else {
            if(numb == 7) {
                s.insert(19);
                s.insert(23);
                s.insert(24);
                s.insert(32);
                s.insert(33);
                s.insert(36);
            } else if(numb == 12) {
                s.insert(36);
                s.insert(40);
                s.insert(41);
                s.insert(49);
                s.insert(50);
                s.insert(53);
            }
            return s;
        }
        s.insert(mid_up_v);
        s.insert(left_up_v1);
        s.insert(left_up_v1 + 1);
        s.insert(left_up_v1 + 8);
        s.insert(left_up_v1 + 9);
        s.insert(mid_up_v + 17);
    }
    return s;
}


Vertex::Vertex() {

    owner = -1;
    building = "";
}

string Vertex::returnOwner() {

    if (owner == 0) {

        return "B";

    } else if (owner == 1) {

        return "R";
    } else if (owner == 2) {

        return "O";
    } else if (owner == 3) {

        return "Y";
    }

    return "";

}

string Vertex::returnBuilding() {

    return building;
}

set<int> Vertex::returnEdges() {
    set<int> s1;
    int div = (vertex - 12) / 12;
    int mod = (vertex - 12) % 12;
    if (vertex == 0) {
        s1.insert(0);
        s1.insert(1);
    } else if (vertex == 1) {
        s1.insert(0);
        s1.insert(2);
    } else if (vertex == 2) {
        s1.insert(3);
        s1.insert(5);
    } else if (vertex == 3) {
        s1.insert(1);
        s1.insert(3);
        s1.insert(6);
    } else if (vertex == 4) {
        s1.insert(2);
        s1.insert(4);
        s1.insert(7);
    } else if (vertex == 5) {
        s1.insert(4);
        s1.insert(8);
    } else if (vertex == 6) {
        s1.insert(9);
        s1.insert(12);
    } else if (vertex == 7) {
        s1.insert(5);
        s1.insert(9);
        s1.insert(13);
    } else if (vertex == 8) {
        s1.insert(6);
        s1.insert(10);
        s1.insert(14);
    } else if (vertex == 9) {
        s1.insert(7);
        s1.insert(10);
        s1.insert(15);
    } else if (vertex == 10) {
        s1.insert(8);
        s1.insert(11);
        s1.insert(16);
    } else if (vertex == 11) {
        s1.insert(11);
        s1.insert(17);
    } else if (vertex == 18) {
        s1.insert(20);
        s1.insert(26);
        s1.insert(29);
    } else if (vertex == 30) {
        s1.insert(37);
        s1.insert(43);
        s1.insert(46);
    } else if (vertex == 48) {
        s1.insert(63);
        s1.insert(67);
    } else if (vertex == 49) {
        s1.insert(64);
        s1.insert(67);
        s1.insert(69);
    } else if (vertex == 50) {
        s1.insert(65);
        s1.insert(68);
        s1.insert(70);
    } else if (vertex == 51) {
        s1.insert(66);
        s1.insert(68);
    } else if (vertex == 52) {
        s1.insert(69);
        s1.insert(71);
    } else if (vertex == 53) {
        s1.insert(70);
        s1.insert(71);
    } else if (mod == 0) {
        s1.insert(vertex + div * 5);
        s1.insert(vertex + div * 5 + 8);
    } else if (mod == 6) {
        if (vertex == 42) {
            s1.insert(54);
            s1.insert(60);
        }
    } else if (mod == 1) {
        s1.insert(vertex + div * 5);
        s1.insert(vertex + div * 5 + 5);
        s1.insert(vertex + div * 5 + 8);
    } else if (mod == 7) {
        s1.insert(12 * (div + 1) + div * 5 + 9);
        s1.insert(12 * (div + 1) + div * 5 + 9 + 5);
        if (vertex == 43) {
            s1.insert(63);
        } else {
            s1.insert(12 * (div + 1) + div * 5 + 9 + 9);
        }
    } else if (mod == 2) {
        s1.insert(12 * (div + 1) + div * 5 + mod);
        s1.insert(12 * (div + 1) + div * 5 + mod + 4);
        s1.insert(12 * (div + 1) + div * 5 + mod + 8);
    } else if (mod == 8) {
        s1.insert(12 * (div + 1) + div * 5 + 10);
        s1.insert(12 * (div + 1) + div * 5 + 15);
        if (vertex == 44) {
            s1.insert(64);
        } else {
            s1.insert(12 * (div + 1) + div * 5 + 19);
        }
    } else if (mod == 3) {
        s1.insert(12 * (div + 1) + div * 5 + 3);
        s1.insert(12 * (div + 1) + div * 5 + 7);
        s1.insert(12 * (div + 1) + div * 5 + 11);
    } else if (mod == 9) {
        s1.insert(12 * (div + 1) + div * 5 + 11);
        s1.insert(12 * (div + 1) + div * 5 + 15);
        if (vertex == 45) {
            s1.insert(65);
        } else {
            s1.insert(12 * (div + 1) + div * 5 + 20);
        }
    } else if (mod == 4) {
        s1.insert(12 * (div + 1) + div * 5 + 4);
        s1.insert(12 * (div + 1) + div * 5 + 7);
        s1.insert(12 * (div + 1) + div * 5 + 12);
    } else if (mod == 10) {
        s1.insert(12 * (div + 1) + div * 5 + 12);
        s1.insert(12 * (div + 1) + div * 5 + 16);
        if (vertex == 46) {
            s1.insert(66);
        } else {
            s1.insert(12 * (div + 1) + div * 5 + 21);
        }
    } else if (mod == 5) {
        s1.insert(12 * (div + 1) + div * 5 + 5);
        s1.insert(12 * (div + 1) + div * 5 + 13);
    } else if (mod == 11) {
        s1.insert(12 * (div + 1) + div * 5 + 13);
        if (vertex == 23) {
            s1.insert(28);
            s1.insert(34);
        } else if (vertex == 35) {
            s1.insert(45);
            s1.insert(51);
        } else if (vertex == 47) {
            s1.insert(62);
        }
    }
    return s1;
}

set<int> Vertex::returnTiles() {
    set<int> s;
    int mod = vertex % 6;
    if(vertex == 0 || vertex == 1 || vertex ==3 || vertex == 4 || vertex == 8 || vertex == 9) {
        s.insert(0);
        if(vertex == 3) {
            s.insert(1);
        }
        if(vertex == 4) {
            s.insert(2);
        }
        if(vertex == 8) {
            s.insert(1);
            s.insert(4);
        }
        if(vertex == 9) {
            s.insert(2);
            s.insert(4);
        }
    } else if(vertex == 2) {
        s.insert(1);
    } else if(vertex == 5) {
        s.insert(2);
    } else if(mod == 0) {
        if(vertex == 48) {
            s.insert(16);
        } else if(vertex == 6) {
            s.insert(3);
        } else if(vertex == 12) {
            s.insert(3);
        } else if(vertex == 18) {
            s.insert(3);
            s.insert(8);
        } else if(vertex == 24) {
            s.insert(8);
        } else if(vertex == 30) {
            s.insert(8);
            s.insert(13);
        } else if(vertex == 36) {
            s.insert(13);
        } else if(vertex == 42) {
            s.insert(13);
        } else if(vertex == 48) {
            s.insert(16);
        }
    } else if(mod == 1) {
        if(vertex == 7) {
            s.insert(1);
            s.insert(3);
        } else if(vertex == 13) {
            s.insert(1);
            s.insert(3);
            s.insert(6);
        } else if(vertex == 19) {
            s.insert(3);
            s.insert(6);
            s.insert(8);
        } else if(vertex == 25) {
            s.insert(6);
            s.insert(8);
            s.insert(11);
        } else if(vertex == 31) {
            s.insert(8);
            s.insert(11);
            s.insert(13);
        } else if(vertex == 37) {
            s.insert(11);
            s.insert(13);
            s.insert(16);
        } else if(vertex == 43) {
            s.insert(13);
            s.insert(16);
        } else if(vertex == 49) {
            s.insert(16);
            s.insert(18);
        }
    } else if(mod == 2) {
        if(vertex == 8) {
            s.insert(0);
            s.insert(1);
            s.insert(4);
        } else if(vertex == 14) {
            s.insert(1);
            s.insert(4);
            s.insert(6);
        } else if(vertex == 20) {
            s.insert(4);
            s.insert(6);
            s.insert(9);
        } else if(vertex == 26) {
            s.insert(6);
            s.insert(9);
            s.insert(11);
        } else if(vertex == 32) {
            s.insert(9);
            s.insert(11);
            s.insert(14);
        } else if(vertex == 38) {
            s.insert(11);
            s.insert(14);
            s.insert(16);
        } else if(vertex == 44) {
            s.insert(14);
            s.insert(16);
            s.insert(18);
        } else if(vertex == 50) {
            s.insert(17);
            s.insert(18);
        }
    } else if(mod == 3) {
        if(vertex == 9) {
            s.insert(0);
            s.insert(2);
            s.insert(4);
        } else if(vertex == 15) {
            s.insert(2);
            s.insert(4);
            s.insert(7);
        } else if(vertex == 21) {
            s.insert(4);
            s.insert(7);
            s.insert(9);
        } else if(vertex == 27) {
            s.insert(7);
            s.insert(9);
            s.insert(12);
        } else if(vertex == 33) {
            s.insert(9);
            s.insert(12);
            s.insert(14);
        } else if(vertex == 39) {
            s.insert(12);
            s.insert(14);
            s.insert(17);
        } else if(vertex == 45) {
            s.insert(14);
            s.insert(17);
            s.insert(18);
        } else if(vertex == 51) {
            s.insert(17);
        }
    } else if(mod == 4) {
        if(vertex == 10) {
            s.insert(2);
            s.insert(5);
        } else if(vertex == 16) {
            s.insert(2);
            s.insert(5);
            s.insert(7);
        } else if(vertex == 22) {
            s.insert(5);
            s.insert(7);
            s.insert(10);
        } else if(vertex == 28) {
            s.insert(7);
            s.insert(10);
            s.insert(12);
        } else if(vertex == 34) {
            s.insert(10);
            s.insert(12);
            s.insert(15);
        } else if(vertex == 40) {
            s.insert(12);
            s.insert(15);
            s.insert(17);
        } else if(vertex == 46) {
            s.insert(15);
            s.insert(17);
        } else if(vertex == 52) {
            s.insert(18);
        }
    } else if(mod == 5) {
        if(vertex == 11) {
            s.insert(5);
        } else if(vertex == 17) {
            s.insert(5);
        } else if(vertex == 23) {
            s.insert(5);
            s.insert(10);
        } else if(vertex == 29) {
            s.insert(10);
        } else if(vertex == 35) {
            s.insert(10);
            s.insert(15);
        } else if(vertex == 41) {
            s.insert(15);
        } else if(vertex == 47) {
            s.insert(15);
        } else if(vertex == 53) {
            s.insert(18);
        }
    }
    return s;
}

string Edge::hasRoad() {

    if (owner == 0) {

        return "B";

    } else if (owner == 1) {

        return "R";
    } else if (owner == 2) {

        return "O";
    } else if (owner == 3) {

        return "Y";
    }

    return "";
}

Edge::Edge() {

    owner = -1;
}

set<int> Edge::returnVertex() {
    set<int> s;
    if(edge == 0) {
        s.insert(0);
        s.insert(1);
    } else if(edge == 1) {
        s.insert(0);
        s.insert(3);
    } else if(edge == 2) {
        s.insert(1);
        s.insert(4);
    } else if(edge == 3) {
        s.insert(2);
        s.insert(3);
    } else if(edge == 4) {
        s.insert(4);
        s.insert(5);
    } else if(edge == 5) {
        s.insert(2);
        s.insert(7);
    } else if(edge == 6) {
        s.insert(3);
        s.insert(8);
    } else if(edge == 7) {
        s.insert(4);
        s.insert(9);
    } else if(edge == 8) {
        s.insert(5);
        s.insert(10);
    } else if(edge >= 9 && edge <= 62) {
        int mod = (edge-9)%17;
        int div = (edge-9)/17;
        if(mod == 0 || mod == 1 || mod == 2) {
            int smallest_v_adj = 6+12*div+mod*2;
            s.insert(smallest_v_adj);
            s.insert(smallest_v_adj+1);
        } else if(mod == 9 || mod == 10) {
            int smallest_v_adj = 6 + 12*div;
            if(mod == 9) {
                smallest_v_adj += 7;
            } else {
                smallest_v_adj += 9;
            }
            s.insert(smallest_v_adj);
            s.insert(smallest_v_adj+1);
        } else if(mod >= 3 && mod <= 8) {
            int smallest_v_adj = 6+div*12+mod-3;
            int largest_v_adj = smallest_v_adj + 6;
            s.insert(smallest_v_adj);
            s.insert(largest_v_adj);
        } else {
            int smallest_v_adj = 6+div*12+6+mod-11;
            int largest_v_adj = smallest_v_adj + 6;
            s.insert(smallest_v_adj);
            s.insert(largest_v_adj);
        }
    } else if(edge == 63) {
        s.insert(43);
        s.insert(48);
    } else if(edge == 64) {
        s.insert(44);
        s.insert(49);
    } else if(edge == 65) {
        s.insert(45);
        s.insert(50);
    } else if(edge == 66) {
        s.insert(46);
        s.insert(51);
    } else if(edge == 67) {
        s.insert(48);
        s.insert(49);
    } else if(edge == 68) {
        s.insert(50);
        s.insert(51);
    } else if(edge == 69) {
        s.insert(49);
        s.insert(52);
    } else if(edge == 70) {
        s.insert(50);
        s.insert(53);
    } else if(edge == 71) {
        s.insert(52);
        s.insert(53);
    }
    return s;
}
