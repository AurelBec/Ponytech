CFLAGS=-g -W -Wall -I ../include/ -I/usr/include/SDL2 -I/usr/include/SDL -fno-stack-protector
LDFLAGS=-lSDLmain -lSDL_image -lSDL -lSDL_ttf #-lSDL_mixer

#Nom de l'executable
EXEC	=	pony

#Récupération des .c
SRC 	=	$(wildcard *.c)
#Liste de .o
OBJ		= 	$(SRC:.c=.o)
HDR		= 	$(SRC:.c=.h)
DEP 	=	$(SRC:.c=.d)


all: $(EXEC)

$(EXEC): $(OBJ)
	@gcc -o $@ $^ $(LDFLAGS)
	@echo "[Travail terminé, prêt à jouer !]"


-include $(OBJ:.o=.d)

%.o: %.c
	@gcc -o $@ -c $< $(CFLAGS)
	@gcc -MM $(CFLAGS) $*.c > $*.d
	@echo "    - Assemblage $@   \t100%"


clean:
	@rm -rf *.o *.d *~ *#

fclean: clean
	@rm -rf $(EXEC)

re: fclean all
