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

	QList<QByteArray> recipes = data.readAll().split('\n');
	data.close();

	parseRecipes(&recipes);
}

void RecipesLoader::parseRecipes(QList<QByteArray> *data)
{
	m_recipes.clear();
	for (QByteArray row : *data) {

		if (row.isEmpty()) continue;

		QVector<QByteArray> requirements;
		QList<QByteArray> items = row.split(':');
		QByteArray idToBeCrafted = items[0];
		items.pop_front();
		QByteArray toolUsed = items[0];
		items.pop_front();

		for (QByteArray item : items) {
			requirements.push_back(item);
		}

		m_recipes[idToBeCrafted] = requirements;
		m_requiredTools[idToBeCrafted] = toolUsed;
	}
}

QVector<QByteArray> RecipesLoader::getRequirementsRaw(QByteArray id)
{
	if (m_recipes.contains(id))
		return m_recipes[id];
	else
		return QVector<QByteArray>();
}

QMap<QByteArray, int> RecipesLoader::getRequirementsTable(QByteArray id)
{
	QVector<QByteArray> requirements = getRequirementsRaw(id);
	QMap<QByteArray, int> result;

	for (QByteArray item : requirements) {
		if (result.contains(item))
			result[item]++;
		else
			result[item] = 1;
	}

	return result;
}

QByteArray RecipesLoader::getRequiredToolForCrafting(QByteArray id)
{
	if (m_requiredTools.contains(id))
		return m_requiredTools[id];
	else
		return "";
}
