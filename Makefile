.PHONY: build

build:
	CC=clang CXX=clang++ cmake -B ./build -S . -G Ninja
	ninja -C ./build

run: build
	./build/check

clean:
	rm -rf ./build
