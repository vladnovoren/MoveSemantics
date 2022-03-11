#ifndef MOVE_SEMANTICS_HPP
#define MOVE_SEMANTICS_HPP

template<typename T>
struct my_remove_reference {
  using type = T;
};

template<typename T>
struct my_remove_reference<T&> {
  using type = T;
};

template<typename T>
struct my_remove_reference<T&&> {
  using type = T;
};

template<typename T>
typename my_remove_reference<T>::type&& my_move(T&& obj) {
  return static_cast<typename my_remove_reference<T>::type&&>(obj);
}

template<typename T>
T&& my_forward(typename my_remove_reference<T>::type& obj) {
  return static_cast<T&&>(obj);
}

#endif /* move_semantics.hpp */
