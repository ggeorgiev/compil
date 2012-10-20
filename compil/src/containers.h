// Boost C++ Smart Pointers
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
// Standard Template Library
#include <string>
#include <vector>

#ifndef __GENERATOR_TEST_CONTAINERS_COMPIL_H_
#define __GENERATOR_TEST_CONTAINERS_COMPIL_H_

#include "containers.h"

class ContainersStructure
{
public:
    // Default constructor
                                            ContainersStructure ();
    // Destructor
    /*lax*/                                 ~ContainersStructure();

    // Getter method for the data field vs
            const std::vector<std::string>& vs                  ()                                   const;
    // Setter method for the data field vs
            ContainersStructure&            set_vs              (const std::vector<std::string>& vs);
    // Provides mutable access to field vs
            std::vector<std::string>&       mutable_vs          ();

private:
    // variable for the data field vs
    std::vector<std::string> mVs;
};

#else // __GENERATOR_TEST_CONTAINERS_COMPIL_H_

// Forward declarations
class ContainersStructure;
typedef ContainersStructure*                         ContainersStructureRPtr;
typedef boost::shared_ptr<ContainersStructure>       ContainersStructureSPtr;
typedef boost::shared_ptr<const ContainersStructure> ContainersStructureSCPtr;
typedef boost::weak_ptr<ContainersStructure>         ContainersStructureWPtr;

#endif // __GENERATOR_TEST_CONTAINERS_COMPIL_H_

