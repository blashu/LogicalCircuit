#include "OBusCellProcessStrategy.h"

const std::wstring OBusCellProcessStrategy::cellTypeName = L"output bus";

CellProcessStrategy* OBusCellProcessStrategy::clone() const
{
	return new OBusCellProcessStrategy();
}

size_t OBusCellProcessStrategy::inodes_min() const
{
	return 0x01;
}

size_t OBusCellProcessStrategy::inodes_max() const
{
	return MAX_NODE_COUNT;
}

size_t OBusCellProcessStrategy::onodes_min() const
{
	return 0x00;
}

size_t OBusCellProcessStrategy::onodes_max() const
{
	return 0x00;
}

void OBusCellProcessStrategy::do_process( const ibus_t& in, const obus_t& out )
{
}

const std::wstring& OBusCellProcessStrategy::cell_type_name()
{
	return cellTypeName;
}


