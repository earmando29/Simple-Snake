#include <iostream>
#include <ncurses.h>
#include <cstdlib>  
#include <unistd.h>
#include <ctime>
#include "functions.h"

using namespace std;
#define KEY_UP 0403 
#define KEY_DOWN 0402 
#define KEY_LEFT 0404 
#define KEY_RIGHT 0405 

// RUN FILE: make && ./main
// cd /Users/armandoespinoza/documents/vs_code/C++/school/snake

int main(){
    do{
        Setup(); // INITIALIZE
        
        while (!gameOver){ // GAME
            display();
            input();
            logic();
        }

        while(!(getch()==10)){ // END SCREEN
            clear();

            attron(COLOR_PAIR(1));
            mvprintw(height / 2 - 1, width / 2 + 8, "DEAD");
            attroff(COLOR_PAIR(1));
            
            mvprintw(height / 2, width / 2, "YOUR FINAL SCORE: %d", score );

            attron(A_REVERSE);
            mvprintw(height / 2 + 3, width / 2, "PRESS ENTER TO CONTINUE");
            attroff(A_REVERSE);
            // refresh();
        } 
        
        attron(A_REVERSE | COLOR_PAIR(3));
        mvprintw(height / 2 + 5, width / 2, "PRESS Y TO PLAY AGAIN");
        mvprintw(height / 2 + 6, width / 2, "PRESS N TO PLAY EXIT"); 
        attroff(A_REVERSE | COLOR_PAIR(3));
        cbreak();
        
        while (!(playAgain = getch()) || (playAgain != 'n' && playAgain != 'y')){
            attron(A_REVERSE | COLOR_PAIR(1));
            mvprintw(height / 2 + 7, width / 2, "PLEASE ENTER 'Y' or 'N'");
            attroff(A_REVERSE | COLOR_PAIR(1));
        }
        
        refresh();
    }while(playAgain=='y');

    endwin();   // Ends the window
    return 0;
}