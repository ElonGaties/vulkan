#pragma once

#include <windows.h>
#include <Psapi.h>
#include <direct.h>
#include <time.h>

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#include "nt.h"

extern volatile BOOLEAN TerminateCurrentTask;

//
// Represents a dumper object.
//
typedef struct _DUMPER
{
    LPWSTR ProcessName;     // Name of the target process.
    DWORD ProcessId;        // ID of the target process.
    HANDLE Process;         // Handle to the target process.
    MODULEINFO ModuleInfo;  // Module information of the target process.
    LPWSTR OutputPath;      // Path to the output directory.
    FLOAT DecryptionFactor; // Decrypt no access memory regions.
    BOOL UseTimestamp;      // Flag to indicate whether to use timestamp in output filename.
} DUMPER, *PDUMPER;

//
// Creates a new dumper object. Initializes the object with the specified process name, output path, and decryption
// flag.
_Success_(return)
BOOL
DumperCreate(
    _Out_ PDUMPER Dumper,
    _In_ LPWSTR ProcessName,
    _In_ LPWSTR OutputPath,
    _In_ FLOAT DecryptionFactor,
    _In_ BOOL UseTimestamp,
    _In_ BOOL WaitLaunch);

//
// Dumps the target process memory to disk. Decrypts no access memory regions if the decryption flag is set.
//
_Success_(return)
BOOL
DumperDumpToDisk(_In_ PDUMPER Dumper);

//
// Destroys the specified dumper object. Closes the handle to the target process.
//
_Success_(return == EXIT_SUCCESS)
INT
DumperDestroy(_In_ PDUMPER Dumper);