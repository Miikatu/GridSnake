#ifndef SNAKE_H 
#define SNAKE_H 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <list>
class Snake{
public:
    Snake();
    float speed{1};
    int dir={0};
    int size={1};
    float hitbox={25.f};
    sf::Sprite head;
    sf::Texture headTexture;
    sf::Texture bodyTexture;
    sf::Sprite skin;
    std::deque<sf::Sprite> cq;
    std::deque<sf::Sprite> visibleSeqments;
    std::list<sf::Sprite> body;
    sf::Vector2<float> velocity{ 0.1f,0.0f};
   
};

#endif
