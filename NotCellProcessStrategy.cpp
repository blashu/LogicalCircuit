#include "NotCellProcessStrategy.h"

const std::wstring NotCellProcessStrategy::cellTypeName = L"not";

CellProcessStrategy* NotCellProcessStrategy::clone() const
{
        return new NotCellProcessStrategy();
}

size_t NotCellProcessStrategy::inodes_min() const
{
        return 1;
}

size_t NotCellProcessStrategy::inodes_max() const
{
        return 1;
}

size_t NotCellProcessStrategy::onodes_min() const
{
        return 1;
}

size_t NotCellProcessStrategy::onodes_max() const
{
        return 1;
}

void NotCellProcessStrategy::do_process( const ibus_t& in, const obus_t& out )
{

        if( true == in[ 0x00 ] )
        {
            out[ 0x00 ] = false;
            return;
        }
        else if ( false == in[ 0x00 ] )
        {
            out[ 0x00 ] = true;
            return;
        }
}

const std::wstring& NotCellProcessStrategy::cell_type_name()
{
        return cellTypeName;
}
