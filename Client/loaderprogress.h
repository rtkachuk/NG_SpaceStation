#ifndef LOADERPROGRESS_H
#define LOADERPROGRESS_H

#include <QDialog>

namespace Ui {
class LoaderProgress;
}

class LoaderProgress : public QDialog
{
	Q_OBJECT

public:
	explicit LoaderProgress(QWidget *parent = nullptr);
	void setMaximum(int max) { m_maximum = max; configureStep(max); }
	void setValue(int value);
	~LoaderProgress();

private:
	void configureStep(int max) { m_step = max / 100; }
	int m_step = 0;
	int m_maximum = 0;

	Ui::LoaderProgress *ui;
};

#endif // LOADERPROGRESS_H
