#ifndef CBOOLEANCUBE_HPP
#define CBOOLEANCUBE_HPP

#include "boolean_l4v.hpp"
#include "boolean_l3v.hpp"
#include "boolean_l2rv.hpp"
#include "parsers_so.hpp"
#include "parsers_mo.hpp"
#include "auxiliary_functions.hpp"

using ullint = unsigned long long int;
using ulint  = unsigned long int;
using uint   = unsigned int;
using uchint = unsigned char;

template<std::size_t NE,std::size_t NS> class parser_linea_mo;

template<const std::size_t NE,const std::size_t NS>
struct Cube {
	B4Term_t<NE>	cube_in;
	B2Term_t<NS>	cube_out;
	constexpr inline bool operator==(const Cube & otro) const { return ((cube_in==otro.cube_in)&&(cube_out==otro.cube_out));}
	constexpr inline bool operator!=(const Cube & otro) const { return ((cube_in!=otro.cube_in)||(cube_out!=otro.cube_out));}
	constexpr inline bool operator<(const Cube & otro) const { return (((cube_in<otro.cube_in)&&(cube_out<=otro.cube_out))||((cube_in<=otro.cube_in)&&(cube_out<otro.cube_out)));}
	constexpr inline bool operator>(const Cube & otro) const { return (((cube_in>otro.cube_in)&&(cube_out>=otro.cube_out))||((cube_in>=otro.cube_in)&&(cube_out>otro.cube_out)));}
	constexpr inline bool operator<=(const Cube & otro) const { return (((cube_in<=otro.cube_in)&&(cube_out<=otro.cube_out)));}
	constexpr inline bool operator>=(const Cube & otro) const { return (((cube_in>=otro.cube_in)&&(cube_out>=otro.cube_out)));}
};	

template<const std::size_t NE,const std::size_t NS>
std::ostream & operator << (std::ostream & out , const Cube<NE,NS> & arg) {
	out << "<" << "[";			
	for( uint i = 0 ; i < NE ; ++i ) {
		const bool_l4v value4 = arg.cube_in[i];
		const char salidai = char(value4);
		out << salidai;
	}
	for( uint i = 0 ; i < NS ; ++i ) {
		const bool value2 = arg.cube_out[i];
		const char salidao = ((value2)?'T':'F');
		out << salidao;
	}
	out << "]>";
	return out;
}

template<const std::size_t NE>
struct Cube<NE,0u> {
	B4Term_t<NE>	cube_in;
};

template<const std::size_t NE,const std::size_t NS>
using B2rTerm = std::array<bool_l2rv,NE+NS>;

template<std::size_t NE,std::size_t NS>
using BinCube = std::pair<ullint,B2rTerm<NE,NS>>;

template<std::size_t NE,std::size_t NS>
using BooleanCube = std::pair<ullint,Cube<NE,NS>>;

template<const std::size_t NE,const std::size_t NS>
class CBinCube;

class boolean_l2rv;

template<const std::size_t NE,const std::size_t NS>
class CBooleanCube : public BooleanCube<NE,NS> {
private:
	static constexpr ullint pow2NENS = pow2<NS>()+pow3<NE>()-2;
	static constexpr ullint max_key = (pow2<NE+NS>())+(pow3<NE+NS>()-pow3<NS>())+(NE*pow2NENS);

private:
	inline
	Cube<NE,NS> & aCube() {
		return this->BooleanCube<NE,NS>::second;
	}
	const Cube<NE,NS> & aCube() const {
		return this->BooleanCube<NE,NS>::second;
	}
	Cube<NE,NS> & aCube(std::size_t i) {
		return this->BooleanCube<NE,NS>::second[i];
	}
	const Cube<NE,NS> & aCube(std::size_t i) const {
		return this->BooleanCube<NE,NS>::second[i];
	}
	std::size_t aUInt(std::size_t arg) {
		return this->BooleanCube<NE,NS>::first=arg;
	}
	std::size_t aUInt() const {
		return this->BooleanCube<NE,NS>::first;
	}

