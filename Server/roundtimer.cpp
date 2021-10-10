#include "roundtimer.h"

static int m_minute = 60000;

RoundTimer::RoundTimer(QObject *parent) : QObject(parent)
{	
	m_timer = new QTimer();
	m_timer->setInterval(m_minute); // 1 minute
	m_timer->start();

	m_hours = 2;
	m_minutes = 0;

	connect (m_timer, &QTimer::timeout, this, &RoundTimer::minutePassed);
}

void RoundTimer::minutePassed()
{
	if (m_minutes > 0) m_minutes--;
	else { m_hours--; m_minutes=60; }

	if (m_hours == 0 && m_minutes == 0)
		emit roundLimit();
	QString message = QString("До самоуничтожения осталось %1 часов %2 минут").arg(m_hours).arg(m_minutes);

	emit emitMinutePassed(message.toUtf8());

	m_timer->start();
}
