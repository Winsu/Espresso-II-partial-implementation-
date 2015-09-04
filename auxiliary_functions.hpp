#ifndef AUXILIARY_FUNCTIONS__HPP
#define AUXILIARY_FUNCTIONS__HPP

#include "typedefs.hpp"

using ullint = unsigned long long int;

template<const ullint e> constexpr ullint pow2(){return 2*pow2<e-1>();}
template<> constexpr ullint pow2<2>(){return 4;}
template<> constexpr ullint pow2<1>(){return 2;}
template<> constexpr ullint pow2<0>(){return 1;}

template<const ullint e> constexpr ullint pow3(){return 3*pow3<e-1>();}
template<> constexpr ullint pow3<2>(){return 9;}
template<> constexpr ullint pow3<1>(){return 3;}
template<> constexpr ullint pow3<0>(){return 1;}

char bool2char(bool value);

template<std::size_t n>
void fill_with_nulls(char* chptr);

bool es_booleano(char car);
bool es_true(char car);
bool es_false(char car);
bool es_dncare(char car);
bool es_separador(char car);
bool es_punto_y_coma(char car);
bool es_fin_de(char car);
bool es_numerico(char car);
bool es_cifra(char car);
bool es_significativo(char car);
bool es_blanco(char car);
bool no_es_numerico(char car);
bool es_valido(char car);
bool es_fin_de_cadena(char car);
bool es_fdl(char car);
bool es_fdc(char car);

template<typename T,uint N>
const std::array<T,N>& fill_array(std::array<T,N>& cstr, T c);

template<uint N>
const std::array<char,N>& fill_array(std::array<char,N>& carray,char c);

template<uint N>
char* fill_cstr(char* carray,char c);



char bool2char(bool value){
	if (value) return 1;
	else return 0;
}

template<std::size_t n>
void fill_with_nulls(char* chptr) {
	for(std::size_t i=0; i<n ; ++i) {
		chptr[i]=nullchar;
	}
}

bool es_booleano(char car){
	if (isalpha(car)||isdigit(car))
			return (car=='T' || car=='t' || car=='F' || car=='f' || car=='x' ||
					car=='X' || car=='H' || car=='h' || car=='L' || car=='l' ||
					car=='0' || car=='1' || car=='U' || car=='u' || car=='2' ||
					car=='-');
	else	return false;
}

bool es_true(char car){
	if (isalpha(car)||isdigit(car))
			return (car=='T' || car=='t' || car=='H' || car=='h' || car=='1');
	else	return false;
}

bool es_false(char car){
	if (isalpha(car)||isdigit(car))
			return (car=='F' || car=='f' || car=='L' || car=='l' || car=='0');
	else	return false;
}

bool es_dncare(char car){
	if (isalpha(car)||isdigit(car))
			return (car=='X' || car=='x' || car=='U' || car=='u' || car=='2' || car=='-');
	else	return false;
}

bool es_separador(char car){
	return (car=='>');
}

bool es_punto_y_coma(char car){
	return (car==';');
}

bool es_fin_de(char car){
	if (car=='\0') return true;
	else return false;
}

bool es_numerico(char car){
	return (isdigit(car));
}

bool es_cifra(char car){
	return (isdigit(car));
}

bool es_significativo(char car) {
	return (isdigit(car) || es_punto_y_coma(car));
}

bool es_blanco(char car) {
	return (isspace(car));
}

bool no_es_numerico(char car) {
	return (es_blanco(car) || es_punto_y_coma(car));
}

bool es_valido(char car) {
	return (isdigit(car) || es_blanco(car) || es_punto_y_coma(car));
}

bool es_fin_de_cadena(char car) {
	return (												\
				(es_fin_de(car))						||	\
				(car=='@')								||	\
				(car=='#')								||	\
				(car=='!')								||	\
				(	(car<=((char)10))	&&					\
					(!es_blanco(car))						\
				)											\
			);
}

bool es_fdl(char car) {
	return ( (car==';') || es_blanco(car) || (car=='\n') || (car=='\0'));
}

bool es_fdc(char car) {
	return ( (car=='\n') || (car=='\0') );
}

template<typename T,uint N>
const std::array<T,N>& fill_array(std::array<T,N>& cstr, T c) {
	for(unsigned i=0;i<(N-1);i++) cstr[i]=c;
	cstr[N-1]='\0';
	return cstr;
}

template<uint N>
const std::array<char,N>& fill_array(std::array<char,N>& carray,char c) {
	for(unsigned i=0;i<(N-1);i++) 
		carray[i]=c;
	carray[N-1]='\0';
	return carray;
}

template<uint N>
char* fill_cstr(char* carray,char c) {
	for(unsigned i=0;i<(N-1);i++) 
		carray[i]=c;
	carray[N-1]='\0';
	return carray;
}

#endif //AUXILIARY_FUNCTIONS__HPP
