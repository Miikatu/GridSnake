#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <forward_list>
#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <cmath>
#include <pthread.h>

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

Game::Game(): window(sf::VideoMode(windowWidth,windowHeight),"Play Snake .02"){
    std::cout<<"Construction done!"<< std::endl;
    //Window border
    //
    border.setSize(sf::Vector2f(windowWidth,windowHeight));
    border.setFillColor(sf::Color::Blue);
    border.setPosition(0,0);
    
    //Add lines to grid
    sf::RectangleShape lineV(sf::Vector2f(5,windowHeight));
    for(int i{0};i<windowWidth;i+=55){
        lineV.setPosition(i,0);
        verticalLines.push_front(lineV);
    }
    sf::RectangleShape lineH(sf::Vector2f(windowWidth,5));
    for(int i{0};i<windowHeight;i+=55){
        lineH.setPosition(0,i);
        horizontalLines.push_front(lineH);
    }
    //Add background Texture
    
    if (!texture.loadFromFile("./assets/floor_sonic.png"))
    { } 
      //texture.loadFromFile("./assets/GridSnake_floorTest.png");
    //texture.setRepeated(true); 
    texture.setRepeated(true);
    background.setTexture(texture);
//    background.setColor(sf::Color(255, 255, 255, 128));
    background.setOrigin(sf::Vector2f(0,0));
    background.setTextureRect(sf::IntRect(0,0, 500, 500));
    background.setScale(sf::Vector2f(2,2));
    
    
    
    //Add apples to map
    //
    for(int i=0 ;i <100;i++){
        sf::CircleShape apple;
        int randomX=rand()%13+1;//Random int between 1-13
        int randomY=rand()%13+1;//Random int between 1-13
        apple.setRadius(10);
        apple.setOrigin(apple.getRadius(),apple.getRadius());
        apple.setPosition(30+randomX*55,30+randomY*55);        
        apple.setOrigin(apple.getRadius(),apple.getRadius());
        apple.setFillColor(sf::Color::Red);
        apples.emplace_back( apple);
    }
}

void Game::eventListener(){
    sf::Event event;
        //while pending events
        while (window.pollEvent(event)) 
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            
                case sf::Event::Resized:
                    windowHeight=window.getSize().y;
                    windowWidth=window.getSize().x;
                    break;
                
                case sf::Event::TextEntered:
                    directionOnKeyPressed(static_cast<char>(event.text.unicode));
                    break;
                    
                case sf::Event::KeyPressed:
                    if(event.key.code==sf::Keyboard::Escape)
                        window.close();
                    break;
                        
                default:
                    break;
            }
            
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
}
void Game::render(){
    window.clear();
    
    //Draw window border
    //window.draw(border); 


    //Draw background
    window.draw(background);
    
    //Draw Grid
    for (const auto& e : verticalLines){window.draw(e);}
    for (const auto& e : horizontalLines){window.draw(e);}  
         
    //snake->head.setTexture(snake.headTexture);     
    window.draw(snake->head);
    
    //Draw Snake
    //
    
    //snake->cq.push_front(snake.head);        
    while((int)snake->body.size() >= snake->size){
        snake->body.pop_back();
    }    /*
    //index rendering
    
    int index{0};
    for(int i=index; i < (int)snake->body.size();i++){
        window.draw(snake->body. at(i));
    };
    
    std::list<sf::CircleShape>::iterator it;
    for (it = snake->body.begin(); it != snake.body.end();++it){
        window.draw(it);
    }*/
    /**/
    
   int i =0;
    std::for_each(snake->body.begin(),snake->body.end(),[&](auto& segment){
        //if(index % 200==0 ){}
            //std::cout<<index<<". size: "<<cq.size()<<std::endl;
        if(i<=snake->size){
             //snake->head.setTexture(snake.bodyTexture); 
        }
        else{}
           // snake->head.setTexture(snake.headTexture);
        window.draw(segment);
        i++;
        //index++;
    });
    
    //Draw Apples
    //Program exited

    std::for_each(apples.begin(),apples.end(),[&](auto& apple){
        window.draw(apple);
    });
    window.display();
}
void Game::boundCheck(){
    //TODO: Switch case
    
    //X-axis check
    //
    if(snake->head.getPosition().x<=0){
        snake->head.setPosition(windowWidth-25,snake->head.getPosition().y);
    }
    if(snake->head.getPosition().x>=window.getSize().x){
       snake->head.setPosition((float)30,snake->head.getPosition().y);
    }
    //Y-axis check
    //
    if(snake->head.getPosition().y<=0){
       snake->head.setPosition((float)snake->head.getPosition().x,window.getSize().y-25);
    }
    if(snake->head.getPosition().y>=window.getSize().y){
       snake->head.setPosition((float)snake->head.getPosition().x,30);
    }
}

