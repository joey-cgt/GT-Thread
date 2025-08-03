#ifndef  __EVENT_ID_DEFINE_H__
#define  __EVENT_ID_DEFINE_H__

#include "basictypes.h"

#define EVENT_ID(classId, functionId) \
    ((classId << 8) | functionId)
    
using CLASSID = UINT8; // 事件类ID类型
using FUNCTIONID = UINT8; // 事件函数ID类型

const CLASSID EVENT_CLASS_ID_TEST = 0x01;
const FUNCTIONID EVENT_FUNCTION_ID_TEST_PRINT = 0x01;

#endif // __EVENT_ID_DEFINE_H__