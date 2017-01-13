#include "../includes/scores.h"
#include "../includes/dataTypes.h"
#include "../includes/files.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>

scores::scores(std::string path)
{
    std::vector<std::string> listOfScores = readScores(path);
    this->scoreBoard = new binaryTree();
    int value = 0;
    int position = 0;

    for(int i = 0; i < listOfScores.size(); i++)
    {
        position = listOfScores[i].rfind(" ");
        value = std::atoi(listOfScores[i].substr(position, listOfScores[i].size() - position).c_str());
        this->scoreBoard->addNode(value, listOfScores[i]);
    }
    this->scoreBoard->buildQueue();
}

scores::~scores()
{
    if(this->scoreBoard) delete this->scoreBoard;
}

void scores::showScores()
{
    std::vector<std::string> result = this->scoreBoard->getStringVector();
    for(int i = 0; i < result.size(); i++)
    {
        std::cout<<result[i]<<"\n";
    }
}

std::vector<std::string> scores::getScores()
{
    return this->scoreBoard->getStringVector();
}
