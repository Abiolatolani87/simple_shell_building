1. Tokenise
2. check the first character of each  token for $
    2.1  if it has $ sign (check length = 2)
            check next char
                if = ?
                    (replace $? with exit status)
                 else if ($)
                    (replace $$ with pid)
    2.2  else != 2 call getenv()
            (replace getenv with value/result)



void interpret_$(char **str)
{
}