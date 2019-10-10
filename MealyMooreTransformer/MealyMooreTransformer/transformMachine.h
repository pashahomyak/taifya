#pragma once
#include <string>

bool compareLength(std::string s1, std::string s2);

void transformToMealy(int numOfInputCharsAlphabet, int numOfVertex, std::ifstream& inputFile, std::ofstream& outputFile);

void transformToMoore(int numOfInputCharsAlphabet, int numOfVertex, std::ifstream& inputFile, std::ofstream& outputFile);
