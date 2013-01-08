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

#include "core/configuration/configuration_manager.h"

#include <boost/program_options.hpp>
#include <boost/program_options/parsers.hpp>

#include <iostream>
#include <fstream>

namespace bpo = boost::program_options;

namespace compil
{

ConfigurationManager::ConfigurationManager()
{
}

ConfigurationManager::~ConfigurationManager()
{
}

void ConfigurationManager::registerConfiguration(const ConfigurationSPtr& configuration)
{
    mvConfiguration.push_back(configuration);
}

bool ConfigurationManager::parse(int argc, const char **argv, const std::string& defaultConfigFile)
{
	try
    {
        mVariablesMap.clear();
        
        bpo::options_description commandLineOptions;
        bpo::positional_options_description commandLinePositionalOptions;
        unsigned positional_option_index = 0;

        std::string commandLineExtraPositionalOptions;

        std::vector<ConfigurationSPtr>::iterator itc;
        for (itc = mvConfiguration.begin(); itc != mvConfiguration.end(); ++itc)
        {
            const ConfigurationSPtr& configuration = *itc;
            commandLineOptions.add(configuration->commandLineOptions());

            string_vector positional_options = configuration->commandLinePositionalOptions();
            string_vector::iterator itp;
            for (itp = positional_options.begin(); itp != positional_options.end(); ++itp)
                commandLinePositionalOptions.add(itp->c_str(), ++positional_option_index);

            std::string commandLineExtra = configuration->commandLineExtraPositionalOptions();
            if (!commandLineExtra.empty())
            {
                if (!commandLineExtraPositionalOptions.empty())
                {
                    std::cout << "more than one configuration with extra positional option." << std::endl;
                    return false;
                }
                commandLineExtraPositionalOptions = commandLineExtra;
            }
        }

        if (!commandLineExtraPositionalOptions.empty())
            commandLinePositionalOptions.add(commandLineExtraPositionalOptions.c_str(), -1);

        bpo::parsed_options parsed = bpo::command_line_parser(argc, argv)
                                                        .style(  bpo::command_line_style::unix_style
                                                               & ~bpo::command_line_style::allow_sticky)
                                                        .options(commandLineOptions)
                                                        .positional(commandLinePositionalOptions)
                                                        .allow_unregistered()
                                                        .run();
        bpo::store(parsed, mVariablesMap);
        bpo::notify(mVariablesMap);
        
        std::string configFile = defaultConfigFile;
        if (mVariablesMap.count("config"))
            configFile = mVariablesMap["config"].as<const std::string>();
            
        if (!configFile.empty())
        {
            // The section that loads config values from files
            bpo::options_description configurationOptions;
            for (itc = mvConfiguration.begin(); itc != mvConfiguration.end(); ++itc)
            {
                const ConfigurationSPtr& configuration = *itc;
                configurationOptions.add(configuration->configurationOptions());
            }

            std::ifstream configurationFS;
            configurationFS.open(configFile.c_str());

            if (configurationFS.good())
            {
                bpo::store(bpo::parse_config_file(configurationFS, configurationOptions),
                    mVariablesMap);
                bpo::notify(mVariablesMap);
                configurationFS.close();
            }
        }
    }
    catch (bpo::error error)
    {
        std::cout << "boost::program_options parse error:" << error.what() << std::endl;
        return false;
    }

    return true;
}

void ConfigurationManager::printVersion() const
{
    std::cout << "Compil 0.0.0.\nCopyright (C) 2011 George Georgiev\n";
}

void ConfigurationManager::printHelp() const
{
    printVersion();
    
    bpo::options_description helpOptions;
    std::vector<ConfigurationSPtr>::const_iterator it;
    for (it = mvConfiguration.begin(); it != mvConfiguration.end(); ++it)
    {
        helpOptions.add((*it)->commandLineOptions());
    }
    
    std::cout << helpOptions;
}

}
