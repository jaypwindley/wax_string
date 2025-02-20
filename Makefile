.PHONY: default lib test install uninstall clean

# Select build type.
BUILD_DIR := build
ifeq ($(origin BUILD_TYPE), undefined)
  BUILD_TYPE := Release
endif

# Select compiler.
CC   := clang
CXX  := clang++
ifeq (, $(shell which $(CC)))
CC   := gcc
CXX  := g++
endif

# Set installation directory if not provided on command line.
INSTALL_ROOT ?= /usr/local
INSTALL_INC  := $(INSTALL_ROOT)/include/wax
INSTALL_LIB  := $(INSTALL_ROOT)/lib

default: lib

lib:
	mkdir -p $(BUILD_DIR)
	cmake -B $(BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_CXX_COMPILER=$(CXX)
	cmake --build $(BUILD_DIR) --config $(BUILD_TYPE) --parallel

test: lib
	mkdir -p ./test/$(BUILD_DIR)
	cmake -B ./test/$(BUILD_DIR) test -DBUILD_DIR=$(BUILD_DIR) \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_CXX_COMPILER=$(CXX)
	cmake --build ./test/$(BUILD_DIR) --parallel
	./test/$(BUILD_DIR)/unit-tests

install: lib
	install -d "$(INSTALL_INC)"
	@cd src && find str -type d | xargs -I TAIL install -v -d "$(INSTALL_INC)/TAIL"
	@cd src && find str -type f | xargs -I TAIL install -C -v TAIL "$(INSTALL_INC)/TAIL"
	install -C $(BUILD_DIR)/libwax-string.so "$(INSTALL_LIB)"
	install -C $(BUILD_DIR)/libwax-string-static.a "$(INSTALL_LIB)"
	@ldconfig

uninstall:
	rm -f $(INSTALL_LIB)/libwax-string.so
	rm -f $(INSTALL_LIB)/libwax-string-static.a
	ldconfig
	rm -rf $(INSTALL_INC)/str

clean:
	find . -type d -name $(BUILD_DIR) -exec rm -rf {} \; -prune
