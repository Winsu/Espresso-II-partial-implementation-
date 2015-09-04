#ifndef BOOLEAN_FUNCTION_NOT_FULLY_SPECIFIED__HPP
#define BOOLEAN_FUNCTION_NOT_FULLY_SPECIFIED__HPP

#include "parsers_so.hpp"

template<const std::size_t NE>
struct ff_t {
	CBooleanCover<NE,0>	ONSET;
	CBooleanCover<NE,0>	DCSET;
	CBooleanCover<NE,0>	OFFSET;
};

template<const std::size_t NE,const std::size_t NS>
using funcs_FS_from_NFS = std::array<ff_t<NE>,NS>;

template<const std::size_t NE,const std::size_t NS>
struct FF_t : public funcs_FS_from_NFS {};

void FF_t(const CBooleanCover<NE,NS>& F,const CBooleanCover<NE,NS>& D) 
{
    const   c_IBFunc itFend         = F.end();
    const   c_IBFunc itFbegin       = F.begin();
            c_IBFunc itF            = itFbegin;
    const   c_IBFunc itDend         = D.end();
    const   c_IBFunc itDbegin       = D.begin();
            c_IBFunc itD            = itDbegin;
    while((itF!=itFend)and(itD!=itDend)) {
        for(unsigned i=0 ; i < NS ; ++i){
            if (*itF.read2(i)==T4v) {
                (*this)[i].ONSET.push_back(*itF);
            }
            else if (*itD.read2(i)==T4v) {
                (*this)[i].DCSET.push_back(*itD);
            }
        }
        if(itF != itFend) ++itF;
        if(itD != itDend) ++itD;
    }
}
#endif //BOOLEAN_FUNCTION_NOT_FULLY_SPECIFIED__HPP
