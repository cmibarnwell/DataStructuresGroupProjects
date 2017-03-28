# Define the machine object files for your program
OBJECTS = cs2123p5Driver.o CMBp5.o BKBp5.o BJLp5.o
# Define your include file
INCLUDES = cs2123p5.h

# make for the executable
p5: ${OBJECTS}
	gcc -g -o p5 ${OBJECTS}

# Simple suffix rules for the .o
%.o: %.c ${INCLUDES}
	gcc -g -c $<

# Clean the .o files
clean:
	rm -f ${OBJECTS}
