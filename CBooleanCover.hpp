#ifndef CBOOLEANCOVER_HPP
#define CBOOLEANCOVER_HPP

#include "CBooleanCube.hpp"
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>

#include <iterator>

using listint = std::list<std::size_t>;
using lintiterator = typename listint::iterator;
using c_lintiterator = typename listint::const_iterator;

using setint = std::set<std::size_t>;
using sintiterator = typename setint::iterator;
using c_sintiterator = typename setint::const_iterator;

template<const std::size_t NE,const std::size_t NS>
using second_t = decltype(BinCube<NE,NS>::second);

template<const std::size_t NE,const std::size_t NS>
using first_t = decltype(BinCube<NE,NS>::first);

template<const std::size_t NE,const std::size_t NS>
using Bin2rMatrix = std::map<second_t<NE,NS>,first_t<NE,NS>>;

template<const uint NE,const uint NS>
using BFunct_t		= std::map<ulint,Cube<NE,NS>>;

template<const uint NE,const uint NS>
using IBFunct_t		= typename BFunct_t<NE,NS>::iterator;

template<const uint NE,const uint NS>
using c_IBFunct_t	= typename BFunct_t<NE,NS>::const_iterator;

template<const uint NE>
struct SBinateVariable {
	bool	is_unate;
	uint	j;
};

struct temp_t {
	uint j;
	bool  gt_t_0;
};

template<const std::size_t,const std::size_t> class CBooleanCover;

template<const std::size_t NE,const std::size_t NS>
class W_CONTAINED_IN_cp{
public:
    CBooleanCover<NE,NS> W;
    CBooleanCube<NE,NS>  cp;
};

template<const std::size_t,const std::size_t> class CBinCover;

template<const std::size_t NE,const std::size_t NS>
using BinMat = std::map<ulint,CBinCube<NE,NS>>;

template<const std::size_t NE,const std::size_t NS>
using IBinCover = typename BinMat<NE,NS>::iterator;

template<const std::size_t NE,const std::size_t NS>
using c_IBinCover = typename BinMat<NE,NS>::const_iterator;

template<const std::size_t NE,const std::size_t NS>
class CBooleanCover : public BFunct_t<NE,NS>
{
	using BCover		=	CBooleanCover<NE,NS>;
	using BFunc			=	BFunct_t<NE,NS>;
	using IBFunc		=	IBFunct_t<NE,NS>;
	using c_IBFunc		=	c_IBFunct_t<NE,NS>;
	using BCube			=	CBooleanCube<NE,NS>;
	using BinCube		=	CBinCube<NE,NS>;
	using BinCubeIn		=	CBinCube<NE,NS>;
	using BinateVar		=	SBinateVariable<NE>;

private:
	ulint	m_NTP;

public:
	inline void push_back(BCube arg) {
	
		BCover & cthis = (*this);
		//std::cout << "INPUT IN PUSH_BACK WITH INSERT" << std::endl;
		//std::cout << cthis << std::endl;
		//std::cout << cthis.size() << std::endl;
		//std::cout << "-------------------------------" << std::endl;
		//std::cout << arg << std::endl;
		cthis.BFunc::insert(CBooleanCube<NE,NS>(arg));
		//std::cout << "-------------------------------" << std::endl;
		//std::cout << cthis << std::endl;
		//std::cout << cthis.size() << std::endl;
		//std::cout << "OUTPUT IN PUSH_BACK WITH INSERT" << std::endl;
		++m_NTP;
		return;
	}
	
	inline void push_back(const BooleanCube<NE,NS>& arg) {
		BCover & cthis = (*this);
		//std::cout << "INPUT IN PUSH_BACK WITH INSERT" << std::endl;
		//std::cout << cthis << std::endl;
		cthis.BFunc::insert(arg);
		//std::cout << cthis << std::endl;
		//std::cout << "OUTPUT IN PUSH_BACK WITH INSERT" << std::endl;
		++m_NTP;
		return;
	}

	inline void push_back(const Cube<NE,NS>& arg) {
		BCover & cthis = (*this);
		//std::cout << "INPUT IN PUSH_BACK WITH INSERT" << std::endl;
		//std::cout << cthis << std::endl;
		cthis.BFunc::insert(std::pair<unsigned long int , Cube<NE,NS> >(CBooleanCube<NE,NS>(arg).calculo_de_key(),arg));
		//std::cout << cthis << std::endl;
		//std::cout << "OUTPUT IN PUSH_BACK WITH INSERT" << std::endl;
		++m_NTP;
		return;
	}
	
	inline void clear() {
		CBooleanCover & cthis = (*this);
		cthis.BFunc::clear();
		m_NTP=0;
		return;
	}

	inline IBFunc erase(IBFunc it){
		if (m_NTP > 0)  --m_NTP;
		return this->BFunc::erase(it);
	}

	inline c_IBFunc erase(c_IBFunc it){
		if (m_NTP > 0)  --m_NTP;
		return this->BFunc::erase(it);
	}

	inline std::size_t size() const {
		return m_NTP;
	}

	CBooleanCover() :
		BFunc(),m_NTP(0)
	{}

	CBooleanCover(const BCover & arg) {
		c_IBFunc		itfrom	=	arg.begin();
		const c_IBFunc	itend	=	arg.end();
		for(;itfrom != itend;++itfrom) {
			this->push_back(itfrom->second);
		}
		this->m_NTP = arg.m_NTP;
	}

	CBooleanCover(const CBinCover<NE,NS> & arg) {
		this->m_NTP = 0;
		c_IBinCover<NE,NS>	itfrom	=	arg.begin();
		const c_IBinCover<NE,NS>	itend	=	arg.end();
		for(;itfrom != itend;++itfrom) {
			BCube thiscube;
			for(std::size_t k = 0; k<NE;++k) {
				thiscube[k]=((((*itfrom)[k])==T2rv)?(((itfrom->asc_desc)[k])?T4v:F4v):X4v);
			}
			this->push_back(thiscube);
		}
	}

	CBooleanCover(const BCover & arg1,const CBooleanCube<NE,NS> & arg2,cofactor_t op) :
		CBooleanCover(arg1)
	{
		c_IBFunc		itfrom	=	arg2.begin();
		const c_IBFunc	itend	=	arg2.end();
		for(;itfrom != itend;++itfrom) {
			itfrom->m_cofactor(arg2);
			if (itfrom->is_empty()) {
				itfrom->erase(itfrom);
				--itfrom;
			}
		}
	}

	CBooleanCover(const BCover & arg,std::size_t j,bool posneg,cofactor_t op) :
		CBooleanCover(arg)
	{
		c_IBFunc		itfrom	=	this->begin();
		const c_IBFunc	itend	=	this->end();
		for(;itfrom != itend;++itfrom) {
			itfrom->m_cofactor(j,posneg);
			if (itfrom->is_empty()) {
				itfrom->erase(itfrom);
				--itfrom;
			}
		}
	}

