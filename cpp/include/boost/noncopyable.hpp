//  Boost noncopyable.hpp header file  --------------------------------------//

//  (C) Copyright Beman Dawes 1999-2003. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/utility for documentation.

#ifndef BOOST_NONCOPYABLE_HPP
#define BOOST_NONCOPYABLE_HPP 1

// protection from unintended ADL
namespace boost { namespace noncopyable_ {

class noncopyable
{
protected:
    noncopyable() = default;
    ~noncopyable() = default;

    noncopyable(const noncopyable&) = delete;
    noncopyable &operator=(const noncopyable&) = delete;

    noncopyable(noncopyable&&) = default;
    noncopyable &operator=(noncopyable&&) = default;
};

} // namespace noncopyable_

using noncopyable = noncopyable_::noncopyable;

} // namespace boost
#endif // BOOST_NONCOPYABLE_HPP
