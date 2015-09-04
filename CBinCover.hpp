#ifndef CBINCOVER_HPP
#define CBINCOVER_HPP

#include "CBooleanCover.hpp"
#include "CBinCube.hpp"

template<const usint NE,const usint NS>
using BinMat_t		= std::map<ulint,CBinCube<NE,NS>>;

template<const usint NE,const usint NS>
using IBinMat_t		= typename BinMat_t<NE,NS>::iterator;

template<const usint NE,const usint NS>
using c_IBinMat_t	= typename BinMat_t<NE,NS>::const_iterator;

template<const std::size_t NE,const std::size_t NS>
class CBinCover : public BinMat_t<NE,NS>
{
	using BCover		=	CBooleanCover<NE,NS>;
	using BFunc			=	BFunct_t<NE,NS>;
	using IBFunc		=	IBFunct_t<NE,NS>;
	using c_IBFunc		=	c_IBFunct_t<NE,NS>;
	using BCube			=	CBooleanCube<NE,NS>;
	using BinCube		=	CBinCube<NE,NS>;
	using BinCubeIn		=	CBinCube<NE,NS>;
	using BinateVar		=	SBinateVariable<NE>;
	using BinCover		=	CBinCover<NE,NS>;
	using IBinCover		=	BinMat_t<NE,NS>::iterator;
	using c_IBinCover	=	BinMat_t<NE,NS>::const_iterator;
private:
	std::array<bool,NE>	asc_desc;
	bool			    is_BB_type;
	bool			    is_CC_type;
	bool			    is_PERS_type;
public:
    inline bool is_empty() const {
        if (this->BinMat<NE,NS>::begin())==(this->BinMat<NE,NS>::end())
            return true;
        else return false;
    }
	inline void push_back(ulint nfila,const BinCube& arg) {
		BinCover & cthis = (*this);
		cthis.BinMat::insert(std::make_pair(nfila,arg));
		return;
	}

	inline void clear() {
		BinCover & cthis = (*this);
		cthis.BinMat::clear();
		return;
	}

	inline IBinCover erase(IBinCover it){
		return this->BinMat::erase(it);
	}

	inline c_IBinCover erase(c_IBinCover it){
		return this->BinMat::erase(it);
	}

	CBinCover() :
		BinMat()
	{}

	CBinCover(const BinCover & arg) {
		c_IBinCover		itfrom	=	arg.begin();
		const c_IBinCover	itend	=	arg.end();
		for(;itfrom != itend;++itfrom) {
			this->push_back(*itfrom);
		}
		this->is_BB_type = arg.is_BB_type;
		this->is_CC_type = arg.is_CC_type;
		this->is_PERS_type = arg.is_PERS_type;
		this->asc_desc = arg.asc_desc;
	}


	CBinCover(const CBooleanCube<NE,NS> & c,const CBooleanCover<NE,NS> & Ri, BB_matrix_t op) {
		c_IBFunc		itfrom	=	Ri.begin();
		const c_IBFunc	itend	=	Ri.end();
		for(;itfrom != itend;++itfrom) {

			this->push_back(CBinCube<NE,NS>(c,*itfrom,BB_matrix_t::op));
		}
		this->is_BB_type = true;
		this->is_CC_type = false;
		this->is_PERS_type = false;
	}

	CBinCover(const CBooleanCube<NE,NS> & c,const CBooleanCover<NE,NS> & Fi, CC_matrix_t op) {
		c_IBFunc		itfrom	=	Fi.begin();
		const c_IBFunc	itend	=	Fi.end();
		for(;itfrom != itend;++itfrom) {
			this->push_back(CBinCube<NE,NS>(c,*itfrom,CC_matrix_t::op));
		}
		this->is_BB_type = false;
		this->is_CC_type = true;
		this->is_PERS_type = false;
	}

	template<const std::size_t NE>
	static std::array<bool,NE> inicializar_a_false(){
		std::array<bool,NE> ret;
		for(std::size_t k=0; k<NE ; ++k) ret[k]=false;
		return ret;
	}

	template<const std::size_t NE>
	static std::array<bool,NE> inicializar_a_true(){
		std::array<bool,NE> ret;
		for(std::size_t k=0; k<NE ; ++k) ret[k]=true;
		return ret;
	}

