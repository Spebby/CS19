app_name = dna_tests
CPP      = g++
CPPFLAGS = -std=c++20

all: $(app_name) dna_tests

$(app_name) : dna_tests.cpp cs19_polynucleotide.h cs19_dna.h
	$(CPP) $^ -o $@ $(CPPFLAGS)

clean:
	rm -f ./*.o $(app_name)