#include "language/compil/document/operator.h"

namespace lang
{

namespace compil
{

Operator::Operator()
{
}

Operator::~Operator()
{
}

OperatorSPtr Operator::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Operator>(object);
}

const EOperatorAction& Operator::action() const
{
    return mAction;
}

Operator& Operator::set_action(const EOperatorAction& action)
{
    mAction = action;
    return *this;
}

EOperatorAction& Operator::mutable_action()
{
    return mAction;
}

const EOperatorFlags& Operator::flags() const
{
    return mFlags;
}

Operator& Operator::set_flags(const EOperatorFlags& flags)
{
    mFlags = flags;
    return *this;
}

EOperatorFlags& Operator::mutable_flags()
{
    return mFlags;
}

const StructureWPtr& Operator::structure() const
{
    return mStructure;
}

StructureWPtr Operator::default_structure()
{
    static StructureWPtr defaultObject;
    return defaultObject;
}

Operator& Operator::set_structure(const StructureSPtr& structure)
{
    mStructure = structure;
    return *this;
}

const CommentSPtr& Operator::comment() const
{
    return mComment;
}

Operator& Operator::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
    return *this;
}

Operator& Operator::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Operator& Operator::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Operator& Operator::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

