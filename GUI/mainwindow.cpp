#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Solver/Solver.hpp>
#include <define.hpp>

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
	setWindowTitle("Calculator");
	
	initKeyboard();
	initConnections();
	initStyle();
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
}

void MainWindow::initConnections() {
	for (QPushButton * button : m_keyboard) {
		QObject::connect(button, &QPushButton::pressed,
						 this, &MainWindow::keyboardButton_Pressed);
	}
	
	QObject::connect(m_backButton, &QPushButton::pressed,
					 this, &MainWindow::undoButton_Pressed);
	
	QObject::connect(m_clearButton, &QPushButton::pressed,
					 this, &MainWindow::clearButton_Pressed);
	
	QObject::connect(m_equalButton, &QPushButton::pressed,
					 this, &MainWindow::equalButton_Pressed);
	
	QObject::connect(ui->expression_field, &QLineEdit::textEdited,
					 this, &MainWindow::keyPressed);
}

void MainWindow::initStyle() {
	m_equalButton->setStyleSheet("background: darkgreen");
	ui->error_message->setStyleSheet("color: red");
}

void MainWindow::keyboardButton_Pressed() {
	ui->error_message->clear();
	QPushButton * button = qobject_cast<QPushButton*>(sender());
	QString value = button->text();
	
	auto expressionField = ui->expression_field;
	QString expression = expressionField->text();
	QString btnText = button->text();
	expression.append(btnText);
	
	if (!m_undoHistory.isEmpty() && !expressionField->text().isEmpty()) {
		m_undoHistory.top().first.append(btnText);
	} else {
		m_undoHistory.push({expression, 0});
	}
	
	expressionField->setText(expression);
}

void MainWindow::keyPressed(const QString & text) {
	if (text.isEmpty() && !m_undoHistory.isEmpty()) {
		m_undoHistory.pop();
	}
	
	if (!m_undoHistory.isEmpty() &&
		!ui->expression_field->text().isEmpty())
	{
		m_undoHistory.top().first = text;
	} else {
		m_undoHistory.push({text, 0});
	}
}

void MainWindow::undoButton_Pressed() {
	if (m_undoHistory.isEmpty()) {
		ui->error_message->setText("No undo history");
		return;
	}
	
	auto & undoData = m_undoHistory.top();
	QString data = undoData.first;
	
	if (data.size() == undoData.second) {
		m_undoHistory.pop();
		if (!m_undoHistory.isEmpty()) {
			data = m_undoHistory.top().first;
			ui->expression_field->setText(data);
		}
	} else {
		if (!ui->expression_field->text().isEmpty()) {
			data.remove(data.size() - 1, 1);
			m_undoHistory.top().first = data;
		}
		
		ui->expression_field->setText(data);
		
		if (data.isEmpty() && m_undoHistory.size() == 1) {
			m_undoHistory.pop();
		}
	}
}

void MainWindow::clearButton_Pressed() {
	ui->error_message->clear();
	ui->expression_field->clear();
	m_expressionResult.clear();
}

void MainWindow::equalButton_Pressed() {
	ui->error_message->clear();
	auto expressionField = ui->expression_field;
	QString expression = expressionField->text();
	
	std::string valid = validate_expression(expression.toStdString());
	
	static float result = 0;
	if (m_expressionSolver->calculate(valid, result)) {
		m_expressionResult = QString::number(result);
		expressionField->setText(m_expressionResult);
		
		ui->listWidget->addItem(expression + " = " + m_expressionResult);
		ui->listWidget->scrollToBottom();
		m_undoHistory.push({m_expressionResult, m_expressionResult.size()});
	} else {
		clearButton_Pressed();
		ui->error_message->setText("invalid expression");
	}
}
