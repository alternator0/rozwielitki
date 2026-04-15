#!/bin/bash

# Caly skrpyt napisal jakis llm jak cos
export LC_NUMERIC=C
ROOT_CMD="snap run root-framework"
INPUT_FILE="$1"
TEMP_MACRO="temp_dump.C"

if [ -z "$1" ]; then
    echo "Uzycie: $0 <nazwa_pliku.root>"
    exit 1
fi

# 1. Tworzymy makro, które po prostu wypluwa surowe dane linia po linii
cat > $TEMP_MACRO <<EOF
void temp_dump() {
    TFile *f = TFile::Open("$INPUT_FILE");
    if (!f) return;
    TTree *t;
    f->GetObject("Dane", t);
    if (!t) return;

    Int_t id;
    Double_t edep;
    t->SetBranchAddress("DaphniaID", &id);
    t->SetBranchAddress("EnergiaZdeponowana", &edep);

    for (Long64_t i=0; i<t->GetEntries(); i++) {
        t->GetEntry(i);
        if (edep > 0) printf("RAW_DATA %d %f\n", id, edep);
    }
    f->Close();
}
EOF

# 2. Uruchamiamy i zbieramy surowe dane
RAW_OUTPUT=$($ROOT_CMD -l -b -q $TEMP_MACRO 2>/dev/null)

# 3. Stałe fizyczne
MASA_KG=$(awk 'BEGIN {print 6.28319e-06 / 4}')
MEV_TO_JOULE=1.6022e-13

echo "===================================================="
echo "         WYNIKI ANALIZY DAWKI DLA ROZWIELITEK       "
echo "===================================================="
printf "%-12s | %-18s | %-15s\n" "Obiekt" "Energia [MeV]" "Dawka [Gy]"
echo "----------------------------------------------------"

# 4. Magia Basha: sumujemy dane w locie za pomocą awk
# Szukamy linii RAW_DATA i grupujemy je po ID
echo "$RAW_OUTPUT" | grep "^RAW_DATA" | awk '
{
    suma[$2] += $3
}
END {
    for (id in suma) {
        printf "RESULT %s %.6f\n", id, suma[id]
    }
}' | sort -k2 -n | while read -r LABEL ID SUM_MEV; do
    
    DAWKA_GY=$(awk -v mev="$SUM_MEV" -v mnoznik="$MEV_TO_JOULE" -v masa="$MASA_KG" \
              'BEGIN { printf "%.6e", (mev * mnoznik) / masa }')

    printf "Daphnia %-4s | %-18.4f | %-15s\n" "$ID" "$SUM_MEV" "$DAWKA_GY"
done

# Sprzątanie
rm -f $TEMP_MACRO
