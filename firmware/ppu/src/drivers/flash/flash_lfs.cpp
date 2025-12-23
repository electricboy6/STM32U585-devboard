#include "flash_lfs.h"

const struct lfs_config config = {
    .read = lfs_hal::read,
    .prog = lfs_hal::prog,
    .erase = lfs_hal::erase,
    .sync = lfs_hal::sync,

    .read_size      = flash::PAGE_SIZE,
    .prog_size      = flash::PAGE_SIZE, 
    .block_size     = flash::BLOCK_SIZE,
    .block_count    = flash::EFLASH_SIZE / flash::BLOCK_SIZE,

    .block_cycles   = 500, // 100-1000, lower numbers = better wear leveling, higher numbers = better performance

    .cache_size     = flash::BLOCK_SIZE,
    .lookahead_size = 32,  // must be a multiple of 8

    .read_buffer = read_buf,
    .prog_buffer = prog_buf,
    .lookahead_buffer = lookahead_buf,
};

// -------------------- HAL --------------------
int lfs_hal::read(const struct lfs_config* cfg, lfs_block_t block, lfs_off_t off, void* buf, lfs_size_t size) {
    if(block >= flash::PAGE_COUNT || off + size > cfg->block_size) {
        return LFS_ERR_IO;
    }

    flash::readBytes(block * cfg->block_size + off, buf, size);

    return LFS_ERR_OK;
}
int lfs_hal::prog(const struct lfs_config* cfg, lfs_block_t block, lfs_off_t off, const void* buf, lfs_size_t size) {
    if(block >= flash::PAGE_COUNT) {
        return LFS_ERR_IO;
    }

    flash::writeBytes(block * cfg->block_size + off, buf, size);

    return LFS_ERR_OK;
}
int lfs_hal::erase(const struct lfs_config* cfg, lfs_block_t block) {
    if(block >= cfg->block_count) {
        return LFS_ERR_IO;
    }

    flash::blockErase4K(block * cfg->block_size);

    return LFS_ERR_OK;
}
int lfs_hal::sync(const struct lfs_config* cfg) {
    UNUSED(cfg);
    return LFS_ERR_OK;
}
// -------------------- END HAL --------------------
int flash_lfs::mount(bool format) {
    int err;
    if(format) {
        err = lfs_format(&lfs, &config);
        if(err) return err;
    }
    err = lfs_mount(&lfs, &config);
    if(err) return err;
    return lfs_fs_gc(&lfs);
}
int flash_lfs::unmount() {
    return lfs_unmount(&lfs);
}
int flash_lfs::open(lfs_file_t* file, const char* path, int flags) {
    return lfs_file_open(&lfs, file, path, flags);
}
int flash_lfs::opencfg(lfs_file_t* file, const char* path, int flags, const struct lfs_file_config* config) {
    return lfs_file_opencfg(&lfs, file, path, flags, config);
}
int flash_lfs::read(lfs_file_t* file, void* buf, lfs_size_t size) {
    return lfs_file_read(&lfs, file, buf, size);
}
int flash_lfs::rewind(lfs_file_t* file) {
    return lfs_file_rewind(&lfs, file);
}
int flash_lfs::write(lfs_file_t* file, const void* buf, lfs_size_t size) {
    return lfs_file_write(&lfs, file, buf, size);
}
int flash_lfs::close(lfs_file_t* file) {
    return lfs_file_close(&lfs, file);
}
int flash_lfs::flush(lfs_file_t* file) {
    return lfs_file_sync(&lfs, file);
}
int flash_lfs::truncate(lfs_file_t* file, lfs_off_t size) {
    return lfs_file_truncate(&lfs, file, size);
}
lfs_soff_t flash_lfs::seek(lfs_file_t* file, lfs_soff_t off, int whence) {
    return lfs_file_seek(&lfs, file, off, whence);
}
lfs_soff_t flash_lfs::tell(lfs_file_t* file) {
    return lfs_file_tell(&lfs, file);
}
lfs_soff_t flash_lfs::size(lfs_file_t* file) {
    return lfs_file_size(&lfs, file);
}

int flash_lfs::remove(const char* path) {
    return lfs_remove(&lfs, path);
}
int flash_lfs::move(const char* oldpath, const char* newpath) {
    return lfs_rename(&lfs, oldpath, newpath);
}

int flash_lfs::fsStat(struct lfs_stat_t* stat) {
    stat->block_count = config.block_count;
    stat->block_size = config.block_size;
    stat->blocks_used = lfs_fs_size(&lfs);
    return LFS_ERR_OK;
}

int flash_lfs::stat(const char* path, struct lfs_info* info) {
    return lfs_stat(&lfs, path, info);
}
lfs_ssize_t flash_lfs::getattr(const char* path, byte type, void* buf, lfs_size_t size) {
    return lfs_getattr(&lfs, path, type, buf, size);
}
int flash_lfs::setattr(const char* path, byte type, const void* buf, lfs_size_t size) {
    return lfs_setattr(&lfs, path, type, buf, size);
}
int flash_lfs::removeattr(const char* path, byte type) {
    return lfs_removeattr(&lfs, path, type);
}

int flash_lfs::mkdir(const char* path) {
    return lfs_mkdir(&lfs, path);
}
lfs_dir_t* flash_lfs::chdir(const char* path) {
    lfs_dir_t* dir = (lfs_dir_t*)lfs_malloc(sizeof(lfs_dir_t));
    // make sure malloc succeeded
    if(!dir) return (lfs_dir_t*)-1;
    if(lfs_dir_open(&lfs, dir, path) != LFS_ERR_OK) {
        lfs_free(dir);
        return (lfs_dir_t*)-1;
    }
    return dir;
}
int flash_lfs::closeDir(lfs_dir_t* dir)  {
    return lfs_dir_close(&lfs, dir);
    lfs_free(dir);
}
int flash_lfs::readDir(lfs_dir_t* dir, struct lfs_info* info) {
    return lfs_dir_read(&lfs, dir, info);
}
int flash_lfs::seekDir(lfs_dir_t* dir, lfs_off_t off) {
    return lfs_dir_seek(&lfs, dir, off);
}
lfs_soff_t flash_lfs::tellDir(lfs_dir_t* dir) {
    return lfs_dir_tell(&lfs, dir);
}
int flash_lfs::rewindDir(lfs_dir_t* dir) {
    return lfs_dir_rewind(&lfs, dir);
}