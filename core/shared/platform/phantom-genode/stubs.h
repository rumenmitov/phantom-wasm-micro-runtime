#ifndef GENODE_STUBS_H
#define GENODE_STUBS_H

#include <ph_string.h>
#include <ph_time.h>
#include <errno.h>
#include <kernel/mutex.h>

#include "stats.h"

// ################ JUST DECLARED ##################

// These 4 functions (including strtoul() below) are only used in
// `wasm_application_execute_func` function As long as we don't use it, these
// can be left alone

unsigned long long int
strtoull(const char *nptr, char **endptr, int base);

double
strtod(const char *str, char **endptr);

float
strtof(const char *str, char **endptr);

// these two seem to only be used for AOT execution
void
os_signal_unmask();
void
os_sigreturn();

// ################## STUBBED ####################

// needed for assertions to terminate program. I'd say not essential
static inline void
abort(void) {};

// these are for built-in libc feature
int
strncasecmp(const char *s1, const char *s2, size_t len);
size_t
strspn(const char *s, const char *accept);
int
isgraph(int c);
int
isalnum(int c);
size_t
strcspn(const char *s, const char *reject);
unsigned long int
strtoul(const char *nptr, char **endptr, int base);

// these are just for WASI

typedef int clockid_t;
typedef void *DIR;
typedef int socklen_t;
struct iovec {
    void *iov_base;
    size_t iov_len;
};
typedef int socktype;
struct msghdr {
    // void *msg_name;
    // socklen_t msg_namelen;
    struct iovec *msg_iov;
    int msg_iovlen;
    // void *msg_control;
    // socklen_t msg_controllen;
    int msg_flags;
};
struct dirent {
    long d_ino;
    unsigned short d_type;
    char d_name[1];
};
struct pollfd {
    int fd;
    short events;
    short revents;
};
typedef int FILE;
typedef unsigned long nfds_t;
typedef hal_mutex_t pthread_rwlock_t;

#define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#define S_ISCHR(m) (((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m) (((m) & S_IFMT) == S_IFBLK)
#define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
#define S_ISSOCK(m) (((m) & S_IFMT) == S_IFSOCK)

#define F_GETFL 3

#define O_RDWR 2
#define O_CREAT 0100

#define SO_TYPE 0x1008
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOCK_RAW 3
#define SOCK_RDM 4
#define SOCK_SEQPACKET 5
#define O_NONBLOCK 04000
#define O_SYNC 04010000
#define O_DIRECTORY 0200000
#define O_NOFOLLOW 0400000
#define SOL_SOCKET 0xffff
#define SHUT_RD 0
#define SHUT_WR 1
#define SHUT_RDWR 2
#define MSG_PEEK 0x0002
#define MSG_WAITALL 0x0100
#define MSG_TRUNC 0x0020
#define AT_SYMLINK_FOLLOW 0x400
#define AT_REMOVEDIR 0x200
#define AT_SYMLINK_NOFOLLOW 0x100
#define DT_FIFO 1
#define DT_CHR 2
#define DT_DIR 4
#define DT_BLK 6
#define DT_REG 8
#define DT_LNK 10
#define UTIME_NOW 0x3fffffff
#define UTIME_OMIT 0x3ffffffe
#define POLLRDNORM 0x040
#define POLLWRNORM 0x100
#define POLLERR 0x008
#define POLLHUP 0x010
#define POLLNVAL 0x020

#define SIGHUP 1       /* hangup */
#define SIGINT 2       /* interrupt */
#define SIGQUIT 3      /* quit */
#define SIGILL 4       /* illegal instr. (not reset when caught) */
#define SIGTRAP 5      /* trace trap (not reset when caught) */
#define SIGABRT 6      /* abort() */
#define SIGIOT SIGABRT /* compatibility */
#define SIGEMT 7       /* EMT instruction */
#define SIGFPE 8       /* floating point exception */
#define SIGKILL 9      /* kill (cannot be caught or ignored) */
#define SIGBUS 10      /* bus error */
#define SIGSEGV 11     /* segmentation violation */
#define SIGSYS 12      /* non-existent system call invoked */
#define SIGPIPE 13     /* write on a pipe with no one to read it */
#define SIGALRM 14     /* alarm clock */
#define SIGTERM 15     /* software termination signal from kill */
#define SIGURG 16      /* urgent condition on IO channel */
#define SIGSTOP 17     /* sendable stop signal not from tty */
#define SIGTSTP 18     /* stop signal from tty */
#define SIGCONT 19     /* continue a stopped process */
#define SIGCHLD 20     /* to parent on child stop or exit */
#define SIGTTIN 21     /* to readers pgrp upon background tty read */
#define SIGTTOU 22     /* like TTIN if (tp->t_local&LTOSTOP) */
#define SIGIO 23       /* input/output possible signal */
#define SIGXCPU 24     /* exceeded CPU time limit */
#define SIGXFSZ 25     /* exceeded file size limit */
#define SIGVTALRM 26   /* virtual time alarm */
#define SIGPROF 27     /* profiling time alarm */
#define SIGWINCH 28    /* window size changes */
#define SIGINFO 29     /* information request */
#define SIGUSR1 29     /* information request */
#define SIGUSR2 29     /* information request */

