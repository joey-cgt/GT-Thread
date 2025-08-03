#ifndef  __EVENTDEFINE_H__
#define  __EVENTDEFINE_H__

#include "eventtemplate.h"
#include "eventiddefine.h"

namespace gt
{
namespace event
{

class GEventTestPrint : public GBaseEvent1Param<std::string>
{
public:
    GEventTestPrint(const std::string& message)
        : GBaseEvent1Param(EVENT_CLASS_ID_TEST, EVENT_FUNCTION_ID_TEST_PRINT, message) {}

    virtual ~GEventTestPrint() = default;
};

}  // event   
}  // gt
#endif // __EVENTDEFINE_H__