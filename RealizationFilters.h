#pragma once
#include <qimage.h>
#include "Structs.h"
#include <qsize.h>
class Filters
{
public:
	Filters(const QSize &size);
	QImage addSepia(unsigned char *mas,int val);
	QImage addSaturation(unsigned char *mas,int value);
	QImage addShine(unsigned char *mas,int value);
	QImage addBlur(unsigned char *mas,int value);
    QImage addColour(unsigned char *mas,rgb options);
    QImage addContrast(unsigned char *mas,int value);
	QImage addTexture(unsigned char *mas,unsigned char *texture);
	QImage addBrightnes(unsigned char *mas,int value);
	QImage addOpacity(unsigned char *mas,int value);
	QImage addGradient(unsigned char *mas,const QColor &colorGradientNach,const QColor &colorGradientKon);
	~Filters(void);

private:
	double Max(double a,double b,double c);
	double Min(double a,double b,double c);
    hsv rgb2hsv(rgb in);
    rgb hsv2rgb(hsv in);
    hsl rgbToHsl(rgb in);
    double hue2rgb(double p,double q,double t);
    rgb  hslToRgb(hsl in);
    int Gray(rgb structRgb);

private:
	QSize m_sizeImage;
    unsigned char *m_listImageOut;
	unsigned char *m_listTexture;
};