	ullint calculo_de_key() const {
		std::array<uchint,NE+NS> Nb,N2;
		for( uint i=0; i < NE ; ++i ) {
			if (in(i)==X4v){
				Nb[i]=1;
				N2[i]=1;
			}
			else if (in(i)==T4v) {
				Nb[i]=1;
				N2[i]=0;
			}
			else {
				Nb[i]=0;
				N2[i]=0;
			}
		}
		for( uint i=0; i < NS ; ++i ) {
			switch(out(i)){
			case true :
				Nb[i+NE]=1;
				N2[i+NE]=0;
				break;
			case false :
				Nb[i+NE]=0;
				N2[i+NE]=0;
			}
		}
		ullint Np,n2s,Ns;
		Np=0;
		Ns=0;
		ullint pot2 = 1;
		ullint pot3 = 1;
		for(uint i=0;i< NE+NS;++i){
			Np += Nb[i]*pot2;
			Ns += N2[i]*pot3;
			pot2*=2;
			pot3*=3;
		}
		n2s=0;
		for(uint i=0;i< NE+NS;++i){
			n2s += N2[i];
		}
		return (max_key-Np-Ns-(n2s*pow2NENS));
	}
	public:
	ullint calculo_de_key() {
		std::array<uchint,NE+NS> Nb,N2;
		for( uint i=0; i < NE ; ++i ) {
			if (in(i)==X4v){
				Nb[i]=1;
				N2[i]=2;
			}
			else if (in(i)==T4v) {
				Nb[i]=1;
				N2[i]=1;
			}
			else {
				Nb[i]=0;
				N2[i]=0;
			}
		}
		for( uint i=0; i < NS ; ++i ) {
			switch(out(i)){
			case true :
				Nb[i+NE]=1;
				N2[i+NE]=0;
				break;
			case false :
				Nb[i+NE]=0;
				N2[i+NE]=0;
			}
		}
		ullint Np,n2s,Ns;
		Np=0;
		Ns=0;
		ullint pot2 = 1;
		ullint pot3 = 1;
		for(uint i=0;i< NE+NS;++i){
			Np += Nb[i]*pot2;
			Ns += N2[i]*pot3;
			pot2*=2;
			pot3*=3;
		}
		n2s=0;
		for(uint i=0;i< NE+NS;++i){
			n2s += N2[i];
		}
		return (max_key-Np-Ns-(n2s*pow2NENS));
	}
public:
	using	B4Term		=	B4Term_t<NE>;
	using	IB4Term		=	IB4Term_t<NE>;
	using	c_IB4Term	=	c_IB4Term_t<NE>;
	using	B2Term		=	B2Term_t<NS>;
	using	IB2Term		=	typename B2Term::iterator;
	using	c_IB2Term	=	typename B2Term::const_iterator;

friend class parser_linea_mo<NE,NS>;

public: 
	inline B4Term & in() {
		return (this->aCube()).cube_in;
	}
	inline const B4Term & in() const {
		return (this->aCube()).cube_in;
	}
	inline bool_l4v & in(std::size_t I) {
		return (this->aCube()).cube_in[I];
	}
	inline const bool_l4v & in(std::size_t I) const {
		return (this->aCube()).cube_in[I];
	}
	inline B2Term & out() {
		return (this->aCube()).cube_out;
	}
	inline const B2Term & out() const {
		return (this->aCube()).cube_out;
	}
	inline bool & out(std::size_t I) {
		return (this->aCube()).cube_out[I];
	}
	inline const bool & out(std::size_t I) const {
		return (this->aCube()).cube_out[I];
	}
	inline std::size_t key() const {
		return this->aUInt();
	}
	inline std::size_t key(std::size_t k) {
		return this->aUInt(k);
	}
	inline bool is_empty() const {
		bool empty_in = false;
		for(size_t i=0 ; i < NE ; ++i) {
			if (this->in(i)==e4v) {
				empty_in=true;
				break;
			}
		}
		if (empty_in) return true;
		bool empty_out = true;
		if (empty_in==false) {
			for(std::size_t i=0 ; i < NS ; ++i) {
				if (this->out(i)) {
					empty_out=false;
					break;
				}
			}
		}
		return (empty_out);
	}
public:
	inline bool is_input_is_empty() const {
		for(size_t i=0 ; i < NE ; ++i) {
			if (this->in(i)==e4v) {
				return true;
			}
		}
		return false;
	}
public:
	CBooleanCube() {
		this->key(0);
		for(std::size_t i=0; i < NE ; ++i)
			this->in()[i]=e4v;
		for(std::size_t i=0; i < NS ; ++i)
			this->out(i)=false;
	}
	
	CBooleanCube(const Cube<NE,NS> & arg) {
		for(std::size_t i=0; i < NE ; ++i)
			this->in()[i]=arg.cube_in[i];
		for(std::size_t i=0; i < NS ; ++i)
			this->out(i)=arg.cube_out[i];
		this->key(this->calculo_de_key());
	}

	CBooleanCube(const CBinCube<NE,NS> & arg,const std::array<bool,NE+NS> & crec) {
		for(uint i=0;i<NE;++i) {
			if(arg.read(i)==T2rv) {
				this->in(i)=((crec[i])?T4v:F4v);
			}
			else {
				this->in(i)=X4v;
			}
		}
		for(uint i=NE;i<NE+NS;++i) {
			if(arg.read(i)==T2rv) {
				this->out(i)=T4v;
			}
			else {
				this->out(i)=F4v;
			}
		}
		this->key(this->calculo_de_key());
	}

	CBooleanCube(universe op) {
		for(std::size_t i=0; i < NE ; ++i)
			in(i)=X4v;
		for(std::size_t i=0; i < NS ; ++i)
			out(i)=true;
		this->key(this->calculo_de_key());
	}

	CBooleanCube(std::size_t N,universe_1_de_m op) {
		for(std::size_t i=0; i < NE ; ++i)
			in(i)=X4v;
		for(std::size_t i=0; i < NS ; ++i)
			out(i)=false;
		out(N)=true;
		this->key(this->calculo_de_key());
	}

	CBooleanCube(std::size_t N,positive_half_space_1_of_n op) {
		for(std::size_t i=0; i < NE ; ++i)
			in(i)=X4v;
		for(std::size_t i=0; i < NS ; ++i)
			out(i)=true;
		in(N)=T4v;
		this->key(this->calculo_de_key());
	}

	CBooleanCube(std::size_t N,negative_half_space_1_of_n op) {
		for(std::size_t i=0; i < NE ; ++i)
			in(i)=X4v;
		for(std::size_t i=0; i < NS ; ++i)
			out(i)=true;
		in(N)=F4v;
		this->key(this->calculo_de_key());
	}

