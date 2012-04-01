#include "cellview.h"

#include <stdexcept>
#include <QtGui>

const QColor CellView::grey = QColor::fromRgb( 0x80, 0x80, 0x80 );

CellView::CellView( Cell* cell, QString title /*= ""*/, qreal width /*= 20*/, qreal height /*= 30*/ )
	: QObject(), QGraphicsItem(), isSelected( false )
{
	if( NULL == cell )
	{
		throw std::logic_error( "NULL == cell" );
	}
	//assert( NULL != cell );
	this->cell = cell;
	titleText = QString::fromStdWString( cell->title() );

	cellRect.setWidth( width );
	cellRect.setHeight( height );
	resize_connectors_count( cell->in_count(), cell->out_count() );

	calc_rects();
}

CellView::~CellView()
{
	emit removed();
	disconnect_all_connectors();
	delete cell;
}

QRectF CellView::boundingRect() const
{
	return boundingCellRect;
}

void CellView::paint( QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget )
{
	paint_cell( painter, item, widget );
}

void CellView::mouseDoubleClickEvent( QGraphicsSceneMouseEvent *event )
{
	emit clicked();
}

void CellView::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
{
	QGraphicsItem::mouseMoveEvent( event );

	for( auto i = inConnectors.size(); i --> 0; )
	{
		if( NULL != inConnectors[ i ] )
		{
			inConnectors[ i ]->set_to( get_in_node_glob_coords( i ) );
		}
	}
	for( auto i = outConnectors.size(); i --> 0; )
	{
		if( NULL != outConnectors[ i ] )
		{
			outConnectors[ i ]->set_from( get_out_node_glob_coords( i ) );
		}
	}
}

QString CellView::title()
{
	return titleText;
}

void CellView::set_title( QString title )
{
	this->titleText = title;
	update();
}

void CellView::process()
{
	cell->process();
	update();
}

void CellView::stop_process()
{
	cell->stop_process();
}

void CellView::resize_connectors_count( size_t newInCount, size_t newOutCount )
{
	if( newInCount < inConnectors.size() )
	{
		for( auto it = inConnectors.begin() + newInCount, end = inConnectors.end();
				 it != end; ++it )
		{
			if( NULL != *it )
			{
				scene()->removeItem( *it );
				delete *it;
				*it = NULL;
			}
		}
	}
	if( newOutCount < outConnectors.size() )
	{
		for( auto it = outConnectors.begin() + newInCount, end = outConnectors.end();
				 it != end; ++it )
		{
			if( NULL != *it )
			{
				scene()->removeItem( *it );
				delete *it;
				*it = NULL;
			}
		}
	}
	inConnectors.resize( newInCount );
	outConnectors.resize( newOutCount );
	cell->resize_node_count( newInCount, newOutCount );

	update();
}

void CellView::connect_to_in( CellView* targetOutCellView, size_t targetOutId, size_t inId )
{
	disconnect_from_in( inId );
	targetOutCellView->disconnect_from_out( targetOutId );
	cell->connect_to_in( *targetOutCellView->cell, targetOutId, inId );

	inConnectors[ inId ] = new ConnectorView( targetOutCellView, targetOutId,
																						this, inId,
																						targetOutCellView->get_out_node_glob_coords( targetOutId ),
																						get_in_node_glob_coords( inId ) );

	targetOutCellView->outConnectors[ targetOutId ] = inConnectors[ inId ];

	scene()->addItem( inConnectors[ inId ] );
	update();
}

void CellView::disconnect_from_in( size_t inId )
{
	if( NULL == inConnectors[ inId ] )
	{
		return;
	}
	cell->disconnect_from_in( inId );

	scene()->removeItem( inConnectors[ inId ] );

	inConnectors[ inId ]->from()->outConnectors[ inConnectors[ inId ]->out_id() ] = NULL;
	delete inConnectors[ inId ];
	inConnectors[ inId ] = NULL;

	update();
}

void CellView::disconnect_from_out( size_t outId )
{
	if( NULL == outConnectors[ outId ] )
	{
		return;
	}
	cell->disconnect_from_out( outId );

	scene()->removeItem( outConnectors[ outId ] );

	outConnectors[ outId ]->to()->inConnectors[ outConnectors[ outId ]->in_id() ] = NULL;
	delete outConnectors[ outId ];
	outConnectors[ outId ] = NULL;

	update();
}

void CellView::disconnect_all_connectors()
{
	for( size_t i = inConnectors.size(); i --> 0; )
	{
		disconnect_from_in( i );
	}
	for( size_t i = outConnectors.size(); i --> 0; )
	{
		disconnect_from_out( i );
	}
}