void Game::collisionCheck(){
    
    //Collision with apples
    //
    std::for_each(apples.begin(),apples.end(),[&](auto& apple){
        sf::Vector2<float> distanceVector{snake->head.getPosition().x-apple.getPosition().x,snake->head.getPosition().y-apple.getPosition().y};
        float distanceLength{std::sqrt(distanceVector.x*distanceVector.x+distanceVector.y*distanceVector.y)};
        if(distanceLength<=snake->hitbox){
            apple.setPosition(-10,-10);
            snake->size+=1;
        }
    });
    
    //Collision with body 
    //
    int i=0;
    std::for_each(snake->body.begin(),snake->body.end(),[&](auto& segment){
        if(i==0){
         //Snake head cannot collide with itself
         i++;
        }
        else if(snake->head.getPosition().x==segment.getPosition().x && snake->head.getPosition().y==segment.getPosition().y){
           snake->size=1;
        }                                                               
    });
    
    boundCheck();
}
void Game::move(){
    //Movement of snake
    switch(snake->dir){
        case UP:
            snake->head.move(0,-55.0); break;
        case DOWN:
            snake->head.move(0,55.0); break;
        case LEFT:
            snake->head.move(-55.0,0); break;
        case RIGHT:
            snake->head.move(55.0,0); break;
    }
    //snake->
    snake->body.push_front(snake->head);
}
void Game::move(sf::Time deltaTime){
    switch(snake->dir){
        case UP:
            snake->head.move(0,-100.10); break;
        case DOWN:
            snake->head.move(0,100.10); break;
        case LEFT:
            snake->head.move(-100.10,0); break;
        case RIGHT:
            snake->head.move(100.10,0); break;
    }
    //Movement with deltaTime
    //
    /*switch(dir){
        case UP:
            velocity.x= 0.0f;
            velocity.y= -0.1f; break;
        case DOWN:
            velocity.x= 0.0f;
            velocity.y= 0.1f; break;
        case LEFT:
            velocity.x= -0.1f;
            velocity.y= 0.0f; break;
        case RIGHT:
            velocity.x= 0.1f;
            velocity.y= 0.0f; break;
    }
    velocity=velocity*speed;
    head.move(velocity.x*deltaTime.asSeconds(),velocity.y*deltaTime.asSeconds());*/
}
void Game::run(){
    
    std::cout<<"Running game inside a Thread"<< std::endl;
    sf::Clock deltaClock;
    sf::Clock gameClock;
    
    int framesPerSecond{15};
    int skipTicks{125};
    sf::Int32 sleepTime{0};
    //bool game_is_running = true;
    //GameLoop
    //
    float nextGameTick= deltaClock.getElapsedTime().asMilliseconds();
    
    while(window.isOpen()){
       
        eventListener();
        collisionCheck();

        if(gameClock.getElapsedTime().asSeconds()>0.2f){ }
        
        move();
        gameClock.restart();    
        render();
        nextGameTick+=skipTicks;
        sleepTime=nextGameTick-deltaClock.getElapsedTime().asMilliseconds();
        
        if(sleepTime>=0){
            //sleepTime;
            sf::sleep(sf::milliseconds(sleepTime));
            //sleep(sleepTime);
        }
        else {
            //myöhässä
        }
        
        framesPerSecond++;
    }
}//Game::run

void Game::directionOnKeyPressed(char input){
    switch(input)
    {
        //direction index 0 = x | index 1 = y
        case 'w':
            //direction.at(0)=0.00;       //x
            //direction.at(1)=-0.05f;     //y
            snake->dir=UP;
            snake->head.setRotation(90.f);
            break;
        
        case 'a':
            //direction.at(0)=-0.05;  
            //direction.at(1)=0.00f;
            snake->dir=LEFT;
            snake->head.setRotation(0);
            break;

        case 's':
            //direction.at(0)=0.00;   
            //direction.at(1)=0.050;  
            snake->dir=DOWN;
            snake->head.setRotation(-90);
            break;
            
        case 'd':
            //direction.at(0)=0.050;  
            //direction.at(1)=0.00f;
            snake->dir=RIGHT;
             snake->head.setRotation(180);
            break;
        case 'u':
                snake->speed+=100; break;
        case 'y':
                if(snake->size>1){
                snake->size-=1;} break;
        case 'g':
            try {
                snake->size+=1;

                }
            catch(const std::exception& e){
                std::cout<<e.what()<<std::endl;
            }
            break;
    }
}; //Game::directionOnKeyPressed()


std::vector<float> directionOnKeyPressed(char input, std::vector<float> direction)
{
    switch(input)
    {
        //direction index 0 = x | index 1 = y
        case 'w':
            direction.at(0)=0.00;   //x
            direction.at(1)=-0.05f;  //y
            break;    
        
        case 'a':
            direction.at(0)=-0.05;  
            direction.at(1)=0.00f; 
            break;

        case 's':
            direction.at(0)=0.00;   
            direction.at(1)=0.050;   
            break;
            
        case 'd':
            direction.at(0)=0.050;  
            direction.at(1)=0.00f;
            break;        
    }
    return direction;
}
void saie(){
    std::cout<<"Inside Thread"<<std::endl;
}

int main()
{   
    //Create instance of Game
    
    Game game;
    sf::Thread gameThread(&Game::run,&game);
    gameThread.launch();
    
    //Example of threading a class --> sf::Thread thread(&MyClass::func, &object);

    return 0;

}
