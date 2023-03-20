# Simpler makefile with implicit rules and wildcards.
# This will be appropriate for most CS 19-level projects, i.e.
# when all relevant files are the only C++ source-code files
# in the working directory.
# WARNING: Won't notice changes in header files.
app_name = cs19s23as06
CPP      = g++
CPPFLAGS = -lncurses

# First target is always the default if you just run "make".
# fun isn't directly referenced by the cpps, but it's used by other headers, which are references.
# thus whenever a header like fun is changed, we need to know to recompile everything that depended on it.
cs19s23as06 : appear.o awaken.o berries.o grandson.o lard.o scorch.o street.o sunset.o whole.o goodbye.o
	$(CPP) $^ -o $@ $(CPPFLAGS)

appear.o : appear.cpp kindly.h seven.h canyon.h
	$(CPP) -c appear.cpp

awaken.o : awaken.cpp cupboard.h jerk.h strange.h ivory.h say.h
	$(CPP) -c awaken.cpp

berries.o : berries.cpp strange.h ivory.h schoolmaster.h ivory.h say.h
	$(CPP) -c berries.cpp

grandson.o : grandson.cpp goody.h jerk.h
	$(CPP) -c grandson.cpp

lard.o : lard.cpp strange.h ivory.h kindly.h seven.h canyon.h say.h
	$(CPP) -c lard.cpp

scorch.o : scorch.cpp goodbye.h
	$(CPP) -c scorch.cpp

street.o : street.cpp say.h
	$(CPP) -c street.cpp

sunset.o : sunset.cpp strange.h ivory.h likely.h fun.h ivory.h say.h
	$(CPP) -c sunset.cpp

whole.o : whole.cpp anyone.h fun.h ivory.h kindly.h seven.h canyon.h say.h
	$(CPP) -c whole.cpp

goodbye.o: goodbye.cpp running.h
	$(CPP) -c goodbye.cpp

clean :
	rm -f ./*.o $(app_name)