	CBooleanCover(const std::string & file_name) {
		char c_linea[2*(NE+NS+1)];
		std::ifstream file;
		this->clear();
		this->m_NTP = 0;
		std::size_t k=0;
		file.open(file_name);
	//	std::cout << ((file.is_open())?"abierto":"error:cerrado") << std::endl;
	//	std::cout << ((file.eof())?"fichero vacio":"fichero no vacio") << std::endl;
		while((!(file.eof()))and(file.is_open())) {
			for(std::size_t i=0 ; i < 2*(NE+NS+1) ; ++i) {c_linea[i] = '\0';}
			file.getline(c_linea,2*(NE+NS+1)-1,'\n');
			const std::string linea(c_linea);
			const BCube cubo(linea);
			if (!(cubo.is_empty())) {
				this->push_back(cubo);
				++k;
			}
		}
		this->m_NTP = k;
		file.close();
	}

	CBooleanCover & operator=(const CBooleanCover & arg) {
		clear();
		c_IBFunc		itfrom	=	arg.begin();
		const c_IBFunc	itend	=	arg.end();
		for(;itfrom != itend;++itfrom) {
			this->push_back(*itfrom);
		}
		this->m_NTP = arg.m_NTP;
		return (*this);
	}

	CBooleanCover & operator=(const std::string & file_name) {
		clear();
		this->m_NTP = 0;
		char c_linea[2*(NE+NS+1)];
		std::size_t k=0;
		std::ifstream file;
		file.open(file_name);
			while(!(file.eof())) {
				for(std::size_t i=0 ; i < 2*(NE+NS+1) ; ++i) {
					c_linea[i] = '\0';
				}
				file.getline(c_linea,2*(NE+NS+1)-1,'\n');
				const std::string linea(c_linea);
				const BCube cubo(k,linea);
				this->push_back(cubo);
				++k;
			}
		file.close();
		return (*this);
	}

	const CBooleanCover<NE,NS>& cofactor(const CBooleanCube<NE,NS> & arg, CBooleanCover & ret) const
	{
		c_IBFunc		itfrom		=	this->begin();
		const c_IBFunc	itend		=	this->end();
		
		for(;itfrom != itend;++itfrom) {
			CBooleanCube<NE,NS> tempt(itfrom->second);
			if (!(tempt.is_empty())) {
				ret.push_back(tempt.cofactor(arg));
			}
		}
		return ret;
	}

	CBooleanCover cofactor(uint v,bool posneg, CBooleanCover & ret) const {
		c_IBFunc		itfrom	=	this->begin();
		const c_IBFunc	itend	=	this->end();
		c_IBFunc		itfromr	=	ret.begin();
		const c_IBFunc	itendr	=	ret.end();

		for(;itfrom != itend;++itfrom,++itfromr) {
			if(itfromr!=itendr) {
				(*itfromr)=itfrom->cofactor(v,posneg);
				if (itfrom->is_empty()) {
					itfrom->erase(itfrom);
					--itfrom;
				}
			}
			else {
				if (!(itfrom->is_empty()))
					ret.push_back(itfrom->cofactor(*this));
			}
		}
		return;
	}

	const CBooleanCover& m_cofactor(uint v,bool posneg) {
		c_IBFunc		itfrom	=	this->begin();
		const c_IBFunc	itend	=	this->end();
		for(;itfrom != itend;++itfrom) {
				(*itfrom)=itfrom->cofactor(v,posneg);
				if (itfrom->is_empty()) {
					itfrom->erase(itfrom);
					--itfrom;
				}
		}
		return;
	}

	CBooleanCover operator && (const BCube & arg) const {
		c_IBFunc			itt		=	this->begin();
		const c_IBFunc		itt_e	=	this->end();
		BCover ret;
		ret.NTP = 0;
		for( ; itt != itt_e ; ++itt) {
			const BCube producto((*itt) and arg);
			const bool empty = producto.is_empty();
			if (!(empty)) ret.push_back(producto);
		}
		return ret;
	}

	CBooleanCover operator || (const CBooleanCover & arg) const {
		c_IBFunc			ita		=	arg.begin();
		const c_IBFunc		ita_e	=	arg.end();
		BCover ret(*this);
		ret.NTP=0;
		for( ; ita != ita_e ; ++ita) {
			ret.push_back(*ita);
		}
		return ret;
	}

	const CBooleanCover & operator |= (const CBooleanCover & arg) {
		c_IBFunc			ita		=	arg.begin();
		const c_IBFunc		ita_e	=	arg.end();
		this->m_NTP=0;
		for( ; ita != ita_e ; ++ita) {
			this->push_back(*ita);
		}
		return (*this);
	}


	const CBooleanCover & operator &= (const BCube & arg) {
				IBFunc		itt		=	this->begin();
		const c_IBFunc		itt_e	=	this->end();

		while( itt != itt_e ) {
			CBooleanCube<4,2> ITT(itt->second);
			ITT&=arg;
			if (ITT.is_empty())
				itt = this->erase(itt);
			else
				++itt;
		}
		return (*this);
	}

    void UNATE_COMPLEMENT( CBooleanCover<NE,NS> & nM
                         ) const {
        const CBooleanCover & M(*this);
        CBinCover<NE,NS> M_PERS(M,PERS_matrix_t::op);
        CBinCover<NE,NS> nM_PERS;
        M_PERS.PERS_UNATE_COMPLEMENT(M_PERS,nM_PERS);
        nM = CBooleanCover<NE,NS>(nM_PERS);
        return;
    }

    void COMP1(CBooleanCover & R) {
        CBooleanCover & F = (*this);
        R.clear();
        const IBFunc itend    = F.end();
        const IBFunc itbegin  = F.begin();
              IBFunc it       = itbegin;
        const CBooleanCover universe(universe::op);
        for( ; it != itend ; ++it ) {
            if((*it)==universe) return;
        }
        if(F.IS_UNATE()) {
            F.UNATE_COMPLEMENT(R);
            return;
        }
        it = itbegin;
        CBooleanCube<NE,NS> c(*it);
        ++it;
        for( unsigned j=0 ; j<NE ; ++j ) {
            for( ; it != itend ; ++it ) {
                if(c.read4(j) != (*it).read4(j))
                    c.write(j,X4v);
            }
        }
        CBooleanCover C;
        CBooleanCover Fc;
        CBooleanCover R1,R0;
        C.push_back(c);
        R|=CBooleanCover(C).UNATE_COMPLEMENT();
        F.cofactor(c,Fc);
        F|=Fc;
        unsigned j = F.BINATE_SELECT();
        R.MERGE_WITH_CONTAINMENT((F.cofactor(j,true,R1)).COMP1(),(F.cofactor(j,false,R0)).COMP1());
        return;
    }

