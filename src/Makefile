GCC = g++ -g -Wall -std=c++17

# target
glex:  glex.cc
	$(GCC) -o glex glex.cc

# test
test: test.cc glex_gencode.h
	$(GCC) -o test test.cc glex_gencode.cc
glex_gencode.h: glex rule
	./glex rule

.PHONY: clean
clean:
	rm -f *.o glex test glex_gencode.h