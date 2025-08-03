#ifndef __THREAD_H__
#define __THREAD_H__
#include <thread>
#include <memory>
#include <atomic>
#include <string>
#include "taskbase.h"
#include "utils/utils.h"
#include "basictypes.h"
#include "looper.h"

namespace gt
{
namespace thread
{

class GThread
{
public:
    GThread(const std::string& name);
    virtual ~GThread();

    void Start();
    void Run();
    void ThreadMain(); 
    virtual void AfterThreadLaunched() = 0;
    virtual bool OnTask(gt::event::GTaskBasePtr pTask) = 0;
    virtual void BeforeThreadShutdown() = 0;
    UINT64 GetThreadId() const;
    std::string GetThreadName() const;

private:
    UINT64 m_nThreadId;
    std::string m_strThreadName;
    gt::base::sp<std::thread> m_pThread;
    gt::base::sp<gt::event::GLooper> m_pLooper;
    std::atomic<bool> m_bRunning;
};

} // namespace thread
} // namespace gt
 
#endif // __THREAD_H__