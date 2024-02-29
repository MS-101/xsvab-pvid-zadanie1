# Počítačové videnie - úloha 1

**Autor: Martin Šváb**

## Rakovinotvorné bunky

### Vstup

![](xsvab-pvid-zadanie1/output/cancerCells/input.png)

### Červený kanál

Z pôvodného obrázku vyberieme červený kanál, lebo v ňom sú rakovinotvorné bunky najviditeľnejšie.

![](xsvab-pvid-zadanie1/output/cancerCells/red.png)

### Threshold

Pomocou thresholdu detekujeme rakovinotvorné bunky.

![](xsvab-pvid-zadanie1/output/cancerCells/threshold.png)

### Výstup

Kontúrovou detekciou bolo nájdených 1179 rakovinotvorných buniek.

![](xsvab-pvid-zadanie1/output/cancerCells/output.png)

## Pivné bublinky

### Vstup

![](xsvab-pvid-zadanie1/output/beerBubbles/input.png)

### Grayscale

Z obrázku odstránime farby na jednoduchšie spracovanie.

![](xsvab-pvid-zadanie1/output/beerBubbles/grayscale.png)

### Canny

Pri správnom nastavení threshold hodnôt môžeme detekovať hrany pivných bubliniek.

![](xsvab-pvid-zadanie1/output/beerBubbles/canny.png)

### Dilácia

Pomocou dilácie odstránime medzeru medzi bublinkami a spojíme niektoré prerušené hrany bubliniek.

![](xsvab-pvid-zadanie1/output/beerBubbles/dilate.png)

### Erózia

Pomocou erózie získame pôvodnú veľkosť bubliniek.

![](xsvab-pvid-zadanie1/output/beerBubbles/erode.png)

### Výstup

Kontúrovou detekciou bolo nájdených 238 pivných bubliniek.

![](xsvab-pvid-zadanie1/output/beerBubbles/output.png)

## Červené krvinky

### Vstup

![](xsvab-pvid-zadanie1/output/bloodCells/input.png)

### Zelený kanál

Z pôvodného obrázku vyberieme červený kanál, lebo v ňom sú najviditeľnejšie biele krvinky, ktoré potrebujeme pri spracovaní odstrániť.

![](xsvab-pvid-zadanie1/output/bloodCells/input.png)

### Gauss

Pomocou gaussovej filtrácie rozmažeme obrázok a odstránime artefakty.

![](xsvab-pvid-zadanie1/output/bloodCells/gauss.png)

### Všetky krvinky

Pomocou znegovaného thresholdu vyberieme všetky krvinky.

![](xsvab-pvid-zadanie1/output/bloodCells/allBloodCells.png)

### Biele krvinky

Pomocou znegovaného thresholdu s nižšou hodnotou ako v predošlom obrázku vyberieme všetky biele krvinky.

![](xsvab-pvid-zadanie1/output/bloodCells/whiteBloodCells.png)

### Červené krvinky

Odčítaním bielych krviniek od všetkých krviniek získame červené krvinky

![](xsvab-pvid-zadanie1/output/bloodCells/redBloodCells.png)

### Erózia

Pomocou erózie od seba oddelíme niektoré červené krvinky. 

![](xsvab-pvid-zadanie1/output/bloodCells/erode.png)

### Výstup

Kontúrovou detekciou bolo nájdených 38 červených krviniek.

![](xsvab-pvid-zadanie1/output/bloodCells/output.png)
