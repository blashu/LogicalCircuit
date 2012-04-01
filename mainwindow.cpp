#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "CellView.h"
#include "TextEditLogger.h"

#include "AboutDialog.h"
#include "CellSizeDialog.h"
#include "CellConnectionDialog.h"

//
//ctor\dctor
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	chosenCell(NULL)
{
	ui->setupUi(this);
	ui->logicalCircuitView->setScene( &logicalCircuitScene );

	Logger::set_logger( logger() );
	Logger::instance().add_info( L"*Информация о программе*" );

	ui->logicalCircuitView->installEventFilter(this);

	add_cell_types_to_view();

	initialize_signals();

    //CellView* ibCV = add_cell_view( cellCreator.create_cell( L"input bus" ),
//                                    QString::fromStdWString( L"input bus_0" ) );
	//add_cell_view( cellCreator.create_cell( L"or" ), QString::fromStdWString( L"or_1" ) );

//	ibCV->resize_connectors_count( 0, 10 );

}

MainWindow::~MainWindow()
{
//	for( auto it = addedCells.begin(), end = addedCells.end(); it != end; ++it )
//	{
//		QApplication::connect( *it, SIGNAL(removed()), this, SLOT(remove_cell()) );
//	}
//	addedCells.clear();

	delete ui;
}
//
// Public slots
void MainWindow::process()
{
	if( 0x00 == processIterationCount )
	{
		return;
	}
	processIterationCount--;

	for( auto it = addedCells.begin(), end = addedCells.end(); it != end; ++it )
	{
		(*it)->process();
	}
	QTimer::singleShot( 2000, this, SLOT(process()) );
}

void MainWindow::start_process()
{
	processIterationCount = 10;
	QTimer::singleShot( 2000, this, SLOT(process()) );
}

void MainWindow::show_about_dialog()
{
	AboutDialog aboutDialog;
	aboutDialog.exec();
}

void MainWindow::show_add_cell_dialog()
{
	QAction* action = reinterpret_cast<QAction*>( sender() );
	Cell *cell = cellCreator.create_cell( action->text().toStdWString() );
	CellSizeDialog cellSizeDialog( cell );

	if( cell->in_is_min_equal_max() && cell->out_is_min_equal_max() )
	{
		add_cell_view( cell, action->text() );
		return;
	}

	switch ( cellSizeDialog.exec() )
	{
		case QDialog::Accepted:
			add_cell_view( cell, action->text() );
			break;
		case QDialog::Rejected:
			delete cell;
			break;
	}
}

void MainWindow::choose_cell()
{
	set_chosen_cell( reinterpret_cast<CellView*>( sender() ) );
}

void MainWindow::remove_cell()
{
	CellView* cv = reinterpret_cast<CellView*>( sender() );
	addedCells.erase( cv );
}
//
//public functions
QList<QAction*>::const_iterator MainWindow::begin_add_cell_action()
{
	return ui->menuAddCell->actions().constBegin();
}

QList<QAction*>::const_iterator MainWindow::end_add_cell_action()
{
	return ui->menuAddCell->actions().constEnd();
}

CellView* MainWindow::add_cell_view( Cell* cell, QString title )
{
	CellView *cellView = new CellView( cell, title );
	cellView->setFlags( QGraphicsItem::ItemIsMovable );
	logicalCircuitScene.addItem( cellView );

	QApplication::connect( cellView, SIGNAL(clicked()), this, SLOT(choose_cell()) );
	QApplication::connect( cellView, SIGNAL(removed()), this, SLOT(remove_cell()) );
	addedCells.insert( cellView );

//	logicalCircuitScene.removeItem( cellView );
//	delete cellView;

	Logger::instance().add_info( L"Добавлен элемент \"" + title.toStdWString() + L"\"" );
	return cellView;
}

void MainWindow::add_cell_type ( QString cellTypeName )
{
	ui->menuAddCell->addAction( cellTypeName );
}

Logger::logger_t MainWindow::logger()
{
	return Logger::logger_t( new TextEditLogger( ui->logger ) );
}
//
//private functions
void MainWindow::initialize_signals()
{
	QApplication::connect( ui->aboutAction, SIGNAL( triggered() ),
												 this, SLOT( show_about_dialog() ) );

	QApplication::connect( ui->processAction, SIGNAL(triggered() ),
												 this, SLOT(start_process()) );

	for( auto it = begin_add_cell_action(), end = end_add_cell_action(); it != end; ++it )
	{
		QApplication::connect( *it, SIGNAL(triggered()),
													 this, SLOT( show_add_cell_dialog() ) );
	}
}

void MainWindow::add_cell_types_to_view()
{
	for(auto it = cellCreator.begin_cell_type(), end = cellCreator.end_cell_type();
			it != end; ++it)
	{
		add_cell_type( QString::fromStdWString(*it) );
	}
}

void MainWindow::set_chosen_cell( CellView* cellView )
{
	if( NULL == cellView )
	{
		cellView = NULL;
		return;
	}
	if( cellView == chosenCell )
	{
		return;
	}

	if( NULL == chosenCell )
	{
		chosenCell = cellView;
		chosenCell->set_selected( true );
		Logger::instance().add_info( L"Ячейка " + chosenCell->title().toStdWString() +  L" выбрана." );
		ui->statusBar->showMessage( QString::fromStdWString( L"Выбрана ячейка " ) + chosenCell->title() );
	}
	else
	{
		chosenCell->set_selected( false );

		if( ( 0x00 != chosenCell->out_node_count() ) &&
				( 0x00 != cellView->in_node_count() ) )
		{
			CellConnectionDialog CCD( chosenCell, cellView );
			switch ( CCD.exec() )
			{
				case QDialog::Accepted:
					Logger::instance().add_info( L"Ячейки " + chosenCell->title().toStdWString() +
																			 L" и " + cellView->title().toStdWString() + L" соединены." );
					ui->statusBar->showMessage( QString::fromStdWString( L"Ячейки соединены." ) );
					break;
				case QDialog::Rejected:
					Logger::instance().add_info( L"Ячейки не были соединены.");
					break;
			}
		}

		chosenCell = NULL;
	}
}
