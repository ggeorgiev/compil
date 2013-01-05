// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/compil/project/project.h"

namespace lang
{

namespace compil
{

Project::Project()
{
}

Project::~Project()
{
}

ProjectSPtr Project::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Project>(object);
}

const FileSPtr& Project::mainFile() const
{
    return mMainFile;
}

Project& Project::set_mainFile(const FileSPtr& mainFile)
{
    mMainFile = mainFile;
    return *this;
}

Project& Project::operator<<(const FileSPtr& mainFile)
{
    return set_mainFile(mainFile);
}

const ProjectSPtr& operator<<(const ProjectSPtr& object, const FileSPtr& mainFile)
{
    BOOST_ASSERT(object);
    *object << mainFile;
    return object;
}

const PackageSPtr& Project::corePackage() const
{
    return mCorePackage;
}

Project& Project::set_corePackage(const PackageSPtr& corePackage)
{
    mCorePackage = corePackage;
    return *this;
}

Project& Project::operator<<(const PackageSPtr& corePackage)
{
    return set_corePackage(corePackage);
}

const ProjectSPtr& operator<<(const ProjectSPtr& object, const PackageSPtr& corePackage)
{
    BOOST_ASSERT(object);
    *object << corePackage;
    return object;
}

const std::vector<SectionSPtr>& Project::sections() const
{
    return mSections;
}

Project& Project::set_sections(const std::vector<SectionSPtr>& sections)
{
    mSections = sections;
    return *this;
}

std::vector<SectionSPtr>& Project::mutable_sections()
{
    return mSections;
}

Project& Project::operator<<(const std::vector<SectionSPtr>& sections)
{
    return set_sections(sections);
}

const ProjectSPtr& operator<<(const ProjectSPtr& object, const std::vector<SectionSPtr>& sections)
{
    BOOST_ASSERT(object);
    *object << sections;
    return object;
}

Project& Project::operator<<(const SectionSPtr& sectionsItem)
{
    mSections.push_back(sectionsItem);
    return *this;
}

const ProjectSPtr& operator<<(const ProjectSPtr& object, const SectionSPtr& sectionsItem)
{
    BOOST_ASSERT(object);
    *object << sectionsItem;
    return object;
}

Project& Project::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Project& Project::operator<<(const SourceIdSPtr& sourceId)
{
    *(Object*)this << sourceId;
    return *this;
}

const ProjectSPtr& operator<<(const ProjectSPtr& object, const SourceIdSPtr& sourceId)
{
    BOOST_ASSERT(object);
    *object << sourceId;
    return object;
}

Project& Project::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Project& Project::operator<<(const Line& line)
{
    *(Object*)this << line;
    return *this;
}

const ProjectSPtr& operator<<(const ProjectSPtr& object, const Line& line)
{
    BOOST_ASSERT(object);
    *object << line;
    return object;
}

Project& Project::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

Project& Project::operator<<(const Column& column)
{
    *(Object*)this << column;
    return *this;
}

const ProjectSPtr& operator<<(const ProjectSPtr& object, const Column& column)
{
    BOOST_ASSERT(object);
    *object << column;
    return object;
}

}

}

