#ifndef ESTRUCTURASFUNCIONES_HPP
#define ESTRUCTURASFUNCIONES_HPP

#include "typedefs.hpp"
#include "boolean_l3v.hpp"
#include <cstdlib>
#include <sstream>
#include <set>

template<const std::size_t N>
using B3Term_t = std::array<bool_l3v,N>;

template<const std::size_t N>
using IB3Term_t = typename B3Term_t<N>::iterator;

template<const std::size_t N>
using c_IB3Term_t = typename B3Term_t<N>::const_iterator;

template<const std::size_t N>
using BFunct_Vt = std::vector<B3Term_t<N>>;

template<const std::size_t N>
using pBFunct_Vt = BFunct_Vt<N>*;
template<const std::size_t N>
using IBFunct_Vt = typename BFunct_Vt<N>::iterator;
template<const std::size_t N>
using c_IBFunct_Vt = typename BFunct_Vt<N>::const_iterator;

template<const std::size_t N>
using BFunct_t = std::list<B3Term_t<N>>;
template<const std::size_t N>
using pBFunct_t = BFunct_t<N>*;
template<const std::size_t N>
using IBFunct_t = typename std::list<B3Term_t<N>>::iterator;
template<const std::size_t N>
using c_IBFunct_t = typename std::list<B3Term_t<N>>::const_iterator;

template<const std::size_t N>
using BFunct_Ord_t = std::list<std::pair<BFunct_t<N>,unsigned int>>;
template<const std::size_t N>
using pBFunct_Ord_t = BFunct_Ord_t<N>*;
template<const std::size_t N>
using IBFunct_Ord_t = typename BFunct_Ord_t<N>::iterator;
template<const std::size_t N>
using c_IBFunct_Ord_t = typename BFunct_Ord_t<N>::const_iterator;

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

template<const std::size_t N>
class BoolFunct {
private:
	class res_parser_l1 {
		friend class BoolFunct;
		enum est_l1  {ERROR_l1=false,BIEN_l1=true};
		est_l1 Est;
		int    NE;
		int    NS;
		res_parser_l1();
		res_parser_l1(const res_parser_l1 & arg);
		res_parser_l1(const std::string & cad_in);
	};

	class res_parser_nl1 {
		friend class BoolFunct;
		enum est_nl1 {EI_nl1,EP1L_nl1,EPT_nl1,EP2L_nl1,DEF_nl1,ERROR_nl1,BIEN_nl1};
		est_nl1		Est;
		B3Term_t<N>		BoolPalIn;
		B3Term_t<N>		BoolPalOut;
		res_parser_nl1();
		res_parser_nl1(est_nl1 arg_est,int nin,int nout);
		res_parser_nl1(const res_parser_nl1 & arg);
		res_parser_nl1(const std::string & lin_in , const int ns ,
					   const int ne );
	};

	friend class res_parser_l1;
	friend class res_parser_nl1;
private:
	res_parser_nl1		estado_nl1	;// parser
	res_parser_l1		estado_l1	;// parser
	int					n_linea		;// parser
	unsigned int		f_k			;// parser
	bool				min_MAX		;// parser
	int					n_terms		;// number of terms
	BFunct_t<N>			bf			;//	The function itself
	BFunct_Ord_t<N>		bolsa[2]	;//	Quine-MCcluskey
	bool				ix			;
	unsigned char		ind_grupo	;// Quine-MCcluskey
	Impl_Primos_set_t<N>	impl_primos	;	// Last part Quine-MCcluskey 
	Impl_Primos_set_t<N>	impl_esenciales;// Last part Quine-MCcluskey 
public: 
	BoolFunct(bool arg = true); 
	BoolFunct(const BoolFunct & arg);
	BoolFunct(std::istream & sin,int f_k,bool vt); L
	bool EstadoFinalParser_BIEN() const;
	bool EstadoFinalParser_ERROR() const;
	const BFunct_t<N> & g_access_funct() const;
	inline int g_NE() const {return this->estado_l1.NE;}
	inline int g_NS() const {return this->estado_l1.NS;}
public: 
	void ordena_por_num_1s();
	void crea_tabla_por_adyacencias();
	bool comprobar_adyacencias(const B3Term_t<N> &,const B3Term_t<N> &) const;
	B3Term_t<N> operar_adyacencias(const B3Term_t<N> &,const B3Term_t<N> &) const;
	unsigned int cuenta_1s_de_la_palabra( IB3Term_t<N> &, c_IB3Term_t<N> & );
	void Generar__F_Num_Terms(Funct_BTerm_Nums_t<N> &,Conj_Z_t &,Bolsa_Palabras_t<N> &, Funct_Num_BTerms_t<N> &) const;
	void Iteracion__Deteccion_Primos_Esenciales_ETC(Funct_BTerm_Nums_t<N> &,Conj_Z_t &,Bolsa_Palabras_t<N> &,Funct_Num_BTerms_t<N> &) const;
	void Detectar_Terminos_Principales_y_Borrar_Los_Mas_pesados(Funct_BTerm_Nums_t<N> &,Conj_Z_t &,Bolsa_Palabras_t<N> &,Funct_Num_BTerms_t<N> &) const;
	void Limpiar__F_Term_Nums__de_terminos_vacios(Funct_BTerm_Nums_t<N> & f_term_nums);
	IBFunct_t<N> begin();
	c_IBFunct_t<N> end() const;
	void asignar_strings_a_listfunct(int n ,	int m ,
									 const std::string & cad_in		);

	
	static std::string bterm2string(B3Term_t<N> cont);

	
	static B3Term_t<N> string2bterm(std::string arg);
	void Genera_Tabla_De_Adyacencias_Por_Recurrencia();
	void Genera_Tabla_De_Implicantes_Primos() ;
	void saca_primos_esenciales();
	template<const std::size_t M>
	friend void saca_bolsa(BoolFunct<M> &,bool);
	template<const std::size_t M>
	friend void saca_lista(BoolFunct<M> &);
	template<const std::size_t M>
	friend void saca_conjunto(BoolFunct<M> &);

};
template<const std::size_t N>
BoolFunct<N>::res_parser_l1::res_parser_l1()
{
	NE  = 0;
	NS  = 1;
	Est = BIEN_l1;
}

