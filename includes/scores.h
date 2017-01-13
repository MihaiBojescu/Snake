#ifndef SCORES_H
#define SCORES_H
#include "dataTypes.h"
#include <vector>
#include <string>

class scores
{
public:
    scores(std::string path);
    ~scores();

    void trimScores(int number);
    void showScores();
    std::vector<std::string> getScores();

private:
    binaryTree *scoreBoard;
};
#endif
