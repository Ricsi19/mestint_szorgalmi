
### Mesterséges Intelligencia szorgalmi feladat

  

### Szabó Richárd István

  

___

  

#### A megoldásról:

- Valószínű nem túl népszerű nyelvben oldottam meg, ami a C :). 
- MINIMAX algoritmust implementáltam, az input karakterjei között szóköz kell (x x 2 x) 
- Osztály helyett struktúrát használtam
  

##### Futtatáshoz szükséges környezet
 - A legegyszerűbb a minimax.C kódot kimásolni, és CLion-ban egy új projektbe illeszteni
 - Linux környezetben szükség lesz a gcc fordítóra, majd terminálban a minimax.C kódhoz navigálva, a következőket kell megadni:
	 - `gcc minmax_fa.c -o minmax_fa`
	 - `./minmax_fa`
 - Windows esetén szükség van a minGW-re, aztán a következőket kell megadni:
	- `gcc minmax_fa.c -o minmax_fa.exe`
	 - `minmax_fa.exe`
 - Miután elindult a program, intuitív módon meg kell adni a fát listaként, amit az 1. pontban ismertettem, milyen módon kell.

