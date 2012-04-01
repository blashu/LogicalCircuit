//#ifndef __PROCESS_LAUNCHER__H__
//#define __PROCESS_LAUNCHER__H__
#ifndef __CELL_MANAGER__H__
#define __CELL_MANAGER__H__

#include "Cell.h"
#include "CellCreator.h"

#include <list>

class LogicalCircuitScene
{
	public:
		typedef std::list<Cell*> cells_t;
		typedef cells_t::iterator cell_iterator;

		// Просчет одной итерации.
		virtual void run() = 0;
		
		// Для создания нового логического 
		// элемента необходимо исопльзовать CellFactory.
		inline void add_cell( Cell* cell );
		inline void remove_cell( Cell* cell );

		inline cell_iterator begin_cell();
		inline cell_iterator end_cell();

	protected:
		cells_t cells;
		CellCreator *pCreator;
};

inline void LogicalCircuitScene::add_cell( Cell* cell )
{
	cells.push_back( cell );
}

inline void LogicalCircuitScene::remove_cell( Cell* cell )
{
	pCreator->free( cell );
	cells.remove( cell );
}

inline LogicalCircuitScene::cell_iterator LogicalCircuitScene::begin_cell()
{
	return cells.begin();
}

inline LogicalCircuitScene::cell_iterator LogicalCircuitScene::end_cell()
{
	return cells.end();
}

#endif
