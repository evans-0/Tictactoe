import sys

#wr -> whole row
#wc -> whole column
#ld -> left diagonal
#rd -> right diagonal
l = []
wr, wc, ld, rd = [], [], [], []

def create(size):
    global l
    l = [['-']*size for i in range(size)]
    return l

def mark(i,j,sym):
    """Marks a space"""
    if l[i][j]=='-' and not isMarked(i,j):
        l[i][j] = sym

def view():
    """Displays the game board"""
    for i in range(2*len(l)-1):
        print(" ", end='')
        for j in range(len(l[0])):
            if i%2==0:
                if j!=len(l[0])-1:
                    print("",l[i//2][j], end="  |   ")
                else:
                    print(l[i//2][j])
        if i%2!=0:
            print((len(l[0])-1)*"____|___")
    print((len(l[0])-1)*"     |  ")

def isMarked(i,j):
    """If the space is already marked returns False"""
    if l[i][j]!='-':
        return True
    else:
        return False

def isFinished():
    """If game finished returns True"""
    for i in range(len(l)):
        if '-' in l[i]:
            return False
            break
        else:
            continue
    else:
        return True
    
def isWin():
    """If game won returns True"""
    #Checking whole row
    for i in range(n):
        c_wr = []
        for j in range(n):
            c_wr+=[l[i][j]]
        if c_wr.count('O')==n or c_wr.count('X')==n:
            return True
            

    #Checking whole column
    for i in range(n):
        c_wc = []
        for j in range(n):
            c_wc+=[l[j][i]]
        if c_wc.count('O')==n or c_wc.count('X')==n:
            return True
    
    #Checking left diagonal
    c_ld = []
    for i,j in ld:
        c_ld+=[l[i][j]]
    if c_ld.count('O')==n or c_ld.count('X')==n:
        return True
    
    #Checking right diagonal
    c_rd = []
    for i,j in rd:
        c_rd+=[l[i][j]]
    if c_rd.count('O')==n or c_rd.count('X')==n:
        return True

    return False
            
n = int(input("Enter size of grid: "))
for i in range(n):
        wr+=[(i,j) for j in range(n)]
        wc+=[(j,i) for j in range(n)]
        ld+=[(i,j) for j in range(n) if (i-j==0)]
        rd+=[(i,j) for j in range(n) if (i+j==n-1)]

p1 = input('Enter player 1 name: ')
p2 = input('Enter player 2 name: ')
create(n)
ch = input(f"Choose symbol for {p1} (O/X): ")
if ch=='O' or ch=='o':
    ch_ = 'X'    #player 2 symbol
    ch = 'O'     #player 1 symbol
elif ch=='X' or ch=='x':
    ch_ = 'O'
    ch = 'X'
i = 0
while not isWin() and not isFinished():
    if i%2==0:
        print(f"\n{p1}({ch}) playing...\n")
    else:
        print(f"\n{p2}({ch_}) playing...\n")
    view()
    try:
        row = int(input("\nWhich row do you want to mark? "))
        col = int(input("Which column do you want to mark? "))
        print()
        if i%2==0:
            if not isMarked(row-1,col-1):
                mark(row-1, col-1, ch)
                i+=1
                if isWin():
                    view()
                    print(f"{p1} won!!")
            elif not isWin():
                sys.stderr.write('Already marked\n')
                sys.stdout.flush()
        else:
            if not isMarked(row-1,col-1):
                mark(row-1, col-1, ch_)
                i+=1
                if isWin():
                    view()
                    print(f"{p2} won!!")
            elif not isWin():
                sys.stderr.write('Already marked\n')
                sys.stdout.flush()
    except:
        pass
else:
    if not isWin() and isFinished():
        view()
        print("\nGame tied!!")
    print("Thank you for playing!!!")
