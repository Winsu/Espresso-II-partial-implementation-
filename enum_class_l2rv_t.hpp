#ifndef ENUM_CLASS_L2RV_T_HPP
#define ENUM_CLASS_L2RV_T_HPP

class l2rv {
	friend class bool_l2rv;
protected:
	enum class l2rv_t { F , T , e };
private:
	inline static l2rv_t conjuncion_logica(l2rv_t a,l2rv_t b) {
		if ((a==(l2rv_t::e))or(b==(l2rv_t::e))) return (l2rv_t::e);
		else if ((a==l2rv_t::F)or(b==l2rv_t::F)) return (l2rv_t::F);
		else return (l2rv_t::T);
	}

	inline static l2rv_t disyuncion_logica (l2rv_t a,l2rv_t b) {
		if ((a==(l2rv_t::e))or(b==(l2rv_t::e))) return (l2rv_t::e);
		else if ((a==(l2rv_t::T))or(b==(l2rv_t::T))) return (l2rv_t::T);
		else return (l2rv_t::F);
	}

	inline static l2rv_t o_exclusiva_logica(l2rv_t a,l2rv_t b) {
		if ((a==(l2rv_t::e))or(b==(l2rv_t::e))) return (l2rv_t::e);
		else if (a==b) return (l2rv_t::F);
		else return (l2rv_t::T);
	}

	inline static l2rv_t negacion_logica(l2rv_t a) {
		if (a==(l2rv_t::e)) return (l2rv_t::e);
		else return ((a==(l2rv_t::T))?(l2rv_t::F):(l2rv_t::T));
	}

	inline static l2rv_t resta_logica(l2rv_t a,l2rv_t b) {
		if ((a==l2rv_t::e)or(b==l2rv_t::e)) return l2rv_t::F;
		else if (a==l2rv_t::T) return negacion_logica(b);
		else if (b==l2rv_t::F) return a;
		else if (a==b) return l2rv_t::F;
		else return l2rv_t::T;
	}

	inline static bool lt (l2rv_t a,l2rv_t b) {
		if (b==(l2rv_t::e)) return false;
		else if ((a==(l2rv_t::F))and(b!=(l2rv_t::F))) return true;
		else return false;
	}

	inline static bool lt_eq (l2rv_t a,l2rv_t b) {
		if ((a==(l2rv_t::e))or(b==(l2rv_t::e))) return false;
		else if (a==l2rv_t::F) return true;
		else if (a==b) return true;
		else return false;
	}

	inline static bool gt (l2rv_t a,l2rv_t b) {
		if ((b==(l2rv_t::e))or(a==(l2rv_t::e))) return false;
		else if ((b==(l2rv_t::F))and(a!=(l2rv_t::F))) return true;
		else return false;
	}

	inline static bool gt_eq (l2rv_t a,l2rv_t b) {
		if ((b==(l2rv_t::e))or(a==(l2rv_t::e))) return false;
		else if (b==(l2rv_t::F)) return true;
		else if (b==a) return true;
		else return false;
	}

	inline static l2rv_t disyuncion_logica(bool a,l2rv_t b) {
		if (b == (l2rv_t::e)) return (l2rv_t::e);
		else return ((a or (b==(l2rv_t::T)))?(l2rv_t::T):(l2rv_t::F));
	}

	inline static l2rv_t conjuncion_logica(bool a,l2rv_t b) {
		if (b == (l2rv_t::e)) return (l2rv_t::e);
		else return ((a and (b==(l2rv_t::T)))?(l2rv_t::T):(l2rv_t::F));
	}

	inline static l2rv_t o_exclusiva_logica(bool a,l2rv_t b) {
		if (b == (l2rv_t::e)) return (l2rv_t::e);
		else return ((a xor (b==(l2rv_t::T)))?(l2rv_t::T):(l2rv_t::F));
	}

	inline static l2rv_t disyuncion_logica(l2rv_t a,bool b) {
		if (a == l2rv_t::e) return (l2rv_t::e);
		else return (((a==(l2rv_t::T)) or b)?(l2rv_t::T):(l2rv_t::F));
	}

	inline static l2rv_t conjuncion_logica(l2rv_t a,bool b) {
		if (a == (l2rv_t::e)) return (l2rv_t::e);
		else return (((a==(l2rv_t::T)) and b)?(l2rv_t::T):(l2rv_t::F));
	}

	inline static l2rv_t o_exclusiva_logica(l2rv_t a,bool b) {
		if (a == (l2rv_t::e)) return (l2rv_t::e);
		else return (((a==(l2rv_t::T)) xor b)?(l2rv_t::T):(l2rv_t::F));
	}

	inline static bool boolean (l2rv_t a) {
		if ((a==(l2rv_t::F))or(a==(l2rv_t::e))) return false;
		else return true;
	}

private:

	static inline l2rv_t g_F() {return (l2rv_t::F);}
	static inline l2rv_t g_T() {return (l2rv_t::T);}
	static inline l2rv_t g_e() {return (l2rv_t::e);}
};

#endif // ENUM_CLASS_L2RV_T_HPP
