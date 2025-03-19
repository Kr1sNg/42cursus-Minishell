# Grammar for Minishell

Grammar with [Extended Backus-Naur Form (EBNF)](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form)
	
	```go
	// [...] means None or once
	// {...} means Zero or more times

	<COMMAND_LINE>    	::= <LOGICAL>
	<LOGICAL>       	::= <PIPEEXPR> { ("&&" | "||") <PIPEEXPR> } 
	<PIPEEXPR>       	::= <EXPRESSION> { "|" <EXPRESSION> }
	<EXPRESSION>     	::= <COMMAND>
						| <SUBSHELL>
						
	<COMMAND>         	::= [ <REDIR_LIST> ] <CMD_WORDS> [ <REDIR_LIST> ]
	<SUBSHELL>          ::= "(" <LOGICAL> ")" [ <REDIR_LIST> ]

	<CMD_WORDS>       	::= <WORD> { <WORD> }
	<REDIR_LIST>      	::= <REDIRECTION> { <REDIRECTION> }

	<REDIRECTION>     	::= (">" | "<" | ">>") <WORD>
						| 	"<<" <WORD>
	<WORD>				::= <WORD>

	```
