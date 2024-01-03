import math
import random

f = open("date.in", "r")
g = open("date.out", "w")


# Definirea functiei de calculare a valorii corespunzatoare cromozomului pe domeniul de definitie
def valueCromozomDomDef(value, intervalSt, intervalDr, dimCromozom, precizie):
    # Aceasta functie transforma un cromozom din reprezentarea sa sub forma de sir binar intr-un numar intreg,
    # apoi il mapeaza pe intervalul dat
    x = int(value, 2)
    ans = (x * (intervalDr - intervalSt)) / (2 ** dimCromozom - 1) + intervalSt
    return round(ans, precizie)


# Definirea functiei de maximizat
def functieDeMaximizat(x, a, b, c):
    return a * (x ** 2) + b * x + c


def binary_search(probSelectie, left, right, x):
    while left <= right:
        mid = (left + right) // 2

        if probSelectie[mid] == x:
            return mid
        elif probSelectie[mid] < x:
            left = mid + 1
        else:
            right = mid - 1

    return -1


def newPopulation(cromRecomb, intervalSt, intervalDr, dimCromozom, precizie, parametri_functie_maximizat):
    # Aceasta functie primeste ca parametru o lista de cromozomi obtinuti prin recombinare, impreuna cu parametrii
    # necesari pentru maparea lor pe intervalul [intervalSt, intervalDr] si pentru evaluarea functiei de maximizat
    c1 = 1
    for i in cromRecomb:
        c = "".join(i)
        x = valueCromozomDomDef(c, intervalSt, intervalDr, dimCromozom, precizie)
        f = functieDeMaximizat(x, parametri_functie_maximizat[0], parametri_functie_maximizat[1],
                               parametri_functie_maximizat[2])
        g.write(str(c1) + " : " + c + " " + "x: " + str(x) + " f: " + str(f) + '\n')
        c1 += 1


# ~~~~~~~~~~~~~~~MAIN~~~~~~~~~~~~~~~~~
dimPopulatie = int(f.readline())

domeniuDefFunct = f.readline().split()  # initializam, punem valorile intr-o lista
intervalSt = int(domeniuDefFunct[0])  # initializezam capatul st al intervalului
intervalDr = int(domeniuDefFunct[1])  # initializezam capatul drept al intervalului
parametri_functie_maximizat = tuple(map(int, f.readline().split()))  # cream un tuplu si fac fiecare valoare sa fie int
precizie = int(f.readline())
probRecombinare = float(f.readline())
probMutatie = float(f.readline())
etape = int(f.readline())
dimCromozom = int(math.log(((intervalDr - intervalSt) * 10 ** precizie), 2) + 1)


matrixCromozom = [[] for i in range(dimCromozom)]
# Pentru matricea de cromozomi, se creeaza o lista vida pentru fiecare pozitie posibila in cromozom. In functie de
# dimensiunea cromozomului dat ca parametru, se creaza dimCromozom astfel de liste. Matricea finala va fi o matrice de
# dimCromozom x dimPopulatie, unde fiecare element reprezinta o pozitie dintr-un cromozom.
for i in range(dimCromozom):
    for j in range(dimPopulatie):
        matrixCromozom[i].append("0")

matrix = [["0" for i in range(dimCromozom)] for j in range(dimPopulatie)]
# Pentru matricea initiala, se creeaza o matrice de dimPopulatie x dimCromozom, unde fiecare element este initializat
# cu "0". Apoi, pentru fiecare element din matrice, se atribuie aleator fie valoarea "0" fie valoarea "1".
for i in matrix:
    for j in range(len(i)):
        i[j] = str(random.choice([0, 1]))

# ~~~~~am terminat citirea~~~~~~

