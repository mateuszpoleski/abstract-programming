// compile with g++ Piramidy.cpp -L/usr/X11R6/lib -lm -lpthread -lX11

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "CImg.h"

class Point
{
    float x;
    float y;

public:
    Point(const float &x = 0., const float &y = 0.) : x(x), y(y) {}
    Point(const Point &point) : x(point.x), y(point.y) {}

    float get_x() const
    {
        return x;
    }
    float get_y() const
    {
        return y;
    }
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
    friend Point operator-(const Point &p1, const Point &p2)
    {
        return Point(p1.x - p2.x, p1.y - p2.y);
    }
    friend Point operator/(const Point &p, const float &scalar)
    {
        return Point(p.x / scalar, p.y / scalar);
    }
    friend Point operator*(const Point &p, const float &scalar)
    {
        return Point(p.x * scalar, p.y * scalar);
    }
    friend Point operator*(const float &scalar, const Point &p)
    {
        return p * scalar;
    }
};

class Canvas
{
    int px_w;
    int px_h;
    float size_w;
    float size_h;
    float px_in_size_w;
    float px_in_size_h;
    cimg_library::CImg<unsigned char> canvas;

public:
    Canvas(const int &px_w, const int &px_h, const float &size_w, const float &size_h) : px_w(px_w), px_h(px_h), size_w(size_w), size_h(size_h), canvas(cimg_library::CImg<unsigned char>(px_w, px_h, 1, 3, 255))
    {
        px_in_size_w = px_w / size_w;
        px_in_size_h = px_h / size_h;
    }

    void save(const std::string &path)
    {
        canvas.save_png(path.c_str());

        cimg_library::CImgDisplay dsp(px_w, px_h, "Display", 0);
        dsp.display(canvas);
        std::getchar();
    }

    int size_to_px_w(const float &size)
    {
        return int(size * px_in_size_w);
    }
    int size_to_px_h(const float &size)
    {
        return int(size * px_in_size_h);
    }
    // w CImg canvas ma trochę inne koordynaty niż chcemy, w ten sposób możemy je transformować.
    int fix_h_coord(const int &h)
    {
        return px_h - h - 1;
    }
    void draw_line(const Point &p1, const Point &p2, const unsigned char color[])
    {
        float w1 = p1.get_x();
        float h1 = p1.get_y();
        float w2 = p2.get_x();
        float h2 = p2.get_y();

        int x1 = size_to_px_w(w1);
        int y1 = fix_h_coord(size_to_px_h(h1));
        int x2 = size_to_px_w(w2);
        int y2 = fix_h_coord(size_to_px_h(h2));

        canvas.draw_line(x1, y1, x2, y2, color);
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
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
    }
    void set_color(const int &r, const int &g, const int &b)
    {
        color[0] = r % 256;
        color[1] = g % 256;
        color[2] = b % 256;
    }
    unsigned char *get_color()
    {
        return color;
    }
    void set_position(const Point &new_position)
    {
        position = new_position;
    }
    Point get_position()
    {
        return position;
    }
    virtual void draw(Canvas &canvas) = 0;
    virtual void resize(const float &scale) = 0;
    virtual void move(const Point &vector) = 0;

    virtual ~Printable() {}
};

class Line : public Printable
{
    Point stop;

public:
    Line(const Point &start, const Point &stop) : Printable(start), stop(stop) {}
    void set_start(const Point &start)
    {
        set_position(start);
    }
    void set_stop(const Point &new_stop)
    {
        stop = new_stop;
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
        canvas.draw_line(get_position(), stop, get_color());
    }
    void resize(const float &scale)
    {
        stop = get_position() + ((stop - get_position()) * scale);
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
    void set_base_width(const float &new_base_width)
    {
        base_width = new_base_width;
    }

    float get_base_width()
    {
        return base_width;
    }

    void move(const Point &vector)
    {

        set_position(get_position() + vector);
    }

    float get_area()
    {
        // Okazuje się, że wzór jest poprawny nawet dla piramidy schodkowej, w razie gdyby pojawiły się jakieś dla których nie jest trzeba zmienić na virtual.
        return base_width * get_height() / 2;
    }
    void resize(const float &scale)
    {
        base_width *= scale;
    }
    virtual float get_height() = 0;
};

class EquilateralPiramid : public Piramid
{
public:
    EquilateralPiramid(const float &x, const float &y, const float &base) : Piramid(x, y, base) {}
    float get_height()
    {
        return get_base_width() * sqrt(3) / 2.;
    }
    void draw(Canvas &canvas)
    {
        unsigned char *color = get_color();
        Point a = get_position();
        Point b = get_position() + Point(get_base_width(), 0);
        Point c = Point(((a + b) / 2).get_x(), get_height() + get_position().get_y());
        canvas.draw_line(a, b, color);
        canvas.draw_line(b, c, color);
        canvas.draw_line(a, c, color);
    }
};

class SymetricPiramid : public Piramid
{
    float height;

public:
    SymetricPiramid(const float &x, const float &y, const float &base, const float &height) : Piramid(x, y, base), height(height) {}
    void set_height(const float &new_height)
    {
        height = new_height;
    }

