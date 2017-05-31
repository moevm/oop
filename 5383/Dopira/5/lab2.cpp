//
// Created by Xtail on 18.05.17.
//


//РќРµРѕР±С…РѕРґРёРјРѕ СЃРїСЂРѕРµРєС‚РёСЂРѕРІР°С‚СЊ СЃРёСЃС‚РµРјСѓ РєР»Р°СЃСЃРѕРІ РґР»СЏ РјРѕРґРµР»РёСЂРѕРІР°РЅРёСЏ РіРµРѕРјРµС‚СЂРёС‡РµСЃРєРёС… С„РёРіСѓСЂ: СЌР»Р»РёРїСЃ, СЃРµРєС‚РѕСЂ СЌР»Р»РёРїСЃР°, РїР°СЂР°Р»Р»РµР»РѕРіСЂР°Рј
//Р—Р°РґР°РЅРёРµ РїСЂРµРґРїРѕР»Р°РіР°РµС‚ РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµ РІРёСЂС‚СѓР°Р»СЊРЅС‹С… С„СѓРЅРєС†РёР№ РІ РёРµСЂР°СЂС…РёРё РЅР°СЃР»РµРґРѕРІР°РЅРёСЏ, РїСЂРѕРµРєС‚РёСЂРѕРІР°РЅРёРµ Рё РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµ Р°Р±СЃС‚СЂР°РєС‚РЅРѕРіРѕ Р±Р°Р·РѕРІРѕРіРѕ РєР»Р°СЃСЃР°.
//Р Р°Р·СЂР°Р±РѕС‚Р°РЅРЅС‹Рµ РєР»Р°СЃСЃС‹ РґРѕР»Р¶РЅС‹ Р±С‹С‚СЊ РЅР°СЃР»РµРґРЅРёРєР°РјРё Р°Р±СЃС‚СЂР°РєС‚РЅРѕРіРѕ РєР»Р°СЃСЃР° Shape, СЃРѕРґРµСЂР¶Р°С‰РµРіРѕ РјРµС‚РѕРґС‹ РґР»СЏ РїРµСЂРµРјРµС‰РµРЅРёСЏ РІ СѓРєР°Р·Р°РЅРЅС‹Рµ РєРѕРѕСЂРґРёРЅР°С‚С‹,
//РїРѕРІРѕСЂРѕС‚Р° РЅР° Р·Р°РґР°РЅРЅС‹Р№ СѓРіРѕР», РјР°СЃС€С‚Р°Р±РёСЂРѕРІР°РЅРёСЏ РЅР° Р·Р°РґР°РЅРЅС‹Р№ РєРѕСЌС„С„РёС†РёРµРЅС‚, СѓСЃС‚Р°РЅРѕРІРєРё Рё РїРѕР»СѓС‡РµРЅРёСЏ С†РІРµС‚Р°, Р° С‚Р°РєР¶Рµ РѕРїРµСЂР°С‚РѕСЂ РІС‹РІРѕРґР° РІ РїРѕС‚РѕРє.
//РќРµРѕР±С…РѕРґРёРјРѕ С‚Р°РєР¶Рµ РѕР±РµСЃРїРµС‡РёС‚СЊ РѕРґРЅРѕР·РЅР°С‡РЅСѓСЋ РёРґРµРЅС‚РёС„РёРєР°С†РёСЋ РєР°Р¶РґРѕРіРѕ РѕР±СЉРµРєС‚Р°.
//Р РµС€РµРЅРёРµ РґРѕР»Р¶РЅРѕ СЃРѕРґРµСЂР¶Р°С‚СЊ:СѓСЃР»РѕРІРёРµ Р·Р°РґР°РЅРёСЏ;UML РґРёР°РіСЂР°РјРјСѓ СЂР°Р·СЂР°Р±РѕС‚Р°РЅРЅС‹С… РєР»Р°СЃСЃРѕРІ;С‚РµРєСЃС‚РѕРІРѕРµ РѕР±РѕСЃРЅРѕРІР°РЅРёРµ РїСЂРѕРµРєС‚РЅС‹С… СЂРµС€РµРЅРёР№;СЂРµР°Р»РёР·Р°С†РёСЋ РєР»Р°СЃСЃРѕРІ
#include "lab2.h"
//#include <functional>

size_t Shape::counter = 0;
std::default_random_engine rng(seed);


std::ostream& operator<< (std::ostream& os, Shape& p)
{
    p.print(os);
    return os;
}
void Shape::setColor(Color newcolor)
{
    color = newcolor;
}

