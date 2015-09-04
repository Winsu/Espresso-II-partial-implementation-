#ifndef PARSERS_HPP
#define PARSERS_HPP

#include "typedefs_2.hpp"
#include "l2rv_t.hpp"
#include "boolean_l3v.hpp"
#include "boolean_l4v.hpp"

template<const std::size_t NS>
using B4Term_t = std::array<bool_l4v,NS>;
template<const std::size_t NS>
using IB4Term_t = typename B4Term_t<NS>::iterator;
template<const std::size_t NS>
using c_IB4Term_t = typename B4Term_t<NS>::const_iterator;

template<const std::size_t NE , const std::size_t NS> class CBooleanCube;

template<const size_t NE , const size_t NS>
class parser_linea {

typedef B4Term_t<NE>				B4Term;
typedef IB4Term_t<NE>				IB4Term;
typedef c_IB4Term_t<NE>				c_IB4Term;
typedef B2Term_t<NS>				B2Term;
typedef IB2Term_t<NS>				IB2Term;
typedef c_IB2Term_t<NS>				c_IB2Term;

friend class CBooleanCube<NE,NS>;
	enum class est_l {ERROR_l=false,BIEN_l=true};
	enum class tipo_cubo {DC_set,ON_set,OFF_set};
	est_l					Est;
	tipo_cubo				cual_set;
	B4Term_t<NE>			in;
	B2Term_t<NS>			out;

void clear_in() {
	for(size_t i=0 ; i < NE ; ++i) {
		in[i]=e4v;
	}
	return;
}

void clear_out() {
	for(size_t i=0 ; i < NS ; ++i) {
		in[i]=false;
	}
	return;
}

void clear() {
	clear_in();
	clear_out();
}

parser_linea():
	Est(est_l::ERROR_l)
{}

parser_linea(const parser_linea & arg):
	Est(arg.Est),in(arg.in),out(arg.out)
{}

parser_linea(const B4Term & argin,const B2Term & argout):
	Est(est_l::BIEN_l),in(argin),out(argout)
{}

parser_linea(	const std::string & linea ){
	std::string::const_iterator it = linea.begin();
	const std::string::const_iterator itend = linea.end();
	int necount = 0;
	int nscount = 0;
	std::string cadena_entr;
	std::string cadena_sal;
	enum class est_l {	INICIO,cubo_entr,esp_blanco_1,
						esp_blanco_2,cubo_sal,esp_blanco_3,
						esp_blanco_4,BIEN,ERROR};
	est_l ESTADO_l = est_l::INICIO;
	while((it!=itend)	and	(ESTADO_l!=est_l::ERROR))	{
		switch (ESTADO_l) {
			case est_l::INICIO:
				if (es_blanco(*it)) {}
				else if (es_booleano(*it)) {
					ESTADO_l = est_l::cubo_entr;
					cadena_entr.push_back(*it);
					++necount;
				}
				else {
					ESTADO_l = est_l::ERROR;
					cadena_entr.clear();
					cadena_sal.clear();}
				break;
			case est_l::cubo_entr:
				if (es_blanco(*it)) {
					ESTADO_l = est_l::esp_blanco_1;
				}
				else if (es_booleano(*it)) {
					cadena_entr.push_back(*it);
					++necount;
				}
				else if (es_separador(*it)) {
					ESTADO_l = est_l::esp_blanco_2;
				}
				else {
					ESTADO_l = est_l::ERROR;
					cadena_entr.clear();
					cadena_sal.clear();
				}
				break;
			case est_l::esp_blanco_1:
				if (es_blanco(*it)) {}
				else if (es_separador(*it)) {
					ESTADO_l = est_l::esp_blanco_2;
				}
				else {
					ESTADO_l = est_l::ERROR;
					cadena_entr.clear();
					cadena_sal.clear();
				}
				break;
			case est_l::esp_blanco_2:
				if (es_blanco(*it)) {}
				else if (es_booleano(*it)) {
					ESTADO_l = est_l::cubo_sal;
					cadena_sal.push_back(*it);
					++nscount;
				}
				else {
					ESTADO_l = est_l::ERROR;
					cadena_sal.clear();
					cadena_entr.clear();
				}
				break;
			case est_l::cubo_sal:
				if (es_blanco(*it)) {
					ESTADO_l = est_l::esp_blanco_3;
				}
				else if (es_booleano(*it)) {
					cadena_sal.push_back(*it);
					++nscount;
				}
				else if (es_punto_y_coma(*it)) {
					ESTADO_l = est_l::esp_blanco_4;
				}
				else if (es_fdl(*it)) {
					ESTADO_l = est_l::BIEN;
				}
				else {
					ESTADO_l = est_l::ERROR;
					cadena_sal.clear();
					cadena_entr.clear();
				}
				break;
			case est_l::esp_blanco_3:
				if (es_blanco(*it)) {}
				else if (es_punto_y_coma(*it)) {
					ESTADO_l = est_l::esp_blanco_4;
				}
				else {
					ESTADO_l = est_l::ERROR;
					cadena_entr.clear();
					cadena_sal.clear();
				}
				break;
			case est_l::esp_blanco_4:
				if (es_blanco(*it)) {}
				else if (es_fdl(*it)) {
					ESTADO_l = est_l::BIEN;
				}
				else {
					cadena_entr.clear();
					cadena_sal.clear();
				}
				break;
			case est_l::BIEN:
					break;
			case est_l::ERROR:
					break;
		}
		++it;
	}
	if	((nscount==NS)and(necount==NE)and(ESTADO_l!=est_l::ERROR)){

			in	=	parser_linea::string2b4term(cadena_entr);
			out	=	parser_linea::string2b2term(cadena_sal);
			Est = parser_linea::est_l::BIEN_l;
		}
	else {
		clear();
		Est = parser_linea::est_l::ERROR_l;
	}
}

const parser_linea & operator = (const parser_linea & arg) {
	parser_linea & cthis = (*this);
	cthis.in = arg.in;
	cthis.out = arg.out;
	cthis.Est = arg.Est;
	return cthis;
}

const parser_linea & operator = (const std::string & linea) {
	parser_linea & cthis = (*this);
	parser_linea cpy(linea);
	Est = cpy.Est;
	in  = cpy.in;
	out = cpy.out;
	return cthis;
}


std::string bterm2string(B4Term cont) {
	std::string ret;		
	ret.clear();	
	IB4Term			it		=	cont.begin();
	c_IB4Term		itend	=	cont.end();
	
	for( ; it < itend ; it++ )
		if ((*it)==T4v)
			ret += 'T';
		else if ((*it)==F4v)
			ret += 'F';
		else
			ret += 'x';
	
	return ret;
}

std::string bterm2string(B2Term cont) {
	std::string ret;	
	ret.clear();	
	IB2Term			it		=	cont.begin();
	c_IB2Term		itend	=	cont.end();
	
	for( ; it < itend ; it++ )
		if ((*it)==true)
			ret += 'T';
		else if ((*it)==false)
			ret += 'F';
		else
			ret += 'x';
	
	return ret;
}


B4Term string2b4term(std::string arg) {
	const int n = arg.size();
	B4Term ret;
	for(int I=0; I<n; ++I)
		if ((arg[I] == 'f')||(arg[I] == 'F')||(arg[I] == '0'))
			ret[I]=F4v ;
		else if ((arg[I] == 't')||(arg[I] == 'T')||(arg[I] == '1'))
			ret[I]=T4v ;
		else
			ret[I]=x4v ;
	return ret;
}

B2Term string2b2term(std::string arg,tipo_set ARG) {
	const int n = arg.size();
	B2Term ret;
	for(int I=0; I<n; ++I) {
		if (ARG==tipo_set::ON_set) {
			if ((arg[I] == 'f')||(arg[I] == 'F')||(arg[I] == '0'))
				ret[I]=false;
			else if ((arg[I] == 't')||(arg[I] == 'T')||(arg[I] == '1'))
				ret[I]=true;
			else if ((arg[I] == 'x')||(arg[I] == 'X')||(arg[I] == '2'))
				ret[I]=false;
		}
		else if (ARG==tipo_set::OFF_set) {
			if ((arg[I] == 'f')||(arg[I] == 'F')||(arg[I] == '0'))
				ret[I]=true;
			else if ((arg[I] == 't')||(arg[I] == 'T')||(arg[I] == '1'))
				ret[I]=false;
			else if ((arg[I] == 'x')||(arg[I] == 'X')||(arg[I] == '2'))
				ret[I]=false;
		}
		else {
			if ((arg[I] == 'f')||(arg[I] == 'F')||(arg[I] == '0'))
				ret[I]=false;
			else if ((arg[I] == 't')||(arg[I] == 'T')||(arg[I] == '1'))
				ret[I]=false;
			else if ((arg[I] == 'x')||(arg[I] == 'X')||(arg[I] == '2'))
				ret[I]=true;
		}
	}
	return ret;
}

};



#endif // PARSERS_HPP
