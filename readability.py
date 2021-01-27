from cs50 import get_string

# get user input
text = get_string("Text: ")

# initialize variables
letters = 0 
words = 1
sentences = 0

# iterate through text
for c in text:
    a = ord(c)
    
    # count letters 
    if a > 64 and a < 90 or a > 96 and a < 122:
        letters += 1
    
    # count words
    elif (a == 32):
        words += 1
    
    # count sentences
    elif a == 46 or a == 63 or a == 33:
        sentences += 1
        
# calculate Coleman-Liau
L = letters / (words / 100)
S = sentences / (words / 100)
CL = .0588 * L - .296 * S - 15.8

# round and return grade level
grade = round(CL)
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade} ")