#define FIONREAD 0x541B
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1
#define CLOCK_PROCESS_CPUTIME_ID 2
#define CLOCK_THREAD_CPUTIME_ID 3
#define PATH_MAX 4096

#define ENOMSG 82           /* No message of desired type */
#define EIDRM 83            /* Identifier removed */
#define EBADMSG 84          /* Not a data message */
#define EPROTO 85           /* Protocol error */
#define ENOLINK 106         /* Link has been severed */
#define EMULTIHOP 110       /* Multihop attempted */
#define EOVERFLOW 112       /* Value too large for defined data type */
#define EILSEQ 116          /* Illegal byte sequence */
#define ECANCELED 131       /* Operation Cancelled */
#define ENOTSUP 134         /* Not supported */
#define EOWNERDEAD 136      /* Owner died */
#define ENOTRECOVERABLE 137 /* State not recoverable */

extern FILE *stderr;
extern errno_t errno;

int
linkat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath,
       int flags);
ssize_t
readlinkat(int dirfd, const char *pathname, char *buf, size_t bufsiz);
int
symlinkat(const char *target, int newdirfd, const char *linkpath);
int
unlinkat(int dirfd, const char *pathname, int flags);
int
renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath);
int
mkdirat(int dirfd, const char *pathname, mode_t mode);
int
posix_fallocate(int fd, off_t offset, off_t len);
int
utimensat(int dirfd, const char *pathname, const struct timespec times[2],
          int flags);
int
futimens(int fd, const struct timespec times[2]);
int
clock_gettime(clockid_t clk_id, struct timespec *tp);
ssize_t
getrandom(void *buf, size_t buflen, unsigned int flags);
int
clock_getres(clockid_t clockid, struct timespec *res);
int
getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
int
fcntl(int fd, int cmd, ...);
int
closedir(DIR *dirp);
ssize_t
readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t
writev(int fd, const struct iovec *iov, int iovcnt);
int
ftruncate(int fd, off_t length);
int
open(const char *path, int flags, ...);
int
openat(int dirfd, const char *pathname, int flags, ...);
char *
realpath(const char *path, char *resolved_path);
int
fstatat(int dirfd, const char *pathname, struct stat *buf, int flags);
int
shutdown(int sockfd, int how);
int
sched_yield(void);
ssize_t
sendmsg(int sockfd, const struct msghdr *msg, int flags);
int
raise(int sig);
ssize_t
recvmsg(int sockfd, struct msghdr *msg, int flags);
DIR *
fdopendir(int fd);
void
rewinddir(DIR *dirp);
void
seekdir(DIR *dirp, long offset);
struct dirent *
readdir(DIR *dirp);
long
telldir(DIR *dirp);
int
fputs(const char *str, FILE *stream);
int
nanosleep(const struct timespec *req, struct timespec *rem);
int
poll(struct pollfd *fds, nfds_t nfds, int timeout);
int
fstat(int fd, struct stat *buf);
int
ioctl(int fd, unsigned long request, ...);
int
fsync(int);
off_t
lseek(int, off_t, int);
ssize_t
pread(int, void *, size_t, off_t);
ssize_t
pwrite(int, void const *, size_t, off_t);
int
close(int);
size_t
fwrite(const void *buffer, size_t size, size_t count, FILE *stream);

int
pthread_rwlock_init(pthread_rwlock_t *rwlock, void *attr);
int
pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
int
pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int
pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int
pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

#endif // GENODE_STUBS_H
