# C language flags to compile the program
CFLAGS += -c -g -Wall -Wextra -Wpedantic \
          -Wformat=2 -Wno-unused-parameter \
          -Wshadow -Wwrite-strings -Wstrict-prototypes \
          -Wold-style-definition -Wredundant-decls \
          -Wnested-externs -Wmissing-include-dirs \
          -Wjump-misses-init -Wlogical-op -O2

# Valgrind flags to check memory leaks
VALGRIND += valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

# Path to source files
PATH_TO_SOURCE += ../src

# Source c language program files
FILES += $(PATH_TO_SOURCE)/operations_check.c \
		 $(PATH_TO_SOURCE)/infix_to_postfix.c \
		 $(PATH_TO_SOURCE)/evaluate_postfix.c \
		 $(PATH_TO_SOURCE)/convertor.c

# Object files to be generated
OFILES += operations_check.o \
		  infix_to_postfix.o \
		  evaluate_postfix.o \
		  convertor.o

# c-language-data-structures dynamically linked library
DYNAMIC_LIB += -ldstruc

# Input file to extract line commands
INFIX_EXPR_FILE += infix.txt
NUMBER_TYPE_FILE += numtype.txt

# Executable to be generated
EXEC += convertor

# Makefile rules
.PHONY: all build link run runv clean cleanall

# Build, Link and Clean the program
all: build link clean
	@printf "Successfully installed convertor\n"

# Build the program
build: $(FILES)
	@gcc $(CFLAGS) $(FILES)

# Link the program
link: $(OFILES)
	@gcc $(OFILES) $(DYNAMIC_LIB) -o $(EXEC)

# Run the program
run: $(INFIX_EXPR_FILE) $(NUMBER_TYPE_FILE)
	@./$(EXEC) "$(shell cat $(INFIX_EXPR_FILE))" "$(shell cat $(NUMBER_TYPE_FILE))"

# Run the program with valgrind
runv: $(INFIX_EXPR_FILE) $(NUMBER_TYPE_FILE)
	@$(VALGRIND) ./$(EXEC) "$(shell cat $(INFIX_EXPR_FILE))" "$(shell cat $(NUMBER_TYPE_FILE))"

clean: 
	@rm -f *.o

cleanall:
	@rm -f *.o $(EXEC)