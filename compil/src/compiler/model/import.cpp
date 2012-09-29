#include "import.h"

namespace compil
{

Import::Import()
{
}

Import::~Import()
{
}

ImportSPtr Import::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Import>(object);
}

const std::string& Import::source() const
{
    return mSource;
}

Import& Import::set_source(const std::string& source)
{
    mSource = source;
    return *this;
}

std::string& Import::mutable_source()
{
    return mSource;
}

}

