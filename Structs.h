#pragma once

class rgb
{
public:
	rgb(double _r, double _g, double _b){r=_r; g=_g; b=_b;}
	rgb(){};
public:
    double r;       // percent
    double g;       // percent
    double b;       // percent
};

struct hsv
{
    double h;       // angle in degrees
    double s;       // percent
    double v;       // percent
};

struct hsl
{
    double h;       // angle in degrees
    double s;       // percent
    double l;       // percent
};

enum FILTERS
{
	Sepia,			//0
	Saturation,		//1
	Shine,			//2
	Blur,			//3
	Colour,			//4
	Contrast,		//5
	Brightnes,		//6
	Opacity,		//7
	Gradient		//8
};
