
all: | build_dir kernel.bin

BUILD_DIR := build

SOURCES =  $(shell find * -name '*.S')
OBJECTS = $(addprefix $(BUILD_DIR)/,$(SOURCES:.S=.o))

$(OBJECTS): $(BUILD_DIR)/%.o: %.S
	@mkdir -p $(@D)
	as $< -o $@

build_dir:
	@mkdir -p $(BUILD_DIR)

iso:
	mkdir -p "$(BUILD_DIR)/iso_disk_files/boot/grub"
	cp scripts/grub/grub.cfg $(BUILD_DIR)/iso_disk_files/boot/grub/grub.cfg
	cp $(BUILD_DIR)/kernel.bin $(BUILD_DIR)/iso_disk_files/boot/kernel.bin
	grub-mkrescue -o $(BUILD_DIR)/disk.iso $(BUILD_DIR)/iso_disk_files

kernel.bin: $(OBJECTS)
	ld -n -o $(BUILD_DIR)/kernel.bin -T \
		arch/x86_64/linker.ld \
		$(OBJECTS)

run: kernel.bin
	qemu-system-x86_64 -cdrom "$(BUILD_DIR)/disk.iso"

clean:
	rm -r $(BUILD_DIR)
