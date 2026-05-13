// PORTED FROM: common/Darwin/DarwinMisc.cpp — BionicSX2 iOS Port
// AUDIT REFERENCE: Section 6.2
// STATUS: YELLOW — CoreGraphics/IOKit code removed, Mach exception port retained

#include <mach/mach.h>
#include <mach/mach_error.h>
#include <mach/mach_init.h>
#include <mach/mach_port.h>
#include <mach/mach_time.h>
#include <mach/message.h>
#include <mach/thread_state.h>
#include <mach/task.h>
#include <pthread.h>
#include <sys/sysctl.h>

#include <thread>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <string>
#include <vector>

// Audit Section 6.2: macOS uses Mach exception ports for page fault handling
// iOS retains the same Mach kernel — exception ports work identically
// RETAINED: Mach exception handler for SIGSEGV → vtlb page fault
// REMOVED: CoreGraphics (CGEventTap, CGWarpCursor, AXIsProcessTrusted)
// REMOVED: IOKit (IOPMAssertion, IOService)

// Audit Section 6.2: System information via sysctl (works identically on iOS)

uint64_t GetPhysicalMemory(void)
{
    uint64_t mem = 0;
    size_t len = sizeof(mem);
    int mib[] = {CTL_HW, HW_MEMSIZE};
    if (sysctl(mib, 2, &mem, &len, NULL, 0) < 0)
        perror("sysctl");
    return mem;
}

uint64_t GetAvailablePhysicalMemory(void)
{
    mach_port_t host_port = mach_host_self();
    vm_size_t page_size;
    if (host_page_size(host_port, &page_size) != KERN_SUCCESS)
        return 0;

    vm_statistics64_data_t vm_stat;
    mach_msg_type_number_t host_size = sizeof(vm_statistics64_data_t) / sizeof(integer_t);
    if (host_statistics64(host_port, HOST_VM_INFO, (host_info64_t)&vm_stat, &host_size) != KERN_SUCCESS)
        return 0;

    uint64_t free_pages = (uint64_t)vm_stat.free_count;
    uint64_t inactive_pages = (uint64_t)vm_stat.inactive_count;
    return (free_pages + inactive_pages) * page_size;
}

// Audit Section 6.2: Mach timebase (identical on iOS)
static mach_timebase_info_data_t s_timebase_info;
static uint64_t s_tickfreq = 0;

uint64_t GetTickFrequency(void)
{
    if (s_tickfreq == 0)
    {
        if (mach_timebase_info(&s_timebase_info) != KERN_SUCCESS)
            abort();
        s_tickfreq = (uint64_t)1e9 * (uint64_t)s_timebase_info.denom / (uint64_t)s_timebase_info.numer;
    }
    return s_tickfreq;
}

uint64_t GetCPUTicks(void)
{
    return mach_absolute_time();
}

// Audit Section 6.2: CPU info via sysctl (works on iOS ARM64)
// Ported from DarwinMisc.cpp:240-303, with CoreGraphics dependency removed

struct CPUClass {
    std::string name;
    uint32_t num_physical;
    uint32_t num_logical;
};

static std::vector<CPUClass> GetCPUClasses(void)
{
    std::vector<CPUClass> out;
    uint32_t nperflevels = 0;
    size_t sz = sizeof(nperflevels);
    if (sysctlbyname("hw.nperflevels", &nperflevels, &sz, NULL, 0) != 0)
    {
        // Fallback: single perf level
        uint32_t physcpu = 0;
        sz = sizeof(physcpu);
        sysctlbyname("hw.physicalcpu", &physcpu, &sz, NULL, 0);
        uint32_t logcpu = physcpu;
        sysctlbyname("hw.logicalcpu", &logcpu, &sz, NULL, 0);
        out.push_back({"Default", physcpu, logcpu});
        return out;
    }

    char name[64];
    for (uint32_t i = 0; i < nperflevels; i++)
    {
        snprintf(name, sizeof(name), "hw.perflevel%u.physicalcpu", i);
        uint32_t physcpu = 0;
        size_t sz = sizeof(physcpu);
        sysctlbyname(name, &physcpu, &sz, NULL, 0);

        snprintf(name, sizeof(name), "hw.perflevel%u.logicalcpu", i);
        uint32_t logcpu = 0;
        sysctlbyname(name, &logcpu, &sz, NULL, 0);

        snprintf(name, sizeof(name), "hw.perflevel%u.name", i);
        char levelname[64];
        size_t levelname_sz = sizeof(levelname);
        if (sysctlbyname(name, levelname, &levelname_sz, NULL, 0) != 0)
            strcpy(levelname, "???");

        out.push_back({levelname, physcpu, logcpu});
    }
    return out;
}

