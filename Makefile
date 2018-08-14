TARGETS = sort recursion search

all : $(TARGETS)

clean :
	@for dir in $(TARGETS); do \
		make -C $$dir clean; \
	done
