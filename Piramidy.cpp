#include <iostream>
#include <cmath>
#include "CImg.h"

class Point
{
    float x;
    float y;

public:
    Point(const float &x = 0., const float &y = 0.) : x(x), y(y) {}
    Point(const Point &point) : x(point.x), y(point.y) {}

    Point &operator=(const Point &other)
    {
        if (this != &other)
        {
            this->x = other.x;
            this->y = other.y;
        }
        return *this;
    }
    friend bool operator==(const Point &p1, const Point &p2)
    {
        double eps = 1e-12;
        return abs(p1.x - p2.x) < eps && abs(p1.y - p2.y) < eps;
    }
    friend bool operator!=(const Point &p1, const Point &p2)
    {
        return !(p1 == p2);
    }
    friend Point operator+(const Point &p1, const Point &p2)
    {
        return Point(p1.x + p2.x, p1.y + p2.y);
    }
    friend Point operator/(const Point &p, const float &scalar)
    {
        return Point(p.x / scalar, p.y / scalar);
    }
};

//Klasa gromadząca obiekty które można rysować, np. piramidy, linie
class Printable
{
    Point position;
    unsigned char color[3];

public:
    Printable(const Point &position) : position(position)
    {
        this->color[0] = 255;
        this->color[1] = 255;
        this->color[2] = 255;
    }
    void set_color(const int &r, const int &g, const int &b)
    {
        this->color[0] = r;
        this->color[1] = g;
        this->color[2] = b;
    }
    void set_position(const Point &position)
    {
        this->position = position;
    }
    Point get_position()
    {
        return this->position;
    }
    virtual void draw(Canvas &canvas) = 0;
    virtual void resize(const float &scale) = 0;

    // Wydało mi się bardziej logiczne przesyłanie wektora przesunięcia jako Point,
    // ze względu na to, że same wartości start i stop z Line nie mają znaczenia, o ile dobrze rozumiem interesuje nas tylko ich różnica.
    virtual void move(const Point &vector) = 0;

    virtual ~Printable() {}
};

class Line : public Printable
{
    Point stop;

public:
    Line(const Point &start, const Point &stop) : Printable(start)
    {
        this->stop = stop;
    }
    void set_start(const Point &start)
    {
        set_position(start);
    }
    void set_stop(const Point &stop)
    {
        this->stop = stop;
    }
    Line intersection(const Line &line)
    {
        //TODO
        return line
    }
    bool is_point()
    {
        return get_position() == stop;
    }
    Point get_middle()
    {
        return Point((get_position() + stop) / 2);
    }
    void draw(Canvas &canvas)
    {
    }
    void resize(const float &scale)
    {
    }
    void move(const Point &vector)
    {
        stop = stop + vector;
        set_position(get_position() + vector);
    }
};

class Piramid : public Printable
{
    float base_width;

public:
    Piramid(const float &x, const float &y, const float &base) : Printable(Point(x, y)), base_width(base) {}
    void set_base_width(const float &base_width)
    {
        this->base_width = base_width;
    }

    float get_base_width()
    {
        return this->base_width;
    }

    void move(const Point &vector)
    {

        set_position(get_position() + vector);
    }

    virtual float get_area() = 0;
    void resize(const float &scale)
    {
    }
};

class EquilateralPiramid : public Piramid
{
    EquilateralPiramid(const float &x, const float &y, const float &base) : Piramid(x, y, base) {}
    void draw(Canvas &canvas)
    {
    }
};

class SymetricPiramid : public Piramid
{
    float height;

public:
    SymetricPiramid(const float &x, const float &y, const float &base, const float &height) : Piramid(x, y, base), height(height) {}
    void set_height(const float &height)
    {
        this->height = height;
    }

    float get_height()
    {
        return this->height;
    }
    void draw(Canvas &canvas)
    {
    }
    void resize(const float &scale)
    {
    }
};

class StepPiramid : public SymetricPiramid
{
    int step_num;

public:
    StepPiramid(const float &x, const float &y, const float &base, const float &height, const int &step_num) : SymetricPiramid(x, y, base, height), step_num(step_num) {}
    void draw(Canvas &canvas)
    {
    }
};

class Canvas
{
};

class Image
{
};

int main()
{

    std::cout << "xd" << std::endl;

    unsigned int w = 300;
    unsigned int h = 400;

    const unsigned char color1[] = {0, 170, 255};
    const unsigned char color2[] = {200, 170, 255};

    cimg_library::CImg<unsigned char> bg(w, h, 1, 3, 255);

    bg.draw_circle(50, 50, 100, color1);
    bg.draw_circle(w / 2, h / 2, 50, color2);
    bg.draw_line(0, 0, 200, 200, color2);

    bg.save_png("1.png");

    cimg_library::CImgDisplay dsp(w, h, "hello", 0);
    dsp.display(bg);
    std::getchar();

    Point p(1., 2.);

    return 0;
}