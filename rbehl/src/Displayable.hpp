#ifndef __DISPLAYABLE_H__
#define __DISPLAYABLE_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdbool>
#include <functional>

class Displayable{
public:
    Displayable();
    virtual void setInvisible();
    virtual void setVisible();
    virtual void setMaxHit(int maxHit);
    virtual void setHpMoves(int moves);
    virtual void setHp(int Hp);
    virtual void setType(char t);
    virtual void setIntValue(int v);
    virtual void setPosX(int x);
    virtual void setPosY(int y);
    virtual void setWidth(int x);
    virtual void setHeight(int y);

    void setFunctionAction(std::string val, void (Displayable::*func)(int));

    virtual int getXPos();
    virtual int getYPos();
    virtual int getHp();
    virtual int getMaxHit();
    virtual int getIntVal();
    virtual int getHpMoves();
    virtual char getType();
protected:
    int hitPoint;
    int hpMoves;
    int maxHit;
    int xPos;
    int yPos;
    int width;
    int height;
    int intVal; /* what is this? */
    bool show; /* for invisble it is false and for visible it is true */
    char cType; /* For creature type */
    //friend class XMLHandler;
};

#endif