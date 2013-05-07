#include "RealizationFilters.h"
#include <qmath.h>
#include <QPainter>
#include <QLinearGradient>

#define FORMAT_IMAGE QImage::Format_ARGB32


Filters::Filters(const QSize &size)
{
	m_sizeImage = size;
	m_listImageOut = new unsigned char[size.width()*size.height()*4];
}


Filters::~Filters(void)
{
}


QImage Filters::addSepia(unsigned char *mas,int val)
{
	int gray;
	rgb structRgb;
	int countItem = m_sizeImage.width()*m_sizeImage.height()*4;
	
	for(int i=0; i<countItem;i+=4)
    {       
			structRgb.b = mas[i];
			structRgb.g = mas[i+1];
			structRgb.r = mas[i+2];
            gray = Gray(structRgb);
            gray = gray*(val/100.0);
			m_listImageOut[i] = gray*0.82;
			m_listImageOut[i+1] = gray*0.95;
			m_listImageOut[i+2] = gray;
			m_listImageOut[i+3] = mas[i+3];
        }
	return  QImage((unsigned char *)m_listImageOut,m_sizeImage.width(),m_sizeImage.height(),FORMAT_IMAGE);

}

QImage  Filters::addSaturation(unsigned char *mas,int value)
{
	rgb structRgb;
    hsv structHsv;
	int countItem = m_sizeImage.width()*m_sizeImage.height()*4;
	
	for(int i=0; i<countItem;i+=4)
    {
        structRgb.b = mas[i];
        structRgb.g = mas[i+1];
        structRgb.r = mas[i+2];
        structHsv = rgb2hsv(structRgb);
        structHsv.s=structHsv.s*value/100.0;
        if(structHsv.s>1) structHsv.s = 1;
        structRgb = hsv2rgb(structHsv);
        m_listImageOut[i] = structRgb.b;
        m_listImageOut[i+1] = structRgb.g;
        m_listImageOut[i+2] = structRgb.r;
        m_listImageOut[i+3] = mas[i+3];
    }

    return  QImage((unsigned char *)m_listImageOut,m_sizeImage.width(),m_sizeImage.height(),FORMAT_IMAGE);
}


QImage  Filters::addShine(unsigned char *mas,int value)
{
	if(value == 0) return QImage((unsigned char *)mas,m_sizeImage.width(),m_sizeImage.height(),FORMAT_IMAGE);
    rgb structRgb;
    hsv structHsv;
	int countItem = m_sizeImage.width()*m_sizeImage.height()*4;
	
	for(int i=0; i<countItem;i+=4)
    {
        structRgb.b = mas[i];
        structRgb.g = mas[i+1];
        structRgb.r = mas[i+2];
		structHsv = rgb2hsv(structRgb);
        structHsv.v=structHsv.v*value/100.0;
        if(structHsv.v>1) structHsv.v = 1;
		structRgb = hsv2rgb(structHsv);
        m_listImageOut[i] = structRgb.b;
        m_listImageOut[i+1] = structRgb.g;
        m_listImageOut[i+2] = structRgb.r;
        m_listImageOut[i+3] = mas[i+3];
    }

    return  QImage((unsigned char *)m_listImageOut,m_sizeImage.width(),m_sizeImage.height(),FORMAT_IMAGE);
}


