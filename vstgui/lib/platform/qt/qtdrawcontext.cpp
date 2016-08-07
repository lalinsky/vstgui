#include "qtdrawcontext.h"
#include "qtbitmap.h"

#include "../../cbitmap.h"

#include <QDebug>
#include <QPainter>

namespace VSTGUI {

QtDrawContext::QtDrawContext (QPainter* painter)
: CDrawContext (CRect (0, 0, 300, 300))
, painter (painter)
{
}

void QtDrawContext::drawLine (const LinePair& line)
{
	painter->drawLine (line.first.x, line.first.y, line.second.x, line.second.y);
}

void QtDrawContext::drawLines (const LineList& lines)
{
	QVector<QLineF> qlines;
	qlines.reserve (lines.size ());
	for (const auto &line : lines) {
		qlines.append (QLineF (line.first.x, line.first.y, line.second.x, line.second.y));
	}
	painter->drawLines (qlines);
}

void QtDrawContext::drawBitmap (CBitmap* bitmap, const CRect& dest, const CPoint& offset, float alpha)
{
	qDebug() << "drawBitmap";
	QRect target (dest.left, dest.top, dest.getWidth (), dest.getHeight ());
	const QPixmap& pixmap = ( static_cast<QtBitmap*> (bitmap->getPlatformBitmap ()) )->getQPixmap ();
	painter->drawPixmap(target, pixmap);
}

} // namespace
