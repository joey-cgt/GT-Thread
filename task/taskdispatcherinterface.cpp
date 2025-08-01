#include "taskdispatcherinterface.h"
#include "eventhandler.h"
#include "loopermanager.h"
#include "looper.h"

namespace gt
{
namespace task
{

using namespace gt::event;
using namespace gt::base;

bool PostWork(const gt::base::Location& location, const std::string& targetThreadName, const gt::event::TaskFunc& pTask)
{
    gt::base::sp<gt::event::GLooper> realPtr = g_LooperManager.GetLooperByName(targetThreadName).lock();
    if (realPtr)
    {
        return false;
    }
    GWorkPtr pWork = CreateWork(location, pTask);
    return realPtr->PostTask(pWork);
}

bool PostWork(const gt::base::Location& location, UINT64 targetThreadId, const gt::event::TaskFunc& pTask)
{
    gt::base::sp<gt::event::GLooper> realPtr = g_LooperManager.GetLooperById(targetThreadId).lock();
    if (!realPtr)
    {
        return false;
    }
    GWorkPtr pWork = CreateWork(location, pTask);
    return realPtr->PostTask(pWork);
}

bool DoWork(const gt::base::Location& location, const std::string& targetThreadName, const gt::event::TaskFunc& pTask)
{
    gt::base::sp<gt::event::GLooper> realPtr = g_LooperManager.GetLooperByName(targetThreadName).lock();
    if (!realPtr)
    {
        return false;
    }
    GWorkPtr  pWork = CreateWork(location, pTask);
    return realPtr->DoTask(pWork);
}

bool DoWork(const gt::base::Location& location, UINT64 targetThreadId, const gt::event::TaskFunc& pTask)
{
    gt::base::sp<gt::event::GLooper> realPtr = g_LooperManager.GetLooperById(targetThreadId).lock();
    if (!realPtr)
    {
        return false;
    }
    GWorkPtr pWork = CreateWork(location, pTask);
    return realPtr->DoTask(pWork);
}

bool PostEvent(const gt::base::Location& location, const std::string& targetThreadName, gt::event::GEventPtr pEvent)
{
    gt::base::sp<gt::event::GLooper> realPtr = g_LooperManager.GetLooperByName(targetThreadName).lock();
    if (!realPtr)
    {
        return false;
    }
    pEvent->SetLocation(location);
    return realPtr->PostTask(pEvent);
}

bool PostEvent(const gt::base::Location& location, UINT64 targetThreadId, gt::event::GEventPtr pEvent)
{
    gt::base::sp<gt::event::GLooper> realPtr = g_LooperManager.GetLooperById(targetThreadId).lock();
    if (!realPtr)
    {
        return false;
    }
    pEvent->SetLocation(location);
    return realPtr->PostTask(pEvent);
}

bool DoEvent(const gt::base::Location& location, const std::string& targetThreadName, gt::event::GEventPtr pEvent)
{
    gt::base::sp<gt::event::GLooper> realPtr = g_LooperManager.GetLooperByName(targetThreadName).lock();
    if (!realPtr)
    {
        return false;
    }
    pEvent->SetLocation(location);
    return realPtr->DoTask(pEvent);
}

bool DoEvent(const gt::base::Location& location, UINT64 targetThreadId, gt::event::GEventPtr pEvent)
{
    gt::base::sp<gt::event::GLooper> realPtr = g_LooperManager.GetLooperById(targetThreadId).lock();
    if (!realPtr)
    {
        return false;
    }
    pEvent->SetLocation(location);
    return realPtr->DoTask(pEvent); 
}

bool RegisterHandler(const gt::base::Location& location, const gt::event::GEventHandler& handler)
{
    gt::base::sp<gt::event::GEventHandler> pHandler = std::make_shared<gt::event::GEventHandler>(handler);
    pHandler->SetRunThreadId(gt::base::GetCurrentThreadId());
    pHandler->SetLocation(location);
    return g_EventHandlerManager.RegisterHandler(pHandler);
}

bool UnregisterHandler(const gt::event::GEventHandler& handler)
{
    gt::base::sp<gt::event::GEventHandler> pHandler = std::make_shared<gt::event::GEventHandler>(handler);
    pHandler->SetRunThreadId(gt::base::GetCurrentThreadId());
    return g_EventHandlerManager.UnRegisterHandler(pHandler);;
}

}
}
