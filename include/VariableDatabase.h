#ifndef VARIABLEDATABASE_H
#define VARIABLEDATABASE_H

#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <memory>

class VariableDatabase {
private:
    std::unordered_map<std::string, double> variables;
    
    std::unordered_map<std::string, std::vector<double>> historyVariables;
    
    std::unordered_map<std::string, std::vector<std::function<void(double)>>> subscribers;

public:
    VariableDatabase();
    
    void setVariable(const std::string& name, double value);
    
    double getVariable(const std::string& name) const;
    
    bool variableExists(const std::string& name) const;
    
    void addToHistory(const std::string& name, double value);
    
    const std::vector<double>& getHistory(const std::string& name) const;
    
    void subscribe(const std::string& variable, std::function<void(double)> callback);
    
    void initializeDemoVariables();
};


#endif
