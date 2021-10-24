GCC = clang++ -g -Wall -std=c++17

# target
glex:  glex.cc
	$(GCC) -o glex glex.cc

# test
test: test.cc glex_lib.h glex_gencode.h
	$(GCC) -o test test.cc
glex_gencode.h: glex
	./glex

.PHONY: clean
clean:
	rm -f *.o glex test glex_gencode.h