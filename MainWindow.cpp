#include "MainWindow.hpp"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	QWidget*	 centralWidget = new QWidget(this);
	QVBoxLayout* mainLayout	   = new QVBoxLayout(centralWidget);

	QLabel* label  = new QLabel("Objects Output:", this);
	outputTextEdit = new QTextEdit(this);
	outputTextEdit->setReadOnly(true);

	tableWidget = new QTableWidget(this);
	tableWidget->setColumnCount(5);
	QStringList headers = {"Name",
						   "Coord X",
						   "Coord Y",
						   "Type",
						   "Creation Time"};
	tableWidget->setHorizontalHeaderLabels(headers);
	tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	setupTableSorting();

	loadButton = new QPushButton("Load", this);
	saveButton = new QPushButton("Save", this);
	addButton  = new QPushButton("Add Object", this);

	connect(loadButton,
			&QPushButton::clicked,
			this,
			&MainWindow::onLoadButtonClicked);
	connect(saveButton,
			&QPushButton::clicked,
			this,
			&MainWindow::onSaveButtonClicked);
	connect(addButton,
			&QPushButton::clicked,
			this,
			&MainWindow::onAddButtonClicked);

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(loadButton);
	buttonLayout->addWidget(saveButton);
	buttonLayout->addWidget(addButton);

	mainLayout->addWidget(label);
	mainLayout->addWidget(outputTextEdit);
	mainLayout->addLayout(buttonLayout);
	mainLayout->addWidget(tableWidget);

	setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

void MainWindow::onLoadButtonClicked()
{
	QString filename =
	  QFileDialog::getOpenFileName(this,
								   "Open File",
								   "",
								   "Text Files (*.txt);;All Files (*)");
	if (!filename.isEmpty())
	{
		objectManager.loadFromFile(filename);
		outputTextEdit->append("Loaded from " + filename);

		auto objects = objectManager.getObjects();
		outputTextEdit->append("Number of objects loaded: "
							   + QString::number(objects.size()));

		tableWidget->setRowCount(0);

		tableWidget->setRowCount(objects.size());
		int row = 0;
		for (const ObjectData& obj : objects)
		{
			tableWidget->setItem(row, 0, new QTableWidgetItem(obj.getName()));
			tableWidget->setItem(
			  row,
			  1,
			  new QTableWidgetItem(QString::number(obj.getCoordX())));
			tableWidget->setItem(
			  row,
			  2,
			  new QTableWidgetItem(QString::number(obj.getCoordY())));
			tableWidget->setItem(row, 3, new QTableWidgetItem(obj.getType()));
			tableWidget->setItem(
			  row,
			  4,
			  new QTableWidgetItem(QString::number(obj.getCreationTime())));
			row++;
		}
	}
}

void MainWindow::onSaveButtonClicked()
{
	QString filename =
	  QFileDialog::getSaveFileName(this,
								   "Save File",
								   "",
								   "Text Files (*.txt);;All Files (*)");
	if (!filename.isEmpty())
	{
		objectManager.saveToFile(filename);
		outputTextEdit->append("Saved to " + filename);
	}
}

void MainWindow::onAddButtonClicked()
{
	bool	ok;
	QString name = QInputDialog::getText(this,
										 tr("Добавить объект"),
										 tr("Имя объекта:"),
										 QLineEdit::Normal,
										 "",
										 &ok);

	if (!ok || name.isEmpty())
		return;

	double coordX = QInputDialog::getDouble(this,
											tr("Добавить объект"),
											tr("Координата X:"),
											0,
											-1000000,
											1000000,
											1,
											&ok);
	if (!ok)
		return;

	double coordY = QInputDialog::getDouble(this,
											tr("Добавить объект"),
											tr("Координата Y:"),
											0,
											-1000000,
											1000000,
											1,
											&ok);
	if (!ok)
		return;

	QString type = QInputDialog::getText(this,
										 tr("Добавить объект"),
										 tr("Тип объекта:"),
										 QLineEdit::Normal,
										 "",
										 &ok);
	if (!ok || type.isEmpty())
		return;

	ObjectData newObject(name,
						 coordX,
						 coordY,
						 type,
						 QDateTime::currentMSecsSinceEpoch());
	objectManager.addObject(newObject);

	int row = tableWidget->rowCount();
	tableWidget->insertRow(row);
	tableWidget->setItem(row, 0, new QTableWidgetItem(newObject.getName()));
	tableWidget->setItem(
	  row,
	  1,
	  new QTableWidgetItem(QString::number(newObject.getCoordX())));
	tableWidget->setItem(
	  row,
	  2,
	  new QTableWidgetItem(QString::number(newObject.getCoordY())));
	tableWidget->setItem(row, 3, new QTableWidgetItem(newObject.getType()));
	tableWidget->setItem(
	  row,
	  4,
	  new QTableWidgetItem(QString::number(newObject.getCreationTime())));

	outputTextEdit->append("Добавлен объект: " + newObject.getName());
}

void MainWindow::setupTableSorting()
{
	connect(tableWidget->horizontalHeader(),
			&QHeaderView::sectionClicked,
			this,
			&MainWindow::sortTable);
}

void MainWindow::sortTable(int column)
{
	ascendingOrder = !ascendingOrder;
	tableWidget->sortItems(column,
						   ascendingOrder ? Qt::AscendingOrder
										  : Qt::DescendingOrder);
}