template<const std::size_t N>
BoolFunct<N>::res_parser_l1::res_parser_l1(const BoolFunct::res_parser_l1 & arg)
{
	NE = arg.NE ;
	NS = arg.NS ;
	Est= arg.Est;
}
template<const std::size_t N>
void saca_mapa(Funct_BTerm_Nums_t<N> & arg);
template<const std::size_t N>
void saca_mapa_inverso( Funct_Num_BTerms_t<N> & arg );
template<const std::size_t N>
void saca_conjunto_de_palabras(Bolsa_Palabras_t<N> & arg);


template<const std::size_t N>
BoolFunct<N>::res_parser_l1::res_parser_l1(const std::string & cad_in) {
	std::stringstream sNE,sNS;
	std::stringstream * p_sNx = &sNE;
	sNE.clear();
	sNS.clear();
	bool es_primer_punto_y_coma = true;
	for( int I=0; (!es_fin_de(cad_in[I]))&&(Est!=ERROR_l1) ; I++ ) {
		if (es_valido(cad_in[I])) {
			if (es_numerico(cad_in[I])) {
				(*p_sNx) << cad_in[I];
			}
			else if (no_es_numerico(cad_in[I])) {
				if (es_punto_y_coma(cad_in[I])) {
					if (es_primer_punto_y_coma) {
						es_primer_punto_y_coma = false;
						p_sNx = &sNS;
					}
					else {
						sNE >> NE;
						sNS >> NS;
						Est = BIEN_l1;
						return;
					}
				}
			}
		}
		else {
			NE			= -1;
			NS			= -1;
			Est 		= ERROR_l1;
			return;
		}
	}
}
template<const std::size_t N>
BoolFunct<N>::res_parser_nl1::res_parser_nl1(	const std::string & lin_in ,
											const int ne ,
											const int ns	)
{
	std::string cad1out;
	std::string cad2out;
	cad1out.clear();
	cad2out.clear();
	int necount=0;
	int nscount=0;

	est_nl1		E 		= EI_nl1;
	int			index 	= 0;
	const int	maximo 	= lin_in.length();
	char 		X 		= lin_in[index];

	while ((index < maximo)&&(E != ERROR_nl1)) {
		switch(E) {
			case EI_nl1		:
				switch(X) {
					case 't'	:
					case 'T'	:
						E = EP1L_nl1;
						cad1out += 'T';
						necount++;
						break;
					case 'f'	:
					case 'F'	:
						E = EP1L_nl1;
						cad1out += 'F';
						necount++;
						break;
					case 'x'	:
					case 'X'	:
					case '-'	:
						E = EP1L_nl1;
						cad1out += 'x';
						necount++;
						break;
					case ' '	:
					case '\t'	:
						E = EI_nl1;
						break;
					case '>'	:
					case '\n'	:
					case '\0'	:
					case '\r'	:
					case '\f'	:
					default		:
						E = ERROR_nl1;
				}
				break;
			case EP1L_nl1     :
				switch(X) {
					case '>'	:
						E = EPT_nl1;
						break;
					case 't'	:
					case 'T'	:
						E = EP1L_nl1;
						cad1out += 'T';
						necount++;
						break;
					case 'f'	:
					case 'F'	:
						E = EP1L_nl1;
						cad1out += 'F';
						necount++;
						break;
					case 'X'	:
					case 'x'	:
					case '-'	:
						E = EP1L_nl1;
						cad1out += 'x';
						necount++;
						break;
					case ' '	:
					case '\t'	:
						E = EP1L_nl1;
						break;
					case '\n'	:
					case '\0'	:
					case '\r'	:
					case '\f'	:
					case ';'	:
					default		:
						E = ERROR_nl1;
				}
				break;
			case EPT_nl1	:
				switch(X) {
					case 't'	:
					case 'T'	:
						E = EP2L_nl1;
						cad2out += 'T';
						nscount++;
						break;
					case 'f'	:
					case 'F'	:
						E = EP2L_nl1;
						cad2out += 'F';
						nscount++;
						break;
					case 'X'	:
					case 'x'	:
					case '-'	:
						E = EP2L_nl1;
						cad2out += 'x';
						nscount++;
						break;
					case ' '	:
					case '\t'	:
						E = EPT_nl1;
						break;
					case '>'	:
					case '\n'	:
					case '\0'	:
					case '\r'	:
					case '\f'	:
					case ';'	:
					default		:
						E = ERROR_nl1;
				}
				break;
			case EP2L_nl1	:
				switch(X) {
					case '\n'	:
					case '\0'	:
					case '\r'	:
					case '\f'	:
					case ';'	:
						E = DEF_nl1;
						break;
					case 't'	:
					case 'T'	:
						E = EP2L_nl1;
						cad2out += 'T';
						nscount++;
						break;
					case 'f'	:
					case 'F'	:
						E = EP2L_nl1;
						cad2out += 'F';
						nscount++;
						break;
					case 'X'	:
					case 'x'	:
					case '-'	:
						E = EP2L_nl1;
						cad2out += 'x';
						nscount++;
						break;
					case ' '	:
					case '\t'	:
						E = EP2L_nl1;
						break;
					case '>'	:
					default		:
						E = ERROR_nl1;
				}
				break;
			case DEF_nl1	:
				E = DEF_nl1;
				break;
			case ERROR_nl1	:
			default			:
				E = ERROR_nl1;
		}
		index++;
		X = lin_in[index];
	}
	if (E==DEF_nl1){
		if ((nscount==ns) && (necount==ne)) E=BIEN_nl1 ;
		else 								E=ERROR_nl1;
	}
	if (E==BIEN_nl1) {
		BoolPalIn  = BoolFunct::string2bterm(cad1out);
		BoolPalOut = BoolFunct::string2bterm(cad2out);
	}
	Est = E;
	switch (Est)
	{
		case EI_nl1 	: {std::cout << "EI_nl1" << std::endl; break;}
		case EP1L_nl1 	: {std::cout << "EP1L_nl1" << std::endl; break;}
		case EPT_nl1 	: {std::cout << "EPT_nl1" << std::endl; break;}
		case EP2L_nl1 	: {std::cout << "EP2L_nl1" << std::endl; break;}
		case DEF_nl1 	: {std::cout << "DEF_nl1" << std::endl; break;}
		case ERROR_nl1 	: {std::cout << "ERROR_nl1" << std::endl; break;}
		case BIEN_nl1 	: {std::cout << "BIEN_nl1" << std::endl; break;}
	}
	std::cout << index << std::endl;
}


