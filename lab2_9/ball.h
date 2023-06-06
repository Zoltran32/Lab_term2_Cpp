#ifndef BALL_H
#define BALL_H


class Ball
{
public:
    Ball();
    Ball(int x, int y, int radius, int dx, int dy);

    /*
    int get_x();
    int get_y();
    int set_x(int x);
    int set_y(int y);
    int get_radius();
    int set_radius(int radius);
    int get_dx(int dx);
    int get_dy(int dy);
    int set_dx(int x);
    int set_xy(int y);
    */

private:
    int x;
    int y;
    int radius;
    int dx;
    int dy;

};

#endif // BALL_H
