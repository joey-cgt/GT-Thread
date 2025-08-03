#ifndef __WORK_H__
#define __WORK_H__

#include <memory>
#include "taskbase.h"
#include "location.h"

namespace gt
{
namespace event
{

typedef std::function<void()> TaskFunc; 

class GWork : public GTaskBase
{
public:
    GWork(const gt::base::Location& location, const TaskFunc& taskFunc);
    virtual ~GWork();
    virtual bool Exec() override;

private:
    TaskFunc m_taskFunc;
};

using GWorkPtr = std::shared_ptr<GWork>;

GWorkPtr CreateWork(const gt::base::Location& location, const TaskFunc& taskFunc);

} // namespace event    
} // namespace gt

#endif  // __WORK_H__
