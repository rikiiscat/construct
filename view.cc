#include "view.h"
#include "controller.h"
#include "component.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;


// see view.h for documentation
void View::printBoard(Controller& con) {
    /*
                        | 0|-- 0--| 1|
                          |         |
                          1    0    2
                          |  BRICK  |
                          
    */

    cout << "                    |" << vt[0] << "|--" << e[0] << "--|" <<  vt[1] << "|" << endl;
    cout << "                      |         |" << endl;
    cout << "                     " << e[1] << "    0   " << e[2] << endl;
    cout << "                      |" << t[0] << "|" << endl;
    
    /*
    
              | 2|-- 3--| 3|   3  | 4|-- 4--| 5|
                |         |         |         |
                5    1    6         7    2    8
                |  ENERGY |         |  HEAT   |
                
    */
    
    cout << "          |" << vt[2] << "|--" << e[3] << "--|" << vt[3] << "|  " << vl[0] 
        << "  |" <<  vt[4] << "|--" <<  e[4] << "--|" << vt[5] << "|" << endl;
    if (con.tiles[0].hasGeese()) {
        cout << "            |         |  GEESE  |         |" << endl;
    } else {
        cout << "            |         |         |         |" << endl;
    }
    cout << "           " << e[5] << "    1   " << e[6] << "        " << e[7] << "    2   " << e[8] << endl;
    cout << "            |" << t[1] << "|         |" << t[2] << "|" << endl;

    /*
    
    | 6|-- 9--| 7|  10  | 8|--10--| 9|   5  |10|--11--|11|
      |         |         |         |         |         |
     12    3   13        14    4   15        16    5   17
      |  ENERGY |         |  PARK   |         |  HEAT   |
    |12|   4  |13|--18--|14|      |15|--19--|16|  10  |17|
    
    */
    
    cout << "|" << vt[6] << "|--" << e[9] << "--|" << vt[7] 
        << "|  " << vl[1] << "  |" << vt[8] << "|--" << e[10] << "--|" << vt[9] << "|  " 
        << vl[2] << "  |" << vt[10] << "|--" << e[11] << "--|" << vt[11] << "|" << endl;
    if (con.tiles[1].hasGeese()) {
        cout << "  |         |  GEESE  |         |         |         |" << endl;
    } else if (con.tiles[2].hasGeese()) {
        cout << "  |         |         |         |  GEESE  |         |"  << endl;
    } else {
        cout << "  |         |         |         |         |         |" << endl;
    }
    cout << " " << e[12] << "    3   " << e[13] << "        " << e[14] << "    4   " 
        << e[15] << "        " << e[16] << "    5   " << e[17] << endl;
    cout << "  |" << t[3] << "|         |" << t[4] << "|         |" << t[5] << "|" << endl;
    cout << "|" << vt[12] << "|  " << vl[3] << "  |" << vt[13] << "|--" << e[18] << "--|" << vt[14] << "|  " 
        << vl[4] << "  |" << vt[15] << "|--" << e[19] << "--|" << vt[16] << "|  " 
        << vl[5] << "  |" << vt[17] << "|" << endl;
        
    /*
    
      |         |         |         |         |         |
     20        21    6   22        23    7   24        25
      |         |  GLASS  |         |  BRICK  |         |
    |18|--26--|19|  11  |20|--27--|21|   3  |22|--28--|23|
    
    */
  
       
    if (con.tiles[3].hasGeese()) {
        cout << "  |  GEESE  |         |         |         |         |" << endl;
    } else if (con.tiles[4].hasGeese()) {
        cout << "  |         |         |  GEESE  |         |         |" << endl;
    } else if (con.tiles[5].hasGeese()){
        cout << "  |         |         |         |         |  GEESE  |" << endl;
    } else {
        cout << "  |         |         |         |         |         |" << endl;
    }
    cout << " " << e[20] << "        " << e[21] << "    6   " << e[22] << "        " 
        << e[23] << "    7   " << e[24] << "        " << e[25] << endl;
    cout << "  |         |" << t[6] << "|         |" << t[7] << "|         |" << endl;
    cout << "|" << vt[18] << "|--" << e[26] << "--|" << vt[19] 
        << "|  " << vl[6]<< "  |" << vt[20] << "|--" << e[27] << "--|" << vt[21] << "|  " 
        << vl[7] << "  |" << vt[22] << "|--" << e[28] << "--|" << vt[23] << "|" << endl;
    
    /*
    
      |         |         |         |         |         |
     29    8   30        31    9   32        33   10   34
      |  HEAT   |         |  BRICK  |         |  BRICK  |
    |24|   8  |25|--35--|26|   2  |27|--36--|28|   6  |29|
    
    
    */   
    
    if (con.tiles[6].hasGeese()) {
        cout << "  |         |  GEESE  |         |         |         |" << endl;
    } else if (con.tiles[7].hasGeese()) {
        cout << "  |         |         |         |  GEESE  |         |" << endl;
    } else {
        cout << "  |         |         |         |         |         |" << endl;
    }
    cout << " " << e[29] << "    8   " << e[30] << "        " << e[31] << "    9   " << e[32] 
        << "        " << e[33] << "   10   " << e[34] << endl;
    cout << "  |" << t[8] << "|         |" << t[9] << "|         |" << t[10] << "|" << endl;
    cout << "|" << vt[24] << "|  " << vl[8] << "  |" << vt[25] << "|--" << e[35] << "--|" << vt[26] << "|  " 
        << vl[9] << "  |" << vt[27] << "|--" << e[36] << "--|" << vt[28] << "|  " 
        << vl[10] << "  |" << vt[29] << "|" << endl;
    
    /*
    
      |         |         |         |         |         |
    37        38   11   39        40   12   41        42
     |         |  ENERGY |         |  WIFI   |         |
    |30|--43--|31|   8  |32|--44--|33|  12  |34|--45--|35|
    
    */
    
    if (con.tiles[8].hasGeese()) {
        cout << "  |  GEESE  |         |         |         |         |" << endl;
    } else if (con.tiles[9].hasGeese()) {
        cout << "  |         |         |  GEESE  |         |         |" << endl;
    } else if (con.tiles[10].hasGeese()){
        cout << "  |         |         |         |         |  GEESE  |" << endl;
    } else {
        cout << "  |         |         |         |         |         |" << endl;
    }
    cout << " " << e[37] << "        " << e[38] << "   11   " << e[39] << "        " 
        << e[40] << "   12   " << e[41] << "        " << e[42] << endl;
    cout << "  |         |" << t[11] << "|         |" << t[12] << "|         |" << endl;
    cout << "|" << vt[30] << "|--" << e[43] << "--|" << vt[31] 
        << "|  " << vl[11]<< "  |" << vt[32] << "|--" << e[44] << "--|" << vt[33] << "|  " 
        << vl[12] << "  |" << vt[34] << "|--" << e[45] << "--|" << vt[35] << "|" << endl;
        
    /*
    
      |         |         |         |         |         |
     46   13   47        48   14   49        50   15   51
      |  ENERGY |         |  WIFI   |         |  GLASS  |
    |36|   5  |37|--52--|38|  11  |39|--53--|40|   4  |41|
    
    */
    
    if (con.tiles[11].hasGeese()) {
        cout << "  |         |  GEESE  |         |         |         |" << endl;
    } else if (con.tiles[12].hasGeese()) {
        cout << "  |         |         |         |  GEESE  |         |" << endl;
    } else {
        cout << "  |         |         |         |         |         |" << endl;
    }
    cout << " " << e[46] << "   13   " << e[47] << "        " << e[48] << "   14   " << e[49] 
        << "        " << e[50] << "   15   " << e[51] << endl;
    cout << "  |" << t[13] << "|         |" << t[14] << "|         |" << t[15] << "|" << endl;
    cout << "|" << vt[36] << "|  " << vl[13] << "  |" << vt[37] << "|--" << e[52] << "--|" << vt[38] << "|  " 
        << vl[14] << "  |" << vt[39] << "|--" << e[53] << "--|" << vt[40] << "|  "  
        << vl[15] << "  |" << vt[41] << "|" << endl;
        
    /*
    
      |         |         |         |         |         |
     54        55   16   56        57   17   58        59
      |         |  WIFI   |         |  GLASS  |         |
    |42|--60--|43|   6  |44|--61--|45|   9  |46|--62--|47|
    
    
    */
    
    if (con.tiles[13].hasGeese()) {
        cout << "  |  GEESE  |         |         |         |         |" << endl;
    } else if (con.tiles[14].hasGeese()) {
        cout << "  |         |         |  GEESE  |         |         |" << endl;
    } else if (con.tiles[15].hasGeese()){
        cout << "  |         |         |         |         |  GEESE  |" << endl;
    } else {
        cout << "  |         |         |         |         |         |" << endl;
    }
    cout << " " << e[54] << "        " << e[55] << "   16   " << e[56] << "        " << e[57] << "   17   " 
        << e[58] << "        " << e[59] << endl;
    cout << "  |         |" << t[16] << "|         |" << t[17] << "|         |" << endl;
    cout << "|" << vt[42] << "|--" << e[60] << "--|" << vt[43] 
        << "|  " << vl[16]<< "  |" << vt[44] << "|--" << e[61] << "--|" << vt[45] << "|  " 
        << vl[17] << "  |" << vt[46] << "|--" << e[62] << "--|" << vt[47] << "|" << endl;
    
    /*
    
                |         |         |         |
               63        64   18   65        66
                |         |  GLASS  |         |
              |48|--67--|49|   9  |50|--68--|51|
    
    */
    
    if (con.tiles[16].hasGeese()) {
        cout << "            |  GEESE  |         |         |" << endl;
    } else if (con.tiles[17].hasGeese()) {
        cout << "            |         |         |  GEESE  |" << endl;
    } else {
        cout << "            |         |         |         |" << endl;
    }
    cout << "           " << e[63] << "        " << e[64] << "   18   " << e[65] << "        " << e[66] << endl;
    cout << "            |         |" << t[18] << "|         |" << endl;
    cout << "          |" << vt[48] << "|--" << e[67] << "--|" << vt[49] << "|  " << vl[18] 
        << "  |" << vt[50]  << "|--" << e[68] << "--|" << vt[51] << "|" << endl;
        

    if (con.tiles[18].hasGeese()) {
	cout << "                      |  GEESE  |" << endl;
    } else {
        cout << "                      |         |" << endl;
    } 
    /*
    
                         69        70
                          |         |
                        |52|--71--|53|
    
    */
    cout << "                     " << e[69] << "        " << e[70] << endl;
    cout << "                      |         |" << endl;
    cout << "                    |" << vt[52] << "|--" << e[71] << "--|" << vt[53] << "|" << endl;
}


