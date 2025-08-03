#include "eventhandlermanager.h"
#include "eventhandler.h"


namespace gt
{
namespace event
{

GEventHandlerManager& GEventHandlerManager::getInstance()
{
    static GEventHandlerManager instance;
    return instance;
}

GEventHandlerManager::GEventHandlerManager()
: m_mutex()
{
}

GEventHandlerManager::~GEventHandlerManager()
{
}

bool GEventHandlerManager::RegisterHandler(gt::base::sp<GEventHandler> pHandler)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_mapHandler.emplace(pHandler->GetEventId(), pHandler);
    return true;
}

bool GEventHandlerManager::UnRegisterHandler(gt::base::sp<GEventHandler> pHandler)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_mapHandler.begin();
    while(it != m_mapHandler.end())
    {
        if(it->first == pHandler->GetRunThreadId() && it->second == pHandler)
        {
            it = m_mapHandler.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return true;
}

std::list<gt::base::wp<GEventHandler>> GEventHandlerManager::GetHandlerList(UINT16 eventId, UINT32 threadId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    std::list<gt::base::wp<GEventHandler>> handlerList;
    auto it = m_mapHandler.begin();
    while(it != m_mapHandler.end())
    {
        if(it->first == eventId && it->second->GetRunThreadId() == threadId)
        {
            handlerList.push_back(it->second);
        }
        ++it;
    }
    return handlerList;
}

} // namespace event
} // namespace gt
