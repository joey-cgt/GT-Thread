#include "looper.h"
#include <future>
#include <boost/asio.hpp>
#include "loopermanager.h"

namespace gt
{
namespace event
{

GLooper::GLooper(UINT64 threadId, const std::string &name)
    : m_nThreadId(threadId)
    , m_bStopped(false)
    , m_strName(name)
{
    m_pIoContext = std::make_shared<boost::asio::io_context>();
}

GLooper::~GLooper()
{
    m_bStopped = true;
    if (m_pIoContext)
    {
        m_pIoContext->stop();
        m_pIoContext.reset();
    }
    m_taskQueue.ClearTask();
}

bool GLooper::PostTask(GTaskBasePtr pTask)
{
    if (!pTask || m_bStopped)
    {
        return false;
    }
    
    if(m_taskQueue.AddTask(pTask))
    {
        gt::base::wp<GLooper> weakPtr = shared_from_this();
        boost::asio::post(*m_pIoContext, [weakPtr](){
            gt::base::sp<GLooper> realPtr = weakPtr.lock();
            if(realPtr && !realPtr->IsStopped())
            {
                realPtr->m_taskQueue.RunAllTasks();
            }
        });
        return true;
    }
    return false;
}

bool GLooper::DoTask(GTaskBasePtr pTask)
{
    if (!pTask || m_bStopped)
    {
        return false;
    }

    if(m_nThreadId == gt::base::GetCurrentThreadId())
    {
        return pTask->Run();
    }
    else
    {
        gt::base::wp<GLooper> weakPtr = shared_from_this();
        //使用future和promise实现同步
        std::promise<bool> promise;
        std::future<bool> future = promise.get_future();
        boost::asio::post(*m_pIoContext, [weakPtr,pTask, &promise](){
            gt::base::sp<GLooper> realPtr = weakPtr.lock();
            if(!realPtr)
            {
                promise.set_value(false);
            }
            else
            {
                bool ret = pTask->Run();
                promise.set_value(ret);
            }
        });
        return future.get();
    }
}

void GLooper::Loop()
{
    g_LooperManager.AddLooper(shared_from_this());
    if(m_pIoContext)
    {
        boost::asio::io_context::work work(*(m_pIoContext.get()));
        m_pIoContext->run();
    }
    g_LooperManager.RemoveLooper(shared_from_this());
}

void GLooper::Stop()
{
    m_bStopped = true;
    if(m_pIoContext)
    {
        m_pIoContext->stop();
    }
}

bool GLooper::IsStopped()
{
    return m_bStopped;
}

UINT64 GLooper::GetThreadId() const
{
    return m_nThreadId;
}

std::string GLooper::GetThreadName() const
{
    return m_strName;
}


} // namespace event
} // namespace gt
