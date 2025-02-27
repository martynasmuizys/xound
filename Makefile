BUILD_ROOT := build
TARGET := linux

clean:
	rm -rf $(BUILD_ROOT)

debug:
ifeq ($(TARGET), linux)
	cmake --no-warn-unused-cli -S . -B $(BUILD_ROOT)/linux -G 'Ninja Multi-Config'
	cmake --build $(BUILD_ROOT)/linux --config Debug
else
	cmake --no-warn-unused-cli -D CMAKE_TOOLCHAIN_FILE=windows.cmake -S . -B $(BUILD_ROOT)/windows -G 'Ninja Multi-Config'
	cmake --build $(BUILD_ROOT)/windows --config Debug
endif

release:
ifeq ($(TARGET), linux)
	cmake --no-warn-unused-cli -S . -B $(BUILD_ROOT)/linux -G 'Ninja Multi-Config'
	cmake --build $(BUILD_ROOT)/linux --config Release
else
	cmake --no-warn-unused-cli -D CMAKE_TOOLCHAIN_FILE=windows.cmake -S . -B $(BUILD_ROOT)/windows -G 'Ninja Multi-Config'
	cmake --build $(BUILD_ROOT)/windows --config Release
endif

run: debug
	$(BUILD_ROOT)/linux/Debug/xound
