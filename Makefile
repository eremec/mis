run:
	g++ core.cpp db.cpp print.cpp actions.cpp && ./a.out

test:
	g++ tests.cpp db.cpp print.cpp actions.cpp && ./a.out
