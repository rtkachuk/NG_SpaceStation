#ifndef ELECTRICGENERATOR_H
#define ELECTRICGENERATOR_H

#include <QObject>
#include <QTimer>
#include <QDebug>

class ElectricGenerator : public QObject
{
	Q_OBJECT
public:
	explicit ElectricGenerator(QObject *parent = nullptr);
	bool isWorking() { return m_started; }
    QByteArray getGeneratorState() { return m_currentState; };

public slots:
	void start();
	void setGenerationPower(int value) { m_powerGeneration = value; }
	void setRequiredPower(int value) { m_powerConstrumption = value; }
	void stop();

private slots:
	void secondPassed();

signals:
    void stateChanged(QByteArray state);

private:
    void log(QString msg);

	QTimer *m_generatorTimer;
	int m_currentTemperature;
	int m_powerConstrumption;
	int m_powerGeneration;
	bool m_started;
	bool m_broken;

    QByteArray m_currentState;

	const int temperatureDecreasing = 3;
	const int lowestTemperature = 24;
	const int explodeTemperature = 500;
};

#endif // ELECTRICGENERATOR_H
