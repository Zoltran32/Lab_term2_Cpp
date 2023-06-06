#ifndef BALL_H
#define BALL_H


class Ball
{
public:
    Ball();
    Ball(float x, float y, float dx, float dy, float radius);

    float x() const;
    void setX(float x);

    float y() const;
    void setY(float y);

    float dx() const;
    void setDx(float dx);

    float dy() const;
    void setDy(float dy);

    float radius() const;
    void setRadius(float radius);

    void move();
    void setMoveTarget(float targetX, float targetY);
    void applyFriction();
    void applyAcceleration();
    bool isValid();
    bool intersectsBall(Ball other);

private:
    float _x;
    float _y;
    float _dx;
    float _dy;
    float _radius;
};

#endif // BALL_H
