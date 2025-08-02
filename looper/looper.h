#ifndef __LOOPER_H__
#define __LOOPER_H__

#include <atomic>
#include <boost/asio.hpp>
#include <string>
#include <memory>
#include "utils/utils.h"
#include "taskqueue.h"

namespace gt
{
namespace event
{

class GLooper : public std::enable_shared_from_this<GLooper>
{
public:
    GLooper(UINT64 threadId, const std::string& name);
    virtual ~GLooper();

    bool PostTask(GTaskBasePtr pTask);
    bool DoTask(GTaskBasePtr pTask);
    void Loop();
    void Stop();
    bool IsStopped();
    UINT64 GetThreadId();
    std::string GetThreadName();
    gt::base::wp<boost::asio::io_context> GetIoContext();

private:
    std::atomic<UINT64> m_nThreadId;
    std::string m_strName;
    std::atomic<bool> m_bStopped;
    gt::base::sp<boost::asio::io_context> m_pIoContext;
    GTaskQueue m_taskQueue;
};

} // namespace gt
} // namespace event


#endif // __LOOPER_H__