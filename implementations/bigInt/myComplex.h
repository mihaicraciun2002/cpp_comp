namespace myfunc {
    template <typename T>
    class complex;
    template <typename T>
    class complex  {
        public:
        T real = 0.0;
        T imag = 0.0;
        complex();
        complex(const T& real, const T& imag);
        complex<T>(const complex& oth);
        complex<T>(const T& oth);

        void operator += (const complex& oth);
        void operator -= (const complex& oth);
        void operator *= (const complex& oth);
        void operator = (const complex& oth);

        void operator += (const T& oth);
        void operator -= (const T& oth);
        void operator *= (const T& oth);
        void operator = (const T &oth);

        complex operator + (const complex& oth);
        complex operator - (const complex& oth);
        complex operator * (const complex& oth);

    };
    template <typename T>
    complex <T> operator - (const complex <T>& oth);
    template <typename T>
    complex <T> operator * (const T& me, const complex <T>& oth);
    template <typename T>
    complex <T> operator * (const complex <T>& oth, const T& me);
    template <typename T>
    complex <T> operator - (const T& me, const complex <T>& oth);
    template <typename T>
    complex <T> operator - (const complex <T>& oth, const T& me);
    template <typename T>
    complex <T> operator + (const T& me, const complex <T>& oth);
    template <typename T>
    complex <T> operator + (const complex <T>& oth, const T& me);

}

template <typename T>
myfunc::complex<T>::complex() {}
template <typename T>
myfunc::complex<T>::complex(const T& real, const T& imag)  {
    this -> real = real;
    this -> imag = imag;
}
template <typename T>
myfunc::complex<T>::complex(const complex& oth)  {
    this -> real = oth.real;
    this -> imag = oth.imag;
}
template <typename T>
myfunc::complex<T>::complex(const T& oth)  {
    this -> real = oth;
    this -> imag = 0;
}
template <typename T>
void myfunc::complex<T>::operator *= (const complex& oth)  {
    const T newReal = this -> real * oth.real - this -> imag * oth.imag;
    const T newImag = this -> imag * oth.real + oth.imag * this -> real;
    this -> real = newReal;
    this -> imag = newImag;
}
template <typename T>
void myfunc::complex<T>::operator += (const complex& oth)  {
    this -> real += oth.real;
    this -> imag += oth.imag;
}
template <typename T>
void myfunc::complex<T>::operator -= (const complex& oth)  {
    this -> real -= oth.real;
    this -> imag -= oth.imag;
}
template <typename T>
void myfunc::complex<T>::operator = (const complex& oth)  {
    this -> real = oth.real;
    this -> imag = oth.imag;
}
template <typename T>
myfunc::complex<T> myfunc::complex<T>::operator + (const complex& oth)  {
    complex ans = *this;
    ans += oth;
    return ans;
}
template <typename T>
myfunc::complex<T> myfunc::complex<T>::operator - (const complex& oth)  {
    complex ans = *this;
    ans -= oth;
    return ans;
}
template <typename T>
myfunc::complex<T> myfunc::complex<T>::operator * (const complex& oth)  {
    complex ans = *this;
    ans *= oth;
    return ans;
}

template <typename T>
void myfunc::complex<T>::operator += (const T& oth)  {
    this -> real += oth;
}
template <typename T>
void myfunc::complex<T>::operator -= (const T& oth)  {
    this -> real -= oth;
}
template <typename T>
void myfunc::complex<T>::operator *= (const T& oth)  {
    this -> real *= oth;
    this -> imag *= oth;
}
template <typename T>
void myfunc::complex<T>::operator = (const T &oth)  {
    this -> real = oth;
    this -> imag = 0;
}
template <typename T>
myfunc::complex<T> myfunc::operator - (const myfunc::complex<T>& oth)  {
    return myfunc::complex(-oth.real, -oth.imag);
}
template <typename T>
myfunc::complex<T> myfunc::operator * (const T& me, const myfunc::complex<T>& oth)  {
    return myfunc::complex(oth.real * me, oth.imag * me);
}
template <typename T>
myfunc::complex<T> myfunc::operator * (const myfunc::complex<T>& oth, const T& me)  {
    return myfunc::complex(oth.real * me, oth.imag * me);
}
template <typename T>
myfunc::complex<T> myfunc::operator - (const T& me, const myfunc::complex<T>& oth)  {
    return myfunc::complex(me - oth.real, -oth.imag);
}
template <typename T>
myfunc::complex<T> myfunc::operator - (const myfunc::complex<T>& oth, const T& me)  {
    return myfunc::complex(oth.real - me, oth.imag);
}
template <typename T>
myfunc::complex<T> myfunc::operator + (const T& me, const myfunc::complex<T>& oth)  {
    return myfunc::complex(me + oth.real, oth.imag);
}
template <typename T>
myfunc::complex<T> myfunc::operator + (const myfunc::complex<T>& oth, const T& me)  {
    return myfunc::complex(me + oth.real, oth.imag);
}
