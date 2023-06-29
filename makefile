QTHOME=/opt/qt5
QTINC=$(QTHOME)/include

CXX=g++
CXXFLAGS=-g -o0 -std=c++11 -pedantic -Wall -DQT_COMPILING_QSTRING_COMPAT_CPP -fpermissive
QTFLAGS=-fPIC -I$(QTINC) -I$(QTINC)/QtCore -I$(QTINC)/QtWidgets \
          -I$(QTINC)/QtGui -I$(QTINC)/QtSql
INCPATH=-I./

LK=g++
LKFLAGS=-g 
LIBPATH=-L./libs -L $(QTHOME)/lib
LIBS=-lQt5Gui -lQt5Core -lQt5Widgets -lQt5Sql -lpthread -ldl

MOC=/opt/qt5/bin/moc

PROG=lanGen

OBJS=dataentry.o datafile.o editglyphdlg.o generator.o consonantsdlg.o \
     voweldlg.o langen.o main.o
MOCS=moc_langen.o moc_voweldlg.o moc_consonantsdlg.o moc_editglyphdlg.o \
     moc_dataentry.o 

$(PROG) : $(OBJS) $(MOCS) makefile
	$(LK) $(LKFLAGS) $(LIBPATH) $(OBJS) $(MOCS) $(LIBS) -o $(PROG)

all : clean $(PROG)

dataentry.o : DataEntry.cpp DataEntry.h
	$(CXX) -c $(CXXFLAGS) $(QTFLAGS) DataEntry.cpp -o dataentry.o

moc_dataentry.o : DataEntry.h
	$(MOC) DataEntry.h -o moc_dataentry.cpp
	$(CXX) -c $(CXXFLAGS) $(QTFLAGS) moc_dataentry.cpp -o moc_dataentry.o

datafile.o : datafile.cpp datafile.h
	$(CXX) -c $(CXXFALGS) $(QTFLAGS) datafile.cpp -o datafile.o

editglyphdlg.o : editGlyphDlg.cpp editGlyphDlg.h
	$(CXX) -c $(CXXFLAGS) $(QTFLAGS) editGlyphDlg.cpp -o editglyphdlg.o

moc_editglyphdlg.o : editGlyphDlg.h
	$(MOC) editGlyphDlg.h -o moc_editglyphdlg.cpp
	$(CXX) -c $(CXXFLAGS) $(QTFLAGS) moc_editglyphdlg.cpp -o moc_editglyphdlg.o

generator.o : generator.cpp generator.h
	$(CXX) -c $(CXXFLAGS) $(QTFLAGS) generator.cpp -o generator.o

consonantsdlg.o : IPAConsonantsDlg.cpp IPAConsonantsDlg.h
	$(CXX) -c $(CXXFLAGS) $(QTFLAGS) IPAConsonantsDlg.cpp -o consonantsdlg.o

moc_consonantsdlg.o : IPAConsonantsDlg.h
	$(MOC) IPAConsonantsDlg.h -o moc_consonantsdlg.cpp
	$(CXX) -c $(CXXFLAGS) $(QTFLAGS) moc_consonantsdlg.cpp -o moc_consonantsdlg.o

voweldlg.o : IPAVowelDlg.cpp IPAVowelDlg.h
	$(CXX) -c $(CXXFLAGS) $(QTFLAGS) IPAVowelDlg.cpp -o voweldlg.o

moc_voweldlg.o : IPAVowelDlg.h
	$(MOC) IPAVowelDlg.h -o moc_voweldlg.cpp
	$(CXX) -c $(CXXFLAGS) $(QTFLAGS) moc_voweldlg.cpp -o moc_voweldlg.o

langen.o : langen.cpp langen.h
	$(CXX) -c $(CXXFLAGS) $(QTFLAGS) langen.cpp -o langen.o

moc_langen.o : langen.h
	$(MOC) langen.h -o moc_langen.cpp
	$(CXX) -c $(CXXFLAGS) $(QTFLAGS) moc_langen.cpp -o moc_langen.o

main.o : main.cpp
	$(CXX) -c $(CXXFLAGS) $(QTFLAGS) main.cpp -o main.o

clean :
	rm -f *.o
	rm -f *.*~
	rm -f moc_*
	rm -f $(PROG)


