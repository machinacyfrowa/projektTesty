# projektTesty <br>
Dostępne przełączniki dla klienta: <br>
-v - tryb gadatliwy - wali wszystkim na ekran <br>
-t xxx - załaduj plik xxx z komendami testowymi <br>
-o xxx - loguj do pliku xxx <br>
 <br>
Przykładowe użycie:  <br>
./client -v -t testFile.txt -o logFile.txt  <br>
 <br>
Możliwe polecenia w pliku z komendami testowymi: <br>
c xxx - połącz z serwerem pod adresem ip xxx <br>
s xxx - wyślij łańcuch tekstowy xxx <br>
p xxx - wyślij plik o nazwie xxx <br>
g xxx - pobierz plik o nazwie xxx <br>
d - rozłącz z serwerem <br>
q - wyjdź z programu <br>
 <br>
Uruchomienie serwera w tle: <br>
./server &
