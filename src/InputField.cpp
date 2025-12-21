#include "InputField.h"
#include "logger.h"

InputField::InputField(float x, float y, float width, float height,
                       sf::Font* font, unsigned int fontSize,
                       const std::string& name, VariableDatabase* db,
                       const std::string& varName)
    : VisualObject(x, y, name, db), 
      font(font),                   
      variableName(varName),         
      isActive(false),            
      inputText("") {             
    
    background.setPosition(x, y);                       
    background.setSize(sf::Vector2f(width, height));    
    background.setFillColor(sf::Color::White);          
    background.setOutlineColor(sf::Color::Black);       
    background.setOutlineThickness(1);                  
    

    text.setPosition(x + 5, y + 5);  
    text.setFont(*font);            
    text.setCharacterSize(fontSize); 
    text.setFillColor(sf::Color::Black);  
    text.setString(inputText);      
    
    if (!variableName.empty() && database) {
        database->subscribe(variableName, [this](double value) {
            this->update(); 
        });
    }
}


void InputField::draw(sf::RenderWindow& window) {
    window.draw(background); 
    window.draw(text);       
}

void InputField::update() {
    if (!variableName.empty() && database && !isActive) {
        double value = database->getVariable(variableName);
        inputText = std::to_string(value);  
        text.setString(inputText);          
    }
}

void InputField::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            setActive(contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
        }
    }
    
    if (isActive && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') { 
            if (!inputText.empty()) {
                inputText.pop_back();
            }
        } else if (event.text.unicode == '\r') {  
            setActive(false);            
            if (!inputText.empty() && !variableName.empty() && database) {
                try {
                    double value = std::stod(inputText);  
                    database->setVariable(variableName, value);
                    Logger::info("Input field set variable '" + variableName + "' to: " + inputText);
                } catch (const std::exception& e) {
                  
                    Logger::error("Invalid input: " + inputText);
                }
            }
        } else if (event.text.unicode < 128) { 
          
            inputText += static_cast<char>(event.text.unicode);
        }

        text.setString(inputText + (isActive ? "|" : ""));
    }
}

void InputField::setActive(bool active) {
    isActive = active;
    
    if (isActive) {
        background.setOutlineColor(sf::Color::Blue);  
        background.setOutlineThickness(2);        
        text.setString(inputText + "|");
    } else {
        background.setOutlineColor(sf::Color::Black);  
        background.setOutlineThickness(1);            
        text.setString(inputText);                   
        
        if (!inputText.empty() && !variableName.empty() && database) {
            try {
                double value = std::stod(inputText);  
                database->setVariable(variableName, value);
            } catch (const std::exception& e) {
                Logger::error("Invalid input in input field: " + inputText);
            }
        }
    }
}

bool InputField::contains(float pointX, float pointY) const {
    return pointX >= x && pointX <= x + background.getSize().x &&
           pointY >= y && pointY <= y + background.getSize().y;

}

