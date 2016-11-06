### ==========================================================================
### General Makefile with misc. options. (c) 2009 Heinz van Saanen
### Enter "make help" to show the different options
### ==========================================================================


### Executable name. Change as wanted
EXE = atmsp


### ==========================================================================
### Compiler speed switches for both GCC and ICC. These settings are generally
### fast on a broad range of systems, but may be changed experimentally
### ==========================================================================
GCCFLAGS = -O3
ICCFLAGS = -O3


### General compiler settings. "Fix" ICC-iomanip-incompatibilty for ICC 12.x
GCCFLAGS += -Wall -Wextra -pedantic -ansi
ICCFLAGS += -Wall


### General linker settings. Add flags as needed
LDFLAGS  =


### Object files
OBJS = main.o


### General rules
default:
	$(MAKE) gcc

help:
	@echo ""
	@echo "Makefile options:"
	@echo ""
	@echo "make                >  Compiler = g++"
	@echo "make complex        >  Compiler = g++ complex version"
	@echo "make mpfr           >  Compiler = g++ MPFR version"
	@echo "make icc            >  Compiler = icpc"
	@echo "make icc-profile    >  Compiler = icpc + automatic pgo-build"
	@echo "make osx-ppc32      >  PPC-Mac OS X 32 bit. Compiler = g++"
	@echo "make osx-ppc64      >  PPC-Mac OS X 64 bit. Compiler = g++"
	@echo "make osx-x86        >  x86-Mac OS X 32 bit. Compiler = g++"
	@echo "make osx-x86_64     >  x86-Mac OS X 64 bit. Compiler = g++"
	@echo "make strip          >  Strip executable"
	@echo "make clean          >  Clean up"
	@echo ""

all: $(EXE) .depend

strip:
	strip $(EXE)

clean:
	$(RM) *.o *~ .depend $(EXE) *~

### Possible targets. You may add your own ones here
gcc:
	$(MAKE) \
	CXX='g++' \
	CXXFLAGS="$(GCCFLAGS)" \
	all

complex:
	$(MAKE) \
	CXX='g++' \
	CXXFLAGS="$(GCCFLAGS)" \
	CXXFLAGS+='-DCOMPLEX' \
	all

mpfr:
	$(MAKE) \
	CXX='g++' \
	CXXFLAGS="$(GCCFLAGS)" \
	CXXFLAGS+='-DMPFR' \
	LDFLAGS+='-lmpfr' \
	all

icc:
	$(MAKE) \
	CXX='icpc' \
	CXXFLAGS="$(ICCFLAGS)" \
	all

icc-profile-make:
	$(MAKE) \
	CXX='icpc' \
	CXXFLAGS="$(ICCFLAGS)" \
	CXXFLAGS+='-prof-gen=srcpos -prof_dir ./profdir' \
	all

icc-profile-use:
	$(MAKE) \
	CXX='icpc' \
	CXXFLAGS="$(ICCFLAGS)" \
	CXXFLAGS+='-prof_use -prof_dir ./profdir' \
	all

icc-profile:
	@rm -rf profdir
	@mkdir profdir
	@touch *.cpp *.h
	$(MAKE) icc-profile-make
	@echo ""
	@echo "Running pgo-build ..."
	@./$(EXE) "1+x+sqrt(y)^z+sin(2*x)" 10000000
	@echo "Optimisation run finished. Build final executable now ..."
	@echo ""
	@touch *.cpp *.h
	$(MAKE) icc-profile-use
	@rm -rf profdir

osx-ppc32:
	$(MAKE) \
	CXX='g++' \
	CXXFLAGS="$(GCCFLAGS)" \
	CXXFLAGS+='-arch ppc' \
	LDFLAGS+='-arch ppc' \
	all

osx-ppc64:
	$(MAKE) \
	CXX='g++' \
	CXXFLAGS="$(GCCFLAGS)" \
	CXXFLAGS+='-arch ppc64' \
	LDFLAGS+='-arch ppc64' \
	all

osx-x86:
	$(MAKE) \
	CXX='g++' \
	CXXFLAGS="$(GCCFLAGS)" \
	CXXFLAGS+='-arch i386' \
	LDFLAGS+='-arch i386' \
	all

osx-x86_64:
	$(MAKE) \
	CXX='g++' \
	CXXFLAGS="$(GCCFLAGS)" \
	CXXFLAGS+='-arch x86_64' \
	LDFLAGS+='-arch x86_64' \
	all


### Compilation. Do not change
$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS)


### Dependencies. Do not change
.depend:
	$(CXX) -MM $(OBJS:.o=.cpp) > $@

include .depend
