# Počítačové videnie - úloha 1

**Autor: Martin Šváb**

## Rakovinotvorné bunky

### Vstup

![](/output/cancerCells/input.png)

### Červený kanál

Z pôvodného obrázku vyberieme červený kanál, lebo v ňom sú rakovinotvorné bunky najviditeľnejšie.

![](/output/cancerCells/red.png)

### Threshold

Pomocou thresholdu detekujeme rakovinotvorné bunky.

![](/output/cancerCells/threshold.png)

### Výstup

Kontúrovou detekciou bolo nájdených 1179 rakovinotvorných buniek.

![](/output/cancerCells/output.png)

## Pivné bublinky

### Vstup

![](/output/beerBubbles/input.png)

### Grayscale

Z obrázku odstránime farby na jednoduchšie spracovanie.

![](/output/beerBubbles/grayscale.png)

### Canny

Pri správnom nastavení threshold hodnôt môžeme detekovať hrany pivných bubliniek.

![](/output/beerBubbles/canny.png)

### Dilácia

Pomocou dilácie odstránime medzeru medzi bublinkami a spojíme niektoré prerušené hrany bubliniek.

![](/output/beerBubbles/dilate.png)

### Erózia

Pomocou erózie získame pôvodnú veľkosť bubliniek.

![](/output/beerBubbles/erode.png)

### Výstup

Kontúrovou detekciou bolo nájdených 238 pivných bubliniek.

![](/output/beerBubbles/output.png)

## Červené krvinky

### Vstup

![](/output/bloodCells/input.png)

### Zelený kanál

Z pôvodného obrázku vyberieme červený kanál, lebo v ňom sú najviditeľnejšie biele krvinky, ktoré potrebujeme pri spracovaní odstrániť.

![](/output/bloodCells/input.png)

### Gauss

Pomocou gaussovej filtrácie rozmažeme obrázok a odstránime artefakty.

![](/output/bloodCells/gauss.png)

### Všetky krvinky

Pomocou znegovaného thresholdu vyberieme všetky krvinky.

![](/output/bloodCells/allBloodCells.png)

### Biele krvinky

Pomocou znegovaného thresholdu s nižšou hodnotou ako v predošlom obrázku vyberieme všetky biele krvinky.

![](/output/bloodCells/whiteBloodCells.png)

### Červené krvinky

Odčítaním bielych krviniek od všetkých krviniek získame červené krvinky

![](/output/bloodCells/redBloodCells.png)

### Erózia

Pomocou erózie od seba oddelíme niektoré červené krvinky. 

![](/output/bloodCells/erode.png)

### Výstup

Kontúrovou detekciou bolo nájdených 38 červených krviniek.

![](/output/bloodCells/output.png)
