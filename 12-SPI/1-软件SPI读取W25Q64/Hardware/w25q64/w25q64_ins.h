# ifndef _W25Q64_INS_H
# define _W25Q64_INS_H

# define W25Q64_WRITE_ENABLE                                0x06
# define W25Q64_WRITE_DISABLE                               0x04
# define W25Q64_READ_STATUS_REGISTEP_1                      0x05
# define W25Q64_READ_STATUS_REGISTEP_2                      0x35
# define W25Q64_WRITE_STATUS_REGISTEP                       0x01
# define W25Q64_PAGE_PROGRAM                                0x02
# define W25Q64_QUAD_PAGE_PROGRAM                           0x32
# define W25Q64_BLOCK_ERASE_64KB                            0xd8
# define W25Q64_BLOCK_ERASE_32KB                            0x52
# define W25Q64_SECTOR_ERASE_4KB                            0x20
# define W25Q64_CHIP_ERASE                                  0xc7
# define W25Q64_ERASE_SUSPEND                               0x75
# define W25Q64_POWER_DOWN                                  0xb9
# define W25Q64_HIGH_PERFORMANCE_MODE                       0xa3
# define W25Q64_CONTINUONS_READ_MODE_RESET                  0xff
# define W25Q64_RELEASE_POWER_DOWN_OR_HPM_DEVICE_ID         0xab
# define MANUFACTURER_DEVICE_ID                             0x90
# define W25Q64_READ_UNIQUE_ID                              0x4b
# define W25Q64_JEDEC_ID                                    0x9f

# define W25Q64_READ_DATA                                   0x03
# define W25Q64_FAST_READ                                   0x0b
# define W25Q64_FAST_READ_DUAL_OUTPUT                       0x3b
# define W25Q64_FAST_READ_DUAL_IO                           0xbb
# define W25Q64_FAST_READ_QUAD_OUTPUT                       0x6b
# define W25Q64_FAST_READ_QUAD_IO                           0xeb
# define W25Q64_OCTAL_WORD_READ_QUAD_IO                     0xe3

# define W25Q64_DUMMY_BYTE                                  0xff

# endif /*_W25Q64_INS_H*/
