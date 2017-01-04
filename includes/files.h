#ifndef FILES_H
#define FILES_H

#include <string>
#include <vector>

extern std::string readWholeFile(std::string location);
extern std::vector<std::string> readScores(std::string location);
extern void writeScores(std::string);

#endif
