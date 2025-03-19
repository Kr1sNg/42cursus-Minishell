/*print environment variable*/

// #include <stdio.h>
// #include <stdlib.h>

// int main() 
//{
//     char *path = getenv("PATH");
//     if (path)
//         printf("PATH: %s\n", path);
//     else
//         printf("PATH not found\n");

//     return 0;
// }


/* print all env variables*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
	int		i = 0;
	char 	*env_variables = envp[i];

	while (env_variables)
	{
		printf("%s\n", env_variables);
		i++;
		env_variables = envp[i];
	}
	return (0);
}
