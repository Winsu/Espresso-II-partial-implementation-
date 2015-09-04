#ifndef TYPEDEFS_2_HPP
#define TYPEDEFS_2_HPP

#include <array>
#include "boolean_l2rv.hpp"
#include "boolean_l3v.hpp"
#include "boolean_l4v.hpp"

template<const std::size_t NS>
using B4Term_t = std::array<bool_l4v,NS>;
template<const std::size_t NS>
using IB4Term_t = typename B4Term_t<NS>::iterator;
template<const std::size_t NS>
using c_IB4Term_t = typename B4Term_t<NS>::const_iterator;

template<const std::size_t NS>
using B2rTerm_t = std::array<bool_l2rv,NS>;
template<const std::size_t NS>
using IB2rTerm_t = typename B2rTerm_t<NS>::iterator;
template<const std::size_t NS>
using c_IB2rTerm_t = typename B2rTerm_t<NS>::const_iterator;

template<const size_t NE>
using B2Term_t = std::array<bool,NE>;
template<const size_t NE>
using IB2Term_t = typename B2Term_t<NE>::iterator;
template<const size_t NE>
using c_IB2Term_t = typename B2Term_t<NE>::const_iterator;

template<const std::size_t NE , const std::size_t NS> class CBinVec;
template<const std::size_t NE , const std::size_t NS> class CBooleanCube;

#endif //TYPEDEFS_2_HPP
