#ifndef BOOLEAN_L3V_HPP
#define BOOLEAN_L3V_HPP

#include <iostream>
#include "enum_class_l3v_t.hpp"

class bool_l3v : private l3v {
private:

	typedef typename l3v::l3v_t l3v_e;
	l3v_e val;

public:
	inline static const bool_l3v g_T(){
		return bool_l3v(l3v::g_T());
	}
	inline static const bool_l3v g_F(){
		return bool_l3v(l3v::g_F());
	}
	inline static const bool_l3v g_x(){
		return bool_l3v(l3v::g_F());
	}
	inline operator int() const;
	inline operator unsigned int() const;
	inline operator char() const;
	inline operator unsigned char() const;
	inline bool_l3v operator ^ (bool_l3v a) const;
	inline bool_l3v operator || (bool_l3v a) const;
	inline bool_l3v operator && (bool_l3v a) const;
	inline bool_l3v operator ^ (bool a) const;
	inline bool_l3v operator || (bool a) const;
	inline bool_l3v operator && (bool a) const;
	inline bool_l3v operator ! () const;
	inline bool operator == (bool_l3v a) const;
	inline bool operator != (bool_l3v a) const;
	inline bool operator < (bool_l3v a) const;
	inline bool operator <= (bool_l3v a) const;
	inline bool operator > (bool_l3v a) const;
	inline bool operator >= (bool_l3v a) const;
	inline bool operator == (bool a) const;
	inline bool operator != (bool a) const;
	inline bool operator < (bool a) const;
	inline bool operator <= (bool a) const;
	inline bool operator > (bool a) const;
	inline bool operator >= (bool a) const;
	friend	inline bool operator == (bool a,bool_l3v b);
	friend	inline bool operator != (bool a,bool_l3v b);
	friend	inline bool operator < (bool a,bool_l3v b);
	friend	inline bool operator <= (bool a,bool_l3v b);
	friend	inline bool operator > (bool a,bool_l3v b);
	friend	inline bool operator >= (bool a,bool_l3v b);
	inline bool_l3v();
	inline bool_l3v(const bool_l3v & a);
	inline explicit bool_l3v(bool a);
	inline bool_l3v(char a);
	inline bool_l3v(int a);
private:
	inline bool_l3v(l3v_e a);
public:
	inline const bool_l3v & operator=(const bool_l3v & a);
	inline const bool_l3v & operator=(bool a);
	inline const bool_l3v & operator=(char a);
	inline const bool_l3v & operator=(int a);
	inline const bool_l3v & operator&=(bool_l3v a);
	inline const bool_l3v & operator|=(bool_l3v a);
	inline const bool_l3v & operator^=(bool_l3v a);
	inline const bool_l3v & operator&=(bool a);
	inline const bool_l3v & operator|=(bool a);
	inline const bool_l3v & operator^=(bool a);
};

bool_l3v::operator int() const {
	return ((val==l3v_t::F)?((int)0):((val==l3v_t::T)?((int)1):((int)2)));
}

bool_l3v::operator unsigned int() const {
	return (val==l3v_t::F?(unsigned)0:(val==l3v_t::T?(unsigned)1:(unsigned)2));
}

