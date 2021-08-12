#ifndef ELECTRICGENERATOR_H
#define ELECTRICGENERATOR_H

#include <QObject>
#include <QTimer>

class ElectricGenerator : public QObject
{
	Q_OBJECT
public:
	explicit ElectricGenerator(QObject *parent = nullptr);

public slots:
	void start();
	void setGenerationPower(int value);
	void stop();

private slots:
	void secondPassed();

signals:
	void exploded();
	void started();
	void stalled();
	void stopped();

private:
	QTimer *m_generatorTimer;
	int m_currentTemperature;
	int m_powerConstrumption;
	int m_powerGeneration;
	bool m_started;
	bool m_broken;

	const int temperatureDecreasing = 3;
	const int lowestTemperature = 24;
	const int explodeTemperature = 500;
};

#endif // ELECTRICGENERATOR_H
