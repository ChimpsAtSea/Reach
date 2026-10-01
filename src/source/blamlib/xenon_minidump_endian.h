#pragma once
#ifndef __XENON_MINIDUMP_ENDIAN_H__
#define __XENON_MINIDUMP_ENDIAN_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

#define EXCEPTION_MAXIMUM_PARAMETERS 15
#define MINIDUMP_MISC1_PROCESS_ID 0x00000001

/* ---------- definitions */

// the XDK ships no DbgHelp.h: minidump stream layouts as in the Windows SDK (pack 4)
#pragma pack(push, 4)

struct _MINIDUMP_LOCATION_DESCRIPTOR
{
    unsigned int DataSize; // 0x0
    unsigned long Rva; // 0x4
};
typedef _MINIDUMP_LOCATION_DESCRIPTOR MINIDUMP_LOCATION_DESCRIPTOR;
static_assert(sizeof(_MINIDUMP_LOCATION_DESCRIPTOR) == 0x8, "_MINIDUMP_LOCATION_DESCRIPTOR");

struct _MINIDUMP_MEMORY_DESCRIPTOR
{
    unsigned __int64 StartOfMemoryRange; // 0x0
    MINIDUMP_LOCATION_DESCRIPTOR Memory; // 0x8
};
typedef _MINIDUMP_MEMORY_DESCRIPTOR MINIDUMP_MEMORY_DESCRIPTOR;
static_assert(sizeof(_MINIDUMP_MEMORY_DESCRIPTOR) == 0x10, "_MINIDUMP_MEMORY_DESCRIPTOR");

struct _MINIDUMP_MEMORY_DESCRIPTOR64
{
    unsigned __int64 StartOfMemoryRange; // 0x0
    unsigned __int64 DataSize; // 0x8
};
typedef _MINIDUMP_MEMORY_DESCRIPTOR64 MINIDUMP_MEMORY_DESCRIPTOR64;
static_assert(sizeof(_MINIDUMP_MEMORY_DESCRIPTOR64) == 0x10, "_MINIDUMP_MEMORY_DESCRIPTOR64");

struct _MINIDUMP_HEADER
{
    unsigned int Signature; // 0x0
    unsigned int Version; // 0x4
    unsigned int NumberOfStreams; // 0x8
    unsigned long StreamDirectoryRva; // 0xC
    unsigned int CheckSum; // 0x10
    union
    {
        unsigned int Reserved;
        unsigned int TimeDateStamp;
    }; // 0x14
    unsigned __int64 Flags; // 0x18
};
typedef _MINIDUMP_HEADER MINIDUMP_HEADER;
static_assert(sizeof(_MINIDUMP_HEADER) == 0x20, "_MINIDUMP_HEADER");

struct _MINIDUMP_DIRECTORY
{
    unsigned int StreamType; // 0x0
    MINIDUMP_LOCATION_DESCRIPTOR Location; // 0x4
};
typedef _MINIDUMP_DIRECTORY MINIDUMP_DIRECTORY;
static_assert(sizeof(_MINIDUMP_DIRECTORY) == 0xC, "_MINIDUMP_DIRECTORY");

union _CPU_INFORMATION
{
    struct
    {
        unsigned int VendorId[3];
        unsigned int VersionInformation;
        unsigned int FeatureInformation;
        unsigned int AMDExtendedCpuFeatures;
    } X86CpuInfo;

    struct
    {
        unsigned __int64 ProcessorFeatures[2];
    } OtherCpuInfo;
};
typedef _CPU_INFORMATION CPU_INFORMATION;
static_assert(sizeof(_CPU_INFORMATION) == 0x18, "_CPU_INFORMATION");

struct _MINIDUMP_SYSTEM_INFO
{
    unsigned short ProcessorArchitecture; // 0x0
    unsigned short ProcessorLevel; // 0x2
    unsigned short ProcessorRevision; // 0x4
    union
    {
        unsigned short Reserved0;
        struct
        {
            unsigned char NumberOfProcessors;
            unsigned char ProductType;
        };
    }; // 0x6
    unsigned int MajorVersion; // 0x8
    unsigned int MinorVersion; // 0xC
    unsigned int BuildNumber; // 0x10
    unsigned int PlatformId; // 0x14
    unsigned long CSDVersionRva; // 0x18
    union
    {
        unsigned int Reserved1;
        struct
        {
            unsigned short SuiteMask;
            unsigned short Reserved2;
        };
    }; // 0x1C
    CPU_INFORMATION Cpu; // 0x20
};
typedef _MINIDUMP_SYSTEM_INFO MINIDUMP_SYSTEM_INFO;
static_assert(sizeof(_MINIDUMP_SYSTEM_INFO) == 0x38, "_MINIDUMP_SYSTEM_INFO");

