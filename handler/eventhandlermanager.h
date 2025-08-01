#ifndef __EVENT_HANDLER_MANAGER_H__
#define __EVENT_HANDLER_MANAGER_H__

#include <unordered_map>
#include <list>
#include <mutex>
#include "utils.h"

namespace gt
{
namespace event
{

class GEventHandler;

class GEventHandlerManager
{
public:
    static GEventHandlerManager& getInstance();
    ~GEventHandlerManager();
    bool RegisterHandler(gt::base::sp<GEventHandler> pHandler);
    bool UnRegisterHandler(gt::base::sp<GEventHandler> pHandler);
    std::list<gt::base::wp<GEventHandler>> GetHandlerList(UINT16 eventId, UINT32 threadId);

private:
    GEventHandlerManager();
    GEventHandlerManager(const GEventHandlerManager&) = delete;
    GEventHandlerManager& operator=(const GEventHandlerManager&) = delete;

private:
    std::unordered_multimap<UINT16, gt::base::sp<GEventHandler>> m_mapHandler;
    std::mutex m_mutex;
};

#define g_EventHandlerManager GEventHandlerManager::getInstance()

} // namespace event
} // namespace gt


#endif  //__EVENT_HANDLER_MANAGER_H__