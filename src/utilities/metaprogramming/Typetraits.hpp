#ifndef SRC_UTILITIES_METAPROGRAMMING_TYPETRAITS_HPP_
#define SRC_UTILITIES_METAPROGRAMMING_TYPETRAITS_HPP_


namespace Typetraits {

	template<class T> struct remove_cv { typedef T type; };
	template<class T> struct remove_cv<const T> { typedef T type; };
	template<class T> struct remove_cv<volatile T> { typedef T type; };
	template<class T> struct remove_cv<const volatile T> { typedef T type; };

	template<class T> struct remove_const { typedef T type; };
	template<class T> struct remove_const<const T> { typedef T type; };

	template<class T> struct remove_volatile { typedef T type; };
	template<class T> struct remove_volatile<volatile T> { typedef T type; };

	template<bool B, class T, class F> struct conditional { using type = T; };
	template<class T, class F> struct conditional<false, T, F> { using type = F; };

	//Todo: Add more functions as needed, copy from <std::type_traits>
}


#endif /* SRC_UTILITIES_METAPROGRAMMING_TYPETRAITS_HPP_ */
