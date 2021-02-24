#ifndef __ACTION_H__
#define __ACTION_H__

#include <iostream>
#include <string>
#include <cstdlib>

class Action{
public:
    Action(std::string name,std::string type);
    virtual void setMessage(std::string msg);
    virtual void setIntValue(int v);
    virtual void setCharValue(char c);
    virtual std::string getName();
    virtual std::string getType();
    virtual std::string getMessage();
    virtual int getIntValue();
    virtual char getCharValue();
protected:
    std::string name;
    std::string type;
    std::string message;
    char charVal;
    int intVal;
};

#endif