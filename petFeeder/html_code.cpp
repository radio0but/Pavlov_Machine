#include "html_code.h"

String htmlCode = "<html><head><style>"
                  "body { font-family: Tahoma, sans-serif; background-color: black; color: white; display: flex; flex-direction: column; align-items: center; } "
                  ".header { padding: 10px; text-align: center; background-color: #333; color: white; width: 80%;font-size: 2vw; border: 2px solid #73AD21; border-radius: 25px;  } "
                  ".header a {color:white;}" 
                  ".content { display: flex; flex-wrap: wrap; justify-content: space-between; width: 100%; padding: 20px; font-size: 1vw; } "
                  ".column { flex: 1; padding: 20px; width: 90%;border: 2px solid #73AD21; border-radius: 25px;  }"
                  ".column h2 { color: #ddd; }"
                  ".column form { margin-bottom: 20px; }"
                  "input[type='text'], input[type='password'], input[type='submit'], select { padding: 10px; margin: 5px; border: 1px solid #ccc; border-radius: 5px; } "
                  "input[type='submit'] { background-color: #f95300; width: 100%; color: white; cursor: pointer; font-size: 1vw;border: 2px solid #73AD21; border-radius: 25px; } "
                  "input[type='submit']:hover { width: 100%; background-color: #6d2400;font-size: 1.5vw; border: 2px solid #73AD21; border-radius: 25px; } "
                  "input[type='time']{ background-color: #f95300; width: 100%; color: white; cursor: pointer; font-size: 1vw;}"
                  "@media screen and (max-width: 1024px) { .content { flex-direction: column; font-size: 3vw;} .column { width: 100%; } input[type='submit'] {   font-size: 3vw;  } "
                  " input[type='submit']:hover {    font-size: 3.5vw;} input[type='time']{ background-color: #000;  color: white; cursor: pointer; font-size: 6vw;} }"
                  
                  "</style></head>"
                  "<body>"
                  "<div class='header'>"
                  "<a href='/' >"
                  "<h1>Pavlov Machine</h1>"
                  "</a>"
                  "</div>"
                  "<div class='content'>"
                  "<div class='column'>"
                  "<h2>Set Feeding Time</h2>"
                  "<form action='/settime1' method='post'>"
                  "Trigger Time 1: <input type='time' name='feedingTime1'>"
                  "<input type='submit' value='Set'>"
                  "</form>"
                  "<form action='/cleartime' method='post'>"
                  "<input type='hidden' name='feedingTime' value='1'>"
                  "<input type='submit' value='Clear Trigger Time 1'>"
                  "</form>"
                  "<form action='/settime2' method='post'>"
                  "Trigger Time 2: <input type='time' name='feedingTime2'>"
                  "<input type='submit' value='Set'>"
                  "</form>"
                  "<form action='/cleartime' method='post'>"
                  "<input type='hidden' name='feedingTime' value='2'>"
                  "<input type='submit' value='Clear Trigger Time 2'>"
                  "</form>"
                  "<form action='/settime3' method='post'>"
                  "Trigger Time 3: <input type='time' name='feedingTime3'>"
                  "<input type='submit' value='Set'>"
                  "</form>"
                  "<form action='/cleartime' method='post'>"
                  "<input type='hidden' name='feedingTime' value='3'>"
                  "<input type='submit' value='Clear Trigger Time 3'>"
                  "</form>"
                  "<form action='/settime4' method='post'>"
                  "Trigger Time 4: <input type='time' name='feedingTime4'>"
                  "<input type='submit' value='Set'>"
                  "</form>"
                  "<form action='/cleartime' method='post'>"
                  "<input type='hidden' name='feedingTime' value='4'>"
                  "<input type='submit' value='Clear Trigger Time 4'>"
                  "</form>"
                  "</div>"
                  "<div class='column'>"
                  "<h2>Feed</h2>"
                  "<form action='/feed' method='post'>"
                  "<input type='submit' value='Feed'>"
                  "</form>"
                  "<h2>Gate controls</h2>"
                  "<form action='/servo' method='post'>"
                  "<input type='hidden' name='angle' value='0'>"
                  "<input type='submit' value='Close Gate'>"
                  "</form>"
                  "<form action='/servo' method='post'>"
                  "<input type='hidden' name='angle' value='90'>"
                  "<input type='submit' value='Open Gate'>"
                  "</form>"
                  "<h2>Carousel Control</h2>"
                  "<form action='/carousel' method='post'>"
                  "<input type='hidden' name='angle' value='8'>"
                  "<input type='submit' value='1/8 Turn'>"
                  "</form>"
                  "<form action='/carousel' method='post'>"
                  "<input type='hidden' name='angle' value='4'>"
                  "<input type='submit' value='1/4 Turn'>"
                  "</form>"
                  "<form action='/carousel' method='post'>"
                  "<input type='hidden' name='angle' value='2'>"
                  "<input type='submit' value='1/2 Turn'>"
                  "</form>"
                  "<form action='/carousel' method='post'>"
                  "<input type='hidden' name='angle' value='1'>"
                  "<input type='submit' value='1 Turn'>"
                  "</form>"
                  "</div>"
                  "<div class='column'>"
                  "<h2>Configurations</h2>"
                    
                  
                  "<h3>Configure your WiFi settings.</h3>"
                  "<form action='/save' method='post'>"
                  "SSID    : <input type='text' name='ssid'><br>"
                  "Password: <input type='password' name='password'><br>"
                  "<input type='submit' value='Save'>"
                  "</form><br>"
                  "<h3>Time Configurations</h3>"
                  "<form action='/settimezone' method='post'>"
                 "Select Timezone: <select name='timezone'>"
                  "<option value='-12'>GMT -12:00</option>"
                  "<option value='-11'>GMT -11:00</option>"
                  "<option value='-10'>GMT -10:00</option>"
                  "<option value='-9'>GMT -9:00</option>"
                  "<option value='-8'>GMT -8:00</option>"
                  "<option value='-7'>GMT -7:00</option>"
                  "<option value='-6'>GMT -6:00</option>"
                  "<option value='-5'>GMT -5:00</option>"
                  "<option value='-4'>GMT -4:00</option>"
                  "<option value='-3'>GMT -3:00</option>"
                  "<option value='-2'>GMT -2:00</option>"
                  "<option value='-1'>GMT -1:00</option>"
                  "<option value='0'>GMT +0:00</option>"
                  "<option value='1'>GMT +1:00</option>"
                  "<option value='2'>GMT +2:00</option>"
                  "<option value='3'>GMT +3:00</option>"
                  "<option value='4'>GMT +4:00</option>"
                  "<option value='5'>GMT +5:00</option>"
                  "<option value='6'>GMT +6:00</option>"
                  "<option value='7'>GMT +7:00</option>"
                  "<option value='8'>GMT +8:00</option>"
                  "<option value='9'>GMT +9:00</option>"
                  "<option value='10'>GMT +10:00</option>"
                  "<option value='11'>GMT +11:00</option>"
                  "<option value='12'>GMT +12:00</option>"
                  "<!-- Add more timezone options here -->"
                  "</select>"
                  "<br> Select NTP Server: <select name='ntpServer'>"
                  "<option value='pool.ntp.org'>pool.ntp.org</option>"
                  "<option value='time.google.com'>time.google.com</option>"
                  "<option value='time.windows.com'>time.windows.com</option>"
                  "<option value='time.apple.com'>time.apple.com</option>"
                  "<option value='time.nist.gov'>time.nist.gov</option>"
                  "<option value='time.cloudflare.com'>time.cloudflare.com</option>"
                  "<!-- Add more NTP server options here -->"
                  "</select>"

                  "<input type='submit' value='Set Timezone and NTP Server'>"
                  "</form>"

                  "<h2>Motors Settings</h2>"
                  "<form action='/setstepper' method='post'>"
                  "Steps per Rotation: <input type='number' name='stepsPerRotation' value='2048' min='1'>"
                  "<input type='submit' value='Set'>"
                   "</form>"
                  
                  "<h2>Theme Configuration</h2>"
                  "<form action='/configtheme' method='post'>"
                  "Button Color: <input type='color' name='buttonColor' value='#f95300'><br>"
                  "Background Color: <input type='color' name='bgColor' value='#000000'><br>"
                  "Text Color: <input type='color' name='textColor' value='#ffffff'><br>"
                  "Border Color: <input type='color' name='borderColor' value='#73AD21'><br>"
                  "Header Background Color: <input type='color' name='headerBgColor' value='#333'><br>"
                  "Header Text Size: <input type='number' name='headerTextSize' value='2'><br>"
                  "Button Text Size: <input type='number' name='buttonTextSize' value='1'><br>"
                  "Border Size: <input type='number' name='borderSize' value='2'><br>"
                  "Border Radius: <input type='number' name='borderRadius' value='25'><br>"
                  "<input type='submit' value='Apply Theme'>"
                  "</form>"


                  "<h3>Image Setting</h3>"
                  "<form action='/setheaderimage' method='post'>"
                  "Header Image URL: <input type='text' name='headerImageUrl'><br>"
                  "<input type='submit' value='Set Header Image'>"
                  "</form>"
                  "<h2>System</h2>" 
                          "<form action='/reboot' method='post'>" 
                          "<input type='submit' value='Reboot'>" 
                          "</form>" 
                  
                  "</div>"
                  "</div>"
                  "</body></html>";