	CBinCover(const CBooleanCover<NE,NS> & arg , PERS_matrix_t op) {
		static array<bool,NE>	flags_asc_desc_k = BinCover::inicializar_a_false<NE>();
		c_IBFunc		itfrom	=	arg.begin();
		const c_IBFunc	itend	=	arg.end();
		for(;itfrom != itend;++itfrom) {
			this->push_back(CBinCube<NE,NS>(c,*itfrom,PERS_matrix_t::op));
			if (!(flags_asc_desc_k==BinCover::inicializar_true<NE>())) {
				for(usint k=0;k < NE;++k) {
					if ((*itfrom)[k]==T4v) {
						(this->asc_desc)[k]=true;
						flags_asc_desc_k[k]=true;
					}
					else if ((*itfrom)[k]==F4v) {
						(this->asc_desc)[k]=false;
						flags_asc_desc_k[k]=true;
					}
				}
			}
		}
		this->is_BB_type = true;
		this->is_CC_type = false;
		this->is_PERS_type = false;
	}

    uint UCOMP_SELECT() const {
        const CBinCover<NE,NS> & arg(*this);
		uint menor = NE;
		uint K;
		uint Q;
		
		std::vector<uint> i; i.resize(m_NTP);
		for(uint I=0;I<m_NTP;++I) {
			uint temp=0;
			for(uint J=0;J<NE;++J) {
				temp+=((arg[I][J]==T2rv)?(1):(0));
			}
			i[I]=temp;
			if (menor > temp) {
				K=I;
				menor = i[K];
			}
		}
		
		std::map<uint,uint> J;
		uint n=0;
		for(uint I=0;I<NE;++I) {
			if (arg[K][I]==T2rv) {
				J.insert(std::make_pair(n,I));
				++n;
			}
		}
		const auto Jsize = n;
	
		std::vector<uint> mayor;
		mayor.resize(Jsize);
		for(uint l=0; l<Jsize ; ++l)
			mayor[l]=0;
		std::vector<uint> temp;
		temp.resize(Jsize);
		for(uint l=0; l<Jsize ; ++l)
			temp[l]=0;
		const std::list<uint>::const_iterator it_J_B = J.begin();
		const std::list<uint>::const_iterator it_J_E = J.end();
		for(uint I=0 ; I < m_NTP ; ++I) {
			std::list<uint>::const_iterator it_J = J.begin();
			for(;it_J!=it_J_E;++it_J){
				temp[*it_J]+=((arg[I][*it_J]==T2rv));
				if (mayor[*it_J] < temp[*it_J]) {
					mayor[*it_J] = temp[*it_J];
				}
			}
		}

		Q=0;
		uint R;
		n=0;
		for(auto it=mayor.begin();it < mayor.end();++it,++n) {
			if ((*it) > Q) {
				Q = *it;
				R = n;
			}
		}

		return J[R];
	}

	void PERS_COFACTORS(	CBinCover<NE,NS> & M0,
							CBinCover<NE,NS> & M1,
							uint j
						) const {
        const CBinCover & M(*this);
		CBooleanCover F1(M,j,true,cofactor_t::op);
		CBooleanCover F0(M,j,false,cofactor_t::op);
		F1.matrix_of_PERS_MATRIX(M1);
		F0.matrix_of_PERS_MATRIX(M0);
	}

	bool IS_TAUTOLOGY() const {
	    const CBinCover & M(*this);
		const uint NTP = M.m_NTP;
		for(uint n=0;n<NTP;++n) {
			bool cubo_universo = true;
			for(uint m=0;m<NE;++m) {
				if(M[n][m]) {
					cubo_universo = false;
					break;
				}
			}
			if (cubo_universo) return true;
		}
		return false;
	}

    void PERS_UNATE_COMPLEMENT( CBinCover<NE,NS> & nM
							  ) const {
        const CBooleanCover & M(*this);
		uint rows_of_nM = 0;
		uint columns_of_nM =0;
		bool es_hora_de_irnos = false;
		if (M.IS_TAUTOLOGY()) 
		{
			return;
		}
		else if ((this->begin())==(this->end())) 
		{
			for(uint n=0;n<NE;++n) {
				nM[0][n]=false;
			}
			return;
		}
		else if ((++(this->begin()))==(this->end())) 
		{
			const CBooleanCube<NE,NS> & cubo_morgan=(*(this->begin()));
			BCover result;
			CBooleanCube<NE,NS> TERM;
			for(uint n=0;n<NE;++n) {
				TERM.clear();
				for(uint m=0;m<NE;++m) {
					if (n==m) {
						TERM.write(!(cubo_morgan.read4(m)),m);
					}
					else {
						TERM.write(X4v,m);
					}
				}
				result.push_back(TERM);
			}
			result.matrix_of_PERS_MATRIX(nM);
			return;
		}
		uint j = M.UCOMP_SELECT();
		CBinCover<NE,0> M0,M1,nM0,nM1;
		M.PERS_COFACTORS(M0,M1,j);
		M1.PERS_UNATE_COMPLEMENT(M1,nM1);
		M0.PERS_UNATE_COMPLEMENT(M0,nM0);
		nM = nM1;
		nM += nM0;
		return;
	}


