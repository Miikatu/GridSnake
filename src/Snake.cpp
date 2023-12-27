#include "Snake.h"

Snake::Snake(){
    
    //Load textures
    //
    if (!headTexture.loadFromFile("./assets/GridSnake_head.png"))
    { } 
    if (!bodyTexture.loadFromFile("./assets/snake_body_3d.png"))
    { } 
    head.setTexture(bodyTexture);
    skin.setTexture(bodyTexture);
    head.setScale(sf::Vector2f(0.025f,0.025f));
    skin.setScale(sf::Vector2f(1.5f, 1.0f)); // absolute scale factor
    //skin.scale(sf::Vector2f(1.5f, 3.f)); // factor relative to the current scale
    // skin.setTextureRect(sf::IntRect(1000, 1000, 3200, 3200));

    //Create snake head
    head.setPosition(30,85);
    //head.setFillColor(sf::Color::Green);
    sf::Rect<float> size = head.getLocalBounds();
    head.setOrigin(sf::Vector2f(size.width/2,size.height/2));
    //head.setOrigin(head.getRadius(),head.getRadius()); 
    
    cq.push_front(head);
    
}