template<const std::size_t N>
BoolFunct<N>::res_parser_nl1::res_parser_nl1(est_nl1 arg_est,int nin,int nout):
	Est(arg_est)
{
	BoolPalIn.resize(nin);
	BoolPalOut.resize(nout);
}

template<const std::size_t N>
BoolFunct<N>::res_parser_nl1::res_parser_nl1():
	Est(EI_nl1)
{
	BoolPalIn.resize(1);
	BoolPalOut.resize(1);
}

template<const std::size_t N>
BoolFunct<N>::res_parser_nl1::res_parser_nl1(const res_parser_nl1 & arg):
	Est(arg.Est)
{
	BoolPalIn.resize(arg.BoolPalIn.size());
	BoolPalOut.resize(arg.BoolPalOut.size());
	BoolPalIn = arg.BoolPalIn;
	BoolPalOut = arg.BoolPalOut;
}

template<const std::size_t N>
BoolFunct<N>::BoolFunct(bool arg)
{
	min_MAX = arg;

	estado_nl1.Est	= res_parser_nl1::BIEN_nl1;
	estado_l1.Est	= res_parser_l1::BIEN_l1;
	estado_l1.NE	= 0;
	estado_l1.NS	= 1;
	n_terms			= 0;
	n_linea			= 0;
	ix				= false;
	ind_grupo		= 0;
	B3Term_t<N>	palabra(1);
	if (arg)
		palabra[0]=true;
	else
		palabra[0]=false;
	bf.push_front(palabra);
}

template<const std::size_t N>
const BFunct_t<N> & BoolFunct<N>::g_access_funct() const
{return (bf);}
template<const std::size_t N>
bool BoolFunct<N>::EstadoFinalParser_BIEN() const {
	return ((estado_l1.Est==res_parser_l1::BIEN_l1)and(estado_nl1.Est==res_parser_nl1::BIEN_nl1));
}
template<const std::size_t N>
bool BoolFunct<N>::EstadoFinalParser_ERROR() const {
	return ((estado_l1.Est==res_parser_l1::ERROR_l1)or(estado_nl1.Est==res_parser_nl1::ERROR_nl1));
}

template<const std::size_t N>
std::string BoolFunct<N>::bterm2string(B3Term_t<N> cont) {
	std::string ret;		
	ret.clear();	
	IB3Term_t<N>		it		=	cont.begin();
	c_IB3Term_t<N>		itend	=	cont.end();
	
	for( ; it < itend ; it++ )
		if ((*it)==T3v)
			ret += 'T';
		else if ((*it)==F3v)
			ret += 'F';
		else
			ret += 'x';
	
	return ret;
}


