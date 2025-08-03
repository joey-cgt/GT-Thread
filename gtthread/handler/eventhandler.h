#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "basictypes.h"
#include "utils.h"
#include "location.h"
#include "eventcallback.h"

namespace gt
{
namespace event
{

class GEventCallbackBase;
class GEventBase;
using GEventPtr = std::shared_ptr<GEventBase>;

class GEventHandler
{
public:
    GEventHandler();
    ~GEventHandler();
    GEventHandler(const GEventHandler& other);
    // 全局函数的事件处理器
    explicit GEventHandler(UINT16 eventId, bool (*pFunc)(GEventPtr));
    // 成员函数的事件处理器
    template<typename T>
    explicit GEventHandler(UINT16 eventId, T* pInstance, bool (T::*pFunc)(GEventPtr));
    UINT16 GetEventId();
    void SetEventId(UINT16 eventId);
    UINT64 GetRunThreadId();
    void SetRunThreadId(UINT64 nThreadId);
    gt::base::Location GetLocation();
    void SetLocation(const gt::base::Location& location);
    bool operator()(GEventPtr pEvent);
    bool operator==(const GEventHandler& other);

private:
    UINT16 m_eventId; // 事件ID
    UINT64 m_nThreadId; // 线程ID
    gt::base::Location m_location;
    gt::base::sp<GEventCallbackBase> m_pCallback; // 事件回调对象
};

template<typename T>
GEventHandler::GEventHandler(UINT16 eventId, T* pInstance, bool (T::*pFunc)(GEventPtr))
    : m_eventId(eventId)
    , m_nThreadId(gt::base::GetCurrentThreadId())
    , m_pCallback(std::make_shared<GMemberFuncCallback<T>>(pInstance, pFunc))
{
    
}

} // namespace event
} // namespace gt


#endif // __EVENT_HANDLER_H__