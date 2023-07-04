#include "Game.c++"

//g++ -c main.c++ "SFML"/include
//g++ main.o -o main -L "SFML"/lib -lsfml-graphics -lsfml-window -lsfml-system
//c++23
int main(){
    std::cout << "Versione di SFML: " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;
    
    Game game;
    game.run();
    return 0;
}