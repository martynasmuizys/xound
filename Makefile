BUILD_ROOT := build

clean:
	rm -rf $(BUILD_ROOT)

debug:
	cmake -S . -B $(BUILD_ROOT) -G 'Ninja Multi-Config'
	cmake --build $(BUILD_ROOT) --config Debug

release:
	cmake -S . -B $(BUILD_ROOT) -G 'Ninja Multi-Config'
	cmake --build $(BUILD_ROOT) --config Release

run: debug
	$(BUILD_ROOT)/Debug/zoundboard