    void COMPLEMENT(const CBooleanCover & F,const CBooleanCover & D) {
        CBooleanCover & R(*this);
        R.clear();
        R.COMPLEMENT(F||D);
        return;
    }

	CBooleanCover exp_Shannon(std::size_t j) const {
		BCover		pret(*this,j,true,cofactor_t::op);
		BCover		nret(*this,j,false,cofactor_t::op);
		pret &= BCover(j,positive_half_space_1_of_n::op);
		nret &= BCover(j,negative_half_space_1_of_n::op);
		pret |= nret;
		return pret;
	}

	const CBooleanCover& m_exp_Shannon(std::size_t j) {
		*this		= BCover(*this,j,true,cofactor_t::op);
		BCover		nret(*this,j,false,cofactor_t::op);
		(*this) &= BCover(j,positive_half_space_1_of_n::op);
		nret &= BCover(j,negative_half_space_1_of_n::op);
		(*this) |= nret;
		return *this;
	}

	inline const	BCover & REUNIR		(
						BCover & H_0,
						BCover & H_1,
						BCube & x_0,
						BCube & x_1		) {
		BCover & H_2 = (*this);
		H_0 &= x_0;
		H_1 &= x_1;
		H_2 |= H_0;
		H_2 |= H_1;
		return H_2;
	}

	inline
	const BCover& BORRAR_cubo_de_Hx_y_Hy__SI_IGUALES_Y_GUARDAR_en_H2 (
				BCover & H_0,
				BCover & H_1 ) {
		
		CBooleanCover & H_2 = (*this);
				IBFunc	i=H_0.begin();
		const	IBFunc k=H_0.end();
				IBFunc	l=H_1.begin();
		const	IBFunc p=H_1.end();

		bool ha_habido_un_borrado;
		while(i != k) {
			ha_habido_un_borrado = false;
			while(l != p) {
				if ((*i)==(*l)) {
					H_2.push_back(*i);
					H_0.erase(i);
					H_1.erase(l);
					l = H_1.begin();
					ha_habido_un_borrado = true;
					break;
				}
				++l;
			}
			if (!(ha_habido_un_borrado)) 
				++i;
		}

		return H_2;
	}

	inline const BCover& BORRAR_cubo_de_Hx_SI_CONTIENE_a_un_cubo_de_Hy_Y_GUARDAR_en_H2(
					BCover & H_0,
					BCover & H_1) {
		
		BCover & H_2 = (*this);
				IBFunc	i=H_0.begin();
		const	IBFunc k=H_0.end();
				IBFunc	l=H_1.begin();
		const	IBFunc p=H_1.end();
		bool ha_habido_un_borrado_i;
		bool ha_habido_un_borrado_l;
		while(i != k) {
			ha_habido_un_borrado_i = false;
			const CBooleanCube<4,2> iI(i->second);
			
			while(l != p) {
				ha_habido_un_borrado_l = false;
				const CBooleanCube<4,2> lL(l->second);
				
				const bool iI_gteq_lL = (iI>lL);
				const bool lL_gteq_iI = (iI<lL);
				if (iI_gteq_lL) {	
					H_2.push_back(*i);
					H_1.erase(l);
					l = H_1.begin();
					ha_habido_un_borrado_l = true;
					
				}
				else if (lL_gteq_iI){	
					H_2.push_back(*l);
					H_0.erase(i);
					i = H_0.begin();
					ha_habido_un_borrado_i = true;
					// std::cout << "*l  > *i" << std::endl;
					// std::cout << H_0 << std::endl;
					// std::cout << H_1 << std::endl;
					// std::cout << H_2 << std::endl;
					break;
				}
				else {
					// std::cout << "*i <> *l" << std::endl;
					// std::cout << H_0 << std::endl;
					// std::cout << H_1 << std::endl;
					// std::cout << H_2 << std::endl;
				}
				if (!(ha_habido_un_borrado_l)) 
					++l;
			}
			if (!(ha_habido_un_borrado_i)) {
				++i;
				l = H_1.begin();
			}
		}
		return H_2;
	}

	inline
	const CBooleanCover & MERGE_WITH_IDENTITY (
				BCover & H_0,
				BCover & H_1,
				BCube & x_0,
				BCube & x_1) {
		BCover & H_2 = (*this);

		H_2.BORRAR_cubo_de_Hx_y_Hy__SI_IGUALES_Y_GUARDAR_en_H2(H_0,H_1);
		H_2.REUNIR(H_0,H_1,x_0,x_1);
		return H_2;
	}

	inline
	const CBooleanCover & MERGE_WITH_CONTAINMENT (
				BCover & H_0,
				BCover & H_1,
				BCube & x_0,
				BCube & x_1) {
		BCover & H_2 = (*this);
	
		H_2.BORRAR_cubo_de_Hx_y_Hy__SI_IGUALES_Y_GUARDAR_en_H2(H_0,H_1);
	
		H_2.BORRAR_cubo_de_Hx_SI_CONTIENE_a_un_cubo_de_Hy_Y_GUARDAR_en_H2
			(H_0,H_1);
		H_2.REUNIR(H_0,H_1,x_0,x_1);
		return H_2;
	}

	inline
	const CBooleanCover & MERGE_WITH_CONTAINMENT (BCover & H,uint j) {
		BCover & H_2 = (*this);
		BCover H_0 = H.cofactor(j,false,cofactor_t::op);
		BCover H_1 = H.cofactor(j,true,cofactor_t::op);
		CBooleanCube<NE,NS> x_0(j,negative_half_space_1_of_n::op);
		CBooleanCube<NE,NS> x_1(j,positive_half_space_1_of_n::op);
		
		H_2.BORRAR_cubo_de_Hx_y_Hy__SI_IGUALES_Y_GUARDAR_en_H2(H_0,H_1);
		
		H_2.BORRAR_cubo_de_Hx_SI_CONTIENE_a_un_cubo_de_Hy_Y_GUARDAR_en_H2(
				H_0,H_1);
		H_2.REUNIR(H_0,H_1,x_0,x_1);
		return H_2;
	}

	inline	const CBooleanCover & MERGE (
				BCover & H_0,
				BCover & H_1,
				const BCube & x_0,
				const BCube & x_1,
				bool CONTAIN) {
		CBooleanCover & H_2 = (*this);

		H_2.BORRAR_cubo_de_Hx_y_Hy__SI_IGUALES_Y_GUARDAR_en_H2(H_0,H_1);
		if (CONTAIN) {
	
			H_2.BORRAR_cubo_de_Hx_SI_CONTIENE_a_un_cubo_de_Hy_Y_GUARDAR_en_H2(H_0,H_1);
		}
		H_2.REUNIR(H_0,H_1,x_0,x_1);
		return H_2;
	}

