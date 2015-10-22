//Austin Willis
//Connect 4
//CS375
#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string> 
enum rec_type { PLAYERREC };

struct keystr { size_t id; rec_type type; };
struct playerrec { size_t id; char name[15]; int wins; int loss; int tie; };

class Board
{
private:
    int gameboard[6][7];
 
    int arrow;

    int player;

    std::string p1name;

    std::string p2name;

    int mode;

    std::string player1;

    std::string player2;

public:
    Board() { 
        for (int i = 0; i < 7; i++) {
	    for (int x=0; x < 6; x++) {
	    	gameboard[x][i] = 0;
 	    }
	}
	arrow = 0;
	player = 1;
    }
    void setSpace(int col, int player);

    void setmode(int n);

    void setpname(int player, std::string name);

    std::vector<int> getAvailableCols();

    void play();

    bool checkWin(int player);

    bool checkrow(int row, int player);

    bool checkcol(int col, int player);

    bool checkangle(int row, int col, int player);

    bool checkangle2(int row, int col, int player);

    void printBoard();

    void modeop();

    void recordgame(int result, int player);

    void displayrecord();

    void reset();

    void printArrow();

    int getSpace(int x, int y) { return gameboard[x][y]; }

    char tochar(int x, int y);
};
 
#endif