    void MINLOW(listint & LL) const {
        const CBinCover & BB = (*this);
        std::array<std::size_t,NE> pares;
        for(int ix = 0 ; ix < NE ; ++ix) pares[ix]=0;
        const c_IBinCover itend = BB.end();
        const c_IBinCover itbegin = BB.begin();
        c_IBinCover it = itbegin;
        std::size_t ix_maximo = 0;
        std::size_t ix_cuenta = 0;
        for( std::size_t ix = 0 ; ix < NE ; ++ix ) {
            for( ; it != itend ; ++it ) {
                if (((*it)[ix]==T2rv)and(LL.count(ix)>0)) (++pares[ix]);
            }
            if (pares[ix]>= ix_cuenta) {
                ix_maximo = ix ;
                ix_cuenta = pares[ix];
            }
        }
        LL.insert(ix_maximo);
    }

    void EG(listint & J_I) const {
        const CBinCover & CC = (*this);
        std::array<std::size_t,NE> pares;
        for(int ix = 0 ; ix < NE ; ++ix) pares[ix]=0;
        const c_IBinCover itend = CC.end();
        const c_IBinCover itbegin = CC.begin();
        c_IBinCover it = itbegin;
        std::size_t ix_maximo = 0;
        std::size_t ix_cuenta = 0;
        for( std::size_t ix = 0 ; ix < NE ; ++ix ) {
            for( ; it != itend ; ++it ) {
                if ((*it)[ix]==T2rv) (++pares[ix]);
            }
            if (pares[ix]>= ix_cuenta) {
                ix_maximo = ix ;
                ix_cuenta = pares[ix];
            }
        }
        J_I.insert(ix_maximo);
    }

	bool J_I_IS_FEASIBLE(const CBinCover & CC,const listint & LL,const listint & RR,const listint & J_I)const {
		const CBinCover & BB = *this;
		listint Z(LL);
		Z.insert(Z.end(),RR.begin(),RR.end());
		Z.insert(Z.end(),J_I.begin(),J_I.end());
		listint nJ_I;
		const c_IBinCover itN = BB.begin();
		for(int k=0 ; k < NE+NS ; ++k) {
			if ((*itN)[k]==e2rv) break;
			const listint::const_iterator itZbegin = Z.begin();
			const listint::const_iterator itZend = Z.end();
			listint::const_iterator itZ = itZbegin;
			for( ; itZ != itZend ; ++itZ ) {
				if ((*itN)[*itZ]== e2rv) break;
				else (k!=(*itZ)) nJ_I.insert(k);
			}
		}
		listint Union_LLyJ_I(LL);
		Union_LLyJ_I.insert(Union_LLyJ_I.end(),nJ_I.begin(),nJ_I.end());
		const c_IBinCover itBBend = BB.end();
		const c_IBinCover itBBbegin = BB.begin();
		c_IBinCover itBB = itBBbegin;
		bool is_feasible = true;
		for( ; itBB != itBBend ; ++itBB ){
			std::size_t cuenta = 0;
			const c_lintiterator itUend = Union_LLyJ_I.end();
			const c_lintiterator itUbegin = Union_LLyJ_I.begin();
			c_lintiterator itU = itUbegin;
			for( ; itU != itUend ; ++itU ) {
				if(itBB->second[*itU]==T2rv) ++cuenta;
			}
			if (cuenta == 0) {
				is_feasible = false;
				break;
			}
		}
		return is_feasible;
	}

