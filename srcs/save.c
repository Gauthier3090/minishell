
char		*ft_backslash_input(char *str, t_minishell *shell)
{
	int		i;

	i = 0;
	shell->backs_input = ft_backzero(shell->backs_input);
	while (str[i])
	{
		if (str[i] == '\\' && shell->backs_input[i] == '0')
		{
			if (ft_simple_quotes_check(shell->input, i) == TRUE)
			{
				shell->backs_input[i] = str[i];
				i = 0;
			}
			else if (ft_double_quotes_check(shell->input, i) == FALSE)
			{
				shell->backs_input[i] = str[i];
				while (str[i])
				{
					str[i] = str[i + 1];
					i++;
				}
				i = 0;
			}
			else if (ft_double_quotes_check(shell->input, i) ==\
			TRUE && (str[i + 1] == '$' || str[i + 1] == '\\') &&\
			ft_simple_quotes_check(shell->input, i) == FALSE)
			{
				shell->backs_input[i] = str[i];
				while (str[i])
				{
					str[i] = str[i + 1];
					i++;
				}
				i = 0;
			}
			else
			{
				shell->backs_input[i] = str[i];
				i = 0;
			}
		}
		i++;
	}
	return (str);
}
