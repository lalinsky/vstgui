#ifndef __qtframe__
#define __qtframe__

#include "../../cframe.h"

namespace VSTGUI {

class QtFrame : public IPlatformFrame
{
public:
	QtFrame (IPlatformFrameCallback* frame, const CRect& size, QWidget* parent);
	~QtFrame ();

	virtual bool getGlobalPosition (CPoint& pos) const override;
	virtual bool setSize (const CRect& newSize) override;
	virtual bool getSize (CRect& size) const override;
	
	virtual bool getCurrentMousePosition (CPoint& mousePosition) const override;
	virtual bool getCurrentMouseButtons (CButtonState& buttons) const override;
	virtual bool setMouseCursor (CCursorType type) override;
	
	virtual bool invalidRect (const CRect& rect) override;
	virtual bool scrollRect (const CRect& src, const CPoint& distance) override;

	virtual bool showTooltip (const CRect& rect, const char* utf8Text) override;
	virtual bool hideTooltip () override;

	virtual void* getPlatformRepresentation () const override;

	virtual IPlatformTextEdit* createPlatformTextEdit (IPlatformTextEditCallback* textEdit) override; ///< create a native text edit control
	virtual IPlatformOptionMenu* createPlatformOptionMenu () override; ///< create a native popup menu
	
	virtual IPlatformViewLayer* createPlatformViewLayer (IPlatformViewLayerDelegate* drawDelegate, IPlatformViewLayer* parentLayer = 0) override; ///< create a native view layer, may return 0 if not supported
	
	virtual COffscreenContext* createOffscreenContext (CCoord width, CCoord height, double scaleFactor = 1.) override; ///< create an offscreen draw device

	virtual DragResult doDrag (IDataPackage* source, const CPoint& offset, CBitmap* dragBitmap) override;

	virtual void setClipboard (IDataPackage* data) override;
	virtual IDataPackage* getClipboard () override;

private:
	class ProxyWidget;
	ProxyWidget* widget;
};

} // namespace

#endif // __qtframe__
