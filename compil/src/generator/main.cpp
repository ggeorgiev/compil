#include <stdio.h>

#include "generator/cpp/c++_generator.h"
#include "generator/cpp/c++_h_generator.h"
#include "generator/cpp/c++_test_generator.h"
#include "generator/cpp/c++_flags_enumeration_generator.h"

#include "generator/project/generator_project.h"
#include "generator/project/file_source_provider.h"

#include "configuration_manager.h"
#include "general_configuration.h"
#include "generator_configuration.h"
#include "aligner_configuration.h"
#include "formatter_configuration.h"
#include "parser.h"

#include "partial_validator.h"


#include "library/compil/document.h"

#include "core/boost/boost_path.h"

#include "boost/make_shared.hpp"
#include "boost/algorithm/string.hpp"

#include <iostream>
#include <fstream>

static boost::shared_ptr<std::ostream> openStream(const boost::filesystem::path& path)
{
    boost::filesystem::create_directories(path.parent_path());
    boost::shared_ptr<std::ofstream> pOutput(new std::ofstream());
    pOutput->open(path.string().c_str());
    return pOutput;
}

static void closeStream(boost::shared_ptr<std::ostream>& pOutputStream)
{
    boost::shared_ptr<std::ofstream> pOutput = boost::static_pointer_cast<std::ofstream>(pOutputStream);
    pOutput->flush();
    pOutput->close();
}

