
CC = gcc -c
LD = gcc
CPPOPTS = -Wall

PROGRAM := membership

OBJS := utils.o sysgroup.o grouplist.o report.o membership.o

all: clean $(PROGRAM)

$(OBJS): %.o : %.c
	$(CC) $(CPPOPTS) $< -o $@

$(PROGRAM): $(OBJS)
	$(LD) $(LDOPTS) $(OBJS) -o $(PROGRAM)

clean:
	- /bin/rm -f $(OBJS)
	- /bin/rm -f $(PROGRAM)