template<const std::size_t N>
B3Term_t<N> BoolFunct<N>::string2bterm(std::string arg) {
    const int n = arg.size();
	B3Term_t<N> ret(n);
    for(int I=0; I<n; I++)
        if ((arg[I] == 'f')||(arg[I] == 'F'))
	  	    ret[I]=F3v ;
        else if ((arg[I] == 't')||(arg[I] == 'T'))
	  	    ret[I]=T3v ;
		else
			ret[I]=x3v ;
    return ret;
}

template<const std::size_t N>
void BoolFunct<N>::asignar_strings_a_listfunct(int n,int m,const std::string & cad_in) {

    B3Term_t<N> pal(n);

    for( int J = 0, JJ = 0 ; J < m ; J++,JJ+=(n+1) ) {
		std::string cpal;
		cpal.clear();
		for( int I = 0 ; I < n ; ++I ) {
			cpal += cad_in[I+JJ];
		}
		
		pal=BoolFunct<N>::string2bterm(cpal);
	
		bf.push_back(pal);
		
    }
    return;
}

char* fill_cstr(char* cstr, char c,unsigned n) {
	for(unsigned i=0;i<(n-1);i++) cstr[i]=c;
	cstr[n-1]='\0';
	return cstr;
}


template<const std::size_t N>
BoolFunct<N>::BoolFunct(std::istream & sin,int arg_f_k,bool vt) {
	ix						= false;
	ind_grupo				= 0;
	f_k						= arg_f_k;
	min_MAX					= vt;
	BoolFunct & cthis		= (*this);
	res_parser_l1    l1;
	res_parser_nl1   nl1;
	std::string str_to_be_parsed;
	str_to_be_parsed.clear();
	char cstr_to_be_parsed[max_long_cstr];
	fill_cstr(cstr_to_be_parsed,'\0',max_long_cstr);
	bool es_la_l1			= true;
	
	int n_terms				= 0;
	int n_linea				= 1;
	while ((!sin.eof()) && sin.good() && ((l1.Est!=res_parser_l1::ERROR_l1)and(nl1.Est!=res_parser_nl1::ERROR_nl1))) {
		sin.getline(cstr_to_be_parsed,max_long_cstr,'\n');
		if (sin.good()) {
			n_linea++;
			str_to_be_parsed = static_cast<std::string>(cstr_to_be_parsed);
			if (es_la_l1) {
				l1				= res_parser_l1(str_to_be_parsed);
				es_la_l1		= false;
				
			}
			else {
				nl1				= res_parser_nl1(str_to_be_parsed,l1.NE,l1.NS);
				if ((nl1.BoolPalOut[f_k])==((vt)?T3v:F3v)){
					bf.push_back(nl1.BoolPalIn);
					n_terms ++;
				}
				es_la_l1		= false;
				
			}
		}
		fill_cstr(cstr_to_be_parsed,'\0',max_long_cstr);
	}
	
	cthis.estado_l1.Est		=	l1.Est;
	cthis.estado_nl1.Est	=	nl1.Est;
	cthis.n_linea			=	n_linea;
	cthis.n_terms			=	n_terms;
	cthis.estado_l1.NE		=	l1.NE;
	cthis.estado_l1.NS		=	l1.NS;
}

template<const std::size_t N>
IBFunct_t<N> BoolFunct<N>::begin() {
	return bf.begin();
}

template<const std::size_t N>
c_IBFunct_t<N> BoolFunct<N>::end() const {
	return bf.end();
}

template<const std::size_t N>
void BoolFunct<N>::ordena_por_num_1s() {
	const unsigned int num_groups = g_NE()+1;
	

	for (unsigned int i = 0; i < num_groups ; ++i){
		bolsa[ix?1:0].push_front(make_pair(BFunct_t<N>(),num_groups-i-1));
	}

	for (unsigned int i = 0; i < num_groups-1 ; ++i){
		bolsa[ix?0:1].push_front(make_pair(BFunct_t<N>(),num_groups-i-2));
	}

	c_IBFunct_t<N>   	fin = bf.end();
	IBFunct_t<N> 		it 	= bf.begin();

	for( ; it != fin ; ++it ) {
	
		c_IB3Term_t<N> pfin = it->end();
		IB3Term_t<N>   pit  = it->begin();
		unsigned int n_g = BoolFunct::cuenta_1s_de_la_palabra(pit,pfin);
		IBFunct_Ord_t<N>   it_bolsa  = bolsa[ix?1:0].begin();
		c_IBFunct_Ord_t<N>   fin_bolsa  = bolsa[ix?1:0].end();
		
		for(; (it_bolsa != fin_bolsa)and((*it_bolsa).second!=n_g); ++it_bolsa);
		
		(*it_bolsa).first.push_front(*it);
	}
	++ind_grupo;
}