	CBooleanCube(const CBooleanCube & arg)	{
		this->in()=arg.in();
		std::cout << (*this) << std::endl;
		this->out()=arg.out();
		std::cout << (*this) << std::endl;
		this->key(arg.key());
		std::cout << (*this) << std::endl;
	}

	CBooleanCube(const B4Term & argin,const B2Term & argout):
		Cube<NE,NS>::cube_in(argin),
		Cube<NE,NS>::cube_out(argout)
	{this->key(this->calculo_de_key());}

	CBooleanCube(const std::string & linea){
		std::string nlinea;
		nlinea = linea;
		parser_linea_mo<NE,NS> cube(nlinea);
		this->in() = cube.in;
		this->out() = cube.out;
		this->key(this->calculo_de_key());
	}

	const CBooleanCube & operator = (const CBooleanCube & arg) {
		this->second.cube_in   = arg.second.cube_in;
		this->second.cube_out  = arg.second.cube_out;
		this->key(this->calculo_de_key());
		return (*this);
	}

    const CBooleanCube & operator = (const Cube<NE,NS> & arg) {
		this->second.in()   = arg.in;
		this->second.out()  = arg.out;
		this->first.key(this->calculo_de_key());
		return (*this);
	}

	const CBooleanCube & operator = (const std::string & linea) {
		parser_linea_mo<NE,NS> cube(linea);
		this->in() = cube.in;
		this->out() = cube.out;
		this->key(this->calculo_de_key());
		return (*this);
	}

	CBooleanCube operator &&(const CBooleanCube & arg) const {
		CBooleanCube ret(*this);
		for(std::size_t I=0 ; I < NE ; ++I)
			ret.write(I,this->read4(I) && arg.read4(I));
		for(std::size_t I=0 ; I < NS ; ++I)
			ret.write(I,this->read2(I) && arg.read2(I));
		ret.key(ret.calculo_de_key());
		return ret;
	}

	CBooleanCube operator ||(const CBooleanCube & arg) const {
	CBooleanCube ret(*this);
	for(std::size_t I=0 ; I < NE ; ++I)
		ret.write(I,this->read4(I) || arg.read4(I));
	for(std::size_t I=0 ; I < NS ; ++I)
		ret.write(I,this->read2(I) || arg.read2(I));
	ret.key(ret.calculo_de_key());
	return ret;
	}

	CBooleanCube operator ^(const CBooleanCube & arg) const {
	CBooleanCube ret(*this);
	for(std::size_t I=0 ; I < NE ; ++I)
		ret.write(I,this->read4(I) ^ arg.read4(I));
	for(std::size_t I=0 ; I < NS ; ++I)
		ret.write(I,this->read2(I) ^ arg.read2(I));
	ret.key(ret.calculo_de_key());
	return ret;
	}

	const CBooleanCube & operator &=(const CBooleanCube & arg) {
	for(std::size_t I=0 ; I < NE ; ++I)
		this->write(I,this->read4(I) && arg.read4(I));
	for(std::size_t I=0 ; I < NS ; ++I)
		this->write(I,this->read2(I) && arg.read2(I));
	this->key(this->calculo_de_key());
	return *this;
	}

	const CBooleanCube & operator |=(const CBooleanCube & arg){
	for(std::size_t I=0 ; I < NE ; ++I)
		this->write(I,this->read4(I) || arg.read4(I));
	for(std::size_t I=0 ; I < NS ; ++I)
		this->write(I,this->read2(I) || arg.read2(I));
	this->key(this->calculo_de_key());
	return *this;
}

	const CBooleanCube & operator ^=(const CBooleanCube & arg){
		for(std::size_t I=0 ; I < NE ; ++I)
			this->write(I,this->read4(I) ^ arg.read4(I));
		for(std::size_t I=0 ; I < NS ; ++I)
			this->write(I,this->read2(I) ^ arg.read2(I));
		this->key(this->calculo_de_key());
		return *this;
}


