# SPDX-License-Identifier: MIT


SOURCES =  $(shell find * -name '*.S')
OBJECTS = $(addprefix $(BUILD_DIR)/,$(SOURCES:.S=.o))

all: $(OBJECTS)

$(OBJECTS): $(BUILD_DIR)/%.o: %.S
	mkdir -p $(@D)
	as $< -o $@
