/*modifiers.c*/

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "types.h"

void Get_modifiers (SPECIES *const s,  AGE *const a, CELL *const c, const MET_DATA *const met, int year,  int month, int daysinmonth, float available_soil_water, float vpd,  int z, int management )
{
	float RelAge;



	Log("\n GET_MODIFIERS\n\n");

	/*TEMPERATURE MODIFIER*/

	Log("--Temperature Average %g °C\n", met[month].tav);
	//Log("--Optimum temperature for species %s = %g °C\n", s->name, s->value[GROWTHTOPT]);
	//Log("--Maximum temperature for species %s = %g °C\n", s->name, s->value[GROWTHTMAX]);
	//Log("--Minimum temperature for species %s = %g °C\n", s->name, s->value[GROWTHTMIN]);

	if ((met[month].tav <= s->value[GROWTHTMIN]) || (met[month].tav >= s->value[GROWTHTMAX]))
	{
		s->value[F_T] = 0;
		Log("F_T = 0 \n");
	}
	else
	{
		s->value[F_T] = ((met[month].tav - s->value[GROWTHTMIN]) / (s->value[GROWTHTOPT] - s->value[GROWTHTMIN])) * pow(((s->value[GROWTHTMAX] - met[month].tav) / (s->value[GROWTHTMAX] - s->value[GROWTHTOPT])),
				((s->value[GROWTHTMAX] - s->value[GROWTHTOPT]) / (s->value[GROWTHTOPT] - s->value[GROWTHTMIN])));
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

	//The input VPD data is in mbar
	//if the VPD is in KPa
	//Convert to mbar
	//1 Kpa = 10 mbar
	//s->value[F_VPD] = exp (- s->value[COEFFCOND] * vpd) * 10);
	//convert also COEFFCOND multiply it for
	s->value[F_VPD] = exp (- s->value[COEFFCOND] * vpd);
	Log("fVPD - VPD modifier = %g\n", s->value[F_VPD]);

	//average yearly f_vpd modifiers
	s->value[AVERAGE_F_VPD] += s->value[F_VPD];


	//look the version 1 for 3pg vpd modifier version

	/*AGE MODIFIER*/


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
			MoistRatio = site->initialAvailableSoilWater / site->maxAsw;
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
		MoistRatio = available_soil_water / site->maxAsw;
		//Log("-Available Soil Water = %g mm\n", available_soil_water);
		Log("-Moist Ratio = %g \n", MoistRatio);
	}
	*/

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


	/*SOIL MATRIC POTENTIAL MODIFIER*/
	//see BIOME-BGC 4.2
	//all percentage are converted in 100 %
	float sand = site->sand_perc * 100;
	float clay = site->clay_perc * 100;
	float silt = site->silt_perc * 100;

	/* calculate the soil pressure-volume coefficients from texture data */
	/* Uses the multivariate regressions from Cosby et al., 1984 */
	/* first check that the percentages add to 100.0 */

	float soil_b;  //soil moisture parameter
	float vwc_sat; //soil saturated Volumetric water content
	float psi_sat;	//soil saturated matric potential
	float vwc_fc; //Soil Field Capacity Volumetric Water Content in m3/m3
	float soilw_fc; //maximum volume soil water content in m3/m3
	float soilw_sat; //maximum volume soil water content in m3/m3
	float vwc; //soil volumetric water content
	float psi, swp;  //soil matric potential
	float SWP_open = -0.6;
	float SWP_close = -3;

	float F_SWP;



	soil_b = -(3.10 + 0.157*clay - 0.003*sand);
	Log ("soil_b = %g\n", soil_b);
	vwc_sat = (50.5 - 0.142*sand - 0.037*clay)/100.0;
	psi_sat = -(exp((1.54 - 0.0095*sand + 0.0063*silt)*log(10.0))*9.8e-5);
	Log ("psi_sat = %g\n", psi_sat);
	vwc_fc =  vwc_sat * pow((-0.015/psi_sat),1.0/soil_b);
	Log ("vwc_fc = %g m^3m^-3\n", vwc_fc);

	/* define maximum soilwater content, for outflow calculation
	converts volumetric water content (m3/m3) --> (kg/m2) */
	soilw_fc = (site->soil_depth / 100) * vwc_fc * 1000.0;
	Log ("soilw_fc BIOME = %g kg m^-2\n", soilw_fc);
	soilw_sat = (site->soil_depth / 100) * vwc_sat * 1000.0;
	Log ("soilw_sat BIOME = %g kg m^-2\n", soilw_sat);

	/* convert kg/m2 or mm  --> m3/m2 --> m3/m3 */
	//100 mm H20 m^-2 = 100 kg H20 m^-2
	vwc = c->available_soil_water / (1000.0 * (site->soil_depth/100));

	/* calculate psi */
	psi = psi_sat * pow((vwc/vwc_sat), soil_b);
	Log ("SWP-PSI BIOME = %g\n", psi);

	psi = swp;



	if (swp > SWP_open) /*no water stress*/
	{
		F_SWP = 1;
	}
	else if (swp <= SWP_close) /* full water stress */
	{
		F_SWP = 0;
	}
	else /* partial water stress */
	{
		F_SWP = (SWP_close - swp)/(SWP_close - SWP_open);
	}

	Log("F_SWP = %g\n", F_SWP);


	/*CO2 MODIFIER FROM C-FIX*/

	Log("-------------------\n");
}
