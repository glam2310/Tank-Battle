#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <tuple>
#include <map>

class ResultsManager {
private:
    std::string screenName;
    std::map<int, std::vector<std::string>> resultsMap;
    int winnerID = 0;
    int winnerScore = 0;
    
    


public:
    void setScreenName(const std::string& name) {
        screenName = "tanks-game_" + name;
    }

    void addShellHit(int time, const std::string& what, int x, int y) {
        resultsMap[time].push_back("HIT " + what + " " + std::to_string(x) + " " + std::to_string(y));
    }
    void addMineDeath(int time, const std::string& tankName) {
        resultsMap[time].push_back("MINE " + tankName);
    }

    void setWinnerScore(int id, int score) {
        winnerID = id;
        winnerScore = score;
    }
    int getWinnerID() const {
        return winnerID;
    }

    int getWinnerScore() const {
        return winnerScore;
    }
    bool LoadFromFile();
    void SaveToFile();
    void reset();
    bool isShellHitAt(int time, const std::string& what, int x, int y) const; //API for validtion the results at gameLoad
    bool isMineDeathAt(int time, const std::string& player) const; //API for validtion the results at gameLoad
    bool isFinishedBy(int currentIteration) const; // Checks whether the result file ends before the current iteration.

};
