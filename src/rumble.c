#include "global.h"
#include "rumble.h"
#include "main.h"
#include "sound.h"

static EWRAM_DATA u32 sRumbleState = 0;
static EWRAM_DATA u8 sRumbleType = RUMBLE_TYPE_OFF;
static EWRAM_DATA u32 stopRumbleVblankCounter = 0;

static u16 const sNintendoHandshakeData[] = {0x494E, 0x544E, 0x4E45, 0x4F44, 0x8000};
static void SetRumbleState(u32 state);

enum
{
    RUMBLE_ON        = 0x40000026,
    RUMBLE_OFF       = 0x40000004,
    RUMBLE_HARD_STOP = 0x40000015
};

void RumbleFrameUpdate()
{
    REG_SIOCNT &= ~1;
    REG_SIOCNT |= SIO_START;
    if(gMain.vblankCounter1 == stopRumbleVblankCounter && sRumbleType == RUMBLE_TYPE_TIMED)
        SetRumbleState(RUMBLE_OFF);
}

static void SetRumbleState(u32 state)
{
    sRumbleState = state;
    if (sRumbleState != RUMBLE_ON)
        sRumbleType = RUMBLE_TYPE_OFF;

    GPIO_PORT_DIRECTION = 1 << 3;
    GPIO_PORT_DATA = (sRumbleState == RUMBLE_ON) << 3;
}

bool32 RumbleStart(void)
{
    if (sRumbleType == RUMBLE_TYPE_TIMED)
        return FALSE;
    sRumbleType = RUMBLE_TYPE_CONT;
    SetRumbleState(RUMBLE_ON);
    return TRUE;
}

bool32 RumbleStop(void)
{
    if (sRumbleType != RUMBLE_TYPE_CONT)
        return FALSE;
    SetRumbleState(RUMBLE_OFF);
    return TRUE;
}

bool32 SetTimedRumble(u8 deciseconds)
{
    if (sRumbleType == RUMBLE_TYPE_CONT)
        return FALSE;
    sRumbleType = RUMBLE_TYPE_TIMED;
    stopRumbleVblankCounter = gMain.vblankCounter1 + (6 * deciseconds);
    SetRumbleState(RUMBLE_ON);
    return TRUE;
}

u32 GetRumbleState(void)
{
    return sRumbleState;
}
