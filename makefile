proj2.x: test_vector.o
        g++47 -std=c++11 -o proj2.x test_vector.o
test_vector.o: test_vector.cpp
        g++47 -std=c++11 -c test_vector.cpp
clean:
        rm *.o proj2.x
