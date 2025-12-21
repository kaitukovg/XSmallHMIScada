#include "SceneFactory.h"
#include "Rectangle.h"
#include "Text.h"
#include "Line.h"
#include "Polyline.h"
#include "InputField.h"
#include "Button.h"
#include "HistoryGraph.h"
#include "Image.h"
#include "logger.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

std::vector<std::unique_ptr<VisualObject>> SceneFactory::createDemoScene(
    VariableDatabase* db,
    sf::Font* font) {
    
    std::vector<std::unique_ptr<VisualObject>> objects;
    
    Logger::info("CREATING SCADA DEMO-SCENE");
    
    return objects;

}
