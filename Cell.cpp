#include "Cell.h"

Cell::Cell( CellProcessStrategy* ps ) :
//	iBus( this, ( NULL == ps ) ? 0x00 : ps->inodes_min(), ( NULL == ps ) ? 0x00 : ps->inodes_max() ),
//	oBus( this, ( NULL == ps ) ? 0x00 : ps->inodes_min(), ( NULL == ps ) ? 0x00 : ps->inodes_max() )
	iBus( ( NULL == ps ) ? 0x00 : ps->inodes_min(), ( NULL == ps ) ? 0x00 : ps->inodes_max() ),
	oBus( ( NULL == ps ) ? 0x00 : ps->onodes_min(), ( NULL == ps ) ? 0x00 : ps->onodes_max() )
{
	processStrategy = ps;
}

Cell::~Cell()
{
	if( NULL != processStrategy )
	{
		delete processStrategy;
	}
}

void Cell::process()
{
	if( NULL != processStrategy )
	{
		processStrategy->process( iBus, oBus );
	}
}

void Cell::stop_process()
{
	if( NULL != processStrategy )
	{
		processStrategy->stop_process();
	}
}

size_t Cell::in_count() const
{
	return iBus.size();
}

size_t Cell::in_min_size() const
{
	return iBus.min_size();
}

size_t Cell::in_max_size() const
{
	return iBus.max_size();
}

bool Cell::in_node( size_t id )
{
	return iBus[ id ];
}

void Cell::connect_to_in( Cell& targetCell, size_t targetOutId, size_t inId )
{
	connect_to_in( &(targetCell.oBus[ targetOutId ]), inId );
}

void Cell::connect_to_in( ONode* oNode, size_t inId )
{
	iBus.connect( oNode, inId );
}

void Cell::disconnect_from_in( size_t inId )
{
	iBus.disconnect( &iBus[ inId ] );
}

size_t Cell::out_count() const
{
	return oBus.size();
}

size_t Cell::out_min_size() const
{
	return oBus.min_size();
}

size_t Cell::out_max_size() const
{
	return oBus.max_size();
}

bool Cell::out_node( size_t id )
{
	return oBus[ id ];
}

void Cell::connect_to_out( Cell& targetCell, size_t targetInId, size_t outId )
{
	connect_to_out( &(targetCell.iBus[ targetInId ]), outId );
}

void Cell::connect_to_out( INode* iNode, size_t outId )
{
	oBus.connect( iNode, outId );
}

void Cell::disconnect_from_out( size_t outId )
{
	oBus.disconnect( &oBus[ outId ] );
}

void Cell::resize_node_count( size_t newInCount, size_t newOutCount )
{
	iBus.resize( newInCount );
	oBus.resize( newOutCount );
}
