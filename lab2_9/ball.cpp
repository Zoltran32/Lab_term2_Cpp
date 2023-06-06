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
