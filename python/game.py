print("Tictactoe Game:\n\t1.Single Player\n\t2.Two Player")
ch = eval(input("Enter choice: "))
if ch==1:
    import single_player_tictactoe
elif ch==2:
    import tictactoe
