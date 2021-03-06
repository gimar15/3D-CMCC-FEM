/*modifiers.c*/

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "types.h"
#include "constants.h"

void Get_modifiers (SPECIES *const s,  AGE *const a, CELL *const c, const MET_DATA *const met, int year,  int month, int daysinmonth, float available_soil_water, float vpd,  int z, int management )
{
	float RelAge;

	float vwc; //soil volumetric water content
	float psi;  //soil matric potential



	Log("\n GET_MODIFIERS\n\n");

	/*TEMPERATURE MODIFIER*/

	Log("--Temperature Average %g °C\n", met[month].tavg);
	Log("--Daylight Average Temperature  %g °C\n", met[month].tday);
	//Log("--Optimum temperature for species %s = %g °C\n", s->name, s->value[GROWTHTOPT]);
	//Log("--Maximum temperature for species %s = %g °C\n", s->name, s->value[GROWTHTMAX]);
	//Log("--Minimum temperature for species %s = %g °C\n", s->name, s->value[GROWTHTMIN]);

	if (met[month].tday == NO_DATA)
	{
		if ((met[month].tavg <= s->value[GROWTHTMIN]) || (met[month].tavg >= s->value[GROWTHTMAX]))
		{
			s->value[F_T] = 0;
			Log("F_T = 0 \n");
		}
		else
		{
			s->value[F_T] = ((met[month].tavg - s->value[GROWTHTMIN]) / (s->value[GROWTHTOPT] - s->value[GROWTHTMIN])) * pow(((s->value[GROWTHTMAX] - met[month].tday) / (s->value[GROWTHTMAX] - s->value[GROWTHTOPT])),
					((s->value[GROWTHTMAX] - s->value[GROWTHTOPT]) / (s->value[GROWTHTOPT] - s->value[GROWTHTMIN])));
		}
	}
	else
	{
		if ((met[month].tday <= s->value[GROWTHTMIN]) || (met[month].tday >= s->value[GROWTHTMAX]))
		{
			s->value[F_T] = 0;
			Log("F_T = 0 \n");
		}
		else
		{
			s->value[F_T] = ((met[month].tday - s->value[GROWTHTMIN]) / (s->value[GROWTHTOPT] - s->value[GROWTHTMIN])) * pow(((s->value[GROWTHTMAX] - met[month].tday) / (s->value[GROWTHTMAX] - s->value[GROWTHTOPT])),
					((s->value[GROWTHTMAX] - s->value[GROWTHTOPT]) / (s->value[GROWTHTOPT] - s->value[GROWTHTMIN])));
		}
	}
	Log("fT - Temperature Modifier = %g\n", s->value[F_T]);

	if (s->value[F_T] > 1)
	{
		Log("ATTENTION fT EXCEEDS 1 \n");
		s->value[F_T] = 1;
	}


	//average yearly f_vpd modifiers
	s->value[AVERAGE_F_T] += s->value[F_T];



	/*FROST MODIFIER*/

	//I dati di Rocca non hanno i giorni di gelo!!!!!!!!!!!!!!!!!!!!!!!!
	//Log("Frost Days = %g\n", met[month].frostdays);
	//s->value[F_FROST] = ( 1 - (met[month].frostdays / (float)daysinmonth));
	//Log("fFROST - Frost modifier = %g\n", s->value[F_FROST]);
	s->value[F_FROST] = 1;


	/*VPD MODIFIER*/

	//Log("--RH = %g %%\n", met[month].rh);
	//Log("--vpd = %g mbar", vpd);

	//The input VPD data is in KPa
	//if the VPD is in KPa
	//Convert to mbar
	//1 Kpa = 10 mbar
	//s->value[F_VPD] = exp (- s->value[COEFFCOND] * vpd) * 10);
	//convert also COEFFCOND multiply it for
	s->value[F_VPD] = exp (- s->value[COEFFCOND] * vpd);
	Log("fVPD = %g\n", s->value[F_VPD]);

	//average yearly f_vpd modifiers
	s->value[AVERAGE_F_VPD] += s->value[F_VPD];


	//look the version 1 for 3pg vpd modifier version

	/*AGE MODIFIER*/

	if (a->value != 0)
	{
		if (management == T)
		{
			//for TIMBER
			//AGE FOR TIMBER IS THE EFFECTIVE AGE
			RelAge = (float)a->value / s->value[MAXAGE];
			s->value[F_AGE] = ( 1 / ( 1 + pow ((RelAge / (float)s->value[RAGE]), (float)s->value[NAGE] )));
			//Log("--Rel Age = %g years\n", RelAge);
			Log("--Age = %d years\n", a->value);
			Log("fAge - Age modifier for timber= %g\n", s->value[F_AGE]);
		}
		else
		{
			//for SHOOTS
			//AGE FOR COPPICE IS THE AGE FROM THE COPPICING
			RelAge = (float)a->value / s->value[MAXAGE_S];
			s->value[F_AGE] = ( 1 / ( 1 + pow ((RelAge / (float)s->value[RAGE_S]), (float)s->value[NAGE_S] )));
			//Log("--Rel Age = %g years\n", RelAge);
			//Log("--Age = %d years\n", a->value);
			Log("fAge - Age modifier for coppice = %g\n", s->value[F_AGE]);

		}
	}
	else
	{
		s->value[F_AGE] = 1;
		Log("no data for age F_AGE = 1\n");
	}





	/*SOIL NUTRIENT MODIFIER*/

	s->value[F_NUTR] = 1.0 - ( 1.0- site->fn0)  * pow ((1.0 - site->fr), site->fnn);
	Log("fNutr - Soil Nutrient modifier = %g\n", s->value[F_NUTR]);




	/*SOIL NUTRIENT MODIFIER*/
	//rev 16 May 2012
	//Log("Soil Nitrogen Content = %g g m^-2 \n", site->sN);


	/*SOIL WATER MODIFIER*/
	//todo:swc data

	//float MoistRatio_from_data;
	/*

	if ( ! year  && ! month )
	{
		if ( met[month].swc == -9999)
		{
			Log("No Data for SWC!!\n");
			Log("swc from data = %g\n", met[month].swc);
			Log("Function use default data\n");

			//in realtà solo per il primo mese dovrebbe prendere INITIALAVAILABLESOILWATER poi dovrebbe ricalcolarselo
			MoistRatio = site->initialAvailableSoilWater / c->max_asw;
			Log("-year %d\n", year);
			Log("-Initial Available Soil Water = %f mm\n", site->initialAvailableSoilWater);
			Log("-Moist Ratio = %g \n", MoistRatio);
		}
		else
		{
			MoistRatio = met[month].swc / 100;
			Log("OK Data for SWC!!\n");
			Log("swc from data = %g %%\n", met[month].swc);
			Log("Function use default data\n");
			Log("-Moist Ratio = %g \n", MoistRatio);
		}
	}
	else
	{
		MoistRatio = available_soil_water / c->max_asw;
		//Log("-Available Soil Water = %g mm\n", available_soil_water);
		Log("-Moist Ratio = %g \n", MoistRatio);
	}
	 */

	if (settings->time == 'm')
	{

		s->value[F_SW] = 1.0 / (1.0 + pow(((1.0 - c->soil_moist_ratio) / s->value[SWCONST]), s->value[SWPOWER]));

		if ( s->value[F_SW] > 1  )
		{
			Log("PROBLEM IN fSW !!!!!!!!!!\n");
			s->value[F_SW] = 1;
			Log("fSW - Soil Water modifier layer %d = %g\n", z,  s->value[F_SW]);
		}
		else
		{
			Log("fSW - Soil Water modifier layer %d = %g\n", z,  s->value[F_SW]);
		}
	}
	else
	{

		//todo F_PSISHOULD BE USED NOT IN GPP COMPUTATION BUT IN THE EVAPOTRANSPIRATION PROCESSES!!
		/*SOIL MATRIC POTENTIAL MODIFIER*/

		//**********************************
		//USABLE ONLY FOR DAILY SIMULATION
		//**********************************

		/* convert kg/m2 or mm  --> m3/m2 --> m3/m3 */
		//100 mm H20 m^-2 = 100 kg H20 m^-2
		Log("available soil water %g mm\n", c->available_soil_water);

		/* (DIM) volumetric water content */
		vwc = c->available_soil_water / (1000.0 * (site->soil_depth/100));
		Log("volumetric available soil water  = %g (DIM)\n", vwc);
		Log ("vwc_sat = %g (DIM)\n", c->vwc_sat);
		Log ("vwc/vwc_sat = %g \n", vwc / c->vwc_sat);

		/* calculate psi */
		//todo controllare vwc è l'unica variabile che può far variare psi fare delle prove su excel e vedere a quanto dovrebbe essere per avere un valore compreso tra OPEN e CLOSE
		/* (MPa) water potential of soil and leaves */
		psi = c->psi_sat * pow((vwc/c->vwc_sat), c->soil_b);
		Log ("PSI BIOME = %g (MPa)\n", psi);
		Log ("PSI_SAT BIOME = %g (MPa)\n", c->psi_sat);


		if (psi > s->value[SWPOPEN]) /*no water stress*/
		{
			s->value[F_PSI] = 1;
		}
		else if (psi <= s->value[SWPCLOSE]) /* full water stress */
		{
			s->value[F_PSI] = 0;
		}
		else /* partial water stress */
		{
			s->value[F_PSI] = (s->value[SWPCLOSE] - psi)/(s->value[SWPCLOSE] - s->value[SWPOPEN]);
		}

		//Log("F_PSI = %g\n", s->value[F_PSI]);

		s->value[F_SW] = s->value[F_PSI];

		if ( s->value[F_SW] > 1  )
		{
			Log("PROBLEM IN fSW !!!!!!!!!!\n");
			s->value[F_SW] = 1;
			Log("fSW-F_PSI - Soil Water modifier layer %d = %g\n", z,  s->value[F_SW]);
		}
		else
		{
			Log("fSW-F_PSI - Soil Water modifier layer %d = %g\n", z,  s->value[F_SW]);
		}

		//put for comparison with biome module
		s->value[F_SW] = 1.0 / (1.0 + pow(((1.0 - c->soil_moist_ratio) / s->value[SWCONST]), s->value[SWPOWER]));


		if ( s->value[F_SW] > 1  )
		{
			Log("PROBLEM IN fSW !!!!!!!!!!\n");
			s->value[F_SW] = 1;
			Log("fSW - Soil Water modifier layer %d = %g\n", z,  s->value[F_SW]);
		}
		else
		{
			Log("fSW - Soil Water modifier layer %d = %g\n", z,  s->value[F_SW]);
		}

	}

	//average yearly f_sw modifiers
	s->value[AVERAGE_F_SW] += s->value[F_SW];

	/*PHYSIOLOGICAL MODIFIER*/
	s->value[PHYS_MOD]= Minimum(s->value[F_VPD], s->value[F_SW]) * s->value[F_AGE];
	Log("PhysMod = %g\n", s->value[PHYS_MOD]);
	if (s->value[F_VPD] < s->value[F_SW])
	{
		Log("PHYSMOD uses F_VPD * F_AGE\n");
	}
	else
	{
		Log("PHYSMOD uses F_SW * F_AGE\n");
	}

	s->value[YEARLY_PHYS_MOD] += s->value[PHYS_MOD];
	//Log("Yearly Physmod = %g\n", s->value[YEARLY_PHYS_MOD]);


	/*SOIL DROUGHT MODIFIER*/
	//(see Duursma et al., 2008)rev_Angelo
	/*

	//to put in species.txt
	//numbers are not real just used for compile!!!!!!!!
	float leaf_res = 1; //leaf specific plant hydraulic resistance
	float min_leaf_pot = 1; //minimum leaf water potential


	//to put in site.txt ?????
	float soil_res = 1; //soil hydraulic resistance
	float psi0 = 2; //dry soil water potential in MPa
	float soil_coeff = 1; //empirical soil coefficient

	//soil average dimension particle
	//value are averaged from limits in site.txt
	float clay_dim = 0.001; //clay avg dimension of particle
	float silt_dim =  0.026;//silt avg dimension of particle
	float sand_dim =  1.025;//sand avg dimension of particle





    float bulk_pot; //bulk soil water potential
    float asw_vol; //available soil water in volume
    float eq;
	float eq1;
	float eq2;
	float sat_soil_water_cont; //saturated soil water content (m^3 m^-3)
	float soil_avg_dim; //soil mean particle diameter in mm
	float sigma_g; //geometric standard deviation in particle size distribution (mm)
	float pentry_temp; //soil entry water potential (MPa)
	float pentry; //correction for bulk density effects
	float bsl; //coefficient in soil water release curve (-)
	float soil_water_pot_sat; //soil water potential at saturation
	float sat_conduct; //saturated conductivity
	float specific_soil_cond; //specific soil hydraulic conductance
	float leaf_specific_soil_cond;


	//compute soil hydraulic characteristics from soil granulometry
	//from model Hydrall
	eq1 = (site->clay_perc * log(clay_dim)) + (site->silt_perc * log(silt_dim)) + (site->sand_perc * log(sand_dim));
	Log("eq1 = %g\n", eq1);

	//soil mean particle diameter in mm
	soil_avg_dim = exp(eq1);
	Log("soil_avg_dim = %g\n", soil_avg_dim);


    eq2 = sqrt ((pow ((site->clay_perc * log(clay_dim)),2)) + (pow ((site->sand_perc * log(sand_dim)),2)) + (pow ((site->silt_perc * log(silt_dim)),2)));
    Log("eq2 = %g\n", eq2);

    //geometric standard deviation in particle size distribution (mm)
    sigma_g = exp(eq2);
    Log("sigma_g = %g\n", sigma_g);

    //soil entry water potential (MPa)
    pentry_temp = -0.5 / sqrt(soil_avg_dim)/1000;
    Log("pentry_temp = %g\n", pentry_temp);
    //correction for bulk density effects with dens = 1.49 g/cm^3
    pentry = pentry_temp * pow ((site->bulk_dens / 1.3), (0.67 * bsl));
    Log("pentry = %g\n", pentry);

    bsl = -2 * (pentry * 1000) + 0.2 * sigma_g;
    Log("bsl = %g\n", bsl);

    //saturated soil water content
    sat_soil_water_cont= 1.0 - (site->bulk_dens/2.56);
    Log("soil water content at saturation = %g\n", sat_soil_water_cont);

    eq = pentry * pow ((sat_soil_water_cont / c->soil_moist_ratio), bsl);
    Log("eq = %g\n", eq);

    //compute bulk soil water potential
    //for psi see Magani xls
    bulk_pot = Maximum (eq, min_leaf_pot);
    Log("bulk soil water potential = %g\n", bulk_pot);

    //compute leaf-specific soil hydraulic conductance
	leaf_specific_soil_cond = sat_conduct * pow ((soil_water_pot_sat / bulk_pot), (2 + (3 / soil_coeff)));
	Log("leaf-specific soil hydraulic conductance = %g\n", leaf_specific_soil_cond);


	s->value[F_DROUGHT] = (leaf_res * (bulk_pot - min_leaf_pot)) / (- min_leaf_pot * ((leaf_res + soil_res) * bulk_pot));
	Log("F_DROUGHT = %g\n", s->value[F_DROUGHT]);
	 */





	/*CO2 MODIFIER FROM C-FIX*/

	Log("-------------------\n");
}

