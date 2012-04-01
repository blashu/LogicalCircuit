#include "CellConnectionDialog.h"
#include "ui_CellConnectionDialog.h"

CellConnectionDialog::CellConnectionDialog(CellView* fromCell, CellView* toCell, QWidget *parent) :
    QDialog(parent),
		ui(new Ui::CellConnectionDialog),
		toCell(toCell),
		fromCell(fromCell)
{
	if( NULL == fromCell )
	{
		throw std::logic_error( "NULL == fromCell" );
	}

	if( NULL == toCell )
	{
		throw std::logic_error( "NULL == toCell" );
	}

	ui->setupUi(this);
	initialize_ui();
	initialize_signals();
}

CellConnectionDialog::~CellConnectionDialog()
{
	delete ui;
}
//
//public slots
void CellConnectionDialog::connect_cells()
{
	toCell->connect_to_in( fromCell, get_out_id(), get_in_id() );
}

void CellConnectionDialog::initialize_signals()
{
	QApplication::connect(this, SIGNAL(accepted()), this, SLOT(connect_cells()));
}

void CellConnectionDialog::initialize_ui()
{
	for(size_t i = 1, end = fromCell->out_node_count(); i <= end; i++)
	{
		ui->outNodeCount->addItem( QString::number( i ) );
	}

	for(size_t i = 1, end = toCell->in_node_count(); i <= end; i++)
	{
		ui->inNodeCount->addItem( QString::number( i ) );
	}

	if( 1 == fromCell->out_node_count() )
	{
		ui->outNodeCount->setEditable( false );
	}
	if( 1 == toCell->in_node_count() )
	{
		ui->inNodeCount->setEditable( false );
	}
}

size_t CellConnectionDialog::get_out_id()
{
	return (ui->outNodeCount->currentText().toUInt() - 1);
}

size_t CellConnectionDialog::get_in_id()
{
	return (ui->inNodeCount->currentText().toUInt() - 1);
}
