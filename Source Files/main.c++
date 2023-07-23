#include "Game.c++"

//g++ -c main.c++ "SFML"/include
//g++ main.o -o main -L "SFML"/lib -lsfml-graphics -lsfml-window -lsfml-system
int main(){
    cout << "Versione di SFML: " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << endl;
    
    Game game;
    game.run();
    return 0;
}