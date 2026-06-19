#include <ph_random.h>
#include <ph_malloc.h>
#include "../../../../../sys/i_fs.h"

#include "stubs.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type", "-Wunused-variable"

int
strncasecmp(const char *s1, const char *s2, size_t len)
{
}
size_t
strspn(const char *s, const char *accept)
{
}
int
isgraph(int c)
{
}
int
isalnum(int c)
{
}
size_t
strcspn(const char *s, const char *reject)
{
}
unsigned long int
strtoul(const char *nptr, char **endptr, int base)
{
}

// Pretty much everything below is for WASI (to compile)

errno_t errno = 0;
FILE *stderr = 0;

int
fsync(int)
{
}
off_t
lseek(int, off_t, int)
{
}
ssize_t
pread(int fd, void *buf, size_t n, off_t offset)
{
    (void)offset;

    return fs_read(fd, buf, n);
}
ssize_t
pwrite(int fd, void const *buf, size_t n, off_t offset)
{
    (void)offset;
    return fs_write(fd, buf, n);
}
char *
strerror(errno_t num)
{
}
int
clock_gettime(clockid_t clk_id, struct timespec *tp)
{
    /* TODO Implement clk_id handling. */
    (void)clk_id;

    bigtime_t us = hal_system_time();

    u_int64_t seconds = us / 1000000UL;
    u_int64_t nanoseconds = (us % 1000000UL) * 1000UL;

    *tp = (struct timespec){
        .tv_sec = seconds,
        .tv_nsec = nanoseconds,
    };

    return 0;
}
int
linkat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath,
       int flags)
{
}
ssize_t
readlinkat(int dirfd, const char *pathname, char *buf, size_t bufsiz)
{
    ssize_t out = fs_readlinkat(dirfd, pathname, buf, bufsiz);

    if (out <= 0) {
        errno = EINVAL;
        out = -1;
    }

    return out;
}
int
symlinkat(const char *target, int newdirfd, const char *linkpath)
{
}
int
unlinkat(int dirfd, const char *pathname, int flags)
{
}
int
renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath)
{
}
int
mkdirat(int dirfd, const char *pathname, mode_t mode)
{
}
int
posix_fallocate(int fd, off_t offset, off_t len)
{
}
int
utimensat(int dirfd, const char *pathname, const struct timespec times[2],
          int flags)
{
}
int
futimens(int fd, const struct timespec times[2])
{
}
int
clock_getres(clockid_t clockid, struct timespec *res)
{
}
int
getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{
}
int
fcntl(int fd, int cmd, ...)
{
    if (cmd == F_GETFL) {
        return O_RDWR;
    }

    return 0;
}
int
closedir(DIR *dirp)
{
}
ssize_t
readv(int fd, const struct iovec *iov, int iovcnt)
{
}
ssize_t
writev(int fd, const struct iovec *iov, int iovcnt)
{
    size_t bufsize = 0;
    size_t bufcopied = 0;
    void *buf = 0;
    ssize_t rc = 0;

    for (int i = 0; i < iovcnt; ++i)
        bufsize += iov[i].iov_len;

    buf = ph_malloc(bufsize);
    if (!buf)
        return -1;

    for (int i = 0; i < iovcnt; ++i) {
        ph_memcpy(buf + bufcopied, iov[i].iov_base, iov[i].iov_len);
        bufcopied += iov[i].iov_len;
    }

    rc = pwrite(fd, buf, bufsize, 0);

    ph_free(buf);
    buf = 0;

    return rc;
}
int
ftruncate(int fd, off_t length)
{
}
int
open(const char *path, int flags, ...)
{
    return fs_open(path, flags);
}
int
openat(int dirfd, const char *pathname, int flags, ...)
{
    (void)dirfd;

    int open_flags = (flags & O_CREAT) ? OPEN_MODE_CREATE : 0;
    open_flags |= OPEN_MODE_RDWR;

    return fs_open(pathname, open_flags);
}
char *
realpath(const char *path, char *resolved_path)
{
    /* TODO need a proper POSIX implementation of realpath() */
    ph_strncpy(resolved_path, path, PATH_MAX);
    return resolved_path;
}
int
fstatat(int dirfd, const char *pathname, struct stat *buf, int flags)
{
}
int
shutdown(int sockfd, int how)
{
}
int
sched_yield(void)
{
}
ssize_t
sendmsg(int sockfd, const struct msghdr *msg, int flags)
{
}
int
raise(int sig)
{
}
ssize_t
recvmsg(int sockfd, struct msghdr *msg, int flags)
{
}
DIR *
fdopendir(int fd)
{
}
void
rewinddir(DIR *dirp)
{
}
void
seekdir(DIR *dirp, long offset)
{
}
struct dirent *
readdir(DIR *dirp)
{}
long
telldir(DIR *dirp)
{
}
int
fputs(const char *str, FILE *stream)
{
}
int
nanosleep(const struct timespec *req, struct timespec *rem)
{
}
int
poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
}
int
fstat(int fd, struct stat *buf)
{
    if (fd < 3) {
        buf->st_mode = S_IFCHR | 0666;
        buf->st_nlink = 1;
        buf->st_size = 0;

        return 0;
    }

    return fs_fstat(fd, buf);
}
int
ioctl(int fd, unsigned long request, ...)
{
}
int
close(int fd)
{
    fs_close(fd);
    return 0;
}
size_t
fwrite(const void *buffer, size_t size, size_t count, FILE *stream)
{
}

int
pthread_rwlock_init(pthread_rwlock_t *rwlock, void *attr)
{
    hal_mutex_init(rwlock, 0);
}
int
pthread_rwlock_destroy(pthread_rwlock_t *rwlock)
{
    hal_mutex_destroy(rwlock);
}
int
pthread_rwlock_wrlock(pthread_rwlock_t *rwlock)
{
    hal_mutex_lock(rwlock);
}
int
pthread_rwlock_rdlock(pthread_rwlock_t *rwlock)
{
    hal_mutex_lock(rwlock);
}
int
pthread_rwlock_unlock(pthread_rwlock_t *rwlock)
{
    hal_mutex_unlock(rwlock);
}

// idk why but here is an actual implementation (should be based on hardware
// tho)
ssize_t
getrandom(void *buf, size_t buflen, unsigned int flags)
{
    unsigned char *ptr = (unsigned char *)buf;
    for (size_t i = 0; i < buflen; i++) {
        ptr[i] = (unsigned char)(ph_random() % 256);
    }
    return buflen;
}

#pragma GCC diagnostic pop
#warning Unimplemented functions
