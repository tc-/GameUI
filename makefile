all: build test

build:
	mkdir -p build
	cd build && cmake ../

test:
	cd build && make gameuitest
	cp build/test/gameuitest test/

codeblocks:
	cmake -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug .

.PHONY: test
