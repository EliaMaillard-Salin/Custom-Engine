#pragma once


// Check if a specific flag is set
#define HAS_FLAG(flags, flag) (((flags) & (flag)) != 0)

// Set a specific flag
#define SET_FLAG(flags, flag) ((flags) |= (flag))

// Unset a specific flag
#define UNSET_FLAG(flags, flag) ((flags) &= ~(flag))

#define VERTEX_NONE								0x00 // 00000000
#define VERTEX_POSITION                         0x01 // 00000001
#define VERTEX_COLOR                            0x02 // 00000010
#define VERTEX_UV                               0x04 // 00000100
#define VERTEX_NORMAL                           0x08 // 00001000

#define LIGHT_TYPE_DIRECTIONAL 0
#define LIGHT_TYPE_SPOT 1
#define LIGHT_TYPE_POINT 2