#ifndef PARSERS_SO_HPP
#define PARSERS_SO_HPP

#include "boolean_l2rv.hpp"
#include "boolean_l4v.hpp"
#include "CBooleanCube.hpp"
#include "auxiliary_functions.hpp"
#include <cctype>
#include <cstdint>
#include <cstdlib>

template<std::size_t> class ff_t;

template<const std::size_t NE , const std::size_t NS> class CBooleanCube;

template<const size_t NE , const size_t NS>
class parser_linea_so {

typedef B4Term_t<NE>				B4Term;
typedef IB4Term_t<NE>				IB4Term;
typedef c_IB4Term_t<NE>				c_IB4Term;
typedef B2Term_t<NS>				B2Term;
using IB2Term =	typename B2Term::iterator;
using c_IB2Term =	typename B2Term::const_iterator;
friend class ff_t<NE>;
friend class CBooleanCube<NE,NS>;
	enum class est_l {ERROR_l=false,BIEN_l=true};
	est_l								Est;
	std::array<B4Term_t<NE>,NS>			inon;
	std::array<B4Term_t<NE>,NS>			inoff;
	std::array<B4Term_t<NE>,NS>			indc;

void clear_inon() {
	for(size_t i=0 ; i < NE ; ++i) {
		inon[i]=e4v;
	}
	return;
}

void clear_inoff() {
	for(size_t i=0 ; i < NE ; ++i) {
		inoff[i]=e4v;
	}
	return;
}
void clear_indc() {
	for(size_t i=0 ; i < NE ; ++i) {
		indc[i]=e4v;
	}
	return;
}

void clear() {
	clear_inon();
	clear_inoff();
	clear_indc();
}

parser_linea_so():
	Est(est_l::ERROR_l)
{}

parser_linea_so(const parser_linea_so & arg):
	Est(arg.Est),inon(arg.inon),inoff(arg.inoff),indc(arg.indc)
{}

parser_linea_so(const B4Term & arg1,const B4Term & arg2,const B4Term & arg3):
	Est(est_l::BIEN_l),inon(arg1),inoff(arg2),indc(arg3)
{}

parser_linea_so(	const std::string & linea ){
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
		this->string2b2term<cubeset_t::ON>(cadena_sal,cadena_entr);
		this->string2b2term<cubeset_t::OFF>(cadena_sal,cadena_entr);
		this->string2b2term<cubeset_t::DC>(cadena_sal,cadena_entr);
		Est = parser_linea_so::est_l::BIEN_l;
	}
	else {
		clear();
		Est = parser_linea_so::est_l::ERROR_l;
	}
}

const parser_linea_so & operator = (const parser_linea_so & arg) {
	parser_linea_so & cthis = (*this);
	cthis.inon = arg.inon;
	cthis.inoff = arg.inoff;
	cthis.indc = arg.indc;
	cthis.Est = arg.Est;
	return cthis;
}

const parser_linea_so & operator = (const std::string & linea) {
	parser_linea_so & cthis = (*this);
	parser_linea_so cpy(linea);
	Est = cpy.Est;
	cthis.inon  = cpy.inon;
	cthis.inoff = cpy.inoff;
	cthis.indc  = cpy.indc;
	return cthis;
}


std::string bterm2string(const B4Term& cont) {
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

B4Term string2b4term(const std::string & arg) {
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

template<const cubeset_t V>
void string2b2term(const std::string& argin,const std::string& argout) {
	const int n = argout.size();
	for(int I=0; I<n; ++I) {
		switch(V) {
			case cubeset_t::ON :
				if ((argout[I] == 't')||(argout[I] == 'T')||(argout[I] == '1')) {
					this->inon[I].push_back(string2b4term(argin));
				}
				break;
			case cubeset_t::OFF :
				if ((argout[I] == 'f')||(argout[I] == 'F')||(argout[I] == '0')) {
					this->inoff[I].push_back(string2b4term(argin));
				}
				break;
			case cubeset_t::DC :
				if ((argout[I] == 'x')||(argout[I] == 'X')||(argout[I] == '2')||(argout[I] == '-')) {
					this->indc[I].push_back(string2b4term(argin));
				}
		}
	}
	return;
}

};



#endif // PARSERS_SO_HPP
