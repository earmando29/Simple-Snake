#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;
void borderArt(char[]);
void isGameOver();
void fruitArt();
void snakeArt();
int sLength = 1;
bool gameOver = false; //Determines when the game ends

void isGameOver(){

}

void fruitArt(){

}

void borderArt(char snake[20][77]){ 
 int i,j,k; 
 for(k=0;k<79;k++) 
 cout<<"-"; 
 cout<<endl; 
 for(i=0;i<20;i++) 
 { 
  cout<<"|"; 
  for(j=0;j<77;j++) 
  { 
   cout<<snake[i][j]; 
  } 
  cout<<"|"<<endl; 
 } 
 for(k=0;k<79;k++) 
 cout<<"-"; 

}

int main(){
    char snake[20][77]
    borderArt(snake);
    return 0;
}