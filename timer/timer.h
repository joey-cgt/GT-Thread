#ifndef __TIMER_H__
#define __TIMER_H__

#include <boost/asio.hpp>
#include <functional>
#include <memory>
#include "utils.h"
#include "basictypes.h"
#include "location.h"

namespace gt
{
namespace event
{

typedef std::function<void()> TimerCallback;

class GTimer : public std::enable_shared_from_this<GTimer>
{
public:
    GTimer();
    virtual ~GTimer();
    bool SetSingleTimer(const gt::base::Location& location, const TimerCallback& callback, UINT32 interval);
    bool SetPeriodTimer(const gt::base::Location& location, const TimerCallback& callback, UINT32 interval, INT32 triggerTimes = -1);
    void DispatcherTimer();
    bool CancelTimer();
    bool IsRunning();

private:
    bool CreateTimer();
private:
    gt::base::sp<boost::asio::steady_timer> m_pTimer;
    TimerCallback m_callback;
    INT32 m_nTriggerTimes;
    UINT32 m_nInterval;
    UINT32 m_nRunThreadId;
    gt::base::Location m_location;
};


}  // namespace event
}  // namespace gt
#endif