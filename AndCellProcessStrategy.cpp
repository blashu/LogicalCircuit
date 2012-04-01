#include "AndCellProcessStrategy.h"

const std::wstring AndCellProcessStrategy::cellTypeName = L"and";

CellProcessStrategy* AndCellProcessStrategy::clone() const
{
	return new AndCellProcessStrategy();
}

size_t AndCellProcessStrategy::inodes_min() const
{
	return 2;
}

size_t AndCellProcessStrategy::inodes_max() const
{
	return 2;
}

size_t AndCellProcessStrategy::onodes_min() const
{
	return 1;
}

size_t AndCellProcessStrategy::onodes_max() const
{
	return 1;
}

void AndCellProcessStrategy::do_process( const ibus_t& in, const obus_t& out )
{
	for( size_t i = in.size(); i --> 0x00; )
	{
		if( false == in[ i ] )
		{
			out[ 0x00 ] = false;
			return;
		}
	}
	out[ 0x00 ] = true;
}

const std::wstring& AndCellProcessStrategy::cell_type_name()
{
	return cellTypeName;
}
