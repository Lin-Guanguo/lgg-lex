GCC = clang++ -g -Wall

# target
glex:  main.cc
	$(GCC) -o glex main.cc


test: test.cc
	$(GCC) -o test test.cc

.PHONY: clean
clean:
	rm -f *.o glex test