void Get_daily_modifiers (SPECIES *const s,  AGE *const a, CELL *const c, const MET_DATA *const met, int year,  int month, int day, int daysinmonth, float available_soil_water, float vpd,  int z, int management )
{
	float RelAge;
	float vwc; //soil volumetric water content
	float psi;  //soil matric potential



	Log("\nGET_DAILY_MODIFIERS\n\n");

	/*TEMPERATURE MODIFIER*/

	//Log("--Temperature Average %g °C\n", met[month].d[day].tavg);
	//Log("--Daylight Average Temperature  %g °C\n", met[month].d[day].tday);
	//Log("--Optimum temperature for species %s = %g °C\n", s->name, s->value[GROWTHTOPT]);
	//Log("--Maximum temperature for species %s = %g °C\n", s->name, s->value[GROWTHTMAX]);
	//Log("--Minimum temperature for species %s = %g °C\n", s->name, s->value[GROWTHTMIN]);

	if (met[month].d[day].tday == NO_DATA)
	{
		if ((met[month].d[day].tavg <= s->value[GROWTHTMIN]) || (met[month].d[day].tavg >= s->value[GROWTHTMAX]))
		{
			s->value[F_T] = 0;
			Log("F_T = 0 \n");
		}
		else
		{
			s->value[F_T] = ((met[month].d[day].tavg - s->value[GROWTHTMIN]) / (s->value[GROWTHTOPT] - s->value[GROWTHTMIN])) * pow(((s->value[GROWTHTMAX] - met[month].d[day].tavg) / (s->value[GROWTHTMAX] - s->value[GROWTHTOPT])),
					((s->value[GROWTHTMAX] - s->value[GROWTHTOPT]) / (s->value[GROWTHTOPT] - s->value[GROWTHTMIN])));
		}
	}
	else
	{
		if ((met[month].d[day].tday <= s->value[GROWTHTMIN]) || (met[month].d[day].tday >= s->value[GROWTHTMAX]))
		{
			Log("tday > GROWTHTMAX\n");
			s->value[F_T] = 0;
			Log("F_T = 0 \n");
		}
		else
		{
			s->value[F_T] = ((met[month].d[day].tday - s->value[GROWTHTMIN]) / (s->value[GROWTHTOPT] - s->value[GROWTHTMIN])) * pow(((s->value[GROWTHTMAX] - met[month].d[day].tday) / (s->value[GROWTHTMAX] - s->value[GROWTHTOPT])),
					((s->value[GROWTHTMAX] - s->value[GROWTHTOPT]) / (s->value[GROWTHTOPT] - s->value[GROWTHTMIN])));
		}
	}
	Log("fT = %g\n", s->value[F_T]);

	if (s->value[F_T] > 1)
	{
		Log("ATTENTION fT EXCEEDS 1 \n");
		s->value[F_T] = 1;
	}

	c->daily_f_t = s->value[F_T];


	//average yearly f_vpd modifiers
	s->value[AVERAGE_F_T] += s->value[F_T];



	/*FROST MODIFIER*/
	if(met[month].d[day].tday < s->value[GROWTHTMIN])
	{
		s->value[F_FROST] = 0;
		Log("fFROST - Frost modifier = %g\n", s->value[F_FROST]);
	}
	else
	{
		s->value[F_FROST] = 1;
		Log("fFROST - Frost modifier = %g\n", s->value[F_FROST]);
	}


	/*VPD MODIFIER*/

	//Log("--RH = %g %%\n", met[month].rh);
	//Log("--vpd = %g mbar", vpd);

	//The input VPD data is in KPa
	//if the VPD is in KPa
	//Convert to mbar
	//1 Kpa = 10 mbar
	//s->value[F_VPD] = exp (- s->value[COEFFCOND] * vpd) * 10);
	//convert also COEFFCOND multiply it for
	s->value[F_VPD] = exp (- s->value[COEFFCOND] * vpd);
	c->daily_f_vpd = s->value[F_VPD];
	Log("fVPD = %g\n", s->value[F_VPD]);

	//average yearly f_vpd modifiers
	s->value[AVERAGE_F_VPD] += s->value[F_VPD];


	//look the version 1 for 3pg vpd modifier version

	/*AGE MODIFIER*/

	if (a->value != 0)
	{
		if (management == T)
		{
			//for TIMBER
			//AGE FOR TIMBER IS THE EFFECTIVE AGE
			RelAge = (float)a->value / s->value[MAXAGE];
			s->value[F_AGE] = ( 1 / ( 1 + pow ((RelAge / (float)s->value[RAGE]), (float)s->value[NAGE] )));
			//Log("--Rel Age = %g years\n", RelAge);
			//Log("--Age = %d years\n", a->value);
			Log("fAge = %g\n", s->value[F_AGE]);
		}
		else
		{
			//for SHOOTS
			//AGE FOR COPPICE IS THE AGE FROM THE COPPICING
			RelAge = (float)a->value / s->value[MAXAGE_S];
			s->value[F_AGE] = ( 1 / ( 1 + pow ((RelAge / (float)s->value[RAGE_S]), (float)s->value[NAGE_S] )));
			//Log("--Rel Age = %g years\n", RelAge);
			//Log("--Age = %d years\n", a->value);
			Log("fAge = %g\n", s->value[F_AGE]);

		}
	}
	else
	{
		s->value[F_AGE] = 1;
		Log("no data for age F_AGE = 1\n");
	}

	/*SOIL NUTRIENT MODIFIER*/
	s->value[F_NUTR] = 1.0 - ( 1.0- site->fn0)  * pow ((1.0 - site->fr), site->fnn);
	Log("fNutr = %g\n", s->value[F_NUTR]);

	/*SOIL NUTRIENT MODIFIER*/
	//rev 16 May 2012
	//Log("Soil Nitrogen Content = %g g m^-2 \n", site->sN);

	/*SOIL WATER MODIFIER*/
	s->value[F_SW] = 1.0 / (1.0 + pow(((1.0 - c->soil_moist_ratio) / s->value[SWCONST]), s->value[SWPOWER]));
	c->daily_f_sw = s->value[F_SW];

	if ( s->value[F_SW] > 1  )
	{
		Log("PROBLEM IN fSW !!!!!!!!!!\n");
		s->value[F_SW] = 1;
		Log("fSW = %g\n", s->value[F_SW]);
	}
	else
	{
		Log("fSW = %g\n", s->value[F_SW]);
	}


	/*SOIL MATRIC POTENTIAL*/

	//**********************************
	//USABLE ONLY FOR DAILY SIMULATION
	//**********************************

	/* convert kg/m2 or mm  --> m3/m2 --> m3/m3 */
	//100 mm H20 m^-2 = 100 kg H20 m^-2
	Log("available soil water %g mm\n", c->available_soil_water);

	/* (DIM) volumetric water content */
	vwc = c->available_soil_water / (1000.0 * (site->soil_depth/100));
	Log("volumetric available soil water  = %g (DIM)\n", vwc);
	Log ("vwc_sat = %g (DIM)\n", c->vwc_sat);
	Log ("vwc/vwc_sat = %g \n", vwc / c->vwc_sat);

	/* calculate psi */
	//todo controllare vwc è l'unica variabile che può far variare psi fare delle prove su excel e vedere a quanto dovrebbe essere per avere un valore compreso tra OPEN e CLOSE
	/* (MPa) water potential of soil and leaves */
	psi = c->psi_sat * pow((vwc/c->vwc_sat), c->soil_b);
	Log ("PSI BIOME = %g (MPa)\n", psi);
	Log ("PSI_SAT BIOME = %g (MPa)\n", c->psi_sat);


	if (psi > s->value[SWPOPEN]) /*no water stress*/
	{
		s->value[F_PSI] = 1;
	}
	else if (psi <= s->value[SWPCLOSE]) /* full water stress */
	{
		s->value[F_PSI] = 0;
	}
	else /* partial water stress */
	{
		s->value[F_PSI] = (s->value[SWPCLOSE] - psi)/(s->value[SWPCLOSE] - s->value[SWPOPEN]);
	}
	Log("F_PSI = %g\n", s->value[F_PSI]);

	c->daily_f_psi = s->value[F_PSI];


	//average yearly f_sw modifiers
	s->value[AVERAGE_F_SW] += s->value[F_SW];

	/*PHYSIOLOGICAL MODIFIER*/
	s->value[PHYS_MOD]= Minimum(s->value[F_VPD], s->value[F_SW]) * s->value[F_AGE];
	Log("PhysMod = %g\n", s->value[PHYS_MOD]);
	if (s->value[F_VPD] < s->value[F_SW])
	{
		Log("PHYSMOD uses F_VPD * F_AGE\n");
	}
	else
	{
		Log("PHYSMOD uses F_SW * F_AGE\n");
	}

	s->value[YEARLY_PHYS_MOD] += s->value[PHYS_MOD];
	//Log("Yearly Physmod = %g\n", s->value[YEARLY_PHYS_MOD]);


	/*SOIL DROUGHT MODIFIER*/
	//(see Duursma et al., 2008)rev_Angelo
	/*

	//to put in species.txt
	//numbers are not real just used for compile!!!!!!!!
	float leaf_res = 1; //leaf specific plant hydraulic resistance
	float min_leaf_pot = 1; //minimum leaf water potential


	//to put in site.txt ?????
	float soil_res = 1; //soil hydraulic resistance
	float psi0 = 2; //dry soil water potential in MPa
	float soil_coeff = 1; //empirical soil coefficient

	//soil average dimension particle
	//value are averaged from limits in site.txt
	float clay_dim = 0.001; //clay avg dimension of particle
	float silt_dim =  0.026;//silt avg dimension of particle
	float sand_dim =  1.025;//sand avg dimension of particle





    float bulk_pot; //bulk soil water potential
    float asw_vol; //available soil water in volume
    float eq;
	float eq1;
	float eq2;
	float sat_soil_water_cont; //saturated soil water content (m^3 m^-3)
	float soil_avg_dim; //soil mean particle diameter in mm
	float sigma_g; //geometric standard deviation in particle size distribution (mm)
	float pentry_temp; //soil entry water potential (MPa)
	float pentry; //correction for bulk density effects
	float bsl; //coefficient in soil water release curve (-)
	float soil_water_pot_sat; //soil water potential at saturation
	float sat_conduct; //saturated conductivity
	float specific_soil_cond; //specific soil hydraulic conductance
	float leaf_specific_soil_cond;


	//compute soil hydraulic characteristics from soil granulometry
	//from model Hydrall
	eq1 = (site->clay_perc * log(clay_dim)) + (site->silt_perc * log(silt_dim)) + (site->sand_perc * log(sand_dim));
	Log("eq1 = %g\n", eq1);

	//soil mean particle diameter in mm
	soil_avg_dim = exp(eq1);
	Log("soil_avg_dim = %g\n", soil_avg_dim);


    eq2 = sqrt ((pow ((site->clay_perc * log(clay_dim)),2)) + (pow ((site->sand_perc * log(sand_dim)),2)) + (pow ((site->silt_perc * log(silt_dim)),2)));
    Log("eq2 = %g\n", eq2);

    //geometric standard deviation in particle size distribution (mm)
    sigma_g = exp(eq2);
    Log("sigma_g = %g\n", sigma_g);

    //soil entry water potential (MPa)
    pentry_temp = -0.5 / sqrt(soil_avg_dim)/1000;
    Log("pentry_temp = %g\n", pentry_temp);
    //correction for bulk density effects with dens = 1.49 g/cm^3
    pentry = pentry_temp * pow ((site->bulk_dens / 1.3), (0.67 * bsl));
    Log("pentry = %g\n", pentry);

    bsl = -2 * (pentry * 1000) + 0.2 * sigma_g;
    Log("bsl = %g\n", bsl);

    //saturated soil water content
    sat_soil_water_cont= 1.0 - (site->bulk_dens/2.56);
    Log("soil water content at saturation = %g\n", sat_soil_water_cont);

    eq = pentry * pow ((sat_soil_water_cont / c->soil_moist_ratio), bsl);
    Log("eq = %g\n", eq);

    //compute bulk soil water potential
    //for psi see Magani xls
    bulk_pot = Maximum (eq, min_leaf_pot);
    Log("bulk soil water potential = %g\n", bulk_pot);

    //compute leaf-specific soil hydraulic conductance
	leaf_specific_soil_cond = sat_conduct * pow ((soil_water_pot_sat / bulk_pot), (2 + (3 / soil_coeff)));
	Log("leaf-specific soil hydraulic conductance = %g\n", leaf_specific_soil_cond);


	s->value[F_DROUGHT] = (leaf_res * (bulk_pot - min_leaf_pot)) / (- min_leaf_pot * ((leaf_res + soil_res) * bulk_pot));
	Log("F_DROUGHT = %g\n", s->value[F_DROUGHT]);
	 */





	/*CO2 MODIFIER FROM C-FIX*/

	Log("-------------------\n");
}

