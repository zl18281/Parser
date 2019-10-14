LIBS = -lm `pkg-config sdl2 --cflags` `pkg-config sdl2 --libs`
CFLAGS = -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi -g $(LIBS)
DEBUG = -g3
OPTIM = -O2
VALGRIND = --error-exitcode=1 --quiet --leak-check=full

all: parse interp extension

parse: parser_main.c parser_func.c test_parser.c parser.h
	$(CC) parser_main.c parser_func.c test_parser.c -o parse $(CFLAGS) $(OPTIM) -include parser.h

interp: interpreter_main.c interpreter_func.c neillsdl2.c test_interpreter.c interpreter.h
	$(CC) interpreter_main.c interpreter_func.c neillsdl2.c test_interpreter.c -o interp $(CFLAGS) $(OPTIM) -include interpreter.h

extension: extension_main.c extension_func.c neillsdl2.c test_extension.c extension.h
	$(CC) extension_main.c extension_func.c neillsdl2.c test_extension.c -o extension $(CFLAGS) $(OPTIM) -include extension.h

run: all
	./parse
	./interp
	./extension

clean:
	rm -f parse interp extension

.PHONY: clean run all
