#ifndef __LOCATION_H__
#define __LOCATION_H__

#include <string>
#include "basictypes.h"

namespace gt
{
namespace base
{

class Location
{
public:
    Location();
    Location(const std::string& file, UINT32 line);
    virtual ~Location();
    std::string GetFile() const;
    UINT32 GetLine() const;
    std::string GetInfo() const;

private:
    std::string m_file;
    UINT32 m_line;
};

#define FROM_HERE gt::base::Location(__FILE__, __LINE__)

} // namespace base    
} // namespace gt


#endif