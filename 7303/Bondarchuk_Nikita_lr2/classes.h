#ifndef CLASSES_H
#define CLASSES_H
    #include <iostream>
    #include <cmath>
    using namespace std;
    class Shape
    {
    protected:
        double Xcentre;
        double Ycentre;

        int Rcolor;
        int Gcolor;
        int Bcolor;

    public:
        Shape(double x, double y)
        {
            Xcentre = x;
            Ycentre = y;
            Rcolor = Gcolor = Bcolor = 0;
        }
        virtual ~Shape() {}
        void MoveCentre(double x, double y)
        {
            Xcentre = x;
            Ycentre = y;
        }
        virtual void rotate(double radian) = 0;
        virtual bool scale(double i) = 0;
        void set_color(int red, int green, int blue)
        {
            Rcolor = red;
            Gcolor = green;
            Bcolor = blue;
        }
        friend ostream& operator<<(ostream& out, const Shape &s)
        {
            return out << "Center: (" << s.Xcentre << ", " << s.Ycentre << ")" << endl;
        }
    };


    class Round : public Shape
    {
    private:
        double radius;

    public:
        Round(double radius, double x, double y) : Shape(x, y), radius(radius) {}
        ~Round() {}
        void rotate(double radian) {}
        bool scale(double i)
        {
            if (i != 0.0)
            {
                radius *= i;
                return true;
            }
            return false;
        }
        friend ostream& operator<<(ostream& out, const Round &s)
        {
            return out << "Center: (" << s.Xcentre << ", " << s.Ycentre << ")" << endl << "Radius: " << s.radius << endl;
        }


    };

    class Fiveverticals_Star : public Shape
    {
    protected:
        int verticals;
        double *x_arr;
        double *y_arr;

    public:
        Fiveverticals_Star(double x, double y, double *x_arr, double *y_arr, int verticals = 5) : Shape(x, y)
        {
            this->verticals = verticals;
            this->x_arr = new double[verticals];
            this->y_arr = new double[verticals];
            if (x_arr && y_arr)
                for (int i = 0; i < verticals; i++)
                {
                    this->x_arr[i] = x_arr[i];
                    this->y_arr[i] = y_arr[i];
                }
        }
        ~Fiveverticals_Star()
        {
            delete[] x_arr;
            delete[] y_arr;
        }
        void MoveCentre(double x, double y)
        {
            double dx = x - Xcentre;
            double dy = y - Ycentre;
            Xcentre = x;
            Ycentre = y;
            for (int i = 0; i < verticals; i++)
            {
                x_arr[i] = x_arr[i] + dx;
                y_arr[i] = y_arr[i] + dy;
            }
        }
        void rotate(double radian)
        {
            for (int i = 0; i < verticals; i++)
            {
                double x_tmp = Xcentre + (Xcentre - x_arr[i]) * cos(radian) - (Ycentre - y_arr[i]) * sin(radian);
                double y_tmp = Ycentre + (Ycentre - y_arr[i]) * cos(radian) + (Xcentre - x_arr[i]) * sin(radian);
                x_arr[i] = x_tmp;
                y_arr[i] = y_tmp;
            }
        }
        bool scale(double i)
        {
            if (i == 0.0)
                return false;

            for (int p = 0; p < verticals; p++)
            {
                double x_tmp = Xcentre + (x_arr[p] - Xcentre) * i;
                double y_tmp = Ycentre + (y_arr[p] - Ycentre) * i;
                x_arr[p] = x_tmp;
                y_arr[p] = y_tmp;
            }

            return true;
        }
        friend ostream& operator<<(ostream& out, const Fiveverticals_Star &s)
        {
            string str;
            for (int i = 0; i < s.verticals; i++)
            {
                str = str + "(" + to_string(s.x_arr[i]) + ", " + to_string(s.y_arr[i]) + ") ";
            }
            return out << "Center: " << s.Xcentre << ", " << s.Ycentre << endl
                       << str << endl;
        }

    };

    class Sixverticals_Star : public Fiveverticals_Star
    {
    public:
        Sixverticals_Star(double x, double y, double *x_arr, double *y_arr, int verticals = 6) : Fiveverticals_Star (x, y, x_arr, y_arr, 6) {}
    };
#endif // CLASSES_H
