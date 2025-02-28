
#include <stdio.h>

typedef	struct s_test
{
	int		t1;
	long	t2;
} test;


typedef struct s_test2
{
	long	a1;
	long	a2;
} example;

typedef struct s_ast
{
	char	*s;
	union
	{
		test	test;
		example	example;
	};
	
} t_ast;

typedef struct s_pointer
{
	/* data */
};
