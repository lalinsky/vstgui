#ifndef __qttimer__
#define __qttimer__

#include "../iplatformtimer.h"

#include <QTimer>

namespace VSTGUI {

class QtTimer : public IPlatformTimer
{
public:
    QtTimer (IPlatformTimerCallback* callback);
    virtual ~QtTimer ();

	virtual bool start (uint32_t fireTime) override;
	virtual bool stop () override;

private:
    QTimer timer;
};

} // namespace

#endif // __qttimer__
