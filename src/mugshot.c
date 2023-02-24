#include "global.h"
#include "blit.h"
#include "window.h"
#include "menu.h"
#include "palette.h"
#include "event_data.h"
#include "constants/mugshots.h"

#define MUGSHOT_PALETTE_NUM 13

struct Mugshot{
    s8 x;               //Allows for a positioning number between -128 to 127 (This is the x axis which means left to right)
    s8 y;               //Allows for a positioning number between -128 to 127 (This is the y axis which means up and down)
    u8 width;           //Determines the width of the image that is shown, acceptable numbers are 0-255. (Must be a multiple of 8)
    u8 height;          //Determines the height of the image that is shown, acceptable numbers are 0-255 (Must be a multiple of 8)
    const u32* image;   //The name of the image you add below (Example: sMugshotImg_Mom_Happy)
    const u16* palette; //The name of the palette you add below (Example: sMugshotPal_Mom_Happy)
};

void DrawMugshot(void);      //VAR_0x8000 = mugshot id
void DrawMugshotAtPos(void); //VAR_0x8000 = mugshot id, VAR_0x8001 = x, VAR_0x8002 = y
void ClearMugshot(void);    //Clears the current Mugshot loaded in VAR_0x8000. 
//ADD YOUR IMAGE AND PALETTES BELOW HERE
static const u32 sMugshotImg_Mom_Happy[] = INCBIN_U32("graphics/mugshots/mom_happy.4bpp.lz"); //This is the Image you are going to laod. Uses the filename with .4bpp.lz instead of .png extension.
static const u16 sMugshotPal_Mom_Happy[] = INCBIN_U16("graphics/mugshots/mom_happy.gbapal");  //This is the Palette you are going to load. created from the indexed image and named as the flename with the .gbapal extension.
static const u32 sMugshotImg_Mom_Frown[] = INCBIN_U32("graphics/mugshots/mom_frown.4bpp.lz");
static const u16 sMugshotPal_Mom_Frown[] = INCBIN_U16("graphics/mugshots/mom_frown.gbapal");
static const u32 sMugshotImg_Mom_Serious[] = INCBIN_U32("graphics/mugshots/mom_serious.4bpp.lz");
static const u16 sMugshotPal_Mom_Serious[] = INCBIN_U16("graphics/mugshots/mom_serious.gbapal");
static const u32 sMugshotImg_May_Serious[] = INCBIN_U32("graphics/mugshots/may_serious.4bpp.lz");
static const u16 sMugshotPal_May_Serious[] = INCBIN_U16("graphics/mugshots/may_serious.gbapal");
static const u32 sMugshotImg_May_Happy[] = INCBIN_U32("graphics/mugshots/may_happy.4bpp.lz");
static const u16 sMugshotPal_May_Happy[] = INCBIN_U16("graphics/mugshots/may_happy.gbapal");
static const u32 sMugshotImg_May_Pout[] = INCBIN_U32("graphics/mugshots/may_pout.4bpp.lz");
static const u16 sMugshotPal_May_Pout[] = INCBIN_U16("graphics/mugshots/may_pout.gbapal");
static const u32 sMugshotImg_May_Smile[] = INCBIN_U32("graphics/mugshots/may_smile.4bpp.lz");
static const u16 sMugshotPal_May_Smile[] = INCBIN_U16("graphics/mugshots/may_smile.gbapal");
static const u32 sMugshotImg_Birch_Scared[] = INCBIN_U32("graphics/mugshots/birch_scared.4bpp.lz");
static const u16 sMugshotPal_Birch_Scared[] = INCBIN_U16("graphics/mugshots/birch_scared.gbapal");
static const u32 sMugshotImg_Birch_Serious[] = INCBIN_U32("graphics/mugshots/birch_serious.4bpp.lz");
static const u16 sMugshotPal_Birch_Serious[] = INCBIN_U16("graphics/mugshots/birch_serious.gbapal");
static const u32 sMugshotImg_Birch_Happy[] = INCBIN_U32("graphics/mugshots/birch_happy.4bpp.lz");
static const u16 sMugshotPal_Birch_Happy[] = INCBIN_U16("graphics/mugshots/birch_happy.gbapal");
static const u32 sMugshotImg_Brendan_Serious[] = INCBIN_U32("graphics/mugshots/brendan_serious.4bpp.lz");
static const u16 sMugshotPal_Brendan_Serious[] = INCBIN_U16("graphics/mugshots/brendan_serious.gbapal");
static const u32 sMugshotImg_Brendan_Happy[] = INCBIN_U32("graphics/mugshots/brendan_happy.4bpp.lz");
static const u16 sMugshotPal_Brendan_Happy[] = INCBIN_U16("graphics/mugshots/brendan_happy.gbapal");
static const u32 sMugshotImg_Brendan_Pout[] = INCBIN_U32("graphics/mugshots/brendan_pout.4bpp.lz");
static const u16 sMugshotPal_Brendan_Pout[] = INCBIN_U16("graphics/mugshots/brendan_pout.gbapal");
static const u32 sMugshotImg_Brendan_Smile[] = INCBIN_U32("graphics/mugshots/brendan_smile.4bpp.lz");
static const u16 sMugshotPal_Brendan_Smile[] = INCBIN_U16("graphics/mugshots/brendan_smile.gbapal");
static const u32 sMugshotImg_Rival_Mom_Serious[] = INCBIN_U32("graphics/mugshots/rival_mom_serious.4bpp.lz");
static const u16 sMugshotPal_Rival_Mom_Serious[] = INCBIN_U16("graphics/mugshots/rival_mom_serious.gbapal");
static const u32 sMugshotImg_Rival_Mom_Happy[] = INCBIN_U32("graphics/mugshots/rival_mom_happy.4bpp.lz");
static const u16 sMugshotPal_Rival_Mom_Happy[] = INCBIN_U16("graphics/mugshots/rival_mom_happy.gbapal");
static const u32 sMugshotImg_Rival_Mom_Smile[] = INCBIN_U32("graphics/mugshots/rival_mom_smile.4bpp.lz");
static const u16 sMugshotPal_Rival_Mom_Smile[] = INCBIN_U16("graphics/mugshots/rival_mom_smile.gbapal");

