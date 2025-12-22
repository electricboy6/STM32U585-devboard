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

    .cache_size     = flash::BLOCK_SIZE / 2,
    .lookahead_size = 32,  // must be a multiple of 8

    .read_buffer = read_buf,
    .prog_buffer = prog_buf,
    .lookahead_buffer = lookahead_buf,
};

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