QImage  Filters::addBlur(unsigned char *mas,int value)
{
	QRgb col;
    int width = m_sizeImage.width();
    int height = m_sizeImage.height();
    
	int r,g,b;
    double rSum = 0, gSum = 0, bSum = 0, kSum = 0;
	int rastToch;
	int centerX = width/2-1;
	int centerY = height/2-1;
	
	int kernelWidth = 1 + 2*value;
	int kernelHeight = 1 + 2*value;
	int otrPer = qPow((qPow((centerX - 0),2)+qPow((centerY-0),2)),0.5)/(1+2*value);
	   
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
           rSum = 0, gSum = 0, bSum = 0, kSum = 0;
		   
			m_listImageOut[4 * (width * y + x) + 3] = mas[4 * (width * y + x) + 3];

			if(x > (width/2-1) && y > (height/2-1))
			{
				rastToch = qPow((qPow((x-centerX),2)+qPow((y-centerY),2)),0.5);
				kernelHeight = rastToch/otrPer;
				kernelWidth = kernelHeight;
			}
			{
				rastToch = qPow((qPow((centerX-x),2)+qPow((centerY-y),2)),0.5);
				kernelHeight = rastToch/otrPer;
				kernelWidth = kernelHeight;
			}
			if(kernelWidth == 0 )
			{
				m_listImageOut[4 * (width * y + x) + 0] = mas[4 * (width * y + x) + 0];
                m_listImageOut[4 * (width * y + x) + 1] = mas[4 * (width * y + x) + 1];
                m_listImageOut[4 * (width * y + x) + 2] = mas[4 * (width * y + x) + 2];
				continue;
			}

            for (int i = 0; i < kernelWidth; i++)
            {
                for (int j = 0; j < kernelHeight; j++)
                {
                    int pixelPosX = x + (i - (kernelWidth / 2));
                    int pixelPosY = y + (j - (kernelHeight / 2));
                    if ((pixelPosX < 0) ||
                        (pixelPosX >= width) ||
                        (pixelPosY < 0) ||
                        (pixelPosY >= height)) continue;

                     b = mas[4 * (width * pixelPosY + pixelPosX) + 0];
                     g = mas[4 * (width * pixelPosY + pixelPosX) + 1];
                     r = mas[4 * (width * pixelPosY + pixelPosX) + 2];


                    double kernelVal = 1.0;

                    rSum += r * kernelVal;
                    gSum += g * kernelVal;
                    bSum += b * kernelVal;

                    kSum += kernelVal;
                }
            }

            if (kSum <= 0) kSum = 1;
           
            rSum /= kSum;
            if (rSum < 0) rSum = 0;
            if (rSum > 255) rSum = 255;

            gSum /= kSum;
            if (gSum < 0) gSum = 0;
            if (gSum > 255) gSum = 255;

            bSum /= kSum;
            if (bSum < 0) bSum = 0;
            if (bSum > 255) bSum = 255;

			m_listImageOut[4 * (width * y + x) + 0] = bSum;
			m_listImageOut[4 * (width * y + x) + 1] = gSum;
			m_listImageOut[4 * (width * y + x) + 2] = rSum;
          }
    }
	return  QImage((unsigned char *)m_listImageOut,m_sizeImage.width(),m_sizeImage.height(),FORMAT_IMAGE);
}


QImage  Filters::addColour(unsigned char *mas,rgb options)
{
	rgb structRgb;

	int countItem = m_sizeImage.width()*m_sizeImage.height()*4;
	
	for(int i=0; i<countItem;i+=4)
    {       
			structRgb.b = mas[i];
			structRgb.g = mas[i+1];
			structRgb.r = mas[i+2];
            if(structRgb.r+options.r>=255) structRgb.r = 255;
            else
            {
                if(structRgb.r+options.r<0)
                {
                    structRgb.r = 0;
                    break;
                }
                structRgb.r+=options.r;
            }
			if(structRgb.g+options.g>=255) structRgb.g = 255;
               else
               {
                   if(structRgb.g+options.g<0)
                   {
                       structRgb.g = 0;
                       break;
                   }
                   structRgb.g+=options.g;
               }
               if(structRgb.b+options.b>=255) structRgb.b = 255;
               else
               {
                   if(structRgb.b+options.b<0)
                   {
                       structRgb.b = 0;
                       break;
                   }
                   structRgb.b+=options.b;
               }
			
			m_listImageOut[i] = structRgb.b;
			m_listImageOut[i+1] = structRgb.g;
			m_listImageOut[i+2] = structRgb.r;
			m_listImageOut[i+3] = mas[i+3];
        }
	return  QImage((unsigned char *)m_listImageOut,m_sizeImage.width(),m_sizeImage.height(),FORMAT_IMAGE);
}

