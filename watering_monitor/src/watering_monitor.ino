// *********************************************************************
// includes
// *********************************************************************
  #include <LCD_I2C.h>
  #include <LCDMenuLib2.h>
  #include <neotimer.h>

// *********************************************************************
// Irrigation settings
// *********************************************************************
  #define _IRRIGARION_seconds   3

// *********************************************************************
// Relay settings
// *********************************************************************
  #define _RELAY_pin   3

// *********************************************************************
// Moisture sensor settings
// *********************************************************************
  #define _MOISTURE_SENSOR_pin   A0
  #define _MOISTURE_water_value  250
  #define _MOISTURE_air_value    590

// *********************************************************************
// LCDML display settings
// *********************************************************************
  // settings for LCD
  #define _LCDML_DISP_cols  20
  #define _LCDML_DISP_rows  4

  // enable this line (set to 1) to show a header above the first menu element
  // this function can be changed in LCDML_display_menu tab
  #define _LCDML_DSIP_use_header 1

  #define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol
  #define _LCDML_DISP_cfg_scrollbar                  0      // enable a scrollbar

  // LCD object
  LCD_I2C lcd(0x27, _LCDML_DISP_cols, _LCDML_DISP_rows);

// *********************************************************************
// Prototypes
// *********************************************************************
  void lcdml_menu_display();
  void lcdml_menu_clear();
  void lcdml_menu_control();

// *********************************************************************
// Objects
// *********************************************************************
  LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element (do not change)
  LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows-_LCDML_DSIP_use_header, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// Create language types
