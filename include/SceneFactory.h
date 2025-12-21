#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

#include <vector>
#include <memory>
#include <string>

class VariableDatabase;
class VisualObject;

namespace sf {
    class Font;
}

class SceneFactory {
public:
    static std::vector<std::unique_ptr<VisualObject>> createDemoScene(
        VariableDatabase* db,
        sf::Font* font);
};


#endif
