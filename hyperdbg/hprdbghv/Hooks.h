/**
 * @file Hooks.h
 * @author Sina Karvandi (sina@rayanfam.com)
 * @brief Hook headers
 * @details 
 * @version 0.1
 * @date 2020-04-11
 * 
 * @copyright This project is released under the GNU Public License v3.
 * 
 */

#pragma once

//////////////////////////////////////////////////
//				   Syscall Hook					//
//////////////////////////////////////////////////

#define IMAGE_DOS_SIGNATURE    0x5A4D     // MZ
#define IMAGE_OS2_SIGNATURE    0x454E     // NE
#define IMAGE_OS2_SIGNATURE_LE 0x454C     // LE
#define IMAGE_VXD_SIGNATURE    0x454C     // LE
#define IMAGE_NT_SIGNATURE     0x00004550 // PE00

//////////////////////////////////////////////////
//				   Structure					//
//////////////////////////////////////////////////

/**
 * @brief SSDT structure
 * 
 */
typedef struct _SSDTStruct
{
    LONG * pServiceTable;
    PVOID  pCounterTable;
#ifdef _WIN64
    ULONGLONG NumberOfServices;
#else
    ULONG NumberOfServices;
#endif
    PCHAR pArgumentTable;
} SSDTStruct, *PSSDTStruct;

typedef struct _SYSTEM_MODULE_ENTRY
{
    HANDLE Section;
    PVOID  MappedBase;
    PVOID  ImageBase;
    ULONG  ImageSize;
    ULONG  Flags;
    USHORT LoadOrderIndex;
    USHORT InitOrderIndex;
    USHORT LoadCount;
    USHORT OffsetToFileName;
    UCHAR  FullPathName[256];
} SYSTEM_MODULE_ENTRY, *PSYSTEM_MODULE_ENTRY;

typedef struct _SYSTEM_MODULE_INFORMATION
{
    ULONG               Count;
    SYSTEM_MODULE_ENTRY Module[0];
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

typedef enum _SYSTEM_INFORMATION_CLASS
{
    SystemModuleInformation         = 11,
    SystemKernelDebuggerInformation = 35
} SYSTEM_INFORMATION_CLASS,
    *PSYSTEM_INFORMATION_CLASS;

typedef NTSTATUS(NTAPI * ZWQUERYSYSTEMINFORMATION)(
    IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
    OUT PVOID                   SystemInformation,
    IN ULONG                    SystemInformationLength,
    OUT PULONG ReturnLength     OPTIONAL);

NTSTATUS(*NtCreateFileOrig)
(
    PHANDLE            FileHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    PIO_STATUS_BLOCK   IoStatusBlock,
    PLARGE_INTEGER     AllocationSize,
    ULONG              FileAttributes,
    ULONG              ShareAccess,
    ULONG              CreateDisposition,
    ULONG              CreateOptions,
    PVOID              EaBuffer,
    ULONG              EaLength);

VOID
SSyscallHookEnableSCE();
VOID
SyscallHookDisableSCE();

//////////////////////////////////////////////////
//				   Hidden Hooks					//
//////////////////////////////////////////////////

PVOID(*ExAllocatePoolWithTagOrig)
(
    POOL_TYPE PoolType,
    SIZE_T    NumberOfBytes,
    ULONG     Tag);

// ----------------------------------------------------------------------

VOID
HiddenHooksTest();
