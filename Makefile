

all:
	cd build && make && mv sim ..
clean:
	cd build && make c