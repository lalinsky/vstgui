#ifndef __qtbitmap__
#define __qtbitmap__

#include "../iplatformbitmap.h"
#include <QPixmap>

namespace VSTGUI {

class QtBitmap : public IPlatformBitmap
{
public:
    QtBitmap();
    QtBitmap(const CPoint& size);
    virtual ~QtBitmap();

	virtual bool load (const CResourceDescription& desc) override;
	virtual const CPoint& getSize () const override;

	virtual IPlatformBitmapPixelAccess* lockPixels (bool alphaPremultiplied) override;
	
	virtual void setScaleFactor (double factor) override;
	virtual double getScaleFactor () const override;

private:
    QPixmap pixmap;
    CPoint size;
};

} // namespace

#endif // __qtbitmap__
