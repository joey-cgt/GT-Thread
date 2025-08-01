#ifndef  __EVENTEMEMPLATE_H__
#define  __EVENTEMEMPLATE_H__

#include <memory>
#include "basictypes.h"
#include "loopermanager.h"
#include "eventhandlermanager.h"
#include "eventiddefine.h"
#include "location.h"
#include "utils.h"

namespace gt
{
namespace event
{

class GEventBase : public GTaskBase, public std::enable_shared_from_this<GEventBase>
{
public:
    GEventBase(UINT8 eventClassId, UINT8 eventFunctionId)
        : m_classId(eventClassId), m_functionId(eventFunctionId) {}

    virtual ~GEventBase() = default;

    UINT8 GetClassId() const { return m_classId; }

    UINT8 GetFunctionId() const { return m_functionId; }

    gt::base::Location GetLocation() const { return m_location; }

    void SetLocation(const gt::base::Location& location) { m_location = location; }

    virtual bool Exec();

protected:
    UINT8 m_classId;
    UINT8 m_functionId;
    gt::base::Location m_location;
};


template<typename T>
class GBaseEvent1Param : public GEventBase
{
public:
    GBaseEvent1Param(UINT8 eventClassId, UINT8 eventFunctionId, T param)
        : GEventBase(eventClassId, eventFunctionId), m_param(param) {}

    virtual ~GBaseEvent1Param() = default;

    // 获取参数
    T getParam() const { return m_param; }
protected:
    T m_param;  // 事件参数
};

template<typename T1, typename T2>
class GBaseEvent2Param : public GEventBase
{
public:
    GBaseEvent2Param(UINT8 eventClassId, UINT8 eventFunctionId, T1 param1, T2 param2)
        : GEventBase(eventClassId, eventFunctionId), m_param1(param1), m_param2(param2) {}

    virtual ~GBaseEvent2Param() = default;

    // 获取参数
    T1 getParam1() const { return m_param1; }
    T2 getParam2() const { return m_param2; }

protected:
    T1 m_param1;  // 第一个事件参数
    T2 m_param2;  // 第二个事件参数
};

template<typename T1, typename T2, typename T3>
class GBaseEvent3Param : public GEventBase
{
public:
    GBaseEvent3Param(UINT8 eventClassId, UINT8 eventFunctionId, T1 param1, T2 param2, T3 param3)
        : GEventBase(eventClassId, eventFunctionId), m_param1(param1), m_param2(param2), m_param3(param3) {}

    virtual ~GBaseEvent3Param() = default;

    // 获取参数
    T1 getParam1() const { return m_param1; }
    T2 getParam2() const { return m_param2; }
    T3 getParam3() const { return m_param3; }

protected:
    T1 m_param1;  // 第一个事件参数
    T2 m_param2;  // 第二个事件参数
    T3 m_param3;  // 第三个事件参数
};

using GEventPtr = std::shared_ptr<GEventBase>;

} // namespace event
} // namespace gt

#endif  // __EVENTEMEMPLATE_H__