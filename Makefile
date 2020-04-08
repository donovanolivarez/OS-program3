P1_OBJS = part1.o
P2_OBJS = part2.o pagetable.o phypages.o
INCLUDES = assign3.h

%.o : %.c ${INCLUDES}
	gcc -g -c $<

part1 : ${P1_OBJS}
	gcc -g -o part1 ${P1_OBJS}

part2 : ${P2_OBJS}
	gcc -g -o part2 ${P2_OBJS}

.PHONY : clean
clean :
	rm -f ${P1_OBJS} ${P2_OBJS}