int main(int argc, const char **argv)
{
    compil::ConfigurationManagerPtr pConfigurationManager(new compil::ConfigurationManager());

    GeneralConfigurationPtr pGeneralConfiguration(new GeneralConfiguration());
    pConfigurationManager->registerConfiguration(pGeneralConfiguration);

    GeneratorConfigurationPtr pGeneratorConfiguration(new GeneratorConfiguration());
    pConfigurationManager->registerConfiguration(pGeneratorConfiguration);

    AlignerConfigurationPtr pAlignerConfiguration(new AlignerConfiguration());
    pConfigurationManager->registerConfiguration(pAlignerConfiguration);

    FormatterConfigurationPtr pFormatterConfiguration(new FormatterConfiguration());
    pConfigurationManager->registerConfiguration(pFormatterConfiguration);

    ImplementerConfigurationPtr pImplementerConfiguration(new ImplementerConfiguration());
    pConfigurationManager->registerConfiguration(pImplementerConfiguration);

    if (!pConfigurationManager->parse(argc, argv, &pGeneralConfiguration->configuration_file))
    {
        std::cout << "failed to parse the arguments!!!\n";
        pConfigurationManager->printHelp();
        return 1;
    }

    if (pGeneralConfiguration->version)
    {
        pConfigurationManager->printVersion();
        return 0;
    }

    if (pGeneralConfiguration->help)
    {
        pConfigurationManager->printHelp();
        return 0;
    }

    compil::FileSourceProviderPtr pFileSourceProvider(new compil::FileSourceProvider());
    
#if 1
    string_vector sources;
    if (!pGeneratorConfiguration->sourceFile.empty())
        sources.push_back(pGeneratorConfiguration->sourceFile);

    compil::GeneratorProject project(pFileSourceProvider);
    if (!project.init(pGeneratorConfiguration->projectFile,
                      pGeneratorConfiguration->projectDirectory,
                      pGeneratorConfiguration->type,
                      sources,
                      pGeneratorConfiguration->importDirectories))
        return 1;
        
    if (!project.parseDocuments())
        return 1;
        
    if (!project.generate(boost::filesystem::resolve(pGeneratorConfiguration->output_directory)))
        return 1;
#endif

    boost::filesystem::path projectDirectory;
    if (pGeneratorConfiguration->projectDirectory.empty())
        projectDirectory = boost::filesystem::current_path();
    else
        projectDirectory = boost::filesystem::resolve(pGeneratorConfiguration->projectDirectory);
        
    boost::filesystem::path input_file_path =
        boost::filesystem::resolve(pGeneratorConfiguration->sourceFile);
    if (!boost::filesystem::exists(input_file_path))
    {
        std::cout << "compil input file doesn't exist!!!\n";
        return 1;
    }
    
    std::string absoluteProjectDirectory = boost::filesystem::absolute(projectDirectory).generic_string() + "/";
    
    std::string source_file;
    {
        std::string fp = boost::filesystem::absolute(input_file_path).generic_string();
        
        if (!boost::starts_with(fp, absoluteProjectDirectory))
        {
            std::cout << "the compil file is not in the project_directory!!!\n";
            return 1;
        }
        
        source_file = fp.substr(absoluteProjectDirectory.length());
    }
    
    std::vector<boost::filesystem::path> importDirectories;
    for (std::vector<std::string>::const_iterator it = pGeneratorConfiguration->importDirectories.begin(); it != pGeneratorConfiguration->importDirectories.end(); ++it)
    {
        boost::filesystem::path absolute_path(boost::filesystem::absolute(*it));
        importDirectories.push_back(absolute_path);
    }

    pFileSourceProvider->setImportDirectories(importDirectories);
    pFileSourceProvider->setWorkingDirectory(absoluteProjectDirectory);
    
    compil::PartialValidatorPtr pPartialValidator(
            new compil::PartialValidator(pGeneratorConfiguration->type));

    compil::ParserPtr pParser(new compil::Parser());
    pParser->addValidator(pPartialValidator);

    compil::DocumentSPtr document;
    compil::SourceIdSPtr sourceId = pFileSourceProvider->sourceId(compil::SourceIdSPtr(), source_file);
    bool bResult = pParser->parseDocument(pFileSourceProvider, sourceId, document);
    if (!bResult)
        return 1;

    compil::CppFormatterPtr pFormatter = boost::make_shared<compil::CppFormatter>
        (pConfigurationManager->getConfiguration<FormatterConfiguration>(), document->package());
    compil::CppImplementerPtr pImplementer = boost::make_shared<compil::CppImplementer>
        (pConfigurationManager->getConfiguration<ImplementerConfiguration>(), pFormatter);

    boost::filesystem::path output =
        boost::filesystem::resolve(pGeneratorConfiguration->output_directory);

    boost::filesystem::path core =
        boost::filesystem::resolve(pGeneratorConfiguration->core_directory);

    std::vector<compil::Dependency> coreDependencies;

    if (pGeneratorConfiguration->type == "main")
    {
        {
            boost::filesystem::path cpp_output = output;
            cpp_output /= document->name()->value() + pImplementer->applicationExtension();

            boost::shared_ptr<std::ostream> pOutput = openStream(cpp_output);

            compil::CppGenerator generator;
            bool bResult = generator.init("main",
                                          pConfigurationManager->getConfiguration<AlignerConfiguration>(),
                                          pFormatter,
                                          pImplementer,
                                          pOutput,
                                          document);
            if (bResult) generator.generate();

            closeStream(pOutput);

            if (!bResult)
                return 1;

            std::vector<compil::Dependency> dependencies = generator.getCoreDependencies();
            coreDependencies.insert(coreDependencies.end(), dependencies.begin(), dependencies.end());
        }
        {
            boost::filesystem::path cpp_h_output = output;
            cpp_h_output /= document->name()->value() + pImplementer->applicationHeaderExtension();

            boost::shared_ptr<std::ostream> pOutput = openStream(cpp_h_output);

            compil::CppHeaderGenerator generator;
            bool bResult = generator.init("main",
                                          pConfigurationManager->getConfiguration<AlignerConfiguration>(),
                                          pFormatter,
                                          pImplementer,
                                          pOutput,
                                          document);
            if (bResult) generator.generate();

            closeStream(pOutput);

            if (!bResult)
                return 1;

            std::vector<compil::Dependency> dependencies = generator.getCoreDependencies();
            coreDependencies.insert(coreDependencies.end(), dependencies.begin(), dependencies.end());
        }
    }

    else
    if (pGeneratorConfiguration->type == "partial")
    {
        {
            boost::filesystem::path cpp_output = output;
            cpp_output /= document->name()->value() + "-partial" + pImplementer->applicationExtension();

            boost::shared_ptr<std::ostream> pOutput = openStream(cpp_output);

            compil::CppGenerator generator;
            bool bResult = generator.init("partial",
                                          pConfigurationManager->getConfiguration<AlignerConfiguration>(),
                                          pFormatter,
                                          pImplementer,
                                          pOutput,
                                          document);
            if (bResult) generator.generate();

            closeStream(pOutput);

            if (!bResult)
                return 1;

            std::vector<compil::Dependency> dependencies = generator.getCoreDependencies();
            coreDependencies.insert(coreDependencies.end(), dependencies.begin(), dependencies.end());
        }
        {
            boost::filesystem::path cpp_h_output = output;
            cpp_h_output /= document->name()->value() + "-partial" + pImplementer->applicationHeaderExtension();

            boost::shared_ptr<std::ostream> pOutput = openStream(cpp_h_output);

            compil::CppHeaderGenerator generator;
            bool bResult = generator.init("partial",
                                          pConfigurationManager->getConfiguration<AlignerConfiguration>(),
                                          pFormatter,
                                          pImplementer,
                                          pOutput,
                                          document);
            if (bResult) generator.generate();

            closeStream(pOutput);

            if (!bResult)
                return 1;

            std::vector<compil::Dependency> dependencies = generator.getCoreDependencies();
            coreDependencies.insert(coreDependencies.end(), dependencies.begin(), dependencies.end());
        }
    }
    else
    if (pGeneratorConfiguration->type == "test")
    {
        {
            boost::filesystem::path cpp_output = output;
            cpp_output /= document->name()->value() + "-test" + pImplementer->applicationExtension();

            boost::shared_ptr<std::ostream> pOutput = openStream(cpp_output);

            compil::CppTestGenerator generator;
            bool bResult = generator.init("test",
                                          pConfigurationManager->getConfiguration<AlignerConfiguration>(),
                                          pFormatter,
                                          pImplementer,
                                          pOutput,
                                          document);
            if (bResult) generator.generate();

            closeStream(pOutput);

            if (!bResult)
                return 1;

            std::vector<compil::Dependency> dependencies = generator.getCoreDependencies();
            coreDependencies.insert(coreDependencies.end(), dependencies.begin(), dependencies.end());
        }
    }
    else
    {
        std::cout << "unknown type!!!\n";
        return 1;
    }

    std::vector<compil::Dependency>::iterator it;
    for (it = coreDependencies.begin(); it != coreDependencies.end(); ++it)
    {
        if (it->mHeader != "flags_enumeration.hpp") continue;

        boost::filesystem::path cpp_flags_enumerator_output = core;
        cpp_flags_enumerator_output /= "flags_enumeration.hpp";

        boost::shared_ptr<std::ostream> pOutput = openStream(cpp_flags_enumerator_output);

        compil::CppFlagsEnumerationGenerator generator;
        bool bResult = generator.init("partial",
                                      pConfigurationManager->getConfiguration<AlignerConfiguration>(),
                                      pFormatter,
                                      pImplementer,
                                      pOutput,
                                      document);
        if (bResult) generator.generate();

        closeStream(pOutput);

        if (!bResult)
            return 1;

        break;
    }





    return 0;
}