template<const std::size_t N>
bool BoolFunct<N>::comprobar_adyacencias(const B3Term_t<N> & arg1,const B3Term_t<N> & arg2) const {
	std::cout << bterm2string(arg1) << " ; " << bterm2string(arg2) << std::endl;
	const unsigned int sz = arg1.size();
	const unsigned int sz2 = arg2.size();
	if (sz != sz2) return false;
	else {
		unsigned int distancia_H = 0;
		for(unsigned int i=0;(i<sz)and(distancia_H<2);++i)
			if(arg1[i]==arg2[i]) continue;
			else if ((arg1[i]==x3v)or(arg2[i]==x3v)) distancia_H+=(this->g_NE())+1;
			else ++distancia_H;
		if (distancia_H == 1) return true;
		else return false;
	}
}

template<const std::size_t N>
B3Term_t<N> BoolFunct<N>::operar_adyacencias(const B3Term_t<N> & arg1,const B3Term_t<N> & arg2) const {
	
	B3Term_t<N> ret(arg1);
	const unsigned int sz = arg1.size();
	unsigned int i = 0;
	for(;(i<sz)and(arg1[i]==arg2[i]);++i);
	ret[i] = x3v;
	return ret;
}

template<const std::size_t N>
unsigned int BoolFunct<N>::cuenta_1s_de_la_palabra(IB3Term_t<N> & it,c_IB3Term_t<N> & fin){
	unsigned int cuenta_de_1s = 0;
	for( ; it != fin ; ++it )
		if ((*it)==T3v) ++cuenta_de_1s;
	return cuenta_de_1s;
}

template<const std::size_t N>
void BoolFunct<N>::crea_tabla_por_adyacencias() {
	const unsigned int num_groups		= g_NE() + 1;
		  unsigned int ind_group_act	= num_groups - ind_grupo;

	c_IBFunct_Ord_t<N> fin_bolsa			= bolsa[ix?1:0].end();
	IBFunct_Ord_t<N>   it_bolsa			= bolsa[ix?1:0].begin();
	IBFunct_Ord_t<N>   it_bolsa_sig_group	= (++(bolsa[ix?1:0].begin()));

	bolsa[ix?0:1].clear();
	for ( int i = ind_group_act-1 ; i >= 0 ; --i){
		bolsa[ix?0:1].push_front(make_pair(BFunct_t<N>(),i));
	}

	Bolsa_Palabras_t<N>	adyacencias_guardadas;

	
	IBFunct_Ord_t<N>   it_bolsa_sig		= bolsa[ix?0:1].begin();

	for (;it_bolsa!=fin_bolsa and it_bolsa_sig_group!=fin_bolsa;++it_bolsa,++it_bolsa_sig,++it_bolsa_sig_group) {
		bool con_adyacencias = false;
		IBFunct_t<N>	it1 = (*it_bolsa).first.begin();
		c_IBFunct_t<N>  ite1= (*it_bolsa).first.end();
		c_IBFunct_t<N>  ite2= (*it_bolsa_sig_group).first.end();

		for(;it1!=ite1;++it1) {
			IBFunct_t<N>	it2 = (*it_bolsa_sig_group).first.begin();
			for(;it2!=ite2;++it2) {
				if (comprobar_adyacencias(*it1,*it2)) {
					adyacencias_guardadas.insert(*it2);
					(*it_bolsa_sig).first.push_front(operar_adyacencias(*it1,*it2));
					std::cout<<"		"<< bterm2string(operar_adyacencias(*it1,*it2)) << std::endl;
					con_adyacencias = true;
				}
			}
			if ((!con_adyacencias)and(! adyacencias_guardadas.count(*it1) )) impl_primos.insert(*it1);
		}
	}

	c_IBFunct_Ord_t<N> fin_bolsa_uc			= bolsa[ix?1:0].end();
	IBFunct_Ord_t<N>   it_bolsa_uc				= bolsa[ix?1:0].begin();
	for(;it_bolsa_uc!=fin_bolsa_uc;++it_bolsa_uc);
	--it_bolsa_uc;
	IBFunct_t<N> it1 = (*it_bolsa_uc).first.begin();
	c_IBFunct_t<N> ite1= (*it_bolsa_uc).first.end();
	for(;it1!=ite1;++it1) {
		if (! adyacencias_guardadas.count(*it1) ) impl_primos.insert(*it1);
	}

	++ind_grupo;
	ix = !(ix);
}

template<const std::size_t N>
void BoolFunct<N>::Genera_Tabla_De_Adyacencias_Por_Recurrencia() {
	ordena_por_num_1s();
	while(ind_grupo <= (g_NE()))
		crea_tabla_por_adyacencias();
	bolsa[0].clear();
	bolsa[1].clear();
}

