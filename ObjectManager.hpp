#pragma once

#include "ObjectData.hpp"

#include <QDebug>
#include <QList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

class ObjectManager
{
public:

	void			  loadFromFile(const QString& filename);
	void			  saveToFile(const QString& filename);
	void			  addObject(const ObjectData& object);
	QList<ObjectData> getObjects() const;

private:

	QList<ObjectData> objects;
};
