IDIR = include
CXX=g++
CXXFLAGS=-I$(IDIR) --std=c++11

TSTDIR=test
BINDIR=bin

LIBS=-lpthread

_DEPS = bench11.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_TST = test_bench test_nobench
TST = $(patsubst %,$(BINDIR)/%,$(_TST))

$(BINDIR)/%: $(TSTDIR)/%.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

tests: $(TST)

.PHONY: clean

clean:
	rm -f $(BINDIR)/* *~ core $(INCDIR)/*~ 
