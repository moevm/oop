#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>
#include <cmath>

class Shape
{
protected:
    double center_x;
    double center_y;

    int color_r;
    int color_g;
    int color_b;

public:
    Shape(double x = 0, double y = 0)
    {
        center_x = x;
        center_y = y;
        color_r = color_g = color_b = 0;
    }
    virtual ~Shape() {}
    void move_to(double x, double y)
    {
        center_x = x;
        center_y = y;
    }
    virtual void rotate(double rad) = 0;
    virtual bool scale(double k) = 0;
    void set_color(int red, int green, int blue)
    {
        color_r = red;
        color_g = green;
        color_b = blue;
    }
    void get_color(int &red, int &green, int &blue)
    {
        red = color_r;
        green = color_g;
        blue = color_b;
    }
    friend std::ostream& operator<<(std::ostream& out, const Shape &s)
    {
        return out << "Center: (" << s.center_x << ", " << s.center_y << ")" << std::endl;
    }
};


class Round : public Shape
{
private:
    double radius;

public:
    Round(double radius, double x = 0, double y = 0) : Shape(x, y), radius(radius) {}
    ~Round() {}
    void rotate(double rad) {}
    bool scale(double k)
    {
        if (k != 0.0)
        {
            radius *= k;
            return true;
        }
        return false;
    }
    friend std::ostream& operator<<(std::ostream& out, const Round &s)
    {
        return out << "Center: (" << s.center_x << ", " << s.center_y << ")" << std::endl
                   << "Radius: " << s.radius << std::endl;
    }

};

class Fivepointed_Star : public Shape
{
protected:
    int points;
    double *x_arr;
    double *y_arr;

public:
    Fivepointed_Star(double x = 0, double y = 0, double *x_arr = nullptr, double *y_arr = nullptr, int points = 5) : Shape(x, y)
    {
        this->points = points;
        this->x_arr = new double[points];
        this->y_arr = new double[points];
        if (x_arr && y_arr)
            for (int i = 0; i < points; i++)
            {
                this->x_arr[i] = x_arr[i];
                this->y_arr[i] = y_arr[i];
            }
    }
    ~Fivepointed_Star()
    {
        delete[] x_arr;
        delete[] y_arr;
    }
    void move_to(double x, double y)
    {
        double dx = x - center_x;
        double dy = y - center_y;
        center_x = x;
        center_y = y;
        for (int i = 0; i < points; i++)
        {
            x_arr[i] = x_arr[i] + dx;
            y_arr[i] = y_arr[i] + dy;
        }
    }
    void rotate(double k)
    {
        for (int i = 0; i < points; i++)
        {
            double x_tmp = center_x + (center_x - x_arr[i]) * std::cos(k) - (center_y - y_arr[i]) * std::sin(k);
            double y_tmp = center_y + (center_y - y_arr[i]) * std::cos(k) + (center_x - x_arr[i]) * std::sin(k);
            x_arr[i] = x_tmp;
            y_arr[i] = y_tmp;
        }
    }
    bool scale(double k)
    {
        if (k == 0.0)
            return false;

        for (int i = 0; i < points; i++)
        {
            double x_tmp = center_x + (x_arr[i] - center_x) * k;
            double y_tmp = center_y + (y_arr[i] - center_y) * k;
            x_arr[i] = x_tmp;
            y_arr[i] = y_tmp;
        }

        return true;
    }
    friend std::ostream& operator<<(std::ostream& out, const Fivepointed_Star &s)
    {
        std::string str;
        for (int i = 0; i < s.points; i++)
        {
            str = str + "(" + std::to_string(s.x_arr[i]) + ", " + std::to_string(s.y_arr[i]) + ") ";
        }
        return out << "Center: " << s.center_x << ", " << s.center_y << std::endl
                   << str << std::endl;
    }

};

class Sixpointed_Star : public Fivepointed_Star
{
public:
    Sixpointed_Star(double x = 0, double y = 0, double *x_arr = nullptr, double *y_arr = nullptr) : Fivepointed_Star (x, y, x_arr, y_arr, 6) {}
};
#endif // FIGURES_H
