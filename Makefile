dirs := sorting

MAKE = mingw32-make


.PHONY: all clean

all:
	for dir in $(dirs); do \
		$(MAKE) -C $$dir; \
	done

clean:
	for dir in $(dirs); do \
		$(MAKE) -C $$dir clean; \
	done