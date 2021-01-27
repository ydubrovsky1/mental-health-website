from cs50 import get_int


height = get_int("Height: ")
while height > 8 or height < 1:
    height = get_int("Height: ")
for j in range(height):
    print(" " *(height - (j + 1)), end="" )
    print("#" * (j + 1))