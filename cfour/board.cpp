//Austin Willis
//Connect 4
//CS375
#include "board.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sstream>
#include <cstring>
#include <string>
#include <string.h>
#include <ncurses.h>
#include <gdbm.h>
#include <functional>
 
	//sets the highest available space on a column to be owned by a player
    void Board::setSpace(int col, int player) {
	for (int i = 0; i < 6; i++) {
	   if (gameboard[i][col] == 0) {
		gameboard[i][col] = player;
		break;
	    }
        }
    }

	//returns a vector containing all columns that are not full
    std::vector<int> Board::getAvailableCols() {
	std::vector<int> cols;
	for (int i = 0; i < 7; i++) {
	    if (gameboard[5][i] == 0)
		cols.push_back(i);
	}
	return cols;
    }

	//sets the board back to it's original state for a new game
    void Board::reset() {
	for (int i = 0; i < 6; i++)
	    for (int j = 0; j < 7; j++)
		gameboard[i][j] = 0;
	arrow = 0;
	player = 1;
    }
	
	//prints out the board
    void Board::printBoard() {
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	clear();
	this->printArrow();
	mvprintw(2,15,"---------------\n");
	for (int i = 0; i < 6; i++) {
	    for (int j = 0; j < 7; j++) {
		if (j == 0)
		    mvprintw(3 + i, 15, "|");
		if (gameboard[5 - i][j] == 2)
			attron(COLOR_PAIR(2));
		mvprintw(3 + i, 15 + j * 2 + 1, "%c", this->tochar( 5 - i, j));
		attron(COLOR_PAIR(1));
		mvprintw(3 + i, 15 + j * 2 + 2, "|");
	    }
        }
	mvprintw(9,15,"---------------\n");
	mvprintw(10, 0, "Use arrow keys to go left and right, Press the down arrow key to drop your piece");
	mvprintw(LINES - 3, 0, "Press F1 to quit the game.");
	if (player == 1)
	    mvprintw(11, 0, "%s's turn.", p1name.c_str());
	else mvprintw(11, 0, "%s's turn.", p2name.c_str());
	refresh();
     }

	//prints the line over the currently selected column
    void Board::printArrow() {
	mvprintw(0,15 + this->arrow * 2 + 1,"|");
	mvprintw(1,15 + this->arrow * 2 + 1, "|");
    }

	//runs the routine to take input from players
    void Board::play() {
	int c;
	bool play = true;
	std::vector<int> avail;
	if (mode == 2) {
	    this->displayrecord();
	    play = false;
	} else {
	    this->printBoard();
	}
	while((c = getch()) && play && c != KEY_F(1))
	{   
	avail = this->getAvailableCols();
	switch(c)
	    {	case KEY_RIGHT:
		{
			arrow+=1;
			if (arrow > 6)
			    arrow = 6;
			while (std::find(avail.begin(), avail.end(), arrow) == avail.end())
				arrow--;
			this->printBoard();
				break;
		}
		case KEY_LEFT:
		{
			arrow = arrow - 1;
			if (arrow < 0)
			    arrow = 0;
			while (std::find(avail.begin(), avail.end(), arrow) == avail.end())
				arrow++;
			this->printBoard();
			break;
		}
		case KEY_DOWN:
		{
			//place the players piece
		    this->setSpace(arrow, player);	
		    if (this->checkWin(this->player))
	    	    	play = false;
	             avail = this->getAvailableCols();
			//end the game if all rows are full
	            if (avail.empty())
	    	    	play = false;
			//routine for the end of the game
		    if (!play) {
			this->printBoard();
			move(10,0);
			clrtoeol();
				//if game is tied
			if (avail.empty()) {
			    mvprintw(10, 0, "Tie game!");
			    this->recordgame(1, player); //record tie
			    if (mode == 1) { //record results for second player if human vs human
				if (player == 1) {
				this->recordgame(1, 2);
				} else { this->recordgame(1, 1); } }
			} else {
			    if (player == 1) //print winner
			        mvprintw(10, 0, "%s won!", p1name.c_str());
			    else mvprintw(10, 0, "%s won!", p2name.c_str());
			    this->recordgame(2, player);
			    if (mode == 1) {  //record loss for other player if human vs human
				if (player == 1) {
				this->recordgame(3, 2);
				} else { this->recordgame(3, 1); } }
			}
			mvprintw(11, 0, "Press any key to return to the menu.");
		    } else {
		        this->modeop();
		        this->printBoard();
		    }
		    if (mode == 0 && this->checkWin(2)) {
			mvprintw(10, 0, "The computer won!");
			play = false;
			this->recordgame(3, 1); //record loss
		    }
		    break;
		}
	    }
	}	
     }

	//added results to the database file
     void Board::recordgame(int result, int player) {
	//make filename for file in home directory
        int myuid; 
        struct passwd *mypasswd; 
        char FileName[30]; 

        myuid = getuid(); 
        mypasswd = getpwuid(myuid); 

        strcpy(FileName, mypasswd->pw_dir); 
        strcat(FileName, "/.cfour"); 

	GDBM_FILE dbf;
	datum key, content, datain;
	std::hash<std::string> hash_fn;
	struct keystr keydata;	
	struct playerrec p;
	struct playerrec p2;
	dbf = gdbm_open(FileName, 0, GDBM_WRCREAT, 0644, 0);
	//record players name
	if (player == 1) {
	    std::size_t length = p1name.copy(p.name,14);
            p.name[length]='\0';
        } else {
	    std::size_t length = p2name.copy(p.name,14);
            p.name[length]='\0';
	}
	//set initial player record for new player
	p.wins = 0;
	p.loss = 0;
	p.tie = 0;
	keydata.id = hash_fn(p.name);
	p.id = hash_fn(p.name);
	keydata.type = PLAYERREC;
	key.dptr = (char *)(&keydata);
	key.dsize = sizeof(keydata);
	if (dbf) {
	    //look for current record for player
	    datain = gdbm_fetch(dbf, key);
	    if (datain.dptr != NULL) {
                p2 = *((struct playerrec *)(datain.dptr));
		free(datain.dptr);
		//copy current record for player
		p.wins = p2.wins;
		p.loss = p2.loss;
		p.tie = p2.tie;
	    }
	//update player for newest game results
	if (result == 1)
	   p.tie ++;
	if (result == 2)
	   p.wins ++;
	if (result == 3)
	   p.loss ++;
	content.dptr = (char *)(&p);
	content.dsize = sizeof(p);

	gdbm_store(dbf, key, content, GDBM_REPLACE);
 	}
	gdbm_close(dbf);
     }

	//return char for whether space is owned or not
     char Board::tochar(int x, int y) {
	if (gameboard[x][y] == 0) {
	    return ' ';
      	}
	    return 'O';
    }

	//do operation for current game mode
    void Board::modeop() {
	std::vector<int> avail = this->getAvailableCols();
	//computer move
	if (mode == 0) {
	    this->setSpace(rand() % avail.size(), 2);
	}
	//change player
	if (mode == 1) {
	    if (std::find(avail.begin(), avail.end(), arrow) == avail.end())
		arrow = avail[0];
	    player++;
	    if (player > 2)
	    	player = 1;
	}	
    }
    //set mode from menu input
    void Board::setmode(int n) {
	this->mode = n;
    }
    // loop over spaces looking for connected 4
    bool Board::checkWin(int player) {
	for (int i = 0; i < 7; i++)
	    if (checkrow(i, player))
		return true;
	for (int i = 0; i < 6; i++)
	    if (checkcol(i, player))
		return true;
	for (int i = 0; i < 3; i++)
	    for (int j = 0; j < 4; j++)
		if (checkangle(i, j, player))
		    return true;
	for (int i = 3; i < 6; i++)
	    for (int j = 0; j < 4; j++)
		if (checkangle2(i, j, player))
		    return true;
	return false;
    }

    //search for all win cases at angles up to the right
    bool Board::checkangle(int row, int col, int player) {
	    if (gameboard[row][col] == player && 
		gameboard[row+1][col+1] == player &&
		gameboard[row+2][col+2] == player && 
		gameboard[row+3][col+3] == player)
		return true;
	return false;
    }

    //search all win cases for up to the left
    bool Board::checkangle2(int row, int col, int player) {
	    if (gameboard[row][col] == player && 
		gameboard[row-1][col+1] == player &&
		gameboard[row-2][col+2] == player && 
		gameboard[row-3][col+3] == player)
		return true;
	return false;
    }

    //search all win cases for horizontal wins
    bool Board::checkrow(int row, int player) {
	for (int i = 0; i < 4; i++) {
	    if (gameboard[row][i] == player && gameboard[row][i+1] == player &&
		gameboard[row][i+2] == player && gameboard[row][i+3] == player)
		return true;
	}
	return false;
    }

    //search all win cases for vertical wins
    bool Board::checkcol(int col, int player) {
	for (int i = 0; i < 3; i++) {
	    if (gameboard[i][col] == player && gameboard[i+1][col] == player &&
		gameboard[i+2][col] == player && gameboard[i+3][col] == player)
		return true;
	}
	return false;
    }

    //display contents of database file
    void Board::displayrecord() {
        int myuid; 
        struct passwd *mypasswd; 
        char FileName[30]; 

        myuid = getuid(); 
        mypasswd = getpwuid(myuid); 

        strcpy(FileName, mypasswd->pw_dir); 
        strcat(FileName, "/.cfour"); 
	clear();
	printw("Player : win-loss-tie\n");
	//char *homedir;
	//if ((homedir = getenv("HOME")) == NULL) {
   	//    homedir = getpwuid(getuid())->pw_dir;
	//}
	//strcat(homedir,"/.cfour");

	GDBM_FILE dbf;

	datum key, datain;
	
	struct keystr keydata;
	struct playerrec p;
	
	dbf = gdbm_open(FileName, 0, GDBM_READER, 0, 0);
	if (dbf) {
	key = gdbm_firstkey(dbf);

	while (key.dptr != NULL) {
	    keydata = *((struct keystr *)(key.dptr));

	    datain = gdbm_fetch(dbf, key);
	    p = *((struct playerrec *)(datain.dptr));
	    free(datain.dptr);
	    printw("%s : %d-%d-%d\n", p.name, p.wins, p.loss, p.tie);
	    key = gdbm_nextkey(dbf, key);
	}
	mvprintw(LINES - 3, 0, "Press any key to return to the menu.");
	refresh();
	free(key.dptr);
	}
	gdbm_close(dbf);
    }

    //set name of players from user input
    void Board::setpname(int player, std::string name) {
	if (player == 1)
	    this->p1name = name;
	else this->p2name = name;
    }