	void MFC(const CBooleanCover & F,const CBinCover & BB,const listint & LL,const listint & RR,listint & J_I)const {
		const CBinCover & CC = *this;
		const bool is_feasible = BB.J_I_IS_FEASIBLE(CC,LL,RR,J_I);
		if (is_feasible) {
		 
            const c_IBinCover itCCend = CC.end();
            const c_IBinCover itCCbegin = CC.begin();
            c_IBinCover itCC = itCCbegin;
            std::list<std::pair<c_IBinCover,setint>> QQ;
            std::list<std::pair<c_IBinCover,std::set<c_IBinCover>>> KK;
			for( ; itCC != itCCend ; ++itCC ) {
				std::pair<c_IBinCover,sintint> par = make_pair(itCC,sintint());
				for( std::size_t k = 0 ; k < NE+NS ; ++k ) {
					if ((*itCC)[k]==T2rv) par.second.insert(k);
				}
				QQ.insert(par);
			}
          
			const decltype(QQ)::const_iterator itQQbegin = QQ.begin();
			const decltype(QQ)::const_iterator itQQend = QQ.end();
			decltype(QQ)::const_iterator itQQ = itQQbegin;
			for( ; itQQ != itQQend ; ++itQQ) {
				decltype(QQ)::const_iterator itQQs = itQQbegin;
                KK.insert(std::make_pair(itQQ,std::set<decltype(itQQs)>());
				for( ; itQQs != itQQend ; ++itQQs) {
					for(unsigned l=0; l<NE+NS ; ++l) {
                        if (itQQ != itQQs) {
                            if((itQQ->second.count(itQQs.second[l]))<1) {
                                break;
                            }
                        }
                        else break;
					}
					KK.second.insert(itQQs);
				}
			}
		
			std::list<std::pair<c_IBinCover,std::set<c_IBinCover>>> KK_mayores;
			const std::list<std::pair<c_IBinCover,std::set<c_IBinCover>>>::const_iterator itKKbegin = KK.begin();
			const std::list<std::pair<c_IBinCover,std::set<c_IBinCover>>>::const_iterator itKKend = KK.end();
			std::list<std::pair<c_IBinCover,std::set<c_IBinCover>>>::const_iterator itKK = itKKbegin;
			std::multimap<std::size_t,decltype(itKK)> argmax;
			std::size_t maximo = 0;
			for(;itKK!=itKKend;++itKK) {
                const std::size_t cuenta = itKK.second.size();
                if(cuenta > maximo) {
                    maximo=cuenta;
                    argmax.insert(std::make_pair(cuenta,itKK));
                }
                std::remove_if(argmax.begin(),argmax.end(),[]()(argmax.first < maximo));
            }
         
            const std::set<c_IBinCover,sint>::const_iterator itQQend = QQ.end();
            const std::set<c_IBinCover,sint>::const_iterator itQQbegin = QQ.begin();
            std::set<c_IBinCover,sint>::const_iterator itQQ = itQQbegin;
            std::multimap<std::size_t,decltype(itQQ)> argmin;
            std::size_t minimo = NE+NS;
            std::
            for(;itQQ!=itQQend;++itQQ) {
                const std::size_t cuenta = itQQ->second.size();
                const decltype(argmax)::const_iterator itmaxend = argmax.end();
                const decltype(argmax)::const_iterator itmaxbegin = argmax.begin();
                decltype(argmax)::const_iterator itmax = itmaxbegin;
                bool esta_dentro = false;
                for( ; itmax != itmaxend ; ++itmax ) {
                    if (itmax->second==itQQ->first) {
                        esta_dentro = true;
                        break;
                    }
                }
                if(esta_dentro) {
                    if(minimo >= cuenta) {
                        minimo=cuenta;
                        argmin.insert(std::make_pair(cuenta,itQQ));
                    }
                    std::remove_if(argmin.begin(),argmin.end(),[]()(argmin.first > minimo));
                }
            }
          
			c_IBinCover itKK_elegido= KK.find(argmin.begin()->first);
			const std::set<c_IBinCube>::const_iterator itKKCend = itKK_elegido->second.end();
			const std::set<c_IBinCube>::const_iterator itKKCbegin = itKK_elegido->second.begin();
			std::set<c_IBinCube>::const_iterator itKKC = itKKCbegin;
			for( ;itKKC!=itKKCend ; ++itKKC) {
				W.insert(F.find(F[itKKC->first]));
			}
            const setint el_conjunto_de_variables_del_cubo_elegido = argmin.begin()->second;
            J_I.insert(J_I.end(),
                       el_conjunto_de_variables_del_cubo_elegido.begin(),
                       el_conjunto_de_variables_del_cubo_elegido.end());
            return;
		}
		else return;
	}

	void ELIM2_2(const CC_matrix_t op) {
		CBinCover & CC = *this;
		const iterador itbegin = CC.begin();
		const iterador itend = CC.end();
		iterador it = itbegin;

		for( ; it != itend ; ++it) {
			for( int k=0 ; k<NE+NS; ++k ) {
				if((*it)[k]==e2rv) break;
				else if((*it)[k]==T2rv) break;
			}
			CC.erase(it);
			--it;
		}
	}

	void ELIM2_1(CBinCover & BB,const std::list<std::size_t> & Z,const CC_matrix_t op) {
		CBinCover & CC = *this;
		using iterador = list<std::size_t>::const_iterator;

		const iterador itbegin = X_E.begin();
		const iterador itend = X_E.end();

		iterador it = itbegin;
		for( ; it != itend ; ++it) {
			const IBinCover itZbegin = Z.begin();
			const IBinCover itZend = Z.end();
			IBinCover itZ = itZbegin;
			for( ; itZ != itZend ; ++itZ) {
				const iterador itCCbegin = CC.begin();
				const iterador itCCend = CC.end();
				const iterador itBBbegin = BB.begin();
				const iterador itBBend = BB.end();
				iterador itCC = itCCbegin;
				iterador itBB = itBBbegin;
				for( ; (itCC != itCCend) and (itBB != itBBend) ; ++itCC,++itBB ) {
					(*itCC)[*itZ]=e2rv;
					(*itBB)[*itZ]=e2rv;
				}
			}
		}
	}

	void INESSENTIAL(std::list<int> & X_i,const BB_matrix_t op) const {
		CBinCover & BB = *this;
		const	c_IBinCover itbegin = BB.begin();
		const	c_IBinCover itend 	= BB.end();
				c_IBinCover it		= itbegin;
		std::array<int,NE+NS> cuenta;
		for( ; it != itend ; ++it ) {
			for( int k = 0 ; k < NE ; ++k ) {
				if ((*it)[k]==e2rv) {cuenta[k]=-1; break;}
				if ((*it)[k]==T2rv)	{++cuenta[k];}
			}
		}
		for( int k = 0 ; k < NE ; ++k )
			if (cuenta[k]==0) X_i.insert(k);
	}

	void ESSENTIAL(std::list<int> & X_E,const BB_matrix_t op) const {
		CBinCover & BB = *this;
		const	c_IBinCover itbegin = BB.begin();
		const	c_IBinCover itend 	= BB.end();
				c_IBinCover it		= itbegin;
		for( ; it != itend ; ++it ) {
			int cuenta_de_1s = 0;
			int K;
			bool es_primer_1 = true;
			for( int k = 0 ; (k < NE)and(es_primer_1) ; ++k ) {
				if ((*it)[k]==T2rv)	{
					++cuenta_de_1s;
				}
				if (es_primer_1 and (cuenta_de_1s==1)) {
					K = k;
					es_primer_1 = false;
				}
				if (cuenta_de_1s>1) break;
			}
			if(cuenta_de_1s!=0) {
				X_E.insert(K)
			}
		}
	}

	void ELIM1(CBinCover & CC,const list<std::size_t> & X_E,const BB_matrix_t op) {
		CBinCover & BB = *this;
		using iterador = list<std::size_t>::const_iterator;

		const iterador itbegin = X_E.begin();
		const iterador itend = X_E.end();

		iterador it = itbegin;
		for( ; it != itend ; ++it) {
			const IBinCover itCCbegin = CC.begin();
			const IBinCover itCCend = CC.end();
			IBinCover itCC = itCCbegin;
			for( ; itCC != itCCend ; ++itCC) {
				if (itCC->second[*it]==T2rv) {
					CC.erase(itCC);
					--itCC;
				}
			}
			for( itCC = itCCbegin ; itCC != itCCend ; ++itCC) {
					(*itCC)[*it] = e2rv;
			}
		}

		iterador it = itbegin;
		for( ; it != itend ; ++it) {
			const IBinCover itBBbegin = BB.begin();
			const IBinCover itBBend = BB.end();
			IBinCover itBB = itBBbegin;
			for( ; itBB != itBBend ; ++itBB) {
				if (itBB->second[*it]==T2rv) {
					CC.erase(itBB);
					--itBB;
				}
			}
			for( itBB = itBBbegin ; itBB != itBBend ; ++itBB) {
					(*itBB)[*it] = e2rv;
			}
		}


	}


r

	friend std::ostream & operator<<	(
			std::ostream & out,
			const CBinCover<NE,NS> & arg)	{
		const	c_IBFunct_t<NE,NS>	itbegin		=	arg.begin();
		const	c_IBFunct_t<NE,NS>	itend		=	arg.end();
		const	c_IBFunct_t<NE,NS>	itendi		=	(--arg.end());
		const	c_IBFunct_t<NE,NS>	itbegini	=	(++arg.begin());
				c_IBFunct_t<NE,NS>	it			=	itbegini;
				c_IBFunct_t<NE,NS>	itcount		=	itbegin;
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

#endif // CBINCOVER_HPP
