/* ===================================================================== *
 *                                                                       *
 * Menu Callback Function                                                *
 *                                                                       *
 * ===================================================================== *
 *
 */

Neotimer moistureCheckTimer = Neotimer();
bool isFirstCheck = true;

uint8_t currentAnimationTick = 0;

// *********************************************************************
void mFunc_information(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function
    lcd.setCursor(0, 0);
    lcd.print(centerText(getTranslation("Irrigation")));
    lcd.setCursor(0, 1);
    lcd.print(centerText(getTranslation("monitoring system")));
    lcd.setCursor(0, 3);
    lcd.print(getTranslation("Version") +  ": 1.0.0");
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if(LCDML.BT_checkAny()) { // check if any button is pressed (enter, up, down, left, right)
      // LCDML_goToMenu stops a running menu function and goes to the menu
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

// *********************************************************************
void mFunc_lang(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function
    g_lcdml_lang_select = param;
    saveDynamicValues();

    LCDML.FUNC_goBackToMenu();
  }
}

// *********************************************************************
void mFunc_defaultScreen(uint8_t param)
// *********************************************************************
{
  // remmove compiler warnings when the param variable is not used:
  LCDML_UNUSED(param);

  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // draw plant pixel art
    drawPlant(0, 1);

    LCDML.FUNC_setLoopInterval(400);  // starts a trigger event for the loop function every 400 milliseconds

    currentAnimationTick = 0;

    // setup moisture check timer
    moistureCheckTimer.set(dyn_values.checkIntvParam * 1000);
    isFirstCheck = true;
  }

  if(LCDML.FUNC_loop())
  {
    // Irrigation animation :D
    currentAnimationTick++;

    lcd.setCursor(1, 0);
    if (currentAnimationTick == 1)
    {
      lcd.print('"');
    } else if (currentAnimationTick == 2)
    {
      lcd.write(B11000010);
    } else if (currentAnimationTick == 3)
    {
      lcd.write(B10101111);

      // reset animation
      currentAnimationTick = 0;
    }

    if(isFirstCheck || moistureCheckTimer.repeat())
    {
      isFirstCheck = false;

      uint8_t moisturePercent = getSoilMoisturePercent();
      if (!isIrrigating && moisturePercent < dyn_values.moistureParam)
      {
        lcd.setCursor(3, 3);
        if (dyn_values.autoIrrigation)
        {
          irrigate();
          // TODO: print "irrigating" text
        } else {
          // TODO: print "pls water me" text
        }
      }

      uint8_t maxTextLength = _LCDML_DISP_cols - 3; //3 = plant pixer art length

      char buf[maxTextLength];
      sprintf(buf, centerText(getTranslation("Moisture: %d%%"), maxTextLength).c_str(), moisturePercent);

      // clear unused chars in the same rows
      String str = String(buf);
      uint8_t spacesCount = maxTextLength - str.length();
      for (int i = 0; i < spacesCount; ++i) {
        str += " ";
      }

      lcd.setCursor(3, 1); //3 = plant pixer art length
      lcd.print(str);
    }

    if (LCDML.BT_checkEnter()) // check if enter button is pressed
    {
      registerAccentedVowels();
      LCDML.FUNC_goBackToMenu();  // leave this function
    }
  }

  if(LCDML.FUNC_close())
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}



// *********************************************************************
void mFunc_back(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1);      // leave this function and go a layer back
  }
}


// *********************************************************************
void mFunc_goToRootMenu(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // go to root and display menu
    LCDML.MENU_goRoot();
  }
}
