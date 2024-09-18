#include "ObjectData.hpp"

ObjectData::ObjectData(const QString& name,
					   double		  coordX,
					   double		  coordY,
					   const QString& type,
					   qint64		  creationTime)
	: name(name),
	  coordX(coordX),
	  coordY(coordY),
	  type(type),
	  creationTime(creationTime)
{}

QString ObjectData::getName() const
{
	return name;
}

double ObjectData::getCoordX() const
{
	return coordX;
}

double ObjectData::getCoordY() const
{
	return coordY;
}

QString ObjectData::getType() const
{
	return type;
}

qint64 ObjectData::getCreationTime() const
{
	return creationTime;
}