for i in range(1, etape + 1):
    if i == 1:
        g.write("Suntem la populatia intiala\n")

    # ne generam populatia initiala
    sumaFunctie = 0
    F = []
    X = []
    sumeF = []
    Fmaxim = 0

    # Itereaza prin fiecare element din matrice
    for j in matrix:
        # Adauga mesajul corespunzator in functie de etapa
        if i == 1:
            g.write(str(matrix.index(j) + 1) + " : ")
        # Extrage valoarea cromozomului
        value = ""
        for k in range(len(j)):
            value = value + j[k]
        # Transforma valoarea cromozomului in valoare reala
        x = valueCromozomDomDef(value, intervalSt, intervalDr, dimCromozom, precizie)
        X.append(x)
        # Calculeaza valoarea functiei de maximizat pentru valoarea reala a cromozomului
        f = functieDeMaximizat(x, parametri_functie_maximizat[0], parametri_functie_maximizat[1],parametri_functie_maximizat[2])

        if f > Fmaxim:
            Fmaxim = f  # Actualizeaza valoarea maxima a functiei de maximizat
        F.append(f)
        sumaFunctie += f  # Calculeaza suma valorilor functiei de maximizat
        sumeF.append(sumaFunctie)
        if i == 1:
            g.write(value + " x: " + str(x) + " f: " + str(f) + '\n')


    if i == 1:
        g.write("\nProbabilitatile de selectie:\n")
    # Functia calculeaza probabilitatea de selectie pentru fiecare cromozom, aceasta fiind egala cu valoarea
    # functiei de fitness a cromozomului curent, impartita la suma valorilor functiilor de fitness pentru toti
    # cromozomii. Probabilitatile calculate sunt adaugate intr-o lista si afisate pe ecran, daca functia este
    # apelata in etapa 1. La final, lista cu probabilitati este returnata.
    probSelectie = []
    for j in F:
        p = j / sumaFunctie
        probSelectie.append(i)
        if i == 1:
            g.write("\ncromozom " + str(F.index(j) + 1) + ": " + str(p))
    sumeF2 = []
    ecran = str(0) + " "
    for j in sumeF:
        ecran += str(j / sumaFunctie) + "\n"
        sumeF2.append(j / sumaFunctie)

    if i == 1:
        g.write("\n\nIntervalele probabilitatilor de selectie:\n")
        g.write(ecran)
        g.write("\nProcesul selectionarii: \n")
        c = "".join(matrix[F.index(Fmaxim)])  # extrage cromozomul corespunzator celei mai bune valori de fitness
        # (Fmaxim) din populatia curenta si il converteste dintr-o lista de caractere ('0' si '1') intr-un sir de
        # caractere ('01010101...') utilizand functia "".join().
        g.write("\nElementul etilist: ")
        rez = str(matrix.index(matrix[F.index(Fmaxim)]) + 1) + " : " + c + " x: " + str(X[F.index(Fmaxim)]) + " f: " + str(Fmaxim)
        # f curent va trece in urmatoarea generatie
        g.write(rez)

    # selectam un cromozom din populatie pt a fi inclus in urmatoarea generatie
    # Pentru a selecta un cromozom din populatia curenta, se genereaza un numar aleatoriu intre 0 si 1 utilizand functia
    # random() din biblioteca Python. Acest numar aleatoriu reprezinta probabilitatea de a selecta un anumit cromozom,
    # deci cu cat valoarea generata este mai mare, cu atat este mai mare probabilitatea ca acel cromozom sa fie
    # selectat. Se cauta apoi in lista "probSelectie" pozitia la care se afla valoarea generata aleatoriu, utilizand o
    # functie de cautare binara. Functia returneaza pozitia elementului gasit in lista, pe baza valorii generate
    # aleatoriu. Aceasta pozitie este stocata intr-o variabila numita "indicec". Dupa ce s-a gasit pozitia cromozomului
    # selectat, se extrage cromozomul din matricea de cromozomi (matrix) corespunzator acelei pozitii si se converteste
    # intr-un sir de caractere (""). Acest cromozom este adaugat apoi la lista "cromRecomb" pentru a fi folosit in etapa
    # de recombinare.
    cromRecomb = []  # va contine cromozomii selectati pt recombinare
    for j in range(dimPopulatie):
        u = random.random()
        indicec = binary_search(probSelectie, 0, dimPopulatie - 1, u)
        if i == 1:
            g.write("\nu= " + str(u) + " -> cromozomul selectat: " + str(indicec + 1))
        c = "".join(matrix[indicec])
        cromRecomb.append(c)

    # dupa ce s-a realizat selectia, ne generam noua populatie
    if i == 1:
        g.write("\n\nDupa ce am facut selectia:\n")
        newPopulation(cromRecomb, intervalSt, intervalDr, dimCromozom, precizie, parametri_functie_maximizat)

    #  aplicam operatorul de incrucisare
    if i == 1:
        g.write("\n\nProbabilitatea de incrucisare:\n")
    # selectam cromozomii care vor participa la incrucisare
    cromParticipanti = []
    for j in range(len(cromRecomb)):
        u = random.random()
        # daca u este mai mic decat probabilitatea de incrucisare, cromozomul va participa
        if u < probRecombinare:
            if i == 1:
                g.write(str(j + 1) + " " + cromRecomb[j] + " u= " + str(u)+" < " + str(probRecombinare) + " participa\n")
            cromParticipanti.append(j)
        else:   # altfel nu participa
            if i == 1:
                g.write(str(j + 1) + " " + cromRecomb[j] + " u= " + str(u) + "\n")
    
    
    if i == 1:
        g.write("\nRecombinarile sunt: \n")

    # recombinam cromozomii
    # In timpul operatiei de recombinare, extragem cromozomii care participa la operatie
    while len(cromParticipanti) > 1:
        c1 = random.choice(cromParticipanti)
        cromParticipanti.remove(c1)
        c2 = random.choice(cromParticipanti)
        cromParticipanti.remove(c2)
        punctRupere = random.randint(0, dimCromozom)  # Alegem un punct de rupere pentru recombinare
        c1copie = cromRecomb[c1]  # Facem copia primului cromozom si apoi efectuam recombinarea
        cromRecomb[c1] = cromRecomb[c1][0:punctRupere] + cromRecomb[c2][punctRupere:]
        cromRecomb[c2] = cromRecomb[c2][0:punctRupere] + c1copie[punctRupere:]

        if i == 1:
            g.write("Recombinarea intre cromozomul " + str(c1 + 1) + " si cromozomul " + str(c2 + 1) + " : \n")
            g.write(cromRecomb[c1] + " " + cromRecomb[c2] + " punctul de rupere " + str(punctRupere) + "\n")
            g.write("Rezultatul este " + " " + cromRecomb[c1] + " " + cromRecomb[c2] + '\n')


    # dupa ce s-a realizat recombinarea, ne generam noua populatie
    if i == 1:
        g.write("\nDupa ce s-a realizat recombinarea: \n")
        newPopulation(cromRecomb, intervalSt, intervalDr, dimCromozom, precizie, parametri_functie_maximizat)


    # aplicam operatorul de mutatie asupra unui cromozom
    # Acest cod aplică operatorul de mutație asupra fiecărui cromozom din lista de cromozomi "cromRecomb". Pentru
    # fiecare cromozom, se generează o listă "value" care conține aceleași valori ca și cromozomul, iar apoi se iterează
    # prin această listă și se verifică dacă fiecare bit din cromozom ar trebui să fie inversat în funcție de
    # probabilitatea de mutație "probMutatie". Dacă acesta este cazul, bitul respectiv este inversat în lista "value",
    # iar cromozomul este actualizat cu noul "value". De asemenea, se ține evidența cromozomilor care suferă mutații,
    # adăugându-i la lista "mutatii".
    mutatii = []
    for j in range(len(cromRecomb)):
        value = []
        value.extend(cromRecomb[j])
        for k in range(j):
            u = random.random()
            if u < probMutatie:
                if cromRecomb[j][k] == '1':
                    value[k] = '0'
                    mutatii.append(j)
                else:
                    value[k] = '1'
        cromRecomb[j] = "".join(value)

    # In acest cod, se aplica operatorul de mutatie asupra fiecarui cromozom din populatie.
    # Fiecare gena din cromozom are o probabilitate "probMutatie" de a suferi o mutatie, daca aceasta probabilitate este
    # indeplinita. Daca se produce o mutatie, valoarea genei este inversata (daca este 1 devine 0 si invers).
    # Dupa aplicarea operatorului de mutatie, sunt afisati cromozomii care au suferit mutatii, valoarea maxima si medie
    # a performantei. Pentru fiecare cromozom se calculeaza valoarea functiei de maximizat pe baza valorilor genelor,
    # utilizand functia "functieDeMaximizat".
    if i == 1:
        g.write("\nProbabilitatea de mutatie pentru fiecare gena este: " + str(probMutatie) + '\n')
        g.write("\nUrmatorii cromozomi au fost modificati: \n")
        for el in mutatii:
            g.write(str(el + 1) + '\n')
        g.write("\nDupa mutatie: \n")
        newPopulation(cromRecomb, intervalSt, intervalDr, dimCromozom, precizie, parametri_functie_maximizat)

    if i == 1:
        g.write("\n")
        g.write("\nEvolutia maximului: \n")

    Fmaxim = 0
    for element in cromRecomb:
        c = "".join(element)
        x = valueCromozomDomDef(c, intervalSt, intervalDr, dimCromozom, precizie)
        f = functieDeMaximizat(x, parametri_functie_maximizat[0], parametri_functie_maximizat[1],
                               parametri_functie_maximizat[2])

        if f > Fmaxim:
            Fmaxim = f
    g.write("\nValoarea maxima este: ")
    g.write(str(Fmaxim) + ' -> ')
    g.write("Valoarea medie a performantei este: ")
    g.write(str(Fmaxim / dimPopulatie))
    g.write('\n')

