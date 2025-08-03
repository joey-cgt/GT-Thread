#include "timer.h"
#include <chrono>
#include "utils.h"
#include "loopermanager.h"

namespace gt
{
namespace event
{

using namespace gt::base;
using namespace gt::event;

GTimer::GTimer()
: m_nInterval(0)
, m_nTriggerTimes(0)
{
    m_nRunThreadId = gt::base::GetCurrentThreadId();
}

GTimer::~GTimer()
{
    CancelTimer();
}

bool GTimer::SetSingleTimer(const gt::base::Location& location, const TimerCallback& callback, UINT32 interval)
{
    return SetPeriodTimer(location, callback, interval, 1);
}

bool GTimer::SetPeriodTimer(const gt::base::Location& location, const TimerCallback& callback, UINT32 interval, INT32 triggerTimes)
{
    if(!CreateTimer())
    {
        return false;
    }

    
    if(interval <= 0)
    {
        return false;
    }
    
    m_pTimer->cancel(); // 先重置

    m_callback = callback;
    m_nInterval = interval;
    m_nTriggerTimes = triggerTimes;
    m_location = location;

    m_pTimer->expires_after(std::chrono::milliseconds(interval));
    auto self = shared_from_this();
    m_pTimer->async_wait([self](const boost::system::error_code& error)
    {
        if(!error)
        {
            self->DispatcherTimer();
        }
        else if (boost::asio::error::basic_errors::operation_aborted == error.value())
        {
            // 主动停止定时器            
        }
        else
        {
            // 其他错误
        }
    });
    return true;
}

void GTimer::DispatcherTimer()
{
    if(!IsRunning())
    {
        return;
    }

    if(m_pTimer && (m_nTriggerTimes > 0 || m_nTriggerTimes == -1)) // -1表示无限次
    {
        if(m_callback)
        {
            m_callback();
        }

        if (m_nTriggerTimes != -1)  
        {
            m_nTriggerTimes--;
        }
        
        m_pTimer->expires_after(std::chrono::milliseconds(m_nInterval));
        m_pTimer->async_wait([this](const boost::system::error_code& error)
        {
            if(!error)
            {
                DispatcherTimer();
            }
            else if (boost::asio::error::basic_errors::operation_aborted == error.value())
            {
                // 主动停止定时器                
            }
            else
            {
                // 其他错误
            }
        });
    }

    if(m_nTriggerTimes == 0)
    {
        CancelTimer();
    }
    return;
}

bool GTimer::CancelTimer()
{
    m_nInterval = 0;
    m_nTriggerTimes = 0;
    if(m_pTimer)
    {
        m_pTimer->cancel();
    }
    return true;
}

bool GTimer::CreateTimer()
{
    if(m_pTimer)
    {
        return false;
    }
    
    sp<GLooper> pLooper = g_LooperManager.GetLooperById(m_nRunThreadId).lock();
    
    if(!pLooper)
    {
        return false;
    }

    sp<boost::asio::io_context> pIoContext = pLooper->GetIoContext().lock();
    if(!pIoContext)
    {
        return false;
    }

    m_pTimer = std::make_shared<boost::asio::steady_timer>(*pIoContext);
    return true;
}

bool GTimer::IsRunning()
{
    // 1. 检查定时器对象是否存在
    if (!m_pTimer) 
    {
        return false;
    }
    
    // 2. 检查是否设置了到期时间（不等于默认构造的time_point）
    if (m_pTimer->expiry() == boost::asio::steady_timer::time_point()) 
    {
        return false;
    }
    
    // 3. 检查是否设置了有效回调
    if (!m_callback) 
    {
        return false;
    }
    
    // 4. 检查是否还有剩余触发次数
    if (m_nTriggerTimes == 0) 
    {
        return false;
    }
    
    // 5. 最后检查时间是否未到期
    return m_pTimer->expiry() > std::chrono::steady_clock::now();
}

}  // namespace event
}  // namespace gt
