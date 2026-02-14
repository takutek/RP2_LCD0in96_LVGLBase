#pragma once

class Screen {
 public:
  Screen() = default;
  virtual ~Screen() = default;

  Screen(const Screen&) = delete;
  Screen& operator=(const Screen&) = delete;
  Screen(Screen&&) = delete;
  Screen& operator=(Screen&&) = delete;

  virtual void Create() = 0;
  virtual void Destroy() = 0;
  virtual void Update(void* data) = 0;
};