#include <gtest/gtest.h>
#include "handler/eventhandler.h"
#include "thread"

using namespace gt::event;
using namespace gt::base;

static int number = 0;

bool testFunc(std::shared_ptr<GEventBase> event)
{
    number = 1;
    return true;
}

UINT8 classId = 2;
UINT8 functionId = 2;
UINT16 eventId = classId << 8 | functionId;
std::shared_ptr<GEventBase> pEvent = std::make_shared<GEventBase>(classId, functionId);

TEST(EventHandlerTest, TestGlobalHandler)
{
    EXPECT_EQ(pEvent->GetEventId(), eventId);
    GEventHandler eventHandler(pEvent->GetEventId(), testFunc);
    EXPECT_EQ(eventHandler.GetEventId(), pEvent->GetEventId());
    std::string file = __FILE__;
    UINT32 line = __LINE__;
    Location location(file, line);
    eventHandler.SetLocation(location);
    std::string info = file + ":" + std::to_string(line);
    EXPECT_EQ(eventHandler.GetLocation().GetInfo(), info);
    EXPECT_EQ(eventHandler.GetRunThreadId(), GetCurrentThreadId());
    std::thread t1([&]()
    {
        EXPECT_NE(eventHandler.GetRunThreadId(), GetCurrentThreadId());
    });
    t1.join();
    eventHandler(pEvent);
    EXPECT_EQ(number, 1);
}

class TestClass
{
public:
    TestClass(){};
    bool OnEvent(std::shared_ptr<GEventBase> pEvent)
    {
        number = 3;
        return true;
    }
};

TEST(EventHandlerTest, TestMemberHandler)
{
    TestClass testClass;
    GEventHandler eventHandler(eventId, &testClass, &TestClass::OnEvent);
    eventHandler(pEvent);
    EXPECT_EQ(number, 3);
}


