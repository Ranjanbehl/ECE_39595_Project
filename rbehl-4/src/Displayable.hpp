#ifndef __DISPLAYABLE_H__
#define __DISPLAYABLE_H__
#include <iostream>
#include <string>
#include <cstdlib>

class Displayable{
public:
    Displayable();
    virtual void setInvisible();
    virtual void setVisible();
    virtual void setMaxHit(int maxHit);
    virtual void setHpMove(int hpMoves);
    virtual void setHp(int Hp);
    virtual void setType(char t);
    virtual void setIntValue(int v);
    virtual void setPosX(int x);
    virtual void setPosY(int y);
    virtual void setWidth(int x);
    virtual void setHeight(int y);
protected:
    int hitPoint;
    int hpMoves;
    int xPos;
    int yPos;
    int width;
    int height;
};

#endif