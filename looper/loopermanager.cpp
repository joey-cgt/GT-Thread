#include "loopermanager.h"

namespace gt
{
namespace event
{

GLooperManager::GLooperManager()
{
}
GLooperManager::~GLooperManager()
{
}

gt::base::wp<GLooper> GLooperManager::GetLooperById(UINT64 threadId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    gt::base::wp<GLooper> weakPtr;
    auto it = m_mapIdLooper.find(threadId);
    if(it != m_mapIdLooper.end())
    {
        weakPtr = it->second;
    }
    return weakPtr;
}

gt::base::wp<GLooper> GLooperManager::GetLooperByName(const std::string threadName)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    gt::base::wp<GLooper> weakPtr;
    auto it = m_mapNameLooper.find(threadName);
    if(it != m_mapNameLooper.end())
    {
        weakPtr = it->second;
    }
    return weakPtr;
}

bool GLooperManager::AddLooper(gt::base::wp<GLooper> pLooper)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    gt::base::sp<GLooper> realPtr = pLooper.lock();
    if(!realPtr)
    {
        return false;
    }
    // 会覆盖已存在的key value
    m_mapIdLooper[realPtr->GetThreadId()] = pLooper;
    m_mapNameLooper[realPtr->GetThreadName()] = pLooper;
    return true;
}

bool GLooperManager::RemoveLooper(gt::base::wp<GLooper> pLooper)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    gt::base::sp<GLooper> realPtr = pLooper.lock();
    if(!realPtr)
    {
        return false;
    }
    // erase是安全的
    m_mapIdLooper.erase(realPtr->GetThreadId());
    m_mapNameLooper.erase(realPtr->GetThreadName());
    return true;
}
GLooperManager& GLooperManager::GetInstance()
{
    static GLooperManager instance;
    return instance;
}

} // namespace event
} // namespace gt
