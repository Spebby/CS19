app_name = cs19_HSV
CPP      = g++
CPPFLAGS = -std=c++20 -Ofast

$(app_name) : generator.o source.o
	$(CPP) $(CPPFLAGS) $^ -o $@

generator.o : HSVTest.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

source.o : cs19_hsv_color.cpp cs19_hsv_color.h
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean :
	rm -f ./*.o $(app_name)