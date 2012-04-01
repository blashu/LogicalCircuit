#include "DelayCellCreator.h"

#include "AndCell.h"
#include "OrCell.h"

//DelayCellCreator::DelayCellCreator( DelayCellManager* manager )
//{
//	managers.push_back( manager );
//}

void DelayCellCreator::add_and()
{
	AndCell* andCell/* = new AndCell()*/;
	//TODO 4 убрать в константы
	andCell->set_process_strategy( new DelayProcessStrategy( /*managers.back(),*/ 4 ) );
	//managers.back()->add_cell( and );
}

void DelayCellCreator::add_or()
{
	OrCell* orCell/* = new OrCell()*/;
	//TODO 4 убрать в константы
	orCell->set_process_strategy( new DelayProcessStrategy( /*managers.back(),*/ 4 ) );
	//managers.back()->add_cell( or );
}

//void DelayCellCreator::add_manager( DelayCellManager* manager )
//{
//	managers.push_back( manager );
//}

//void DelayCellCreator::remove_manager( DelayCellManager* manager )
//{
//	for(manager_iterator it = managers.begin(), end = managers.end(); it != end; ++it)
//	{
//		/*if( *it == DelayCellManager )
//		{
//			it->
//		}*/
//	}
//}

//void DelayCellCreator::remove_manager( int num )
//{
////	managerList
//}
