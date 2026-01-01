#include "../include/filesystem/msdospart.h"

/*
This code implements the function that reads
the Master Boot Record (MBR) from an ATA hard drive and prints its contents in
both raw and formatted forms. It also checks the validity of the MBR by
verifying its magic number and prints information about the primary partitions.
*/

namespace uqaabOS {
namespace filesystem {

void MSDOSPartitionTable::read_partitions(driver::ATA *hd) {
    MasterBootRecord mbr;

    libc::printf("Reading MBR...\n");

    // Read the MBR from the hard drive into the mbr variable
    hd->read28(0, (uint8_t *)&mbr, sizeof(MasterBootRecord));

    // Debugging: Print the raw magic number and partition IDs
    libc::printf("MBR Magic Number: 0x%X\n", mbr.magicnumber);

    // Check if the MBR's magic number is valid (0xAA55)
    if (mbr.magicnumber != 0xAA55) {
        libc::printf("Illegal MBR (Magic Number: 0x%X)\n", mbr.magicnumber);
        return; // Invalid MBR, return early
    }

    // Debugging: Print partition information
    for (int i = 0; i < 4; i++) {
        libc::printf("Partition %d: ", i);

        // Check if the partition is bootable
        if (mbr.primary_partitions[i].bootable == 0x80) {
            libc::printf("Bootable. Type ");
        } else {
            libc::printf("Not bootable. Type ");
        }

        // Print the partition type
        libc::print_hex(mbr.primary_partitions[i].partition_id);
        libc::printf("\n");
    }
}

uint32_t MSDOSPartitionTable::get_first_fat32_partition_lba(driver::ATA *hd) {
    MasterBootRecord mbr;

    // Read the MBR from the hard drive into the mbr variable
    hd->read28(0, (uint8_t *)&mbr, sizeof(MasterBootRecord));

    // Check if the MBR's magic number is valid (0xAA55)
    if (mbr.magicnumber != 0xAA55) {
        // Return 0 if the MBR is invalid
        libc::printf("Invalid MBR (Magic Number: 0x%X)\n", mbr.magicnumber);
        return 0;
    }

    // Look for the first FAT32 partition (type 0x0B or 0x0C)
    for (int i = 0; i < 4; i++) {
        uint8_t partition_id = mbr.primary_partitions[i].partition_id;

        // Debugging: Print partition ID to see which partition types are detected
        libc::printf("Partition %d - Type: 0x%X\n", i, partition_id);

        // Check if the partition type is FAT32 (0x0B or 0x0C)
        if (partition_id == 0x0B || partition_id == 0x0C) {
            uint32_t start_lba = mbr.primary_partitions[i].start_lba;

            // Ensure the start LBA is valid (non-zero)
            if (start_lba != 0) {
                libc::printf("FAT32 partition found: Partition %d, LBA: 0x%X\n", i, start_lba);
                return start_lba; // Return the start LBA of the first FAT32 partition found
            }
        }
    }

    // If no FAT32 partition is found, return 0
    libc::printf("No FAT32 partition found.\n");
    return 0; // No FAT32 partition found
}

} // namespace filesystem
} // namespace uqaabOS
