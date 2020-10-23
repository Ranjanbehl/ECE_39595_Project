#ifndef __ACTION_H__
#define __ACTION_H__

#include <iostream>
#include <string>
#include <cstdlib>

class Action{
public:
    void setMessage(std::string msg);
    void setIntValue(int v);
    void setCharValue(char c);
protected:
    std::string message;
    int intVal;
    char charVal;
};

#endif