const bool Shape::operator ==(const Shape &other) const
{
    if (this->id == other.id)
    {
        return true;
    }
    else return false;
}
Color Shape :: getColor() const //РїРѕР»СѓС‡РµРЅРёРµ С†РІРµС‚Р°
{
    return color;
}

void Ellipse::print(std::ostream& os)
{
    os << "[Ellipse] ";
    os << "Id: " << id;
    os << "; Center = " << center;
    os << "; a = " << a;
    os << "; b = " << b;
    os << "; fi = " << fi;
    os << "; Color = " << getColor();
    os << std::endl;
}
void Ellipse ::  move(int dx, int dy) {//РїРµСЂРµРјРµС‰РµРЅРёРµ
    center.x+=dx;
    center.y+=dy;
}
void Ellipse :: rotate(int angle) { //РїРѕРІРѕСЂРѕС‚ РЅР° СѓРіРѕР»
    fi+=angle;
}
void Ellipse :: scale(int k)//РјР°СЃС€Р°Р±РёСЂРѕРІР°РЅРёРµ РЅР° РєРѕСЌС„С„РёС†РёРµРЅС‚
{
    a=a*k;
    b=b*k;
}

void SectorOfEllipse::print(std::ostream& os)
{
    os << "[SectorOfEllipse] ";
    os << "Id: " << id;
    os << "; Center = " << center;
    os << "; a = " << a;
    os << "; b = " << b;
    os << "; fi = " << fi;
    os << "; f1 = " << f1;
    os << "; f2 = " << f2;
    os << "; Color = " << getColor();
    os << std::endl;
}

Point Ellipse::getCenter() const
{
    return center;
}
unsigned int Ellipse::getAAxis()
{
    return a;
}
unsigned int Ellipse::getBAxis()
{
    return b;
}
unsigned int Ellipse::getAngle()
{
    return fi;
}

void SectorOfEllipse::split (Ellipse* ellipse, SectorOfEllipse* s1, SectorOfEllipse* s2, SectorOfEllipse* s3) {
    //Сѓ СЌР»Р»РёРїСЃР° Рё РµРіРѕ СЃРµРєС‚РѕСЂРѕРІ РєРѕРѕСЂРґРёРЅР°С‚С‹ С†РµРЅС‚СЂР°, РїРѕР»СѓРѕСЃРё Рё СѓРіРѕР» РЅР°РєР»РѕРЅР° Р±СѓРґСѓС‚ РѕРґРёРЅР°РєРѕРІС‹РјРё
    if(ellipse)
    {
        Color ellipseColor = ellipse->getColor();
        Color colorS1(ellipseColor.red,0,0);
        Color colorS2(0,ellipseColor.green,0);
        Color colorS3(0,0,ellipseColor.blue);

        Point ellipseCenter = ellipse->getCenter();
        unsigned int a = ellipse->getAAxis();
        unsigned int b = ellipse->getBAxis();
        unsigned int angle = ellipse->getAngle();

        *s1 = SectorOfEllipse(colorS1, ellipseCenter, a, b, angle, 0, 120);
        *s2 = SectorOfEllipse(colorS2, ellipseCenter, a, b, angle, 120, 240);
        *s3 = SectorOfEllipse(colorS3, ellipseCenter, a, b, angle, 240, 360);
        delete ellipse;
    }
}

bool SectorOfEllipse::operator ==(const SectorOfEllipse &other) const
{
    return(a == other.a &&
           b == other.b &&
           getColor() == other.getColor() &&
           getCenter() == other.getCenter() &&
           fi == other.fi &&
           f1 == other.f1 &&
           f2 == other.f2);
}

//Р РµР°Р»РёР·РѕРІР°С‚СЊ РјРµС‚РѕРґ static void SectorOfEllipse::split(Ellipse* ellipse, SectorOfEllipse* s1, SectorOfEllipse* s2, SectorOfEllipse* s3),
//РєРѕС‚РѕСЂС‹Р№ РїСЂРёРЅРёРјР°РµС‚ СЌР»Р»РёРїСЃ Рё СЂР°Р·СЂРµР·Р°РµС‚ РµРіРѕ РЅР° 3 РЅРµРїРµСЂРµСЃРµРєР°СЋС‰РёС…СЃСЏ СЃРµРєС‚РѕСЂР°. Р­Р»Р»РёРїСЃ РїСЂРё СЌС‚РѕРј РґРѕР»Р¶РµРЅ СѓРґР°Р»СЏС‚СЊСЃСЏ. Р¦РІРµС‚ РєР°Р¶РґРѕРіРѕ СЃРµРєС‚РѕСЂР° Р·Р°РґР°С‘С‚СЃСЏ
//РѕРґРЅРѕР№ РёР· СЃРѕСЃС‚Р°РІР»СЏСЋС‰РёС… С†РІРµС‚Р° РёСЃС…РѕРґРЅРѕРіРѕ СЌР»Р»РёРїСЃР°.
//РџСЂРёРјРµСЂ: Р±С‹Р» СЌР»Р»РёРїСЃ Р»РёРјРѕРЅРЅРѕРіРѕ С†РІРµС‚Р°(#F8F344). РџРѕР»СѓС‡РёР»Рё s1 - РєСЂР°СЃРЅС‹Р№(#F80000), s2 - Р·РµР»С‘РЅС‹Р№(#00F300), s3 - СЃРёРЅРёР№(#000044).