	bool operator ==(const CBooleanCube & arg) const {
		bool igual_in  = true;
		bool igual_out = true;
		if((this->is_empty())&&(arg.is_empty())) return true;
		else if((this->is_empty())^(arg.is_empty())) return false;
		for(std::size_t i=0;i < NE; ++i) {
			if (this->read4(i)!=arg.read4((i))){
				igual_in = false;
				break;
			}
		}
		if (igual_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if (this->read2(i)!=arg.read2((i))){
					igual_out = false;
					break;
				}
			}
		}
		else {
			return false;
		}
		return igual_out;
	}

	bool operator !=(const CBooleanCube & arg) const {
		return (!(*this==arg));
	}

	bool operator >=(const CBooleanCube & arg) const {
		bool contiene_in  = true;
		bool contiene_out = true;

		if(arg.is_empty()) return true;
		else if((this->is_empty())&&(!(arg.is_empty()))) return false;

		for(std::size_t i=0;i < NE; ++i) {
			if (this->read4(i) < arg.read4(i)){ 
				contiene_in = false;
				break;
			}
		}
		if (contiene_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if (!(this->read2(i)) and (arg.read2(i))){
					contiene_out = false;
					break;
				}
			}
		}
		else {
			return false;
		}
		return contiene_out;
	}

	bool operator <= (const CBooleanCube & arg) const {

		if(this->is_empty()) return true;
		else if(!(this->is_empty())&&(arg.is_empty())) return false;

		for(std::size_t i=0;i < NE; ++i) {
			if (this->read4(i) > arg.read4(i)){
				return false;
			}
		}

		for(std::size_t i=0; i < NS; ++i) {
			if ((this->read2(i)) and !(arg.read2(i))){
				return false;
			}
		}

		return true;
	}

	bool operator >(const CBooleanCube & arg) const {
		bool contiene_in			= false;
		bool contiene_in_estricto	= false;
		bool contiene_out_estricto	= false;

		if(this->is_empty()) return false;
		else if(!(this->is_empty())&&(arg.is_empty())) return true;

		for(std::size_t i=0;i < NE; ++i) {
			if (this->read4(i) == arg.read4(i)) {
				contiene_in = true;
			}
			else if (this->read4(i) > arg.read4(i)) {
				contiene_in = true;
				contiene_in_estricto = true;
			}
			else if (this->read4(i) < arg.read4(i)){
				contiene_in = false;
				contiene_in_estricto = false;
				break;
			}
		}
		if (contiene_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if ((this->read2(i)) && (!(arg.read2(i)))) {
					contiene_out_estricto = true;
				}
				else if ((!(this->read2(i))) && (arg.read2(i))) {
					contiene_out_estricto = false;
					contiene_in_estricto = false;
					break;
				}
			}
		}
		if ((contiene_in_estricto)or(contiene_out_estricto))
			return true;
		else
			return false;
	}

	bool operator <(const CBooleanCube & arg) const {
		bool contenido_in			= false;
		bool contenido_in_estricto	= false;
		bool contenido_out_estricto	= false;
		for(std::size_t i=0;i < NE; ++i) {
			if (this->read4(i) == arg.read4(i)) {
				contenido_in = true;
			}
			else if (this->read4(i) < arg.read4(i)) {
				contenido_in = true;
				contenido_in_estricto = true;
			}
			else if (this->read4(i) > arg.read4(i)){
				contenido_in = false;
				contenido_in_estricto = false;
				break;
			}
		}
		if (contenido_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if ((!(this->read2(i))) && (arg.read2(i))) {
					contenido_out_estricto = true;
				}
				else if ((this->read2(i)) && (!(arg.read2(i)))) {
					contenido_out_estricto = false;
					contenido_in_estricto = false;
					break;
				}
			}
		}
		if ((contenido_in_estricto)or(contenido_out_estricto))
			return true;
		else
			return false;
	}

	explicit CBooleanCube(const CBooleanCube & arg1,const CBooleanCube & arg2,or_t op) {
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->in(i)=arg1.in(i) || arg2.in(i);
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->out(i)=arg1.out(i) || arg2.out(i);
		}
		this->key(this->calculo_de_key());
	}
	
	
	

	explicit CBooleanCube(const CBooleanCube & arg1,const CBooleanCube & arg2,and_t op) {
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->write(i,arg1.read4(i) && arg2.read4(i));
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->write(i,arg1.read2(i) && arg2.read2(i));
		}
		this->key(this->calculo_de_key());
	}

	explicit CBooleanCube(const CBooleanCube & arg1,const CBooleanCube & arg2,diff_t op) {
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->write(i,arg1.read4(i) - arg2.read4(i));
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->write(i,(arg1.read2(i)) && (!(arg2.read2(i))));
		}
		this->key(this->calculo_de_key());
	}

	explicit CBooleanCube(const CBooleanCube & arg1,const CBooleanCube & arg2,cofactor_t op):
		CBooleanCube(arg1)
	{
		this->m_cofactor(arg2);
		this->key(this->calculo_de_key());
	}

	explicit CBooleanCube(const CBooleanCube & arg,std::size_t j,bool posneg,cofactor_t op):
		CBooleanCube(*arg)
	{
		this->m_cofactor(j,posneg);
		this->key(this->calculo_de_key());
	}

	explicit CBooleanCube(	const CBooleanCube & arg1,
					const CBooleanCube & arg2,
					xor_t op) {
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->in(i)=arg1.in(i) ^ arg2.in(i);
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->out(i)=arg1.out(i) ^ arg2.out(i);
		}
		this->key(this->calculo_de_key());
	}

	explicit CBooleanCube(const CBooleanCube & arg,not_t op){
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->write(i,!(arg.read4(i)));
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->write(i,!(arg.read2(i)));
		}
		this->key(this->calculo_de_key());
	}

	const CBooleanCube & assign(	const CBooleanCube & arg1,
									const CBooleanCube & arg2,
									or_t op) {
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->in(i)=arg1.in(i) || arg2.in(i);
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->out(i)=arg1.out(i) || arg2.out(i);
		}
		this->key(this->calculo_de_key());
		return *this;
	}

	const CBooleanCube & assign(	const CBooleanCube & arg1,
									const CBooleanCube & arg2,
									and_t op) {
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->in(i)=arg1.in(i) && arg2.in(i);
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->out(i)=arg1.out(i) && arg2.out(i);
		}
		this->key(this->calculo_de_key());
		return *this;
	}

	const CBooleanCube & assign(	const CBooleanCube & arg1,
									const CBooleanCube & arg2,
									xor_t op) {

		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->in(i)=arg1.in(i) ^ arg2.in(i);
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->out(i)=arg1.out(i) ^ arg2.out(i);
		}
		this->key(this->calculo_de_key());
		return *this;
	}

	const CBooleanCube & assign(	const CBooleanCube & arg1,
									const CBooleanCube & arg2,
									diff_t op) {
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->in(i)=arg1.in(i)-arg2.in(i);
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->out(i)=(arg1.out(i))&&(!(arg2.out(i)));
		}
		this->key(this->calculo_de_key());
		return *this;
	}


	CBooleanCube operator - (const CBooleanCube & arg) const {
		CBooleanCube ret(*this,arg,diff_t::op);
		ret.key(ret.calculo_de_key());
		return ret;
	}

	const CBooleanCube & operator -= (const CBooleanCube & arg) {
		*this &= !arg;
		this->key(this->calculo_de_key());
		return *this;
	}

	inline std::size_t distin(const CBooleanCube & arg) const {
		if ((this->is_empty())^(arg.is_empty())) {
			return NE;
		}
		else if (!((this->is_empty())or((arg.is_empty())))) {
			std::size_t distancia = 0;
			for( std::size_t i=0 ; i < NE ; ++i ){
				if ((this->read4(i)&&arg.read4(i))==e4v)
					++distancia;
			}
			return distancia;
		}
		return 0;
	}

	inline std::size_t distout(const CBooleanCube & arg) const {
		if ((this->is_empty())^(arg.is_empty())) {
			return 1;
		}
		else if (!((this->is_empty())or((arg.is_empty())))) {
			for( std::size_t i=0 ; i < NS ; ++i ){
				if (this->read2(i)&&arg.read2(i)) {
					return 0;
				}
			}
			return 1;
		}
		return 0;
	}

	inline std::size_t dist(const CBooleanCube & arg) const {
		if ((this->is_empty())^(arg.is_empty())) {
			return (NE+1);
		}
		else if (!((this->is_empty())or((arg.is_empty())))) {
			std::size_t distancia = 0;
			for( std::size_t i=0 ; i < NE ; ++i ){
				if ((this->read4(i)&&arg.read4(i))==e4v)
					++distancia;
			}
			for( std::size_t i=0 ; i < NS ; ++i ){
				if (this->read2(i)&&arg.read2(i)) {
					return distancia;
				}
			}
			++distancia;
			return distancia;
		}
		return 0;
	}

	// CONSENSUS = operator*
	CBooleanCube operator*(const CBooleanCube & arg) 
	{ 
		CBooleanCube ret(*this);
		const std::size_t d_i =this->distin(arg);
		const std::size_t d_o =this->distout(arg);
		if ((d_i+d_o)!=1) {
			
			ret&=arg;
		}
		else if((d_i==1) and (d_o==0)) {
			for( std::size_t i = 0 ; i < NE ; ++i ) {
				const bool_l4v intersect = ((this->read4(i))&&(arg.read4(i)));
				if (intersect!=e4v)
					ret.write(i,intersect);
				else
					ret.write(i,x4v);
			}
			for( std::size_t i = 0 ; i < NS ; ++i) {
				ret.write(i,(this->read2(i))&&(arg.read2(i)));
			}
		}
		else {
			for( std::size_t i = 0 ; i < NE ; ++i ) {
				ret.write(i,(this->read4(i))&&(arg.read4(i)));
			}
			for( std::size_t i = 0 ; i < NS ; ++i) {
				ret.write(i,this->read2(i) || arg.read2(i));
			}
		}
		this->key(this->calculo_de_key());
		return ret;
	}

	// m_CONSENSUS = operator *=
	const CBooleanCube & operator*=(const CBooleanCube & arg) {

		const std::size_t d_i =this->distin(arg);
		const std::size_t d_o =this->distout(arg);
		if ((d_i+d_o)!=1) {
			(*this)&=arg;
		}
		else if((d_i==1) and (d_o==0)) {
			for( std::size_t i = 0 ; i < NE ; ++i ) {
				const bool_l4v intersect = ((this->read4(i))&&(arg.read4(i)));
				if (intersect!=e4v)
					this->write(i,intersect);
				else
					this->write(i,x4v);
			}
			for( std::size_t i = 0 ; i < NS ; ++i) {
				this->write(i,(this->read2(i))&&(arg.read2(i)));
			}
		}
		else {
			for( std::size_t i = 0 ; i < NE ; ++i ) {
				this->write(i,(this->read4(i))&&(arg.read4(i)));
			}
			for( std::size_t i = 0 ; i < NS ; ++i) {
				this->write(i,this->read2(i) || arg.read2(i));
			}
		}
		this->key(this->calculo_de_key());
		return *this;
	}

	CBooleanCube cofactor(const CBooleanCube<NE,NS> & p)  const
	{
		CBooleanCube<NE,NS> I(*this,p,cofactor_t::op);
		I.key(I.calculo_de_key());
		return I;
	}

	const CBooleanCube & m_cofactor(const CBooleanCube & p) {
		CBooleanCube c(*this);
		for(uint k = 0 ; k < NE ; ++k) {
			if (((*this) && p).is_empty()) {
				c.write(k,e4v);
				(*this)=c;
				return (*this);
			}
			else if (p.read4(k) < x4v) {
				c.write(k,x4v);
			}
		}
		for(uint k = NE ; k < NE+NS ; ++k) {
			if (!(p.read2(k)))
				c.write(k,false);
		}
		(*this)=c;
		this->key(this->calculo_de_key());
		return (*this);
	}

	CBooleanCube cofactor(std::size_t j,bool posneg) const {
		const CBooleanCube & c = (*this);
		CBooleanCube I(c,j,posneg,cofactor_t::op);
		I.key(I.calculo_de_key());
		return I;
	}

	const CBooleanCube & m_cofactor(std::size_t j,bool posneg) {
		*this = this->cofactor(j,posneg);
		this->key(this->calculo_de_key());
		return *this;
	}

	void write(std::size_t arg,bool_l4v val) {
		this->in(arg) = val;
		this->key(this->calculo_de_key());
	}

	void write(std::size_t arg,bool val) {
		this->out(arg) = val;
		this->key(this->calculo_de_key());
	}

	bool_l4v read4(std::size_t arg) const {
		return this->in(arg);
	}

	bool read2(std::size_t arg) const {
		return this->out(arg);
	}

	template<const std::size_t E,const std::size_t S>
	friend
	std::ostream & operator << (std::ostream & out,const CBooleanCube<E,S> & arg) {
		out << "<" << arg.key() << "," << "[";
		for( uint i = 0 ; i < E ; ++i ) {
			const bool_l4v value4 = arg.in(i);
			const char salidai = char(value4);
			out << salidai;
		}
		for( uint i = 0 ; i < S ; ++i ) {
			const bool value2 = arg.out(i);
			const char salidao = ((value2)?'T':'F');
			out << salidao;
		}
		out << "]>";
		return out;
	}
};

