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
// Standard Template Library
#include <string>
#include <vector>

#ifndef __GENERATOR_SELF_GENERATOR_CPP_FORMAT_COMMENT_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_CPP_FORMAT_COMMENT_COMPIL_H_

#include "comment.h"

namespace cpp
{

namespace frm
{

class Comment
{
public:
    // Default constructor
                                            Comment           ();
    // Destructor
    /*lax*/                                 ~Comment          ();

    // Getter method for the data field paragraphs
            const std::vector<std::string>& paragraphs        ()                                           const;
    // Setter method for the data field paragraphs
            Comment&                        set_paragraphs    (const std::vector<std::string>& paragraphs);
    // Provides mutable access to field paragraphs
            std::vector<std::string>&       mutable_paragraphs();
    // Store operator for the data field paragraphs
            Comment&                        operator<<        (const std::vector<std::string>& paragraphs);
    // Store operator for an item of data field paragraphs
            Comment&                        operator<<        (const std::string& paragraphsItem);

private:
    // variable for the data field paragraphs
    std::vector<std::string> mParagraphs;
};

// Reference store operator for the data field paragraphs
const CommentSPtr& operator<<(const CommentSPtr& , const std::vector<std::string>& );
// Reference store operator for an item of data field paragraphs
const CommentSPtr& operator<<(const CommentSPtr& , const std::string& );

inline CommentSPtr commentRef()
{
    return boost::make_shared<Comment>();
}

}

}

#else // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_COMMENT_COMPIL_H_

namespace cpp
{

namespace frm
{

// Forward declarations
class Comment;
typedef Comment*                         CommentRPtr;
typedef boost::shared_ptr<Comment>       CommentSPtr;
typedef boost::shared_ptr<const Comment> CommentSCPtr;
typedef boost::weak_ptr<Comment>         CommentWPtr;

}

}

#endif // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_COMMENT_COMPIL_H_

