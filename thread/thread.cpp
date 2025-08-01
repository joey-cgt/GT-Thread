#include "thread.h"
#include "taskbase.h"
#include "work.h"

namespace gt
{
namespace thread
{

using namespace gt::base;
using namespace gt::event;

GThread::GThread(const std::string& name)
    : m_strThreadName(name)
{
    
}

GThread::~GThread()
{
}

UINT64 GThread::GetThreadId() const
{
    return m_nThreadId;
}

std::string GThread::GetThreadName() const
{
    return m_strThreadName;
}

void GThread::Start()
{
    m_pThread = std::make_shared<std::thread>(&GThread::ThreadMain, this);
}

void GThread::Run()
{
    ThreadMain();
}

void GThread::ThreadMain()
{
    m_nThreadId = gt::base::GetCurrentThreadId();
    gt::base::SetThreadName(m_strThreadName);

    m_pLooper = std::make_shared<GLooper>(m_nThreadId, m_strThreadName);

    GWorkPtr pFirstTask = CreateWork(FROM_HERE,[this](){
        if(this->m_bRunning)
        {
            this->AfterThreadLaunched(); 
        }
    });

    m_pLooper->PostTask(pFirstTask);
    m_bRunning = true;
    m_pLooper->Loop();
    m_bRunning = false;
    BeforeThreadShutdown();
}


} // namespace thread
} // namespace gt