	uint Cuenta_cubos_con_valor(const bool_l4v V,uint j) const {
		const CBooleanCover & C = (*this);
		uint	cuenta = 0;

		c_IBFunc it = C.begin();
		const c_IBFunc itend = C.end();

		for( ; it!= itend ; ++it ) {
			if ((it->read4(j))==V) ++cuenta;
		}

		return cuenta;
	}

	inline static
	uint max_j_min(const std::array<uint,NE>& p0,const std::array<uint,NE>& p1,std::array<temp_t,NE>& vJ) {
		uint ret = (p0[0]<=p1[0])?(p0[0]):(p1[0]);
		uint num_temp;
		for( uint j=1 ; j < NE ; ++j ) {
			num_temp = (p0[j]<=p1[j])?(p0[j]):(p1[j]);
			vJ[j].gt_t_0 = (num_temp!=0);
			vJ[j].j = num_temp;
			ret = ((ret >= num_temp)?(ret):(num_temp));
		}
		return ret;
	}

	inline static
	void RellenaConjuntoDeMinimosDeP0YP1_no_0(const std::array<temp_t,NE>& vJ,std::set<uint>& J) {
		for(uint j = 0 ; j < NE ; ++j ) 
		{
			if (vJ[j].gt_t_0) J.insert(j);
		}
	}

	inline static
	uint maximo(const std::set<uint>& J,const std::array<uint,NE> & p0,const std::array<uint,NE> & p1) {
		std::set<uint>::const_iterator			itJ=	J.begin();
		const std::set<uint>::const_iterator	itendJ=	J.end();

		uint j = (*itJ);
		uint cmax=p0[j]+p1[j];
		uint jmax = j;
		++itJ;

		for( ; itJ != itendJ ; ++itJ ) {
			j = (*itJ);
			const uint cactual = p0[j]+p1[j];
			const bool cmax_menor_que_cactual = (cmax < cactual);
			cmax = ((cmax_menor_que_cactual)?(cactual):(cmax));
			if (cmax_menor_que_cactual) {
				jmax = j;
			}
		}

		return jmax;
	}

	BinateVar BINATE_SELECT() const {
		const CBooleanCover & C = (*this);
		BinateVar ret;

		std::array<uint,NE> p0,p1;
		for(uint j=0; j < NE ;++j) { 
			p0[j] = C.Cuenta_cubos_con_valor(F4v,j); 
			p1[j] = C.Cuenta_cubos_con_valor(T4v,j);
		}

		std::array<temp_t,NE>	vJ;
		uint					maxjmin = max_j_min(p0,p1,vJ); 
		std::set<uint>			J;
		RellenaConjuntoDeMinimosDeP0YP1_no_0(vJ,J); 

		if (maxjmin==0) { 
			ret.is_unate=true;
			ret.j=0;
		}
		else { 
			ret.is_unate = false;
			ret.j = maximo(J,p0,p1); 
		}

		return ret;
	}

	void UNATE_SIMPLIFY() {
		CBooleanCover & H = (*this);
		bool viene_de_un_break = false;
		IBFunc it1 = H.begin();
		while( it1 != H.end() ) {
			const c_IBFunc itend = H.end();
			for (IBFunc it2 = H.begin(); it2 != itend ; ++it2 ) {
				if ((it1 != it2)and((*it1)<=(*it2))) {
					it1 = H.erase(it1);
					viene_de_un_break = true;
					break;
				}
			}
			if (!(viene_de_un_break)) {
				++it1;
			}
			viene_de_un_break = false;
		}
		return;
	}

	bool IS_UNATE(std::size_t j) const {
		const c_IBFunc itt_b = this->begin();
		const c_IBFunc itt_e = this->end();
		c_IBFunc itt;
		bool_l4v vg = X4v;
		if (j<NE) {
			for(itt=itt_b;itt!=itt_e;++itt){
				vg &= (itt->read4(j));
				if (vg==e4v) return false;
			}
			return true;
		}
		else return false;
	}

	bool IS_UNATE() const {
		const c_IBFunc itt_b = this->begin();
		const c_IBFunc itt_e = this->end();
		c_IBFunc itt;
		CBooleanCube<NE,NS> vg(universe::op);
		for(itt=itt_b;itt!=itt_e;++itt){
			vg &= *itt;
			if (vg.is_input_is_empty()) return false;
		}
		return true;
	}

	void SIMPLIFY(BinateVar & result) {

		CBooleanCover & F = (*this);
		CBooleanCover F1;

		result.is_unate = F.IS_UNATE();
		result.j = F.BINATE_SELECT();

		if (result.is_unate()) {
			F.UNATE_SIMPLIFY();
			return;
		}

		F1.MERGE_WITH_CONTAINMENT(
			((F.cofactor(result.j,false)).SIMPLIFY(result)) && CBooleanCube<NE,NS>(negative_half_space_1_of_n::op),
			((F.cofactor(result.j,true)).SIMPLIFY(result)) && CBooleanCube<NE,NS>(positive_half_space_1_of_n::op)
		);

		if (F.size() >= F1.size()) F = F1;

		return;

	}

// ESSENTIAL INESSENTIAL ELIM1 ELIM2 EG NCOLS MINLOW
    const W_CONTAINED_IN_cp<NE,NS> & EXPAND1(const CBooleanCube<NE,NS> & c,
                                             const CBooleanCover & OFFSET,
                                                   CBooleanCover & W,
                                                   CBooleanCube<NE,NS> & cp) const {
        const CBooleanCover & ONSET = *this;
        CBinCover<NE,NS> BB(c,OFFSET,BB_matrix_t::op);
        CBinCover<NE,NS> CC(c,ONSET,CC_matrix_t::op);
        std::list<unsigned int> LL;
        std::list<unsigned int> RR;
        const unsigned int N = NE+NS;
        std::list<std::size_t> 	X_E;
        std::list<std::size_t> 	X_I;
		CBooleanCube<NE,NS> 	F_I;
        std::list<std::size_t> 	J_I;
		std::list<std::size_t> 	X_i;
        std::map<ulint,listint> QQ;
		ulint clave = c.calculo_de_key();
		const c_IBFunc itF = ONSET.find(clave);
        while (((LL.size()+RR.size()) < N)and(! BB.is_empty())and(! CC.is_empty())) {
			X_E.clear();
            BB.ESSENTIAL(X_E,BB_matrix_t::op);
            LL.insert(LL.end(), X_E.begin(), X_E.end());
            BB.ELIM1(CC,X_E,BB_matrix_t::op);
			J_I.clear();
			CC.MFC(ONSET,BB,LL,RR,J_I);
			if(J_I.empty()) {
                if((!BB.is_empty())and(!CC.is_empty())) {
                    CC.EG(J_I);
                }
			}
			BB.INESSENTIAL(X_i,BB_matrix_t::op);
            J_I.insert(J_I.end(),X_i.begin(),X_i.end());
            RR.insert(RR.end(), J_I.begin(), J_I.end());
            CC.ELIM2_1(BB,J_I,CC_matrix_t::op);
			CC.ELIM2_2(CC_matrix_t::op);
        }
        if((!BB.is_empty())and(CC.is_empty())) BB.MINLOW(LL);
       
		bool vacio = false;
		const c_IBinCover<NE,NS> itCCend = CC.end();
		c_IBinCover<NE,NS> itCC = CC.begin();
        for( ;itCC != itCCend; ++itCC) {
        
            vacio=false;
            for( std::size_t i=0; i < NE+NS ; ++i ) {
                if (*itCC[i]==T2rv) {
                    vacio = true;
                    break;
                }
            }
            if (vacio) W.insert();
        }
        
        const c_lintiterator itLLbegin = LL.begin();
        const c_lintiterator itLLend   = LL.end();
              c_lintiterator itLL      = itLLbegin;
        for(std::size_t i=0;i<NE+NS;++i)
            cp[i]=E4v;
        for( ; itLL != itLLend ; ++itLL )
            cp[*itLL]=X4v;
        for(std::size_t i=0;i<NE+NS;++i)
            if (cp[i]!=X4v)
                cp[i]=c[i];
    }


	
	const CBooleanCover & EXPAND(const CBooleanCover && OFFSET) {
	    const CBooleanCover & ONSET = *this;
	    const   c_IBFunc itend      = ONSET.end();
	    const   c_IBFunc itbegin    = ONSET.begin();
                c_IBFunc it         = itbegin;
		CBooleanCover W;
		CBooleanCube<NE,NS> cp;
	    for(; it != itend ; ++it) {
			W.clear();
			ONSET.EXPAND1(*it,OFFSET,W,cp);
			ONSET.insert(cp);
			ONSET-=W;
	    }
	    return ONSET;
	}
		
