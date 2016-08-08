#ifndef __qtdrawcontext__
#define __qtdrawcontext__

#include "../../cdrawcontext.h"

namespace VSTGUI {

class QtDrawContext : public CDrawContext
{
public:
	QtDrawContext (QPainter* painter);

	virtual void drawLine (const LinePair& line) override;
	virtual void drawLines (const LineList& lines) override;
	virtual void drawPolygon (const PointList& polygonPointList, const CDrawStyle drawStyle = kDrawStroked) override {}
	virtual void drawRect (const CRect &rect, const CDrawStyle drawStyle = kDrawStroked) override;
	virtual void drawArc (const CRect &rect, const float startAngle1, const float endAngle2, const CDrawStyle drawStyle = kDrawStroked) override {}
	virtual void drawEllipse (const CRect &rect, const CDrawStyle drawStyle = kDrawStroked) override {}
	virtual void drawPoint (const CPoint &point, const CColor& color) override {}
	virtual void drawBitmap (CBitmap* bitmap, const CRect& dest, const CPoint& offset = CPoint (0, 0), float alpha = 1.f) override;

	virtual void clearRect (const CRect& rect) override {}

	virtual CGraphicsPath* createGraphicsPath () override { return 0; }
	virtual CGraphicsPath* createTextPath (const CFontRef font, UTF8StringPtr text) override { return 0; }

	virtual void drawGraphicsPath (CGraphicsPath* path, PathDrawMode mode = kPathFilled, CGraphicsTransform* transformation = 0) override {}
	virtual void fillLinearGradient (CGraphicsPath* path, const CGradient& gradient, const CPoint& startPoint, const CPoint& endPoint, bool evenOdd = false, CGraphicsTransform* transformation = 0) override {}
	virtual void fillRadialGradient (CGraphicsPath* path, const CGradient& gradient, const CPoint& center, CCoord radius, const CPoint& originOffset = CPoint (0,0), bool evenOdd = false, CGraphicsTransform* transformation = 0) override {}

private:
	QPainter* painter;
};

} // namespace

#endif
