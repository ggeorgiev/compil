#include <stdio.h>

#include "generator/project/generator_project.h"
#include "generator/project/file_source_provider.h"

#include "compiler/parser.h"
#include "compiler/validator/partial_validator.h"

#include "general_configuration.h"
#include "generator_configuration.h"
#include "aligner_configuration.h"
#include "formatter_configuration.h"


#include "library/compil/document.h"

#include "core/boost/boost_path.h"
#include "core/configuration/configuration_manager.h"

#include "boost/make_shared.hpp"
#include "boost/algorithm/string.hpp"

#include <iostream>
#include <fstream>

int main(int argc, const char **argv)
{
    compil::ConfigurationManagerPtr pConfigurationManager(new compil::ConfigurationManager());

    GeneralConfigurationPtr pGeneralConfiguration(new GeneralConfiguration());
    pConfigurationManager->registerConfiguration(pGeneralConfiguration);

    GeneratorConfigurationPtr pGeneratorConfiguration(new GeneratorConfiguration());
    pConfigurationManager->registerConfiguration(pGeneratorConfiguration);

    AlignerConfigurationSPtr pAlignerConfiguration(new AlignerConfiguration());
    pConfigurationManager->registerConfiguration(pAlignerConfiguration);

    FormatterConfigurationSPtr pFormatterConfiguration(new FormatterConfiguration());
    pConfigurationManager->registerConfiguration(pFormatterConfiguration);

    ImplementerConfigurationSPtr pImplementerConfiguration(new ImplementerConfiguration());
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
        
    if (!project.generate(boost::filesystem::resolve(pGeneratorConfiguration->outputDirectory),
                          boost::filesystem::resolve(pGeneratorConfiguration->coreOutputDirectory),
                          pConfigurationManager->getConfiguration<AlignerConfiguration>(),
                          pConfigurationManager->getConfiguration<FormatterConfiguration>(),
                          pConfigurationManager->getConfiguration<ImplementerConfiguration>()))
        return 1;

    return 0;
}