	template<std::size_t ME,std::size_t MS>	friend
	std::ostream & operator<<	(
		std::ostream & out,
		const CBooleanCover<ME,MS> & arg)
	{
		if (!(arg.empty())) {
			const	c_IBFunct_t<ME,MS>	itbegin		=	arg.begin();
			const	c_IBFunct_t<ME,MS>	itbegini	=	(++arg.begin());
			const	c_IBFunct_t<ME,MS>	itendi		=	(--arg.end());
					c_IBFunct_t<ME,MS>	it;
			const std::size_t numero_de_cubos = (arg.size()==0?1:arg.size());
			if (numero_de_cubos == 0) {
				out << "[<>]" << std::endl;
			}
			else if (numero_de_cubos == 1) {
				out << "[" << "<";
				out << (itbegin->second);
				out << ",";
				out << (itbegin->first);
				out << ">";
				out << "]" << std::endl;
			}
			else if (numero_de_cubos == 2) {
				out << "["	<< "<" << (itbegin->second) << "," << (itbegin->first) << ">" << std::endl;
				out << " "	<< "<" << (itbegini->second) << "," << (itbegini->first) << ">]" << std::endl;
			}
			else {
				out << "["	<< "<" << (itbegin->second) << "," << (itbegin->first) << ">" << std::endl;
				it = itbegini;
				for( ; it != itendi ; ++it ) {
					out << " " << "<" << (it->second) << "," << (it->first) << ">" << std::endl;
				}
				
				out << " "	<< "<" << (itendi->second) << "," << (itendi->first) << ">]" << std::endl;
			}
		}
		else {
			out << "[<>]" << std::endl;
		}
		return out;
	}
};
		

template<const std::size_t N>
class CBooleanCover<N,0> : public BFunct_t<N,0>
{

	using BCover		=	CBooleanCover<N,0>;
	using BFunc			=	BFunct_t<N,0>;
	using IBFunc		=	IBFunct_t<N,0>;
	using c_IBFunc		=	c_IBFunct_t<N,0>;
	using BCube			=	CBooleanCube<N,0>;
	using BinCube		=	CBinCube<N,0>;
	using BinCubeIn		=	CBinCube<N,0>;
	using BinateVar		=	SBinateVariable<N>;
private:

	
	ulint	m_NTP;

public:
	inline void push_back(BCube arg) {
		BCover & cthis = (*this);
		std::cout << "ENTRADA EN PUSH_BACK CON INSERT" << std::endl;
		std::cout << cthis << std::endl;
		cthis.BFunc::insert(std::make_pair(m_NTP,arg));
		std::cout << cthis << std::endl;
		std::cout << "ENTRADA EN PUSH_BACK CON INSERT" << std::endl;
		++m_NTP;
		return;
	}

	inline void clear() {
		CBooleanCover & cthis = (*this);
		cthis.BFunc::clear();
		m_NTP=0;
		return;
	}

	inline IBFunc erase(IBFunc it){
		if (m_NTP > 0)  --m_NTP;
		return this->BFunc::erase(it);
	}

	inline c_IBFunc erase(c_IBFunc it){
		if (m_NTP > 0)  --m_NTP;
		return this->BFunc::erase(it);
	}

	inline std::size_t size() const {
		return m_NTP;
	}

	CBooleanCover() :
		BFunc(),m_NTP(0)
	{}

	CBooleanCover(const BCover & arg) {
		c_IBFunc		itfrom	=	arg.begin();
		const c_IBFunc	itend	=	arg.end();
		for(;itfrom != itend;++itfrom) {
			this->push_back(*itfrom);
		}
		this->m_NTP = arg.m_NTP;
	}

	CBooleanCover(const CBinCover<N,0> & arg) {
		this->m_NTP = 0;
		c_IBinCover<N,0>			itfrom	=	arg.begin();
		const c_IBinCover<N,0>	itend	=	arg.end();
		for(;itfrom != itend;++itfrom) {
			BCube thiscube;
			for(std::size_t k = 0; k<N;++k) {
				thiscube[k]=((((*itfrom)[k])==T2rv)?(((itfrom->asc_desc)[k])?T4v:F4v):X4v);
			}
			this->push_back(thiscube);
		}
	}

	CBooleanCover(const BCover & arg1,const CBooleanCube<N,0> & arg2,cofactor_t op) :
		CBooleanCover(arg1)
	{
		c_IBFunc		itfrom	=	arg2.begin();
		const c_IBFunc	itend	=	arg2.end();
		for(;itfrom != itend;++itfrom) {
			itfrom->m_cofactor(arg2);
			if (itfrom->is_empty()) {
				itfrom->erase(itfrom);
				--itfrom;
			}
		}
	}

	CBooleanCover(const BCover & arg,std::size_t j,bool posneg,cofactor_t op) :
		CBooleanCover(arg)
	{
		c_IBFunc		itfrom	=	this->begin();
		const c_IBFunc	itend	=	this->end();
		for(;itfrom != itend;++itfrom) {
			itfrom->m_cofactor(j,posneg);
			if (itfrom->is_empty()) {
				itfrom->erase(itfrom);
				--itfrom;
			}
		}
	}

