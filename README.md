# std::move vs std::forward: differences and puposes to use both

## Introduction
Since C++11, we can use move semantics to avoid unnecessary copying. One of such cases is forwarding objects to containers. Somtimes copying an object on forwarding is too expensive. If our object is temporary or no longer required, we can pass it as `rvalue`. But what if we want to keep it and pass as `lvalue`?

## Perfect forwarding
Let's write a wrapper function that forwards our objects to some container. If we want to pass out object as `lvalue`, we should write something like that:

```
template<typename T>
void Imitator(const T& obj) {
  volatile T copy = obj;
}

template<typename T>
void Wrapper(const T& obj) {
  Imitator(obj);
}
```