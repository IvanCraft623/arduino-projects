// *********************************************************************
// Char cosntants
// *********************************************************************

const int FULL_CHAR = 255;
const int EMPTY_CHAR = 254;

const int FIRST_CUSTOM_CHAR = 0;
const int SECOND_CUSTOM_CHAR = 1;
const int THIRD_CUSTOM_CHAR = 2;
const int FOURTH_CUSTOM_CHAR = 3;
const int FIFTH_CUSTOM_CHAR = 4;
const int SIXTH_CUSTOM_CHAR = 5;
const int SEVENTH_CUSTOM_CHAR = 6;
const int EIGHTH_CUSTOM_CHAR = 7;

// *********************************************************************
// Custom chars
// *********************************************************************

uint8_t plant_first[8] = {
  B00000,
  B00000,
  B01110,
  B01011,
  B01101,
  B00110,
  B00011,
  B00000
};

uint8_t plant_second[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10001,
  B10001,
  B10001
};

uint8_t plant_third[8] = {
  B00000,
  B00000,
  B00000,
  B01110,
  B11010,
  B10110,
  B01100,
  B11000
};

uint8_t plant_fourth[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001
};

uint8_t plant_fifth[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B11111
};

uint8_t plant_sixth[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000
};

uint8_t plant_seventh[8] = {
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

uint8_t plant_eighth[8] = {
  B00000,
  B00000,
  B11011,
  B00100,
  B00100,
  B11111,
  B01110,
  B01110
};

uint8_t accented_a[] = {
  B00111,
  B00000,
  B01110,
  B00001,
  B01111,
  B10001,
  B01111,
  B00000
};

uint8_t accented_e[] = {
  B00111,
  B00000,
  B01110,
  B10001,
  B11111,
  B10000,
  B01110,
  B00000
};

uint8_t accented_i[] = {
  B00111,
  B00000,
  B01100,
  B00100,
  B00100,
  B00100,
  B01110,
  B00000
};

uint8_t accented_o[] = {
  B00111,
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000
};

uint8_t accented_u[] = {
  B00111,
  B00000,
  B10001,
  B10001,
  B10001,
  B10011,
  B01101,
  B00000
};

// *********************************************************************
// Chars registers
// *********************************************************************
  void registerAccentedVowels() {
    lcd.createChar(SECOND_CUSTOM_CHAR, accented_a);
    lcd.createChar(THIRD_CUSTOM_CHAR, accented_e);
    lcd.createChar(FOURTH_CUSTOM_CHAR, accented_i);
    lcd.createChar(FIFTH_CUSTOM_CHAR, accented_o);
    lcd.createChar(SIXTH_CUSTOM_CHAR, accented_u);
  }

  void registerPlantChars() {
    lcd.createChar(FIRST_CUSTOM_CHAR, plant_first);
    lcd.createChar(SECOND_CUSTOM_CHAR, plant_second);
    lcd.createChar(THIRD_CUSTOM_CHAR, plant_third);
    lcd.createChar(FOURTH_CUSTOM_CHAR, plant_fourth);
    lcd.createChar(FIFTH_CUSTOM_CHAR, plant_fifth);
    lcd.createChar(SIXTH_CUSTOM_CHAR, plant_sixth);
    lcd.createChar(SEVENTH_CUSTOM_CHAR, plant_seventh);
    //lcd.createChar(EIGHTH_CUSTOM_CHAR, plant_eighth);
  }

void drawPlant(uint8_t offsetCol, uint8_t offsetRow) {
  registerPlantChars();

  lcd.setCursor(offsetCol, offsetRow);
  lcd.write(FIRST_CUSTOM_CHAR);
  lcd.write(SECOND_CUSTOM_CHAR);
  lcd.write(THIRD_CUSTOM_CHAR);

  lcd.setCursor(offsetCol, offsetRow + 1);
  lcd.write(FOURTH_CUSTOM_CHAR);
  lcd.write(FIFTH_CUSTOM_CHAR);
  lcd.write(SIXTH_CUSTOM_CHAR);

  lcd.setCursor(offsetCol + 1, offsetRow + 2);
  lcd.write(SEVENTH_CUSTOM_CHAR);
}
