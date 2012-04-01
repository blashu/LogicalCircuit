#ifndef __DELAY_CELL_CREATOR__H__
#define __DELAY_CELL_CREATOR__H__

//#include "CellManager.h"
#include "CellCreator.h"
#include "DelayProcessStrategy.h"
#include <vector>

//class DelayCellManager;

class DelayCellCreator: public CellCreator
{
	public:
//		typedef std::vector<LogicalCircuitScene*> managers_t;
//		typedef managers_t::iterator manager_iterator;

		DelayCellCreator(){}
		//DelayCellCreator( DelayCellManager* manager );

		virtual void add_and();
		virtual void add_or();

//		virtual void add_manager( DelayCellManager* manager );
//		virtual void remove_manager( DelayCellManager* manager );
//		virtual void remove_manager( int num );

	private:
//		managers_t managers;
};

#endif
