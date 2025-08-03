#include "taskbase.h"

namespace gt
{
namespace event
{

GTaskBase::GTaskBase()
: m_taskType(TaskType::NONE)
{
}

GTaskBase::GTaskBase(TaskType taskType)
: m_taskType(taskType)
{
}

GTaskBase::GTaskBase(TaskType taskType, const gt::base::Location& location)
: m_taskType(taskType)
, m_location(location)
{
}

GTaskBase::~GTaskBase()
{
}

bool GTaskBase::Run()
{
    return Exec();
}

TaskType GTaskBase::GetTaskType() const
{
    return m_taskType;
}

gt::base::Location GTaskBase::GetLocation() const
{
    return m_location;
}

void GTaskBase::SetTaskType(const TaskType taskType)
{
    m_taskType = taskType;
}

void GTaskBase::SetLocation(const gt::base::Location& location)
{
    m_location = location;
}

} // namespace event
} // namespace gt
