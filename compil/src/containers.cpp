#include "containers.h"

ContainersStructure::ContainersStructure()
{
}

ContainersStructure::~ContainersStructure()
{
}

const std::vector<std::string>& ContainersStructure::vs() const
{
    return mVs;
}

ContainersStructure& ContainersStructure::set_vs(const std::vector<std::string>& vs)
{
    mVs = vs;
    return *this;
}

std::vector<std::string>& ContainersStructure::mutable_vs()
{
    return mVs;
}

