########################################################################################################################
#                                                       VARIABLE                                                       #
########################################################################################################################

SRCS		:=	main.c			\
				params_parser.c	\
				time.c			\
				init.c			\
				routine.c		\
				monitoring.c	\
				mtx_func.c

SRCS_D		:=	srcs/

OBJS_D		:=	objs/

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

HEAD		:=	includes/philosophers.h

HEAD_D		:=	.

CFLAGS		:=	-Wall -Wextra -Werror -pthread -o3

NAME		:=	philosophers

########################################################################################################################
#                                                        RULES                                                         #
########################################################################################################################

all			:
				$(MAKE) $(NAME)

$(NAME)		:	$(OBJS_D) $(OBJS) $(HEAD)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD)
				$(CC) $(CFLAGS) -I/usr/include -c $< -o $@

$(OBJS_D)	:
				@mkdir -p $(OBJS_D)

########################################################################################################################
#                                                        COMMANDS                                                      #
########################################################################################################################

clean		:
				$(RM) -r $(OBJS) $(OBJS_D)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all

.PHONY: all clean fclean re lib
