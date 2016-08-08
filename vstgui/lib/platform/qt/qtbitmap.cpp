#include "../../cpoint.h"
#include "../../cresourcedescription.h"
#include "qtbitmap.h"

#include <QDebug>

namespace VSTGUI {

struct QtBitmapPixelAccess : public IPlatformBitmapPixelAccess
{
	QtBitmapPixelAccess (QImage* image) : image (image) {}

	virtual uint8_t* getAddress () const override
	{
		return image->bits ();
	}

	virtual uint32_t getBytesPerRow () const override
	{
		return image->bytesPerLine ();
	}

	virtual PixelFormat getPixelFormat () const override
	{
		return kARGB;
	}

	QImage* image;
};

IPlatformBitmap* IPlatformBitmap::create (CPoint* size)
{
    if (size)
        return new QtBitmap (*size);
    return new QtBitmap ();
}

QtBitmap::QtBitmap ()
{
}

QtBitmap::QtBitmap (const CPoint& size)
: image (size.x, size.y, QImage::Format_ARGB32)
, size (size)
{
	image.fill (qRgba (0, 0, 0, 0));
}

QtBitmap::~QtBitmap ()
{
}

bool QtBitmap::load (const CResourceDescription& desc)
{
    if (desc.type == CResourceDescription::kStringType) {
        const bool result = image.load (desc.u.name);
		if (result && image.format () != QImage::Format_ARGB32)
			image = image.convertToFormat (QImage::Format_ARGB32);
		size.x = image.size ().width ();
		size.y = image.size ().height ();
		return result;
	}
    return false;
}

const CPoint& QtBitmap::getSize () const
{
    return size;
}

IPlatformBitmapPixelAccess* QtBitmap::lockPixels (bool alphaPremultiplied)
{
	return new QtBitmapPixelAccess (&image);
}

void QtBitmap::setScaleFactor (double factor)
{
	scaleFactor = factor;
}

double QtBitmap::getScaleFactor () const
{
    return scaleFactor;
}

} // namespace