template<const std::size_t NumEntradas>
class CBooleanCube<NumEntradas,0> : public BooleanCube<NumEntradas,0> {
private:
	inline
	Cube<NumEntradas,0> & aCube() {
		return this->BooleanCube<NumEntradas,0>::second;
	}
	const Cube<NumEntradas,0> & aCube() const {
		return this->BooleanCube<NumEntradas,0>::second;
	}
	Cube<NumEntradas,0> & aCube(std::size_t i) {
		return this->BooleanCube<NumEntradas,0>::second[i];
	}
	const Cube<NumEntradas,0> & aCube(std::size_t i) const {
		return this->BooleanCube<NumEntradas,0>::second[i];
	}
	std::size_t & aUInt() {
		return this->BooleanCube<NumEntradas,0>::first;
	}
	const std::size_t & aUInt() const {
		return this->BooleanCube<NumEntradas,0>::first;
	}

public:
	using	B4Term		=	B4Term_t<NumEntradas>;
	using	IB4Term		=	IB4Term_t<NumEntradas>;
	using	c_IB4Term	=	c_IB4Term_t<NumEntradas>;
	using	B2Term		=	B2Term_t<0>;

friend class parser_linea_so<NumEntradas,0>;

public: 
	inline B4Term & in() {
		return (this->aCube()).cube_in;
	}
	inline const B4Term & in() const {
		return (this->aCube()).cube_in;
	}
	inline bool_l4v & in(std::size_t I) {
		return (this->aCube()).cube_in[I];
	}
	inline const bool_l4v & in(std::size_t I) const {
		return (this->aCube()).cube_in[I];
	}
	inline std::size_t key() const {
		return this->aUInt();
	}
	inline std::size_t key(std::size_t k) {
		return this->aUInt()=k;
	}
	inline std::size_t key() {
		return this->aUInt();
	}
	inline bool is_empty() const {
		for(size_t i=0 ; i < NumEntradas ; ++i) {
			if (this->in(i)==e4v) {
				return true;
			}
		}
		return false;
	}
public:
	inline bool is_input_is_empty() const {
		for(size_t i=0 ; i < NumEntradas ; ++i) {
			if (this->in(i)==e4v) {
				return true;
			}
		}
		return false;
	}
public:
	CBooleanCube() {
		this->key(0);
		for(std::size_t i=0; i < NumEntradas ; ++i)
			this->in()[i]=e4v;
	}

