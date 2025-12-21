#include "VariableDatabase.h"
#include "logger.h"
#include <iostream>

VariableDatabase::VariableDatabase() {
    initializeDemoVariables();  
}

void VariableDatabase::setVariable(const std::string& name, double value) {
    double oldValue = variables[name];
    
    variables[name] = value;
    addToHistory(name, value);
    
    if (subscribers.find(name) != subscribers.end()) {
        for (auto& callback : subscribers[name]) {
            callback(value);  
        }
    }
    
    Logger::info("Variable '" + name + "' set to: " + std::to_string(value));
}

double VariableDatabase::getVariable(const std::string& name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second; 
    }
    throw std::invalid_argument("Variable: " + name + " not found in Database");
}

bool VariableDatabase::variableExists(const std::string& name) const {
    return variables.find(name) != variables.end();
}

void VariableDatabase::addToHistory(const std::string& name, double value) {
    historyVariables[name].push_back(value);    
    if (historyVariables[name].size() > 100) {
        historyVariables[name].erase(historyVariables[name].begin());
    }
}

const std::vector<double>& VariableDatabase::getHistory(const std::string& name) const {
    static std::vector<double> emptyHistory;
    
    auto it = historyVariables.find(name);
    if (it != historyVariables.end()) {
        return it->second;  
    }
    return emptyHistory;  
}

void VariableDatabase::subscribe(const std::string& variable, std::function<void(double)> callback) {
    subscribers[variable].push_back(callback);
}

void VariableDatabase::initializeDemoVariables() {
    setVariable("panel_status", 0.0);      
    setVariable("temperature_value", 72.5); 
    setVariable("setpoint_value", 65.0);    
    setVariable("pressure_value", 3.5);     
    
    for (int i = 0; i < 10; ++i) {
        setVariable("temperature_history", 70.0 + i * 0.5);
    }

}

