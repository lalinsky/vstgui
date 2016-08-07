#ifndef __qtfont__
#define __qtfont__

#include "../iplatformfont.h"
#include "../../vstguibase.h"
#include <QFont>

namespace VSTGUI {

class QtFont : public IPlatformFont
{
public:
    QtFont (UTF8StringPtr name, const CCoord& size, const int32_t& style);
    virtual ~QtFont ();

	virtual double getAscent () const override;
	virtual double getDescent () const override;
	virtual double getLeading () const override;
	virtual double getCapHeight () const override;

	virtual IFontPainter* getPainter () override;

private:
    QFont font;
};

} // namespace

#endif // __qtfont__
