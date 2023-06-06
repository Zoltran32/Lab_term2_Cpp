#ifndef BALL_H
#define BALL_H

#include <QPainter>

class Ball
{
public:
    Ball();
    Ball(int x, int y, int radius, int dx, int dy);

    int getX() const;
    void setX(int newX);

    int getY() const;
    void setY(int newY);

    int getRadius() const;
    void setRadius(int newRadius);

    int getDx() const;
    void setDx(int newDx);

    int getDy() const;
    void setDy(int newDy);

    void draw(QPainter *painter);

private:
    int x;
    int y;
    int radius;
    int dx;
    int dy;

};

#endif // BALL_H