bool checkParallelogram(Point a, Point b, Point c, Point d){//РїСЂРѕРІРµСЂРєР° РЅР° РїР°СЂР°Р»Р»РµР»РѕРіСЂР°РјРј
    //СЂР°Р·РЅРёС†Р°РјРё РјРµР¶РґСѓ x-РІРѕР№ РєРѕРѕСЂРґРёРЅР°С‚РѕР№ (Р° Рё РІ) РґРѕР»Р¶РЅР° Р±С‹С‚СЊ С‚Р°РєРѕР№ Р¶Рµ, РєР°Рє Рё Сѓ (c Рё d)
    //Р° СЂР°Р·РЅРёС†Р° РјРµР¶РґСѓ Сѓ-РєРѕРІС‹РјРё РєРѕРѕСЂРґРёРЅР°С‚Р°РјРё (Р° Рё d)==(b Рё c)
    if( ((b.x-a.x)==(c.x-d.x)) & ((c.y-b.y)==(d.y-a.y)) ) return true;
    else return false;
}
void Parallelogram::print(std::ostream& os)
{
    os << "[Parallelogram] ";
    os << "Id: " << id;
    os << "; Point a = " << a;
    os << "; Point b = " << b;
    os << "; Point c = " << c;
    os << "; Point d = " << d;
    os << "; Color = " << getColor();
    os << std::endl;
}
void Parallelogram ::  move(int dx, int dy) {//РїРµСЂРµРјРµС‰РµРЅРёРµ
    a.x+=dx;
    a.y+=dy;
    b.x+=dx;
    b.y+=dy;
    c.x+=dx;
    c.y+=dy;
    d.x+=dx;
    d.y+=dy;
}
void Parallelogram :: rotate(int angle) { //РїРѕРІРѕСЂРѕС‚ РЅР° СѓРіРѕР»
    angle=angle;
}
void Parallelogram :: scale(int k)//РјР°СЃС€Р°Р±РёСЂРѕРІР°РЅРёРµ РЅР° РєРѕСЌС„С„РёС†РёРµРЅС‚
{
    a.x*=k;
    a.y*=k;
    b.x*=k;
    b.y*=k;
    c.x*=k;
    c.y*=k;
    d.x*=k;
    d.y*=k;
}

Shape *Shape::createRandomShape()
{
    static std::function<Shape*()> childCreators[] = {Parallelogram::createRandomShape, SectorOfEllipse::createRandomShape, Ellipse::createRandomShape};
    static const size_t childN = sizeof(childCreators) / sizeof(childCreators[0]);
    int s = std::uniform_int_distribution<int>(0, childN-1)(rng);
    return childCreators[s]();
}

Ellipse *Ellipse::createRandomShape() {
    return new Ellipse(
            Color(
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // r
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // g
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng) // b
            ),
            Point(
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng), // x
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng) // y
            ),
            std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // a
            std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // b
            std::uniform_int_distribution<unsigned int>(0, 360)(rng) // angle
    );
}

SectorOfEllipse *SectorOfEllipse::createRandomShape() {
    return new SectorOfEllipse(
            Color(
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // r
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // g
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng) // b
            ),
            Point(
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng), // x
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng) // y
            ),
            std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // a
            std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // b
            std::uniform_int_distribution<unsigned int>(0, 360)(rng), // angle
            std::uniform_int_distribution<unsigned int>(0, 360)(rng), // startAngle
            std::uniform_int_distribution<unsigned int>(0, 360)(rng) // finishAngle
    );
}

Parallelogram *Parallelogram::createRandomShape() {
    return new Parallelogram(
            Color(
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // r
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // g
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng) // b
            ),
            Point(
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng), // x
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng) // y
            ),
            Point(
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng), // x
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng) // y
            ),
            Point(
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng), // x
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng) // y
            ),
            Point(
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng), // x
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng) // y
            )
    );
}

