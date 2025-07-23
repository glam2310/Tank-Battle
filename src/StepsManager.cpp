#include "StepsManager.h"
#include <sstream>

StepsManager::~StepsManager() {
    if (outFile.is_open()) {
        outFile.close();
    }
    if (inFile.is_open()) {
        inFile.close();
    }
}

bool StepsManager::openFile(const std::string& screenName) {
    fileName = "tanks-game_" + screenName + ".steps";
    outFile.open(fileName);
    return outFile.is_open();
}

void StepsManager::setSeed(unsigned int seed) {
    if (outFile.is_open()) {
        outFile << "SEED " << seed << "\n";
    }
}

void StepsManager::recordStep(const std::vector<char>& keys) {
    if (outFile.is_open() && !keys.empty()) {
        outFile << "T " << timePoint << " ";
        for (char key : keys) {
            outFile << (int)key << " ";
        }
        outFile << "\n";
    }
}



void StepsManager::closeFile() {
    if (outFile.is_open()) {
        outFile.close();
    }
}

bool StepsManager::loadFile(const std::string& screenName) {
    fileName = "tanks-game_" + screenName + ".steps";
    inFile.open(fileName);
    if (!inFile.is_open()) return false;

    stepsMap.clear();
    timePoint = 1;
    std::string line;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string tag;
        iss >> tag;

        if (tag == "SEED") {
            iss >> seed;
        }
        else if (tag == "T") {
            int time;
            iss >> time;
            std::vector<char> keys;
            int keyInt;
            while (iss >> keyInt) {
                keys.push_back(static_cast<char>(keyInt));
            }
            stepsMap[time] = keys;
        }
    }

    inFile.close();
    return true;
}


bool StepsManager::getNextStep(std::vector<char>& keysOut) {
    auto it = stepsMap.find(timePoint);
    if (it != stepsMap.end()) {
        keysOut = it->second;
        timePoint++;
        return true;
    }
    keysOut.clear();
    //timePoint++;
    return false;
}

void StepsManager::incrementTime() {
    ++timePoint;
}