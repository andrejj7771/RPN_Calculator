#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
	class MainWindow;
}

namespace Solver {
	class solver;
	typedef std::shared_ptr<solver> solver_ptr;
}

class QPushButton;
class QLineEdit;
class QPlainTextEdit;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	
private:
	
	Ui::MainWindow *ui;
	
	Solver::solver_ptr m_expressionSolver;
	float m_expressionResult;
	
	QVector<QPushButton*> m_keyboard;
	
	QPushButton * m_backButton;
	QPushButton * m_clearButton;
	QPushButton * m_equalButton;
	
	QLineEdit * m_errorMessageField;
	QPlainTextEdit * m_inputField;
	
	void initKeyboard();
	void connectKeyboard();
	
	void keyboardButton_Pressed();
	void backButton_Pressed();
	void clearButton_Pressed();
	void equalButton_Pressed();
	
};

#endif // MAINWINDOW_H
