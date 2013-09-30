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
// based on code from Adam Bowen posted on stackoverflow.com

#include "core/boost/boost_path.h"

#include "boost/iostreams/device/mapped_file.hpp"

namespace boost {

namespace filesystem {

path resolve(const path& p)
{
    path result;

    path abs = absolute(p);

    path::iterator it = abs.begin();
#ifdef _WIN32
    result = *it;
    result += "\\";
    ++it;
    ++it;
#endif

    for (; it != abs.end(); ++it)
    {
        if (*it == ".")
            continue;

        if (*it == "..")
        // /a/b/.. is not necessarily /a if b is a symbolic link
        if (!is_symlink(result))
        // /a/b/../.. is not /a/b/.. under most circumstances
        // We can end up with ..s in our result because of symbolic links
        if (result.filename() != "..")
        {
            result = result.parent_path();
            continue;
        }

        result /= *it;
    }
    return result;
}

path relative_path(const path& directory, const path& to)
{
    path::iterator itFrom = directory.begin();
    path::iterator itTo = to.begin();

    // If directory do not have same root, just return "to path"!!!
    if (*itFrom != *itTo)
    {
        assert(*itFrom == *itTo);
        return to;
    }

    while ((itFrom != directory.end()) && (itTo != to.end()) && (*itFrom == *itTo))
    {
        ++itFrom;
        ++itTo;
    }

    path relPath;
    for (;itFrom != directory.end(); ++itFrom)
        relPath /= "..";

    for (;itTo != to.end(); ++itTo)
        relPath /= *itTo;

    return relPath;
}

bool is_identical(const boost::filesystem::path file1, const boost::filesystem::path& file2)
{
    if (!exists(file1))
        return false;

    if (!exists(file2))
        return false;

    boost::iostreams::mapped_file_source source_map(file1);
    boost::iostreams::mapped_file_source target_map(file2);

    if (source_map.size() != target_map.size())
        return false;

    if (!std::equal(source_map.data(), source_map.data() + source_map.size(), target_map.data()))
        return false;

    return true;
}

void optional_copy(const boost::filesystem::path source, const boost::filesystem::path& target)
{
    if (source == target)
        return;

    if (!exists(source))
        return;

    if (is_identical(source, target))
        return;

    copy_file(source, target, copy_option::overwrite_if_exists);
}

}

}