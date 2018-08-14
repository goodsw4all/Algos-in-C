TARGETS = sort recursion search

all : $(TARGETS)
	@for dir in $(TARGETS); do \
		make -C $$dir; \
	done

clean :
	@for dir in $(TARGETS); do \
		make -C $$dir clean; \
	done
