#include <common/task.hpp>

namespace common {

auto task::delay(const common::units::seconds& delay) -> void {
  vTaskDelay(pdMS_TO_TICKS(common::units::quantity_cast<common::units::milli_seconds>(delay)));
}

auto task::handle() const noexcept -> handle_type {
  return _handle;
}

} // namespace common