QImage  Filters::addContrast(unsigned char *mas,int value)
{
	const int L = 256;
		rgb structRgb;
        int b[L];

        int imageRows = m_sizeImage.height();
        int imageCols = m_sizeImage.width();

        int lAB = 0;
        int countItem = m_sizeImage.width()*m_sizeImage.height()*4;
	
		for(int i=0; i<countItem;i+=4)
		{       
			structRgb.b = mas[i];
			structRgb.g = mas[i+1];
			structRgb.r = mas[i+2];
        
            lAB += (int)(structRgb.r * 0.299 + structRgb.g * 0.587 + structRgb.b * 0.114);
        }

        lAB /= imageRows * imageCols;

        double k = 1.0 + value / 100.0;

        for (int i = 0; i < L; i++)
            {
                int delta = (int)i - lAB;
                int temp  = (int)(lAB + k *delta);

                if (temp < 0)
                    temp = 0;

                if (temp >= 255)
                    temp = 255;
                b[i] = (unsigned char)temp;
            }

        for(int i=0; i<countItem;i+=4)
		{       
			m_listImageOut[i] = b[(int)mas[i]];
			m_listImageOut[i+1] = b[(int)mas[i+1]];
			m_listImageOut[i+2] = b[(int)mas[i+2]];
			m_listImageOut[i+3] = mas[i+3];
        
         }

	return  QImage((unsigned char *)m_listImageOut,m_sizeImage.width(),m_sizeImage.height(),FORMAT_IMAGE);
}

QImage  Filters::addTexture(unsigned char *mas,unsigned char *texture)
{
	double a,a1,a2;

	int countItem = m_sizeImage.width()*m_sizeImage.height()*4;
	
	for(int i=0; i<countItem;i+=4)
    { 
		a1 = mas[i+3], a2 = texture[i+3];
		a=255-(255-a1)*(255-a2);
		a = a<0 ? 0 : a;
		a = a>255 ? 255 : a;
		
		m_listImageOut[i]   = (mas[i+0] * texture[i+0])/255;
		m_listImageOut[i+1] = (mas[i+1] * texture[i+1])/255;
		m_listImageOut[i+2] = (mas[i+2] * texture[i+2])/255;
		m_listImageOut[i+3] = a;

	}
	
	return  QImage((unsigned char *)m_listImageOut,m_sizeImage.width(),m_sizeImage.height(),FORMAT_IMAGE);
}

QImage  Filters::addBrightnes(unsigned char *mas,int value)
{
	rgb structRgb;

    int countItem = m_sizeImage.width()*m_sizeImage.height()*4;
	
	for(int i=0; i<countItem;i+=4)
    {
		structRgb.b = mas[i];
        structRgb.g = mas[i+1];
        structRgb.r = mas[i+2];

		structRgb.r += value;
		structRgb.g += value;
		structRgb.b += value;
		structRgb.r = structRgb.r > 255 ? 255 : structRgb.r;
		structRgb.r = structRgb.r < 0 ? 0 : structRgb.r;
		structRgb.g = structRgb.g > 255 ? 255 : structRgb.g;
		structRgb.g = structRgb.g < 0 ? 0 : structRgb.g;
		structRgb.b = structRgb.b > 255 ? 255 : structRgb.b;
		structRgb.b = structRgb.b < 0 ? 0 : structRgb.b;
		
		m_listImageOut[i] = structRgb.b;
        m_listImageOut[i+1] = structRgb.g;
        m_listImageOut[i+2] = structRgb.r;
        m_listImageOut[i+3] = mas[i+3];
		

    }
	return  QImage((unsigned char *)m_listImageOut,m_sizeImage.width(),m_sizeImage.height(),FORMAT_IMAGE);
}

QImage  Filters::addOpacity(unsigned char *mas,int value)
{
	int testVal;

    int countItem = m_sizeImage.width()*m_sizeImage.height()*4;
	
	for(int i=0; i<countItem;i+=4)
    {
		m_listImageOut[i] = mas[i];
        m_listImageOut[i+1] = mas[i+1];
        m_listImageOut[i+2] = mas[i+2];
        testVal = mas[i+3]+value;
		
		testVal = testVal < 0 ? 0 : testVal;
		testVal = testVal > 255 ? 255 : testVal;
		
		m_listImageOut[i+3] = testVal;

    }
	return  QImage((unsigned char *)m_listImageOut,m_sizeImage.width(),m_sizeImage.height(),FORMAT_IMAGE);
}

