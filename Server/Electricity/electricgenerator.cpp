#include "electricgenerator.h"

ElectricGenerator::ElectricGenerator(QObject *parent) : QObject(parent)
{
	m_generatorTimer = new QTimer();
	m_generatorTimer->setInterval(1000);
	m_generatorTimer->start();

	m_currentTemperature = 24;
	m_powerConstrumption = 0;
	m_powerGeneration = 0;
	m_started = false;
	m_broken = false;

    m_currentState = "STOPPED";

    connect (m_generatorTimer, &QTimer::timeout, this, &ElectricGenerator::secondPassed);
}

void ElectricGenerator::start()
{
	if (m_broken == false) {
		m_started = true;
        m_currentState = "STARTED";
        emit stateChanged(m_currentState);
	}
}

void ElectricGenerator::stop()
{
	m_started = false;
    m_currentState = "STOPPED";
    emit stateChanged(m_currentState);
}

void ElectricGenerator::secondPassed()
{
	int powerDelta = m_powerGeneration - m_powerConstrumption;

	if (m_started == false) {
		if (m_currentTemperature > lowestTemperature)
			m_currentTemperature -= temperatureDecreasing;
		return;
	}

	if (powerDelta < 0) {
		m_powerGeneration = 0;
		m_started = false;
        m_currentState = "STALLED";
        emit stateChanged(m_currentState);
		return;
	}

	m_currentTemperature += powerDelta / 10;

	if (m_currentTemperature >= explodeTemperature) {
		disconnect (m_generatorTimer, &QTimer::timeout, this, &ElectricGenerator::secondPassed);
		m_broken = true;
        m_currentState = "EXPLODED";
        emit stateChanged(m_currentState);
	}
}