QPointF CellView::get_in_node_glob_coords( size_t id )
{
	QRectF sbr = sceneBoundingRect();
	return QPointF( sbr.left() + cellRect.left() ,
									(	sbr.top() + tidr( cellRect.top() + PADDING_TOP ) +
										id*( wdr( FLAG_SIDE ) + MARGIN_MID ) + wdr( FLAG_SIDE )/2 ) );
}

QPointF CellView::get_out_node_glob_coords( size_t id )
{
	QPointF symmetric = get_in_node_glob_coords( id );
	symmetric.setX( symmetric.x() + cellRect.width() );
	return symmetric;
}

int CellView::wdr( int width )
{
	return width + 2*PEN_SIZE;
}

int CellView::hdr( int height )
{
	return height + 2*PEN_SIZE;
}

int CellView::lidr( int left )
{
	return left + PEN_SIZE;
}

int CellView::tidr( int top )
{
	return top + PEN_SIZE;
}

void CellView::paint_cell( QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget )
{
	painter->save();
	painter->drawText( titleRect, Qt::AlignLeft, titleText );
	draw_std_cell_nodes( painter );
	painter->restore();
}

void CellView::draw_std_cell_nodes( QPainter *painter )
{
//	static int lol = 10;
//	lol--;
//	if( 0 == lol )
//	{
//		lol = 10;
//		cell->process();
//	}
	if( isSelected )
	{
		painter->setPen( grey );
	}
	painter->drawRect( cellRect );

	draw_std_cell_nodes( painter, cell->ibus(),
											 lidr( cellRect.left() + MARGIN_SIDE ) ,
											 tidr( cellRect.top() + PADDING_TOP ) );

	draw_std_cell_nodes( painter, cell->obus(),
											 lidr( cellRect.left() + MARGIN_SIDE ) + wdr( FLAG_SIDE ) + MARGIN_MID,
											 tidr( cellRect.top() + PADDING_TOP ) );
}

template <typename T>
void CellView::draw_std_cell_nodes( QPainter *painter, T& bus, int x, int y )
{
	for( size_t i = 0, end = bus.size(); i < end; ++i )
	{
		if( bus[ i ] )
		{
			painter->fillRect( x, y, FLAG_SIDE, FLAG_SIDE , Qt::black );
		}
		else
		{
			painter->drawRect( x, y, FLAG_SIDE, FLAG_SIDE );
		}
		y += wdr( FLAG_SIDE ) + MARGIN_MID;
	}
}

void CellView::update()
{
	calc_rects();
	QGraphicsItem::update( boundingRect() );
}

void CellView::calc_rects()
{
	calc_title_rect();
	calc_cell_rect();
	calc_bounding_rect();

	calc_rects_translation();
}

void CellView::calc_title_rect()
{
	QFontMetrics fm( QApplication::font() );
	titleRect = fm.boundingRect( titleText );
	titleRect.setWidth( titleRect.width() );

	titleRect.moveTo( 0, 0 );
}

void CellView::calc_cell_rect()
{
	auto maxNodeCount = ( cell->in_count() < cell->out_count() ) ? cell->out_count() : cell->in_count();
	cellRect.moveTo( 0, 0 );

	cellRect.setWidth( 2*( MARGIN_SIDE + wdr( FLAG_SIDE ) ) + MARGIN_MID );
	// мб тут погрешность с CORRECTED_ONE, который не вычитается
	cellRect.setHeight( PADDING_TOP + PADDING_BOTTOM +
											( maxNodeCount )*( hdr( FLAG_SIDE ) + MARGIN_MID ) -
											( maxNodeCount ? MARGIN_MID : 0 ) );
}

void CellView::calc_bounding_rect()
{
	qreal resultHeight = hdr( cellRect.height() ) + titleRect.height() + GAP_TITLE_TOP;
	qreal resultWidth = ( wdr( cellRect.width() ) > titleRect.width() )
												? wdr ( cellRect.width() ) : titleRect.width();

	boundingCellRect = QRectF( 0, 0, resultWidth, resultHeight );
}

void CellView::calc_rects_translation()
{
	cellRect.translate( 0 , GAP_TITLE_TOP + titleRect.height() );

	int cw = wdr( cellRect.width() );
	int tw = titleRect.width();
	int res;
	if( cw > tw )
	{
		res = cw - tw;
		res /= 2;
		titleRect.translate( res , 0 );
	}
	else
	{
		res = tw - cw;
		res /= 2;
		cellRect.translate( res, 0 );
	}
}


