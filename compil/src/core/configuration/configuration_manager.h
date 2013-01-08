// CompIL - Component Interface Language
// Copyright 2011 George Georgiev.  All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * The name of George Georgiev can not be used to endorse or 
// promote products derived from this software without specific prior 
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: george.georgiev@hotmail.com (George Georgiev)
//

#include <boost/shared_ptr.hpp>

#ifndef _CONFIGURATION_MANAGER_H__
#define _CONFIGURATION_MANAGER_H__

#include "configuration.h"
#include <vector>

namespace compil
{

class ConfigurationManager
{
public:
    ConfigurationManager();
    virtual ~ConfigurationManager();
    
    void registerConfiguration(const ConfigurationSPtr& configuration);
    
    bool parse(int argc, const char **argv, const std::string& defaultConfigFile = "");
    
    void printVersion() const;
    void printHelp() const;
    
    template <class T>
    const boost::shared_ptr<T> getConfiguration() const
    {
        std::vector<ConfigurationSPtr>::const_iterator it;
        for (it = mvConfiguration.begin(); it != mvConfiguration.end(); ++it)
        {
            if (T::staticName() == (*it)->name())
                return boost::static_pointer_cast<T>(*it);
        }
        return boost::shared_ptr<T>();
    }
    
private:
    bpo::variables_map mVariablesMap;
    std::vector<ConfigurationSPtr> mvConfiguration;
    
};

typedef boost::shared_ptr<ConfigurationManager> ConfigurationManagerPtr;
typedef boost::weak_ptr<ConfigurationManager> ConfigurationManagerWPtr;

}

#endif // _CONFIGURATION_MANAGER_H__

