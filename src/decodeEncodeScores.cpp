#include "../includes/decodeEncodeScores.h"

char decode(int number)
{
    char output;
    number = (number >> 5) / 5;
    output = (char)number;
    return output;
}

int encode(char character)
{
    int output;
    output = (int)character;
    output = (output << 5) * 5;
    return output;
}
