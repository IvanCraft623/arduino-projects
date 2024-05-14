// *********************************************************************
// includes
// *********************************************************************
  #include <EEPROM.h>

/* ===================================================================== *
 *                                                                       *
 * Dynamic content                                                       *
 *                                                                       *
 * ===================================================================== *
 */

const uint8_t EE_ADDRESS = 0; //EEPROM address to start reading from

const uint8_t MAX_BUTTON_NAME_LENGTH = 10;

uint8_t currentScrollIndex = 0;

struct DynValues {
  bool autoIrrigation;
  uint8_t checkIntvParam;
  uint8_t moistureParam;
};

DynValues dyn_values;

void loadDynamicValues()
{
  uint8_t eeAddress = EE_ADDRESS;

  EEPROM.get(eeAddress, g_lcdml_lang_select);
  eeAddress += sizeof(lang_types); //Move address to the next byte after lang_types 'g_lcdml_lang_select'

  EEPROM.get(eeAddress, dyn_values);
}

void saveDynamicValues()
{
  uint8_t eeAddress = EE_ADDRESS;

  EEPROM.put(eeAddress, g_lcdml_lang_select);
  eeAddress += sizeof(lang_types);

  EEPROM.put(eeAddress, dyn_values);
}

String scrollText(const String &text, uint8_t *scrollPos, const uint8_t &maxLength = _LCDML_DISP_cols)
{
  uint8_t textLength = text.length();
  if (textLength <= maxLength) // Doesn't need to be scrolled
  {
    return text;
  }

  uint8_t endOffset = min(*scrollPos + maxLength, textLength);

  String result = text.substring(*scrollPos, endOffset);

  // Increase scroll count
  *scrollPos = (*scrollPos + 1) % (textLength);

  return result;
}

void mInformation_para(uint8_t line)
{
  String translation = getTranslation("Information");
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    if(LCDML.BT_checkEnter())
    {
      LCDML.OTHER_jumpToFunc(mFunc_information);
    }
    if(LCDML.BT_checkLeft())
    {
      currentScrollIndex = 0;
    }
    if(LCDML.BT_checkRight()) {
      translation = scrollText(translation, &currentScrollIndex, MAX_BUTTON_NAME_LENGTH + 4);
    }
  }

  // display button name
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(translation.substring(0, MAX_BUTTON_NAME_LENGTH + 4));
}

void mAutoIrrigation_para(uint8_t line)
{
  String translation = getTranslation("Auto irrigation");
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    if(LCDML.BT_checkEnter())
    {
      // toggle irrigation
      dyn_values.autoIrrigation = !dyn_values.autoIrrigation;
      saveDynamicValues();
    }

    if(LCDML.BT_checkLeft())
    {
      currentScrollIndex = 0;
    }
    if(LCDML.BT_checkRight()) {
      translation = scrollText(translation, &currentScrollIndex, MAX_BUTTON_NAME_LENGTH);
    }
  }

  // display button name
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(translation.substring(0, MAX_BUTTON_NAME_LENGTH));

  // display dinamic value
  lcd.setCursor(MAX_BUTTON_NAME_LENGTH + 6, (line + _LCDML_DSIP_use_header));
  lcd.print((dyn_values.autoIrrigation ? "ON" : "OFF"));
}

void mMinMoisture_para(uint8_t line)
// *********************************************************************
{
  String translation = getTranslation("Min moisture");
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    if(LCDML.BT_checkEnter())
    {
      // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
      if (LCDML.MENU_getScrollDisableStatus() == 0)
      {
        // disable scrolling
        LCDML.MENU_disScroll();
      } else {
        // enable scrolling and save
        LCDML.MENU_enScroll();
        saveDynamicValues();
      }
    }

    if (LCDML.MENU_getScrollDisableStatus() == 1)
    {
      if(LCDML.BT_checkRight())
      {
        dyn_values.moistureParam++;
      }
      if(LCDML.BT_checkLeft())
      {
        dyn_values.moistureParam--;
      }
    } else {
      if(LCDML.BT_checkLeft())
      {
        currentScrollIndex = 0;
      }
      if(LCDML.BT_checkRight()) {
        translation = scrollText(translation, &currentScrollIndex, MAX_BUTTON_NAME_LENGTH);
      }
    }
  }

  dyn_values.moistureParam = min(dyn_values.moistureParam, 100);

  // display button name
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(translation.substring(0, MAX_BUTTON_NAME_LENGTH));

  // display dinamic value
  lcd.setCursor(MAX_BUTTON_NAME_LENGTH + 2, (line + _LCDML_DSIP_use_header));
  lcd.print("(%) ");
  lcd.print(dyn_values.moistureParam);
}

void mCheckInterval_para(uint8_t line)
// *********************************************************************
{
  String translation = getTranslation("Sample interval");
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    if(LCDML.BT_checkEnter())
    {
      // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
      if (LCDML.MENU_getScrollDisableStatus() == 0)
      {
        // disable scrolling
        LCDML.MENU_disScroll();
      } else {
        // enable scrolling and save
        LCDML.MENU_enScroll();
        saveDynamicValues();
      }
    }

    if (LCDML.MENU_getScrollDisableStatus() == 1)
    {
      if(LCDML.BT_checkRight())
      {
        dyn_values.checkIntvParam++;
      }
      if(LCDML.BT_checkLeft())
      {
        dyn_values.checkIntvParam--;
      }
    } else {
      if(LCDML.BT_checkLeft())
      {
        currentScrollIndex = 0;
      }
      if(LCDML.BT_checkRight()) {
        translation = scrollText(translation, &currentScrollIndex, MAX_BUTTON_NAME_LENGTH);
      }
    }
  }

  dyn_values.checkIntvParam = max(dyn_values.checkIntvParam, 2);

  // display button name
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(translation.substring(0, MAX_BUTTON_NAME_LENGTH));

  // display dinamic value
  lcd.setCursor(MAX_BUTTON_NAME_LENGTH + 2, (line + _LCDML_DSIP_use_header));
  lcd.print("(s) ");
  lcd.print(dyn_values.checkIntvParam);
}
