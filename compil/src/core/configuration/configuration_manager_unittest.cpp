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

#include "configuration.h"
#include "configuration_manager.h"

#include "gtest/gtest.h"

#include <boost/filesystem.hpp>

#include <fstream>

class TestConfiguration : public compil::Configuration
{
public:
    virtual std::string name() { return "test"; }
    
    virtual bpo::options_description commandLineOptions()
    {
        bpo::options_description options("Test Configuration");
        options.add_options()
            ("config,c", bpo::value<std::string>(&config), "config file")
            ("test", bpo::value<std::string>(&test), "test")
            ;
        return options;
    }

    virtual bpo::options_description configurationOptions()
    {
        bpo::options_description options("Test File Configuration");
        options.add_options()
            ("test", bpo::value<std::string>(&test), "test")
            ;
        return options;
    }
    
    std::string config;
    std::string test;
};

typedef boost::shared_ptr<TestConfiguration> TestConfigurationPtr;

TEST(TestConfigurationManager, construct)
{
    compil::ConfigurationManagerPtr pConfigurationManager(new compil::ConfigurationManager());
    TestConfigurationPtr pConfiguration(new TestConfiguration());
    
    pConfigurationManager->registerConfiguration(pConfiguration);
    
    boost::filesystem::path configFile = "config.ini";
    
    std::ofstream stream;
    stream.open(configFile.string().c_str());
    stream << "test=config\n";
    stream.close();
    
    const char* arg[] = { "@@@path", "-c", "config.ini", "--test=commandline" };
    
    pConfigurationManager->parse(1, arg);
    EXPECT_STREQ(pConfiguration->config.c_str(), "");
    EXPECT_STREQ(pConfiguration->test.c_str(), "");
    
    pConfigurationManager->parse(3, arg);
    EXPECT_STREQ(pConfiguration->config.c_str(), "config.ini");
    EXPECT_STREQ(pConfiguration->test.c_str(), "config");
    
    pConfigurationManager->parse(4, arg);
    EXPECT_STREQ(pConfiguration->config.c_str(), "config.ini");
    EXPECT_STREQ(pConfiguration->test.c_str(), "commandline");
    
    boost::filesystem::remove(configFile);
}