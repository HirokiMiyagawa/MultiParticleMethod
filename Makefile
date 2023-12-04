#
#---------------------------------------
#  Last update      : 2020/12/11
#  Author           : Teruhisa Okura
#  Email            : okura.teruhisa397@mail.kyutech.jp
#  Language         : Makefile
#  Original library : 
#  <summary>
#      This Makefile is "Multi-Particle Method" simulation compile program.
#  </summary>
#---------------------------------------
#
#



TARGET1		= main
# TARGET2		= SimpleTensile
# TARGET3		= SimpleShare
# TARGET4		= SimpleBend
# TARGET5		= SimplePressure
# TARGET6		= CylinderPressure
# TARGET7		= CubePressure
# TARGET8		= DiagonalTensile
# TESTTARGET1	= test


CXXDIR		= ./src/cpp
HXXDIR		= ./src/hpp
BINDIR		= ./bin
TESTDIR		= ./test
PDFDIR		= ./data/pdf
INCLUDES	= -I$(HXXDIR)/Base -I$(HXXDIR)/Global -I$(HXXDIR)/MultiParticle -I$(HXXDIR)/DefinitionOfSituation -I$(HXXDIR)/Readcsv -I$(HXXDIR)/MyLibrary

CC			= g++
#CC			= pgc++
# CFLAGS		= -acc -O2 -Minfo=accel -gpu=cc75,managed
# CFLAGS		= -Wall -Wextra -Ofast -flto -lm -std=c++17 -fopenacc
CFLAGS		= -Wall -Wextra -Ofast -flto -lm -fopenmp -std=c++17
# CFLAGS		= -Wall -Wextra -Ofast -flto -lm -std=c++17
# CFLAGS		= -Wall -Wextra -lm -std=c++17 -g -O0
TESTFLAGS	= -Wall -Wextra -lm -fopenmp -std=c++17 -g -O0 -DEBUG
#  -march=native:gcc -mtune=native -munune+native
# for DEBUG
# CFLAGS		= -Wall -Wextra -O0 -lm -std=c++17 -g

#-fopenmp -std=c++1z
CXXFLAGS	= $(CFLAGS)
# CXXFLAGS	= -std=c++11 $(CFLAGS)
#FLAGS		= -std=c++11 -fopenmp

ALLHXXBASE	= CalcDataAllocation.hpp DataSet.hpp Params.hpp
ALLPSBASE	= $(ALLHXXBASE:%.hpp=$(HXXDIR)/Base/%.ps)

ALLHXXMULT	= BaseCalc.hpp  Console.hpp  ForceCalc.hpp  GetNewCoordinate.hpp  InitialConditions.hpp  MultiParticle.hpp  ThicknessCalc.hpp  VirtualParticleCalc.hpp MatrixCalc.hpp
ALLPSMULT	= $(ALLHXXMULT:%.hpp=$(HXXDIR)/MultiParticle/%.ps)

ALLHXXGLOB	= Color.hpp  Library_header.hpp Basic.hpp
ALLPSGLOB	= $(ALLHXXGLOB:%.hpp=$(HXXDIR)/Global/%.ps)

ALLCXX		= main.cpp
ALLPS		= $(ALLCXX:%.cpp=$(CXXDIR)/%.ps)


ALLPDF		= $(ALLHXXBASE:%.hpp=$(PDFDIR)/%.pdf) $(ALLHXXMULT:%.hpp=$(PDFDIR)/%.pdf) $(ALLHXXGLOB:%.hpp=$(PDFDIR)/%.pdf) $(ALLCXX:%.cpp=$(PDFDIR)/%.pdf)

.SUFFIXES:.hpp .cpp .ps .pdf 


.PHONY:all
# 本来はこれ
# all:TOUCH $(TARGET1:%=$(BINDIR)/%) $(TARGET2:%=$(BINDIR)/%) $(TARGET3:%=$(BINDIR)/%) $(TARGET4:%=$(BINDIR)/%) $(TARGET5:%=$(BINDIR)/%) $(TARGET6:%=$(BINDIR)/%) $(TARGET7:%=$(BINDIR)/%) $(TARGET8:%=$(BINDIR)/%)
# $(TARGET9:%=$(BINDIR)/%)

# コンパイル時間短縮 Tensile, Share, Bend, Diagonal
# all:TOUCH $(TARGET2:%=$(BINDIR)/%) $(TARGET3:%=$(BINDIR)/%) $(TARGET4:%=$(BINDIR)/%) $(TARGET8:%=$(BINDIR)/%) $(INPUTFILE)
all:TOUCH $(TARGET1:%=$(BINDIR)/%) $(TESTTARGET1:%=$(TESTDIR)/%)

