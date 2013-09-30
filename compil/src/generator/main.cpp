#include "generator/project/generator_project.h"
#include "generator/project/file_source_provider.h"
#include "generator/general_configuration.h"
#include "generator/generator_configuration.h"
#include "generator/c++/configuration/formatter_configuration.h"
#include "generator/c++/configuration/aligner_configuration.h"

#include "compiler/parser.h"
#include "compiler/validator/partial_validator.h"

#include "library/compil/document.h"

#include "core/boost/boost_path.h"
#include "core/configuration/configuration_manager.h"

#include "boost/make_shared.hpp"
#include "boost/algorithm/string.hpp"

#include <iostream>
#include <fstream>

#include <stdio.h>

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

    if (!pConfigurationManager->parse(argc, argv, pGeneralConfiguration->configuration_file))
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

    compil::GeneratorProject project(pFileSourceProvider);
    if (!project.init(pGeneratorConfiguration->forceGeneration,
                      pGeneratorConfiguration->ignoreTheGenerator,
                      pGeneratorConfiguration->projectFile,
                      pGeneratorConfiguration->projectDirectory,
                      pGeneratorConfiguration->type,
                      pGeneratorConfiguration->sourceFiles,
                      pGeneratorConfiguration->importDirectories))
        return 1;

    if (!project.parseDocuments())
        return 1;

    if (!project.generate(boost::filesystem::resolve(pGeneratorConfiguration->outputDirectory),
                          pGeneratorConfiguration->flatOutput,
                          boost::filesystem::resolve(pGeneratorConfiguration->coreOutputDirectory),
                          pGeneratorConfiguration->flatCoreOutput,
                          pConfigurationManager->getConfiguration<AlignerConfiguration>(),
                          pConfigurationManager->getConfiguration<FormatterConfiguration>(),
                          pConfigurationManager->getConfiguration<ImplementerConfiguration>()))
        return 1;

    return 0;
}