struct _MINIDUMP_THREAD
{
    unsigned int ThreadId; // 0x0
    unsigned int SuspendCount; // 0x4
    unsigned int PriorityClass; // 0x8
    unsigned int Priority; // 0xC
    unsigned __int64 Teb; // 0x10
    MINIDUMP_MEMORY_DESCRIPTOR Stack; // 0x18
    MINIDUMP_LOCATION_DESCRIPTOR ThreadContext; // 0x28
};
typedef _MINIDUMP_THREAD MINIDUMP_THREAD;
static_assert(sizeof(_MINIDUMP_THREAD) == 0x30, "_MINIDUMP_THREAD");

struct _MINIDUMP_MISC_INFO
{
    unsigned int SizeOfInfo; // 0x0
    unsigned int Flags1; // 0x4
    unsigned int ProcessId; // 0x8
    unsigned int ProcessCreateTime; // 0xC
    unsigned int ProcessUserTime; // 0x10
    unsigned int ProcessKernelTime; // 0x14
};
typedef _MINIDUMP_MISC_INFO MINIDUMP_MISC_INFO;
static_assert(sizeof(_MINIDUMP_MISC_INFO) == 0x18, "_MINIDUMP_MISC_INFO");

struct _MINIDUMP_EXCEPTION
{
    unsigned int ExceptionCode; // 0x0
    unsigned int ExceptionFlags; // 0x4
    unsigned __int64 ExceptionRecord; // 0x8
    unsigned __int64 ExceptionAddress; // 0x10
    unsigned int NumberParameters; // 0x18
    unsigned int __unusedAlignment; // 0x1C
    unsigned __int64 ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS]; // 0x20
};
typedef _MINIDUMP_EXCEPTION MINIDUMP_EXCEPTION;
static_assert(sizeof(_MINIDUMP_EXCEPTION) == 0x98, "_MINIDUMP_EXCEPTION");

struct MINIDUMP_EXCEPTION_STREAM
{
    unsigned int ThreadId; // 0x0
    unsigned int __alignment; // 0x4
    MINIDUMP_EXCEPTION ExceptionRecord; // 0x8
    MINIDUMP_LOCATION_DESCRIPTOR ThreadContext; // 0xA0
};
static_assert(sizeof(MINIDUMP_EXCEPTION_STREAM) == 0xA8, "MINIDUMP_EXCEPTION_STREAM");

struct tagVS_FIXEDFILEINFO
{
    unsigned long dwSignature; // 0x0
    unsigned long dwStrucVersion; // 0x4
    unsigned long dwFileVersionMS; // 0x8
    unsigned long dwFileVersionLS; // 0xC
    unsigned long dwProductVersionMS; // 0x10
    unsigned long dwProductVersionLS; // 0x14
    unsigned long dwFileFlagsMask; // 0x18
    unsigned long dwFileFlags; // 0x1C
    unsigned long dwFileOS; // 0x20
    unsigned long dwFileType; // 0x24
    unsigned long dwFileSubtype; // 0x28
    unsigned long dwFileDateMS; // 0x2C
    unsigned long dwFileDateLS; // 0x30
};
typedef tagVS_FIXEDFILEINFO VS_FIXEDFILEINFO;
static_assert(sizeof(tagVS_FIXEDFILEINFO) == 0x34, "tagVS_FIXEDFILEINFO");

struct _MINIDUMP_MODULE
{
    unsigned __int64 BaseOfImage; // 0x0
    unsigned int SizeOfImage; // 0x8
    unsigned int CheckSum; // 0xC
    unsigned int TimeDateStamp; // 0x10
    unsigned long ModuleNameRva; // 0x14
    VS_FIXEDFILEINFO VersionInfo; // 0x18
    MINIDUMP_LOCATION_DESCRIPTOR CvRecord; // 0x4C
    MINIDUMP_LOCATION_DESCRIPTOR MiscRecord; // 0x54
    unsigned __int64 Reserved0; // 0x5C
    unsigned __int64 Reserved1; // 0x64
};
typedef _MINIDUMP_MODULE MINIDUMP_MODULE;
static_assert(sizeof(_MINIDUMP_MODULE) == 0x6C, "_MINIDUMP_MODULE");

#pragma pack(pop)

struct _MINIDUMP_CONTEXT;

/* ---------- prototypes */

void change_system_info_struct_endianness(_MINIDUMP_SYSTEM_INFO * system_info);
void change_header_struct_endianness(_MINIDUMP_HEADER * header);
void change_directory_struct_endianness(_MINIDUMP_DIRECTORY * directory);
void change_thread_struct_endianness(_MINIDUMP_THREAD * thread);
void change_misc_info_struct_endianness(_MINIDUMP_MISC_INFO * misc_info);
void change_thread_context_struct_endianness(_MINIDUMP_CONTEXT const * context);
void change_exception_stream_endianness(MINIDUMP_EXCEPTION_STREAM * exception_stream);
void change_module_struct_endianness(_MINIDUMP_MODULE * module);
void change_memory_descriptor_struct_endianness(_MINIDUMP_MEMORY_DESCRIPTOR * memory_descriptor);
void change_memory_descriptor_struct_endianness(_MINIDUMP_MEMORY_DESCRIPTOR64 * memory_descriptor);

/* ---------- globals */

/* ---------- public code */

#endif // __XENON_MINIDUMP_ENDIAN_H__