	CBooleanCube(const CBinCube<NumEntradas,0> & arg,const std::array<bool,NumEntradas> & crec) {
		this->key(arg.key());
		for(uint i=0;i<NumEntradas;++i) {
			if(arg.read(i)==T2rv) {
				this->in(i)=((crec[i])?T4v:F4v);
			}
			else {
				this->in(i)=X4v;
			}
		}
	}

	CBooleanCube(universe op) {
		this->key(0);
		for(std::size_t i=0; i < NumEntradas ; ++i)
			in(i)=X4v;
	}

	CBooleanCube(std::size_t N,positive_half_space_1_of_n op) {
		this->key(0);
		for(std::size_t i=0; i < NumEntradas ; ++i)
			in(i)=X4v;
		in(N)=T4v;
	}

	CBooleanCube(std::size_t N,negative_half_space_1_of_n op) {
		this->key(0);
		for(std::size_t i=0; i < NumEntradas ; ++i)
			in(i)=X4v;
		in(N)=F4v;
	}

	CBooleanCube(const CBooleanCube & arg)
	{
		this->in()=arg.in();
		this->key(arg.key());
	}

	CBooleanCube(const B4Term & argin):
		Cube<NumEntradas,0>::cube_in(argin)
	{this->key(0);}

	CBooleanCube(const std::size_t n_linea,const std::string & linea,cubeset_t V){
		const auto N = 10*(NumEntradas+1);
		char c_nlinea[N];
		fill_with_nulls<N>(c_nlinea);
		std::string nlinea;
		nlinea = linea;
		parser_linea_so<NumEntradas,0> cube(nlinea,V);
		switch(V) {
			case cubeset_t::ON : this->in() = cube.inon;
								 break;
			case cubeset_t::OFF : this->in() = cube.inoff;
								 break;
			case cubeset_t::DC : this->in() = cube.indc;
		}
		this->key(n_linea);
	}

