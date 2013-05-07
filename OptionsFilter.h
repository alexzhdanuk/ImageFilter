#pragma once

#include "Filter.h"
class OptionsFilter
{
public:
	OptionsFilter(void);
	OptionsFilter(const QString &_value="");
	QByteArray* toByteArray();
	void fromByteArray(QByteArray* byteArray);
	~OptionsFilter(void);

public:
	InstallationFilter filter[12];
	QString NameFilter;

};

