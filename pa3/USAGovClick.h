/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * Provides the USAGovClick struct, which represents a single click
 * on 1.usa.gov as specified in http://www.usa.gov/About/developer-resources/1usagov.shtml
 *
 */

#ifndef USAGOVCLICK_H_
#define USAGOVCLICK_H_

#include <stdbool.h>
#include <time.h>

// A single click
typedef struct USAGovClick {

    const char* userAgent;             // "a": USER_AGENT,
    const char* countryCode;           // "c": COUNTRY_CODE, # 2-character iso code
    bool known;                       // "nk": KNOWN_USER,  # 1 or 0. 0=this is the first time we've seen this browser
    const char* globalBitlyHash;       // "g": GLOBAL_BITLY_HASH,
    const char* encodingUserBitlyHash; // "h": ENCODING_USER_BITLY_HASH,
    const char* encodingUserLogin;     // "l": ENCODING_USER_LOGIN,
    const char* shortURLcname;         // "hh": SHORT_URL_CNAME,
    const char* referringURL;          // "r": REFERRING_URL,
    const char* longURL;               // "u": LONG_URL,
    time_t timestamp;                  // "t": TIMESTAMP,
    const char* geoRegion;             // "gr": GEO_REGION,
    float latitude, longitude;        // "ll": [LATITUDE, LONGITUDE],
    const char* geoCityName;           // "cy": GEO_CITY_NAME,
    const char* timezone;              // "tz": TIMEZONE # in http://en.wikipedia.org/wiki/Zoneinfo format
    time_t hashTimestamp;              // "hc": TIMESTAMP OF TIME HASH WAS CREATED,
    const char* acceptLanguage;        // "al": ACCEPT_LANGUAGE http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.4
} USAGovClick;

// Constructor. Takes the JSON representation of the click.
USAGovClick* click_init(char* json);

// Destructor
void click_free(USAGovClick* t);

#endif /* USAGOVCLICK_H_ */
