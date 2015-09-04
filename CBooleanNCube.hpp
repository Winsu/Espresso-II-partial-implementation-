#ifndef CBOOLEANNCUBE_HPP
#define CBOOLEANNCUBE_HPP

#include "typedefs.hpp"
#include <vector>
#include <iterator>
#include "CBooleanCube.hpp"
#include "parsers.hpp"

enum class string_value_type {content,path_to_content};

template<std::size_t NE,std::size_t NS>
using booleanNCube = std::pair<ulint,CBooleanCube<NE,NS>>;

template<const std::size_t NE,const std::size_t NS>
class CBooleanNCube : protected template booleanNCube {

typedef B4Term_t<NE>				B4Term;
typedef IB4Term_t<NE>				IB4Term;
typedef c_IB4Term_t<NE>				c_IB4Term;
typedef B2Term_t<NS>				B2Term;
typedef IB2Term_t<NS>				IB2Term;
typedef c_IB2Term_t<NS>				c_IB2Term;

friend class parser_linea<NE,NS>;

public:

	inline bool is_empty() const {
		return (booleanNCube::first).is_empty();
	}

	CBooleanNCube() {
		second = 0ul;
		for(std::size_t i=0; i < NE ; ++i)
			first.cube_in[i]=e4v;
		for(std::size_t i=0; i < NS ; ++i)
			first.cube_out[i]=false;
	}

	CBooleanNCube(universe op,ulint nrow=0ul) {
		second = nrow;
		for(std::size_t i=0; i < NE ; ++i)
			first.cube_in[i]=X4v;
		for(std::size_t i=0; i < NS ; ++i)
			first.cube_out[i]=true;
	}

	CBooleanNCube(std::size_t N,universe_1_de_m op,ulint nrow=0ul) {
		second = nrow;
		for(std::size_t i=0; i < NE ; ++i)
			first.cube_in[i]=X4v;
		for(std::size_t i=0; i < NS ; ++i)
			first.cube_out[i]=false;
		first.cube_out[N]=true;
	}

	CBooleanNCube(std::size_t N,positive_half_space_1_de_n op,ulint nrow = 0ul) {
		second = nrow;
		for(std::size_t i=0; i < NE ; ++i)
			first.cube_in[i]=X4v;
		for(std::size_t i=0; i < NS ; ++i)
			first.cube_out[i]=true;
		first.cube_in[N]=T4v;
	}

	CBooleanNCube(std::size_t N,negative_half_space_1_de_n op,ulint nrow = 0ul) {
		second = nrow;
		for(std::size_t i=0; i < NE ; ++i)
			first.cube_in[i]=X4v;
		for(std::size_t i=0; i < NS ; ++i)
			first.cube_out[i]=true;
		first.cube_in[N]=F4v;
	}

	CBooleanNCube(const CBooleanCube & arg,ulint nrow = 0ul):
		first.cube_in(arg.cube_in),first.cube_out(arg.cube_out),second(nrow)
	{}
	
	CBooleanNCube(const CBooleanNCube & arg):
		first.cube_in(arg.first.cube_in),first.first.cube_out(arg.cube_out),second(arg.second)
	{}

	CBooleanNCube(const B4Term & argin,const B2Term & argout,ulint nrow = 0ul):
		first.cube_in(argin),first.cube_out(argout),second(nrow)
	{}

	CBooleanNCube(const std::string & linea,string_value_type arg=string_value_type::content,ulint nrow = 0ul){
		second = nrow;
		const auto N = 10*(NE+NS+1);
		const char* cstr_cubo;
		char c_nlinea[N];
		fill_with_nulls<N>(c_nlinea);
		std::string nlinea;
		if (arg==string_value_type::content) {
			nlinea = linea;
		}
		else {
			cstr_cubo=linea.c_str();
			std::ifstream	cubo(cstr_cubo);
				cubo.getline(c_nlinea,N,'\n');
			cubo.close();
			nlinea = c_nlinea;
		}
		parser_linea<NE,NS> cube(nlinea);
		first.cube_in = cube.in;
		first.cube_out = cube.out;
	}

	const CBooleanNCube & operator = (const CBooleanNCube & arg) {
		second 			= arg.second;
		first.cube_in 	= arg.first.cube_in;
		first.cube_out 	= arg.first.cube_out;
		return (*this);
	}

