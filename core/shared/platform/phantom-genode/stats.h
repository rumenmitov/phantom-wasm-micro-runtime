#ifndef __STATS_H
#define __STATS_H

#define S_IFMT 0170000   // bit mask for the file type bit field
#define S_IFSOCK 0140000 // socket
#define S_IFLNK 0120000  // symbolic link
#define S_IFREG 0100000  // regular file
#define S_IFBLK 0060000  // block device
#define S_IFDIR 0040000  // directory
#define S_IFCHR 0020000  // character device
#define S_IFIFO 0010000  // FIFO
#define S_ISUID 04000    // set-user-ID bit (see execve(2))
#define S_ISGID 02000    // set-group-ID bit (see below)
#define S_ISVTX 01000    // sticky bit (see below)
#define S_IRWXU 00700    // owner has read, write, and execute permission
#define S_IRUSR 00400    // owner has read permission
#define S_IWUSR 00200    // owner has write permission
#define S_IXUSR 00100    // owner has execute permission
#define S_IRWXG 00070    // group has read, write, and execute permission
#define S_IRGRP 00040    // group has read permission
#define S_IWGRP 00020    // group has write permission
#define S_IXGRP 00010    // group has execute permission
#define S_IRWXO 00007    // others  (not  in group) have read, write, and exe‐
#define S_IROTH 00004    // others have read permission
#define S_IWOTH 00002    // others have write permission
#define S_IXOTH 00001    // others have execute permission

#include <ph_time.h>
struct stat {
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
    int st_mode;
    int st_size;
    int st_dev;
    int st_ino;
    int st_nlink;
};

#endif // __STATS_H
