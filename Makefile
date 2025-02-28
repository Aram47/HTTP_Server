G++ = g++
FILES = main.cpp 														\
				./src/HTTPServer/HTTPServer.cpp 		\
				./src/Request/Request.cpp						\
				./src/Response/Response.cpp					\

EXE = server
DEL = rm

all:
	$(G++) $(FILES) -o $(EXE)

run:
	./$(EXE)

del:
	$(DEL) $(EXE)