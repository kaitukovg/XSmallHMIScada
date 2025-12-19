#ifndef HMIPLAYER_H
#define HMIPLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include "VariableDatabase.h"  
#include "VisualObject.h"     

// Главный класс приложения 

class HmiPlayer {
private:
    sf::RenderWindow window;   
    VariableDatabase database; 
    std::vector<std::unique_ptr<VisualObject>> objects;  
    sf::Font font;             
    
public:
    HmiPlayer();

    // Инициализация
    bool initialize();

    
    void run();

    // Методы главного цикла
    void handleEvents(); 
    void update();        
    void render();  
    
    // Сохраняет демо-сцену в JSON файл
    bool saveSceneToJSON(const std::string& filename);
};


#endif

