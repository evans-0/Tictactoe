import sys
import random

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

def isMarked(i,j):
    """If the space is already marked returns False"""
    if l[i][j]!='-':
        return True
    else:
        return False

def mark(i,j,sym):
    """Marks a space"""
    if l[i][j]=='-' and not isMarked(i,j):
        l[i][j] = sym
def comp_mark(sym):
    """Computer marking"""
    avail = []
    l1 = list(l)
    for i in range(len(l)):
        for j in range(len(l)):
            if not isMarked(i, j):
                avail.append((i, j))  #available spaces to mark
    if sym=='X':
        o_sym = 'O'
    else:
        o_sym = 'X'

    for r, c in avail:
        l1[r][c] = sym
        if isWin(l1):  #Checking if computer won after computer marked
            l[r][c] = sym
            return 0
        else:
            l1[r][c] = '-'
        
    for r, c in avail:
        l1[r][c] = o_sym
        if isWin(l1):  #Checking if player won after player marked
            l[r][c] = sym
            break
        else:
            l1[r][c] = '-'
    else:
        n = random.randint(0, len(avail) - 1)
        l[avail[n][0]][avail[n][1]] = sym
        return 0
   
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
    
def isWin(arr):
    """If game won returns True"""
    n = len(arr)
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
            
def play(size):
    create(size)
    i = 0
    while not isWin(l) and not isFinished():
        if i%2==0:
            print(f"\n{p1}({ch}) playing...\n")
        else:
            print(f"\n{p2}({ch_}) playing...\n")
        try:
            if i%2==0:
                view()
                row = int(input("\nWhich row do you want to mark? "))
                col = int(input("Which column do you want to mark? "))
                print()
                if (row>size or col >size or row<1 or col<1):
                    sys.stderr.write("Enter a valid row or column\n")
                else:
                    if not isMarked(row-1,col-1):
                        mark(row-1, col-1, ch)
                        i+=1
                        if isWin(l):
                            view()
                            print(f"{p1} won!!")
                            return 1
                    elif not isWin():
                        sys.stderr.write('Already marked\n')
                        sys.stdout.flush()
            else:
                comp_mark(ch_)
                i+=1
                if isWin(l):
                    view()
                    print(f"{p2} won!!")
                    return 2
        except:
            pass
    else:
        if not isWin(l) and isFinished():
            view()
            print("\nGame tied!!")
            return 0
        

n = int(input("Enter size of grid: "))
for i in range(n):
        wr+=[(i,j) for j in range(n)]
        wc+=[(j,i) for j in range(n)]
        ld+=[(i,j) for j in range(n) if (i-j==0)]
        rd+=[(i,j) for j in range(n) if (i+j==n-1)]

p1 = input('Enter player name: ')
p2 = "Computer"
ch = input(f"Choose symbol for {p1} (O/X): ")
if ch=='O' or ch=='o':
    ch_ = 'X'    #computer symbol
    ch = 'O'     #player 1 symbol
elif ch=='X' or ch=='x':
    ch_ = 'O'
    ch = 'X'

num_game = int(input("Enter number of game: "))   #No. of games
s1 = 0   #s1 -> score of player 1
s2 = 0   #s2 -> score of computer

for i in range(num_game):
    print(f"\nMatch {i+1} of {num_game}")
    res = play(n)
    if res==1:
        s1+=1
    elif res==2:
        s2+=1

print(f"\nScores:\n{p1} -> {s1}\n{p2} -> {s2}")
print("\nThank you for playing!!!")