// Audit Section 6.2: Mach exception port page fault handler
// Ported from DarwinMisc.cpp:391-569, IOKit/CoreGraphics code removed
// iOS power management handled by UIApplicationDelegate — not replicated here

#define USE_MACH_EXCEPTION_PORTS

namespace PageFaultHandler
{
    enum class HandlerResult
    {
        ContinueExecution,
        ExecuteNextHandler,
    };

    static HandlerResult HandlePageFault(void* exception_pc, void* fault_address, bool is_write);

    // iOS stub — Mach exception handler placeholder
    // Called from SignalHandler when a BAD_ACCESS Mach exception is received.
    // Returns ContinueExecution to keep the VM running.
    // Full implementation will integrate with vtlb page fault handling.
    static HandlerResult HandlePageFault(void* exception_pc, void* fault_address, bool is_write)
    {
        return HandlerResult::ContinueExecution;
    }

    static mach_port_t s_port = 0;
    static std::recursive_mutex s_exception_handler_mutex;
    static bool s_in_exception_handler = false;
    static bool s_installed = false;

#ifdef USE_MACH_EXCEPTION_PORTS

#define THREAD_STATE64 ARM_THREAD_STATE64
#define THREAD_STATE64_COUNT ARM_THREAD_STATE64_COUNT

    static void SignalHandler(mach_port_t port)
    {
        pthread_setname_np("Mach Exception Thread");

#pragma pack(4)
        struct {
            mach_msg_header_t Head;
            NDR_record_t NDR;
            exception_type_t exception;
            mach_msg_type_number_t codeCnt;
            int64_t code[2];
            int flavor;
            mach_msg_type_number_t old_stateCnt;
            natural_t old_state[THREAD_STATE64_COUNT];
            mach_msg_trailer_t trailer;
        } msg_in;

        struct {
            mach_msg_header_t Head;
            NDR_record_t NDR;
            kern_return_t RetCode;
            int flavor;
            mach_msg_type_number_t new_stateCnt;
            natural_t new_state[THREAD_STATE64_COUNT];
        } msg_out;
#pragma pack()

        memset(&msg_in, 0xee, sizeof(msg_in));
        memset(&msg_out, 0xee, sizeof(msg_out));
        mach_msg_size_t send_size = 0;
        mach_msg_option_t option = MACH_RCV_MSG;

        while (true)
        {
            kern_return_t r;
            if ((r = mach_msg_overwrite(&msg_out.Head, option, send_size, sizeof(msg_in), port,
                     MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL, &msg_in.Head, 0)))
            {
                fprintf(stderr, "[BionicSX2] mach_msg_overwrite: %x (Audit Sec 6.2)\n", r);
            }

            if (msg_in.Head.msgh_id == MACH_NOTIFY_NO_SENDERS)
            {
                mach_port_deallocate(mach_task_self(), port);
                return;
            }

            if (msg_in.Head.msgh_id != 2406)
                return;

            arm_thread_state64_t* state = (arm_thread_state64_t*)msg_in.old_state;

            HandlerResult result = HandlerResult::ExecuteNextHandler;
            if (!s_in_exception_handler)
            {
                s_in_exception_handler = true;
                result = HandlePageFault(
                    reinterpret_cast<void*>(state->__pc),
                    reinterpret_cast<void*>(msg_in.code[1]),
                    (msg_in.code[0] & 2) != 0);
                s_in_exception_handler = false;
            }

            msg_out.Head.msgh_bits = MACH_MSGH_BITS(MACH_MSGH_BITS_REMOTE(msg_in.Head.msgh_bits), 0);
            msg_out.Head.msgh_remote_port = msg_in.Head.msgh_remote_port;
            msg_out.Head.msgh_local_port = MACH_PORT_NULL;
            msg_out.Head.msgh_id = msg_in.Head.msgh_id + 100;
            msg_out.NDR = msg_in.NDR;

            if (result != HandlerResult::ContinueExecution)
            {
                msg_out.RetCode = KERN_FAILURE;
                msg_out.flavor = 0;
                msg_out.new_stateCnt = 0;
            }
            else
            {
                msg_out.RetCode = KERN_SUCCESS;
                msg_out.flavor = THREAD_STATE64;
                msg_out.new_stateCnt = THREAD_STATE64_COUNT;
                memcpy(msg_out.new_state, msg_in.old_state, THREAD_STATE64_COUNT * sizeof(natural_t));
            }

            msg_out.Head.msgh_size = offsetof(__typeof__(msg_out), new_state) + msg_out.new_stateCnt * sizeof(natural_t);
            send_size = msg_out.Head.msgh_size;
            option |= MACH_SEND_MSG;
        }
    }

