#ifndef ENUM_CLASS_L4V_T_HPP
#define ENUM_CLASS_L4V_T_HPP



class l4v {
public:
	friend class bool_l4v;
	friend class l3v;
protected:
	enum class l4v_t { e, F , T , x };
private:
	inline static l4v_t conjuncion_logica(l4v_t a,l4v_t b) {
		if (a==l4v_t::x) return b;
		else if (b==l4v_t::x) return a;
		else if (a==b) return a;
		else return l4v_t::e;
	}	

	inline static l4v_t disyuncion_logica (l4v_t a,l4v_t b) {
		if ((a==l4v_t::x)or(b==l4v_t::x)) return l4v_t::x;
		else if ((a==l4v_t::T)and(b==l4v_t::F)) return l4v_t::x;
		else if ((a==l4v_t::F)and(b==l4v_t::T)) return l4v_t::x;
		else if (a==b) return a;
		else return l4v_t::e;
	}

	inline static l4v_t o_exclusiva_logica(l4v_t a,l4v_t b) {
		if (a==l4v_t::e) return b;
		else if (b==l4v_t::e) return a;
		else if (a==b) return l4v_t::e;
		else if ((a==l4v_t::T)and(b==l4v_t::F)) return l4v_t::x;
		else if ((a==l4v_t::F)and(b==l4v_t::T)) return l4v_t::x;
		else if ((a==l4v_t::x)and(b==l4v_t::F)) return l4v_t::T;
		else if ((a==l4v_t::F)and(b==l4v_t::x)) return l4v_t::T;
		else return l4v_t::F;
	}

	inline static l4v_t negacion_logica(l4v_t a) {
		if (a==l4v_t::x) return l4v_t::e;
		else if (a==l4v_t::e) return l4v_t::x;
		else if (a==l4v_t::T) return l4v_t::F;
		else return l4v_t::T;
	}

	inline static l4v_t resta_logica(l4v_t a,l4v_t b) {
		if (a==l4v_t::e) return l4v_t::e;
		else if (b==l4v_t::x) return l4v_t::e;
		else if (a==l4v_t::x) return negacion_logica(b);
		else if (b==l4v_t::e) return a;
		else if (a==b) return l4v_t::e;
		else return a;
	}

	inline static bool lt (l4v_t a,l4v_t b) {
		if ((a==l4v_t::e)and(b!=l4v_t::e)) return true;
		else if ((a!=l4v_t::x)and(b==l4v_t::x)) return true;
		else return false;
	}

	inline static bool lt_eq (l4v_t a,l4v_t b) {
		if (a==l4v_t::e) return true;
		else if (b==l4v_t::x) return true;
		else if (a==b) return true;
		else return false;
	}

	inline static bool gt (l4v_t a,l4v_t b) {
		if ((a==l4v_t::x)and(b!=l4v_t::x)) return true;
		else if ((a!=l4v_t::e)and(b==l4v_t::e)) return true;
		else return false;
	}

	inline static bool gt_eq (l4v_t a,l4v_t b) {
		if (a==l4v_t::x) return true;
		else if (b==l4v_t::e) return true;
		else if (a==b) return true;
		else return false;
	}

	static inline  l4v_t g_F() {return l4v_t::F;}
	static inline  l4v_t g_T() {return l4v_t::T;}
	static inline  l4v_t g_x() {return l4v_t::x;}
	static inline  l4v_t g_e() {return l4v_t::e;}
};

#endif // ENUM_CLASS_L4V_T_HPP
