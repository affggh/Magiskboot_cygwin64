#pragma once

#ifndef __CYGWIN__ // Add by affggh
#include <sys/syscall.h>
#include <linux/fcntl.h>
#else
#include <sys/fcntl.h>
#endif // __CYGWIN__

#include <unistd.h>
#include <cerrno>
#include <cstdio>

// Add by affggh
// Cygwin compiled magiskboot do not need these functions
#if !defined(__CYGWIN__)
static inline int sigtimedwait(const sigset_t* set, siginfo_t* info, const timespec* timeout) {
    union {
        sigset_t set;
        sigset_t set64;
    } s{};
    s.set = *set;
    return syscall(__NR_rt_sigtimedwait, &s.set64, info, timeout, sizeof(sigset64_t));
}

static inline int fexecve(int fd, char* const* argv, char* const* envp) {
    syscall(__NR_execveat, fd, "", argv, envp, AT_EMPTY_PATH);
    if (errno == ENOSYS) {
        char buf[256];
        std::snprintf(buf, sizeof(buf), "/proc/self/fd/%d", fd);
        execve(buf, argv, envp);
    }
    return -1;
}
#endif // __CYGWIN__
