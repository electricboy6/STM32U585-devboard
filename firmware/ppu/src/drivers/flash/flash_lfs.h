#pragma once

#include "lfs/lfs.h"
#include "flash.h"

static byte read_buf[flash::BLOCK_SIZE];
static byte prog_buf[flash::BLOCK_SIZE];
static byte lookahead_buf[32];

static lfs_t lfs;

struct lfs_stat_t {
    lfs_size_t block_size;
    lfs_size_t block_count;
    lfs_size_t blocks_used;
};

namespace lfs_hal {
    int read(const struct lfs_config* cfg, lfs_block_t block, lfs_off_t off, void* buf, lfs_size_t size);
    int prog(const struct lfs_config* cfg, lfs_block_t block, lfs_off_t off, const void* buf, lfs_size_t size);
    int erase(const struct lfs_config* cfg, lfs_block_t block);
    int sync(const struct lfs_config* cfg);
}

namespace flash_lfs {
    // also garbage collects - will take a bit, but shouldn't be in critical paths anyways
    int mount(bool format);
    int unmount();

    int open(lfs_file_t* file, const char* path, int flags);
    int opencfg(lfs_file_t* file, const char* path, int flags, const struct lfs_file_config* config);
    int read(lfs_file_t* file, void* buf, lfs_size_t size);
    int write(lfs_file_t* file, const void* buf, lfs_size_t size);
    int close(lfs_file_t* file);
    int truncate(lfs_file_t* file, lfs_off_t size);
    lfs_soff_t seek(lfs_file_t* file, lfs_soff_t off, int whence);
    lfs_soff_t tell(lfs_file_t* file);
    int rewind(lfs_file_t* file);
    int flush(lfs_file_t* file);
    lfs_soff_t size(lfs_file_t* file);

    int remove(const char* path);
    int move(const char* oldpath, const char* newpath);

    int fsStat(struct lfs_stat_t* stat);
    
    int stat(const char* path, struct lfs_info* info);
    lfs_ssize_t getattr(const char* path, byte type, void* buf, lfs_size_t size);
    int setattr(const char* path, byte type, const void* buf, lfs_size_t size);
    int removeattr(const char* path, byte type);

    int mkdir(const char* path);
    lfs_dir_t* chdir(const char* path);
    int closeDir(lfs_dir_t* dir);
    int readDir(lfs_dir_t* dir, struct lfs_info* info);
    int seekDir(lfs_dir_t* dir, lfs_off_t off);
    lfs_soff_t tellDir(lfs_dir_t* dir);
    int rewindDir(lfs_dir_t* dir);
}