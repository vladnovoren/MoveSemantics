# std::move vs std::forward: differences and reasons for using both

## Introduction
Since C++11, we can use move semantics to avoid unnecessary copying. One of such cases is forwarding objects to containers. Somtimes copying an object on forwarding is too expensive. If our object is temporary or no longer required, we can pass it as `rvalue`. But what if we want to keep it and pass as `lvalue`?

## First steps
Let's write a wrapper function that forwards our objects to some container. At first, we can write something like that:

```
template<typename T>
void Imitator(const T& obj) {
  FUNC_LOG;
  volatile T copy = obj; // imitates of passing obj to some container
}

template<typename T>
void Wrapper(const T& obj) {
  FUNC_LOG;
  Imitator(obj);
}

int main() {
  LogIniter::GetInstance(LogType::GV);
  FUNC_LOG;

  LOG_INT_INIT_BY_VALUE(a, 42);
  Wrapper(a);

  return 0;
}
```
But here we use copy constructor of `T` in `Imitator` function. Let's use move semantics to avoid unnecessary copying:

```
template<typename T>
void Imitator(T&& obj) {
  FUNC_LOG;
  volatile typename my_remove_reference<T>::type copy = my_move(obj);
}

template<typename T>
void Wrapper(T&& obj) {
  FUNC_LOG;
  Imitator(obj);
}

int main() {
  LogIniter::GetInstance(LogType::GV);
  FUNC_LOG;

  LOG_INT_INIT_BY_VALUE(a, 42);
  Wrapper(my_move(a));

  return 0;
}
```
## First problems
Let's compare results:
| copy | my_move |
|:-----------------------------------------------------------------:|:------------------------------------------------------------:|
| <img src="copy.png" alt="Picture 1" width="800"> | <img src="move.png" alt="Picture 2" width="800"> |
| ***Picture 1***<br/>Temporary variable turns into lvalue          | ***Picture 2***<br/>The lvalue is forced to be rvalue        |

As you can notice, in second case value of `a` variable was reset to default (`0`). It happens in move constructor:
```
LogInt::LogInt(LogInt&& other, const std::string& name): value_(other.value_) {
  SetName(name);
  history_ += name_ + "(" + other.history_ + ")";
  other.value_ = 0;
  ILogger::curr_logger_->LogMoveCtor(*this, other);
}
```
This implementation of move constructor realises common important rule: reset moved object to default or invalid state. But what if we want to keep our object?

## Perfect solution
Instead of writing a lot of extra function overloads let's forward objects wisely and use `my_forward` (my implementation of `std::forward`). You can see source code of this function and a couple of calls:

```
template<typename T>
T&& my_forward(typename my_remove_reference<T>::type& obj) {
  return static_cast<T&&>(obj);
}
```
It forwards `rvalue`-s as `rvalue`-s, prohibits forwarding of `rvalue`-s as `lvalue`-s and helps us to forward `lvalue`-s as `lvalue`-s.
Let's rewrite our wrapper using forwarding and check results of it:
```
template<typename T>
void Imitator(T&& obj) {
  FUNC_LOG;
  volatile typename my_remove_reference<T>::type copy = my_forward<T>(obj);
}

template<typename T>
void Wrapper(T&& obj) {
  FUNC_LOG;
  Imitator(my_forward<T>(obj));
}

int main() {
  LogIniter::GetInstance(LogType::GV);
  FUNC_LOG;

  LOG_INT_INIT_BY_VALUE(a, 42);
  Wrapper(a);
  Wrapper(LogInt());

  return 0;
}

```
<img src="forward.png" alt="Picture 3" width="800">
<em><b>Picture 3</b> Forwarding using my_forward (like std::forward)</em>

Here you can see that `a` passed as `lvalue`-reference and copy constructor has been called, but temporary object passed as `rvalue`-reference and move constructor has been called.