shell: \
			main.o \
			exec_cd.o \
			display_shell_prompt.o \
			parse_str.o \
			readcmd.o \
			interpret_cmd.o \
			exec_ls.o \
			exec_cd.o \
			exec_pinfo.o
	$(CC) -g -o shell $^

clean:
	@rm -f *.o shell

main.o: shell.h main.c
	$(CC) -g -c main.c

exec_cd.o: shell.h exec_cd.c
	$(CC) -g -c exec_cd.c

exec_ls.o: shell.h exec_ls.c
	$(CC) -g -c exec_ls.c

exec_pinfo.o: shell.h exec_pinfo.c
	$(CC) -g -c exec_pinfo.c

display_shell_prompt.o: shell.h display_shell_prompt.c
	$(CC) -g -c display_shell_prompt.c

parse_str.o: shell.h parse_str.c
	$(CC) -g -c parse_str.c

readcmd.o: shell.h readcmd.c
	$(CC) -g -c readcmd.c

