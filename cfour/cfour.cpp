//Austin Willis
//Connect 4
//CS375
#include <ncurses.h>
#include <menu.h>
#include "menu.h"
#include <new>
#include "board.h"
#include <cstring>
#include <stdlib.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4
#define WIDTH 30
#define HEIGHT 10
const char *choices[] = {
                        "Play against the computer",
                        "Play against a person",
                        "Display player records",
			"Exit"
                  };

std::string menu();

int main() {
	std::string selection;
	char str[40];
	//Make a new board
	Board b;
	while (selection != choices[3]) {
	    selection = menu();
		//routine for playing against a computer
	    if (selection == choices[0]) {
		b.setmode(0);
		clear();
		printw("Enter a name:");
		getstr(str);
		b.setpname(1, str);
	        mvprintw(LINES - 2, 0, "You Entered: %s", str);
 	        getch();
	    }
		//routine for playing another person
	    if (selection == choices[1]) {
		b.setmode(1);
		printw("Enter a name for Player 1:");
		getstr(str);
		b.setpname(1, str);
	        mvprintw(LINES - 2, 0, "You Entered: %s", str);
		move(0,0);
		printw("Enter a name for Player 2:");
		getstr(str);
		b.setpname(2, str);
		move(LINES - 2, 0);
		clrtoeol();
	        mvprintw(LINES - 2, 0, "You Entered: %s", str);
	 	getch();	
	    }
		//displaying database file
	    if (selection == choices[2]) {
		b.setmode(2);
	    }
		//exit
	    if (selection == choices[3]) {
		break;
	    }
	    b.play();
	    b.reset();
	    
        }	
	clear();
	endwin();
	return 0;
}
//Display meny and return the result
std::string menu()
{	ITEM **my_items;
	int c;	
	std::string selection;			
	MENU *my_menu;
        int n_choices, i;
	ITEM *cur_item;
	
	/* Initialize curses */	
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	clear();
        noecho();
	keypad(stdscr, TRUE);

	/* Initialize items */
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices[i], NULL);
	my_items[n_choices] = (ITEM *)NULL;

	/* Create menu */
	my_menu = new_menu((ITEM **)my_items);

	/* Post the menu */
	mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
	mvprintw(LINES - 2, 0, "Up and Down arrow keys to naviage");
	post_menu(my_menu);
	refresh();

	while((c = getch()))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 10: /* Enter */
				selection = std::string(item_name(current_item(my_menu)));
				unpost_menu(my_menu);
				for(i = 0; i < n_choices; ++i)
					free_item(my_items[i]);
				free_menu(my_menu);
				return selection;
		}
	}
	return std::string("null");	
}
	
