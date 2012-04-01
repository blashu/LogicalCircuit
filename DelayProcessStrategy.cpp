#include "DelayProcessStrategy.h"

DelayProcessStrategy::DelayProcessStrategy( /*const DelayCellManager* manager, */circuit_time_t delay )
{
	//this->manager = manager;
	this->delay = delay;
}

bool DelayProcessStrategy::is_circuit_time_to_process()
{
	//return ( 0 == ( manager->get_current_time() % delay ) );
	return true;
}
