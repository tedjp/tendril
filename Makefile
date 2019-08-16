SUBDIRS = src

all:
	for d in $(SUBDIRS); do \
		$(MAKE) -C $$d; \
	done
