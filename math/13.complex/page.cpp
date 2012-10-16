template<typename data_type>
struct Complex {
	data_type x, y;
	Complex(data_type x = data_type(), data_type y = data_type()) : x(x), y(y) {};
	const data_type& real() const { return x; }
	const data_type& imag() const { return y; }
	Complex operator+ (const Complex& o) const {
		return Complex(real() + o.real(), imag() + o.imag());
	}
	Complex operator* (const Complex& o) const {
		return Complex(real() * o.real() - imag() * o.imag(), real() * o.imag() + imag() * o.real());
	}
	Complex operator- (const Complex& o) const {
		return Complex(real() - o.real(), imag() - o.imag());
	}
	Complex operator/ (const data_type& o) const {
		return Complex(real() / o, imag() / o);
	}
	data_type norm() const {
		return real() * real() + imag() * imag();
	}
	Complex conj() const {
		return Complex(real(), -imag());
	}
	void out() {
		cout << real() << "+" << imag() << "i" << endl;
	}
};

