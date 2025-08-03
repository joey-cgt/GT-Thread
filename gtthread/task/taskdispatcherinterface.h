#ifndef __TASK_DISPATCHER_INTERFACE_H__
#define __TASK_DISPATCHER_INTERFACE_H__

#include <string>
#include "basictypes.h"
#include "eventtemplate.h"
#include "utils/utils.h"
#include "location.h"
#include "work.h"
#include "eventtemplate.h"


namespace gt
{
namespace task
{

bool PostWork(const gt::base::Location& location, const std::string& targetThreadName, const gt::event::TaskFunc& pTask);
bool PostWork(const gt::base::Location& location, UINT64 targetThreadId, const gt::event::TaskFunc& pTask);
bool DoWork(const gt::base::Location& location, const std::string& targetThreadName, const gt::event::TaskFunc& pTask);
bool DoWork(const gt::base::Location& location, UINT64 targetThreadId, const gt::event::TaskFunc& pTask);
bool PostEvent(const gt::base::Location& location, const std::string& targetThreadName, gt::event::GEventPtr pEvent);
bool PostEvent(const gt::base::Location& location, UINT64 targetThreadId, gt::event::GEventPtr pEvent);
bool DoEvent(const gt::base::Location& location, const std::string& targetThreadName, gt::event::GEventPtr pEvent);
bool DoEvent(const gt::base::Location& location, UINT64 targetThreadId, gt::event::GEventPtr pEvent);
bool RegisterHandler(const gt::base::Location& location, const gt::event::GEventHandler& handler);
bool UnregisterHandler(const gt::event::GEventHandler& handler);
#define RegisterClassHandler(eventId, obj, func) RegisterHandler(gt::base::FROM_HERE, gt::event::GEventHandler(eventId, obj, func))
#define UnregisterClassHandler(eventId, obj, func) UnRegisterHandler(gt::event::GEventHandler(eventId, obj, func))
#define RegisterGlobalHandler(eventId, func) RegisterHandler(gt::base::FROM_HERE, gt::event::GEventHandler(eventId, func))
#define UnregisterGlobalHandler(eventId, func) UnRegisterHandler(gt::event::GEventHandler(eventId, func))

}
}

#endif // __TASK_DISPATCHER_INTERFACE_H__