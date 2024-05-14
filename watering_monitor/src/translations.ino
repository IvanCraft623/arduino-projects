String getTranslation(String raw)
{

  switch(g_lcdml_lang_select)
  {
    case LANG_ES:
      if (raw == "Menu") {
        return "Men\5";
      } else if (raw == "Information") {
        return "Informaci\4n";
      } else if (raw == "Irrigation") {
        return "Sistema de monitoreo";
      } else if (raw == "monitoring system") {
        return "de riego";
      } else if (raw == "Moisture: %d%%") {
        return "Humedad: %d%%";
      } else if (raw == "Auto irrigation") {
        return "Riego autom\1tico";
      } else if (raw == "Min moisture") {
        return "Humedad m\3nima";
      } else if (raw == "Sample interval") {
        return "Intervalo de muestreo";
      } else if (raw == "Version") {
        return "Versi\4n";
      } else {
        return raw;
      }
    break;

    case LANG_MAY:
      if (raw == "Menu") {
        return "Ch\5unul";
      } else if (raw == "Information") {
        return "Ba'ax u ts'abal ojetbil";
      } else if (raw == "Irrigation") {
        return "Bixil u p'iisbal bix";
      } else if (raw == "monitoring system") {
        return "u j\4oyalta'a p\1ak'al";
      } else if (raw == "Moisture: %d%%") {
        return "U ja'il: %d%%";
      } else if (raw == "Auto irrigation") {
        return "U j\4oyaltikuba'a tu juunaj";
      } else if (raw == "Min moisture") {
        return "U x\5upulil u ja'il";
      } else if (raw == "Sample interval") {
        return "U s\5utukil u p'iisbal ka u ye\2saj";
      } else if (raw == "Version") {
        return "M\1akalm\1aki'";
      } else {
        return raw;
      }
    break;

    default: // default language
      return raw;
    break;
  }
}
