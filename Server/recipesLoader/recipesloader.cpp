#include "recipesloader.h"

RecipesLoader::RecipesLoader(QObject *parent) : QObject(parent)
{
	processFile();
}

void RecipesLoader::processFile()
{
	QFile data("recipes.txt");

	if (data.open(QIODevice::ReadOnly) == false) {
		log ("Problem loading recipes file");
		return;
	}

	QString recipes = data.readAll();
	data.close();

	parseRecipes(&recipes);
}

void RecipesLoader::parseRecipes(QString *data)
{
	m_recipes.clear();
	for (QString row : *data) {

		QVector<QByteArray> requirements;
		QList items = row.split(':');
		QString idToCraft = items.first();
		items.pop_front();

		for (QString item : items) {
			requirements.push_back(item.toUtf8());
		}

		m_recipes[idToCraft.toUtf8()] = requirements;
	}
}
