#pragma once
#include <qstring.h>
#include <Structs.h>
#include <qcolor.h>

class InstallationFilter
{
public:
	explicit InstallationFilter(int _name ,bool state, int _value,rgb struc);
	InstallationFilter();
	~InstallationFilter(void);

public:
	void setName(int _value);
	void setActive(bool _state);
	void setRgbColour(rgb _value);
	void setValue(int _value);
	void setGradientColorNach(const QColor &value);
	void setGradientColorKon(const QColor &value);

public:
	int getName();
	bool getState();
	rgb GetColour();
	int getValue();
	QColor getGradientColourNach();
	QColor getGradientColourKon();

private:
	int name;
	bool isActive;
	rgb rgbStruct;
	int value;
	QColor colorGradientNach;
	QColor colorGradientKon;
};

