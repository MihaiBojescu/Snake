#ifndef FILES_H
#define FILES_H

#include <string>
#include <vector>

std::string readShader(std::string location);
std::vector<std::string> readScores(std::string location);
void writeScores(std::string);

#endif
