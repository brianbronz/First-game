#include "Game.c++"

//g++ -c main.c++ "SFML"/include
//g++ main.o -o main -L "SFML"/lib -lsfml-graphics -lsfml-window -lsfml-system
int main(){
    Game game;
    game.run();
    return 0;
}