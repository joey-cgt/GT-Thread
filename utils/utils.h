#ifndef __UTILS_H__
#define __UTILS_H__

#include <memory> 
#include <string> 

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif

#include "basictypes.h"

namespace gt
{
namespace base
{

template<typename T>
using sp = std::shared_ptr<T>;  // 智能指针别名

template<typename T>
using up = std::unique_ptr<T>;    // 智能指针别名

template<typename T>
using wp = std::weak_ptr<T>;      // 弱引用智能指针别名


UINT64 GetCurrentThreadId();
void SetThreadName(const std::string& name);

} // namespace base    
} // namespace gt

#endif // __UTILS_H__


