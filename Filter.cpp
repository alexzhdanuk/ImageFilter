#include "Filter.h"


InstallationFilter::InstallationFilter(int _name = 100 ,bool state = false, int _value = 0 ,rgb struc = rgb(0,0,0)) 
{
	name = _name; 
	isActive = state;
	value  = _value;
	rgbStruct = struc; 
}

InstallationFilter::InstallationFilter()
{
	name = 100; 
	isActive = false;
	value  = 0;
	rgbStruct = rgb(); 
}


InstallationFilter::~InstallationFilter(void)
{
}


void InstallationFilter::setName(int _value)
{
	name = _value;
}

void InstallationFilter::setActive(bool _state)
{
	isActive = _state;
}


void InstallationFilter::setRgbColour(rgb _value)
{
	rgbStruct = _value;
}


void InstallationFilter::setValue(int _value)
{
	value = _value;
}


int InstallationFilter::getName()
{
	return name;
}

bool InstallationFilter::getState()
{
	return isActive;
}

rgb InstallationFilter::GetColour()
{
	return rgbStruct;
}

int InstallationFilter::getValue()
{
	return value;
}

void InstallationFilter::setGradientColorNach(const QColor &value)
{
	colorGradientNach = value;
}

void InstallationFilter::setGradientColorKon(const QColor &value)
{
	colorGradientKon = value;
}


QColor InstallationFilter::getGradientColourNach()
{
	return colorGradientNach;
}

QColor InstallationFilter::getGradientColourKon()
{
	return colorGradientKon;
}