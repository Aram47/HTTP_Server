G++ = g++
FILES = main.cpp 														\
				./src/HTTPServer/HTTPServer.cpp 		\
				./src/Request/Request.cpp						\
				./src/Response/Response.cpp					\

FLAGS = -Wall -Wextra -Werror
STANDART = -std=c++98
EXE = server
DEL = rm

all:
# commented :)))
# $(G++) $(FLAGS) $(STANDART) $(FILES) -o $(EXE)
	$(G++) $(FILES) -o $(EXE)

run:
	./$(EXE)

del:
	$(DEL) $(EXE)