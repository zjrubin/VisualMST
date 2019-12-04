# The name of the main executable
EXECUTABLE = mst

# The name of the main project file
PROJECTFILE = main.cpp

# Libraries that the main executable needs to link with
EXECLIBS =

# Compiler flags for the executable
EXECFLAGS =

# designate which compiler to use
CXX = g++

# Default Flags (would prefer -std=c++17 but Mac/Xcode/Clang doesn't support)
CXXFLAGS = -O3 -std=c++17 -pedantic-errors -Wall

# list of test drivers (with main()) for development
TESTSOURCES = $(wildcard test*.cpp)

# names of test executables
TESTS = $(TESTSOURCES:%.cpp=%)

# list of sources used in project
SOURCES = $(wildcard *.cpp)
SOURCES := $(filter-out $(TESTSOURCES), $(SOURCES))

# list of objects used in project
OBJECTS = $(SOURCES:%.cpp=%.o)

# Highest target; sews together all objects into executable
all: $(EXECUTABLE)

# Build rules for the executable
$(EXECUTABLE): $(OBJECTS) $(EXEC_LIBS)
ifeq ($(EXECUTABLE), executable)
	@echo Edit EXECUTABLE variable in Makefile.
	@echo Using default a.out.
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(EXECLIBS) $(EXECFLAGS)
else
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(EXECLIBS) $(EXECFLAGS) -o $(EXECUTABLE)
endif

# Automatically generate all the tests cases
alltests: $(TESTS)

# Build rules for test*.cpp files
define make_tests
    ifeq ($$(PROJECTFILE),)
	    @echo Edit PROJECTFILE variable to .cpp file with main\(\)
	    @exit 1
    endif
    SRCS = $$(filter-out $$(PROJECTFILE), $$(SOURCES)) #comparisons.cpp
    OBJS = $$(SRCS:%.cpp=%.o)
    HDRS = $$(wildcard *.h *.hpp)
    LIBS =
    # FLAGS = ???
    $(1): $$(OBJS) $$(HDRS) $$(LIBS) $(1).cpp
	$$(CXX) $$(CXXFLAGS) $$(OBJS) $$(LIBS) $(1).cpp -o $(1)
    # $$(CXX) $$(CXXFLAGS) $$(OBJS) $$(LIBS) $$(FLAGS) $(1).cpp -o $(1)
endef
$(foreach test, $(TESTS), $(eval $(call make_tests, $(test))))

# Generic rules for compiling a source file to an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Rules to recompile .cpp files when included .h files are modified
depend: .depend
.depend: $(SOURCES)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^ -MF  ./.depend;
include .depend

# make clean - remove .o files, executables, tarball
clean:
	@rm -vf a.out $(OBJECTS) *.o $(EXECUTABLE) $(DEBUG) $(TESTS)
	@rm -Rf *.dSYM

help:
	@echo "$$MAKEFILE_HELP"

define MAKEFILE_HELP
Advanced Makefile Help
* This Makefile uses advanced techniques, for more information:
    $$ man make

* General usage
    1. Follow directions at each "TODO" in this file.
       a. Set EXECUTABLE equal to the name given in the project specification.
       b. Set PROJECTFILE equal to the name of the source file with main()
       c. Add any dependency rules specific to your files.
    2. Build, test, submit... repeat as necessary.

* Unit testing support
    A) Source files for unit testing should be named test*.cpp.  Examples
       include test_input.cpp or test3.cpp.
    B) Automatic build rules are generated to support the following:
           $$ make test_input
           $$ make test3
           $$ make alltests        (this builds all test drivers)
    C) If test drivers need special dependencies, they must be added manually.
endef
export MAKEFILE_HELP

# these targets do not create any files
.PHONY: all clean alltests help

# disable built-in rules
.SUFFIXES:
