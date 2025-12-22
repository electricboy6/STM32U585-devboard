#pragma once

#include "lfs/lfs.h"
#include "flash.h"

#define LFS_NAME_MAX 32

static byte read_buf[flash::BLOCK_SIZE / 2];
static byte prog_buf[flash::BLOCK_SIZE / 2];
static byte lookahead_buf[32];

static lfs_t lfs;

namespace lfs_hal {
    int read(const struct lfs_config* cfg, lfs_block_t block, lfs_off_t off, void* buf, lfs_size_t size);
    int prog(const struct lfs_config* cfg, lfs_block_t block, lfs_off_t off, const void* buf, lfs_size_t size);
    int erase(const struct lfs_config* cfg, lfs_block_t block);
    int sync(const struct lfs_config* cfg);
}

namespace flash_lfs {
    int mount(bool format);
    int unmount();

    int open(lfs_file_t* file, const char* path, int flags);
    int read(lfs_file_t* file, void* buf, lfs_size_t size);
    int rewind(lfs_file_t* file);
    int write(lfs_file_t* file, const void* buf, lfs_size_t size);
    int close(lfs_file_t* file);

    int remove(const char* path);
    int rename(const char* oldpath, const char* newpath);

    int flush(lfs_file_t* file);
    int fsStat(struct littlfs_fsstat_t* stat);
    lfs_soff_t seek(lfs_file_t* file, lfs_soff_t off, int whence);
    int truncate(lfs_file_t* file, lfs_off_t size);
    lfs_soff_t tell(lfs_file_t* file);
    int stat(const char* path, struct lfs_info* info);
    lfs_ssize_t getattr(const char* path, byte type, void* buf, lfs_size_t size);
    int setattr(const char* path, byte type, const void* buf, lfs_size_t size);
    int removeattr(const char* path, byte type);
    int opencfg(lfs_file_t* file, const char* path, int flags, const struct lfs_file_config* config);
    lfs_soff_t size(lfs_file_t* file);

    int mkdir(const char* path);
    int openDir(const char* path);
    int closeDir(int dir);
    int readDir(int dir, struct lfs_info* info);
    int seekDir(int dir, lfs_off_t off);
    lfs_soff_t tellDir(int dir);
    int rewindDir(int dir);
}