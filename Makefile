CC      = cc
CFLAGS  = -Wall -Werror -Wextra -g
RM      = rm -rf
NAME    = minishell
NAME2   = sigint_sender

READLINE_CFLAGS := $(shell pkg-config --cflags readline 2>/dev/null)
READLINE_LDFLAGS := $(shell pkg-config --libs readline 2>/dev/null)

ifeq ($(READLINE_CFLAGS),)
	READLINE_CFLAGS := -I/opt/homebrew/opt/readline/include
endif

ifeq ($(READLINE_LDFLAGS),)
	READLINE_LDFLAGS := -L/opt/homebrew/opt/readline/lib -lreadline
endif

BUILTINS_DIR = builtins
CD_DIR = cd
ECHO_DIR = echo
ENV_DIR = env
EXIT_DIR = exit
EXPORT_DIR = export
PWD_DIR = pwd
UNSET_DIR = unset
LIBFT_DIR = libft
INCLUDES = -I$(LIBFT_DIR) -I$(BUILTINS_DIR)

SRCS = main.c errors.c ft_split_quote.c pipex.c checks.c execute.c utils.c token.c check.c lib_ft_more.c\
		token_helper.c lib_functions.c token_add.c free_t.c parse.c var_check.c expand.c built.c\
		quote_help.c remove_quote.c sig_n_free.c here_hand.c pipex_handle.c check_built_init.c red_in_red_out.c\
		red_exec_init.c handle_pipes_n_free.c main_helper.c lexing_pipex_main.c main_more.c built_main_lib.c remove_not_exist.c\
		check_paths.c execute_helpers.c exec_opts.c prepare_arg.c pipex_errors.c alloc_helper.c write_words.c errors_helper.c \
	   $(BUILTINS_DIR)/$(CD_DIR)/ft_cd.c $(BUILTINS_DIR)/$(CD_DIR)/cd_pwd_oldpwd.c \
	   $(BUILTINS_DIR)/$(CD_DIR)/cd_free.c \
	   $(BUILTINS_DIR)/$(CD_DIR)/cd_errors.c $(BUILTINS_DIR)/$(CD_DIR)/cd_utils.c \
	   $(BUILTINS_DIR)/$(ECHO_DIR)/ft_echo.c \
	   $(BUILTINS_DIR)/$(ENV_DIR)/ft_env.c $(BUILTINS_DIR)/$(ENV_DIR)/env_errors.c \
	   $(BUILTINS_DIR)/$(EXIT_DIR)/ft_exit.c $(BUILTINS_DIR)/$(EXIT_DIR)/exit_errors.c \
		$(BUILTINS_DIR)/$(EXPORT_DIR)/ft_export.c $(BUILTINS_DIR)/$(EXPORT_DIR)/export_utils.c \
		$(BUILTINS_DIR)/$(EXPORT_DIR)/export_no=.c $(BUILTINS_DIR)/$(EXPORT_DIR)/export+=.c \
	   $(BUILTINS_DIR)/$(EXPORT_DIR)/export_errors.c $(BUILTINS_DIR)/$(EXPORT_DIR)/checking_export.c \
	   $(BUILTINS_DIR)/$(EXPORT_DIR)/print_export.c $(BUILTINS_DIR)/$(EXPORT_DIR)/export_var_cases.c \
	   $(BUILTINS_DIR)/$(EXPORT_DIR)/export_expand.c \
	   $(BUILTINS_DIR)/$(PWD_DIR)/ft_pwd.c $(BUILTINS_DIR)/$(PWD_DIR)/pwd_errors.c\
       $(BUILTINS_DIR)/$(UNSET_DIR)/ft_unset.c $(BUILTINS_DIR)/$(UNSET_DIR)/unset_errors.c

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a .
	$(CC) $(CFLAGS) $(OBJS) $(READLINE_LDFLAGS) libft.a -o $(NAME)
	$(CC) $(CFLAGS) sigint_sender.c -o $(NAME2)
	$(RM) libft.a

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME) $(NAME2)

re: fclean all
