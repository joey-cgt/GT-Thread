#ifndef __LOOPERMANAGER_H__
#define __LOOPERMANAGER_H__
#include <map>
#include <mutex>
#include <string>
#include "looper.h"
#include "utils.h"

namespace gt
{
namespace event
{

class GLooperManager
{
public:
    static GLooperManager& GetInstance();
    virtual ~GLooperManager();
    gt::base::wp<GLooper> GetLooperById(UINT64 threadId);
    gt::base::wp<GLooper> GetLooperByName(const std::string threadName);
    bool AddLooper(gt::base::wp<GLooper> pLooper);
    bool RemoveLooper(gt::base::wp<GLooper> pLooper);

private:
    GLooperManager();
    GLooperManager(const GLooperManager&) = delete;
    GLooperManager& operator=(const GLooperManager&) = delete;

private:
    std::map<UINT64, gt::base::wp<GLooper>> m_mapIdLooper;
    std::map<std::string, gt::base::wp<GLooper>> m_mapNameLooper;
    std::mutex m_mutex;
};

#define g_LooperManager GLooperManager::GetInstance()

}}

#endif // __LOOPERMANAGER_H__