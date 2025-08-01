#include "utils.h"

namespace gt {
namespace base {    

UINT64 GetCurrentThreadId() {
#ifdef _WIN32
    return static_cast<UINT64>(GetCurrentThreadId());
#else
    return static_cast<UINT64>(pthread_self());
#endif
}

void SetThreadName(const std::string& name)
{
#if SYSTEM_WINDOWS
    setThreadName(-1, name.c_str());
#elif defined(SYSTEM_MACOS) || defined(SYSTEM_IOS)
    pthread_setname_np(name.substr(0, 15).c_str());
#else
    pthread_setname_np(pthread_self(), name.substr(0, 15).c_str());
#endif
}

}
}