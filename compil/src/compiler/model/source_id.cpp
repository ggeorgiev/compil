#include "source_id.h"
// Standard C Library
#include <stddef.h>

namespace compil
{

SourceId::Builder::Builder()
        : mpObject(new SourceId())
{
}

SourceId::Builder::Builder(const SourceId& object)
        : mpObject(new SourceId())
{
    *(SourceId*)mpObject = object;
}

SourceId::Builder::Builder(SourceIdRPtr pObject)
        : mpObject(pObject)
{
}

SourceId::Builder::~Builder()
{
    delete (SourceIdRPtr)mpObject;
    mpObject = NULL;
}

const SourceId& SourceId::Builder::build() const
{
    return *(SourceIdRPtr)mpObject;
}

SourceIdSPtr SourceId::Builder::finalize()
{
    SourceIdRPtr objectRPtr = (SourceIdRPtr)mpObject;
    mpObject = NULL;
    return SourceIdSPtr(objectRPtr);
}

SourceId::SourceId()
{
}

SourceId::~SourceId()
{
}

const std::string& SourceId::value() const
{
    return mValue;
}

SourceId::Builder& SourceId::Builder::set_value(const std::string& value)
{
    mpObject->mValue = value;
    return *this;
}

std::string& SourceId::Builder::mutable_value()
{
    return mpObject->mValue;
}

const std::vector<PackageElement>& SourceId::externalElements() const
{
    return mExternalElements;
}

SourceId::Builder& SourceId::Builder::set_externalElements(const std::vector<PackageElement>& externalElements)
{
    mpObject->mExternalElements = externalElements;
    return *this;
}

std::vector<PackageElement>& SourceId::Builder::mutable_externalElements()
{
    return mpObject->mExternalElements;
}

const std::string& SourceId::uniquePresentation() const
{
    return mUniquePresentation;
}

SourceId::Builder& SourceId::Builder::set_uniquePresentation(const std::string& uniquePresentation)
{
    mpObject->mUniquePresentation = uniquePresentation;
    return *this;
}

std::string& SourceId::Builder::mutable_uniquePresentation()
{
    return mpObject->mUniquePresentation;
}

const SourceIdSPtr& SourceId::parent() const
{
    return mParent;
}

SourceIdSPtr SourceId::default_parent()
{
    static SourceIdSPtr defaultObject;
    return defaultObject;
}

SourceId::Builder& SourceId::Builder::set_parent(const SourceIdSPtr& parent)
{
    mpObject->mParent = parent;
    return *this;
}

const std::string& SourceId::original() const
{
    return mOriginal;
}

SourceId::Builder& SourceId::Builder::set_original(const std::string& original)
{
    mpObject->mOriginal = original;
    return *this;
}

std::string& SourceId::Builder::mutable_original()
{
    return mpObject->mOriginal;
}

}

