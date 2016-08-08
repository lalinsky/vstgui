#include "../../cpoint.h"
#include "../../cresourcedescription.h"
#include "qtbitmap.h"
#include "qtutils.h"

#include <QDebug>
#include <QBuffer>

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

IPlatformBitmap* IPlatformBitmap::createFromPath (UTF8StringPtr absolutePath)
{
	QImage image;
	image.load (QString::fromUtf8 (absolutePath));
	return new QtBitmap (image);
}

IPlatformBitmap* IPlatformBitmap::createFromMemory (const void* ptr, uint32_t memSize)
{
	QImage image;
	image.loadFromData ((const uchar*) ptr, memSize);
	return new QtBitmap (image);
}

bool IPlatformBitmap::createMemoryPNGRepresentation (IPlatformBitmap* bitmap, void** ptr, uint32_t& size)
{
	QByteArray ba;
	QBuffer buffer (&ba);
	buffer.open (QIODevice::WriteOnly);
	bool saved = dynamic_cast<QtBitmap*> (bitmap)->getQImage ().save (&buffer, "PNG");
	if (saved) {
		size = ba.size ();
		*ptr = malloc (size);
		memcpy (*ptr, ba.data (), size);
	}
	return saved;
}

QtBitmap::QtBitmap ()
: image (0, 0, QImage::Format_ARGB32)
{
}

QtBitmap::QtBitmap (const CPoint& size)
: image (size.x, size.y, QImage::Format_ARGB32)
, size (size)
{
	image.fill (qRgba (0, 0, 0, 0));
}

QtBitmap::QtBitmap (const QImage& im)
: image (im)
, size (makeCPoint (im.size ()))
{
	if (image.format () != QImage::Format_ARGB32)
		image = image.convertToFormat (QImage::Format_ARGB32);
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
