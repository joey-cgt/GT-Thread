#include "taskqueue.h"

namespace gt
{
namespace event
{
GTaskQueue::GTaskQueue()
{
}

GTaskQueue::~GTaskQueue()
{
    ClearTask();
}

bool GTaskQueue::RunAllTasks()
{
    bool bResult = false;
    while(RunOneTask())
    {
        bResult = true;
    }
    return bResult;
}

bool GTaskQueue::RunOneTask()
{
    bool bResult = false;
    GTaskBasePtr pTask = PopOneTask();
    if (pTask) {
        pTask->Run();
        bResult = true;
    }
    return bResult;
}

GTaskBasePtr GTaskQueue::PopOneTask()
{
    std::unique_lock<std::mutex> lock(m_queueMutex);

    if (m_taskQueue.empty()) 
    {
        return nullptr;
    }

    GTaskBasePtr pTask = m_taskQueue.front();
    m_taskQueue.pop();

    return pTask;
}

bool GTaskQueue::AddTask(GTaskBasePtr pTask)
{
    if (!pTask) {
        return false; // 无效任务
    }

    std::unique_lock<std::mutex> lock(m_queueMutex);

    if (m_taskQueue.size() >= MAX_TASK_QUEUE_SIZE) 
    {
        return false;
    }
    m_taskQueue.push(pTask);
    return true;
}

void GTaskQueue::ClearTask()
{
    std::unique_lock<std::mutex> lock(m_queueMutex);
    while(m_taskQueue.size() > 0) 
    {
        m_taskQueue.pop();
    }
}



} // namespace event
} // namespace gt
