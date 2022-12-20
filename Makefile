.PHONY: level-zero

ze-count-engines: lib/libze_loader.so level-zero main.cpp
	LIBRARY_PATH=lib g++ main.cpp -g -lze_loader -I./level-zero/include -Wl,-rpath=lib -o ze-count-engines

level-zero:
	git submodule init
	git submodule update

lib/libze_loader.so: level-zero
	mkdir -p lib && mkdir -p level-zero/build && cd level-zero/build && cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build . --target ze_loader && cd - && cp level-zero/build/lib/libze_loader.so* lib

clean:
	rm -rf level-zero/build
	rm -f ze-count-engines
	rm -rf lib