String modifiedHtmlCode;

String feedingTime1, feedingTime2, feedingTime3, feedingTime4;
String headerImageUrl;
int stepsPerRotation;
void modifyHtml(Preferences& preferences) {
    // Fetch stored trigger times from preferences
    feedingTime1 = preferences.getString("feedingTime1", "");
    feedingTime2 = preferences.getString("feedingTime2", "");
    feedingTime3 = preferences.getString("feedingTime3", "");
    feedingTime4 = preferences.getString("feedingTime4", "");
    // Fetch stored colors from preferences
    String ibuttonColor = preferences.getString("buttonColor", "#f95300");
    String ibgColor = preferences.getString("bgColor", "black");
    String itextColor = preferences.getString("textColor", "white");
    String iborderColor = preferences.getString("borderColor", "#73AD21");
    String iheaderBgColor = preferences.getString("headerBgColor", "#333");
    int iborderRadius = preferences.getInt("borderRadius", 25);
    int iheaderTextSize = preferences.getInt("headerTextSize", 2);
    int ibuttonTextSize = preferences.getInt("buttonTextSize", 1);
    int iborderSize = preferences.getInt("borderSize", 2);
    headerImageUrl = preferences.getString("headerImageUrl", "");
    stepsPerRotation = preferences.getInt("stepsPerRotation", 2048);


   String modifiedCSS = "<style>"
                         "body { font-family: Tahoma, sans-serif; background-color: " + ibgColor + "; color: " + itextColor + "; display: flex; flex-direction: column; align-items: center; } "
                         ".header { padding: 10px; text-align: center; background-color: " + iheaderBgColor + "; color: white; width: 80%;font-size: " + String(iheaderTextSize) + "vw; border: " + String(iborderSize) + "px solid " + iborderColor + "; border-radius: " + String(iborderRadius) + "px;  } "
                         ".header a {color:white;}" 
                         ".content { display: flex; flex-wrap: wrap; justify-content: space-between; width: 100%; padding: 20px; font-size: 1vw; } "
                         ".column { flex: 1; padding: 20px; width: 90%;border: " + String(iborderSize) + "px solid " + iborderColor + "; border-radius: " + String(iborderRadius) + "px;  }"
                         ".column h2 { color: #ddd; }"
                         ".column form { margin-bottom: 20px; }"
                         "input[type='text'], input[type='password'], input[type='submit'], select { padding: 10px; margin: 5px; border: 1px solid #ccc; border-radius: 5px; } "
                         "input[type='submit'] { background-color: " + ibuttonColor + "; width: 100%; color: white; cursor: pointer; font-size: " + ibuttonTextSize + "vw;border: " + String(iborderSize) + "px solid " + iborderColor + "; border-radius: " + String(iborderRadius) + "px; } "
                         "input[type='submit']:hover { width: 100%; background-color: " + ibuttonColor + ";font-size: 1.5vw; border: 2px solid #73AD21; border-radius: " + String(iborderRadius) + "px; } "
                         "input[type='time']{ background-color: " + ibgColor + "; width: 100%; color: " + itextColor + "; cursor: pointer; font-size: 1vw;}"
                         "@media screen and (max-width: 1024px) { .content { flex-direction: column; font-size: 3vw;} .column { width: 100%; } input[type='submit'] {   font-size: 3vw;  } "
                         " input[type='submit']:hover {    font-size: 3.5vw;} input[type='time']{ background-color: #000;  color: white; cursor: pointer; font-size: 6vw;} }"
                         "</style>";

String originalCSS = "<style>"
                     "body { font-family: Tahoma, sans-serif; background-color: black; color: white; display: flex; flex-direction: column; align-items: center; } "
                     ".header { padding: 10px; text-align: center; background-color: #333; color: white; width: 80%;font-size: 2vw; border: 2px solid #73AD21; border-radius: 25px;  } "
                     ".header a {color:white;}" 
                     ".content { display: flex; flex-wrap: wrap; justify-content: space-between; width: 100%; padding: 20px; font-size: 1vw; } "
                     ".column { flex: 1; padding: 20px; width: 90%;border: 2px solid #73AD21; border-radius: 25px;  }"
                     ".column h2 { color: #ddd; }"
                     ".column form { margin-bottom: 20px; }"
                     "input[type='text'], input[type='password'], input[type='submit'], select { padding: 10px; margin: 5px; border: 1px solid #ccc; border-radius: 5px; } "
                     "input[type='submit'] { background-color: #f95300; width: 100%; color: white; cursor: pointer; font-size: 1vw;border: 2px solid #73AD21; border-radius: 25px; } "
                     "input[type='submit']:hover { width: 100%; background-color: #6d2400;font-size: 1.5vw; border: 2px solid #73AD21; border-radius: 25px; } "
                     "input[type='time']{ background-color: #f95300; width: 100%; color: white; cursor: pointer; font-size: 1vw;}"
                     "@media screen and (max-width: 1024px) { .content { flex-direction: column; font-size: 3vw;} .column { width: 100%; } input[type='submit'] {   font-size: 3vw;  } "
                     " input[type='submit']:hover {    font-size: 3.5vw;} input[type='time']{ background-color: #000;  color: white; cursor: pointer; font-size: 6vw;} }"
                     "</style>";

                     
     // Inject the stored steps per rotation into the HTML string
    modifiedHtmlCode.replace("name='stepsPerRotation'>", "name='stepsPerRotation' value='" + String(stepsPerRotation) + "'>");

    String headerBgColor = preferences.getString("headerBgColor", "#333");
    int headerTextSize = preferences.getInt("headerTextSize", 2);
    int buttonTextSize = preferences.getInt("buttonTextSize", 1);
    int borderSize = preferences.getInt("borderSize", 2);
    // Inject the stored trigger times into the HTML string
    modifiedHtmlCode = htmlCode;
    modifiedHtmlCode.replace("name='feedingTime1'>", "name='feedingTime1' value='" + feedingTime1 + "'>");
    modifiedHtmlCode.replace("name='feedingTime2'>", "name='feedingTime2' value='" + feedingTime2 + "'>");
    modifiedHtmlCode.replace("name='feedingTime3'>", "name='feedingTime3' value='" + feedingTime3 + "'>");
    modifiedHtmlCode.replace("name='feedingTime4'>", "name='feedingTime4' value='" + feedingTime4 + "'>");
    modifiedHtmlCode.replace(originalCSS, modifiedCSS);
 

    // Inject the stored header image URL into the HTML string
    modifiedHtmlCode.replace("<a href='/' >", "<a href='/' >");
    if (headerImageUrl != "") {
        modifiedHtmlCode.replace("<h2>Set Feeding Time</h2>", "<img src='" + headerImageUrl + "' alt='Header Image' style='width:100%;'></div><div class='column'><h2>Set Feeding Time</h2>");
    } else {
        modifiedHtmlCode.replace("<h2>Set Feeding Time</h2>", "<h2>Set Feeding Time</h2>");
    }
}
