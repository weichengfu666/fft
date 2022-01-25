LTYPE=A18
TARGET=realfft.a
CFLAGS=-O
PREFLAGS=
IDIRS=-I../
LLIBS=

LINT=lint -uhbaxc
CTAGS=ctags
PRINT=@pr -t

CFILES=\
	realfft.c
HFILES=\
	../complex.h
OBJECTS=\
	realfft.o

.SUFFIXES: .i

$(TARGET):	$(OBJECTS)
	ar rv $@ $?
	ranlib $@

lint:
	$(LINT) $(PREFLAGS) $(IDIRS) $(CFILES) $(LLIBS) -lc

tags:	$(HFILES) $(CFILES)
	$(CTAGS) $(HFILES) $(CFILES)

print:	realfft.man
	$(PRINT) realfft.man $(CFILES)

realfft.man:	realfft.3
	@nroff -man realfft.3 > realfft.man

.c.o:
	$(CC) $(CFLAGS) -c $(IDIRS) $<

.c.i:
	$(CC) $(CFLAGS) -P $(IDIRS) $<

.c.s:
	$(CC) $(CFLAGS) -S $(IDIRS) $<

realfft.o:\
	../complex.h
