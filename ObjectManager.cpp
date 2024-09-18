#include "ObjectManager.hpp"

#include <QDateTime>
#include <QFile>
#include <QMap>
#include <QTextStream>

void ObjectManager::loadFromFile(const QString& filename)
{
	objects.clear();

	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qWarning() << "Could not open file for reading:" << file.errorString();
		return;
	}

	QTextStream in(&file);
	while (!in.atEnd())
	{
		QString		line  = in.readLine();
		QStringList parts = line.split(' ');
		if (parts.size() == 5)
		{
			QString name		 = parts[0];
			double	coordX		 = parts[1].toDouble();
			double	coordY		 = parts[2].toDouble();
			QString type		 = parts[3];
			qint64	creationTime = parts[4].toLongLong();
			objects.append(
			  ObjectData(name, coordX, coordY, type, creationTime));
		}
		else
		{
			qWarning() << "Invalid line format:" << line;
		}
	}
}

void ObjectManager::saveToFile(const QString& filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qWarning() << "Could not open file for writing:" << file.errorString();
		return;
	}

	QTextStream out(&file);
	for (const ObjectData& obj : objects)
	{
		out << obj.getName() << " " << obj.getCoordX() << " " << obj.getCoordY()
			<< " " << obj.getType() << " " << obj.getCreationTime() << "\n";
		qDebug() << "Saving object:" << obj.getName() << obj.getCoordX()
				 << obj.getCoordY() << obj.getType() << obj.getCreationTime();
	}
}

void ObjectManager::addObject(const ObjectData& object)
{
	objects.append(object);
}

QList<ObjectData> ObjectManager::getObjects() const
{
	return objects;
}