template<const std::size_t N>
void BoolFunct<N>::Genera_Tabla_De_Implicantes_Primos() {
 
    Funct_BTerm_Nums_t<N> f_term_nums;
    Funct_Num_BTerms_t<N> f_num_terms;
    Conj_Z_t           conj_terms_en_dec;
	
	B3Term_t<N> destino(estado_l1.NE);
	unsigned char num_Xs = 0;
	std::vector< bool >	posiciones_Xs(static_cast<unsigned char>(estado_l1.NE));
    Conj_Z_t conj_nums;
    Elem_Z_t representacion;

	IImpl_Primos_set_t<N> 		itip 		= impl_primos.begin();
    c_IImpl_Primos_set_t<N> 	itip_end 	= impl_primos.end();
	for ( ; itip != itip_end ; ++itip ) {
		num_Xs = 0;
		for ( unsigned char i=0 ; i < static_cast<unsigned char>(estado_l1.NE) ; ++i ) {
			if (((*itip)[i]) == x3v) {
				++num_Xs;
				posiciones_Xs[i] =  true;
			}
			else {
				posiciones_Xs[i] = false;
			}
		}

		if (num_Xs == 0) {
			destino = *itip;
			representacion = 0;
			for ( unsigned char r = 0 ; r < static_cast<unsigned char>(estado_l1.NE) ; ++r ){
				representacion *= 2;
				if (destino[r]==T3v) ++representacion;
			}
			conj_nums.insert(representacion);
			conj_terms_en_dec.insert(representacion);
			f_term_nums.insert( make_pair(destino,conj_nums) );
			conj_nums.clear();
		}
		else {
			B3Term_t<N> pal(num_Xs);
			for (unsigned char q=0 ; q < static_cast<unsigned char>(num_Xs) ; ++q )
				pal[q]=false;
			destino = *itip;
			Elem_Z_t pot_2_num_Xs = 2;
			for (unsigned char t = 1 ; t < num_Xs ; ++t)
				pot_2_num_Xs *= 2;
			for (Elem_Z_t i=0; i < pot_2_num_Xs ; ++i) {
				
				unsigned char s = 0;
				for(unsigned char t=0 ; t < static_cast<unsigned char>(estado_l1.NE) ; ++t) {
					if (posiciones_Xs[t]) {
						destino[t]=pal[s];
						++s;
					}
				}
				representacion = 0;
				for ( unsigned char r=0 ; r <static_cast<unsigned char>(estado_l1.NE) ; ++r ){
					representacion *= 2;
					if (destino[r]==T3v) ++representacion;
				}
				conj_nums.insert(representacion);
				conj_terms_en_dec.insert(representacion);
				
				bool carry = true;
				for (unsigned char p = 0; p < num_Xs ; ++p) {
					pal[p] = pal[p] xor carry;
					if ((pal[p] and carry) == T3v) carry = true;
					else carry = false;
				}
				destino = *itip;
			}
			f_term_nums.insert( make_pair(destino,conj_nums) );
			conj_nums.clear();
		}
	}
	saca_mapa(f_term_nums);
	std::cout << " f_term_nums es de tamano : " << f_term_nums.size() << std::endl;

	
	Bolsa_Palabras_t<N>    conj_terms;
	Generar__F_Num_Terms(f_term_nums,conj_terms_en_dec,conj_terms,f_num_terms);
	saca_mapa_inverso(f_num_terms);
	Iteracion__Deteccion_Primos_Esenciales_ETC(f_term_nums,conj_nums,conj_terms,f_num_terms);
	impl_esenciales.insert(conj_terms.begin(),conj_terms.end());
	saca_conjunto_de_palabras(conj_terms);
	saca_mapa(f_term_nums);
	Generar__F_Num_Terms(f_term_nums,conj_terms_en_dec,conj_terms,f_num_terms);
	saca_mapa_inverso(f_num_terms);
	Limpiar__F_Term_Nums__de_terminos_vacios(f_term_nums);
	Generar__F_Num_Terms(f_term_nums,conj_terms_en_dec,conj_terms,f_num_terms);
	
	while(!(f_term_nums.empty())) {
		std::cout << std::endl << " Entro en un nuevo bucle porque f_term_nums no es vacio. " << std::endl;
		Detectar_Terminos_Principales_y_Borrar_Los_Mas_pesados(f_term_nums,conj_nums,conj_terms,f_num_terms);
		impl_esenciales.insert(conj_terms.begin(),conj_terms.end());
		saca_conjunto_de_palabras(conj_terms);
		saca_mapa(f_term_nums);
		Generar__F_Num_Terms(f_term_nums,conj_terms_en_dec,conj_terms,f_num_terms);
		Iteracion__Deteccion_Primos_Esenciales_ETC(f_term_nums,conj_nums,conj_terms,f_num_terms);
		impl_esenciales.insert(conj_terms.begin(),conj_terms.end());
		saca_conjunto_de_palabras(conj_terms);
		saca_mapa(f_term_nums);
		Generar__F_Num_Terms(f_term_nums,conj_terms_en_dec,conj_terms,f_num_terms);
		saca_mapa_inverso(f_num_terms);
		Limpiar__F_Term_Nums__de_terminos_vacios(f_term_nums);
		Generar__F_Num_Terms(f_term_nums,conj_terms_en_dec,conj_terms,f_num_terms);
	}
	return;
}

