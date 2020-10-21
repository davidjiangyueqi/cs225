EXENAME = main
OBJS = main.o order.o restaurant.o mcronald.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm


all: $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp order.h restaurant.h mcronald.h
#main.o: main.cpp mcronald.h restaurant.h order.h
	$(CXX) $(CXXFLAGS) main.cpp

order.o: order.cpp order.h
	$(CXX) $(CXXFLAGS) order.cpp

restaurant.o: restaurant.cpp restaurant.h
	$(CXX) $(CXXFLAGS) restaurant.cpp

mcronald.o: mcronald.cpp mcronald.h
	$(CXX) $(CXXFLAGS) mcronald.cpp

clean:
	-rm -f *.o $(EXENAME)