	CBooleanCover(const std::string & file_name) {
		char c_linea[2*(N+0+1)];
		std::ifstream file;
		this->clear();
		this->m_NTP = 0;
		std::size_t k=0;
		file.open(file_name);
		while(
				(!(file.eof()))
					and
				(file.is_open())
			) {
			for(std::size_t i=0 ; i < 2*(N+0+1) ; ++i) {
				c_linea[i] = '\0';
			}
			file.getline(c_linea,2*(N+0+1)-1,'\n');
			const std::string linea(c_linea);
			const BCube cubo(k,linea);
			if (!(cubo.is_empty())) {
				this->push_back(cubo);
				++k;
			}
		}
		file.close();
	}

	CBooleanCover & operator=(const CBooleanCover & arg) {
		clear();
		c_IBFunc		itfrom	=	arg.begin();
		const c_IBFunc	itend	=	arg.end();
		for(;itfrom != itend;++itfrom) {
			this->push_back(*itfrom);
		}
		this->m_NTP = arg.m_NTP;
		return (*this);
	}

	CBooleanCover & operator=(const std::string & file_name) {
		clear();
		this->m_NTP = 0;
		char c_linea[2*(N+0+1)];
		std::size_t k=0;
		std::ifstream file;
		file.open(file_name);
			while(!(file.eof())) {
				for(std::size_t i=0 ; i < 2*(N+0+1) ; ++i) {
					c_linea[i] = '\0';
				}
				file.getline(c_linea,2*(N+0+1)-1,'\n');
				const std::string linea(c_linea);
				const BCube cubo(k,linea);
				this->push_back(cubo);
				++k;
			}
		file.close();
		return (*this);
	}

	void cofactor(const CBooleanCube<N,0> & arg, CBooleanCover & ret) const {
		c_IBFunc		itfrom		=	this->begin();
		const c_IBFunc	itend		=	this->end();
		c_IBFunc		itfromr		=	ret.begin();
		const c_IBFunc	itendr		=	ret.end();
		for(;itfrom != itend;++itfrom,++itfromr) {
			if(itfromr!=itendr) {
				(*itfromr)=itfrom->cofactor(*this);
				if (itfrom->is_empty()) {
					itfromr->erase(itfrom);
					--itfromr;
				}
			}
			else {
				if (!(itfrom->is_empty()))
					ret.push_back(itfrom->cofactor(*this));
			}
		}
		return;
	}
	
	CBooleanCover cofactor(uint v,bool posneg, CBooleanCover & ret) const {
		c_IBFunc		itfrom	=	this->begin();
		const c_IBFunc	itend	=	this->end();
		c_IBFunc		itfromr	=	ret.begin();
		const c_IBFunc	itendr	=	ret.end();

		for(;itfrom != itend;++itfrom,++itfromr) {
			if(itfromr!=itendr) {
				(*itfromr)=itfrom->cofactor(v,posneg);
				if (itfrom->is_empty()) {
					itfrom->erase(itfrom);
					--itfrom;
				}
			}
			else {
				if (!(itfrom->is_empty()))
					ret.push_back(itfrom->cofactor(*this));
			}
		}
		return;
	}

	const CBooleanCover& m_cofactor(uint v,bool posneg) {
		this->m_cofactor(*this,v,posneg,cofactor_t::op);
		return *this;
	}

	CBooleanCover operator && (const BCube & arg) const {
		c_IBFunc			itt		=	this->begin();
		const c_IBFunc		itt_e	=	this->end();
		BCover ret;
		ret.NTP = 0;
		for( ; itt != itt_e ; ++itt) {
			const BCube producto((*itt) and arg);
			const bool empty = producto.is_empty();
			if (!(empty)) ret.push_back(producto);
		}
		return ret;
	}

	CBooleanCover operator || (const CBooleanCover & arg) const {
		c_IBFunc			ita		=	arg.begin();
		const c_IBFunc		ita_e	=	arg.end();
		BCover ret(*this);
		ret.NTP=0;
		for( ; ita != ita_e ; ++ita) {
			ret.push_back(*ita);
		}
		return ret;
	}

	const CBooleanCover & operator |= (const CBooleanCover & arg) {
		c_IBFunc			ita		=	arg.begin();
		const c_IBFunc		ita_e	=	arg.end();
		this->NTP=0;
		for( ; ita != ita_e ; ++ita) {
			this->push_back(*ita);
		}
		return (*this);
	}


	const CBooleanCover & operator &= (const BCube & arg) {
				IBFunc		itt		=	this->begin();
		const c_IBFunc		itt_e	=	this->end();

		while( itt != itt_e ) {
			(*itt)&=arg;
			if (itt->is_empty())
				itt = this->erase(itt);
			else
				++itt;
		}
		return (*this);
	}

	uint UCOMP_SELECT(const CBinCover<N,0> & arg) const {
		uint menor = N;
		uint K;
		uint Q;
		std::vector<uint> i; i.resize(m_NTP);
		for(uint I=0;I<m_NTP;++I) {
			uint temp=0;
			for(uint J=0;J<N;++J) {
				temp+=((arg[I][J])?(1):(0));
			}
			i[I]=temp;
			if (menor > temp) {
				K=I;
				menor = i[K];
			}
		}
		std::list<uint> J;
		for(uint I=0;I<N;++I) {
			if (arg[K][I]) J.push_back(I);
		}
		const std::list<uint>::const_iterator it_J_B = J.begin();
		const std::list<uint>::const_iterator it_J_E = J.end();
		std::list<uint>::const_iterator it_J = J.begin();
		uint mayor = 0;
		for(;it_J!=it_J_E;++it_J){
			uint temp=0;
			for(uint I=0; I<N ;++I){
				temp+=((arg[I][*it_J])?(1):(0));
			}
			if (mayor < temp) {
				Q=(*it_J);
				mayor = temp;
			}
		}
		return Q;
	}

	//COVER_FROM_PERS_MATRIX()

	void PERS_COFACTORS(	CBinCover<N,0> & M0,
							CBinCover<N,0> & M1,
							uint j
						) const
	{
		CBooleanCover F1(*this,j,true,cofactor_t::op);
		CBooleanCover F0(*this,j,false,cofactor_t::op);
		M1 = CBinCover<N,0>(F1,true,PERS_matrix_t::op);
		M0 = CBinCover<N,0>(F0,true,PERS_matrix_t::op);
	}

	friend bool IS_TAUTOLOGY(const CBinCover<N,0> & M) { 
		const uint NTP = M.size();
		for(uint n=0;n<NTP;++n) {
			bool cubo_universo = true;
			for(uint m=0;m<N;++m) {
				if(M[n][m]==T2rv) {
					cubo_universo = false;
					break;
				}
			}
			if (cubo_universo) return true;
		}
		return false;
	}

