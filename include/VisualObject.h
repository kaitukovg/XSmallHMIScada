#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <VariableDatabase.h>

class VariableDatabase;

class VisualObject {
protected:
    float x, y;                  
    
    std::string name;            
    
    VariableDatabase* database;  

public:
    VisualObject(float x, float y, const std::string& name, VariableDatabase* db);
    
    virtual ~VisualObject() = default;
    
    virtual void draw(sf::RenderWindow& window) = 0;
    
    virtual void update() = 0;

    virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) {};

    void setPosition(float newX, float newY);
    
    std::string getName() const;
};


#endif
