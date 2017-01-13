#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../includes/files.h"

std::string readWholeFile(std::string location)
{
    std::ifstream file;
    try
    {
        file.open(location.c_str(), std ::ios::in | std::ios::binary);
    }
    catch(std::string error)
    {
        std::cout<<"Error: " + error;
    }
    return(std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()));
}

std::vector<std::string> readScores(std::string location)
{
    std::vector<std::string> output;
    std::string line;
    std::ifstream file;

    try
    {
        file.open(location.c_str());
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

void writeScores(std::string location, std::string score)
{
    std::ofstream file;

    try
    {
        file.open(location.c_str(), std::ios_base::app);
    }
    catch(std::string error)
    {
        std::cout<<"Error: " + error;
        return;
    }
    file<<score<<"\n";
}
