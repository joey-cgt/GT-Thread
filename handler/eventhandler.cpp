#include "eventhandler.h"
#include "eventcallback.h"
#include "eventtemplate.h"

namespace gt
{
namespace event
{
GEventHandler::GEventHandler()
{
}

GEventHandler::~GEventHandler()
{
}

GEventHandler::GEventHandler(const GEventHandler &other)
    : m_eventId(other.m_eventId)
    , m_nThreadId(other.m_nThreadId)
    , m_pCallback(other.m_pCallback)
{
}

GEventHandler::GEventHandler(UINT16 eventId, bool (*pFunc)(GEventPtr))
    : m_eventId(eventId)
    , m_nThreadId(gt::base::GetCurrentThreadId())
    , m_pCallback(std::make_shared<GGlobalFuncCallback>(pFunc))
{
}

UINT16 GEventHandler::GetEventId()
{
    return m_eventId;
}


void GEventHandler::SetEventId(UINT16 eventId)
{
    m_eventId = eventId;
}

UINT64 GEventHandler::GetRunThreadId()
{
    return m_nThreadId;
}

void GEventHandler::SetRunThreadId(UINT64 nThreadId)
{
    m_nThreadId = nThreadId;
}

gt::base::Location GEventHandler::GetLocation()
{
    return m_location;
}

void GEventHandler::SetLocation(const gt::base::Location& location)
{
    m_location = location;
}

bool GEventHandler::operator()(GEventPtr pEvent)
{
    return (*m_pCallback)(pEvent);
}

bool GEventHandler::operator==(const GEventHandler& other)
{
    if(!other.m_pCallback || !m_pCallback)
    {
        return false;
    }
    return (*other.m_pCallback == *m_pCallback) && (m_nThreadId == other.m_nThreadId);
}

} // namespace event
} // namespace gt