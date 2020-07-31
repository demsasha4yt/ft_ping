RM = rm

# LIBS
D_LIBS = ./libs
D_LIBFT = ${D_LIBS}/libft
L_LIBFT = -L ${D_LIBFT} -lft
I_LIBFT = -I $(D_LIBFT)/includes


# INCLUDES
I_DIR = ./includes
I_I = -I $(I_DIR) 
HEADER	=	includes/ft_ping.h

#COMPILER OPTIONS
CC = gcc
LFLAGS = $(L_LIBFT) -lncurses
IFLAGS = $(I_I) $(I_LIBFT)
DFLAGS = -g
EFLAGS = -Wall -Wextra -Werror
CFLAGS = $(DFLAGS) $(IFLAGS) $(EFLAGS)
CCFLAGS = $(DFLAGS) $(IFLAGS) $(LFLAGS) $(EFLAGS)

# PING EXECUTABLE
PING_EXEC = ft_ping
PING_SRCS = $(wildcard ./src/*.c ./src/**/*.c /src/**/**/*.c)
PING_OBJS = $(patsubst %.c,%.o,$(PING_SRCS))

# ASM EXECUTABLE

all: $(PING_EXEC)

$(PING_EXEC): libft $(PING_OBJS)
	@$(CC) $(CCFLAGS) -o $(PING_EXEC) $(PING_OBJS)
	@echo ...........The $(PING_EXEC) program builded!............

%.o: %.c
	@$(CC) $(CFLAGS) $< -c -o $@
	@echo [OBJS]:    [$@ Builded...]

clean: libftclean
	@$(RM) -f $(PING_OBJS)
	@$(RM) -f $(ASM_OBJS)
	@echo [RM]: All .o cleaned!

fclean: clean
	@$(RM) -f $(PING_EXEC)
	@$(RM) -f $(ASM_EXEC)
	@echo [RM]: All executables cleaned!

re: fclean libftfclean all

libft:
	@echo [LIBFT]: Libft Make
	@make -C $(D_LIBFT)

libftclean:
	@echo [LIBFT]: Libft clean
	@make -C $(D_LIBFT) clean

libftfclean:
	@echo [LIBFT]: Libft fclean
	@make -C $(D_LIBFT) fclean
