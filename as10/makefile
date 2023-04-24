app_name = recurrence
CPP      = g++
CPPFLAGS = -lgmp -lgmpxx

all: $(app_name) tester

# since we only have a header file and no .cpp file, we can't make an object file for linking.
$(app_name) : recurrence_tests.cpp cs19_recurrence.h
	$(CPP) $^ -o $@ $(CPPFLAGS)

tester : recurrence_tests2.cpp cs19_recurrence.h
	$(CPP) $^ -o $@ $(CPPFLAGS)

clean:
	rm -f ./*.o $(app_name) tester