    float get_height()
    {
        return height;
    }
    void draw(Canvas &canvas)
    {
        unsigned char *color = get_color();
        Point a = get_position();
        Point b = get_position() + Point(get_base_width(), 0);
        Point c = Point(((a + b) / 2).get_x(), get_height() + get_position().get_y());
        canvas.draw_line(a, b, color);
        canvas.draw_line(b, c, color);
        canvas.draw_line(a, c, color);
    }
    void resize(const float &scale)
    {
        Piramid::resize(scale);
        height *= scale;
    }
};

class StepPiramid : public SymetricPiramid
{
    int step_num;

public:
    StepPiramid(const float &x, const float &y, const float &base, const float &height, const int &step_num) : SymetricPiramid(x, y, base, height), step_num(step_num) {}
    void draw(Canvas &canvas)
    {
        float step_height = get_height() / step_num;
        float step_width = get_base_width() / (2 * step_num);
        //base
        unsigned char *color = get_color();
        Point a = get_position();
        Point b = get_position() + Point(get_base_width(), 0);
        canvas.draw_line(a, b, color);

        //sides
        Point curr_left = get_position() + Point(step_width / 2, 0);
        Point curr_right = curr_left + Point(step_width * (2 * step_num - 1), 0);
        Point step_left = Point(step_width, step_height);
        Point step_right = Point(-step_width, step_height);
        Point next_left = curr_left + step_left;
        Point next_right = curr_right + step_right;

        for (int i = 0; i < step_num; i++)
        {
            Point vertex_left = Point(curr_left.get_x(), next_left.get_y());
            Point vertex_right = Point(curr_right.get_x(), next_right.get_y());

            canvas.draw_line(curr_left, vertex_left, color);
            canvas.draw_line(vertex_left, next_left, color);

            canvas.draw_line(curr_right, vertex_right, color);
            canvas.draw_line(vertex_right, next_right, color);

            curr_left = next_left;
            curr_right = next_right;
            next_left = next_left + step_left;
            next_right = next_right + step_right;
        }
    }
};

class Image
{
    std::vector<Printable *> printables;

public:
    void add(Printable *printable)
    {
        printables.push_back(printable);
    }
    void resize(const float &scale)
    {
        for (Printable *printable : printables)
            printable->resize(scale);
    }
    void draw(Canvas &canvas)
    {
        for (Printable *printable : printables)
            printable->draw(canvas);
    }
    void move(const Point &vector)
    {
        for (Printable *printable : printables)
            printable->move(vector);
    }
};

int main()
{
    Canvas canvas(200, 200, 10., 10.);
    float base_1 = 10.;
    float base_2 = 6.;
    StepPiramid *p1 = new StepPiramid(0, 0, base_2, 5, 10);
    SymetricPiramid *p2 = new SymetricPiramid(base_2, 0, base_1 - base_2, 5);
    EquilateralPiramid *p3 = new EquilateralPiramid(0, 0, base_1);
    p1->set_color(255, 191, 64);
    p2->set_color(255, 223, 64);
    p3->set_color(255, 255, 64);
    //Line *l1 = new Line(Point(0, 0), Point(5, 5));
    Image img;
    //img.add(l1);
    img.add(p3);
    img.add(p2);
    img.add(p1);
    //img.resize(0.5);
    //img.move(Point(1, 1));
    img.draw(canvas);
    //std::cout << p1->get_area() << ' ' << p2->get_area() << ' ' << p3->get_area() << ' ' << std::endl;
    canvas.save("piramids.png");

    return 0;
}