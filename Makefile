export PATH := /usr/local/share/Qt-5.5.1/5.5/gcc_64/bin:$(PATH)
export LD_LIBRARY_PATH := /usr/local/share/Qt-5.5.1/5.5/gcc_64/lib:$(LD_LIBRARY_PATH)

all: hra2016 hra2016-cli

clean:
	rm -rf ./doc ./build ./src/Makefile xjanov10-xhladi21.zip

doxygen:
	doxygen config.doxygen

hra2016:
	cd src && qmake hra2016.pro && make && cd ..
	echo -e "[Paths]\nPrefix=/usr/local/share/Qt-5.5.1/5.5/gcc_64" > ./build/qt.conf

hra2016-cli:
	cd src && qmake hra2016-cli.pro && make && cd ..

pack:
	zip -r xjanov10-xhladi21.zip ./

run:
	./build/hra2016 &> /dev/null &
	./build/hra2016-cli
