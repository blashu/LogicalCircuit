#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "Logger.h"
#include "CellCreator.h"
#include "CellView.h"

#include <set>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
	public:
		explicit MainWindow( QWidget *parent = 0 );
		~MainWindow();

	public slots:
		void process();
		void start_process();
		void show_about_dialog();
		void show_add_cell_dialog();
		void choose_cell();
		void remove_cell();

	public:

		QList<QAction*>::const_iterator begin_add_cell_action();
		QList<QAction*>::const_iterator end_add_cell_action();

		CellView* add_cell_view( Cell* cell, QString title );
		void add_cell_type( QString cellTypeName );

		Logger::logger_t logger();

protected:
	private:
		void initialize_signals();
		void add_cell_types_to_view();
		void set_chosen_cell( CellView* cellView );

	private:
    Ui::MainWindow *ui;
		std::set<CellView*> addedCells;

		QGraphicsScene logicalCircuitScene;

		CellCreator cellCreator;
		CellView* chosenCell;
		size_t processIterationCount;
};

#endif // MAINWINDOW_H
