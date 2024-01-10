# Makefile
#
TARGET_J  = poisson_j		# Jacobi
TARGET_GS = poisson_gs		# Gauss-Seidel
TARGET_JOMP = poisson_jomp	# Jacobi with OpenMP

SOURCES	= main.c print.c alloc3d.c util.c
OBJECTS	= print.o alloc3d.o util.o
MAIN_J	= main_j.o
MAIN_GS = main_gs.o
MAIN_JOMP = main_jomp.o
OBJS_J	= $(MAIN_J) jacobi.o
OBJS_GS	= $(MAIN_GS) gauss_seidel.o
OBJS_JOMP = $(MAIN_JOMP) jacobi_omp.o

# options and settings for the GCC compilers
#
CC	= gcc
DEFS	= 
OPT	= -g -fopenmp
IPO	= 
ISA	= 
CHIP	= 
ARCH	= 
PARA	= 
CFLAGS	= $(DEFS) $(ARCH) $(OPT) $(ISA) $(CHIP) $(IPO) $(PARA) $(XOPTS)
LDFLAGS = -lm 

all: $(TARGET_J) $(TARGET_GS) $(TARGET_JOMP)

$(TARGET_J): $(OBJECTS) $(OBJS_J)
	$(CC) -o $@ $(CFLAGS) $(OBJS_J) $(OBJECTS) $(LDFLAGS)

$(TARGET_GS): $(OBJECTS) $(OBJS_GS)
	$(CC) -o $@ $(CFLAGS) $(OBJS_GS) $(OBJECTS) $(LDFLAGS)

$(TARGET_JOMP): $(OBJECTS) $(OBJS_JOMP)
	$(CC) -o $@ $(CFLAGS) $(OBJS_JOMP) $(OBJECTS) $(LDFLAGS)

$(MAIN_J):
	$(CC) -o $@ -D_JACOBI $(CFLAGS) -c main.c 

$(MAIN_GS):
	$(CC) -o $@ -D_GAUSS_SEIDEL $(CFLAGS) -c main.c 

$(MAIN_JOMP):
	$(CC) -o $@ -D_JACOBI_OMP $(CFLAGS) -c main.c

clean:
	@/bin/rm -f core *.o *~

realclean: clean
	@/bin/rm -f $(TARGET_J)  $(TARGET_GS)

# DO NOT DELETE

main_j.o: main.c print.h jacobi.h 
main_gs.o: main.c print.h gauss_seidel.h
main_jomp.o: main.c print.h jacobi_omp.h
print.o: print.h
