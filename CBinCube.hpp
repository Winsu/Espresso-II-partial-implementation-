#ifndef CBINCUBE_HPP
#define CBINCUBE_HPP

#include "l2rv_t.hpp"
#include "CBooleanCube.hpp"

template<const std::size_t NE,const std::size_t NS>
class CBinCube : protected BinCube<NE,NS> {
public:
	using	B2rTerm		=	B2rTerm_t<NE,NS>;
	using	IB2rTerm	=	IB2rTerm_t<NE,NS>;
	using	c_IB2rTerm	=	c_IB2rTerm_t<NE,NS>;
private:
		
	inline B4Term & var() {
		return this->BinCube<NE,NS>::first;
	}
	inline const B4Term & var() const {
		return this->BinCube<NE,NS>::first;
	}
	inline bool_l4v & var(std::size_t I) {
		return this->BinCube<NE,NS>::first[I];
	}
	inline const bool_l4v & var(std::size_t I) const {
		return this->BinCube<NE,NS>::first[I];
	}
public:
	inline ulint key() const { return this->BinCube<NE,NS>::second;}
	
	inline ulint key(ulint k) { return (this->BinCube<NE,NS>::second=k);}
	
	inline bool is_empty() const {
		bool empty_in = false;
		for(size_t i=0 ; i < NE ; ++i) {
			if (var(i)==e2rv) {
				empty_in=true;
				break;
			}
		}
		if (empty_in) return true;
		bool empty_out = true;
		if (empty_in==false) {
			for(std::size_t i=NE ; i < NS+NE ; ++i) {
				if (var(i)!=e2rv) {
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
			if (var(i)==e2rv) {
				return true;
			}
		}
		return false;
	}
public:
	CBinCube() {
		this->key(0);
		for(std::size_t i=0; i < NE+NS ; ++i)
			this->var(i)=e4v;
	}

	CBinCube(const CBinCube & arg) : 
		this->BinCube<NE,NS>::first(arg.BinCube<NE,NS>::first),
		this->BinCube<NE,NS>::second(arg.BinCube<NE,NS>::second)
	{}
	
	CBinCube(const CBooleanCube & c,const CBooleanCube & Ri,BB_matrix_t op){
		for(uint j =0 ; j < NE+NS ; ++j) {
			if (j<NE) {
				if (((c.read4(j)==T4v)and(Ri.read4(j)==F4v))
					or
					((c.read4(j)==F4v)and(Ri.read4(j)==T4v))){
						this->write(j,T2rv);
					}
				else {
					this->write(j,F2rv);
				}
			}
			else {
				if ((!c.read2(j))and(Ri.read2(j))){
					this->write(j,T2rv);
				}
				else {
					this->write(j,F2rv);
				}
			}
		}
		this->key(Ri.key());
	}
	
	CBinCube(const CBooleanCube & c,const CBooleanCube & Fi,CC_matrix_t op) {
		for(uint j =0 ; j < NE+NS ; ++j) {
			if (j<NE) {
				if (((c.read4(j)==T4v)and(Fi.read4(j)!=F4v))
					or
					((c.read4(j)==F4v)and(Fi.read4(j)!=T4v))) {
						this->write(j,T2rv);
					}
				else {
					this->write(j,F2rv);
				}
			}
			else {
				if ((!c.read2(j))and(Fi.read2(j))) {
					this->write(j,T2rv);
				}
				else {
					this->write(j,F2rv);
				}
			}
		}
		this->key(Fi.key());
	}
	
	CBinCube(const CBooleanCube & arg,PERS_matrix_t op) {
		for(uint j =0 ; j < NE ; ++j) {
			if (arg.read4(j)==T4v or arg.read4(j)==F4v) {
				this->write(j,T2rv);
			}
			else {
				this->write(j,F2rv);
			}
		}
		for(uint j =NE ; j < NE+NS ; ++j) {
			this->write(j,arg.read2(j));
		}
		this->key(arg.key());
	}
	
	CBinCube & operator = (CBinCube & arg) {
		this->var() = arg.var();
		this->key(arg.key());
		return (*this);
	}
	
	const CBinCube & operator = (const CBinCube & arg) {
		this->var() = arg.var();
		this->key(arg.key());
		return (*this);
	}
	
	CBinCube & assign_BB(const CBooleanCube<NE,NS> & c,const CBooleanCube<NE,NS> & Ri) {
		for(uint j =0 ; j < NE+NS ; ++j) {
			if (j<NE) {
				if (((c.read4(j)==T4v)and(Ri.read4(j)==F4v))
					or
					((c.read4(j)==F4v)and(Ri.read4(j)==T4v)))
					this->write(j,T2rv);
				else
					this->write(j,F2rv);
			}
			else {
				if ((!c.read2(j))and(Ri.read2(j)))
					this->write(j,T2rv);
				else
					this->write(j,F2rv);
			}
		}
		this->key(Ri.key());
		return (*this);
	}
	
	const CBinCube & assign_BB(const CBooleanCube<NE,NS> & c,const CBooleanCube<NE,NS> & Ri) {
		for(uint j =0 ; j < NE+NS ; ++j) {
			if (j<NE) {
				if (((c.read4(j)==T4v)and(Ri.read4(j)==F4v))
					or
					((c.read4(j)==F4v)and(Ri.read4(j)==T4v)))
					this->write(j,T2rv);
				else
					this->write(j,F2rv);
			}
			else {
				if ((!c.read2(j))and(Ri.read2(j)))
					this->write(j,T2rv);
				else
					this->write(j,F2rv);
			}
		}
		this->key(Ri.key());
		return (*this);
	}
	
	CBinCube & assign_CC(const CBooleanCube<NE,NS> & c,const CBooleanCube<NE,NS> & Fi) {
		for(uint j =0 ; j < NE+NS ; ++j) {
			if (j<NE) {
				if (((c.read4(j)==T4v)and(Fi.read4(j)!=F4v))
					or
					((c.read4(j)==F4v)and(Fi.read4(j)!=T4v)))
					this->write(j,T2rv);
				else
					this->write(j,F2rv);
			}
			else {
				if ((!c.read2(j))and(Fi.read2(j)))
					this->write(j,T2rv);
				else
					this->write(j,F2rv);
			}
		}
		this->key(Fi.key());
		return (*this);
	}
	
	const CBinCube & assign_CC(const CBooleanCube<NE,NS> & c,const CBooleanCube<NE,NS> & Fi) {
		for(uint j =0 ; j < NE+NS ; ++j) {
			if (j<NE) {
				if (((c.read4(j)==T4v)and(Fi.read4(j)!=F4v))
					or
					((c.read4(j)==F4v)and(Fi.read4(j)!=T4v)))
					this->write(j,T2rv);
				else
					this->write(j,F2rv);
			}
			else {
				if ((!c.read2(j))and(Fi.read2(j)))
					this->write(j,T2rv);
				else
					this->write(j,F2rv);
			}
		}
		this->key(Fi.key());
		return (*this);
	}
	
	CBinCube & assign_PERS(CBooleanCube<NE,NS> & arg) {
		for(uint j =0 ; j < NE ; ++j) {
			if (arg.read4(j)==T4v or arg.read4(j)==F4v) {
				this->write(j,T2rv);
			}
			else {
				this->write(j,F2rv);
			}
		}
		for(uint j =NE ; j < NE+NS ; ++j) {
			this->write(j,arg.read2(j));
		}
		this->key(arg.key());
		return (*this);
	}
	
	const CBinCube & assign_PERS(const CBooleanCube<NE,NS> & arg) {
		for(uint j =0 ; j < NE ; ++j) {
			if (arg.read4(j)==T4v or arg.read4(j)==F4v) {
				this->write(j,T2rv);
			}
			else {
				this->write(j,F2rv);
			}
		}
		for(uint j =NE ; j < NE+NS ; ++j) {
			this->write(j,arg.read2(j));
		}
		this->key(arg.key());
		return (*this);
	}
	
	template<typename T>
	bool operator == (T) const = delete;
	template<typename T>
	bool operator == (T) = delete;
	template<typename T>
	bool operator !=(T) const = delete;
	template<typename T>
	bool operator !=(T) = delete;
	
	void write(std::size_t arg,bool_l2rv val) {
		var(arg) = val;
	}
	
	bool_l2rv read(std::size_t arg) const {
		return var(arg);
	}
	
};

std::ostream & operator << (std::ostream & out,const CBinCube<NE,NS> & arg) {
	out << "<";
	out << arg.key() << ",[";
	for( uint i = 0 ; i < NE ; ++i ) {
		const bool_l2rv value(arg.read(i));
		const char salida = char(value);
		out << salida;
	}
	for( uint i = NE ; i < NS+NE ; ++i ) {
		const bool value(arg.read(i));
		const char salida = ((bool2char(value))+'3');
		out << salida;
	}
	out << "]>";
	return out;
}

template<const usint NE,const usint NS>
using BFunct_t		= std::map<ulint,CBooleanCube<NE,NS>>;

template<const usint NE,const usint NS>
using IBFunct_t		= typename BFunct_t<NE,NS>::iterator;

template<const usint NE,const usint NS>
using c_IBFunct_t	= typename BFunct_t<NE,NS>::const_iterator;

#endif // CBINCUBE_HPP