	void PERS_UNATE_COMPLEMENT( const	CBinCover<N,0> & M,
										CBinCover<N,0> & nM
							  ) const 
	{
		uint rows_of_nM = 0;
		uint columns_of_nM =0;
		bool es_hora_de_irnos = false;
		if (IS_TAUTOLOGY(M)) 
		{
			return;
		}
		else if ((this->begin())==(this->end())) 
		{
			for(uint n=0;n<N;++n) {
				nM[0][n]=F2rv;
			}
			return;
		}
		else if ((++(this->begin()))==(this->end())) 
		{
			const CBooleanCube<N,0> & cubo_morgan=(*(this->begin()));
			BCover result;
			CBooleanCube<N,0> TERM;
			for(uint n=0;n<N;++n) {
				TERM.clear();
				for(uint m=0;m<N;++m) {
					if (n==m) {
						TERM.write(!(cubo_morgan.read4(m)),m);
					}
					else {
						TERM.write(X4v,m);
					}
				}
				result.push_back(TERM);
			}
			nM=CBinCover<N,0>(result);
			return;
		}
		uint j = this->UCOMP_SELECT(M);
		CBinCover<N,0> M0,M1,nM0,nM1;
		this->PERS_COFACTORS(M0,M1,j);
		this->PERS_UNATE_COMPLEMENT(M1,nM1);
		this->PERS_UNATE_COMPLEMENT(M0,nM0);
		nM = nM1 + nM0;
		return;
	}

	CBooleanCover exp_Shannon(std::size_t j) const {
		BCover		pret(*this,j,true,cofactor_t::op);
		BCover		nret(*this,j,false,cofactor_t::op);
		pret &= BCover(j,positive_half_space_1_of_n::op);
		nret &= BCover(j,negative_half_space_1_of_n::op);
		pret |= nret;
		return pret;
	}

	const CBooleanCover& m_exp_Shannon(std::size_t j) {
		*this		= BCover(*this,j,true,cofactor_t::op);
		BCover		nret(*this,j,false,cofactor_t::op);
		(*this) &= BCover(j,positive_half_space_1_of_n::op);
		nret &= BCover(j,negative_half_space_1_of_n::op);
		(*this) |= nret;
		return *this;
	}

	inline const	BCover & REUNIR		(
						BCover & H_0,
						BCover & H_1,
						BCube & x_0,
						BCube & x_1		) {
		BCover & H_2 = (*this);
		H_0 &= x_0;
		H_1 &= x_1;
		H_2 |= H_0;
		H_2 |= H_1;
		return H_2;
	}

	inline
	const BCover& BORRAR_cubo_de_Hx_y_Hy__SI_IGUALES_Y_GUARDAR_en_H2 (
				BCover & H_0,
				BCover & H_1 ) {
		
		CBooleanCover & H_2 = (*this);
				IBFunc	i=H_0.begin();
		const	IBFunc k=H_0.end();
				IBFunc	l=H_1.begin();
		const	IBFunc p=H_1.end();

		bool ha_habido_un_borrado;
		while(i != k) {
			ha_habido_un_borrado = false;
			while(l != p) {
				if ((*i)==(*l)) {
					H_2.push_back(*i);
					i = H_0.erase(i);
					H_1.erase(l);
					l = H_1.begin();
					ha_habido_un_borrado = true;
					break;
				}
				++l;
			}
			if (!(ha_habido_un_borrado)) ++i;
		}

		return H_2;
	}

	inline const BCover& BORRAR_cubo_de_Hx_SI_CONTIENE_a_un_cubo_de_Hy_Y_GUARDAR_en_H2(
					BCover & H_0,
					BCover & H_1) {
		
		BCover & H_2 = (*this);
				IBFunc	i=H_0.begin();
		const	IBFunc k=H_0.end();
				IBFunc	l=H_1.begin();
		const	IBFunc p=H_1.end();
		bool ha_habido_un_borrado_0;
		while(i != k) {
			ha_habido_un_borrado_0 = false;
			while(l != p) {
				if ((*i)>(*l)) {		
					H_2.push_back(*l);
					H_1.erase(l);
					l = H_1.begin();
					break;
				}
				else if ((*i)<(*l)){	
					H_2.push_back(*i);
					H_0.erase(i);
					i = H_0.begin();
					ha_habido_un_borrado_0 = true;
					break;
				}
			}
			if (!(ha_habido_un_borrado_0)) ++i;
		}
		return H_2;
	}

	inline
	const CBooleanCover & MERGE_WITH_IDENTITY (
				BCover & H_0,
				BCover & H_1,
				BCube & x_0,
				BCube & x_1) {
		BCover & H_2 = (*this);
		
		H_2.BORRAR_cubo_de_Hx_y_Hy__SI_IGUALES_Y_GUARDAR_en_H2(H_0,H_1);
		H_2.REUNIR(H_0,H_1,x_0,x_1);
		return H_2;
	}

	inline
	const CBooleanCover & MERGE_WITH_CONTAINMENT (
				BCover & H_0,
				BCover & H_1,
				BCube & x_0,
				BCube & x_1) {
		BCover & H_2 = (*this);

		H_2.BORRAR_cubo_de_Hx_y_Hy__SI_IGUALES_Y_GUARDAR_en_H2(H_0,H_1);

		H_2.BORRAR_cubo_de_Hx_SI_CONTIENE_a_un_cubo_de_Hy_Y_GUARDAR_en_H2(
				H_0,H_1);
		H_2.REUNIR(H_0,H_1,x_0,x_1);
		return H_2;
	}

	inline
	const CBooleanCover & MERGE_WITH_CONTAINMENT (BCover & H,uint j) {
		BCover & H_2 = (*this);
		BCover H_0 = H.cofactor(j,false,cofactor_t::op);
		BCover H_1 = H.cofactor(j,true,cofactor_t::op);
		CBooleanCube<N,0> x_0(j,negative_half_space_1_of_n::op);
		CBooleanCube<N,0> x_1(j,positive_half_space_1_of_n::op);

		H_2.BORRAR_cubo_de_Hx_y_Hy__SI_IGUALES_Y_GUARDAR_en_H2(H_0,H_1);

		H_2.BORRAR_cubo_de_Hx_SI_CONTIENE_a_un_cubo_de_Hy_Y_GUARDAR_en_H2(
				H_0,H_1);
		H_2.REUNIR(H_0,H_1,x_0,x_1);
		return H_2;
	}

	inline	const CBooleanCover & MERGE (
				BCover & H_0,
				BCover & H_1,
				const BCube & x_0,
				const BCube & x_1,
				bool CONTAIN) {
		CBooleanCover & H_2 = (*this);

		H_2.BORRAR_cubo_de_Hx_y_Hy__SI_IGUALES_Y_GUARDAR_en_H2(H_0,H_1);
		if (CONTAIN) {

			H_2.BORRAR_cubo_de_Hx_SI_CONTIENE_a_un_cubo_de_Hy_Y_GUARDAR_en_H2(H_0,H_1);
		}
		H_2.REUNIR(H_0,H_1,x_0,x_1);
		return H_2;
	}

