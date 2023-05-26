app_name = dna_tests
CPP      = g++
CPPFLAGS = -std=c++20

all: $(app_name) autocomplete

$(app_name) : cs19_compact_string_set_autocomplete_test.cpp autocomplete
	$(CPP) $^ -o $@ $(CPPFLAGS)

autocomplete: cs19_compact_string_set.h cs19_compact_string_set.cpp
	$(CPP) $^ -o $@ $(CPPFLAGS)

clean:
	rm -f ./*.o $(app_name)