#include "ConnectorView.h"

#include <QtGui>
#include "Logger.h"

ConnectorView::ConnectorView( CellView* fromCell, size_t outId,
															CellView* toCell, size_t inId,
															QPointF worldFrom, QPointF worldTo )
{
	_fromCell = fromCell;
	_toCell = toCell;
	_worldFrom = worldFrom;
	_worldTo = worldTo;
	_inId = inId;
	_outId = outId;

	calc_bounding_and_line_rect();
}

QRectF ConnectorView::boundingRect() const
{
	return boundingConnectorRect;
}

void ConnectorView::paint( QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget )
{
	painter->save();
	painter->drawLine( resLine );
	painter->restore();
}

CellView* ConnectorView::from()
{
	return _fromCell;
}

CellView* ConnectorView::to()
{
	return _toCell;
}

size_t ConnectorView::out_id()
{
	return _outId;
}

size_t ConnectorView::in_id()
{
	return _inId;
}

void ConnectorView::set_from( QPointF point )
{
	_worldFrom.setX( point.x() );
	_worldFrom.setY( point.y() );

	ConnectorView::update();
}

void ConnectorView::set_to( QPointF point )
{
	_worldTo.setX( point.x() );
	_worldTo.setY( point.y() );

	ConnectorView::update();
}

void ConnectorView::update()
{
	calc_bounding_and_line_rect();
	//QGraphicsItem::update( boundingConnectorRect );
}

void ConnectorView::calc_bounding_and_line_rect()
{
	auto sbr = sceneBoundingRect();
	qreal left, top, height, width;
	qreal toX = 0, toY = 0, fromX = 0, fromY = 0;

	if( _worldTo.y() < _worldFrom.y() )
	{
		top = _worldTo.y();
		height = _worldFrom.y() - _worldTo.y();
		fromY = height;
	}
	else
	{
		top = _worldFrom.y();
		height = _worldTo.y() - _worldFrom.y();
		toY = height;
	}
	if( _worldTo.x() < _worldFrom.x() )
	{
		left = _worldTo.x();
		width = _worldFrom.x() - _worldTo.x();
		fromX = width;
	}
	else
	{
		left = _worldFrom.x();
		width = _worldTo.x() - _worldFrom.x();
		toX = width;
	}

	boundingConnectorRect.moveTo( 0,0 );

	setPos( -sceneBoundingRect().width(), -sceneBoundingRect().height() );
	setPos( left, top );

	resLine.setLine( toX, toY, fromX, fromY );

	prepareGeometryChange();
	boundingConnectorRect.setHeight( height );
	boundingConnectorRect.setWidth( width );
}
