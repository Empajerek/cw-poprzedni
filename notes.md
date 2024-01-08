# Code review Konrad Kaczmarczyk

1. `8` `9` możesz chyba wpisać na stałe zmienne `L` i `R` do programu, używasz ich raz.
2. Dziwna nazwa `convertTo_UINT()`
3. `62` nagle używasz `auto` gdy linijke wcześniej piszesz `shared_ptr`
4. `62` agresywne zawijanie linijek, troche niespójne z wcześniejszymi
5. `70`, hmm `std::`
6. `71` użwyając `(int)seq.size()` strasznie zamulasz program, warto wrzucić to jak zmienną pomocniczą
7. `89`, i `90` powrót `auto`, mimo że w linijce `60` już piszesz typ zmiennej
8. Lubie w kodzie gdy jest dużo pustych linijek, lecz używasz ich chaotycznie, raz są często, raz ich nie ma, postaraj się to usystematyzować

