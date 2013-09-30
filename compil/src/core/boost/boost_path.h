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

#include <boost/filesystem.hpp>

namespace boost {

namespace filesystem {

// path resolve method eliminates . and .. where it is possible
// the normalized method boost offers is dangerous because of
// simlinks ... but not resolving the path could be equally harmful.
// For the path: /foo/../bar could be reported as not existing
// on most of the operating system even if /bar exists but /foo
// doesn't. Sounds like very corner case, but it is not so unusual
// in the world of build systems

// NOTE: in context of multi-platform serialization keep the path
// as match as possible close to the original. Use resolve just before
// to access the file/directory from the file system.

path resolve(const path& p);
path relative_path(const path& directory, const path& to);

bool is_identical(const boost::filesystem::path file1, const boost::filesystem::path& file2);

// copies the source over the target only if the target id different
void optional_copy(const boost::filesystem::path source, const boost::filesystem::path& target);

}

}
