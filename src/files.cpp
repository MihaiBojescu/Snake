#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "files.h"

std::string readShader(std::string location)
{
    std::string output = "", line;
    std::ifstream file;

    try
    {
        file.open(location.c_str ());
    }
    catch(std::string error)
    {
        std::cout<<"Error: " + error;
        return NULL;
    }

    while(std::getline(file, line))
        output += line;

    return output;
}

std::vector<std::string> readScores(std::string location)
{
    std::vector<std::string> output;
    std::string line;
    std::ifstream file;

    try
    {
        file.open(location.c_str ());
    }
    catch(std::string error)
    {
        std::cout<<"Error: " + error;
        return output;
    }

    while(std::getline(file, line))
        output.push_back(line);

    return output;
}

void writeScores(std::string location, std::vector<std::string> scores)
{
    std::ofstream file;

    try
    {
        file.open(location.c_str());
    }
    catch(std::string error)
    {
        std::cout<<"Error: " + error;
        return;
    }
    for(std::vector<std::string>::iterator i = scores.begin(); i < scores.end(); i++)
    {
        //file<<scores::at(i)<<"\n";
    }
}