QImage  Filters::addGradient(unsigned char *mas,const QColor &colorGradientNach,const QColor &colorGradientKon)
{
	QImage img(m_sizeImage.width(),m_sizeImage.height(),FORMAT_IMAGE);
	
	img.fill(QColor(255,255,255,colorGradientNach.alpha()));
	QPainter painter;
	QLinearGradient grad(m_sizeImage.width(),0.0,0.0,m_sizeImage.height());
	grad.setColorAt(0,colorGradientKon);
	grad.setColorAt(1,colorGradientNach);
	QBrush  brush = QBrush(grad);
	painter.begin(&img);
	painter.fillRect(QRect(0,0,m_sizeImage.width(),m_sizeImage.height()),brush);
	painter.end();
	
	m_listTexture = img.bits();
	return addTexture(mas,m_listTexture);

}

double  Filters::Max(double a,double b,double c)
{
	double max;
	max = a;
	if(max<b) max = b;
	if(max<c) max = c;
	return max;
}

double  Filters::Min(double a,double b,double c)
{
	double min;
	min = a;
	if(min>b) min = b;
	if(min>c) min = c;
	return min;
}

hsv  Filters::rgb2hsv(rgb in)
{
	hsv         out;
    double      min, max, delta;
    double r,g,b;

    r = in.r/255.0, g = in.g/255.0, b = in.b/255.0;
    max = Max(r, g, b);
    min = Min(r, g, b);
    out.v = max;

    delta = max - min;
    out.s = max == 0 ? 0 : delta / max;

        if(max == min){
            out.h = 0; // achromatic
        }
        else
        {
            if(r>=max)
            {
                out.h = (g - b) / delta + (g < b ? 6 : 0);
            }
            if(g>=max)
            {
               out.h = (b - r) / delta + 2;
            }
			if(b>=max)
            {
                out.h = (r - g) / delta + 4;
            }
			out.h /= 6;
        }

    return out;
}

rgb  Filters::hsv2rgb(hsv in)
{
	 rgb         out;

    double r, g, b;

        int i = floor(in.h * 6);
        double f = in.h * 6 - i;
        double p = in.v * (1 - in.s);
        double q = in.v * (1 - f * in.s);
        double t = in.v * (1 - (1 - f) * in.s);

        switch(i % 6){
            case 0: r = in.v, g = t, b = p; break;
            case 1: r = q, g = in.v, b = p; break;
            case 2: r = p, g = in.v, b = t; break;
            case 3: r = p, g = q, b = in.v; break;
            case 4: r = t, g = p, b = in.v; break;
            case 5: r = in.v, g = p, b = q; break;
        }

        out.r = r*255;
        out.g = g*255;
        out.b = b*255;

    return out;
}

hsl  Filters::rgbToHsl(rgb in)
{
	double r,g,b,min,max;
    hsl out;

    r = in.r/255;
    g = in.g/255;
    b = in.b/255;
    max = Max(r, g, b);
    min = Min(r, g, b);
    //double h, s;
	out.l = (max + min) / 2;

    if(max == min)
    {
        out.h = out.s = 0; // achromatic
    }
    else
    {
        double d = max - min;
        if(out.l > 0.5) out.s = d / (2 - max - min);
		else out.s = d / (max + min);
		
		if(r>=max)
        {
            out.h = (g - b) / d + (g < b ? 6 : 0);
        }
        if(g>=max)
        {
           out.h = (b - r) / d + 2;
        }
        if(b>=max)
        {
             out.h = (r - g) / d + 4;
        }

        out.h /= 6;
    }
    
    return out;
}

double  Filters::hue2rgb(double p,double q,double t)
{
	if(t < 0) t += 1;
    if(t > 1) t -= 1;
    if(t < 1/6) return p + (q - p) * 6 * t;
    if(t < 1/2) return q;
    if(t < 2/3) return p + (q - p) * (2/3 - t) * 6;
    return p;
}

rgb  Filters::hslToRgb(hsl in)
{
	rgb out;
    double h,s,l;
    double r, g, b;

    h=in.h;
    s=in.s;
    l=in.l;

    if(s == 0){
        r = g = b = l; // achromatic
    }
    else
    {
        double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        double p = 2 * l - q;
        r = hue2rgb(p, q, h + 1/3);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1/3);
    }
    out.r = r*255;
    out.g = g*255;
    out.b = b*255;

    return out;
}

int  Filters::Gray(rgb structRgb)
{
	int gray;
	gray = static_cast<int>(structRgb.r*0.30+structRgb.g*0.59+structRgb.b*0.11);
	return gray;
}