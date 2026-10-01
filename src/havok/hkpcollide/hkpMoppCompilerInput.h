#pragma once
#ifndef __HKPMOPPCOMPILERINPUT_H__
#define __HKPMOPPCOMPILERINPUT_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

// $TODO: layout not reversed (hkVector4 at 0x0, floats at 0x10-0x18, hkBools at 0x1C-0x20); size 0x30 per collision_bsp_physics_build stack usage
class hkpMoppCompilerInput
{
public:
    hkpMoppCompilerInput();
    void setAbsoluteFitToleranceOfTriangles(float tolerance);

    unsigned char unknown0[0x30]; // 0x0
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HKPMOPPCOMPILERINPUT_H__

