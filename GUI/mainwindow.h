#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QStack>

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
	
	//<Data, SolidItemSize>
	using UndoData = QPair<QString, int>;
	
	Ui::MainWindow *ui;
	
	Solver::solver_ptr m_expressionSolver;
	QString m_expressionResult;
	
	QVector<QPushButton*> m_keyboard;
	
	QStack<UndoData> m_undoHistory;
	
	QPushButton * m_backButton;
	QPushButton * m_clearButton;
	QPushButton * m_equalButton;
	
	QLineEdit * m_errorMessageField;
	QPlainTextEdit * m_inputField;
	
private:
	
	void initKeyboard();
	void initConnections();
	void initStyle();
	
	void keyPressed(const QString & text);
	void keyboardButton_Pressed();
	void undoButton_Pressed();
	void clearButton_Pressed();
	void equalButton_Pressed();
	
};

#endif // MAINWINDOW_H
