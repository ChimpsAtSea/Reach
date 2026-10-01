/* ---------- headers */

#include "blamlib\xenon_minidump_endian.h"
#include "blamlib\minidump_helper.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void change_system_info_struct_endianness(struct _MINIDUMP_SYSTEM_INFO *);
// void change_header_struct_endianness(struct _MINIDUMP_HEADER *);
// void change_directory_struct_endianness(struct _MINIDUMP_DIRECTORY *);
// void change_thread_struct_endianness(struct _MINIDUMP_THREAD *);
// void change_misc_info_struct_endianness(struct _MINIDUMP_MISC_INFO *);
// void change_thread_context_struct_endianness(struct _MINIDUMP_CONTEXT const *);
// void change_exception_stream_endianness(struct MINIDUMP_EXCEPTION_STREAM *);
// void change_module_struct_endianness(struct _MINIDUMP_MODULE *);
// void change_memory_descriptor_struct_endianness(struct _MINIDUMP_MEMORY_DESCRIPTOR *);
// void change_memory_descriptor_struct_endianness(struct _MINIDUMP_MEMORY_DESCRIPTOR64*);

void change_system_info_struct_endianness(_MINIDUMP_SYSTEM_INFO * system_info)
{
    mangled_ppc("?change_system_info_struct_endianness@@YAXPAU_MINIDUMP_SYSTEM_INFO@@@Z");

    if (system_info)
    {
        system_info->Cpu.OtherCpuInfo.ProcessorFeatures[0] = bytes_swap(system_info->Cpu.OtherCpuInfo.ProcessorFeatures[0]);
        system_info->Cpu.OtherCpuInfo.ProcessorFeatures[1] = bytes_swap(system_info->Cpu.OtherCpuInfo.ProcessorFeatures[1]);
        system_info->BuildNumber = bytes_swap(system_info->BuildNumber);
        system_info->CSDVersionRva = bytes_swap(system_info->CSDVersionRva);
        system_info->MajorVersion = bytes_swap(system_info->MajorVersion);
        system_info->MinorVersion = bytes_swap(system_info->MinorVersion);
        system_info->NumberOfProcessors = bytes_swap(system_info->NumberOfProcessors);
        system_info->PlatformId = bytes_swap(system_info->PlatformId);
        system_info->ProcessorArchitecture = bytes_swap(system_info->ProcessorArchitecture);
        system_info->ProcessorLevel = bytes_swap(system_info->ProcessorLevel);
        system_info->ProcessorRevision = bytes_swap(system_info->ProcessorRevision);
        system_info->ProductType = bytes_swap(system_info->ProductType);
        system_info->SuiteMask = bytes_swap(system_info->SuiteMask);
    }
};

void change_header_struct_endianness(_MINIDUMP_HEADER * header)
{
    mangled_ppc("?change_header_struct_endianness@@YAXPAU_MINIDUMP_HEADER@@@Z");

    if (header)
    {
        header->CheckSum = bytes_swap(header->CheckSum);
        header->Flags = bytes_swap(header->Flags);
        header->NumberOfStreams = bytes_swap(header->NumberOfStreams);
        header->Signature = bytes_swap(header->Signature);
        header->StreamDirectoryRva = bytes_swap(header->StreamDirectoryRva);
        header->TimeDateStamp = bytes_swap(header->TimeDateStamp);
        header->Version = bytes_swap(header->Version);
    }
};

void change_directory_struct_endianness(_MINIDUMP_DIRECTORY * directory)
{
    mangled_ppc("?change_directory_struct_endianness@@YAXPAU_MINIDUMP_DIRECTORY@@@Z");

    if (directory)
    {
        directory->StreamType = bytes_swap(directory->StreamType);
        directory->Location.Rva = bytes_swap(directory->Location.Rva);
        directory->Location.DataSize = bytes_swap(directory->Location.DataSize);
    }
};

void change_thread_struct_endianness(_MINIDUMP_THREAD * thread)
{
    mangled_ppc("?change_thread_struct_endianness@@YAXPAU_MINIDUMP_THREAD@@@Z");

    if (thread)
    {
        thread->Priority = bytes_swap(thread->Priority);
        thread->PriorityClass = bytes_swap(thread->PriorityClass);
        thread->Stack.Memory.DataSize = bytes_swap(thread->Stack.Memory.DataSize);
        thread->Stack.Memory.Rva = bytes_swap(thread->Stack.Memory.Rva);
        thread->Stack.StartOfMemoryRange = bytes_swap(thread->Stack.StartOfMemoryRange);
        thread->SuspendCount = bytes_swap(thread->SuspendCount);
        thread->Teb = bytes_swap(thread->Teb);
        thread->ThreadContext.DataSize = bytes_swap(thread->ThreadContext.DataSize);
        thread->ThreadContext.Rva = bytes_swap(thread->ThreadContext.Rva);
        thread->ThreadId = bytes_swap(thread->ThreadId);
    }
};

void change_misc_info_struct_endianness(_MINIDUMP_MISC_INFO * misc_info)
{
    mangled_ppc("?change_misc_info_struct_endianness@@YAXPAU_MINIDUMP_MISC_INFO@@@Z");

    if (misc_info)
    {
        misc_info->Flags1 = bytes_swap(misc_info->Flags1);
        misc_info->ProcessCreateTime = bytes_swap(misc_info->ProcessCreateTime);
        misc_info->ProcessId = bytes_swap(misc_info->ProcessId);
        misc_info->ProcessKernelTime = bytes_swap(misc_info->ProcessKernelTime);
        misc_info->ProcessUserTime = bytes_swap(misc_info->ProcessUserTime);
        misc_info->SizeOfInfo = bytes_swap(misc_info->SizeOfInfo);
    }
};

