import csv
import sys

# define main. use command line argument (csv STR counts for indiv; txt file w DNA sequence)
def main():
    # print error if not 3 command line arguments
    if len(sys.argv) != 3:
        sys.exit("Error: indicate CSV file and txt file")

    # open CSV, read contents into memory
    # code for reading first line from: https://stackoverflow.com/questions/17262256/how-to-read-one-single-line-of-csv-data-in-python
    STR = []
    CSV = sys.argv[1]
    with open(CSV, "r") as csvfile:

        # read and store first line as list
        reader1 = csv.reader(csvfile)
        row1 = next(reader1)

    with open(CSV, "r") as csvfile:
        # read and store each line as a dictionary
        reader = csv.DictReader(csvfile)
        for row in reader:
            STR.append(row)

    # open DNA sequence and read contents into memory
    TXT = sys.argv[2]
    with open(TXT) as file:
        DNA = file.read()

    # for each STR string (first line CSV), compute longest run of conseq repeats in DNA
    DNAcounts = []
    for i in range (len(row1) - 1):
        substr = row1[i + 1]
        total = compare(DNA, substr)
        DNAcounts.append(total)

    #does STR count match any individual in CSV file?
    matched = "No match"
    x = 0
    while x == 0:
        for j in range (len(STR)):
            name = STR[j]["name"]
            counter = 0
            for k in range (len(row1) - 1):
                key = row1[k + 1]
                if (int(STR[j][key])) != DNAcounts[k]:
                    break
                if (int(STR[j][key])) == DNAcounts[k]:
                    counter += 1
                    if counter == (len(row1) -1):
                        matched = name
                        x == 1
        break
    print(matched)
    # print name matching individual, or print "No match"

# function to find substrings STRs in DNA string.
#Substring finder code from: <https://stackoverflow.com/questions/11476713/determining-how-many-times-a-substring-occurs-in-a-string-in-python>.
def compare(DNA, STR):
    
    # define variables
    count = 0
    flag = True
    start = 0
    end = (len(DNA) - 1)

    # return count if no instance of substring at all
    a = DNA.find(STR, start, end)
    if a == -1:
        return count
            
    # if instances present, count consecutive instances
    while flag:
        a = DNA.find(STR, start, end)
        if a == -1:
            flag = False
        else:
            count += 1
            end = len(STR)
            DNA = DNA[a + len(STR): len(DNA)]
     
    while len(DNA) > 2:
        start = 0
        end = (len(DNA))
        count2 = 0
        flag1 = True
        
        # retrun count if no instance of substring at all in this shortened DNA string
        b = DNA.find(STR, start, end)
        if b == -1:
            return count
        
        # if instances present, count consecutive instances
        while flag1: 
            b = DNA.find(STR, start, end)
            if b == -1:
                if count2 > count:
                    count = count2
                flag1 = False
            else:
                count2 +=1
                end = (len(STR))
                DNA = DNA[b + len(STR): len(DNA)]
    return count

# run main
if __name__ == "__main__":
    main()
