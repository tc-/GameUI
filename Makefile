all: build test

build:
	mkdir build
	cd build && cmake ../

test:
	cd build && make gameuitest
	cp build/test/gameuitest .

.PHONY: test