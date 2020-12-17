#include "../includes/header.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] && s2[i]) && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int main ()
{
char *a = "AA";
char *b = "AB";
/*char *c = "AC";*/
char *c = "BC";

printf("%i\n", ft_strcmp(a, b));
printf("%i\n", ft_strcmp(b, a));
printf("%i\n", ft_strcmp(a, c));
printf("%i\n", ft_strcmp(c, b));
printf("%i\n", ft_strcmp(b, b));

}
