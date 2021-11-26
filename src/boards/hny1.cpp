#include "mapinc.h"

static uint16 hny1_reg;

static void HNY1Sync(void)
{
    setprg16(0x8000, hny1_reg);
    setprg16(0xc000, ~0);
    setchr8(0);
}

static DECLFW(HNY1Write)
{
    if (A & 0x4000) // high byte
    {
        hny1_reg = hny1_reg & 0x00ff | V << 8;
    }
    else // low byte
    {
        hny1_reg = hny1_reg & 0xff00 | V;
    }
    HNY1Sync();
}

static void HNY1Power(void)
{
    HNY1Sync();
    SetReadHandler(0x8000, 0xFFFF, CartBR);
    SetWriteHandler(0x8000, 0xFFFF, HNY1Write);
}

static void StateRestore(int version)
{
    HNY1Sync();
}

void HNY1_Init(CartInfo *info)
{
    hny1_reg = 0;
    info->Power = HNY1Power;
    GameStateRestore = StateRestore;
    AddExState(&hny1_reg, 2, 0, "HNY1 address register");
}
