#pragma once

#include "ObjectManager.hpp"

#include <QFileDialog>
#include <QHeaderView>
#include <QInputDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
	void onLoadButtonClicked();
	void onSaveButtonClicked();
	void onAddButtonClicked();

private:

	void setupTableSorting();
	void sortTable(int column);

	ObjectManager objectManager;
	QTextEdit*	  outputTextEdit;
	QTableWidget* tableWidget;
	QPushButton*  loadButton;
	QPushButton*  saveButton;
	QPushButton*  addButton;

	bool ascendingOrder = true;
};
