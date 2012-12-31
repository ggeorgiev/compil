#include "compil/factory.h"

namespace lang
{

namespace compil
{

FilterSPtr Factory::findFilter(const std::string& fieldName)
{
    const std::vector<FilterSPtr>& fltrs = filters();
    std::vector<FilterSPtr>::const_iterator it;
    for (it = fltrs.begin(); it != fltrs.end(); ++it)
    {
        FilterSPtr pFilter = *it;
        if (pFilter->field()->name()->value() == fieldName)
            return pFilter;

    }
    return FilterSPtr();
}
    
}

}