void change_thread_context_struct_endianness(_MINIDUMP_CONTEXT const * context)
{
    mangled_ppc("?change_thread_context_struct_endianness@@YAXPBU_MINIDUMP_CONTEXT@@@Z");
};

void change_exception_stream_endianness(MINIDUMP_EXCEPTION_STREAM * exception_stream)
{
    mangled_ppc("?change_exception_stream_endianness@@YAXPAUMINIDUMP_EXCEPTION_STREAM@@@Z");

    if (exception_stream)
    {
        exception_stream->__alignment = bytes_swap(exception_stream->__alignment);
        exception_stream->ExceptionRecord.ExceptionAddress = bytes_swap(exception_stream->ExceptionRecord.ExceptionAddress);
        exception_stream->ExceptionRecord.ExceptionCode = bytes_swap(exception_stream->ExceptionRecord.ExceptionCode);
        exception_stream->ExceptionRecord.ExceptionFlags = bytes_swap(exception_stream->ExceptionRecord.ExceptionFlags);
        for (long parameter_index = 0; parameter_index < EXCEPTION_MAXIMUM_PARAMETERS; parameter_index++)
        {
            exception_stream->ExceptionRecord.ExceptionInformation[parameter_index] = bytes_swap(exception_stream->ExceptionRecord.ExceptionInformation[parameter_index]);
        }
        exception_stream->ExceptionRecord.ExceptionRecord = bytes_swap(exception_stream->ExceptionRecord.ExceptionRecord);
        exception_stream->ExceptionRecord.NumberParameters = bytes_swap(exception_stream->ExceptionRecord.NumberParameters);
        exception_stream->ThreadContext.DataSize = bytes_swap(exception_stream->ThreadContext.DataSize);
        exception_stream->ThreadContext.Rva = bytes_swap(exception_stream->ThreadContext.Rva);
        exception_stream->ThreadId = bytes_swap(exception_stream->ThreadId);
    }
};

void change_module_struct_endianness(_MINIDUMP_MODULE * module)
{
    mangled_ppc("?change_module_struct_endianness@@YAXPAU_MINIDUMP_MODULE@@@Z");

    if (module)
    {
        module->BaseOfImage = bytes_swap(module->BaseOfImage);
        module->CheckSum = bytes_swap(module->CheckSum);
        module->CvRecord.DataSize = bytes_swap(module->CvRecord.DataSize);
        module->CvRecord.Rva = bytes_swap(module->CvRecord.Rva);
        module->MiscRecord.DataSize = bytes_swap(module->MiscRecord.DataSize);
        module->MiscRecord.Rva = bytes_swap(module->MiscRecord.Rva);
        module->ModuleNameRva = bytes_swap(module->ModuleNameRva);
        module->SizeOfImage = bytes_swap(module->SizeOfImage);
        module->TimeDateStamp = bytes_swap(module->TimeDateStamp);
        module->VersionInfo.dwFileDateLS = bytes_swap(module->VersionInfo.dwFileDateLS);
        module->VersionInfo.dwFileDateMS = bytes_swap(module->VersionInfo.dwFileDateMS);
        module->VersionInfo.dwFileFlags = bytes_swap(module->VersionInfo.dwFileFlags);
        module->VersionInfo.dwFileFlagsMask = bytes_swap(module->VersionInfo.dwFileFlagsMask);
        module->VersionInfo.dwFileOS = bytes_swap(module->VersionInfo.dwFileOS);
        module->VersionInfo.dwFileSubtype = bytes_swap(module->VersionInfo.dwFileSubtype);
        module->VersionInfo.dwFileType = bytes_swap(module->VersionInfo.dwFileType);
        module->VersionInfo.dwFileVersionLS = bytes_swap(module->VersionInfo.dwFileVersionLS);
        module->VersionInfo.dwFileVersionMS = bytes_swap(module->VersionInfo.dwFileVersionMS);
        module->VersionInfo.dwProductVersionLS = bytes_swap(module->VersionInfo.dwProductVersionLS);
        module->VersionInfo.dwProductVersionMS = bytes_swap(module->VersionInfo.dwProductVersionMS);
        module->VersionInfo.dwSignature = bytes_swap(module->VersionInfo.dwSignature);
        module->VersionInfo.dwStrucVersion = bytes_swap(module->VersionInfo.dwStrucVersion);
    }
};

void change_memory_descriptor_struct_endianness(_MINIDUMP_MEMORY_DESCRIPTOR * memory_descriptor)
{
    mangled_ppc("?change_memory_descriptor_struct_endianness@@YAXPAU_MINIDUMP_MEMORY_DESCRIPTOR@@@Z");

    if (memory_descriptor)
    {
        memory_descriptor->Memory.DataSize = bytes_swap(memory_descriptor->Memory.DataSize);
        memory_descriptor->Memory.Rva = bytes_swap(memory_descriptor->Memory.Rva);
        memory_descriptor->StartOfMemoryRange = bytes_swap(memory_descriptor->StartOfMemoryRange);
    }
};

void change_memory_descriptor_struct_endianness(_MINIDUMP_MEMORY_DESCRIPTOR64 * memory_descriptor)
{
    mangled_ppc("?change_memory_descriptor_struct_endianness@@YAXPAU_MINIDUMP_MEMORY_DESCRIPTOR64@@@Z");

    if (memory_descriptor)
    {
        memory_descriptor->DataSize = bytes_swap(memory_descriptor->DataSize);
        memory_descriptor->StartOfMemoryRange = bytes_swap(memory_descriptor->StartOfMemoryRange);
    }
};

