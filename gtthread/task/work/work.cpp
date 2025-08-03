#include "work.h"

namespace gt
{
namespace event
{

GWork::GWork(const gt::base::Location& location, const TaskFunc& taskFunc)
    : GTaskBase(TaskType::EVENT, location)
    , m_taskFunc(taskFunc)
{

}

GWork::~GWork()
{

}

bool GWork::Exec()
{
    if (m_taskFunc) {
        m_taskFunc();
        return true;
    }
    return false;
}

GWorkPtr CreateWork(const gt::base::Location& location, const TaskFunc& taskFunc)
{
    GWorkPtr pWork = std::make_shared<GWork>(location, taskFunc);
    return pWork;
}

} // namespace event
} // namespace gt