template<const std::size_t N>
void BoolFunct<N>::Limpiar__F_Term_Nums__de_terminos_vacios(Funct_BTerm_Nums_t<N> & f_term_nums) {
	Bolsa_Palabras_t<N> bolsa_terminos;
	c_IFunct_BTerm_Nums_t<N> it_end = f_term_nums.end();
	IFunct_BTerm_Nums_t<N>   it     = f_term_nums.begin();
	for( ;it != it_end; ++it) {
		if ((it->second).empty()) {
			bolsa_terminos.insert(it->first);
		}
	}
	c_IBolsa_Palabras_t<N> it_bp_end = bolsa_terminos.end();
	IBolsa_Palabras_t<N>   it_bp     = bolsa_terminos.begin();
	for( ;it_bp != it_bp_end; ++it_bp) {
		f_term_nums.erase(*it_bp);
	}
	return;
}

template<const std::size_t N>
void BoolFunct<N>::Generar__F_Num_Terms(Funct_BTerm_Nums_t<N> & f_term_nums,
                                     Conj_Z_t & conj_terms_en_dec,
									 Bolsa_Palabras_t<N> & conj_terms,
									 Funct_Num_BTerms_t<N> & f_num_terms) const {
	
	conj_terms.clear();
	f_num_terms.clear();
	c_IConj_Z_t itz_end = conj_terms_en_dec.end();
	IConj_Z_t   itz     = conj_terms_en_dec.begin();
	for( ; itz != itz_end ; ++itz ){
		
		c_IFunct_BTerm_Nums_t<N> it_bt_nums_end = f_term_nums.end();
		IFunct_BTerm_Nums_t<N> it_bt_nums = f_term_nums.begin();
		for( ; it_bt_nums != it_bt_nums_end ; ++it_bt_nums ) {
			if (it_bt_nums->second.count(*itz)>0) {
				conj_terms.insert(it_bt_nums->first);
			}
		}
		if (conj_terms.size()>0) {
			f_num_terms.insert( make_pair(*itz,conj_terms) );
		}
	    conj_terms.clear();
	}
	return;
}

template<const std::size_t N>
void BoolFunct<N>::Iteracion__Deteccion_Primos_Esenciales_ETC(
									 Funct_BTerm_Nums_t<N> & f_term_nums,
                                     Conj_Z_t & conj_nums,
									 Bolsa_Palabras_t<N> & conj_terms,
									 Funct_Num_BTerms_t<N> & f_num_terms) const {
	conj_terms.clear();
	B3Term_t<N> palabra;
	IFunct_Num_BTerms_t<N> it_num_bts = f_num_terms.begin();
	c_IFunct_Num_BTerms_t<N> it_num_bts_end = f_num_terms.end();
	for( ; it_num_bts != it_num_bts_end ; ++it_num_bts ) {
		if((it_num_bts->second.size())==1) {
			palabra = (*(it_num_bts->second.begin()));
			conj_terms.insert(palabra);
			conj_nums = f_term_nums[palabra];
			IConj_Z_t it_Z = conj_nums.begin();
			c_IConj_Z_t it_Z_end = conj_nums.end();
			for( ; it_Z != it_Z_end ; ++it_Z ) {
				c_IBolsa_Palabras_t<N> it_1_end = f_num_terms[*it_Z].end();
				IBolsa_Palabras_t<N>   it_1 = f_num_terms[*it_Z].begin();
				for( ; it_1 != it_1_end ; ++ it_1 ) {
					f_term_nums[*it_1].erase(*it_Z);
				}
			}
		}
		f_term_nums.erase(palabra);
	}
	return;
}

template<const std::size_t N>
void BoolFunct<N>::Detectar_Terminos_Principales_y_Borrar_Los_Mas_pesados (
				Funct_BTerm_Nums_t<N> & f_term_nums,
				Conj_Z_t & conj_nums,
				Bolsa_Palabras_t<N> & conj_terms,
				Funct_Num_BTerms_t<N> & f_num_terms ) const {
	c_IFunct_BTerm_Nums_t<N>   it_bterm_nums_end = f_term_nums.end();
	IFunct_BTerm_Nums_t<N>		it_bterm_nums	  = f_term_nums.begin();
	IFunct_BTerm_Nums_t<N>		it_bterm_nums_max;
	IFunct_BTerm_Nums_t<N>		it_bterm_nums_min;

	conj_terms.clear();
	B3Term_t<N> palabra;
	palabra.clear();
	
	
	unsigned int numero = it_bterm_nums->second.size();
	unsigned int numero_max = numero;
	it_bterm_nums_max = it_bterm_nums;
	unsigned int numero_min = numero;
	it_bterm_nums_min = it_bterm_nums;
	++it_bterm_nums;
	for( ; it_bterm_nums != it_bterm_nums_end ; ++it_bterm_nums ) {
		numero = it_bterm_nums->second.size();
		if (numero > numero_max) {
			numero_max = numero;
			it_bterm_nums_max = it_bterm_nums;
		}
		else if (numero < numero_min) {
			numero_min = numero;
			it_bterm_nums_min = it_bterm_nums;
		}
	}
	if (numero_max == numero_min) {
		it_bterm_nums_min	  = f_term_nums.begin();
		it_bterm_nums_max	  = ++it_bterm_nums_max; 
	}
	
	palabra.clear();
	palabra = it_bterm_nums_max->first;
	conj_terms.insert(palabra);
	conj_nums = it_bterm_nums_max->second;
	c_IConj_Z_t it_Z_end = conj_nums.end();
	IConj_Z_t it_Z = conj_nums.begin();
	for( ; it_Z != it_Z_end ; ++it_Z ) {
		c_IBolsa_Palabras_t<N> it_1_end = f_num_terms[*it_Z].end();
		IBolsa_Palabras_t<N>   it_1 = f_num_terms[*it_Z].begin();
		for( ; it_1 != it_1_end ; ++ it_1 ) {
			f_term_nums[*it_1].erase(*it_Z);
		}
	}
	f_term_nums.erase(palabra);
	return;
}

