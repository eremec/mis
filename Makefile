run:
	g++ core.cpp db.cpp print.cpp && ./a.out

test:
	g++ tests.cpp db.cpp print.cpp && ./a.out
