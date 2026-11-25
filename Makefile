NAME = ft_ls
CC = cc
CFLAGS = -Wall -Wextra -Werror
CLANG_FORMAT_IMAGE := ghcr.io/cpp-linter/clang-tools:19
CLANG_FORMAT := docker run --rm --user $(shell id -u):$(shell id -g) -v "$(CURDIR):/src" -w /src $(CLANG_FORMAT_IMAGE) clang-format

SRCS = src/ft_ls.c \
	src/parser.c \
	src/filelist.c \
	src/print.c \
	src/sort.c

OBJS = $(SRCS:.c=.o)
FORMAT_FILES = $(SRCS) $(wildcard include/*.h)
TEST_FILES = $(wildcard test/*.test.sh)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full ./$(NAME)

test: $(NAME)
	@for test in $(TEST_FILES); do sh "$$test" || exit 1; done

format:
	$(CLANG_FORMAT) -i --style=file $(FORMAT_FILES)

format-check:
	$(CLANG_FORMAT) --dry-run --Werror --style=file $(FORMAT_FILES)

.PHONY: all clean fclean re valgrind test format format-check
