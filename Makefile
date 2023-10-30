.PHONY: config configure build release clean rebuild run lldb debug doc windows scripting package
BUILD_SYSTEM = Ninja
MSVC_CONFIG_TYPE = Debug
all: build run
configure:
	@cmake . -B build -D CMAKE_BUILD_TYPE=Debug -G $(BUILD_SYSTEM)
build:
	@cmake --build build --config $(MSVC_CONFIG_TYPE)
install:
	@cmake --install build --config $(MSVC_CONFIG_TYPE)
clean:
	@ - rm -rf build
rebuild: clean configure build