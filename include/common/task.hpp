#ifndef COMMON_TASK_HPP_
#define COMMON_TASK_HPP_

#include <type_traits>
#include <string_view>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <common/utility/enum.hpp>

#include <common/units/time.hpp>
#include <common/units/data.hpp>

namespace common {

class task {

public:

  using parameters = void*;
  using handle_type = TaskHandle_t;

  enum class priority : std::uint8_t {
    idle = 0,
    low = 1,
    medium = 3,
    high = 5
  }; // enum class priority

  template<typename Callable>
  requires (std::is_invocable_r_v<void, Callable, parameters>)
  task(std::string_view name, Callable&& callable, units::byte stack_size, priority priority, parameters parameters = nullptr) {
    xTaskCreate(std::forward<Callable>(callable), name.data(), stack_size, parameters, common::utility::to_underlying(priority), &_handle);
  }

  static auto delay(const common::units::seconds& delay) -> void;

  template<typename Callable>
  requires (std::is_invocable_r_v<void, Callable, parameters>)
  static auto create(std::string_view name, Callable&& callable, units::byte stack_size, priority priority, parameters parameters = nullptr) {
    auto handle = handle_type{};
    xTaskCreate(std::forward<Callable>(callable), name.data(), stack_size, parameters, common::utility::to_underlying(priority), &handle);
  }

  auto handle() const noexcept -> handle_type;

private:

  handle_type _handle;

}; // class task

} // namespace common

#endif // COMMON_TASK_HPP_
