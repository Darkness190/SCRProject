# Zasady przy projektowaniu
Od urządzeń do procesu może być event data.
Od procesu do wątku może być event data.
Z i do wątku porty (raczej event data).
Z i do podprogramu tylko parametry (nie porty).
Connections między wątkiem a podprogramem to parametry.
Ale lepiej popatrzeć po prostu na kod.

# Opis systemu
Zakładamy, że jest jakaś górna granica czasu parkowania. Założenie to pozwala ustalić, czy klient posiada wystarczającą ilość środków na koncie. Przy wyjeździe z parkingu, wysyłamy do jakiegoś zewnętrznego serwisu informację odnośnie naliczenia odpowiedniej kwoty. Opłata może zostać dokonana po wyjeździe - nie kontrolujemy czy zapłacił czy nie, zakładamy, że zajmie się tym inny system. Niewypuszczenie klienta byłoby co najmniej nietaktowne.

### WJAZD:

1) Pojazd wjeżdża przed bramkę aktywując `entry_driveway_sensor`.

2) Sensor przekazuje informację do kamery przy wjeździe `entry_camera`, która pobiera obraz tablicy rejestracyjnej użytkownika.

3) Tablica zostaje przesłana do kontrolera, który w wątku `image_processing_thread` wydobywa z niej numery, zapisuje do pamięci i przesyła je do `network_module`

4) `network_module` reprezentuje całą komunikację z zewnętrznym systemem odpowiedzialnym za kontrolę konta użytkownika związanego z parkingiem. Po otrzymaniu tablicy sprawdza czy użytkownik posiada wystarczającą kwotę na koncie by opłacić parking. Jeśli nie, wysyła sygnał do `parking_display` który informuje o tym użytkownika. Jeśli tak, przesyła informację o tym do kontrolera.

5) Kontroler uruchamia proces `check_slots_thread`, który sprawdza ilość dostępnego miejsca. Jeśli jest wystarczająca - przesyła do `entry_gate` polecenie podniesienia szlabanu. Jeśli nie - przesyła zapytanie do `network_module`, które zwraca informację o adresie innego parkingu na którym są miejsca. Ta jest wyświetlana przez `parking_display`

6) Po przejechaniu przez bramkę, `entry_gate_passing_sensor` przesyła sygnał do wątku `car_passed_gate_handler_thread`, który zamyka bramkę, inkrementuje ilość użytkowników i zapisuje timestamp momentu w którym użytkownik wjechał.

	
### WYJAZD:
Analogicznie do wjazdu tylko z bramką, kamerą i sensorami wyjazdowymi. Po przetworzeniu numeru tablicy wysyłany jest sygnał do wątku `calculate_price` a następnie przez `network_module` przesyłany jest sygnał do serwisu, żeby naliczył opłatę na konto użytkownika związanego z daną tablicą. Jeśli informacja została przesłana i przetworzona pomyślnie, `network_module` zwraca sygnał do otwarcia bramki. Reszta logiki jest analogiczna jak przy wjeździe.

# Pytania
1) 1 wyjście z wątku na 2 wejścia - Rozwiązaliśmy to przez umieszczenie dwóch wyjść z subprogramu, ale nie jestem pewien czy działa. Wydaje mi się, że powinien przesłać dwa rózne "deskryptory" do subprogramu.
2) typy portów (event data?) 
3) sieć - Rozwiązaliśmy przez dodanie `network_module`
4) priorytety - tak

