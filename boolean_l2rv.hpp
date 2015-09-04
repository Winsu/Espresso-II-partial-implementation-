#ifndef BOOLEAN_L2RV_HPP
#define BOOLEAN_L2RV_HPP

#include "enum_class_l2rv_t.hpp"
#include <iostream>
#include <array>

class bool_l2rv : private l2rv {
private:
	l2rv_t val;
public:
	inline static const bool_l2rv g_T(){
		bool_l2rv ret;
		ret.val = l2rv::g_T();
		return ret;
	}
	inline static const bool_l2rv g_F(){
		bool_l2rv ret;
		ret.val = l2rv::g_F();
		return ret;
	}
	inline static const bool_l2rv g_e(){
		bool_l2rv ret;
		ret.val = l2rv::g_e();
		return ret;
	}

	inline operator int() const;
	inline operator unsigned int() const;
	inline operator char() const;
	inline operator unsigned char() const;
	inline bool_l2rv operator ! () const;
	inline bool_l2rv operator ^ (bool_l2rv a) const;
	inline bool_l2rv operator || (bool_l2rv a) const;
	inline bool_l2rv operator && (bool_l2rv a) const;
	inline bool_l2rv operator - (bool_l2rv a) const;
	inline bool operator == (bool_l2rv a) const;
	inline bool operator != (bool_l2rv a) const;
	inline bool operator < (bool_l2rv a) const;
	inline bool operator <= (bool_l2rv a) const;
	inline bool operator > (bool_l2rv a) const;
	inline bool operator >= (bool_l2rv a) const;
	inline bool_l2rv();
	inline bool_l2rv(const bool_l2rv & a);
	inline bool_l2rv(const bool & a);
	inline bool_l2rv(char a);
	inline bool_l2rv(int a);
	inline operator bool() const;
	inline bool is_empty() const;
	inline const bool_l2rv & operator=(const bool_l2rv & a);
	inline const bool_l2rv & operator=(const bool & a);
	inline const bool_l2rv & operator=(char a);
	inline const bool_l2rv & operator=(int a);
	inline const bool_l2rv & operator~();
	inline const bool_l2rv & operator&=(bool_l2rv a);
	inline const bool_l2rv & operator|=(bool_l2rv a);
	inline const bool_l2rv & operator^=(bool_l2rv a);
	inline const bool_l2rv & operator-=(bool_l2rv a);
};

inline bool_l2rv::operator bool() const {
	return l2rv::boolean(this->val);
}

inline bool bool_l2rv::is_empty() const {
	return ((l2rv_t::e)==(this->val));
}

inline
bool_l2rv::operator int() const {
	switch (val) {
		case l2rv_t::T	: return (1);
		case l2rv_t::F	: return (0);
		case l2rv_t::e	: 
		default			: return (-1);
	}
}

inline
bool_l2rv::operator unsigned int() const {
	switch (val) {
		case l2rv_t::T	: return (1);
		case l2rv_t::F	: return (0);
		case l2rv_t::e	: 
		default			: return (3);
	}
}

inline
bool_l2rv::operator char() const {
	switch (val) {
		case l2rv_t::F	:	return '0';
		case l2rv_t::T	:	return '1';
		case l2rv_t::e	:
		default			:	return '-';
	}
}

inline
bool_l2rv::operator unsigned char() const {
	switch (val) {
		case l2rv_t::T	:	return (static_cast<unsigned char>(1));
		case l2rv_t::F	:	return (static_cast<unsigned char>(0));
		case l2rv_t::e	:
		default			:	return (static_cast<unsigned char>(3));
	}
}

inline
bool_l2rv bool_l2rv::operator ^ (bool_l2rv a) const {
	bool_l2rv ret;
	ret.val = l2rv::o_exclusiva_logica(val,a.val);
	return ret;
}

inline
bool_l2rv bool_l2rv::operator || (bool_l2rv a) const {
	bool_l2rv ret;
	ret.val = l2rv::disyuncion_logica(val,a.val);
	return ret;
}

inline
bool_l2rv bool_l2rv::operator && (bool_l2rv a) const {
	bool_l2rv ret;
	ret.val = l2rv::conjuncion_logica(val,a.val);
	return ret;
}

inline
bool_l2rv bool_l2rv::operator ! () const {
	bool_l2rv ret;
	ret.val = l2rv::negacion_logica(val);
	return ret;
}

inline
bool_l2rv bool_l2rv::operator - (bool_l2rv a) const {
	bool_l2rv ret;
	ret.val = l2rv::resta_logica(val,a.val);
	return ret;
}

inline
const bool_l2rv & bool_l2rv::operator ~ () {
	val = l2rv::negacion_logica(val);
	return (*this);
}