bool_l3v::operator char() const {
	switch (val) {
		case l3v_t::F : return 'F';
		case l3v_t::T : return 'T';
		case l3v_t::x : return 'x';
		default : return 'x';
	}
}
bool_l3v::operator unsigned char() const {
	return bool_l3v((val==l3v_t::F?(unsigned char)0:(val==l3v_t::T?(unsigned char)1:(unsigned char)2)));
}
bool_l3v bool_l3v::operator ^ (bool_l3v a) const {
	return bool_l3v(l3v::o_exclusiva_logica(val,a.val));
}
bool_l3v bool_l3v::operator || (bool_l3v a) const {
	return bool_l3v(l3v::disyuncion_logica(val,a.val));
}
bool_l3v bool_l3v::operator && (bool_l3v a) const {
	return bool_l3v(l3v::conjuncion_logica(val ,a.val));
}
bool_l3v bool_l3v::operator ^ (bool a) const {
	return bool_l3v(l3v::o_exclusiva_logica(val,a));
}
bool_l3v bool_l3v::operator || (bool a) const {
	return bool_l3v(l3v::disyuncion_logica(val,a));
}
bool_l3v bool_l3v::operator && (bool a) const {
	return bool_l3v(l3v::conjuncion_logica(val,a));
}
bool_l3v bool_l3v::operator ! () const {
	return bool_l3v(l3v::negacion_logica(val));
}
bool bool_l3v::operator == (bool_l3v a) const {
	return (val == a.val);
}
bool bool_l3v::operator != (bool_l3v a) const {
	return (val != a.val);
}
bool bool_l3v::operator < (bool_l3v a) const {
	return (l3v::lt(val,a.val));
}
bool bool_l3v::operator <= (bool_l3v a) const {
	return (l3v::lt_eq(val,a.val));
}
bool bool_l3v::operator > (bool_l3v a) const {
	return (l3v::gt(val,a.val));
}
bool bool_l3v::operator >= (bool_l3v a) const {
	return (l3v::gt_eq(val,a.val));
}
bool bool_l3v::operator == (bool a) const {
	if (val==l3v_t::x) return false;
	else return (a == (val==l3v_t::T));
}
bool bool_l3v::operator != (bool a) const {
	if (val==l3v_t::x) return true;
	else return (a != (val==l3v_t::T));
}
bool bool_l3v::operator < (bool a) const {
	if (val==l3v_t::x) return false;
	else return (a < (val==l3v_t::T?true:false));
}
bool bool_l3v::operator <= (bool a) const {
	if (val==l3v_t::x) return false;
	else return (a <= (val==l3v_t::T?true:false));
}
bool bool_l3v::operator > (bool a) const {
	if (val==l3v_t::x) return true;
	else return (a > (val==l3v_t::T?true:false));
}
bool bool_l3v::operator >= (bool a) const {
	if (val==l3v_t::x) return true;
	else return (a >= (val==l3v_t::T?true:false));
}
bool operator == (bool a,bool_l3v b) {
	typedef typename l3v::l3v_t l3v_e;
	if (b.val==l3v_e::x) return false;
	else return (a == (b.val==l3v_e::T));
}
bool operator != (bool a,bool_l3v b) {
	typedef typename l3v::l3v_t l3v_e;
	if (b.val==l3v_e::x) return true;
	else return (a != (b.val==l3v_e::T));
}
bool operator < (bool a,bool_l3v b) {
	typedef typename l3v::l3v_t l3v_e;
	if (b.val==l3v_e::x) return true;
	else return (a < (b.val==l3v_e::T));
}
bool operator <= (bool a,bool_l3v b) {
	typedef typename l3v::l3v_t l3v_e;
	if (b.val==l3v_e::x) return true;
	else return (a <= (b.val==l3v_e::T));
}
bool operator > (bool a,bool_l3v b) {
	typedef typename l3v::l3v_t l3v_e;
	if (b.val==l3v_e::x) return false;
	else return (a > (b.val==l3v_e::T));
}
bool operator >= (bool a,bool_l3v b) {
	typedef typename l3v::l3v_t l3v_e;
	if (b.val==l3v_e::x) return false;
	else return (a >= (b.val==l3v_e::T));
}
bool_l3v::bool_l3v():val(l3v_t::F){}
bool_l3v::bool_l3v(const bool_l3v & a):val(a.val){}
bool_l3v::bool_l3v(l3v_e a):val(a){}
bool_l3v::bool_l3v(bool a):val(a?l3v_t::T:l3v_t::F){}
bool_l3v::bool_l3v(char a):val((a=='F')?(l3v_t::F):((a=='T')?l3v_t::T:l3v_t::x)){}
bool_l3v::bool_l3v(int a):val((a==0)?(l3v_t::F):((a==1)?(l3v_t::T):(l3v_t::x))){}
const bool_l3v & bool_l3v::operator=(const bool_l3v & a){
	val=a.val;
	return (*this);
}
const bool_l3v & bool_l3v::operator=(bool a){
	val=(a?l3v_t::T:l3v_t::F);
	return (*this);
}
const bool_l3v & bool_l3v::operator=(char a){
	val=(a=='F')?l3v_t::F:((a=='T')?l3v_t::T:l3v_t::x);
	return (*this);
}
const bool_l3v & bool_l3v::operator=(int a){
	val=((a==0)?(l3v_t::F):((a==1)?(l3v_t::T):(l3v_t::x)));
	return (*this);
}
const bool_l3v & bool_l3v::operator&=(bool_l3v a) {
	val = l3v::conjuncion_logica((l3v_e)val,(l3v_e)a.val);
	return (*this);
}
const bool_l3v & bool_l3v::operator|=(bool_l3v a) {
	val = l3v::disyuncion_logica((l3v_e)val,(l3v_e)a.val);
	return (*this);
}
const bool_l3v & bool_l3v::operator^=(bool_l3v a)  {
	val = l3v::o_exclusiva_logica((l3v_e)val,(l3v_e)a.val);
	return (*this);
}
const bool_l3v & bool_l3v::operator&=(bool a) {
	val = l3v::conjuncion_logica(val,a);
	return (*this);
}
const bool_l3v & bool_l3v::operator|=(bool a) {
	val = l3v::disyuncion_logica(val,a);
	return (*this);
}
const bool_l3v & bool_l3v::operator^=(bool a)  {
	val = l3v::o_exclusiva_logica(val,a);
	return (*this);
}

