#ifndef RECIPESLOADER_H
#define RECIPESLOADER_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QFile>
#include <QDebug>

class RecipesLoader : public QObject
{
	Q_OBJECT
public:
	explicit RecipesLoader(QObject *parent = nullptr);
	void processFile();
	void parseRecipes(QString *data);
	QVector<QByteArray> getRequirements(QByteArray id) { return m_recipes[id]; }
	QList<QByteArray> getAvaiableRecipes() { return m_recipes.keys(); }

private:
	void log(QString msg) { qDebug() << "[RecipesLoader]: " << msg; }
	QMap<QByteArray, QVector<QByteArray>> m_recipes;

};

#endif // RECIPESLOADER_H
