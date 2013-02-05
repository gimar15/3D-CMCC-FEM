/*canopy transpiration.c*/

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "types.h"
#include "constants.h"


extern void Get_canopy_transpiration (SPECIES *const s,  CELL *const c, const MET_DATA *const met, int month,  int DaysInMonth, float vpd, int height)
{
	Log("\n GET_CANOPY_TRANSPIRATION_ROUTINE \n");

	static float CanCond;
	static float CanopyTranspiration;
	float const e20 = 2.2;          // rate of change of saturated VPD with T at 20C
	float rhoAir;       // density of air, kg/m3
	float const lambda = 2460000;   // latent heat of vapourisation of H2O (J/kg)
	float const VPDconv = 0.000622; // convert VPD to saturation deficit = 18/29/1000
	static float defTerm;
	static float duv;                      // 'div' in 3pg
	static float Etransp;
	static float DailyTransp;
	float alpha_evapo = 0.65;
	float beta_evapo = 0.95;
	//static float MonthTransp;


	//following BIOME
	rhoAir = 1.292 - (0.00428 * met[month].tav);

	//todo move into atmosphere.c
	/*compute air pressure*/
	float t1, t2;

	//todo insert elev in struct site and in site.txt file
	t1 = 1.0 - (LR_STD * 500/*site->elev*/)/T_STD;
	t2 = G_STD / (LR_STD * (R / MA));
	//todo move air_pressure into met file
	c->air_pressure = P_STD * pow (t1, t2);
	//Log("Air pressure = %g Pa\n", c->air_pressure);

	/* temperature and pressure correction factor for conductances */
	c->gcorr = pow((met[month].tav + 273.15)/293.15, 1.75) * 101300/c->air_pressure;
	Log("gcorr = %g\n", c->gcorr);

	/*Canopy Conductance*/

	//Lai is different among layers so CanCond is different
	//Log("Lai for Can Cond = %g\n", s->value[LAI]);

	//todo get maximum stomatal condictance from biome data instead canopy max conductance

	if (settings->version == 's')
	{
		CanCond = s->value[MAXCOND] * s->value[PHYS_MOD] * Minimum(1.0, met[month].ndvi_lai / s->value[LAIGCX]);
		//Log("MAXCOND da biome = %g\n", 0.006 * met[month].ndvi_lai);
		//Log("Cancond biome = %g\n", (0.006 * met[month].ndvi_lai * c->gcorr));
		//Log("CanCond 3PG = %g\n", CanCond);
	}
	else
	{
		CanCond = s->value[MAXCOND] * s->value[PHYS_MOD] * Minimum(1.0, s->value[LAI]  / s->value[LAIGCX]);
		//Log("MAXCOND da biome = %g\n", 0.006 * s->value[LAI]);
		//Log("Cancond biome = %g\n", (0.006 * s->value[LAI] * c->gcorr));
		//Log("CanCond 3PG = %g\n", CanCond);
	}

	//Log("Canopy Conductance  = %g\n", CanCond);

	/*Canopy Transpiration*/
	//todo change all functions with BIOME's

	// Penman-Monteith equation for computing canopy transpiration
	// in kg/m2/day, which is converted to mm/day.
	// The following are constants in the PM formula (Landsberg & Gower, 1997)
	defTerm = rhoAir * lambda * (VPDconv * vpd) * s->value[BLCOND];
	//Log("defTerm = %g\n", defTerm);
	duv = (1.0 + e20 + s->value[BLCOND] / CanCond);
	//Log("duv = %g\n", duv);

	//10 July 2012
	//net radiation should be takes into account of the ALBEDO effect
	//for APAR the ALBEDO is 1/3 as large for PAR because less PAR is reflected than NetRad
	//see Biome-BGC 4.2 tech report


	/*
	Etransp = (e20 * (c->net_radiation * ( 1 - s->value[MAXALB])) + defTerm) / duv;
	Log("Etransp con ALBEDO = %g J/m^2/sec\n", Etransp);
	Log("NET RADIATION with ALBEDO = %g \n", c->net_radiation * (1 - s->value[MAXALB]));
	 */

	switch (c->monthly_layer_number)
	{
	case 1:
		Etransp = (e20 * c->net_radiation + defTerm) / duv;  // in J/m2/s
		Log("Etransp for dominant layer = %g J/m^2/sec\n", Etransp);
		Log("NET RADIATION = %g \n", c->net_radiation);
		break;
	case 2:
		if ( c->heights[height].z == c->top_layer )
		{
			Etransp = (e20 * c->net_radiation + defTerm) / duv;  // in J/m2/s
			Log("Etransp for dominant layer = %g J/m^2/sec\n", Etransp);
			Log("NET RADIATION = %g \n", c->net_radiation);
		}
		else
		{
			Etransp = (e20 * c->net_radiation_for_dominated + defTerm) / duv;  // in J/m2/s
			Log("Etransp for dominant layer = %g J/m^2/sec\n", Etransp);
			Log("NET RADIATION = %g \n", c->net_radiation);
		}
		break;
	case 3:
		if ( c->heights[height].z == c->top_layer )
		{
			Etransp = (e20 * c->net_radiation + defTerm) / duv;  // in J/m2/s
			Log("Etransp for dominant layer = %g J/m^2/sec\n", Etransp);
			Log("NET RADIATION = %g \n", c->net_radiation);
		}
		if ( c->heights[height].z == c->top_layer - 1 )
		{
			Etransp = (e20 * c->net_radiation_for_dominated + defTerm) / duv;  // in J/m2/s
			Log("Etransp for dominant layer = %g J/m^2/sec\n", Etransp);
			Log("NET RADIATION = %g \n", c->net_radiation);
		}
		else
		{
			Etransp = (e20 * c->net_radiation_for_subdominated + defTerm) / duv;  // in J/m2/s
			Log("Etransp for dominant layer = %g J/m^2/sec\n", Etransp);
			Log("NET RADIATION = %g \n", c->net_radiation);
		}

		break;
	}



	CanopyTranspiration = Etransp / lambda * c->daylength;         // converted to kg-mm H2o/m2/day
	//1Kg m^2 H2o correspond to 1mm H2o
	Log("Daily Canopy Transpiration = %g mm-Kg H2o/m^2/day\n", CanopyTranspiration);
	DailyTransp = CanopyTranspiration;
	Log("Daily Transpiration = %g mm/m^2/day\n", DailyTransp);
	//initial transpiration from Penman-Monteith (mm/day converted to mm/month)
	s->value[MONTH_TRANSP] = CanopyTranspiration * DaysInMonth;
	Log("Monthly Canopy Transpiration = %g mm-Kg H2o/m^2/month\n", s->value[MONTH_TRANSP]);

	//5 october 2012 "simplified evapotranspiration modifier" f(E), Angelo Nolè
	//alpha e beta andranno inserite come specie specifiche!!!!
	/*

	s->value[F_EVAPO] = 1 - exp (- alpha_evapo * pow (c->soil_moist_ratio, beta_evapo));
	Log("ANGELO F_EVAPO = %g \n", s->value[F_EVAPO] );


	s->value[MONTH_TRANSP] *= s->value[F_EVAPO];
	Log("ANGELO MonthTransp = %g \n", s->value[MONTH_TRANSP]);
	*/


	//CANOPY TRASPIRATION FOLLOWING BIOME APPROACH
	float tav_k; //Average temperature in Kelvin
	float rr; //resistance to radiative heat transfer through air
	float gl_bl_corr;  //leaf boundary layer conductance corrected for temperature and pressure
	float gl_c_corr; //leaf cuticolar conductance corrected for temperature and pressure
	float ppfd_sun;  //photosynthetic photon flux density (umol/m2/s) PPFD for 1/2 stomatal closure
	float final_ppfd_sun;
	float gl_s_sun;   //maximum stomatal condictance




	/* daily atmospheric pressure (Pa) as a function of elevation (m) */
	/* From the discussion on atmospheric statics in:
	Iribane, J.V., and W.L. Godson, 1981. Atmospheric Thermodynamics, 2nd
		Edition. D. Reidel Publishing Company, Dordrecht, The Netherlands.
		(p. 168)
	*/







	/* leaf boundary-layer conductance */
	gl_bl_corr = s->value[BLCOND]* c->gcorr;
	//Log("gl_bl_corr = %g\n", gl_bl_corr);

	/* leaf cuticular conductance */
	//todo insert CCOND into species.txt
    gl_c_corr = /*s->value[CCOND]*/ 0.00006 * c->gcorr;
    //Log("gl_c_corr = %g\n", gl_c_corr);


	/* leaf stomatal conductance: first generate multipliers, then apply them
	to maximum stomatal conductance */
	/* calculate stomatal conductance radiation multiplier: */


	/* photosynthetic photon flux density  */
	ppfd_sun = s->value[APAR] * EPAR;
	//Log("ppfd_sun = %g\n", ppfd_sun);

	/* photosynthetic photon flux density conductance control */
	ppfd_sun /= (PPFD50 + ppfd_sun);
	//Log("ppfd_sun = %g\n", ppfd_sun);


	/* apply all multipliers to the maximum stomatal conductance */
	//Currently I will use the 3-PG modifiers
	final_ppfd_sun = ppfd_sun * s->value[F_SW] * s->value[F_T] * s->value[F_VPD];
	//Log("final_ppfd_sun = %g\n", final_ppfd_sun);
	gl_s_sun = /*s->value[MAX_STOM_COND]*/ 0.006 * final_ppfd_sun * c->gcorr;
	//Log("gl_s_sun = %g\n", gl_s_sun);

	/* Leaf conductance to evaporated water vapor, per unit projected LAI */
	float gl_e_wv;
	gl_e_wv = gl_bl_corr;
	//Log("gl_e_wv = %g\n", gl_e_wv);



	/* Leaf conductance to transpired water vapor, per unit projected
	LAI.  This formula is derived from stomatal and cuticular conductances
	in parallel with each other, and both in series with leaf boundary
	layer conductance. */
	float gl_t_wv_sun;
	gl_t_wv_sun = (gl_bl_corr * (gl_s_sun))/(gl_bl_corr + gl_s_sun + gl_c_corr);
	//Log("gl_t_wv_sun = %g\n", gl_t_wv_sun);

	/* Leaf conductance to sensible heat, per unit all-sided LAI */
	float gl_sh;
	gl_sh = gl_bl_corr;
	//Log("gl_sh = %g\n", gl_sh);


	float lai;
	if (settings->version == 'u')
	{
		lai = s->value[LAI];
	}
	else
	{
		lai = met[month].ndvi_lai;
	}

	/* Canopy conductance to evaporated water vapor */
	float gc_e_wv;
	gc_e_wv = gl_e_wv * lai;
	//Log("LAI = %g\n", lai);
	//Log("gc_e_wv = %g\n", gc_e_wv);

	/* Canopy conductane to sensible heat */
	float gc_sh;
	gc_sh = gl_sh * lai;
	//Log("gc_sh = %g\n", gc_sh);

	float rv;  //resistance to latent heat transfer
	rv = 1.0/gc_e_wv;
	//Log("rv = %g\n", rv);
	float rh;  //resistance to convective heat transfer
	rh = 1.0/gc_sh;
	//Log("rh = %g\n", rh);
	//todo make a better function using values from light.c
	float swabs; //absorbed shortwave radiation in W/m^2
	swabs = c->net_radiation * (1 -exp (-s->value[K]+lai));
	//Log("swabs = %g\n", swabs);


	/*PENMAN-MONTEITH*/
	/* call penman-monteith function, returns e in kg/m2/s */

	//todo per finire la parte di BIOME devo inserire anche la parte di VPD
	/* assign tav (Celsius) and tav_k (Kelvins) */
	tav_k = met[month].tav + 273.15;

    /* calculate density of air (rho) as a function of air temperature */
	rhoAir = 1.292 - (0.00428 * met[month].tav);

    /* calculate resistance to radiative heat transfer through air, rr */
    rr = rhoAir * CP / (4.0 * SBC * (tav_k*tav_k*tav_k));

    /* calculate combined resistance to convective and radiative heat transfer,
    parallel resistances : rhr = (rh * rr) / (rh + rr) */
    float rhr;
    rhr = (rh * rr) / (rh + rr);

    /* calculate latent heat of vaporization as a function of ta */
    float lhvap;
    lhvap = 2.5023e6 - 2430.54 * met[month].tav;

    /* calculate temperature offsets for slope estimate */
    float dt = 0.2; //set the temperature offset for slope calculation
    t1 = met[month].tav+dt;
    t2 = met[month].tav-dt;


    /* calculate saturation vapor pressures at t1 and t2 */
    float pvs1, pvs2;
    pvs1 = 610.7 * exp(17.38 * t1 / (239.0 + t1));
    pvs2 = 610.7 * exp(17.38 * t2 / (239.0 + t2));

    /* calculate slope of pvs vs. T curve, at ta */
    float esse;
    esse = (pvs1-pvs2) / (t1-t2);

    /* calculate evaporation, in W/m^2  */
    float evap;
    evap = ( ( esse * swabs ) + ( rhoAir * CP * vpd / rhr ) ) /
    	( ( ( c->air_pressure * CP * rv ) / ( lhvap * EPS * rhr ) ) + esse );

    /* covert evaporation into kg/m^2/s */
    evap /= lhvap;

    /* convert evaporation into kg/m^2/day */
    evap *= 84600;
    //Log("Daily transpiration from biome = %g\n", evap);

    /* convert evaporation into kg/m^2/month */
    evap *= met[month].n_days;
    //Log("Montlhy transpiration from biome = %g\n", evap);





















}
