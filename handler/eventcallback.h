#ifndef  __EVENT_CALLBACK_H__
#define  __EVENT_CALLBACK_H__

#include "eventtemplate.h"

namespace gt
{
namespace event
{

class GEventCallbackBase
{
public:
    virtual ~GEventCallbackBase() = default;
    // 处理事件回调
    virtual bool operator()(GEventPtr pEvent) = 0;
    virtual bool operator==(const GEventCallbackBase& funcObj) = 0;
};

// 全局函数仿函数
class GGlobalFuncCallback : public GEventCallbackBase
{   
public:
    typedef bool (*CallbackFuncPtr)(GEventPtr);
    GGlobalFuncCallback(CallbackFuncPtr pFunc)
        : m_pFunc(pFunc) 
    {
        
    }

    virtual bool operator()(GEventPtr pEvent) override
    {   
        return m_pFunc(pEvent);
    }

    virtual bool operator==(const GEventCallbackBase& funcObj) override
    {
        const GGlobalFuncCallback* pOther = dynamic_cast<const GGlobalFuncCallback*>(&funcObj);
        if (pOther)
        {
            return m_pFunc == pOther->m_pFunc;
        }
        return false;
    }
    
private:
    CallbackFuncPtr m_pFunc; // 成员函数指针
};


// 成员函数仿函数
template<typename T>
class GMemberFuncCallback : public GEventCallbackBase
{
public:
    typedef bool (T::*CallbackFuncPtr)(GEventPtr);
    GMemberFuncCallback(T* pInstance, CallbackFuncPtr pFunc)
        : m_pInstance(pInstance)
        , m_pFunc(pFunc) 
    {
        
    }

    virtual bool operator()(GEventPtr pEvent) override
    {
        return (m_pInstance->*m_pFunc)(pEvent);
    }

    virtual bool operator==(const GEventCallbackBase& funcObj) override
    {
        const GMemberFuncCallback* pOther = dynamic_cast<const GMemberFuncCallback*>(&funcObj);
        if (pOther)
        {
            return m_pInstance == pOther->m_pInstance && m_pFunc == pOther->m_pFunc;
        }
        return false;
    }

private:
    T* m_pInstance; // 实例指针
    CallbackFuncPtr m_pFunc; // 成员函数指针
};

} // namespace event
} // namespace gt

#endif  // __EVENT_CALLBACK_H__