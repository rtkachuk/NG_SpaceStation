#ifndef SELECTDIRECTIONDIALOG_H
#define SELECTDIRECTIONDIALOG_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class SelectDirectionDialog;
}

class SelectDirectionDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SelectDirectionDialog(QWidget *parent = nullptr);
	~SelectDirectionDialog();

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	Ui::SelectDirectionDialog *ui;
};

#endif // SELECTDIRECTIONDIALOG_H
