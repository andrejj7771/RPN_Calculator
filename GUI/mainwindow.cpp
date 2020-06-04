#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Solver/Solver.hpp>

#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_expressionSolver(std::make_shared<Solver::solver>())
{
	ui->setupUi(this);
	
	initKeyboard();
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::initKeyboard() {
	m_keyboard.append(ui->button_dot);
	
	m_keyboard.append(ui->button_0);
	m_keyboard.append(ui->button_1);
	m_keyboard.append(ui->button_2);
	m_keyboard.append(ui->button_3);
	m_keyboard.append(ui->button_4);
	m_keyboard.append(ui->button_5);
	m_keyboard.append(ui->button_6);
	m_keyboard.append(ui->button_7);
	m_keyboard.append(ui->button_8);
	m_keyboard.append(ui->button_9);
	
	m_keyboard.append(ui->button_add);
	m_keyboard.append(ui->button_sub);
	m_keyboard.append(ui->button_mul);
	m_keyboard.append(ui->button_div);
	m_keyboard.append(ui->button_pow);
	m_keyboard.append(ui->button_sqrt);
	m_keyboard.append(ui->button_percent);
	
	m_keyboard.append(ui->button_br_o);
	m_keyboard.append(ui->button_br_c);
	
	m_backButton = ui->button_back;
	m_clearButton = ui->button_clear;
	m_equalButton = ui->button_equal;
	
	connectKeyboard();
}

void MainWindow::connectKeyboard() {
	for (QPushButton * button : m_keyboard) {
		QObject::connect(button, &QPushButton::pressed,
						 this, &MainWindow::keyboardButton_Pressed);
	}
	
	QObject::connect(m_backButton, &QPushButton::pressed,
					 this, &MainWindow::backButton_Pressed);
	
	QObject::connect(m_clearButton, &QPushButton::pressed,
					 this, &MainWindow::clearButton_Pressed);
	
	QObject::connect(m_equalButton, &QPushButton::pressed,
					 this, &MainWindow::equalButton_Pressed);
}

void MainWindow::keyboardButton_Pressed() {
	QPushButton * button = qobject_cast<QPushButton*>(sender());
	QString value = button->text();
	
	auto expressionField = ui->expression_field;
	QString expression = expressionField->text();
	expression.append(button->text());
	expressionField->setText(expression);
}

void MainWindow::backButton_Pressed() {
	QMessageBox m;
	m.information(this, "Info", "The function not yet available");
}

void MainWindow::clearButton_Pressed() {
	ui->error_message->clear();
	ui->expression_field->clear();
	
	m_expressionResult = 0;
}

void MainWindow::equalButton_Pressed() {
	auto expressionField = ui->expression_field;
	std::string expression = expressionField->text().toStdString();
	
	if (m_expressionSolver->calculate(expression, m_expressionResult)) {
		auto numberStr = QString::number(m_expressionResult);
		expressionField->setText(numberStr);
	} else {
		clearButton_Pressed();
		ui->error_message->setText("invalid expression");
	}
}
