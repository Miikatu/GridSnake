#ifndef GAME_H 
#define GAME_H
#include "Snake.h"
#include <iostream>
#include <forward_list>
#include <cmath>

class Game //TODO Move snake container a sepereate class
{   
public:
    Game();
    
    void run();
    void directionOnKeyPressed(char input);
    void move(sf::Time deltaTime);
    void move();
    sf::Time deltaTime;
private:
    Snake* snake = new Snake();
    char input;
    int windowWidth{715};
    int windowHeight{715};
    sf::RenderWindow window;
    
    enum directionKey{ DOWN,UP,LEFT,RIGHT};
    
    //Grid
    //
    std::forward_list<sf::RectangleShape> verticalLines;
    //std::list<sf::RectangleShape> verticalLines;
    std::list<sf::RectangleShape> horizontalLines;
    sf::RectangleShape border;
    sf::Sprite background;
    sf::Texture texture;
    //Apple container
    //
    std::vector<sf::CircleShape> apples;
    void eventListener();
    void render();
    void render(sf::Clock gameClock);
    void collisionCheck();
    void boundCheck();
};

#endif
