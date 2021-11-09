

pl0_lex: glex_gencode.h glex_gencode.cc pl0_lex.cc
	clang++ -std=c++17 -opl0_lex glex_gencode.cc pl0_lex.cc

glex_gencode.h glex_gencode.cc: pl0rule.txt
	../../build/tools/glex/glex pl0rule.txt