#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

#include <vector>
#include <memory>
#include <string>

// Предварительные объявления (чтобы не включать заголовочные файлы)
class VariableDatabase;
class VisualObject;

// Пространство имен SFML
namespace sf {
    class Font;
}

// Фабрика сцен - создает наборы визуальных объектов

class SceneFactory {
public:
    // Создает тестовую сцену для демонстрации возможностей
    static std::vector<std::unique_ptr<VisualObject>> createDemoScene(
        VariableDatabase* db,
        sf::Font* font);
};


#endif
