#include "Util.h"

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
}//directionOnKeyPressed(char,vector)

void saie(){
    std::cout<<"Inside Thread"<<std::endl;
}

