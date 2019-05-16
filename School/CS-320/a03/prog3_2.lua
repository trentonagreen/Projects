function InfixToPostfix(str)

    
    --print("Assignment #3-2, Trenton Green, trenton.green@sbcglobal.net\n")

    stack = {}
    stackSize = 0

    postfix = {}
    postSize = 0
    ops = {}
    opSize = 0

    priority = 0
    popPriority = 0
    
    result = " "

    for token in string.gmatch(str, "[^%s]+") do
        
        -- check if string is an operator
        -- else it is a number, push onto postfix stack and increment postfix size
        if string.match(token, "+") or string.match(token, "-") or string.match(token, "*") or string.match(token, "/") then

            -- check if there have been any operators
            -- if 0 operators, push onto stack and increment amount of operators
            if opSize == 0 then
                table.insert(ops,token)
                opSize = opSize + 1
                
            -- else loop through and set a value on operators
            -- if '*' or '/' set a higher value than '+' or '-'
            -- do this check for both the token and operator on stack
            else
                bool = 1
                while bool == 1 do

                    if opSize == 0 then
                        table.insert(ops,token)
                        opSize = opSize + 1
                        bool = 0
                        break
                    end
                    
                    if string.match(ops[opSize],"*")  then priority = 1 end
                    if string.match(ops[opSize],"/")  then priority = 1 end
                    if string.match(ops[opSize],"-")  then priority = 0 end
                    if string.match(ops[opSize],"+")  then priority = 0 end

                    if string.match(token,"*")  then popPriority = 1 end
                    if string.match(token,"/")  then popPriority = 1 end
                    if string.match(token,"-")  then popPriority = 0 end
                    if string.match(token,"+")  then popPriority = 0 end

                    -- if the token is lower priority push onto postfix 
                    -- increment postfix and decrement operator
                    -- continue loop
                    if priority >= popPriority then
                        table.insert(postfix, table.remove(ops))
                        postSize = postSize + 1
                        opSize = opSize - 1
                    -- else token has higher priority
                    -- push operator onto stack
                    -- end loop
                    else
                        table.insert(ops, token)
                        opSize = opSize + 1
                        bool = 0
                    end
                end
            end
        else
            table.insert(postfix, token)
            postSize = postSize + 1
        end
    end

    -- if there are still operators left over
    -- set to the end of the postfix stack
    while opSize > 0 do
        table.insert(postfix, table.remove(ops))
        opSize = opSize -1
        postSize = postSize + 1
    end

    i = 1
    
    -- append the contents of postfix stack followed by a ' '
    while i <= postSize do
        result = result .. postfix[i] .. " " 
        i = i + 1
    end

    return result
    
end