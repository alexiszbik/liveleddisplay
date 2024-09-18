//
//  GfxRes.h
//  TestLEDMatri0
//
//  Created by Ale0is ZBIK on 31/13/2124.
//

#ifndef GfxRes_h
#define GfxRes_h

enum GfxEnum {
    gfx_hearth,
    gfx_star
};

/*
const bool hearth[16][16] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0},
    {0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0},
    {0,1,0,0,0,0,0,1,1,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};*/

static int PROGMEM hearth[16] = {
    0,
    0,
    7224,
    8772,
    16770,
    16386,
    16386,
    16386,
    8196,
    4104,
    2064,
    1056,
    576,
    384,
    0,
    0,
};

static int PROGMEM star[16] = {
    0,
    384,
    576,
    1056,
    31806,
    16386,
    8196,
    4104,
    2064,
    2064,
    4104,
    8196,
    8580,
    18018,
    30750,
    0,
};


#endif /* GfxRes_h */