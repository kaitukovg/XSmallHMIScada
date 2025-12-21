#include "Image.h"
#include "logger.h"
#include <iostream>

Image::Image(float x, float y, float width, float height,
             const std::string& path, const std::string& name,
             VariableDatabase* db)
    : VisualObject(x, y, name, db), 
      imgWidth(width), imgHeight(height),  
      imagePath(path),                   
      textureLoaded(false) {           
    
    std::cout << "Try to load image from: " << path << std::endl;
    
    textureLoaded = loadTexture(path);
    
    sprite.setPosition(x, y);
    
    if (textureLoaded) {
        float scaleX = width / sprite.getLocalBounds().width;
        float scaleY = height / sprite.getLocalBounds().height;
        sprite.setScale(scaleX, scaleY);
        
        std::cout << "IMAGE IS LOADED FROM: " << path << std::endl;
    } else {
        std::cout << "FAILED TO LOAD THE IMAGE: " << path << std::endl;
    }
}

void Image::draw(sf::RenderWindow& window) {
    if (textureLoaded) {
        window.draw(sprite);
    } else {
        sf::RectangleShape placeholder(sf::Vector2f(imgWidth, imgHeight));
        placeholder.setPosition(x, y);
        placeholder.setFillColor(sf::Color(200, 200, 200));  
        placeholder.setOutlineColor(sf::Color::Black);      
        placeholder.setOutlineThickness(2);
        window.draw(placeholder);
        
        sf::Font font;
        if (font.loadFromFile("../assets/fonts/arial.ttf")) {
            sf::Text errorText;
            errorText.setFont(font);
            errorText.setString("Image not found");
            errorText.setCharacterSize(16);
            errorText.setFillColor(sf::Color::Black);
            errorText.setPosition(x + 10, y + imgHeight / 2 - 10);
            window.draw(errorText);
        }
    }
}

bool Image::loadTexture(const std::string& path) {
    std::vector<std::string> possiblePaths = {
        path,                      
        "../" + path,         
        "../../" + path,         
        "assets/images/logo.png", 
        "../assets/images/logo.png" 
    };
    
    for (const auto& testPath : possiblePaths) {
        std::cout << "Try to load from: " << testPath << std::endl;
        if (texture.loadFromFile(testPath)) {
            sprite.setTexture(texture);
            std::cout << "SUCCESSFULL LOAD FROM: " << testPath << std::endl;
            return true;
        }
    }
    
    Logger::warning("FAILED TO LOAD IMAGE FROM ANY PATH: " + path);
    return false;
}