inline
bool bool_l2rv::operator == (bool_l2rv a) const {
	return (val == a.val);
}

inline
bool bool_l2rv::operator != (bool_l2rv a) const {
	return (val != a.val);
}

inline
bool bool_l2rv::operator < (bool_l2rv a) const {
	return (l2rv::lt(val,a.val));
}

inline
bool bool_l2rv::operator <= (bool_l2rv a) const {
	return (l2rv::lt_eq(val,a.val));
}

inline
bool bool_l2rv::operator > (bool_l2rv a) const {
	return (l2rv::gt(val,a.val));
}

inline
bool bool_l2rv::operator >= (bool_l2rv a) const {
	return (l2rv::gt_eq(val,a.val));
}

inline bool_l2rv::bool_l2rv():val(l2rv_t::e){}
inline bool_l2rv::bool_l2rv(const bool_l2rv & a):val(a.val){}
inline bool_l2rv::bool_l2rv(const bool & a):val((a)?(l2rv_t::T):(l2rv_t::F)){}
inline bool_l2rv::bool_l2rv(char a){
	switch (a) {
		case 'F':
		case 'f':
		case '0':
		case 'L':
		case 'l': val = l2rv_t::F; break;
		case 'T':
		case 't':
		case '1':
		case 'H':
		case 'h': val = l2rv_t::T; break;
		case 'E':
		case 'e':
		case '3': 
		default : val = l2rv_t::e;
	}
	return;
}

inline bool_l2rv::bool_l2rv(int a) {
	switch (a) {
		case 0 : val = l2rv_t::F; break;
		case 1 : val = l2rv_t::T; break;
		case -1:
		case 3 :
		default: val = l2rv_t::e;
	}
}

inline
const bool_l2rv & bool_l2rv::operator=(const bool_l2rv & a){
	val=a.val;
	return (*this);
}

inline
const bool_l2rv & bool_l2rv::operator=(const bool & a){
	if (a) this->val=(l2rv_t::T);
	else this->val=(l2rv_t::F);
	return (*this);
}

inline
const bool_l2rv & bool_l2rv::operator=(char a){
	switch (a) {
		case 'F' : 
		case 'f' :
		case '0' :
		case 'L' :
		case 'l' : val = l2rv_t::F; return(*this);
		case 'T' : 
		case 't' :
		case '1' :
		case 'H' :
		case 'h' : val = l2rv_t::T; return (*this);
		case 'E' : 
		case 'e' :
		case '3' : 
		default  : val = l2rv_t::e; return (*this);
	} 
}

inline
const bool_l2rv & bool_l2rv::operator=(int a){
	switch (a) {
		case 0 : val = l2rv_t::F; return (*this);
		case 1 : val = l2rv_t::T; return (*this);
		case -1:
		case 3 :
		default: val = l2rv_t::e; return (*this);
	}
}

inline
const bool_l2rv & bool_l2rv::operator&=(bool_l2rv a) {
	val = l2rv::conjuncion_logica((l2rv_t)val,(l2rv_t)a.val);
	return (*this);
}

inline
const bool_l2rv & bool_l2rv::operator|=(bool_l2rv a) {
	val = l2rv::disyuncion_logica((l2rv_t)val,(l2rv_t)a.val);
	return (*this);
}

inline
const bool_l2rv & bool_l2rv::operator^=(bool_l2rv a)  {
	val = l2rv::o_exclusiva_logica((l2rv_t)val,(l2rv_t)a.val);
	return (*this);
}

inline
const bool_l2rv & bool_l2rv::operator-=(bool_l2rv a)  {
	val = l2rv::resta_logica((l2rv_t)val,(l2rv_t)a.val);
	return (*this);
}

const bool_l2rv F2rv		=	bool_l2rv::g_F();
const bool_l2rv f2rv		=	F2rv;
const bool_l2rv T2rv		=	bool_l2rv::g_T();
const bool_l2rv t2rv		=	T2rv;
const bool_l2rv e2rv		=	bool_l2rv::g_e();
const bool_l2rv E3rv		=	e2rv;

std::ostream & operator << (std::ostream & out,const bool_l2rv & arg) {
	out << char(arg);
	return out;
}

std::istream & operator >> (std::istream & in,bool_l2rv & arg) {
	char entrada;
	in >> entrada;
	arg = bool_l2rv(entrada);
	return in;
}

template<const std::size_t NS>
using B2rTerm_t = std::array<bool_l2rv,NS>;
template<const std::size_t NS>
using IB2rTerm_t = typename B2rTerm_t<NS>::iterator;
template<const std::size_t NS>
using c_IB2rTerm_t = typename B2rTerm_t<NS>::const_iterator;

#endif // BOOLEAN_L2RV_HPP
