#include "IBusCellProcessStrategy.h"

const std::wstring IBusCellProcessStrategy::cellTypeName = L"input bus";

CellProcessStrategy* IBusCellProcessStrategy::clone() const
{
	return new IBusCellProcessStrategy();
}

size_t IBusCellProcessStrategy::inodes_min() const
{
	return 0x00;
}

size_t IBusCellProcessStrategy::inodes_max() const
{
	return 0x00;
}

size_t IBusCellProcessStrategy::onodes_min() const
{
	return 0x01;
}

size_t IBusCellProcessStrategy::onodes_max() const
{
	return MAX_NODE_COUNT;
}

void IBusCellProcessStrategy::do_process( const ibus_t& in, const obus_t& out )
{
	if( has_just_started() )
	{
		initialize_out( out );
		return;
	}
	increment_out( out );
}

const std::wstring& IBusCellProcessStrategy::cell_type_name()
{
	return cellTypeName;
}

