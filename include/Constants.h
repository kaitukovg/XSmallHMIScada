#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace Constants {
    const int WINDOW_WIDTH = 1024;   
    const int WINDOW_HEIGHT = 768;  
    const std::string FONT_PATH = "assets/fonts/helveticabold.ttf"; 


    #ifdef SFML_STATIC
        const bool IS_STATIC_BUILD = true;
    #else
        const bool IS_STATIC_BUILD = false;
    #endif
}

#endif