	const CBooleanCube & operator = (const CBooleanCube & arg) {
		this->in()   = arg.in();
		this->key(arg.key());
		return (*this);
	}

	const CBooleanCube & assign (const std::string & linea,cubeset_t V) {
		parser_linea_so<NumEntradas,0> cube(linea,V);
		this->in() = cube.in;
		this->key(0);
		return (*this);
	}

	CBooleanCube operator &&(const CBooleanCube & arg) const {
		CBooleanCube ret(*this);
		for(std::size_t I=0 ; I < NumEntradas ; ++I)
			ret.write(I,this->read4(I) && arg.read4(I));
		return ret;
	}

	CBooleanCube operator ||(const CBooleanCube & arg) const {
	CBooleanCube ret(*this);
	for(std::size_t I=0 ; I < NumEntradas ; ++I)
		ret.write(I,this->read4(I) || arg.read4(I));
	return ret;
	}

	CBooleanCube operator ^(const CBooleanCube & arg) const {
	CBooleanCube ret(*this);
	for(std::size_t I=0 ; I < NumEntradas ; ++I)
		ret.write(I,this->read4(I) ^ arg.read4(I));
	return ret;
	}

	const CBooleanCube & operator &=(const CBooleanCube & arg) {
	for(std::size_t I=0 ; I < NumEntradas ; ++I)
		this->write(I,this->read4(I) && arg.read4(I));
	return *this;
	}

	const CBooleanCube & operator |=(const CBooleanCube & arg){
	for(std::size_t I=0 ; I < NumEntradas ; ++I)
		this->write(I,this->read4(I) || arg.read4(I));
	return *this;
}

	const CBooleanCube & operator ^=(const CBooleanCube & arg){
		for(std::size_t I=0 ; I < NumEntradas ; ++I)
			this->write(I,this->read4(I) ^ arg.read4(I));
		return *this;
}


	bool operator ==(const CBooleanCube & arg) const {
		if((this->is_empty())&&(arg.is_empty())) return true;
		else if((this->is_empty())^(arg.is_empty())) return false;
		for(std::size_t i=0;i < NumEntradas; ++i) {
			if (this->read4(i)!=arg.read4((i))){
				return false;
			}
		}
		return true;
	}

	bool operator !=(const CBooleanCube & arg) const {
		return (!(*this==arg));
	}

	bool operator >=(const CBooleanCube & arg) const {
		if(arg.is_empty()) return true;
		else if((this->is_empty())&&(!(arg.is_empty()))) return false;

		for(std::size_t i=0;i < NumEntradas; ++i) {
			if (this->read4(i) < arg.read4(i)){
				return false;
			}
		}
		return true;
	}

	bool operator <= (const CBooleanCube & arg) const {
		if(this->is_empty()) return true;
		else if(!(this->is_empty())&&(arg.is_empty())) return false;

		for(std::size_t i=0;i < NumEntradas; ++i) {
			if (this->read4(i) > arg.read4(i)){
				return false;
			}
		}
		return true;
	}

	bool operator >(const CBooleanCube & arg) const {
		if(this->is_empty()) return false;
		else if(!(this->is_empty())&&(arg.is_empty())) return true;
		bool ret = true;
		for(std::size_t i=0;i < NumEntradas; ++i) {
			if (this->read4(i) == arg.read4(i)) {
				ret = ret && true ;
			}
			if (this->read4(i) != arg.read4(i)) {
				ret = ret && false ;
			}
			else if (this->read4(i) < arg.read4(i)){
				return false;
			}
		}
		return ret;
	}

	bool operator <(const CBooleanCube & arg) const {
		if(arg.is_empty()) return false;
		if((this->is_empty())&&(!(arg.is_empty()))) return true;
		bool ret = true;
		for(std::size_t i=0;i < NumEntradas; ++i) {
			if (this->read4(i) == arg.read4(i)) {
				ret = ret && true ;
			}
			if (this->read4(i) != arg.read4(i)) {
				ret = ret && false ;
			}
			else if (this->read4(i) > arg.read4(i)){
				return false;
			}
		}
		return ret;
	}

	CBooleanCube(const CBooleanCube & arg1,const CBooleanCube & arg2,or_t op) {
		for(std::size_t i = 0 ; i < NumEntradas ; ++i) {
			this->in(i)=arg1.in(i) || arg2.in(i);
		}
	}

	CBooleanCube(const CBooleanCube & arg1,const CBooleanCube & arg2,and_t op) {
		for(std::size_t i = 0 ; i < NumEntradas ; ++i) {
			this->write(i,arg1.read4(i) && arg2.read4(i));
		}
	}

	CBooleanCube(const CBooleanCube & arg1,const CBooleanCube & arg2,diff_t op) {
		for(std::size_t i = 0 ; i < NumEntradas ; ++i) {
			this->write(i,arg1.read4(i) - arg2.read4(i));
		}
	}

