#pragma once
#include <fstream>   
#include <string>    
#include <vector>    
#include <map>

class StepsManager {
private:
    std::ofstream outFile;     // for save mode
    std::ifstream inFile;      // for load mode
    int timePoint = 1;         // current time step
    std::string fileName;      // file name to load/save
    unsigned int seed = 0;     // loaded seed
    std::map<int, std::vector<char>> stepsMap; // maps time point to key list

public:
    StepsManager() = default;
    ~StepsManager();

    // Save Mode
    bool openFile(const std::string& screenName);     // open for writing
    void setSeed(unsigned int seed);                  // write the seed at start
    void recordStep(const std::vector<char>& keys);   // write keys for this timePoint
    void closeFile();         
    void incrementTime();// close outFile manually
    void resetAll() { stepsMap.clear(); seed = 0;} //reset stepsMap - used for change stages

    // Load Mode
    bool loadFile(const std::string& screenName);     // open and parse for reading
    unsigned int getSeed() const { return seed; }     // get loaded seed
    bool getNextStep(std::vector<char>& keysOut);     // get keys for current timePoint
    void resetTime() { timePoint = 1; }               // reset time to 1
};
