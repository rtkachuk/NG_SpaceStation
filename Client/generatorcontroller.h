#ifndef GENERATORCONTROLLER_H
#define GENERATORCONTROLLER_H

#include <QDialog>

namespace Ui {
class GeneratorController;
}

struct generatorInfo {
	bool status = false;
	int power = -1;
	int construmption = -1;
	int temperature = -1;
	int x = -1;
	int y = -1;
};

class GeneratorController : public QDialog
{
	Q_OBJECT

public:
	explicit GeneratorController(QWidget *parent);
	~GeneratorController();

	generatorInfo getNewConfiguration() { return m_generator; }
	void setConfiguration(generatorInfo info);

private slots:
	void configurePower(int value);
	void switchGenerator();

private:
	void updateButtonName();

	Ui::GeneratorController *ui;
	generatorInfo m_generator;
};

#endif // GENERATORCONTROLLER_H
