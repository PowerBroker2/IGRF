#include "IGRF.h"




float lat = 37.7749f;    // San Francisco latitude
float lon = -122.4194f;  // San Francisco longitude




void setup()
{
    Serial.begin(115200);
    while (!Serial) ; // Wait for serial on some boards

    Serial.println(F("---- IGRF LUT Test ----"));

    // Print LUT metadata from header
    Serial.print(F("Date (year/month/day): "));
    Serial.print(IGRF_YEAR);    // If you added YEAR/MONTH/DAY in your header
    Serial.print('/');
    Serial.print(IGRF_MONTH);
    Serial.print('/');
    Serial.println(IGRF_DAY);

    Serial.print(F("Altitude (m): "));
    Serial.println(IGRF_ALTITUDE_M);

    Serial.print(F("Grid resolution (deg): "));
    Serial.println(IGRF_RESOLUTION_DEG);

    Serial.print(F("Number of latitudes: "));
    Serial.println(IGRF_NUM_LATS);

    Serial.print(F("Number of longitudes: "));
    Serial.println(IGRF_NUM_LONS);

    Serial.print(F("Query location: lat = "));
    Serial.print(lat, 6);
    Serial.print(F(", lon = "));
    Serial.println(lon, 6);

    // ---- Compute interpolated values ----
    float decl = igrf_declination(lat, lon);
    float incl = igrf_inclination(lat, lon);
    float Bmag = igrf_Bmag(lat, lon);
    float Bn = igrf_Bn(lat, lon);
    float Be = igrf_Be(lat, lon);
    float Bd = igrf_Bd(lat, lon);

    Serial.println(F("---- Interpolated magnetic field ----"));
    Serial.print(F("Declination (deg): ")); Serial.println(decl, 3);
    Serial.print(F("Inclination (deg): ")); Serial.println(incl, 3);
    Serial.print(F("Magnitude (nT): "));   Serial.println(Bmag, 1);
    Serial.print(F("Bn (nT): "));          Serial.println(Bn, 1);
    Serial.print(F("Be (nT): "));          Serial.println(Be, 1);
    Serial.print(F("Bd (nT): "));          Serial.println(Bd, 1);

    Serial.println(F("-----------------------------"));
}




void loop()
{
    // Nothing to do
}
