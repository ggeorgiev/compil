// CompIL - Component Interface Language
// Copyright 2011 George Georgiev.  All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// 
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// * The name of George Georgiev can not be used to endorse or
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

// Boost C++ Smart Pointers
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#ifndef __COMPIL_ALL_OBJECT_SCOMPIL_H_
#define __COMPIL_ALL_OBJECT_SCOMPIL_H_

#include "language/compil/all/object.h"
#include "language/compil/all/source_id.h"
// Boost C++ Smart Pointers
#include <boost/enable_shared_from_this.hpp>

namespace lang
{

namespace compil
{

class Line
{
public:
                  Line      ();
    explicit      Line      (long value);

    inline   long value     ()                   const;
    inline   bool operator==(const Line& rValue) const;
    inline   bool operator!=(const Line& rValue) const;
    inline   bool operator< (const Line& rValue) const;
    inline   Line operator+ (const Line& rValue) const;
    inline   Line operator- (const Line& rValue) const;
private:
    long mValue;
};

class Column
{
public:
                    Column    ();
    explicit        Column    (long value);

    inline   long   value     ()                     const;
    inline   bool   operator==(const Column& rValue) const;
    inline   bool   operator!=(const Column& rValue) const;
    inline   bool   operator< (const Column& rValue) const;
    inline   Column operator+ (const Column& rValue) const;
    inline   Column operator- (const Column& rValue) const;
private:
    long mValue;
};

class Object : public boost::enable_shared_from_this<Object>
{
public:
    // Default constructor
                                Object         ();
    // Destructor
    virtual                     ~Object        ();

    // Identifier for the objects from Object class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId           staticObjectId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId           runtimeObjectId()                             const;

    // Getter method for the data field sourceId
            const SourceIdSPtr& sourceId       ()                             const;
    // Setter method for the data field sourceId
            Object&             set_sourceId   (const SourceIdSPtr& sourceId);
    // Store operator for the data field sourceId
            Object&             operator<<     (const SourceIdSPtr& sourceId);

    // Getter method for the data field line
            const Line&         line           ()                             const;
    // Setter method for the data field line
            Object&             set_line       (const Line& line);
    // Provides mutable access to field line
            Line&               mutable_line   ();
    // Store operator for the data field line
            Object&             operator<<     (const Line& line);

    // Getter method for the data field column
            const Column&       column         ()                             const;
    // Setter method for the data field column
            Object&             set_column     (const Column& column);
    // Provides mutable access to field column
            Column&             mutable_column ();
    // Store operator for the data field column
            Object&             operator<<     (const Column& column);

private:
    // variable for the data field sourceId
    SourceIdSPtr mSourceId;
    // variable for the data field line
    Line         mLine;
    // variable for the data field column
    Column       mColumn;
};

// Reference store operator for the data field sourceId
const ObjectSPtr& operator<<(const ObjectSPtr& , const SourceIdSPtr& );
// Reference store operator for the data field line
const ObjectSPtr& operator<<(const ObjectSPtr& , const Line& );
// Reference store operator for the data field column
const ObjectSPtr& operator<<(const ObjectSPtr& , const Column& );

inline LineSPtr lineRef()
{
    return boost::make_shared<Line>();
}

inline LineSPtr lineRef(long value)
{
    return boost::make_shared<Line>(value);
}

inline long Line::value() const
{
    return mValue;
}

inline bool Line::operator==(const Line& rValue) const
{
    return value() == rValue.value();
}

inline bool Line::operator!=(const Line& rValue) const
{
    return value() != rValue.value();
}

inline bool Line::operator<(const Line& rValue) const
{
    return value() < rValue.value();
}

inline Line Line::operator+(const Line& rValue) const
{
    return Line(value() + rValue.value());
}

inline Line Line::operator-(const Line& rValue) const
{
    return Line(value() - rValue.value());
}

inline ColumnSPtr columnRef()
{
    return boost::make_shared<Column>();
}

inline ColumnSPtr columnRef(long value)
{
    return boost::make_shared<Column>(value);
}

inline long Column::value() const
{
    return mValue;
}

inline bool Column::operator==(const Column& rValue) const
{
    return value() == rValue.value();
}

inline bool Column::operator!=(const Column& rValue) const
{
    return value() != rValue.value();
}

inline bool Column::operator<(const Column& rValue) const
{
    return value() < rValue.value();
}

inline Column Column::operator+(const Column& rValue) const
{
    return Column(value() + rValue.value());
}

inline Column Column::operator-(const Column& rValue) const
{
    return Column(value() - rValue.value());
}

inline ObjectSPtr objectRef()
{
    return boost::make_shared<Object>();
}

}

}

#else // __COMPIL_ALL_OBJECT_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class Line;
typedef Line*                         LineRPtr;
typedef boost::shared_ptr<Line>       LineSPtr;
typedef boost::shared_ptr<const Line> LineSCPtr;
typedef boost::weak_ptr<Line>         LineWPtr;

class Column;
typedef Column*                         ColumnRPtr;
typedef boost::shared_ptr<Column>       ColumnSPtr;
typedef boost::shared_ptr<const Column> ColumnSCPtr;
typedef boost::weak_ptr<Column>         ColumnWPtr;

class Object;
typedef Object*                         ObjectRPtr;
typedef boost::shared_ptr<Object>       ObjectSPtr;
typedef boost::shared_ptr<const Object> ObjectSCPtr;
typedef boost::weak_ptr<Object>         ObjectWPtr;

class EObjectId;

}

}

#endif // __COMPIL_ALL_OBJECT_SCOMPIL_H_

