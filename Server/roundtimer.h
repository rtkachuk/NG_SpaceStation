#ifndef ROUNDTIMER_H
#define ROUNDTIMER_H

#include <QObject>
#include <QTimer>

class RoundTimer : public QObject
{
	Q_OBJECT
public:
	explicit RoundTimer(QObject *parent = nullptr);

private slots:
	void minutePassed();

private:
	int m_hours;
	int m_minutes;
	QTimer *m_timer;

signals:
	void emitMinutePassed(QByteArray message);
	void roundLimit();
};

#endif // ROUNDTIMER_H
