#include <SFML/Graphics.hpp>
#include <iostream>
#include <pthread.h>
#include "include/Game.h"

int main(){
    //Create instance of Game
    Game game;
    sf::Thread gameThread(&Game::run,&game);
    gameThread.launch();
    
    //Example of threading a class --> sf::Thread thread(&MyClass::func, &object);

    return 0;

}
