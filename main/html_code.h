#ifndef HTML_CODE_H
#define HTML_CODE_H

#include <Arduino.h>
#include <Preferences.h>

extern String htmlCode;
extern String modifiedHtmlCode;
extern String feedingTime1, feedingTime2, feedingTime3, feedingTime4;
extern String headerImageUrl;

void modifyHtml(Preferences& preferences);

#endif
