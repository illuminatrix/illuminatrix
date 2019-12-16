# SPDX-License-Identifier: MIT

BUILD_DIR := $(CURDIR)/build
LINKER_SCRIPT := tools/ld/multiboot/linker.ld
GRUB_CONFIG := tools/grub/grub.cfg

all: | build_dir kernel.bin

build_dir:
	@mkdir -p $(BUILD_DIR)

kernel.bin: boot_objects
	# --nmagic: disables the automatic section alignment in the executable, to help GRUB find the Multiboot header
	#           We can also use ALIGN in the script lets use do it in one place
	#  --gc-sections to remove unused program sections
	ld \
		--nmagic \
		--gc-sections \
		-o $(BUILD_DIR)/kernel.bin -T \
		$(LINKER_SCRIPT) \
		$(shell find $(BUILD_DIR) -name '*.o')

boot_objects:
	@cd boot; BUILD_DIR=$(BUILD_DIR) make all

iso: kernel.bin
	@mkdir -p "$(BUILD_DIR)/iso_disk_files/boot/grub"
	cp $(GRUB_CONFIG) $(BUILD_DIR)/iso_disk_files/boot/grub/grub.cfg
	cp $(BUILD_DIR)/kernel.bin $(BUILD_DIR)/iso_disk_files/boot/kernel.bin
	grub-mkrescue -o $(BUILD_DIR)/disk.iso $(BUILD_DIR)/iso_disk_files

run: iso
	qemu-system-x86_64 -cdrom "$(BUILD_DIR)/disk.iso"

sections: $(BUILD_DIR)/kernel.bin
	readelf --sections $(BUILD_DIR)/kernel.bin

clean:
	rm -rf $(BUILD_DIR)
