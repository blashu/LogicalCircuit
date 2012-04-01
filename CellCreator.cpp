#include "CellCreator.h"

#include "AndCellProcessStrategy.h"
#include "OrCellProcessStrategy.h"
#include "IBusCellProcessStrategy.h"
#include "OBusCellProcessStrategy.h"
#include "NotCellProcessStrategy.h"

#include <stdexcept>
#include <sstream>

size_t CellCreator::global_id = 0x00;

CellCreator::CellCreator()
{
	add_process_strategy( new AndCellProcessStrategy() );
	add_process_strategy( new OrCellProcessStrategy() );
	add_process_strategy( new IBusCellProcessStrategy() );
	add_process_strategy( new OBusCellProcessStrategy() );
	add_process_strategy( new NotCellProcessStrategy() );
}

CellCreator::~CellCreator()
{
	for( auto it = processStrategies.begin(), end = processStrategies.end();
			 it != end; ++it )
	{
		delete it->second;
	}
}

Cell* CellCreator::create_cell( const std::wstring& cellTypeName )
{
	std::wstringstream title;
	Cell* newCell;
	auto it = processStrategies.find( cellTypeName );

	title << cellTypeName << L"_" << global_id;
	global_id++;
	if( processStrategies.end() == it )
	{
		newCell = new Cell( NULL );
	}
	else
    {
        newCell = new Cell( it->second->clone() );
		newCell->set_title(  title.str() );
	}
	return newCell;
}

void CellCreator::add_process_strategy( process_strategy_t ps )
{
	auto it = processStrategies.find( ps->cell_type_name() );

	if( it != processStrategies.end() )
	{
		throw std::logic_error( "it != processStrategies.end()" );
	}

	processStrategies[ ps->cell_type_name() ] = ps;
	typeNames.push_back( ps->cell_type_name() );
}

CellCreator::type_names_iterator CellCreator::begin_cell_type()
{
	return typeNames.begin();
}

CellCreator::type_names_iterator CellCreator::end_cell_type()
{
	return typeNames.end();
}
