#ifndef __CELL_CREATOR__H__
#define __CELL_CREATOR__H__

#include "Cell.h"

#include <map>
#include <vector>

class CellCreator
{
public:
	typedef std::wstring type_name_t;
	typedef std::vector<type_name_t> type_names_t;
	typedef type_names_t::const_iterator type_names_iterator;

public:
	CellCreator();
	virtual ~CellCreator();

	virtual Cell* create_cell( const std::wstring& cellTypeName );
	type_names_iterator begin_cell_type();
	type_names_iterator end_cell_type();

protected:
	typedef CellProcessStrategy* process_strategy_t;
	typedef std::map<std::wstring, process_strategy_t> process_strategies_t;

protected:
	void add_process_strategy( process_strategy_t ps );

protected:
	process_strategies_t processStrategies;
	type_names_t typeNames;

private:
	static size_t global_id;
};

#endif
