#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <filesystem>


static constexpr int FIVE = 5;
static constexpr int ZERO = 0;
static constexpr int SIX = 6;
void hideCursor();
void Flush();
void sortFiles(std::vector<std::string>& files); // helper to getAllFileNames 
int getScreenNumber(const std::string& filename); // helpr to getAllFileNames
void getAllFileNames(std::vector<std::string>& vec_to_fill, std::string file_type); // get all file name at the ctor of game 
inline void advanceIndex(int& index, int size) {// Advances index by one in a circular way: (index + 1) % size
    index = (index + 1) % size;
}