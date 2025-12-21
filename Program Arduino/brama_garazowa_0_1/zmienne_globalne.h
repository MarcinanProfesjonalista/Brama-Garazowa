// =====================
// STANY JAZDY
// =====================
bool jedzie_w_dol = false;
bool jedzie_w_gore = false;
bool zaciety = false;

bool trybSET = false;
bool autoStop = false;
bool awaria = false;

// =====================
// BLOKADY / LOCKI
// =====================
bool lock_po_uruchomieniu = true;
bool lock_po_jazdach_przyciskiem = false;
bool lock_po_uderzeniu_w_krancowke_gorna = false;  
bool lock_po_uderzeniu_w_krancowke_dolna = false;  

bool zezwol_na_jazde_w_gore = true;                
bool zezwol_na_jazde_w_dol = true;                 
bool zezwol_na_zapis_pozycji = true;               

// =====================
// KRAŃCÓWKI
// =====================
bool krGorna = false;
bool krDolna = false;

// =====================
// PRZYCISKI – STANY GLOBALNE
// =====================
bool momentaryUp = false;
bool momentaryDown = false;
bool setUp = false;
bool setDown = false;

// =====================
// CZASY I RUCH
// =====================
unsigned long startCzasJazdy = 0;
unsigned long czasZmianyKierunku = 0;

const unsigned long czasGora = 8000;
const unsigned long czasDol  = 6000;
const unsigned long deadTime = 300;


