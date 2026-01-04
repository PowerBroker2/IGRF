#pragma once
#include "Arduino.h"
#include "ArduHelpers.h"
#include "IGRF_LUTs.h"

// ---- Grid boundaries ----
#define IGRF_LAT_MIN (IGRF_LATS[0])
#define IGRF_LAT_MAX (IGRF_LATS[IGRF_NUM_LATS - 1])
#define IGRF_LON_MIN (IGRF_LONS[0])
#define IGRF_LON_MAX (IGRF_LONS[IGRF_NUM_LONS - 1])

// ---- Bilinear interpolator ----
static inline float igrf_bilinear_interp(float lat_deg,
                                         float lon_deg,
                                         const float table[IGRF_NUM_LATS][IGRF_NUM_LONS])
{
    // ---- Clamp latitude ----
    if (lat_deg < IGRF_LATS[0]) {
        lat_deg = IGRF_LATS[0];
    } else if (lat_deg > IGRF_LATS[IGRF_NUM_LATS - 1]) {
        lat_deg = IGRF_LATS[IGRF_NUM_LATS - 1];
    }

    // ---- Wrap longitude ----
    const float lon_span = IGRF_LONS[IGRF_NUM_LONS - 1] - IGRF_LONS[0];

    if (lon_deg < IGRF_LONS[0]) {
        lon_deg += lon_span;
    } else if (lon_deg > IGRF_LONS[IGRF_NUM_LONS - 1]) {
        lon_deg -= lon_span;
    }

    // ---- Grid coordinates ----
    const float inv_res = 1.0f / IGRF_RESOLUTION_DEG;

    float lat_idx = (lat_deg - IGRF_LATS[0]) * inv_res;
    float lon_idx = (lon_deg - IGRF_LONS[0]) * inv_res;

    int lat0 = (int)lat_idx;
    int lon0 = (int)lon_idx;

    // ---- Safety clamp ----
    if (lat0 >= IGRF_NUM_LATS - 1) lat0 = IGRF_NUM_LATS - 2;
    if (lon0 >= IGRF_NUM_LONS - 1) lon0 = IGRF_NUM_LONS - 2;

    float lat_f = lat_idx - lat0;
    float lon_f = lon_idx - lon0;

    const float one_minus_lat = 1.0f - lat_f;
    const float one_minus_lon = 1.0f - lon_f;

    const float v00 = table[lat0][lon0];
    const float v10 = table[lat0 + 1][lon0];
    const float v01 = table[lat0][lon0 + 1];
    const float v11 = table[lat0 + 1][lon0 + 1];

    return
        v00 * one_minus_lat * one_minus_lon +
        v10 * lat_f          * one_minus_lon +
        v01 * one_minus_lat * lon_f +
        v11 * lat_f          * lon_f;
}

// ---- Wrapper functions ----
static inline float igrf_declination(float lat, float lon)
{
    return igrf_bilinear_interp(lat, lon, IGRF_DECLINATION_DEG);
}

static inline float igrf_inclination(float lat, float lon)
{
    return igrf_bilinear_interp(lat, lon, IGRF_INCLINATION_DEG);
}

static inline float igrf_Bn(float lat, float lon)
{
    return igrf_bilinear_interp(lat, lon, IGRF_BN);
}

static inline float igrf_Be(float lat, float lon)
{
    return igrf_bilinear_interp(lat, lon, IGRF_BE);
}

static inline float igrf_Bd(float lat, float lon)
{
    return igrf_bilinear_interp(lat, lon, IGRF_BD);
}

static inline float igrf_Bmag(float lat, float lon)
{
    return igrf_bilinear_interp(lat, lon, IGRF_BMAG);
}
