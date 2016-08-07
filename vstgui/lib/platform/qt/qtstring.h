#ifndef __qtstring__
#define __qtstring__

#include "../iplatformstring.h"

#include <QString>

namespace VSTGUI {

class QtString : public IPlatformString
{
public:
    QtString (UTF8StringPtr utf8String);
    ~QtString ();
	
    virtual void setUTF8String (UTF8StringPtr utf8String) override;

private:
    QString string;
};

} // namespace

#endif // __qtstring__
