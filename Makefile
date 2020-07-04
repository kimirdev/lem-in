all:
	gcc *.c lemin.h -L libft libft/libft.a

clean:
	rm -rf a.out
