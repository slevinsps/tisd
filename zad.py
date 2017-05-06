# Не успел доделать, она не работает
s1 = input("Введите имя входного файла")
s2 = input("Введите имя выходного файла")
f1 = open(s1,'r')

while True:
    chis = [0]*100
    k = 0
    s = f1.readline()
    if s == '':
        break
    s += ' '
    ch = ''

    for i in range(len(s)):
        if s[i] != ' ':
            ch += s[i]
        else:
            chis[k] = ch
            ch = ''
            k += 1
    maxi = chis[0]
    mini = chis[0]
    for i in range(k):
        if len(chis[i])>len(maxi):
            maxi = chis[i]
        if len(chis[i])<len(mini):
            mini = chis[i]
    f2 = open(s2,'a+')
    for i in range(k):
        if chis[i] == maxi:
            f2.write(mini+' ')
        elif chis[i] == mini:
            f2.write(maxi+' ')
        else:
            f2.write(chis[i]+' ')
    f2.close()
        
