def dfs(i, x, y, a, s, ops):   
    if ops != '':
        c = ops[-1]
        if c == 'r':
            s += 1
        elif c == 'L':
            a = (a + 1) % 4
        elif c == 'R':
            a = (a + 3) % 4
        if a == 0:
            x += s
        elif a == 1:
            y += s
        elif a == 2:
            x -= s
        elif a == 3:
            y -= s
        
    if i == 20:
        if x == 168 and y == 32:
            print(ops)
        return
    
    dfs(i+1,x,y,a,s,ops+"r")
    dfs(i+1,x,y,a,s,ops+"L")
    dfs(i+1,x,y,a,s,ops+"R")

dfs(0,0,0,0,0,'')