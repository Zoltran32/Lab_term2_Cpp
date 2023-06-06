#include "ball.h"

Ball::Ball()
{
    this->_x = 0;
    this->_y = 0;
    this->_dx = 0;
    this->_dy = 0;
    this->_radius = 0;
}

Ball::Ball(float x, float y, float dx, float dy, float radius)
{
    this->_x = x;
    this->_y = y;
    this->_dx = dx;
    this->_dy = dy;
    this->_radius = radius;
}

float Ball::x() const
{
    return _x;
}

void Ball::setX(float x)
{
    _x = x;
}

float Ball::y() const
{
    return _y;
}

void Ball::setY(float y)
{
    _y = y;
}

float Ball::dx() const
{
    return _dx;
}

void Ball::setDx(float dx)
{
    _dx = dx;
}

float Ball::dy() const
{
    return _dy;
}

void Ball::setDy(float dy)
{
    _dy = dy;
}

float Ball::radius() const
{
    return _radius;
}

void Ball::setRadius(float radius)
{
    _radius = radius;
}

void Ball::move()
{
    _x += _dx;
    _y += _dy;
}

void Ball::setMoveTarget(float targetX, float targetY)
{
    float difX = targetX - (_x);
    float difY = targetY - (_y);
    //-------------getting "almost" square root--------
    //adequate only if 1 object calls this method
    //no icludes for <cmath> thought
    float length_sqr = difX*difX + difY*difY;
    float almost_dir_length_sqr = 0.0f;
    float dir_length = 0.0f;
    while(almost_dir_length_sqr < length_sqr)
    {
       dir_length += 0.1f;
       almost_dir_length_sqr = dir_length*dir_length;
    }
    //-------------------------------------------------
    _dx = difX/dir_length;
    _dy = difY/dir_length;
}

void Ball::applyFriction()
{
    _dx *= 0.8f; //this can be field
    _dy *= 0.8f;
    if(-1e-03f < _dx && _dx < 1e-03f) _dx = 0;
    if(-1e-03f < _dy &&_dy < 1e-03f) _dy = 0;
}

void Ball::applyAcceleration()
{
    _dx *= 1.2f;
    _dy *= 1.2f;
}

bool Ball::isValid()
{
    if(_radius <= 0) return false;
    return true;
}

bool Ball::intersectsBall(Ball other)
{
    float difX = other.x() - (_x);
    float difY = other.y() - (_y);
    float dist_length_sqr = difX*difX + difY*difY;
    if((_radius + other.radius())*(_radius + other.radius()) >= dist_length_sqr) return true;
    return false;
}