	const CBooleanCube & operator = (const std::string & linea) {
		second = 0ul;
		parser_linea<NE,NS> cube(linea);
		first.cube_in = cube.in;
		first.cube_out = cube.out;
		return (*this);
	}

	CBooleanNCube operator &&(const CBooleanNCube & arg) const {
		CBooleanNCube ret(*this);
		ret.second = 0ul;
		for(std::size_t I=0 ; I < NE ; ++I)
			ret.first.write(I,this->read4(I) && arg.first.read4(I));
		for(std::size_t I=0 ; I < NS ; ++I)
			ret.first.write(I,this->read2(I) && arg.first.read2(I));
		return ret;
	}

	CBooleanNCube operator ||(const CBooleanNCube & arg) const {
		CBooleanNCube ret(*this);
		ret.second = 0ul;
		for(std::size_t I=0 ; I < NE ; ++I)
			ret.first.write(I,this->first.read4(I) || arg.first.read4(I));
		for(std::size_t I=0 ; I < NS ; ++I)
			ret.first.write(I,this->first.read2(I) || arg.first.read2(I));
		return ret;
	}

	CBooleanNCube operator ^(const CBooleanNCube & arg) const {
		CBooleanNCube ret(*this);
		ret.second = 0ul;
		for(std::size_t I=0 ; I < NE ; ++I)
			ret.first.write(I,this->first.read4(I) ^ arg.first.read4(I));
		for(std::size_t I=0 ; I < NS ; ++I)
			ret.first.write(I,this->first.read2(I) ^ arg.first.read2(I));
		return ret;
	}
	
	
	CBooleanNCube operator !() const {
		CBooleanNCube ret(*this);
		ret.second = 0ul;
		for(std::size_t I=0 ; I < NE ; ++I)
			ret.first.write(I,!this->first.read4(I));
		for(std::size_t I=0 ; I < NS ; ++I)
			ret.first.write(I,!this->first.read2(I));
		return ret;
	}

	
	CBooleanNCube consnot(usint j) const {
		CBooleanNCube ret(*this);
		ret.second = 0ul;
		ret.first.write(j,!this->first.read4(j));
		return ret;
	}

	const CBooleanNCube & m_consnot(usint j) {
		this->first.write(j,!(this->first.read4(j)));
		return (*this);
	}

	const CBooleanNCube & operator &=(const CBooleanNCube & arg) {
		second = 0ul;
		for(std::size_t I=0 ; I < NE ; ++I)
			this->first.write(I,this->first.read4(I) && arg.first.read4(I));
		for(std::size_t I=0 ; I < NS ; ++I)
			this->first.write(I,this->first.read2(I) && arg.first.read2(I));
		return *this;
	}
	
	
	const CBooleanNCube & operator |=(const CBooleanNCube & arg){
	for(std::size_t I=0 ; I < NE ; ++I)
		this->first.write(I,this->first.read4(I) || arg.first.read4(I));
	for(std::size_t I=0 ; I < NS ; ++I)
		this->first.write(I,this->first.read2(I) || arg.first.read2(I));
	return *this;
	}

	const CBooleanNCube & operator ^=(const CBooleanNCube & arg){
		for(std::size_t I=0 ; I < NE ; ++I)
			this->first.write(I,this->first.read4(I) ^ arg.first.read4(I));
		for(std::size_t I=0 ; I < NS ; ++I)
			this->first.write(I,this->first.read2(I) ^ arg.first.read2(I));
		return *this;
	}
	
	
	const CBooleanNCube & operator~(){
		for(std::size_t I=0 ; I < NE ; ++I)
			this->first.write(I,!this->first.read4(I));
		for(std::size_t I=0 ; I < NS ; ++I)
			this->first.write(I,!this->first.read2(I));
		return *this;
	}

