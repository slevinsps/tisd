
def find_Min_Max(a,k):
    maxi = a[0]
    mini = a[0]
    for i in range(k):
        if len(a[i])>len(maxi):
            maxi = a[i]
        if len(a[i])<len(mini):
            mini = a[i]
    return mini, maxi

def swap(a,maxi,mini,k):
    ss = ''
    for i in range(k): 
        if a[i] == maxi:
            ss += mini+' '
        elif a[i] == mini:
            ss += maxi+' '   
        else:
            ss += a[i]+' '
    return ss

def readString(s):
    kk = 0
    chis = [0]*100
    k = 0

    if s == '':
        return -1, -1
    s = s.rstrip()
    s += ' '
    ch = ''
    for i in range(len(s)):
        if s[i] != ' ':
            ch += s[i]
        else:
            chis[k] = ch
            kk += 1
            ch = ''
            k += 1
    if kk > 100:
        return -2,-2
    return chis, k

def printString(s,s2):
    f2 = open(s2,'a+')
    f2.write(s+'\n')
    f2.close()
def check(s1,s2):
    
    try:
        f1 = open(s1,'r')
    except IOError:
        print ("Не найден входной файл")
        
    
    try:
        f2 = open(s2,'w')
    except IOError:
        print ("Не найден выходной файл")
        return -2
    f1.close()
    f2.close()
    return 0
    
def main():
    kk = 0
    s1 = input("Введите имя входного файла: ")
    s2 = input("Введите имя выходного файла: ")
    t = check(s1,s2)
    if t == 0:
        f1 = open(s1,'r')
        while True:
            s = f1.readline()
            kk += 1
            if kk > 100:
                break
            chis,k = readString(s)
            if k == -1:
                break
            if k == -2:
                print("Ошибка слов в строке больше 100")
                break
            mini,maxi = find_Min_Max(chis,k)
            ss = swap(chis,maxi,mini,k)
            printString(ss,s2)
        f1.close()

main()
