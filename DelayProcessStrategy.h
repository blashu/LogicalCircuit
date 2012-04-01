#ifndef __DELAY_PROCESS_STRATEGY__H__
#define __DELAY_PROCESS_STRATEGY__H__

#include "ProcessStrategy.h"
#include "DelayCellManager.h"

typedef unsigned int circuit_time_t;

class DelayProcessStrategy : public ProcessStrategy
{
	public:
		DelayProcessStrategy( /*const DelayCellManager* manager,*/ circuit_time_t delay );

		virtual bool is_circuit_time_to_process();

	private:
		//const DelayCellManager* manager;
		circuit_time_t delay;
};

#endif