const bool_l3v F3v		=	bool_l3v::g_F();
const bool_l3v f3v		=	F3v;
const bool_l3v T3v		=	bool_l3v::g_T();
const bool_l3v t3v		=	T3v;
const bool_l3v DC3v		=	bool_l3v::g_x();
const bool_l3v x3v		=	DC3v;
const bool_l3v X3v		=	DC3v;
const bool_l3v dc3v		=	DC3v;
const bool_l3v Dc3v		=	DC3v;
const bool_l3v dC3v		=	DC3v;

template<const std::size_t NS>
using B3Term_t = std::array<bool_l3v,NS>;

template<const std::size_t NS>
using IB3Term_t = typename B3Term_t<NS>::iterator;

template<const std::size_t NS>
using c_IB3Term_t = typename B3Term_t<NS>::const_iterator;

template<const std::size_t N>
using BFunct_Vt = std::vector<B3Term_t<N>>;

template<const std::size_t N>
using pBFunct_Vt = BFunct_Vt<N>*;

template<const std::size_t N>
using IBFunct_Vt = typename BFunct_Vt<N>::iterator;

template<const std::size_t N>
using c_IBFunct_Vt = typename BFunct_Vt<N>::const_iterator;

template<const std::size_t N>
using Impl_Primos_set_t = std::set<B3Term_t<N>>;

template<const std::size_t N>
using pImpl_Primos_set_t = Impl_Primos_set_t<N>*;

template<const std::size_t N>
using IImpl_Primos_set_t = typename Impl_Primos_set_t<N>::iterator;

template<const std::size_t N>
using c_IImpl_Primos_set_t = typename Impl_Primos_set_t<N>::const_iterator;

template<const std::size_t N>
using Bolsa_Palabras_t=std::set<B3Term_t<N>>;

template<const std::size_t N>
using pBolsa_Palabras_t=Bolsa_Palabras_t<N>*;

template<const std::size_t N>
using IBolsa_Palabras_t=typename Bolsa_Palabras_t<N>::iterator;

template<const std::size_t N>
using c_IBolsa_Palabras_t=typename Bolsa_Palabras_t<N>::const_iterator;

using Conj_Z_t=std::set< Elem_Z_t >;
using IConj_Z_t=typename Conj_Z_t::iterator;
using c_IConj_Z_t=typename Conj_Z_t::const_iterator;

template<const std::size_t N>
using Funct_BTerm_Nums_t=std::map< B3Term_t<N> , Conj_Z_t >;

template<const std::size_t N>
using IFunct_BTerm_Nums_t=typename Funct_BTerm_Nums_t<N>::iterator;

template<const std::size_t N>
using c_IFunct_BTerm_Nums_t=typename Funct_BTerm_Nums_t<N>::const_iterator;

template<const std::size_t N>
using Funct_Num_BTerms_t=std::map< Elem_Z_t , Bolsa_Palabras_t<N> >;

template<const std::size_t N>
using IFunct_Num_BTerms_t=typename Funct_Num_BTerms_t<N>::iterator;

template<const std::size_t N>
using c_IFunct_Num_BTerms_t=typename Funct_Num_BTerms_t<N>::const_iterator;


std::ostream & operator << (std::ostream & out,const bool_l3v & arg) {
	out << char(arg);
	return out;
}

std::istream & operator >> (std::istream & in,bool_l3v & arg) {
	char entrada;
	in >> entrada;
	arg = bool_l3v(entrada);
	return in;
}

#endif // BOOLEAN_L3V_HPP