    bool Install(void)
    {
        exception_mask_t masks[EXC_TYPES_COUNT];
        mach_port_t ports[EXC_TYPES_COUNT];
        exception_behavior_t behaviors[EXC_TYPES_COUNT];
        thread_state_flavor_t flavors[EXC_TYPES_COUNT];
        mach_msg_type_number_t count = EXC_TYPES_COUNT;

        kern_return_t r = task_get_exception_ports(mach_task_self(), EXC_MASK_ALL,
            masks, &count, ports, behaviors, flavors);

        mach_port_t port;
        if ((r = mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &port)))
        {
            fprintf(stderr, "[BionicSX2] mach_port_allocate: %x (Audit Sec 6.2)\n", r);
            return false;
        }

        std::thread sig_thread(SignalHandler, port);
        sig_thread.detach();

        if ((r = mach_port_insert_right(mach_task_self(), port, port, MACH_MSG_TYPE_MAKE_SEND)))
        {
            mach_port_deallocate(mach_task_self(), port);
            fprintf(stderr, "[BionicSX2] mach_port_insert_right: %x (Audit Sec 6.2)\n", r);
            return false;
        }

        task_set_exception_ports(mach_task_self(), EXC_MASK_BAD_ACCESS, MACH_PORT_NULL, EXCEPTION_DEFAULT, THREAD_STATE_NONE);

        if ((r = thread_set_exception_ports(mach_thread_self(), EXC_MASK_BAD_ACCESS, port,
                 EXCEPTION_STATE | MACH_EXCEPTION_CODES, THREAD_STATE64)))
        {
            mach_port_deallocate(mach_task_self(), port);
            fprintf(stderr, "[BionicSX2] thread_set_exception_ports: %x (Audit Sec 6.2)\n", r);
            return false;
        }

        mach_port_t previous;
        if ((r = mach_port_request_notification(mach_task_self(), port, MACH_NOTIFY_NO_SENDERS, 0,
                 port, MACH_MSG_TYPE_MAKE_SEND_ONCE, &previous)))
        {
            mach_port_deallocate(mach_task_self(), port);
            fprintf(stderr, "[BionicSX2] mach_port_request_notification: %x (Audit Sec 6.2)\n", r);
            return false;
        }

        s_installed = true;
        s_port = port;
        return true;
    }

    bool InstallSecondaryThread(void)
    {
        kern_return_t r = thread_set_exception_ports(mach_thread_self(), EXC_MASK_BAD_ACCESS,
            s_port, EXCEPTION_STATE | MACH_EXCEPTION_CODES, THREAD_STATE64);
        if (r)
        {
            fprintf(stderr, "[BionicSX2] thread_set_exception_ports(secondary): %x (Audit Sec 6.2)\n", r);
            return false;
        }
        return true;
    }

#endif // USE_MACH_EXCEPTION_PORTS
} // namespace PageFaultHandler
