mixed:imcpp.o c.o
	gcc -lstdc++ imcpp.o c.o -o mixed

imcpp.o: imcpp.h imcpp.cpp
	g++ -c -std=c++0x imcpp.cpp

c.o: imcpp.h c.c
	gcc -c c.c

.PHONY : clean
clean:
	-rm *.o mixed