	CBooleanCube(const CBooleanCube & arg1,const CBooleanCube & arg2,cofactor_t op):
		CBooleanCube(*arg1)
	{
		CBooleanCube c(*this);
		const CBooleanCube & p = arg2;
		for(uint k = 0 ; k < NumEntradas ; ++k) {
			if (((*this) && p).is_empty()) {
				c.write(k,e4v);
				(*this)=c;
				break;
			}
			else if (p.read4(k) < x4v) {
				c.write(k,x4v);
			}
		}
	
		(*this)=c;
		this->key(this->calculo_de_key());
	}

	CBooleanCube(const CBooleanCube & arg,std::size_t j,bool posneg,cofactor_t op):
		CBooleanCube(*arg)
	{
		this->m_cofactor(j,posneg);
	}

	CBooleanCube(	const CBooleanCube & arg1,
					const CBooleanCube & arg2,
					xor_t op) {
		for(std::size_t i = 0 ; i < NumEntradas ; ++i) {
			this->in(i)=arg1.in(i) ^ arg2.in(i);
		}
	}

	const CBooleanCube & assign(	const CBooleanCube & arg1,
									const CBooleanCube & arg2,
									or_t op) {
		for(std::size_t i = 0 ; i < NumEntradas ; ++i) {
			this->in(i)=arg1.in(i) || arg2.in(i);
		}
		return *this;
	}

	const CBooleanCube & assign(	const CBooleanCube & arg1,
									const CBooleanCube & arg2,
									and_t op) {
		for(std::size_t i = 0 ; i < NumEntradas ; ++i) {
			this->in(i)=arg1.in(i) && arg2.in(i);
		}
		return *this;
	}

	const CBooleanCube & assign(	const CBooleanCube & arg1,
									const CBooleanCube & arg2,
									xor_t op) {

		for(std::size_t i = 0 ; i < NumEntradas ; ++i) {
			this->in(i)=arg1.in(i) ^ arg2.in(i);
		}
		return *this;
	}

	const CBooleanCube & assign(	const CBooleanCube & arg1,
									const CBooleanCube & arg2,
									diff_t op) {
		for(std::size_t i = 0 ; i < NumEntradas ; ++i) {
			this->in(i)=arg1.in(i)-arg2.in(i);
		}
		return *this;
	}


	CBooleanCube operator - (const CBooleanCube & arg) const {
		CBooleanCube ret(*this,arg,diff_t::op);
		return ret;
	}

	const CBooleanCube & operator -= (const CBooleanCube & arg) {
		*this &= !arg;
		return *this;
	}

	inline std::size_t distin(const CBooleanCube & arg) const {
		if ((this->is_empty())^(arg.is_empty())) {
			return NumEntradas;
		}
		else if (!((this->is_empty())or((arg.is_empty())))) {
			std::size_t distancia = 0;
			for( std::size_t i=0 ; i < NumEntradas ; ++i ){
				if ((this->read4(i)&&arg.read4(i))==e4v)
					++distancia;
			}
			return distancia;
		}
		return 0;
	}

	inline std::size_t distout(const CBooleanCube & arg) const {
		return 0;
	}

	inline std::size_t dist(const CBooleanCube & arg) const {
		return this->distin(arg);
	}

	// CONSENSUS = operator*
	CBooleanCube operator*(const CBooleanCube & arg) const {
		CBooleanCube ret(*this);
		const std::size_t d_i =this->distin(arg);
		if (d_i!=1) {
		
			ret&=arg;
		}
		else {
			for( std::size_t i = 0 ; i < NumEntradas ; ++i ) {
				const bool_l4v intersect = ((this->read4(i))&&(arg.read4(i)));
				if (intersect!=e4v)
					ret.write(i,intersect);
				else
					ret.write(i,x4v);
			}
		}
		return ret;
	}

	// m_CONSENSUS = operator *=
	const CBooleanCube & operator*=(const CBooleanCube & arg) {

		const std::size_t d_i =this->distin(arg);
		if (d_i!=1) {
			(*this)&=arg;
		}
		else {
			for( std::size_t i = 0 ; i < NumEntradas ; ++i ) {
				const bool_l4v intersect = ((this->read4(i))&&(arg.read4(i)));
				if (intersect!=e4v)
					this->write(i,intersect);
				else
					this->write(i,x4v);
			}
		}
		return *this;
	}

	CBooleanCube cofactor(const CBooleanCube & p) const {
		const CBooleanCube & I(*this,p,cofactor_t::op);
		return I;
	}

	const CBooleanCube & m_cofactor(const CBooleanCube & p) {
		const CBooleanCube & I(*this,p,cofactor_t::op);
		(*this) = I;
		return *this;
	}

	CBooleanCube cofactor(std::size_t j,bool posneg) const {
		const CBooleanCube & c = (*this);
		CBooleanCube I(c,j,posneg,cofactor_t::op);
		return I;
	}

	const CBooleanCube & m_cofactor(std::size_t j,bool posneg) {
		*this = this->cofactor(j,posneg);
		return *this;
	}

	void write(std::size_t arg,bool_l4v val) {
		in(arg) = val;
	}

	bool_l4v read4(std::size_t arg) const {
		return in(arg);
	}

	template<const std::size_t NE>	
	friend std::ostream & operator << (std::ostream & out,const CBooleanCube<NE,0> & arg) {
		out << "<" << arg.key() << "," << "[";
		for( uint i = 0 ; i < NE ; ++i ) {
			const bool_l4v value = arg.in(i);
			const char salida = char(value);
			out << salida;
		}
		out << "]>";
		return out;
	}

};


#endif // CBOOLEANCUBE_HPP
