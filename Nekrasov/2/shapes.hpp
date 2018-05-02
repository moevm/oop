#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdint>

struct point
{
    double x;
    double y;
};

class Shape
{
public:

    Shape( double ix, double iy ) : x(ix), y(iy)
    {
        angle = 0;
        colour = { 0, 0, 0 };
    }

    double toDeg( double rad )
    {
        return rad * 180 / M_PI;
    }

    double toRad( double deg )
    {
        return deg * M_PI / 180;
    }

    void setCenter( double ix, double iy )
    {
        //Change pos of every point
        for(auto& p : arr)
        {
            p.x += x - ix;
            p.y += y - iy;
        }

        //Change cen pos
        this->x = ix;
        this->y = iy;
    }

    virtual void setAngle( double iangle )
    {
        if( iangle == 360 || iangle == 0 )
                return;

        //only for output
        angle += iangle;
        angle = std::fmod( angle, 360 );

        double rang = toRad( iangle );
        double x2, y2;
        for( auto& p : arr )
        {
            x2 = x + (p.x-x)*cos(rang)-(p.y-y)*sin(rang);
            y2 = y + (p.x-x)*sin(rang)+(p.y-y)*cos(rang);
            p.x = x2;
            p.y = y2;
        }
    }

    virtual void zoom( double inum )
    {
        x *= inum;
        y *= inum;
        for(auto& p : arr)
        {
            p.x *= inum;
            p.y *= inum;
        }
    }

    void setcolour( uint8_t r, uint8_t g, uint8_t b )
    {
        colour = { r, g, b };
    }

    void clr()
    {
        x = y = angle = 0;
        colour = { 0, 0, 0 };
        arr.clear();
    }

    virtual void print(std::ostream& out)
    {
        out << "Center: " << x <<  ',' << y << '\n';
        out << "Angle: " << angle << '\n';
        out << "RGB: " << colour;
        out << "Point number: " << arr.size() << '\n';

        for(auto p : arr)
            out << "x: " << p.x << " y: " << p.y << '\n';

        out << '\n';
    }

    friend std::ostream& operator<<(std::ostream& out, Shape& in)
    {
        in.print(out);
        return out;
    }

protected:

    struct RGB
    {
        uint8_t R;
        uint8_t G;
        uint8_t B;

        friend std::ostream& operator<<(std::ostream& out, RGB& in)
        { out << (unsigned int)in.R << ' ' << (unsigned int)in.G << ' ' << (unsigned int)in.B <<'\n'; return out; }

    } colour;

    double x;
    double y;
    double angle;
    std::vector<point> arr;
};


class Circle : public Shape
{
public:

    Circle( double ix, double iy, double irad ) : Shape(ix, iy), rad( std::abs(irad) ){}

        void setAngle( double ia )
        {
            angle = ia;
        }

        void print(std::ostream &out)
        {
            out << "Center: " << x <<  ',' << y << '\n';
            out << "Radius: " << rad << '\n';
            out << "Angle: " << angle << '\n';
            out << "Colour: " << colour << '\n' << '\n';
        }

        void zoom(double inum) { rad *= inum; }

        void setRad( double irad )
        {
            rad = std::abs( irad );
        }

protected:
        double rad;
};


class Polygon : public Shape
{
public:

    void makeSimple( unsigned short num, int sideSize, double x, double y )
    {
        arr.clear();
        if( !num )
        {
            arr.push_back( {x,y} );
            return;
        }
        unsigned short R = sideSize / sqrt( 2 - 2 * cos( 180 / num ) );

        unsigned int a;
        point buff;

        for (int i = 1; i < ( num * 2 + 1 ); i++)
        {
            if (i % 2)
            {
                buff.x = x + R * cos( a * M_PI / 180 );
                buff.y = y - R * sin( a * M_PI / 180 );
                arr.push_back( buff );
            }
            a = a + 180 / num;
        }
    }

    void detCen()
    {
        double bx = 0, by = 0;
        for( auto p : arr )
        {
            bx += p.x;
            by += p.y;
        }
        this->x = bx/arr.size();
        this->y = by/arr.size();
    }

    Polygon( double ix, double iy, bool iequilaterality, int isideSize, unsigned short inum )
        : Shape( ix, iy )
    {
        if( iequilaterality && isideSize && inum )
            makeSimple( inum, isideSize, ix, iy );
    }

    void addDot( double ix, double iy  )
    {
        arr.push_back( {ix, iy} );
    }

    void deleteLastDot()
    {
        arr.pop_back();
    }
};
