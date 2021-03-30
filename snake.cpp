#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;

const int width = 40;
const int height = 40;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; // snail coordinates
int nTail;

enum eDirection {STOP = 0, LEFT,RIGHT,UP,DOWN}; //controls for snake
eDirection dir;


    //set fruit position and snake position
    void setup(){
        gameOver = false;
        dir = STOP;
        x = width / 2;
        y = width / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }

    //draw the map
    void draw(){
        system("cls");

        for(int i = 0; i < width+2; i++)
            cout << "#";
        std::cout << endl;

        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                if (j == 0){
                    std::cout << "|";
                }
                if(i == y && j == x){
                    std::cout << "O";
                
                } else if (i == fruitY && j == fruitX) {
                    std::cout << "F";
                } else {
                    bool segment = false;
                    for(int l = 0; l < nTail; l++){
                        if (tailX[l] == j && tailY[l] == i){
                            std::cout << "o";
                            segment = true;
                        };
                    }
                    
                    if(!segment){
                        std::cout << " ";
                    }

                }
                if(j == width-1) {
                    std::cout << "|";
                }

            }
            std::cout << endl;
        }

        for(int i = 0; i < width+2; i++)
            cout << "#";
        std::cout << endl;

        //display score
        std::cout << " Score: " << score << endl;

    }

    //set snake direction
    void movement(){
        if(_kbhit()){
            switch(_getch()){
                case 'a':
                    dir = LEFT;
                    break;

                case 'w':
                    dir = UP;
                    break;

                case 's':
                    dir = DOWN;
                    break;

                case 'd':
                    dir = RIGHT;
                    break;

                case 'x':
                    gameOver = true;
                    break;

            }
        }
    }

    //update snake direction
    void movementUpdate(){

        // make tail and coordinate tail
        int prevX = tailX[0];
        int prevY = tailY[0];
        int tX, tY;
        tailX[0] = x;
        tailY[0] = y;

        for(int i = 1; i < nTail; i++){
            tX = tailX[i];
            tY = tailY[i];

            tailX[i] = prevX;
            tailY[i] = prevY;

            prevX = tX;
            prevY = tY;
        }

        switch(dir){
            case STOP:
                break;
            
            case LEFT:
                x--;
                break;
            
            case RIGHT:
                x++;
                break;

            case UP:
                y--;
                break;
            
            case DOWN:
                y++;
                break;

            default:
                break;
        }
        //allow player to move through left and right walls
        if(x >= width){
            x = 0;
        } else if ( x < 0) {
            x = width -1;
        }

        if(y >= height){
            y = 0;
        } else if ( y < 0) {
            y = height -1;
        }


        // check for game over
        // if(x > width || x < 0 || y > height || y < 0){
        //     gameOver = true;
        // }

        //check if snake hit itself
        for(int i = 0; i < nTail; i++){
            if(tailX[i] == x && tailY[i] == y){
                gameOver = true;
            }
        }

        //check if snake takes fruit
        if(x == fruitX && y == fruitY){
            nTail++;
            score += 10;
            fruitX = rand() % width;
            fruitY = rand() % height;

        }
    }

    // initialize game
    int main(){
        setup();

        while(!gameOver){
            draw();
            movement();
            movementUpdate();
            //sleep(10);
        }

        return 0;
    }
