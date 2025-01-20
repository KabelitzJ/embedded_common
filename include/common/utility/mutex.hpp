#ifndef COMMON_UTILITY_MUTEX_HPP_
#define COMMON_UTILITY_MUTEX_HPP_

#include <concepts>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <common/utility/type.hpp>

namespace common::utility {

template<typename Type>
concept mutex = requires(Type m) {
  { m.lock() } -> std::same_as<void>;
  { m.unlock() } -> std::same_as<void>;
}; // concept mutex

template<mutex Mutex>
class guard {

public:

  using mutex_type = Mutex;

  guard(utility::reference<mutex_type> mutex)
  : _mutex{mutex} {
    _mutex.lock();
  }

  ~guard() {
    _mutex.unlock();
  }

private:

  utility::reference<mutex_type> _mutex;

}; // class guard

struct null_mutex {
  auto lock() -> void { }
  auto unlock() -> void { }
}; // struct null_mutex

class rtos_mutex {

public:

  using handle_type = SemaphoreHandle_t;
  using buffer_type = StaticSemaphore_t;

  rtos_mutex()
  : _handle{xSemaphoreCreateMutexStatic(&_buffer)} {

  }

  ~rtos_mutex() {
    // vSemaphoreDelete(_handle);
  }

  auto lock() const -> void {
    xSemaphoreTake(_handle, portMAX_DELAY);
  }

  auto unlock() const -> void {
    xSemaphoreGive(_handle);
  }

private:

  buffer_type _buffer;
  handle_type _handle;

}; // class rtos_mutex

} // namespace common::utility

#endif // COMMON_UTILITY_MUTEX_HPP_
