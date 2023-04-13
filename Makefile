# Nom du binaire
NAME	=	damier

# Compileur
CC		= 	gcc

# Définition de la suppression de fichiers
RM		=	rm -f

# Dénition du dossier des sources pour aller les chercher au bon endroit
SRC_DIR	=	./src/

# Dénition du path pour le main.c
SRC_MAIN	=	./main.c

# Appel de toutes les sources .c
SRC	=	$(SRC_MAIN)						\
		$(SRC_DIR)display.c 			\
		$(SRC_DIR)game.c 				\
		$(SRC_DIR)player.c 				\
		$(SRC_DIR)pawn.c


# Transformation des .c en .o
OBJ		= 	$(SRC:%.c=%.o)

# Flages de compilation (souvent utilisé pour les includes "-InonDuDossierOùSontSituéLesIncludes")
# W est un flag de Warning permettant d'afficher à la compilation les erreurs du type :
# - variable non utilisée
# - variable non initialisée
CFLAGS	= 	-Iinclude -W -Wall -Wextra -Wshadow

# On appelle cette regle dans le terminal avec :
# $>make
# Elle permet de compiler les sources
all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

# On appelle cette regle dans le terminal avec :
# $>make clean
# Elle permet de supprimer les .o
clean:
		$(RM) $(OBJ)

# On appelle cette regle dans le terminal avec :
# $>make fclean
# Appelle la regle "clean" ET supprime le binaire (ici : fight)
fclean:		clean
		$(RM) $(NAME)
		$(RM) $(NAME_TEST)

# On appelle cette regle dans le terminal avec :
# $>make re
# Appelle les regles "clean" et "fclean" puis recompile
re: 	fclean all

# On appelle cette regle dans le terminal avec :
# $>make debug
# Elle permet d'ajouter le flag "-g" aux CFLAGS et appelle la regle "re"
# C'est une regle de debug
debug:	CFLAGS += -g
debug:	re

# Norme pour ne pas avoir à recompiler si cela n'est pas necéssaire
.PHONY: all clean fclean re