// *********************************************************************
  enum lang_types
  {
    LANG_EN  = 0,
    LANG_ES  = 1,
    LANG_MAY = 2
  };

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // LCDML_0        => layer 0
  // LCDML_0_X      => layer 1
  // LCDML_0_X_X    => layer 2
  // LCDML_0_X_X_X  => layer 3
  // LCDML_0_...      => layer ...

  LCDML_addAdvanced (0  , LCDML_0         , 1  , NULL,         ""        , mInformation_para,      0,   _LCDML_TYPE_dynParam);
  LCDML_langDef     (0  , ES,  "");
  LCDML_langDef     (0  , MAY, "");


  //Language configuration
  LCDML_addAdvanced (1 , LCDML_0         , 2  , NULL,          "Language"     , NULL,             0,            _LCDML_TYPE_default);
  LCDML_langDef     (1 , ES,  "Idioma");
  LCDML_langDef     (1 , MAY, "U T'aanil");

  LCDML_addAdvanced (2 , LCDML_0_2       , 1  , NULL,          "English"      , mFunc_lang,       LANG_EN,      _LCDML_TYPE_default);
  LCDML_langDef     (2 , ES,  "English");
  LCDML_langDef     (2 , MAY, "English");

  LCDML_addAdvanced (3 , LCDML_0_2       , 2  , NULL,          "Espa\xEEol"   , mFunc_lang,       LANG_ES,      _LCDML_TYPE_default);
  LCDML_langDef     (3 , ES,     "Espa\xEEol");
  LCDML_langDef     (3 , MAY,    "Espa\xEEol");

  LCDML_addAdvanced (4 , LCDML_0_2       , 3  , NULL,          "Maaya t'aan"  , mFunc_lang,       LANG_MAY,      _LCDML_TYPE_default);
  LCDML_langDef     (4 , ES,     "Maaya t'aan");
  LCDML_langDef     (4 , MAY,    "Maaya t'aan");

  // LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)
  LCDML_add         (5 , LCDML_0_2       , 4  , "Back"             , mFunc_back);              // this menu function can be found on "display_menuFunction" tab
  LCDML_langDef     (5, ES,  "Volver");
  LCDML_langDef     (5, MAY, "U Suutnalil");

  // Example for dynamic content
  // 1. set the string to ""
  // 2. use type  _LCDML_TYPE_dynParam   instead of    _LCDML_TYPE_default
  // this function type can not be used in combination with different parameters
  // LCDMenuLib_addAdvanced(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
  LCDML_addAdvanced (6 , LCDML_0         , 3  , NULL,          ""        , mAutoIrrigation_para,       0,   _LCDML_TYPE_dynParam);
  LCDML_langDef     (6 , ES,     "");
  LCDML_langDef     (6 , MAY,    "");
  
  LCDML_addAdvanced (7 , LCDML_0         , 4  , NULL,          ""        , mMinMoisture_para,          0,   _LCDML_TYPE_dynParam);
  LCDML_langDef     (7 , ES,     "");
  LCDML_langDef     (7 , MAY,    "");
  
  LCDML_addAdvanced (8 , LCDML_0         , 5  , NULL,          ""        , mCheckInterval_para,        0,   _LCDML_TYPE_dynParam);
  LCDML_langDef     (8 , ES,     "");
  LCDML_langDef     (8 , MAY,    "");

  // Example for conditions (for example for a screensaver)
  // 1. define a condition as a function of a boolean type -> return false = not displayed, return true = displayed
  // 2. set the function name as callback (remove the braces '()' it gives bad errors)
  // LCDMenuLib_addAdvanced(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
  LCDML_addAdvanced (9 , LCDML_0         , 7  , NULL,       "Exit"      , mFunc_defaultScreen,        0,   _LCDML_TYPE_default);       // this menu function can be found on "LCDML_display_menuFunction" tab
  LCDML_langDef     (9 , ES,     "Salir");
  LCDML_langDef     (9 , MAY,    "U J\x4ok'olil");
  LCDML_addAdvanced (10 , LCDML_0        , 8  , COND_hide,  "XD"      , mFunc_information,        0,   _LCDML_TYPE_default);       // this menu function can be found on "LCDML_display_menuFunction" tab
  LCDML_langDef     (10 , ES,  "");
  LCDML_langDef     (10 , MAY, "");

  // ***TIP*** Try to update _LCDML_DISP_cnt when you add a menu element.
 
  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    10

  // irrigation
  Neotimer irrigationTimer = Neotimer(_IRRIGARION_seconds * 1000);
  bool isIrrigating = false;

  // create menu
  LCDML_createMenu(_LCDML_DISP_cnt);

  // set the default language with the long name
  //lang_types g_lcdml_lang_select = LANG_EN;
  lang_types g_lcdml_lang_select = LANG_ES;

  // create custom language with short name, not with the long name   
  LCDML_createCustomLang(_LCDML_DISP_cnt, ES);
  LCDML_createCustomLang(_LCDML_DISP_cnt, MAY);

  // next step when you add a new language:
  // go into the display_menu tab and change or add a switch case condition

  // next step:
  // change the menu function 

  // *********************************************************************
  // SETUP
  // *********************************************************************
  void setup() {
    // serial init; only be needed if serial control is used
    Serial.begin(9600);                // start serial
    Serial.println(F(_LCDML_VERSION)); // only for examples

    // relay pin init
    pinMode(_RELAY_pin, OUTPUT);
    setRelayActivated(false);

    loadDynamicValues();

    // lcd init
    lcd.begin();
    lcd.backlight();

    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Some settings which can be used

    // Enable Menu Rollover
    //LCDML.MENU_enRollover();

    // Enable Screensaver (screensaver menu function, time to activate in ms)
    LCDML.SCREEN_enable(mFunc_defaultScreen, 15000); // set to 15 seconds

    // Some needful methods

    LCDML.SCREEN_start();
  }

  void loop() {
    LCDML.loop();

    if (isIrrigating && irrigationTimer.done())
    {
      isIrrigating = false;
      setRelayActivated(false);
      Serial.println("Relay off");

      irrigationTimer.reset();
    }
  }

  void irrigate() {
    isIrrigating = true;
    setRelayActivated(true);
    Serial.println("Relay on");

    irrigationTimer.start();
  }

  void setRelayActivated(bool value) {
    digitalWrite(_RELAY_pin, value ? LOW : HIGH); // my relay activation signal is inverted :P
  }

  uint8_t getSoilMoisturePercent() {
    return min(max(map(analogRead(_MOISTURE_SENSOR_pin), _MOISTURE_air_value, _MOISTURE_water_value, 0, 100), 0), 100);
  }
