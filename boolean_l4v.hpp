#ifndef L4V_T_HPP
#define L4V_T_HPP

#include "typedefs.hpp"
#include "enum_class_l4v_t.hpp"

class bool_l4v : private l4v {
private:
	l4v::l4v_t val;
public:
	inline static const bool_l4v g_T(){
		bool_l4v	ret;
		ret.val = l4v::g_T();
		return ret;
	}
	inline static const bool_l4v g_F(){
		bool_l4v	ret;
		ret.val = l4v::g_F();
		return ret;

	}
	inline static const bool_l4v g_x(){
		bool_l4v	ret;
		ret.val = l4v::g_x();
		return ret;

	}
	inline static const bool_l4v g_e(){
		bool_l4v	ret;
		ret.val = l4v::g_e();
		return ret;
	}

	inline operator int() const;
	inline operator unsigned int() const;
	inline operator char() const;
	inline operator unsigned char() const;
	inline bool_l4v operator ! () const;
	inline bool_l4v operator ^ (bool_l4v a) const;
	inline bool_l4v operator || (bool_l4v a) const;
	inline bool_l4v operator && (bool_l4v a) const;
	inline bool_l4v operator - (bool_l4v a) const;
	inline bool operator == (bool_l4v a) const;
	inline bool operator != (bool_l4v a) const;
	inline bool operator < (bool_l4v a) const;
	inline bool operator <= (bool_l4v a) const;
	inline bool operator > (bool_l4v a) const;
	inline bool operator >= (bool_l4v a) const;
	inline bool_l4v();
	inline bool_l4v(const bool_l4v & a);
	inline bool_l4v(char a);
	inline bool_l4v(int a);
	inline const bool_l4v & operator=(const bool_l4v & a);
	inline const bool_l4v & operator=(char a);
	inline const bool_l4v & operator=(int a);
	inline const bool_l4v & operator~();
	inline const bool_l4v & operator&=(bool_l4v a);
	inline const bool_l4v & operator|=(bool_l4v a);
	inline const bool_l4v & operator^=(bool_l4v a);
	inline const bool_l4v & operator-=(bool_l4v a);
};

inline
bool_l4v::operator int() const {
	switch (val) {
		case l4v_t::x	: return (2);
		case l4v_t::T	: return (1);
		case l4v_t::F	: return (0);
		case l4v_t::e	:
		default			: return (-1);
	}
}

inline
bool_l4v::operator unsigned int() const {
	switch (val) {
		case l4v_t::x	: return (2);
		case l4v_t::T	: return (1);
		case l4v_t::F	: return (0);
		case l4v_t::e	:
		default			: return (3);
	}
}

inline
bool_l4v::operator char() const {
	switch (val) {
		case l4v_t::F	:	return '0';
		case l4v_t::T	:	return '1';
		case l4v_t::x	:	return '2';
		case l4v_t::e	:
		default			:	return '-';
	}
}

inline
bool_l4v::operator unsigned char() const {
	switch (val) {
		case l4v_t::x	:	return (static_cast<unsigned char>(2));
		case l4v_t::T	:	return (static_cast<unsigned char>(1));
		case l4v_t::F	:	return (static_cast<unsigned char>(0));
		case l4v_t::e	:
		default			:	return (static_cast<unsigned char>(3));
	}
}

inline
bool_l4v bool_l4v::operator ^ (bool_l4v a) const {
	bool_l4v ret;					
	ret.val = l4v::o_exclusiva_logica(val,a.val);
	return ret;
}

inline
bool_l4v bool_l4v::operator || (bool_l4v a) const {
	bool_l4v ret;
	ret.val = l4v::disyuncion_logica(val,a.val);
	return ret;

}

inline
bool_l4v bool_l4v::operator && (bool_l4v a) const {
	bool_l4v ret;
	ret.val = l4v::conjuncion_logica(val,a.val);
	return ret;
}

inline
bool_l4v bool_l4v::operator ! () const {
	bool_l4v ret;
	ret.val = l4v::negacion_logica(val);
	return ret;
}

inline
bool_l4v	bool_l4v::operator - (bool_l4v a) const {
	bool_l4v ret;
	ret.val = l4v::resta_logica(val,a.val);
	return ret;
}

inline
const bool_l4v & bool_l4v::operator ~ () {
	val = l4v::negacion_logica(val);
	return (*this);
}

inline
bool bool_l4v::operator == (bool_l4v a) const {
	return (val == a.val);
}

inline
bool bool_l4v::operator != (bool_l4v a) const {
	return (val != a.val);
}

