#include "OrCellProcessStrategy.h"

const std::wstring OrCellProcessStrategy::cellTypeName = L"or";

CellProcessStrategy* OrCellProcessStrategy::clone() const
{
	return new OrCellProcessStrategy();
}

size_t OrCellProcessStrategy::inodes_min() const
{
	return 2;
}

size_t OrCellProcessStrategy::inodes_max() const
{
	return 2;
}

size_t OrCellProcessStrategy::onodes_min() const
{
	return 1;
}

size_t OrCellProcessStrategy::onodes_max() const
{
	return 1;
}

void OrCellProcessStrategy::do_process( const ibus_t& in, const obus_t& out )
{
	for( size_t i = in.size(); i --> 0x00; )
	{
		if( true == in[ i ] )
		{
			out[ 0x00 ] = true;
			return;
		}
	}
	out[ 0x00 ] = false;
}

const std::wstring& OrCellProcessStrategy::cell_type_name()
{
	return cellTypeName;
}
