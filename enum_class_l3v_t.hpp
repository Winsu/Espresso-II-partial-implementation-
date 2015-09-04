#ifndef ENUM_CLASS_L3V_T_HPP
#define ENUM_CLASS_L3V_T_HPP

#include "enum_class_l4v_t.hpp"

class l3v {
public:
	friend class bool_l3v;
protected:
	enum class l3v_t { F , T , x };
private:
	inline static l3v_t conjuncion_logica(l3v_t a,l3v_t b) {
		if ((a==l3v_t::x)or(b==l3v_t::x)) return l3v_t::x;
		else if ((a==l3v_t::F)or(b==l3v_t::F)) return l3v_t::F;
		else return l3v_t::T;
	}

	inline static l3v_t disyuncion_logica (l3v_t a,l3v_t b) {
		if ((a==l3v_t::x)or(b==l3v_t::x)) return l3v_t::x;
		else if ((a==l3v_t::T)or(b==l3v_t::T)) return l3v_t::T;
		else return l3v_t::F;
	}

	inline static l3v_t o_exclusiva_logica(l3v_t a,l3v_t b) {
		if ((a==l3v_t::x)or(b==l3v_t::x)) return l3v_t::x;
		else if (a==b) return l3v_t::F;
		else return l3v_t::T;
	}

	inline static l3v_t negacion_logica(l3v_t a) {
		if (a==l3v_t::x) return l3v_t::x;
		else return ((a==l3v_t::T)?l3v_t::F:l3v_t::T);
	}

	inline static bool lt (l3v_t a,l3v_t b) {
		if ((a==l3v_t::F)and(b!=l3v_t::F)) return true;
		else if ((a==l3v_t::T)and(b==l3v_t::x)) return true;
		else return false;
	}

	inline static bool lt_eq (l3v_t a,l3v_t b) {
		if (a==l3v_t::F) return true;
		else if ((a==l3v_t::T)and(b!=l3v_t::F)) return true;
		else if ((a==l3v_t::x)and(b==l3v_t::x)) return true;
		else return false;
	}

	inline static bool gt (l3v_t a,l3v_t b) {
		if ((b==l3v_t::F)and(a!=l3v_t::F)) return true;
		else if ((b==l3v_t::T)and(a==l3v_t::x)) return true;
		else return false;
	}

	inline static bool gt_eq (l3v_t a,l3v_t b) {
		if (b==l3v_t::F) return true;
		else if ((b==l3v_t::T)and(a!=l3v_t::F)) return true;
		else if ((b==l3v_t::x)and(a==l3v_t::x)) return true;
		else return false;
	}

	inline static l3v_t disyuncion_logica(bool a,l3v_t b) {
		if (b == l3v_t::x) return l3v_t::x;
		else return ((a or (b==l3v_t::T))?l3v_t::T:l3v_t::F);
	}

	inline static l3v_t conjuncion_logica(bool a,l3v_t b) {
		if (b == l3v_t::x) return l3v_t::x;
		else return ((a and (b==l3v_t::T))?l3v_t::T:l3v_t::F);
	}

	inline static l3v_t o_exclusiva_logica(bool a,l3v_t b) {
		if (b == l3v_t::x) return l3v_t::x;
		else return ((a xor (b==l3v_t::T))?l3v_t::T:l3v_t::F);
	}

	inline static l3v_t disyuncion_logica(l3v_t a,bool b) {
		if (a == l3v_t::x) return l3v_t::x;
		else return (((a==l3v_t::T) or b)?l3v_t::T:l3v_t::F);
	}

	inline static l3v_t conjuncion_logica(l3v_t a,bool b) {
		if (a == l3v_t::x) return l3v_t::x;
		else return (((a==l3v_t::T) and b)?l3v_t::T:l3v_t::F);
	}

	inline static l3v_t o_exclusiva_logica(l3v_t a,bool b) {
		if (a == l3v_t::x) return l3v_t::x;
		else return (((a==l3v_t::T) xor b)?l3v_t::T:l3v_t::F);
	}

	inline static l3v_t resta_logica(l3v_t a,l3v_t b) {
		if (a==l3v_t::x) return negacion_logica(b);
		else if (b==l3v_t::x) return a;
		else if (a==b) return l3v_t::F;
		else return l3v_t::T;
	}

	inline static l3v_t g_F() {return l3v_t::F;}
	inline static l3v_t g_T() {return l3v_t::T;}
	inline static l3v_t g_x() {return l3v_t::x;}
};

#endif // ENUM_CLASS_L3V_T_HPP
