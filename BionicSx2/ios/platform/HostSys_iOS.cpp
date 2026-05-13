// PORTED FROM: common/Linux/LnxHostSys.cpp — BionicSX2 iOS Port
// AUDIT REFERENCE: Sections 6.2, 6.3
// STATUS: YELLOW — mmap/mprotect replaced with vm_allocate/vm_protect

#import <Foundation/Foundation.h>
#import <mach/mach.h>
#import <mach/mach_vm.h>
#import <sys/sysctl.h>
#import <pthread.h>

#include <cstddef>
#include <cstdlib>

// Audit Section 6.2: iOS-safe memory allocation using Mach VM API
// macOS LnxHostSys.cpp uses mmap/mprotect — these work on iOS but MAP_JIT
// requires entitlement. For interpreter-only Phase 1, we use vm_allocate/vm_protect.

// Audit Section 6.2 — Replace mmap with vm_allocate
void* HostSys_Mmap(size_t size)
{
    mach_vm_address_t addr = 0;
    kern_return_t kr = mach_vm_allocate(mach_task_self(), &addr, size, VM_FLAGS_ANYWHERE);
    if (kr != KERN_SUCCESS)
    {
        NSLog(@"[BionicSX2] vm_allocate failed for size %zu — error %d (Audit Sec 6.2)", size, kr);
        return nullptr;
    }
    NSLog(@"[BionicSX2] vm_allocate: %zu bytes at 0x%llx", size, addr);
    return reinterpret_cast<void*>(addr);
}

// Audit Section 6.2 — Replace munmap with vm_deallocate
void HostSys_Munmap(void* addr, size_t size)
{
    if (!addr) return;
    kern_return_t kr = mach_vm_deallocate(mach_task_self(), reinterpret_cast<mach_vm_address_t>(addr), size);
    if (kr != KERN_SUCCESS)
    {
        NSLog(@"[BionicSX2] vm_deallocate failed at %p — error %d (Audit Sec 6.2)", addr, kr);
    }
}

// Audit Section 6.2 — Replace mprotect with vm_protect
bool HostSys_MemProtect(void* addr, size_t size, int prot)
{
    // prot: VM_PROT_READ, VM_PROT_WRITE, VM_PROT_EXECUTE
    kern_return_t kr = mach_vm_protect(mach_task_self(), reinterpret_cast<mach_vm_address_t>(addr), size, FALSE, prot);
    if (kr != KERN_SUCCESS)
    {
        NSLog(@"[BionicSX2] vm_protect failed at %p — error %d (Audit Sec 6.2)", addr, kr);
        return false;
    }
    return true;
}

// Audit Section 6.3: MAP_JIT handling — not available without entitlement
// Phase 1: JIT disabled — log and return gracefully, do NOT crash
void* HostSys_MmapJIT(size_t size)
{
    NSLog(@"[BionicSX2] MAP_JIT not available — JIT disabled, interpreter path active (Audit Sec 6.3)");
    // Fall back to regular vm_allocate without MAP_JIT
    return HostSys_Mmap(size);
}

// Audit Section 6.2: Runtime page size via sysctl (works identically on iOS)
size_t HostSys_GetPageSize(void)
{
    static size_t s_pagesize = 0;
    if (s_pagesize == 0)
    {
        size_t len = sizeof(s_pagesize);
        if (sysctlbyname("hw.pagesize", &s_pagesize, &len, NULL, 0) != 0)
        {
            s_pagesize = 16384; // iOS Apple Silicon default
        }
    }
    return s_pagesize;
}

// Audit Section 6.2: Shared memory creation — Mach shared memory
void* HostSys_CreateSharedMemory(const char* name, size_t size)
{
    // iOS does not support POSIX shared memory (shm_open) in the sandbox.
    // Use vm_allocate with shared memory entry for inter-process sharing.
    mach_port_t mem_entry;
    kern_return_t kr = mach_make_memory_entry_64(mach_task_self(), &size,
        (memory_object_offset_t)0, MAP_MEM_NAMED_CREATE | VM_PROT_DEFAULT, &mem_entry, MACH_PORT_NULL);
    if (kr != KERN_SUCCESS)
    {
        NSLog(@"[BionicSX2] mach_make_memory_entry_64 failed — error %d (Audit Sec 6.2)", kr);
        return nullptr;
    }
    // Map the entry into process address space
    mach_vm_address_t addr = 0;
    kr = mach_vm_map(mach_task_self(), &addr, size, 0, VM_FLAGS_ANYWHERE,
                     mem_entry, 0, FALSE, VM_PROT_READ | VM_PROT_WRITE,
                     VM_PROT_READ | VM_PROT_WRITE, VM_INHERIT_NONE);
    if (kr != KERN_SUCCESS)
    {
        NSLog(@"[BionicSX2] mach_vm_map failed for shared memory — error %d (Audit Sec 6.2)", kr);
        return nullptr;
    }
    return reinterpret_cast<void*>(addr);
}

// Audit Section 6.2: Destroy shared memory
void HostSys_DestroySharedMemory(void* ptr, size_t size)
{
    HostSys_Munmap(ptr, size);
}
