#ifndef LOCATOR_H
#define LOCATOR_H

template<typename T>
class Locator {
public:
  static T* get() { return instance_; }

  static void reset(T* service)
  {
    instance_ = service;
  }

private:
  static T* instance_;
};

template<typename T>
T* Locator<T>::instance_ = nullptr;

#endif // LOCATOR_H
