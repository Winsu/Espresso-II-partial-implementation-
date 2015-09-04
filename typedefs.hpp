#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include <array>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>

typedef		unsigned char				uchar;
typedef		signed char					schar;// o preferentemente char
typedef		unsigned char				uchint;
typedef		signed char					schint;
typedef		unsigned short int			usint;
typedef		signed short int			ssint;
typedef		unsigned int				uint;
typedef		signed int					sint;// o preferentemente int
typedef		unsigned long int			ulint;
typedef		signed long int				slint;
typedef		unsigned long long int		ullint;
typedef		signed long long int		sllint;
typedef		char*						cstr_t;
typedef		char**						cstr_cstrs_t;

enum class or_t							{ op };
enum class nor_t						{ op };
enum class and_t						{ op };
enum class nand_t						{ op };
enum class xor_t						{ op };
enum class xnor_t						{ op };
enum class not_t						{ op };

enum class diff_t						{ op };

enum class cofactor_t					{ op };
enum class if_t							{ op };
enum class cons_t						{ op };
enum class universe						{ op };
enum class universe_1_de_m				{ op };
enum class positive_half_space_1_of_n	{ op };
enum class negative_half_space_1_of_n	{ op };
enum class BB_matrix_t					{ op };
enum class CC_matrix_t					{ op };
enum class PERS_matrix_t				{ op };
enum class BB_row_t						{ op };
enum class CC_row_t						{ op };
enum class PERS_row_t					{ op };
enum class cubeset_t {DC,ON,OFF};
const ulint max_long_cstr = 1050;

const char nullchar = '\0';

template<const std::size_t NS>
using B2Term_t = std::array<bool,NS>;

typedef long long unsigned int Elem_Z_t;

#endif // TYPEDEFS_HPP
