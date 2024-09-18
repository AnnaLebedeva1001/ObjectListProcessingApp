#pragma once

#include <QDateTime>
#include <QString>
#include <cmath>

class ObjectData
{
public:

	ObjectData(const QString& name,
			   double		  coordX,
			   double		  coordY,
			   const QString& type,
			   qint64		  creationTime);

	QString getName() const;
	double	getCoordX() const;
	double	getCoordY() const;
	QString getType() const;
	qint64	getCreationTime() const;

private:

	QString name;
	double	coordX;
	double	coordY;
	QString type;
	qint64	creationTime;
};