inline
bool bool_l4v::operator < (bool_l4v a) const {
	return (l4v::lt(val,a.val));
}

inline
bool bool_l4v::operator <= (bool_l4v a) const {
	return (l4v::lt_eq(val,a.val));
}

inline
bool bool_l4v::operator > (bool_l4v a) const {
	return (l4v::gt(val,a.val));
}

inline
bool bool_l4v::operator >= (bool_l4v a) const {
	return (l4v::gt_eq(val,a.val));
}


inline bool_l4v::bool_l4v():val(l4v_t::e){}
inline bool_l4v::bool_l4v(const bool_l4v & a):val(a.val){}
inline bool_l4v::bool_l4v(char a){ 
	switch (a) {
		case 'F':
		case 'f':
		case '0':
		case 'L':
		case 'l': val = l4v_t::F; break;
		case 'T':
		case 't':
		case '1':
		case 'H':
		case 'h': val = l4v_t::T; break;
		case 'X':
		case 'x':
		case '2':
		case 'U':
		case 'u': val = l4v_t::x; break;
		case 'E':
		case 'e':
		case '3':
		default : val = l4v_t::e;
	}
	return;
}


inline bool_l4v::bool_l4v(int a)  {
    switch (a) {
            case 0 : val = l4v::l4v_t::F; break;
            case 1 : val = l4v::l4v_t::T; break;
            case 2 : val = l4v::l4v_t::x; break;
            case -1:
            case 3 :
            default: val = l4v::l4v_t::e;
        }
}

inline
const bool_l4v & bool_l4v::operator=(const bool_l4v & a){
	val=a.val;
	return (*this);
}

inline
const bool_l4v & bool_l4v::operator=(char a){
	switch (a) {
		case 'F' :
		case 'f' :
		case '0' :
		case 'L' :
		case 'l' : val = l4v_t::F; return(*this);
		case 'T' :
		case 't' :
		case '1' :
		case 'H' :
		case 'h' : val = l4v_t::T; return (*this);
		case 'X' :
		case 'x' :
		case '-' :
		case '2' : val = l4v_t::x; return (*this);
		case 'E' :
		case 'e' :
		case '3' :
		default  : val = l4v_t::e; return (*this);
	}
}

inline
const bool_l4v & bool_l4v::operator=(int a){
	switch (a) {
		case 0 : val = l4v_t::F; return (*this);
		case 1 : val = l4v_t::T; return (*this);
		case 2 : val = l4v_t::x; return (*this);
		case -1:
		case 3 :
		default: val = l4v_t::e; return (*this);
	}
}

inline
const bool_l4v & bool_l4v::operator&=(bool_l4v a) {
	val = l4v::conjuncion_logica((l4v_t)val,(l4v_t)a.val);
	return (*this);
}

inline
const bool_l4v & bool_l4v::operator|=(bool_l4v a) {
	val = l4v::disyuncion_logica((l4v_t)val,(l4v_t)a.val);
	return (*this);
}

inline
const bool_l4v & bool_l4v::operator^=(bool_l4v a)  {
	val = l4v::o_exclusiva_logica((l4v_t)val,(l4v_t)a.val);
	return (*this);
}

inline
const bool_l4v & bool_l4v::operator-=(bool_l4v a)  {
	val = l4v::resta_logica((l4v_t)val,(l4v_t)a.val);
	return (*this);
}

const bool_l4v F4v		=	bool_l4v::g_F();
const bool_l4v f4v		=	F4v;
const bool_l4v T4v		=	bool_l4v::g_T();
const bool_l4v t4v		=	T4v;
const bool_l4v DC4v		=	bool_l4v::g_x();
const bool_l4v x4v		=	DC4v;
const bool_l4v X4v		=	DC4v;
const bool_l4v dc4v		=	DC4v;
const bool_l4v Dc4v		=	DC4v;
const bool_l4v dC4v		=	DC4v;
const bool_l4v e4v		=	bool_l4v::g_e();
const bool_l4v E4v		=	e4v;

std::ostream & operator << (std::ostream & out,const bool_l4v & arg) {
	out << char(arg);
	return out;
}

std::istream & operator >> (std::istream & in,bool_l4v & arg) {
	char entrada;
	in >> entrada;
	arg = bool_l4v(entrada);
	return in;
}

template<const std::size_t NS>
using B4Term_t = std::array<bool_l4v,NS>;
template<const std::size_t NS>
using IB4Term_t = typename B4Term_t<NS>::iterator;
template<const std::size_t NS>
using c_IB4Term_t = typename B4Term_t<NS>::const_iterator;

#endif // L4V_T_HPP
