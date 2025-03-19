# Grammar for BaSh

```go
// [...] means None or once
// {...} means Zero or more times

<COMMAND_LINE>    	::= <EXPRESSION>

<EXPRESSION>      	::= <LOGICAL_EXPR>

<LOGICAL_EXPR>    	::= <PIPE_EXPR> { ("&&" | "||") <PIPE_EXPR> } 

<PIPE_EXPR>       	::= <SIMPLE_EXPR> { "|" <SIMPLE_EXPR> }

<SIMPLE_EXPR>     	::= <COMMAND> 
                    | "(" <EXPRESSION> ")"

<COMMAND>         	::= <CMD_WORDS> [ <REDIR_LIST> ]

<CMD_WORDS>       	::= <WORD> { <WORD> }
                    | <ASSIGNMENT_WORD> { <WORD> }

<REDIR_LIST>      	::= <REDIRECTION> { <REDIRECTION> }

<REDIRECTION>     	::= ">"  <FILENAME>
                    | "<"  <FILENAME>
                    | ">>" <FILENAME>
                    | "<<" <HERE_END>

<ASSIGNMENT_WORD>	::= <WORD> "=" <WORD>

<FILENAME>			::= <WORD>

<HERE_END>			::= <WORD>

```