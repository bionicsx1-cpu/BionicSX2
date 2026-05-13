// PORTED FROM: common/Darwin/DarwinThreads.cpp — BionicSX2 iOS Port
// AUDIT REFERENCE: Section 5.3
// STATUS: GREEN — Mach semaphores and pthreads identical on iOS and macOS

#include <pthread.h>
#include <mach/mach.h>
#include <mach/mach_error.h>
#include <mach/mach_init.h>
#include <mach/mach_port.h>
#include <mach/mach_time.h>
#include <mach/semaphore.h>
#include <mach/task.h>
#include <mach/thread_act.h>
#include <sched.h>
#include <sys/time.h>
#include <unistd.h>

#include <cassert>
#include <cstdio>
#include <cstring>

// Audit Section 5.3: Mach semaphore — identical on iOS and macOS
// Ported from DarwinThreads.cpp:119-147

static void MACH_CHECK(kern_return_t mach_retval)
{
    if (mach_retval != KERN_SUCCESS)
    {
        fprintf(stderr, "[BionicSX2] mach error: %s (Audit Sec 5.3)\n", mach_error_string(mach_retval));
        assert(mach_retval == KERN_SUCCESS);
    }
}

// KernelSemaphore — Mach semaphore_create/destroy/wait/signal
// Audit Section 5.3: Ported from common/Darwin/DarwinThreads.cpp:119-147

typedef struct {
    semaphore_t m_sema;
} KernelSemaphore;

void KernelSemaphore_Create(KernelSemaphore* ks)
{
    MACH_CHECK(semaphore_create(mach_task_self(), &ks->m_sema, SYNC_POLICY_FIFO, 0));
}

void KernelSemaphore_Destroy(KernelSemaphore* ks)
{
    MACH_CHECK(semaphore_destroy(mach_task_self(), ks->m_sema));
}

void KernelSemaphore_Post(KernelSemaphore* ks)
{
    MACH_CHECK(semaphore_signal(ks->m_sema));
}

void KernelSemaphore_Wait(KernelSemaphore* ks)
{
    MACH_CHECK(semaphore_wait(ks->m_sema));
}

bool KernelSemaphore_TryWait(KernelSemaphore* ks)
{
    mach_timespec_t time = {};
    kern_return_t res = semaphore_timedwait(ks->m_sema, time);
    if (res == KERN_OPERATION_TIMED_OUT)
        return false;
    MACH_CHECK(res);
    return true;
}

// Audit Section 5.3: pthread wrappers — ported from DarwinThreads.cpp:164-278

void Thread_Sleep(int ms)
{
    usleep(1000 * ms);
}

// Audit Section 5.3: Set thread name (pthread_setname_np — works on iOS)
void Thread_SetName(const char* name)
{
    pthread_setname_np(name);
}

// Audit Section 5.3: Get thread CPU time via Mach thread_info

static uint64_t getthreadtime(thread_port_t thread)
{
    mach_msg_type_number_t count = THREAD_BASIC_INFO_COUNT;
    thread_basic_info_data_t info;

    kern_return_t kr = thread_info(thread, THREAD_BASIC_INFO,
        (thread_info_t)&info, &count);
    if (kr != KERN_SUCCESS)
        return 0;

    return (uint64_t)info.user_time.seconds * (uint64_t)1e6 +
           (uint64_t)info.user_time.microseconds +
           (uint64_t)info.system_time.seconds * (uint64_t)1e6 +
           (uint64_t)info.system_time.microseconds;
}

uint64_t Thread_GetCPUTime(void)
{
    return getthreadtime(pthread_mach_thread_np(pthread_self()));
}

uint64_t Thread_GetThreadCPUTime(pthread_t thread)
{
    return getthreadtime(pthread_mach_thread_np(thread));
}

// Audit Section 5.3: Yields the CPU timeslice
void Thread_Timeslice(void)
{
    sched_yield();
}

// Audit Section 5.3: ARM64 spin-wait hint — ported from DarwinThreads.cpp:39-42
void Thread_SpinWait(void)
{
#if defined(ARCH_ARM64)
    __asm__ __volatile__("isb");
#endif
}

// Audit Section 5.3: Thread creation — ported from DarwinThreads.cpp:229-254

typedef void* (*ThreadEntryPoint)(void*);

typedef struct {
    pthread_t handle;
} Thread;

bool Thread_Create(Thread* t, ThreadEntryPoint func, void* arg, uint32_t stackSize)
{
    pthread_attr_t attrs;
    bool hasAttributes = false;

    if (stackSize != 0)
    {
        hasAttributes = true;
        pthread_attr_init(&attrs);
        pthread_attr_setstacksize(&attrs, stackSize);
    }

    int res = pthread_create(&t->handle, hasAttributes ? &attrs : nullptr, func, arg);
    if (res != 0)
        return false;

    return true;
}

void Thread_Detach(Thread* t)
{
    pthread_detach(t->handle);
}

void Thread_Join(Thread* t)
{
    void* retval;
    pthread_join(t->handle, &retval);
}
