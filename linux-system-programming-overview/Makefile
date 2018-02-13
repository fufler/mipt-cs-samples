SUBDIRS := $(wildcard *-*)

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done


.PHONY: all $(SUBDIRS) clean
