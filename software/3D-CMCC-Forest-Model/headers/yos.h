/* yos.h */
#ifndef YOS_H_
#define YOS_H_

#define YOS_MONTHS_COUNT	12
#define YOS_DAYS_COUNT		31

typedef struct {
	int n_days;
	double solar_rad;                           /* (MJ/m2/day) incoming short wave radiation */
	double tavg;                                /* (deg C) daily average air temperature */
	double tmax;                                /* (deg C) daily maximum air temperature */
	double tmin;                                /* (deg C) daily minimum air temperature */
	double tday;                                /* (deg C) daylight  daily air temperature */
	double tnight;                              /* (deg C) nightime average daily air temperature */
	double tdew;                                /* (deg C) daily dew average daily air temperature */
	double vpd;                                 /* (hPa-mbar) daily vapour pressure dificit */
	double rh_f;                                /* (%) daily relative humidity */
	double ts_f;                                /* (deg C) daily soil temperature from data file */
	double prcp;                                /* (mm) daily precipitation */
	double swc;                                 /* (% vol) daily soil wtaer content from data file */
	double ndvi_lai;                            /* (m2/m2) daily LAI from data file */
	double daylength;                           /* (hours) day length */
	double ni;                                  /* (ratio) fraction of day length */
	double thermic_sum;                         /* (deg C) daily thermic sum */
	double rho_air;                             /* (kg/m3) daily air density */
	double tsoil;                               /* (deg C) daily soil temperature computed by the model */
	double et;                                  /* (mm) daily evapo-transpiration (not used)*/
	double windspeed;                           /* (m/sec) daily wind speed */
	double lh_vap;                              /* (J/Kg) daily latent heat of vaporization trees */
	double lh_vap_soil;                         /* (J/Kg) daily latent heat of vaporization soil */
	double lh_fus;                              /* (KJ/Kg) daily latent heat of fusion snow */
	double lh_sub;                              /* (KJ/Kg) daily latent heat of sublimation snow */
	double air_pressure;                        /* (Pa) daily air pressure */
	double co2_conc;                            /* (ppmv) daily CO2 concentration */
	double es;                                  /* (KPa) daily weighted mean saturation vapour pressure at the air temperature */
	double ea;                                  /* (KPa) daily actual vapour pressure derived from relative humidity data */
	double psych;                               /* (KPa/°C) daily psychrometric constant */
	double sw_pot_downward_W;                   /* (W/m2) potential shortwave downward radiation */
	double sw_downward_MJ;                      /* (MJ/m2/day) daily downward short wave radiation */
	double sw_downward_W;                       /* (W/m2) daily downward short wave radiation */
	double lw_downward_MJ;                      /* (MJ/m2/day) daily downward long wave radiation */
	double lw_downward_W;                       /* (W/m2) daily downward long wave radiation */
	double lw_net_MJ;                           /* (MJ/m2/day) daily net long wave radiation */
	double lw_net_W;                            /* (W/m2) daily net long wave radiation */
	double par;                                 /* (molPAR/m2/day) incoming PAR */
	double ppfd;                                /* (umol/m2/sec) incoming PPFD */
	double cloud_cover_frac;                    /* (ratio) daily cloud cover fraction */
} meteo_daily_t;

typedef struct {
	meteo_daily_t d[YOS_DAYS_COUNT];
} meteo_t;

typedef struct {
	int year;
	meteo_t m[YOS_MONTHS_COUNT];
} yos_t; /* just for clarification YOS stand for Year Of Simulation ! */

yos_t* yos_import(const char *const file, int *const yos_count, const int x, const int y);

#endif /* YOS_H_ */
