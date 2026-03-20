#!/bin/bash
#wygenerowane przez llm jak cos
# Ustawienia nazwy komendy (dla Snapa)
ROOT_CMD="snap run root-framework"

# Sprawdzenie czy komenda root istnieje
if ! command -v $ROOT_CMD &> /dev/null; then
    echo "Błąd: Nie znaleziono komendy '$ROOT_CMD'."
    echo "Zmień zmienną ROOT_CMD w skrypcie na komendę uruchamiającą root."
    exit 1
fi
# Sprawdzenie argumentu
if [ -z "$1" ]; then
    echo "Uzycie: $0 <nazwa_pliku.root>"
    exit 1
fi

INPUT_FILE="$1"
TREE_NAME="Dane"
BRANCH_NAME="Energia Zdeponowana"
TEMP_MACRO="temp_calc_energy.C"

# 1. Tworzymy tymczasowy plik makra C++
# Dzięki temu unikamy problemów z cudzysłowami w terminalu
cat > $TEMP_MACRO <<EOF
#include <iostream>
#include "ROOT/RDataFrame.hxx"

void temp_calc_energy() {
    // Wylaczamy zbedne logi ROOTa
    gErrorIgnoreLevel = kError;

    // Tworzymy ramke danych
    ROOT::RDataFrame d("$TREE_NAME", "$INPUT_FILE");

    // Liczymy sume
    double suma = d.Sum("$BRANCH_NAME").GetValue();

    // Wypisujemy w unikalny sposob
    std::cout << ">>>WYNIK=" << suma << std::endl;
}
EOF

# 2. Uruchamiamy ROOTa na tym pliku
# Przechwytujemy wynik do zmiennej
RAW_OUTPUT=$($ROOT_CMD -l -b -q $TEMP_MACRO 2>/dev/null)

# 3. Wyciągamy liczbę z wyniku (grep + cut)
FINAL_RESULT=$(echo "$RAW_OUTPUT" | grep ">>>WYNIK=" | cut -d'=' -f2)

# 4. Sprzątamy (usuwamy plik tymczasowy)
rm -f $TEMP_MACRO

# 5. Sprawdzamy czy udalo sie pobrac liczbe
if [ -z "$FINAL_RESULT" ]; then
    echo "BŁĄD: Nie udalo sie wyciagnac danych. Sprawdz czy plik .root istnieje." >&2
    # Opcjonalnie: odkomentuj linię poniżej, żeby zobaczyć co ROOT wypluł w razie błędu
    # echo "$RAW_OUTPUT" >&2
    exit 1
else
    MASA_KG=$(awk 'BEGIN {print 6.28319e-06 / 4}')
    
    MEV_TO_JOULE=1.6022e-13

    # Przekazujemy zmienne z basha do awk używając flagi -v
    ENERGIA_J=$(awk -v wynik="$FINAL_RESULT" -v mnoznik="$MEV_TO_JOULE" 'BEGIN {print (wynik / 4) * mnoznik}')

    ENERGIA_MeV=$(awk -v wynik="$FINAL_RESULT" 'BEGIN {print wynik / 4}')

    # Obliczamy dawkę w Grejach (Gy = J / kg)
    DAWKA_GY=$(awk -v j="$ENERGIA_J" -v m="$MASA_KG" 'BEGIN {print j / m}')

    echo "=== WYNIKI ANALIZY ==="
    echo "Całkowita zdeponowana energia: $FINAL_RESULT MeV"
    echo "Energia zdeponowana w jednym obiekcie: $ENERGIA_MeV MeV"
    echo "Masa pojedynczego obiektu:  $MASA_KG kg"
    echo "--------------------------------------"
    echo "POCHŁONIĘTA DAWKA: $DAWKA_GY Gy"
fi

