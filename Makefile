run:
	g++ core.cpp db.cpp print.cpp actions.cpp eligibility_check.cpp && ./a.out

test:
	g++ tests.cpp db.cpp print.cpp actions.cpp eligibility_check.cpp && ./a.out
