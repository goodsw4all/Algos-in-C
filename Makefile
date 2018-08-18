TARGETS = sort recursion search linkedList tree

all : $(TARGETS)
	@for dir in $(TARGETS); do \
		make -C $$dir; \
	done

clean :
	@for dir in $(TARGETS); do \
		make -C $$dir clean; \
	done
