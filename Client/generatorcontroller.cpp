#include "generatorcontroller.h"
#include "ui_generatorcontroller.h"

GeneratorController::GeneratorController(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::GeneratorController)
{
	ui->setupUi(this);
	connect (ui->b_switch, &QPushButton::clicked, this, &GeneratorController::switchGenerator);
	connect (ui->s_power, &QSlider::valueChanged, this, &GeneratorController::configurePower);
}

GeneratorController::~GeneratorController()
{
	delete ui;
}

void GeneratorController::setConfiguration(generatorInfo info)
{
	m_generator = info;
	ui->l_state->setText(info.status == true ? "Включен" : "Выключен");
	ui->l_construmption->setText(QString::number(info.construmption));
	ui->l_power->setText(QString::number(info.power));
	ui->s_power->setValue(info.power);
	ui->g_temperature->display(QString::number(info.temperature));
	updateButtonName();
}

void GeneratorController::configurePower(int value)
{
	ui->l_power->setText(QString::number(value));
	m_generator.power = value;
}

void GeneratorController::switchGenerator()
{
	m_generator.status = !m_generator.status;
	updateButtonName();
	this->accept();
}

void GeneratorController::updateButtonName()
{
	ui->b_switch->setText(m_generator.status == true ? "Выключить" : "Включить");
}
