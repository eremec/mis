run:
	g++ core.cpp db.cpp && ./a.out

test:
	g++ tests.cpp db.cpp && ./a.out
