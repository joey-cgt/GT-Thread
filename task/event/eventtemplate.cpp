#include "eventtemplate.h"
#include "eventhandler.h"

namespace gt
{
namespace event
{
    
bool GEventBase::Exec()
{
    UINT16 eventId = EVENT_ID(m_classId, m_functionId);
    std::list<gt::base::wp<GEventHandler>> handlerList = g_EventHandlerManager.GetHandlerList(eventId, gt::base::GetCurrentThreadId());
    
    for (auto& handler : handlerList)
    {
        gt::base::sp<GEventHandler> pHandler = handler.lock();
        if (pHandler)
        {
            (*pHandler)(shared_from_this());
        }
    }

    return true;
}

} // namespace event 
} // namespace gt
