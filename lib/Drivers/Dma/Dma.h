#pragma once
#include <memory>

class Impl;

class Dma {
 public:
  enum class TransferSize { SIZE_8bit = 0, SIZE_16bit = 1, SIZE_32bit = 2 };
  Dma(TransferSize size);
  ~Dma();
  void ConfigureAndStart(uint32_t src, uint32_t dst, size_t len);
  void SetTransferSize(TransferSize size);
  void SetDreq(int dreq);
  void SetIrq(void (*handler)(void));
  bool isDone() const;
  void AckIrq() const;

 private:
  std::unique_ptr<Impl> _impl;
};