template<const std::size_t N>
void  BoolFunct<N>::saca_primos_esenciales() {
	saca_conjunto_de_palabras(impl_esenciales);
	return;
}

template<const std::size_t N>
void saca_mapa( Funct_BTerm_Nums_t<N> & arg ) {
	IFunct_BTerm_Nums_t<N> 	it		=arg.begin();
	c_IFunct_BTerm_Nums_t<N> 	itend	=arg.end();
	for ( ; it != itend ; ++it) {
			std::cout << " Un implicante primo : " << std::endl;
			std::string salida_palabra(BoolFunct<N>::bterm2string(it->first));
			std::cout << "	" << salida_palabra << std::endl;
			c_IConj_Z_t     itn_end = it->second.end();
			IConj_Z_t       itn     = it->second.begin();
			for( ; itn != itn_end ; ++itn) {
				std::cout << (*itn) << std::endl;
			}
			std::cout << " Termino del implicante primo. " << std::endl;
	}
	std::cout << std::endl;
	return;
}

template<const std::size_t N>
void saca_mapa_inverso( Funct_Num_BTerms_t<N> & arg ) {
	IFunct_Num_BTerms_t<N> 	it		=arg.begin();
	c_IFunct_Num_BTerms_t<N> 	itend	=arg.end();
	for ( ; it != itend ; ++it) {
			std::cout << " Un numero correpodiente a un minterms : " << std::endl;
			std::cout << "	" << (it->first) << std::endl;
			c_IBolsa_Palabras_t<N>   itn_end = it->second.end();
			IBolsa_Palabras_t<N>     itn     = it->second.begin();
			for( ; itn != itn_end ; ++itn) {
			    std::string salida_palabra(BoolFunct<N>::bterm2string(*itn));
				std::cout << salida_palabra << std::endl;
			}
			std::cout << " Termino del numero representante del minterm. " << std::endl;
	}
	std::cout << std::endl;
	return;
}

template<const std::size_t N>
void saca_bolsa(BoolFunct<N> & arg,bool ind_bool) {
	IBFunct_Ord_t<N> it2=(arg.bolsa[ind_bool?1:0]).begin();
	c_IBFunct_Ord_t<N> fin2=(arg.bolsa[ind_bool?1:0]).end();
	for (unsigned int ind = 0 ; it2 != fin2 ; ++it2,++ind) {
		IBFunct_t<N> itg=((*it2).first).begin();
		c_IBFunct_t<N> fing=((*it2).first).end();
		std::cout << " itg es igual que fing ?	" << ((itg == fing)?("vacio"):("no vacio")) << std::endl;
		std::cout << "	Numero de Grupo es	" << (*it2).second << "	;	" << ind << std::endl;
		for( ; itg != fing ; ++itg) {
			std::string salida_palabra(BoolFunct<N>::bterm2string(*itg));
			std::cout << '	' << salida_palabra << " en grupo " << (*it2).second << std::endl;
		}
	}
	return;
}

template<const std::size_t N>
void saca_lista(BoolFunct<N> & arg) {
	IBFunct_t<N> it2=arg.bf.begin();
	c_IBFunct_t<N> fin2=arg.bf.end();
	for (; it2 != fin2 ; ++it2) {
			std::string salida_palabra = BoolFunct<N>::bterm2string(*it2);
			std::cout << '	' << salida_palabra << std::endl;
	}
	return;
}

template<const std::size_t N>
void saca_conjunto(BoolFunct<N> & arg) {
	IImpl_Primos_set_t<N> it		=arg.impl_primos.begin();
	c_IImpl_Primos_set_t<N> itend	=arg.impl_primos.end();
	for (; it != itend ; ++it) {
			std::string salida_palabra(BoolFunct<N>::bterm2string(*it));
			std::cout << '	' << salida_palabra << std::endl;
	}
	return;
}

template<const std::size_t N>
void saca_conjunto_de_palabras(Bolsa_Palabras_t<N> & arg) {
	IBolsa_Palabras_t<N> it		=arg.begin();
	c_IBolsa_Palabras_t<N> itend	=arg.end();
	for (; it != itend ; ++it) {
			std::string salida_palabra(BoolFunct<N>::bterm2string(*it));
			std::cout << '	' << salida_palabra << std::endl;
	}
	return;
}

#endif // ESTRUCTURASFUNCIONES_HPP
