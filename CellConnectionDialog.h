#ifndef CELLCONNECTIONDIALOG_H
#define CELLCONNECTIONDIALOG_H

#include <QDialog>
#include "CellView.h"

namespace Ui {
    class CellConnectionDialog;
}

class CellConnectionDialog : public QDialog
{
    Q_OBJECT

	public:
		explicit CellConnectionDialog( CellView* fromCell, CellView* toCell, QWidget *parent = 0 );
    ~CellConnectionDialog();

	public slots:
		void connect_cells();

	private:
		void initialize_signals();
		void initialize_ui();

		size_t get_in_id();
		size_t get_out_id();

	private:
    Ui::CellConnectionDialog *ui;
		CellView* toCell;
		CellView* fromCell;
};

#endif // CELLCONNECTIONDIALOG_H