	uint Cuenta_cubos_con_valor(const bool_l4v V,uint j) const {
		const CBooleanCover & C = (*this);
		uint	cuenta = 0;

		c_IBFunc it = C.begin();
		const c_IBFunc itend = C.end();

		for( ; it!= itend ; ++it ) {
			if ((it->read4(j))==V) ++cuenta;
		}

		return cuenta;
	}

	inline static
	uint max_j_min(const std::array<uint,N>& p0,const std::array<uint,N>& p1,std::array<temp_t,N>& vJ) {
		uint ret = (p0[0]<=p1[0])?(p0[0]):(p1[0]);
		uint num_temp;
		for( uint j=1 ; j < N ; ++j ) {
			num_temp = (p0[j]<=p1[j])?(p0[j]):(p1[j]);
			vJ[j].gt_t_0 = (num_temp!=0);
			vJ[j].j = num_temp;
			ret = ((ret >= num_temp)?(ret):(num_temp));
		}
		return ret;
	} 

	inline static
	void RellenaConjuntoDeMinimosDeP0YP1_no_0(const std::array<temp_t,N>& vJ,std::set<uint>& J) {
		for(uint j = 0 ; j < N ; ++j ) 
		{
			if (vJ[j].gt_t_0) J.insert(j);
		}
	} 

	inline static
	uint maximo(const std::set<uint>& J,const std::array<uint,N> & p0,const std::array<uint,N> & p1) {
		std::set<uint>::const_iterator			itJ=	J.begin();
		const std::set<uint>::const_iterator	itendJ=	J.end();

		uint j = (*itJ);
		uint cmax=p0[j]+p1[j];
		uint jmax = j;
		++itJ;

		for( ; itJ != itendJ ; ++itJ ) {
			j = (*itJ);
			const uint cactual = p0[j]+p1[j];
			const bool cmax_menor_que_cactual = (cmax < cactual);
			cmax = ((cmax_menor_que_cactual)?(cactual):(cmax));
			if (cmax_menor_que_cactual) {
				jmax = j;
			}
		}

		return jmax;
	}

	BinateVar BINATE_SELECT() const {
		const CBooleanCover & C = (*this);
		BinateVar ret;

		std::array<uint,N> p0,p1;
		for(uint j=0; j < N ;++j) { 
			p0[j] = C.Cuenta_cubos_con_valor(F4v,j); 
			p1[j] = C.Cuenta_cubos_con_valor(T4v,j); 
		}

		std::array<temp_t,N>	vJ;
		uint					maxjmin = max_j_min(p0,p1,vJ); 
		std::set<uint>			J;
		RellenaConjuntoDeMinimosDeP0YP1_no_0(vJ,J); 

		if (maxjmin==0) { 
			ret.is_unate=true;
			ret.j=0;
		}
		else { 
			ret.is_unate = false;
			ret.j = maximo(J,p0,p1); 
		}

		return ret;
	}

	void UNATE_SIMPLIFY() {
		CBooleanCover & H = (*this);
		bool viene_de_un_break = false;
		IBFunc it1 = H.begin();
		while( it1 != H.end() ) {
			const c_IBFunc itend = H.end();
			for (IBFunc it2 = H.begin(); it2 != itend ; ++it2 ) {
				if ((it1 != it2)and((*it1)<=(*it2))) {
					it1 = H.erase(it1);
					viene_de_un_break = true;
					break;
				}
			}
			if (!(viene_de_un_break)) {
				++it1;
			}
			viene_de_un_break = false;
		}
		return;
	}

	bool IS_UNATE(std::size_t j) const {
		const c_IBFunc itt_b = this->begin();
		const c_IBFunc itt_e = this->end();
		c_IBFunc itt;
		bool_l4v vg = X4v;
		if (j<N) {
			for(itt=itt_b;itt!=itt_e;++itt){
				vg &= (itt->read4(j));
				if (vg==e4v) return false;
			}
			return true;
		}
		else return false;
	}

	bool IS_UNATE() const {
		for(uint j=0;j < N; ++j){
			if (!(this->IS_UNATE(j))) return false;
		}
		return true;
	}

	void SIMPLIFY(BinateVar & result) {

		CBooleanCover & F = (*this);
		CBooleanCover F1;

		result.is_unate = F.IS_UNATE();
		result.j = F.BINATE_SELECT();

		if (result.is_unate()) {
			F.UNATE_SIMPLIFY();
			return;
		}

		F1.MERGE_WITH_CONTAINMENT(
			((F.cofactor(result.j,false)).SIMPLIFY(result)) && CBooleanCube<N,0>(negative_half_space_1_of_n::op),
			((F.cofactor(result.j,true)).SIMPLIFY(result)) && CBooleanCube<N,0>(positive_half_space_1_of_n::op)
		);

		if (F.size() >= F1.size()) F = F1;

		return;

	}

	

	template<const std::size_t ME> friend 
	std::ostream & operator<< (
		std::ostream & out,
			const CBooleanCover<ME,0> & arg)	
	{
		const	c_IBFunct_t<ME,0>	itbegin		=	arg.begin();
		const	c_IBFunct_t<ME,0>	itend		=	arg.end();
		const	c_IBFunct_t<ME,0>	itendi		=	(--arg.end());
		const	c_IBFunct_t<ME,0>	itbegini	=	(++arg.begin());
				c_IBFunct_t<ME,0>	it			=	itbegini;
				c_IBFunct_t<ME,0>	itcount		=	itbegin;
		std::size_t	numero_de_cubos = 0;
		for( ; itcount != itend ; ++itcount) {
			++numero_de_cubos;
		}
		if (numero_de_cubos == 0) {
			out << "[[]]" << std::endl;
		}
		else if (numero_de_cubos == 1) {
			out << "["	<< "<" << (itbegin->second) << ">," << (itbegin->first) << "]" << std::endl;
		}
		else if (numero_de_cubos == 2) {
			out << "["	<< "<" << (itbegin->second) << ">," << (itbegin->first) << " " << std::endl;
			out << " "	<< "<" << (itbegin->second) << ">," << (itbegin->first) << "]" << std::endl;
		}
		else {
			out << "["	<< "<" << (itbegin->second) << ">," << (itbegin->first) << " " << std::endl;
			for( ; it != itendi ; ++it ) {
				out << " " << "<" << (itbegin->second) << ">," << (itbegin->first) << " " << std::endl;
			}
			out << " "	<< "<" << (itbegin->second) << ">," << (itbegin->first) << "]" << std::endl;
		}
		return out;
	}
};

#endif // CBOOLEANCOVER_HPP
