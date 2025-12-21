#include "HmiPlayer.h"
#include "logger.h"

int main() {
    Logger::info("LAUNCHING XSmall-HMI SCADA Player...");
    
    HmiPlayer player;
    
    if (!player.initialize()) {
        Logger::error("FAILED TO INITIALIZED HMI Player");
        return -1;  
    }
    
    Logger::info("HMI Player SUCCESSFULLY INITIALIZED. CONGRATULATIONS!");
    player.run();  
    
    return 0;  
}

