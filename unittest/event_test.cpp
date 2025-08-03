#include <gtest/gtest.h>
#include "task/event/eventdefine.h"

using namespace gt::event;
using namespace gt::base;

GEventTestPrint event("hello world");

TEST(EventTest, TestId)
{
    EXPECT_EQ(event.GetClassId(), 1);
    EXPECT_EQ(event.GetFunctionId(), 1);
}

TEST(EventTest, TestParam)
{
    EXPECT_EQ(event.GetParam(), "hello world");
}

