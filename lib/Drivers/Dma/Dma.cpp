#include "Drivers/Dma/Dma.h"
#include "hardware/dma.h"
#include "hardware/irq.h"

class Impl {
public:
    Impl(Dma::TransferSize size)
    {
        _channel = dma_claim_unused_channel(true);
        _config = dma_channel_get_default_config(_channel);
        SetTransferSize(size);
    }
    ~Impl()
    {
        dma_channel_unclaim(_channel);
        irq_set_enabled(_irqnum, false);
    }
    void ConfigureAndStart(uint32_t src, uint32_t dst, size_t len)
    {
        dma_channel_configure(_channel, &_config, reinterpret_cast<void*>(dst), reinterpret_cast<const void*>(src), len, true);
    }
    void SetTransferSize(Dma::TransferSize size)
    {
        dma_channel_transfer_size sz;
        switch (size)
        {
        case Dma::TransferSize::SIZE_8bit:
            sz = DMA_SIZE_8;
            break;
        case Dma::TransferSize::SIZE_16bit:
            sz = DMA_SIZE_16;
            break;
        case Dma::TransferSize::SIZE_32bit:
            sz = DMA_SIZE_32;
            break;
        default:
            sz = DMA_SIZE_8;
            break;
        }
        channel_config_set_transfer_data_size(&_config, sz);
    }
    void SetDreq(uint dreq)
    {
        channel_config_set_dreq(&_config, dreq);
    }
    void SetIrq(uint irqnum, irq_handler_t handler)
    {
        _irqnum = irqnum;
        dma_channel_set_irq0_enabled(_channel, true);
        irq_set_exclusive_handler(_irqnum, handler);
        irq_set_enabled(_irqnum, true);
    }
    bool isDone() const
    {
        return dma_channel_get_irq0_status(_channel);
    }
    void AckIrq() const
    {
        dma_channel_acknowledge_irq0(_channel);
    }
private:
    uint _channel;
    uint _irqnum;
    dma_channel_config _config;
};

Dma::Dma(TransferSize size)
{
    _impl = std::make_unique<Impl>(size);
}

Dma::~Dma() = default;

void Dma::ConfigureAndStart(uint32_t src, uint32_t dst, size_t len)
{
    _impl->ConfigureAndStart(src, dst, len);
}

void Dma::SetTransferSize(TransferSize size)
{
    _impl->SetTransferSize(size);
}

void Dma::SetDreq(int dreq)
{
    _impl->SetDreq(dreq);
}

void Dma::SetIrq(void (*handler)(void))
{
    _impl->SetIrq(DMA_IRQ_0, handler);
}

bool Dma::isDone() const
{
    return _impl->isDone();
}

void Dma::AckIrq() const
{
    _impl->AckIrq();
}
