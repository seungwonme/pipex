#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "here_doc.h"
#include "safe_syscalls.h"

static char*		get_tmp_file(const char* tmp_dir);
static t_here_doc	init_here_doc(t_vars* vars);
static void			read_input(t_here_doc* here_doc);

void	here_doc(t_vars* vars)
{
	t_here_doc	here_doc;

	here_doc = init_here_doc(vars);
	read_input(&here_doc);
	unlink(here_doc.tmp_file);
}

t_here_doc	init_here_doc(t_vars* vars)
{
	t_here_doc	here_doc;

	here_doc.limiter = vars->argv[2];
	here_doc.tmp_file = get_tmp_file("/tmp/pipex_tmp_");
	here_doc.tmp_fd = safe_open(here_doc.tmp_file, O_CREAT | O_RDWR, 0644);
	return (here_doc);
}

char*	get_tmp_file(const char* tmp_dir)
{
	char*	tmp_file;
	int		i;

	i = 0;
	tmp_file = ft_strjoin(tmp_dir, ft_itoa(i++));
	while (access(tmp_file, F_OK) == 0)
	{
		free(tmp_file);
		tmp_file = ft_strjoin(tmp_dir, ft_itoa(i++));
	}
	return (tmp_file);
}

void	read_input(t_here_doc* here_doc)
{
	char*	buf;
	int		buf_len;
	int		read_cnt;

	buf_len = ft_strlen(here_doc->limiter);
	buf = ft_calloc(sizeof(char), buf_len + 2);
	ft_putstr_fd("> ", 1);
	read_cnt = 0;
	while (read(STDIN_FILENO, buf, buf_len + 1) > 0)
	{
		++read_cnt;
		if (ft_strchr(buf, '\n'))
		{
			if (ft_strncmp(buf, here_doc->limiter, buf_len) == 0 && read_cnt == 1)
				break ;
			read_cnt = 0;
			ft_putstr_fd("> ", 1);
		}
		ft_putstr_fd(buf, here_doc->tmp_fd);
		ft_bzero(buf, buf_len + 1);
	}
	free(buf);
}
