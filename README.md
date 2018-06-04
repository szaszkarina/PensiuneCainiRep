Pensiunea Canina
	Proiectul meu este un program care ne ajuta pe mine si pe parintii mei cu managementul afacerii noastre. El are un meniu care are 4 optiuni: afisarea padocurilor, afisarea animalelor, adaugarea unui animal nou si inchidere program. 
	El foloseste mai multe operatii cu ajutorul listelor si al arborilor, practic fiind o lista in care nodurile sunt arbori.
	Ce este interesant sunt arborii de intervale care au un mod de parcurgere foarte interesant. 
Avand doua intervale de exemplu: [27.04.2018 (not=d1) - 29.04.2018 (not=d2) ] si [10.05.2018 (not=d3) - 15.05.2018 (not=d4) ], compararea pentru a verifica daca exista un padoc liber se va face oarecum in X. Adica se vor compara d1 cu d4 si d2 cu d3 avand doua optiuni:
	~ Daca data d2 < data d3 mergem pe stanga arborelui (se verifica ziua, luna si anul)
	~ Daca data d1 > data d4 mergem pe dreapta arborelui (se verifica ziua, luna si anul)
Parcurgerea se va face in inordine (stg-rad-dr), iar programul afiseaza crescator.
