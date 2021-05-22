/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * Provides the USAGovClick struct, which represents a single click
 * on 1.usa.gov as specified in http://www.usa.gov/About/developer-resources/1usagov.shtml
 *
 * See USAGovClick.h for details.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <json/json.h>
#include "USAGovClick.h"

USAGovClick* click_init(char* json) {
    USAGovClick* t = (USAGovClick*)malloc(sizeof(USAGovClick));
    
	// Create a JSON reader
	Json::Reader reader;
	Json::Value root;

	// Parse the JSON
	if (!reader.parse(json, root))
	{
        fprintf(stderr, "unable to parse JSON\n");
        exit(1);
	}

	// The 1.usa.gov stream sometimes returns heartbeat messages.
	// We can filter them simply by checking whether any of the
	// attributes is present (arbitrarily, we choose "a")
    if (!root.isMember("a")) {
		fprintf(stderr, "JSON Does not have 'a'");
        exit(1);
    }

	// Retrieve the values from the click JSON object
    t->userAgent = strdup(root.get("a", Json::Value::null).asString().c_str());
    t->countryCode = strdup(root.get("c", Json::Value::null).asString().c_str());
    t->known = root.get("nk", Json::Value::null).asBool();
    t->globalBitlyHash = strdup(root.get("g", Json::Value::null).asString().c_str());
    t->encodingUserBitlyHash = strdup(root.get("h", Json::Value::null).asString().c_str());
    t->encodingUserLogin = strdup(root.get("l", Json::Value::null).asString().c_str());
    t->shortURLcname = strdup(root.get("hh", Json::Value::null).asString().c_str());
    t->referringURL = strdup(root.get("r", Json::Value::null).asString().c_str());
    t->longURL = strdup(root.get("u", Json::Value::null).asString().c_str());
    t->timestamp = root.get("t", Json::Value::null).asLargestUInt();
    t->geoRegion = strdup(root.get("gr", Json::Value::null).asString().c_str());
    t->latitude = root.get("ll", Json::Value::null)[0].asFloat();
    t->longitude = root.get("ll", Json::Value::null)[1].asFloat();
    t->geoCityName = strdup(root.get("cy", Json::Value::null).asString().c_str());
    t->timezone = strdup(root.get("tz", Json::Value::null).asString().c_str());
    t->hashTimestamp = root.get("hc", Json::Value::null).asLargestUInt();
    t->acceptLanguage = strdup(root.get("al", Json::Value::null).asString().c_str());
    
    return t;
}

void nnfree(const char* p) {
    if (p) {
        free((void*)p);
    }
}

void click_free(USAGovClick* t) {
    nnfree(t->userAgent);
    nnfree(t->countryCode);
    nnfree(t->globalBitlyHash);
    nnfree(t->encodingUserBitlyHash);
    nnfree(t->encodingUserLogin);
    nnfree(t->shortURLcname);
    nnfree(t->referringURL);
    nnfree(t->longURL);
    nnfree(t->geoRegion);
    nnfree(t->geoCityName);
    nnfree(t->timezone);
    nnfree(t->acceptLanguage);
    free(t);
}
