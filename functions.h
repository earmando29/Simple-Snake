#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <iostream>
#include <ncurses.h>
#include <cstdlib>  
#include <unistd.h>
#include <ctime>
using namespace std;
#define KEY_UP 0403 
#define KEY_DOWN 0402 
#define KEY_LEFT 0404 
#define KEY_RIGHT 0405 

bool gameOver;
char playAgain = 'y';
const int width = 30; 
const int height = 15;
int xPos, yPos, nTail, xFruit, yFruit, score;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int tailX[100], tailY[100];

void Setup(){
    clear();
    srand (time(0));
    gameOver = false;
    initscr(); clear(); noecho(); cbreak(); // Initializes nCurses
    curs_set(0);
    start_color();
    gameOver = false;
    dir = STOP;
    xPos = width / 2;
    yPos = height / 2;
    nTail = 1;
    fill_n(tailX, 100, 0);
    fill_n(tailY, 100, 0);
    xFruit = (rand() % width)+1;
    yFruit = (rand() % height)+1;
    score = 0;
    char playAgain;
    init_pair(1,COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    
}


void display(){
    clear();
    for (int x = 0; x < width+2; x++){
        for (int y = 0; y < height+2; y++){
            if (x ==  0 || x == width+1) 
                mvprintw (y, x,  "#");
            
            else if (y == 0 || y == height+1)
                mvprintw (y, x,  "+");
            
            else if (x == xPos && y == yPos){
                attron(COLOR_PAIR(2));
                mvprintw(y, x, "O");
                attroff(COLOR_PAIR(2));
            }
            else if (x == xFruit && y == yFruit){
                attron(COLOR_PAIR(1));
                mvprintw(y, x, "@");
                attroff(COLOR_PAIR(1));
            }
            else{
                for (int k = 0; k < nTail; k++){
                    if (tailX[k] == x  && tailY[k] == y){
                        attron(COLOR_PAIR(2));
                        mvprintw(y, x, "o");
                        attroff(COLOR_PAIR(2));
                    }
                }
            }
        }
    }
    mvprintw(height + 3, 0, "SCORE: %d", score);
    attron(A_REVERSE);
    mvprintw(height + 5, 0, "Press 'P' at anytime to PAUSE");
    mvprintw(height + 6, 0, "Press 'Q' at anytime to QUIT");
    attroff(A_REVERSE);
    
    refresh(); // Prints/Displays all
}

void input(){
    keypad(stdscr, TRUE);
    halfdelay(1);   // Waits for user input, if no input it moves on

    int c = getch(); // Receives a KB input and reads it as a number (nCurses)

    switch (c) {
        case KEY_LEFT: if(dir==RIGHT){dir=RIGHT;} 
            else {dir = LEFT;}; break;
        
        case 'a': if(dir==RIGHT){dir=RIGHT;} 
            else {dir = LEFT;}; break;

        case KEY_RIGHT: if(dir==LEFT){dir=LEFT;} 
            else {dir = RIGHT;}; break;

        case 'd': if(dir==LEFT){dir=LEFT;} 
            else {dir = RIGHT;}; break;

        case KEY_UP: if(dir==DOWN){dir=DOWN;} 
            else {dir = UP;}; break;
        
        case 'w': if(dir==DOWN){dir=DOWN;} 
            else {dir = UP;}; break;

        case KEY_DOWN: if(dir==UP){dir=UP;} 
            else {dir = DOWN;}; break;

        case 's': if(dir==UP){dir=UP;} 
            else {dir = DOWN;}; break;
        
        case 'p': while(!(getch()=='p')){
            timeout(-1);} 
            for(int i = 3; i >= 0; i--){
                usleep(1000000);
                mvprintw(height / 2, width / 2, "%d", i);
                refresh();}
            ;timeout(1000); break;

        case 113: gameOver = true; break;
    }
}


void logic(){
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = xPos;
    tailY[0] = yPos;

    for (int i = 0; i < nTail; i++) // Places the tail behind the head
    {
        // Captures the last tail in the the Temp Prev
        prev2X = tailX[i];
        prev2Y = tailY[i];
        // Captures the tail to the old coords
        tailX[i] = prevX;
        tailY[i] = prevY;
        // Restores the last tail
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir){ // heads position
        case LEFT: xPos--; break;

        case RIGHT: xPos++; break;

        case UP: yPos--; break;

        case DOWN: yPos++; break;

        default: break;
    }

    if (xPos ==  0|| xPos == width+1 || yPos == 0 || yPos == height+1){
        gameOver = true;
    }

    if (xPos == xFruit && yPos == yFruit) { // Adds to the tail and replaces the fruit
        score++;
        xFruit = (rand() % width)+1;
        yFruit = (rand() % height)+1;
        for (int i = 1; i < nTail; i++)
        {
            while(xFruit == tailX[i] && yFruit == tailY[i]){
                xFruit = (rand() % width)+1;
                yFruit = (rand() % height)+1;
            }
        }
        
        nTail++;
    }

    for (int i = 1; i < nTail; i++){ // Checks if the head touches the tail
        if (tailX[i] == xPos && tailY[i] == yPos)
        {
            gameOver = true;
        }
    }
}

#endif