View::View(Controller& con) {
    
    // Convert the number(int) that represents the type of resource to string and surround it with
    // a number of spaces according to the layout.
    // Collect the type of resource of each tile into an array of string "t".
    // Note: 0 representing BRICK, 1 representing ENERGY, 2 representing GLASS,
    //  3 representing HEAT, 4 representing WIFI, and 5 representing PARK.
    for (int i = 0; i < 19; ++i) {
        int type = con.tiles[i].getType();
        if (type == 0) {
            t.emplace_back("  BRICK  ");
        } else if (type == 1) {
            t.emplace_back(" ENERGY  ");
        } else if (type == 2) {
            t.emplace_back("  GLASS  ");
        } else if (type == 3) {
            t.emplace_back("  HEAT   ");
        } else if (type == 4) {
            t.emplace_back("  WIFI   ");
        } else { // type == 5
            t.emplace_back("  PARK   ");
        }
    }
    
    
    // Convert the number(int) that represents the tile value to string and might
    // add one space at the front of it according to the layout.
    // Collect the tile value of each tile into an array of string "vl".
    for (int i = 0; i < 19; ++i) {
        int n = con.tiles[i].getVal();
        if (n == 7) {
            vl.emplace_back("  ");
            continue;
        }
        if (n < 10) {
            string value = to_string(n);
            string space = " ";
            vl.emplace_back(space + value);
        } else {
            vl.emplace_back(to_string(n));
        }
    }
    
    
    // Collect the state of each vertex into an array of string "vt".
    // If there is a building on a vertex, the vertex is represent by 
    // first character of the colour of the owner  followed by
    // the first character of the name of the building.
    // If there is no building on a vertex, the vertext is represent by
    // the original number and we might add one space at the front of it according to the layout.
    for (int i = 0; i < 54; ++i) {
        if (con.vertices[i].returnOwner() == "") { // if this vertex hasn't own by anyone.
            if (i < 10) {
                string num = to_string(i);
                string space = " ";
                vt.emplace_back(space + num);
            } else {
                vt.emplace_back(to_string(i));
            }
            
        } else { // if this vertex has own by someone.
            string building = con.vertices[i].returnBuilding();
            string owner = con.vertices[i].returnOwner();
            vt.emplace_back(owner + building);
        }
    }
    
    
    // Collect the state of each edge into an array of string "e".
    // If there is a road on a edge, the edge is represent by 
    // first character of the colour of the owner followed by ‘R’ for “Road”.
    // If there is no road on a edge, the edge is represent by
    // the original number and we might add one space at the front of it according to the layout.
    for (int i = 0; i < 72; ++i) {
        if (con.edges[i].owner >= 0) { // if road is built on this edge.
            string color = con.edges[i].hasRoad(); // get the owner of this road.
            string r = "R";
            e.emplace_back(color + r);
        } else { // if no road on this edge.
            if (i < 10) { // "1" => " 1"
                string num = to_string(i);
                string space = " ";
                e.emplace_back(space + num);
            } else {
                e.emplace_back(to_string(i));
            }
        }
    }
}


