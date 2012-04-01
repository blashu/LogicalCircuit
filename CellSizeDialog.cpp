#include "CellSizeDialog.h"
#include "ui_CellSizeDialog.h"

#include "CellProcessStrategy.h"

#include <stdexcept>

void CellSizeDialog::set_layout_visible( QLayout* layout, bool visible )
{
	if( NULL == layout )
	{
		return;
	}

	for( auto i = layout->count(); i --> 0; )
	{
		QLayout* tmpLayout;
		QSpacerItem* tmpSpacerItem;
		QWidget* tmpWidget;
		if( NULL != ( tmpWidget = layout->itemAt( i )->widget() ) )
		{
			tmpWidget->setVisible( visible );
		}
		else if( NULL != ( tmpLayout = layout->itemAt( i )->layout() ) )
		{
			set_layout_visible( tmpLayout, visible );
		}
		else if( NULL != ( tmpSpacerItem = layout->itemAt( i )->spacerItem() ) )
		{
			tmpSpacerItem->sizeHint().setHeight(0);
			tmpSpacerItem->sizeHint().setWidth(0);
		}
	}
}

CellSizeDialog::CellSizeDialog( Cell* cell, QWidget *parent ) :
		QDialog(parent),
		ui(new Ui::CellSizeDialog),
		cell(cell)
{
	if( NULL == cell )
	{
		throw std::logic_error( "NULL == cell" );
	}

	ui->setupUi(this);

	initialize_ui();
	initialize_signals();
}

CellSizeDialog::~CellSizeDialog()
{
    delete ui;
}

void CellSizeDialog::check_in_count( int size )
{
	check_setting_counts( NT_INPUT, size, ui->requiredOutCount->value() );
}

void CellSizeDialog::check_out_count( int size )
{
	check_setting_counts( NT_OUTPUT, ui->requiredInCount->value(), size );
}

void CellSizeDialog::resize_cell()
{
	cell->resize_node_count( ui->requiredInCount->value(), ui->requiredOutCount->value() );
}

void CellSizeDialog::check_setting_counts( NodeTypes updatingType, size_t inCount, size_t outCount )
{
	const std::wstring& errorMsg = cell->process_strategy()->is_valid_node_count( inCount, outCount );
	if( CellProcessStrategy::noErrorMessage != errorMsg )
	{
		ui->errorMessageOutput->setText( QString::fromStdWString( errorMsg ) );

		if( ui->isAutoCorrect->isChecked() )
		{
			cell->process_strategy()->correct_node_count( updatingType, inCount, outCount );
			ui->requiredInCount->setValue( inCount );
			ui->requiredOutCount->setValue( outCount );
		}
		return;
	}
	ui->errorMessageOutput->setText( "" );
}

void CellSizeDialog::initialize_signals()
{
	QApplication::connect( ui->requiredInCount, SIGNAL(valueChanged(int)),
												 this, SLOT(check_in_count(int)));
	QApplication::connect( ui->requiredOutCount, SIGNAL(valueChanged(int)),
												 this, SLOT(check_out_count(int)));
	QApplication::connect( this, SIGNAL(accepted()), this, SLOT(resize_cell()));
}

void CellSizeDialog::initialize_ui()
{
	auto ps = cell->process_strategy();
	ui->requiredInCount->setMinimum( ps->inodes_min() );
	ui->requiredInCount->setMaximum( ps->inodes_max() );
	ui->requiredInCountSB->setMinimum( ps->inodes_min() );
	ui->requiredInCountSB->setMaximum( ps->inodes_max() );

	ui->requiredOutCount->setMinimum( ps->onodes_min() );
	ui->requiredOutCount->setMaximum( ps->onodes_max() );
	ui->requiredOutCountSB->setMinimum( ps->onodes_min() );
	ui->requiredOutCountSB->setMaximum( ps->onodes_max() );

	if( cell->in_is_min_equal_max() )
	{
		set_layout_visible( ui->inInfoLayout, false );
	}
	else if ( cell->out_is_min_equal_max() )
	{
		set_layout_visible( ui->outInfoLayout, false );
	}
}
