#include "qtdrawcontext.h"
#include "qtbitmap.h"
#include "qtutils.h"

#include "../../cbitmap.h"

#include <QDebug>
#include <QPainter>

namespace VSTGUI {

QtDrawContext::QtDrawContext (QPainter* painter)
: CDrawContext (makeCRect (painter->viewport ()))
, painter (painter)
{
	init ();
}

void QtDrawContext::drawLine (const LinePair& line)
{
	qDebug() << "drawLine";
	painter->drawLine (line.first.x, line.first.y, line.second.x, line.second.y);
}

void QtDrawContext::drawLines (const LineList& lines)
{
	qDebug() << "drawLines";
	QVector<QLineF> qlines;
	qlines.reserve (lines.size ());
	for (const auto& line : lines) {
		qlines.append (QLineF (line.first.x, line.first.y, line.second.x, line.second.y));
	}
	painter->drawLines (qlines);
}

void QtDrawContext::drawBitmap (CBitmap* bitmap, const CRect& dest, const CPoint& offset, float alpha)
{
	qDebug() << "drawBitmap";
	const auto target = makeQRectF (dest);
	const auto pixmap = ( static_cast<QtBitmap*> (bitmap->getPlatformBitmap ()) )->getQPixmap ();
	const auto source = QRectF (offset.x, offset.y,	pixmap.width () - offset.x, pixmap.height () - offset.y);
	painter->drawPixmap(target, pixmap, source);
}

void QtDrawContext::drawRect (const CRect &rect, const CDrawStyle drawStyle)
{
	qDebug() << "drawRect";
	painter->drawRect (rect.left, rect.top, rect.getWidth (), rect.getHeight ());
}


} // namespace