	bool operator ==(const CBooleanCube & arg) const {
		bool igual_in  = true;
		bool igual_out = true;
		if((this->first.is_empty())&&(arg.is_empty())) return true;
		else if((this->first.is_empty())^(arg.is_empty())) return false;
		for(std::size_t i=0;i < NE; ++i) {
			if (this->first.read4(i)!=arg.read4((i))){
				igual_in = false;
				break;
			}
		}
		if (igual_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if (this->first.read2(i)!=arg.read2((i))){
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

	bool operator ==(const CBooleanNCube & arg) const {
		bool igual_in  = true;
		bool igual_out = true;
		bool igual_n   = (this->second == arg.second);
		if (!igual_n) then return false;
		if((this->first.is_empty())&&(arg.first.is_empty())) return true;
		else if((this->first.is_empty())^(arg.first.is_empty())) return false;
		for(std::size_t i=0;i < NE; ++i) {
			if (this->first.read4(i)!=arg.first.read4((i))){
				igual_in = false;
				break;
			}
		}
		if (igual_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if (this->first.read2(i)!=arg.first.read2((i))){
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
	
	static
	BinRow<NE+NS> row_of_BB(const CBooleanNCube & c,const CBooleanNCube & Ri) {
		BinRow<NE+NS> result;
		result.second = 0ul;
		for(uint j =0 ; j < NE+NS-1 ; ++j) {
			if (j<NE-1) {
				if (((c.first.read4(j)==T4v)and(Ri.first.read4(j)==F4v))
					or
					((c.first.read4(j)==F4v)and(Ri.first.read4(j)==T4v)))
					result[j]=T4v;
				else
					result[j]=F4v;
			}
			else {
				if ((!c.first.read2(j))and(Ri.first.read2(j)))
					result[j]=T4v;
				else
					result[j]=F4v;
			}
		}
		return result;
	} 


	static
	BinRow<NE+NS> row_of_CC(const CBooleanNCube & c,const CBooleanNCube & Fi) {
		BinRow<NE+NS> result;
		result.second = 0ul;
		for(uint j =0 ; j < NE+NS-1 ; ++j) {
			if (j<NE-1) {
				if (((c.first.read4(j)==T4v)and(Fi.first.read4(j)!=F4v))
					or
					((c.first.read4(j)==F4v)and(Fi.first.read4(j)!=T4v)))
					result[j]=T4v;
				else
					result[j]=F4v;
			}
			else {
				if ((!c.first.read2(j))and(Fi.first.read2(j)))
					result[j]=T4v;
				else
					result[j]=F4v;
			}
		}
		return result;
	}

	

	bool operator !=(const CBooleanCube & arg) const {
		return (!(*this->first.operator==(arg)));
	}
	
	bool operator !=(const CBooleanNCube & arg) const {
		return (!((*this)==arg));
	}
	
	bool operator >=(const CBooleanCube & arg) const {
		bool contiene_in  = true;
		bool contiene_out = true;

		if(arg.first.is_empty())
			return true;
		else if((this->first.is_empty())&&(!(arg.is_empty())))
			return false;

		for(std::size_t i=0;i < NE; ++i) {
			if (this->first.read4(i) < arg.read4(i)){
				contiene_in = false;
				break;
			}
		}
		if (contiene_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if (!(this->first.read2(i)) and (arg.read2(i))){
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

	bool operator >=(const CBooleanNCube & arg) const {
		bool contiene_in  = true;
		bool contiene_out = true;

		if(arg.first.is_empty())
			return true;
		else if((this->first.is_empty())&&(!(arg.first.is_empty())))
			return false;

		for(std::size_t i=0;i < NE; ++i) {
			if (this->first.read4(i) < arg.first.read4(i)){
				contiene_in = false;
				break;
			}
		}
		if (contiene_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if (!(this->first.read2(i)) and (arg.first.read2(i))){
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
		bool contiene_in  = true;
		bool contiene_out = true;

		if(this->first.is_empty()) return true;
		else if(!(this->first.is_empty())&&(arg.is_empty())) return false;

		for(std::size_t i=0;i < NE; ++i) {
			if (this->first.read4(i) > arg.read4(i)){
				contiene_in = false;
				break;
			}
		}
		if (contiene_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if ((this->first.read2(i)) and !(arg.read2(i))){
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

	bool operator <= (const CBooleanNCube & arg) const {
		bool contiene_in  = true;
		bool contiene_out = true;

		if(this->first.is_empty()) return true;
		else if(!(this->first.is_empty())&&(arg.first.is_empty())) return false;

		for(std::size_t i=0;i < NE; ++i) {
			if (this->first.read4(i) > arg.first.read4(i)){
				contiene_in = false;
				break;
			}
		}
		if (contiene_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if ((this->first.read2(i)) and !(arg.first.read2(i))){
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

	bool operator >(const CBooleanCube & arg) const {
		bool contiene_in			= false;
		bool contiene_in_estricto	= false;
		bool contiene_out_estricto	= false;

		if(this->first.is_empty()) return false;
		else if(!(this->first.is_empty())&&(arg.is_empty())) return true;

		for(std::size_t i=0;i < NE; ++i) {
			if (this->first.read4(i) == arg.read4(i)) {
				contiene_in = true;
			}
			else if (this->first.read4(i) > arg.read4(i)) {
				contiene_in = true;
				contiene_in_estricto = true;
			}
			else if (this->first.read4(i) < arg.read4(i)){
				contiene_in = false;
				contiene_in_estricto = false;
				break;
			}
		}
		if (contiene_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if ((this->first.read2(i)) && (!(arg.read2(i)))) {
					contiene_out_estricto = true;
				}
				else if ((!(this->first.read2(i))) && (arg.read2(i))) {
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

	bool operator >(const CBooleanNCube & arg) const {
		bool contiene_in			= false;
		bool contiene_in_estricto	= false;
		bool contiene_out_estricto	= false;

		if(this->first.is_empty()) return false;
		else if(!(this->first.is_empty())&&(arg.first.is_empty())) return true;

		for(std::size_t i=0;i < NE; ++i) {
			if (this->first.read4(i) == arg.first.read4(i)) {
				contiene_in = true;
			}
			else if (this->first.read4(i) > arg.first.read4(i)) {
				contiene_in = true;
				contiene_in_estricto = true;
			}
			else if (this->first.read4(i) < arg.first.read4(i)){
				contiene_in = false;
				contiene_in_estricto = false;
				break;
			}
		}
		if (contiene_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if ((this->first.read2(i)) && (!(arg.first.read2(i)))) {
					contiene_out_estricto = true;
				}
				else if ((!(this->first.read2(i))) && (arg.first.read2(i))) {
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
			if (this->first.read4(i) == arg.read4(i)) {
				contenido_in = true;
			}
			else if (this->first.read4(i) < arg.read4(i)) {
				contenido_in = true;
				contenido_in_estricto = true;
			}
			else if (this->first.read4(i) > arg.read4(i)){
				contenido_in = false;
				contenido_in_estricto = false;
				break;
			}
		}
		if (contenido_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if ((!(this->first.read2(i))) && (arg.read2(i))) {
					contenido_out_estricto = true;
				}
				else if ((this->first.read2(i)) && (!(arg.read2(i)))) {
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

	bool operator <(const CBooleanNCube & arg) const {
		bool contenido_in			= false;
		bool contenido_in_estricto	= false;
		bool contenido_out_estricto	= false;
		for(std::size_t i=0;i < NE; ++i) {
			if (this->first.read4(i) == arg.first.read4(i)) {
				contenido_in = true;
			}
			else if (this->first.read4(i) < arg.first.read4(i)) {
				contenido_in = true;
				contenido_in_estricto = true;
			}
			else if (this->first.read4(i) > arg.first.read4(i)){
				contenido_in = false;
				contenido_in_estricto = false;
				break;
			}
		}
		if (contenido_in) {
			for(std::size_t i=0; i < NS; ++i) {
				if ((!(this->first.read2(i))) && (arg.first.read2(i))) {
					contenido_out_estricto = true;
				}
				else if ((this->first.read2(i)) && (!(arg.first.read2(i)))) {
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
		
	CBooleanNCube(const CBooleanNCube & arg1,const CBooleanNCube & arg2,or_t op,ulint nrow=0ul) {
		second = nrow;
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->first.cube_in[i]=arg1.first.cube_in[i] || arg2.first.cube_in[i];
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->first.cube_out[i]=arg1.first.cube_out[i] || arg2.first.cube_out[i];
		}
	}

	CBooleanNCube(const CBooleanNCube & arg1,const CBooleanNCube & arg2,and_t op,ulint nrow = 0ul) {
		second = nrow;
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->first.write(i,arg1.first.read4(i) && arg2.first.read4(i));
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->first.write(i,arg1.first.read2(i) && arg2.first.read2(i));
		}
	}

	CBooleanNCube(const CBooleanNCube & arg1,const CBooleanNCube & arg2,diff_t op,ulint nrow = 0ul) {
		second = nrow;
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->first.write(i,arg1.first.read4(i) - arg2.first.read4(i));
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->first.write(i,(arg1.first.read2(i)) && (!(arg2.first.read2(i))));
		}
	}

	CBooleanNCube(	const CBooleanNCube & arg1,
					const CBooleanNCube & arg2,
					xor_t op,ulint nrow = 0ul) {
		second = nrow;
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->first.cube_in[i]=arg1.first.cube_in[i] ^ arg2.first.cube_in[i];
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->first.cube_out[i]=arg1.first.cube_out[i] ^ arg2.first.cube_out[i];
		}
	}

	
	CBooleanNCube(const CBooleanNCube & arg,not_t op,ulint nrow = 0ul){
		second = nrow;
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->first.write(i,!(arg.first.read4(i)));
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->first.write(i,!(arg.first.read2(i)));
		}
	}

	const CBooleanNCube & assign(	const CBooleanNCube & arg1,
									const CBooleanNCube & arg2,
									or_t op,ulint nrow = 0ul) {
		second = nrow;
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->first.cube_in[i]=arg1.first.cube_in[i] || arg2.first.cube_in[i];
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->first.cube_out[i]=arg1.first.cube_out[i] || arg2.first.cube_out[i];
		}
		return *this;
	}

	const CBooleanNCube & assign(	const CBooleanNCube & arg1,
									const CBooleanNCube & arg2,
									and_t op,ulint nrow = 0ul) {
		second = nrow;
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->first.cube_in[i]=arg1.first.cube_in[i] && arg2.first.cube_in[i];
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->first.cube_out[i]=arg1.first.cube_out[i] && arg2.first.cube_out[i];
		}
		return *this;
	}

	const CBooleanNCube & assign(	const CBooleanNCube & arg1,
									const CBooleanNCube & arg2,
									xor_t op,ulint nrow = 0ul) {
		second = nrow;
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->first.cube_in[i]=arg1.first.cube_in[i] ^ arg2.first.cube_in[i];
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->first.cube_out[i]=arg1.first.cube_out[i] ^ arg2.first.cube_out[i];
		}
		return *this;
	}

	const CBooleanNCube & assign(	const CBooleanNCube & arg1,
									const CBooleanNCube & arg2,
									diff_t op,ulint nrow = 0ul) {
		second = nrow;
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->first.cube_in[i]=arg1.first.cube_in[i]-arg2.first.cube_in[i];
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->first.cube_out[i]=(arg1.first.cube_out[i])&&(!(arg2.first.cube_out[i]));
		}
		return *this;
	}
	
	const CBooleanNCube & assign(const CBooleanNCube & arg,not_t op,ulint nrow = 0ul){
		second = nrow;
		for(std::size_t i = 0 ; i < NE ; ++i) {
			this->first.write(i,!(arg.first.read4(i)));
		}
		for(std::size_t i = 0 ; i < NS ; ++i) {
			this->first.write(i,!(arg.first.read2(i)));
		}
		return *this;
	}
	

	CBooleanNCube operator - (const CBooleanNCube & arg) const {
		second = 0ul;
		CBooleanNCube ret(*this,arg,diff_t::op);
		return ret;
	}

	const CBooleanCube & operator -= (const CBooleanNCube & arg) {
		*this &= !arg;
		return *this;
	}

	inline std::size_t distin(const CBooleanNCube & arg) const {
		if ((this->first.is_empty())^(arg.first.is_empty())) {
			return NE;
		}
		else if (!((this->first.is_empty())or((arg.first.is_empty())))) {
			std::size_t distancia = 0;
			for( std::size_t i=0 ; i < NE ; ++i ){
				if ((this->first.read4(i)&&arg.first.read4(i))==e4v) 
					++distancia;
			}
			return distancia;
		}
		return 0;
	}

	inline std::size_t distout(const CBooleanNCube & arg) const {
		if ((this->first.is_empty())^(arg.first.is_empty())) {
			return 1;
		}
		else if (!((this->first.is_empty())or((arg.first.is_empty())))) {
			for( std::size_t i=0 ; i < NS ; ++i ){
				if (this->first.read2(i)&&arg.first.read2(i)) {
					return 0;
				}
			}
			return 1;
		}
		return 0;
	}

	inline std::size_t dist(const CBooleanNCube & arg) const {
		if ((this->first.is_empty())^(arg.first.is_empty())) {
			return (NE+1);
		}
		else if (!((this->first.is_empty())or((arg.first.is_empty())))) {
			std::size_t distancia = 0;
			for( std::size_t i=0 ; i < NE ; ++i ){
				if ((this->first.read4(i)&&arg.first.read4(i))==e4v) 
					++distancia;
			}
			for( std::size_t i=0 ; i < NS ; ++i ){
				if (this->first.read2(i)&&arg.first.read2(i)) {
					return distancia;
				}
			}
			++distancia;
			return distancia;
		}
		return 0;
	}

	// CONSENSUS = operator*
	CBooleanNCube operator*(const CBooleanNCube & arg) const {
		CBooleanNCube ret(*this);
		ret.second = 0ul;
		(ret.first)*=(arg.first);
		return ret;
	}

	// m_CONSENSUS = operator *=
	const CBooleanNCube & operator*=(const CBooleanNCube & arg) {
		this->second = 0ul;
		(*this)*=(arg.first);
		return (*this);
	}

	CBooleanNCube cofactor(const CBooleanNCube & p,ulint nrow = 0ul) const {
		const CBooleanNCube & c = (*this);
		c.second = nrow;
		CBooleanNCube I(c,p,and_t::op);
		const bool es_vacio = I.is_empty();
		if (es_vacio) {
			return I;
		}
		else {
			for(std::size_t i=0 ; i < NE ; ++i)
				if ((p.first.read4(i)==F4v) or (p.first.read4(i)==T4v))
					I.first.write(i,X4v);
				else
					I.first.write(i,c.first.read4(i));
			for(std::size_t i=0 ; i < NS ; ++i)
				if (!(p.first.read2(i)))
					I.first.write(i,true);
				else
					I.first.write(i,c.first.read2(i));
		}
		return I;
	}

	const CBooleanNCube & m_cofactor(const CBooleanNCube & p,ulint nrow = 0ul) {
		CBooleanCube & c = (*this);
		c.second = nrow;
		const CBooleanCube & I(c,p,and_t::op);
		const bool es_vacio = I.first.is_empty();
		if (c.es_vacio) {
			c = I;
			return c;
		}
		else {
			for(std::size_t i=0 ; i < NE ; ++i) {
				if ((p.first.read4(i)==F4v) or (p.first.read4(i)==T4v)) {
					c.first.write(i,X4v);
				}
				else {
					c.first.write(i,c.first.read4(i));
				}
			}
			for(std::size_t i=0 ; i < NS ; ++i) {
				if (!(p.first.read2(i))) {
					c.first.write(i,true);
				}
				else {
					c.first.write(i,c.first.read2(i));
				}
			}
			return c;
		}
	}

	void write(std::size_t arg,bool_l4v val) {
		first.cube_in[arg] = val;
	}

	void write(std::size_t arg,bool val) {
		first.cube_out[arg] = val;
	}
	
	void write_key(std::size_t arg) {
		second = arg;
	}

	bool_l4v read4(std::size_t arg) const {
		return first.cube_in[arg];
	}

	bool read2(std::size_t arg) const {
		return first.cube_out[arg];
	}
	
	ulint read_k() const {
		return second;
	}

friend
std::ostream & operator << (std::ostream & out,const CBooleanNCube<NE,NS> & arg) {
	out << "<";
	out << arg.second << ":";
	out << "[";
	for( uint i = 0 ; i < NE ; ++i ) {
		const bool_l4v value(arg.first.read4(i));
		const char salida = char(value);
		out << salida;
	}
	for( uint i = 0 ; i < NS ; ++i ) {
		const bool value(arg.first.read2(i));
		const char salida = ((bool2char(value))+'3');
		out << salida;
	}
	out << "]>";
	return out;
}
};


#endif // CBOOLEANNCUBE_HPP
