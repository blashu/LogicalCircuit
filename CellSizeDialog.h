#ifndef CELLSIZEDIALOG_H
#define CELLSIZEDIALOg_H

#include <QDialog>
#include "Cell.h"

namespace Ui {
		class CellSizeDialog;
}

class CellSizeDialog : public QDialog
{
    Q_OBJECT

public:
	static void set_layout_visible( QLayout* layout, bool visible );

	public:
		explicit CellSizeDialog( Cell* cell, QWidget *parent = 0 );
		~CellSizeDialog();

	public slots:
		void check_in_count( int size );
		void check_out_count( int size );
		void resize_cell();

	private:
		void initialize_signals();
		void initialize_ui();
		void check_setting_counts( NodeTypes updatingType, size_t inCount, size_t outCount );

	private:
		Ui::CellSizeDialog *ui;
		Cell* cell;
};

#endif // CELLSIZEDIALOG_H
