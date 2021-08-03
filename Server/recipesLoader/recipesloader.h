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
	void parseRecipes(QList<QByteArray> *data);
	QVector<QByteArray> getRequirements(QByteArray id);
	QList<QByteArray> getAvaiableRecipes() { return m_recipes.keys(); }
	QByteArray getRequiredToolForCrafting(QByteArray id);

private:
	void log(QString msg) { qDebug() << "[RecipesLoader]: " << msg; }
	QMap<QByteArray, QVector<QByteArray>> m_recipes;
	QMap<QByteArray, QByteArray> m_requiredTools;

};

#endif // RECIPESLOADER_H
