#include "ResultsManager.h"

bool ResultsManager::LoadFromFile() {

    std::ifstream in(screenName + ".result");
    if (!in.is_open()) return false;

    reset();

    std::string type;
    while (in >> type) {
        if (type == "T") {
            int time;
            std::string subType;
            in >> time >> subType;

            std::string restOfLine;
            std::getline(in, restOfLine); //read the rest of the line
            resultsMap[time].push_back(subType + restOfLine); //save to map
        }
        else if (type == "SCORE") {
            int s1, s2;
            in >> s1 >> s2;
            winnerID = s1 > s2 ? 1 : 2;
            winnerScore = std::max(s1, s2);
        }
    }

    in.close();
    return true;
    
}

void ResultsManager::SaveToFile() {

    std::ofstream out(screenName + ".result");
    if (!out.is_open()) return;

    for (const auto& [time, events] : resultsMap) {
        for (const std::string& line : events) {
            out << "T " << time << " " << line << "\n";
        }
    }

    if (winnerID == 1)
        out << "SCORE " << winnerScore << " 0\n";
    else if (winnerID == 2)
        out << "SCORE 0 " << winnerScore << "\n";

    out.close();
    
}

void ResultsManager::reset(){
   
    resultsMap.clear();
    winnerID = 0;
    winnerScore = 0;
    screenName.clear();
   
    
}

bool ResultsManager::isShellHitAt(int time, const std::string& what, int x, int y) const
{
    auto it = resultsMap.find(time);
    if (it == resultsMap.end()) return false;

    std::string expected = "HIT " + what + " " + std::to_string(x) + " " + std::to_string(y);
    for (const auto& line : it->second) {
        if (line == expected) return true;
    }
    return false;
}

bool ResultsManager::isMineDeathAt(int time, const std::string& player) const
{
    auto it = resultsMap.find(time);
    if (it == resultsMap.end()) return false;

    std::string expected = "MINE " + player;
    for (const auto& line : it->second) {
        if (line == expected) return true;
    }
    return false;
}

// Checks whether the result file ends before the current iteration.
// Returns true if the given iteration number is greater than the last recorded iteration
bool ResultsManager::isFinishedBy(int currentIteration) const {
    if (resultsMap.empty())
        return true; 

    auto last = resultsMap.rbegin();  
    int last_iter = last->first;
    return currentIteration >= last_iter;
}

