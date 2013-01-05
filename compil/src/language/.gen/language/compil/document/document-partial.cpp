#include "language/compil/document/document.h"

namespace lang
{

namespace compil
{

DocumentPartial::DocumentPartial()
{
}

DocumentPartial::~DocumentPartial()
{
}

DocumentSPtr DocumentPartial::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Document>(object);
}

const FileSPtr& DocumentPartial::mainFile() const
{
    return mMainFile;
}

Document& DocumentPartial::set_mainFile(const FileSPtr& mainFile)
{
    mMainFile = mainFile;
    return *(Document*)this;
}

const PackageSPtr& DocumentPartial::package() const
{
    return mPackage;
}

Document& DocumentPartial::set_package(const PackageSPtr& package)
{
    mPackage = package;
    return *(Document*)this;
}

const NameSPtr& DocumentPartial::name() const
{
    return mName;
}

Document& DocumentPartial::set_name(const NameSPtr& name)
{
    mName = name;
    return *(Document*)this;
}

Document& DocumentPartial::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *(Document*)this;
}

Document& DocumentPartial::set_line(const Line& line)
{
    Object::set_line(line);
    return *(Document*)this;
}

Document& DocumentPartial::set_column(const Column& column)
{
    Object::set_column(column);
    return *(Document*)this;
}

}

}

