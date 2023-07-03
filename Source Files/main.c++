#include <iostream>
#include "Game.c++"
#include <cstdlib>
#include <vector>
#include <ctime>
#include <sstream>
#include <map>

using namespace std;
//g++ -c main.c++ "SFML-2.6.0"/include
//g++ main.o -o main -L "SFML-2.6.0"/lib -lsfml-graphics -lsfml-window -lsfml-system
int main(){
    Game game;
    game.run();
    return 0;
}