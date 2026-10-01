#pragma once
#ifndef __HKREFERENCEDOBJECT_H__
#define __HKREFERENCEDOBJECT_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class hkBaseObject
{
public:
    virtual ~hkBaseObject();
};

class hkReferencedObject :
    public hkBaseObject
{
public:
    int getReferenceCount() const; // $TODO inline in the target (f i, instanced_geometry_definitions.obj); body not reversed yet
    void removeReference() const;

    unsigned short m_memSizeAndFlags; // 0x4
    short m_referenceCount; // 0x6
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HKREFERENCEDOBJECT_H__

