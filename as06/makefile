# Simpler makefile with implicit rules and wildcards.
# This will be appropriate for most CS 19-level projects, i.e.
# when all relevant files are the only C++ source-code files
# in the working directory.
# WARNING: Won't notice changes in header files.
app_name = cs19s23as06
CPP      = g++
CPPFLAGS = -lncurses

# we never need to compile header files, so don't bother making objects for them, dumbass.

# First target is always the default if you just run "make".
cs19s23as06 : appear.o awaken.o berries.o grandson.o lard.o scorch.o street.o sunset.o whole.o goodbye.o
	$(CPP) $^ -o $@ $(CPPFLAGS)
# in this case, flags should go after as lncurses happens only in the linking stage
# this is why the others don't have these args, they don't need them.

appear.o : appear.cpp kindly.h seven.h canyon.h
	$(CPP) -c appear.cpp

awaken.o : awaken.cpp cupboard.h jerk.h strange.h say.h
	$(CPP) -c awaken.cpp

berries.o : berries.cpp strange.h schoolmaster.h say.h
	$(CPP) -c berries.cpp

grandson.o : grandson.cpp goody.h jerk.h
	$(CPP) -c grandson.cpp

lard.o : lard.cpp strange.h kindly.h say.h
	$(CPP) -c lard.cpp

scorch.o : scorch.cpp goodbye.h
	$(CPP) -c scorch.cpp

street.o : street.cpp say.h
	$(CPP) -c street.cpp

sunset.o : sunset.cpp strange.h likely.h say.h
	$(CPP) -c sunset.cpp

whole.o : whole.cpp anyone.h kindly.h say.h
	$(CPP) -c whole.cpp

goodbye.o: goodbye.cpp
	$(CPP) -c goodbye.cpp

clean :
	rm -f $(app_name) $(objects)