#include "ball.h"

Ball::Ball()
{

}

Ball::Ball(int x, int y, int radius, int dx, int dy)
{
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->dx = dx;
    this->dy = dy;
}

int Ball::getX() const
{
    return x;
}

void Ball::setX(int newX)
{
    x = newX;
}

int Ball::getY() const
{
    return y;
}

void Ball::setY(int newY)
{
    y = newY;
}

int Ball::getRadius() const
{
    return radius;
}

void Ball::setRadius(int newRadius)
{
    radius = newRadius;
}

int Ball::getDx() const
{
    return dx;
}

void Ball::setDx(int newDx)
{
    dx = newDx;
}

int Ball::getDy() const
{
    return dy;
}

void Ball::setDy(int newDy)
{
    dy = newDy;
}

void Ball::draw(QPainter *painter)
{
    painter->drawEllipse(QPoint(x, y), radius, radius);
}
