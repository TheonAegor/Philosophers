NAME = philo

option = -Iincludes

cc = gcc -Wall -Werror -Wextra #-fsanitize=address

files = src/*.c

src = $(wildcard src/*.c)

mkdir = mkdir -p

OBJDIR = obj

obj = $(addprefix $(OBJDIR)/,$(addsuffix .o, $(basename $(notdir $(src)))))

all: $(NAME)

$(NAME): $(obj)
	@$(cc) -o $(NAME) $(option) $^ -lpthread

$(OBJDIR)/%.o:  src/%.c
	@mkdir -p $(OBJDIR)
	$(cc) $(option) -O3 -c $< -o $@

clean:
	rm -rf $(obj)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make all
