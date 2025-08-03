#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include "taskbase.h"

namespace gt
{
namespace event
{
#define MAX_TASK_QUEUE_SIZE 512 // 最大任务队列大小

class GTaskQueue
{
public:
    GTaskQueue();
    virtual ~GTaskQueue();
    
    bool RunAllTasks();
    bool RunOneTask();
    bool AddTask(GTaskBasePtr pTask);
    void ClearTask();
    GTaskBasePtr PopOneTask();

private:
    std::queue<GTaskBasePtr> m_taskQueue; // 任务队列
    std::mutex m_queueMutex; // 互斥锁
};

} // namespace event
} // namespace gt


#endif // __TASK_QUEUE_H__