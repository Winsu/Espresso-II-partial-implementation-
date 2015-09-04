#include "CBooleanCube.hpp"
#include "CBooleanCover.hpp"
#include "boolean_l2rv.hpp"
#include "boolean_l3v.hpp"
#include "boolean_l4v.hpp"
#include "recursos.hpp"
#include "auxiliary_functions.hpp"

const std::size_t	NE = 4;
const std::size_t	NS = 2;
const std::size_t	N = 8*(NE+NS+1);

int main()
{
	///*
	std::cout<<"We Create Jc cover"<<std::endl;
	CBooleanCover<NE,NS> Jc(file_name_full_Cover_J);
	std::cout << file_name_full_Cover_J << std::endl;
	std::cout<<"We Create Hc cover"<<std::endl;
	CBooleanCover<NE,NS> Hc(file_name_full_Cover_H);
	std::cout << file_name_full_Cover_H << std::endl;
	//Cover is used for operations
	CBooleanCover<NE,NS> cover;
	//Two universe are created
	CBooleanCube<NE,NS> u(universe::op);
	CBooleanCube<NE,NS> v(universe::op);
	
	//CBooleanCover<NE,NS> Hi(identity_Cover_Hi);//they are cover with identity, they are displayed Hi and Ji
	//CBooleanCover<NE,NS> Ji(identity_Cover_Ji);
	
	// BEGIN __ MERGE_WITH_IDENTITY
	//Hc and Jc are displayed 
	
	std::cout << "Hc =" << std::endl;
 	std::cout << Hc << std::endl;
	
	
	
	std::cout << "Jc =" << std::endl;
 	std::cout << Jc << std::endl;
	
	cover.MERGE_WITH_IDENTITY(Hc,Jc,u,v);
	std::cout << "Cover == Hi.merge_with_indentity.Ji = " << std::endl;
	std::cout << cover << std::endl;
	cover.clear();
	
	cover.MERGE_WITH_IDENTITY(Jc,Hc,u,v);
	std::cout << "Cover == Ji.merge_with_indentity.Hi = " << std::endl;
	std::cout << cover << std::endl;
	
	// END __ MERGE_WITH_IDENTITY 
	
	// BEGIN __ MERGE_WITH_CONTAINMENT 
	
	//Hc and Jc are displayed again without any change
	std::cout << "Hc =" << std::endl;
 	std::cout << Hc << std::endl;
	
	std::cout << "Jc =" << std::endl;
 	std::cout << Jc << std::endl;
	cover.clear();
	

	cover.MERGE_WITH_CONTAINMENT(Hc,Jc,u,v);
	std::cout << "cover == coverH.merge_with_containment.cubiertaJ = " << std::endl;
	std::cout << cover << std::endl;
	cover.clear();
	
	cover.MERGE_WITH_CONTAINMENT(Jc,Hc,u,v);
	std::cout << "cover == coverJ.merge_with_containment.cubiertaH = " << std::endl;
	std::cout << cover << std::endl;
	// END __ MERGE_WITH_CONTAINMENT por Pantalla de las Dos Cubiertas
	
	
	// BEGIN __ COFACTOR
	std::cout<<"Cover_G"<<std::endl;
	CBooleanCover<NE,NS> G(file_name_full_Cover_G);
	
	
	
	std::cout<<"Cover_p"<<std::endl;
	CBooleanCover<NE,NS> P(file_name_full_Cube_p);
	
	
	std::cout<<"Cover_x"<<std::endl;
	CBooleanCover<NE,NS> X(file_name_full_Cube_x);
	
	
	auto p = CBooleanCube<NE,NS>(P.begin()->second);
	
	auto x = CBooleanCube<NE,NS>(X.begin()->second);
	
	std::cout<<"Cover_G"<<std::endl;
	std::cout << G << std::endl;
	std::cout << file_name_full_Cover_G << std::endl;
	
	std::cout<<"Cover_p"<<std::endl;
	std::cout << p << std::endl;
	std::cout << file_name_full_Cube_p << std::endl;
	
	std::cout<<"Cover_x"<<std::endl;
	std::cout << x << std::endl;
	std::cout << file_name_full_Cube_x << std::endl;
	
	
	CBooleanCover<NE,NS> ret;
	std::cout<<"COFACTOR"<<std::endl;
	G.cofactor(p,ret);
	
	
	// END __ COFACTOR
 	
	return 0;
