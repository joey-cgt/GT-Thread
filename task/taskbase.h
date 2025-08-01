#ifndef __TASK_BASE_H__
#define __TASK_BASE_H__

#include <functional>
#include <memory>
#include "utils/utils.h"
#include "location.h"

namespace gt
{
namespace event
{
enum TaskType
{
    NONE,
    EVENT,
    TASK,
};

class GTaskBase
{
public:
    GTaskBase();
    GTaskBase(TaskType taskType);
    GTaskBase(TaskType taskType, const gt::base::Location& location);
    virtual ~GTaskBase();
    TaskType GetTaskType() const;
    gt::base::Location GetLocation() const;
    void SetTaskType(const TaskType taskType);
    void SetLocation(const gt::base::Location& location);
    bool Run();
protected:
    // 任务执行接口
    virtual bool Exec() = 0;

private:
    TaskType m_taskType;
    gt::base::Location m_location;
};

using GTaskBasePtr = gt::base::sp<GTaskBase>; // 任务指针类型

} // namespace event 
} // namespace gt

#endif // __TASK_BASE_H__