static const struct Mugshot sMugshots[] = {
    //ADD YOUR MUGSHOTS HERE
    [MUGSHOT_MOM_HAPPY] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Mom_Happy, .palette = sMugshotPal_Mom_Happy},
    [MUGSHOT_MOM_FROWN] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Mom_Frown, .palette = sMugshotPal_Mom_Frown},
    [MUGSHOT_MOM_SERIOUS] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Mom_Serious, .palette = sMugshotPal_Mom_Serious},
    [MUGSHOT_MAY_SERIOUS] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_May_Serious, .palette = sMugshotPal_May_Serious},
    [MUGSHOT_MAY_HAPPY] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_May_Happy, .palette = sMugshotPal_May_Happy},
    [MUGSHOT_MAY_POUT] = {.x = 0, .y = 1, .width = 240, .height = 104, .image = sMugshotImg_May_Pout, .palette = sMugshotPal_May_Pout},
    [MUGSHOT_MAY_SMILE] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_May_Smile, .palette = sMugshotPal_May_Smile},
    [MUGSHOT_BIRCH_SCARED] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Birch_Scared, .palette = sMugshotPal_Birch_Scared},
    [MUGSHOT_BIRCH_SERIOUS] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Birch_Serious, .palette = sMugshotPal_Birch_Serious},
    [MUGSHOT_BIRCH_HAPPY] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Birch_Happy, .palette = sMugshotPal_Birch_Happy},
    [MUGSHOT_BRENDAN_SERIOUS] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Brendan_Serious, .palette = sMugshotPal_Brendan_Serious},
    [MUGSHOT_BRENDAN_HAPPY] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Brendan_Happy, .palette = sMugshotPal_Brendan_Happy},
    [MUGSHOT_BRENDAN_POUT] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Brendan_Pout, .palette = sMugshotPal_Brendan_Pout},
    [MUGSHOT_BRENDAN_SMILE] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Brendan_Smile, .palette = sMugshotPal_Brendan_Smile},
    [MUGSHOT_RIVAL_MOM_SERIOUS] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Rival_Mom_Serious, .palette = sMugshotPal_Rival_Mom_Serious},
    [MUGSHOT_RIVAL_MOM_HAPPY] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Rival_Mom_Happy, .palette = sMugshotPal_Rival_Mom_Happy},
    [MUGSHOT_RIVAL_MOM_SMILE] = {.x = 17, .y = 1, .width = 104, .height = 104, .image = sMugshotImg_Rival_Mom_Smile, .palette = sMugshotPal_Rival_Mom_Smile},
};


//WindowId + 1, 0 if window is not open
static EWRAM_DATA u8 sMugshotWindow = 0;

void ClearMugshot(void){
    if(sMugshotWindow != 0){
        ClearStdWindowAndFrameToTransparent(sMugshotWindow - 1, 0);
        CopyWindowToVram(sMugshotWindow - 1, 3);
        RemoveWindow(sMugshotWindow - 1);
        sMugshotWindow = 0;
    }
}

static void DrawMugshotCore(const struct Mugshot* const mugshot, int x, int y){
    struct WindowTemplate t;
    u16 windowId;
    
    if(sMugshotWindow != 0){
        ClearMugshot();
    }
    
    #if GAME_VERSION==VERSION_EMERALD
    SetWindowTemplateFields(&t, 0, x, y, mugshot->width/8, mugshot->height/8, MUGSHOT_PALETTE_NUM, 0);
    #else
    t = SetWindowTemplateFields(0, x, y, mugshot->width/8, mugshot->height/8, MUGSHOT_PALETTE_NUM, 0);
    #endif
    windowId = AddWindow(&t);
    sMugshotWindow = windowId + 1;
    
    LoadPalette(mugshot->palette, 16 * MUGSHOT_PALETTE_NUM, 32);
    CopyToWindowPixelBuffer(windowId, (const void*)mugshot->image, 0, 0);
    PutWindowRectTilemap(windowId, 0, 0, mugshot->width/8, mugshot->height/8);
    CopyWindowToVram(windowId, 3);
}

void DrawMugshot(void){
    const struct Mugshot* const mugshot = sMugshots + VarGet(VAR_0x8000);
    DrawMugshotCore(mugshot, mugshot->x, mugshot->y);
}

void DrawMugshotAtPos(void){
    DrawMugshotCore(sMugshots + VarGet(VAR_0x8000), VarGet(VAR_0x8001), VarGet(VAR_0x8002));
}