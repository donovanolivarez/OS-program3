P1_OBJS = part1.o
P2_OBJS = part2.o pagetable.o phypages.o
P3_OBJS = part3.o pagetable.o phypages.o
INCLUDES = assign3.h

%.o : %.c ${INCLUDES}
	gcc -g -c $<

all: part1 part2 part3

part1 : ${P1_OBJS}
	gcc -g -o part1 ${P1_OBJS}

part2 : ${P2_OBJS}
	gcc -g -o part2 ${P2_OBJS} -lm

part3 : ${P3_OBJS}
	gcc -g -o part3 ${P3_OBJS} -lm

.PHONY : clean
clean :
	rm -f ${P1_OBJS} ${P2_OBJS} ${P3_OBJS}