# $(info div: $(DIVIDESCRIPT))
# $(info CSV: $(INPUTFILE))
# $(info div: $(TARGET2))



$(BINDIR)/$(TARGET1:%=%.o):$(CXXDIR)/$(TARGET1).cpp
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET1:%=$(BINDIR)/%):$(BINDIR)/$(TARGET1:%=%.o)
	$(CC) $(CXXFLAGS) $+ -o $@

$(TESTDIR)/$(TESTTARGET1:%=%.o):$(TESTDIR)/$(TESTTARGET1).cpp
	$(CC) $(TESTFLAGS) $(INCLUDES) -c $< -o $@

$(TESTTARGET1:%=$(TESTDIR)/%):$(TESTDIR)/$(TESTTARGET1:%=%.o)
	$(CC) $(TESTFLAGS) $+ -o $@

# $(BINDIR)/$(TARGET2:%=%.o):$(CXXDIR)/$(TARGET2).cpp
#	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# $(TARGET2:%=$(BINDIR)/%):$(BINDIR)/$(TARGET2:%=%.o)
# 	$(CC) $(CXXFLAGS) $+ -o $@

# $(BINDIR)/$(TARGET3:%=%.o):$(CXXDIR)/$(TARGET3).cpp
# 	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# $(TARGET3:%=$(BINDIR)/%):$(BINDIR)/$(TARGET3:%=%.o)
# 	$(CC) $(CXXFLAGS) $+ -o $@

# $(BINDIR)/$(TARGET4:%=%.o):$(CXXDIR)/$(TARGET4).cpp
# 	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# $(TARGET4:%=$(BINDIR)/%):$(BINDIR)/$(TARGET4:%=%.o)
# 	$(CC) $(CXXFLAGS) $+ -o $@

# $(BINDIR)/$(TARGET5:%=%.o):$(CXXDIR)/$(TARGET5).cpp
# 	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# $(TARGET5:%=$(BINDIR)/%):$(BINDIR)/$(TARGET5:%=%.o)
# 	$(CC) $(CXXFLAGS) $+ -o $@

# $(BINDIR)/$(TARGET6:%=%.o):$(CXXDIR)/$(TARGET6).cpp
# 	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# $(TARGET6:%=$(BINDIR)/%):$(BINDIR)/$(TARGET4:%=%.o)
# 	$(CC) $(CXXFLAGS) $+ -o $@

# $(BINDIR)/$(TARGET7:%=%.o):$(CXXDIR)/$(TARGET7).cpp
# 	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# $(TARGET7:%=$(BINDIR)/%):$(BINDIR)/$(TARGET7:%=%.o)
# 	$(CC) $(CXXFLAGS) $+ -o $@

# $(BINDIR)/$(TARGET8:%=%.o):$(CXXDIR)/$(TARGET8).cpp
# 	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
# $(TARGET8:%=$(BINDIR)/%):$(BINDIR)/$(TARGET8:%=%.o)
# 	$(CC) $(CXXFLAGS) $+ -o $@




TOUCH:
	touch $(CXXDIR)/*





.PHONY:clean
clean:
	-@rm $(ALLPSBASE) $(ALLPSMULT) $(ALLPSGLOB) $(ALLPS) > /dev/null 2>&1; rm $(PDFDIR)/* > /dev/null 2>&1; rm $(BINDIR)/* > /dev/null; ./src/scripts/copy2results.sh; ./src/scripts/delete_csvfile.sh; 2>&1



.PHONY:pdf
pdf:MOVE $(ALLPDF)

.PHONY:ps
ps:$(ALLPSBASE) $(ALLPSMULT) $(ALLPSGLOB) $(ALLPS)


.ps.pdf:
	ps2pdf $< $@; rm $< > /dev/null 2>&1


.hpp.ps:
	enscript --pretty-print=cpp --color --line-numbers -H1 --no-header --tabsize=4 --font="Courier8" --columns=1 $< -o $@

.cpp.ps:
	enscript --pretty-print=cpp --color --line-numbers -H1 --no-header --tabsize=4 --font="Courier8" --columns=1 $< -o $@

MOVE:
	-@mv $(HXXDIR)/Base/*.ps $(PDFDIR)/
	-@mv $(HXXDIR)/MultiParticle/*.ps $(PDFDIR)/
	-@mv $(HXXDIR)/Global/*.ps $(PDFDIR)/
	-@mv $(CXXDIR)/*.ps $(PDFDIR)/
