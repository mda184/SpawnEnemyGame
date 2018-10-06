#include "Vec2.h"
#include "math.h"
#include "iostream"

Vec2::Vec2()
{

}

Vec2::Vec2(float xin, float yin)
    : x(xin), y(yin)
{

}

Vec2 Vec2::operator + (const Vec2 & rhs) const
{
    // TODO
	return Vec2(x+rhs.x,y+rhs.y);
   // return Vec2(0, 0);
}

Vec2 Vec2::operator - (const Vec2 & rhs) const
{
    // TODO
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator / (const float & val) const
{
    // TODO
    
	return Vec2(x / val, y / val);
}

Vec2 Vec2::operator * (const float & val) const
{
    // TODO
    //return Vec2(0, 0);
	return Vec2(x* val, y * val);
}

bool Vec2::operator == (const Vec2 & rhs) const

{
	
    // TODO
    return (x==rhs.x&& y==rhs.y);
}

bool Vec2::operator != (const Vec2 & rhs) const
{
    // TODO
    return (x!=rhs.x|| y!=rhs.y);
}

void Vec2::operator += (const Vec2 & rhs)
{
    // TODO
	x = x + rhs.x;
	y = y + rhs.y;
}

void Vec2::operator -= (const Vec2 & rhs)
{
    // TODO
	x = x - rhs.x;
	y = y - rhs.y;
}

void Vec2::operator *= (const float & val)
{
    // TODO
	x = x * val;
	y = y * val;
		
}

void Vec2::operator /= (const float & val)
{
    // TODO
	x = x / val;
	y = y / val;
}

float Vec2::dist(const Vec2 & rhs) const
{
    // TODO
    return sqrtf(rhs.x*rhs.x +rhs.y*rhs.y);
}

void print(Vec2 & v)
{
    std::cout <<"("<<v.x<<","<<v.y<<")";
}

