#include "location.h"

namespace gt
{
namespace base
{

Location::Location()
    : m_file("")
    , m_line(0)
{
}

Location::Location(const std::string& file, UINT32 line)
    : m_file(file)
    , m_line(line)
{
}

Location::~Location()
{
}

std::string Location::GetFile() const
{
    return m_file;
}

UINT32 Location::GetLine() const
{
    return m_line;
}

std::string Location::GetLocation() const
{
    return m_file + ":" + std::to_string(m_line);
}

} // namespace base
} // namespace gt
