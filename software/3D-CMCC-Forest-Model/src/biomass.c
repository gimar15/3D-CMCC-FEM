/*biomass_increment.c*/

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "types.h"
#include "constants.h"


void Tree_Branch_Bark (CELL *const c,  int years)
{
	int height;
	int age;
	int species;




	for ( height = c->heights_count - 1; height >= 0; height-- )
	{
		for ( age = c->heights[height].ages_count - 1 ; age >= 0 ; age-- )
		{
			for (species = 0; species < c->heights[height].ages[age].species_count; species++)
			{
				if (!years && c->heights[height].ages[age].species[species].value[FRACBB0] == 0)
				{
					Log("I don't have FRACBB0 = FRACBB1 \n");
					c->heights[height].ages[age].species[species].value[FRACBB0] = c->heights[height].ages[age].species[species].value[FRACBB1];
					Log("FRACBB0 = %f\n", c->heights[height].ages[age].species[species].value[FRACBB0]);
				}
				else
				{
					c->heights[height].ages[age].species[species].value[FRACBB] = c->heights[height].ages[age].species[species].value[FRACBB1]
											  + (c->heights[height].ages[age].species[species].value[FRACBB0]
											 - c->heights[height].ages[age].species[species].value[FRACBB1])
										 * exp(-ln2 * (c->heights[height].ages[age].value / c->heights[height].ages[age].species[species].value[TBB]));

				}
			}
		}
	}
}
void Biomass_increment_BOY (CELL *const c, SPECIES *const s, int height, int age, int years)
{
	double oldBasalArea;

	Log("BIOMASS_INCREMENT_Beginning of Year\n");

	//compute Basal Area
		if (years == 0)
		{
			Log("avdbh = %f\n",s->value[AVDBH] );
			s->value[BASAL_AREA] = (((pow((s->value[AVDBH] / 2), 2)) * Pi) / 10000);
			s->value[STAND_BASAL_AREA] = s->value[BASAL_AREA] * s->counter[N_TREE];
		}
		else
		{
			oldBasalArea = s->value[BASAL_AREA];
			s->value[BASAL_AREA] = (((pow((s->value[AVDBH] / 2), 2)) * Pi) / 10000);
			s->value[STAND_BASAL_AREA] = s->value[BASAL_AREA] * s->counter[N_TREE];
			Log("old basal area = %f \n", oldBasalArea);
			Log(" Basal Area Increment= %f m^2/tree \n", s->value[BASAL_AREA] - oldBasalArea);
			Log(" Basal Area Increment= %f cm^2/tree \n", (s->value[BASAL_AREA] - oldBasalArea) * 10000);

		}

		Log("Basal Area for this layer = %f cm^2/tree\n", s->value[BASAL_AREA]*10000);
		Log("Stand Basal Area for this layer = %f m^2/area\n", s->value[STAND_BASAL_AREA]);


		//Log("**Kostner eq** \n");
		//sapwood area
		//see Kostner et al in Biogeochemistry of Forested Catchments in a Changing Environment, Matzner, Springer for Q. petraea
		s->value[SAPWOOD_AREA] = s->value[SAP_A] * pow (s->value[AVDBH], s->value[SAP_B]);

		Log("sapwood area from Kostner = %f cm^2\n", s->value[SAPWOOD_AREA]);
		s->value[HEARTWOOD_AREA] = (s->value[BASAL_AREA] * 10000) - s->value[SAPWOOD_AREA];
		Log("heartwood from Wang et al 2010 = %f cm^2\n", s->value[HEARTWOOD_AREA]);

		s->value[SAPWOOD_PERC] = (s->value[SAPWOOD_AREA] / 10000) / s->value[BASAL_AREA];
		Log("Sapwood/Basal Area = %f \n", s->value[SAPWOOD_PERC] );
		Log("Sapwood/Basal Area = %f %%\n",s->value[SAPWOOD_PERC] * 100);


		//compute sap wood pools and heart wood pool
		s->value[WS_sap] =  s->value[BIOMASS_STEM] * s->value[SAPWOOD_PERC];
		Log("Stem biomass = %f tDM/area \n", s->value[BIOMASS_STEM]);
		Log("Sapwood stem biomass = %f tDM/area \n", s->value[WS_sap]);
		s->value[WS_heart] = s->value[BIOMASS_STEM] - s->value[WS_sap];
		Log("Heartwood stem biomass = %f tDM/area \n", s->value[WS_heart]);
		s->value[WRC_sap] =  (s->value[BIOMASS_ROOTS_COARSE] * s->value[SAPWOOD_PERC]);
		Log("Sapwood coarse root biomass = %f tDM class cell \n", s->value[WRC_sap]);
		s->value[WRC_heart] = s->value[BIOMASS_ROOTS_COARSE] - s->value[WRC_sap];
		Log("Heartwood coarse root biomass (NOT USED) = %f tDM/area \n", s->value[WRC_heart]);

		/*COMPUTE BIOMASS LIVE WOOD*/
		s->value[BIOMASS_LIVE_WOOD] = s->value[BIOMASS_STEM_LIVE_WOOD]+
										s->value[BIOMASS_COARSE_ROOT_LIVE_WOOD]+
										s->value[BIOMASS_STEM_BRANCH_LIVE_WOOD]+
										s->value[BIOMASS_ROOTS_FINE]+
										s->value[BIOMASS_FOLIAGE];
		Log("Live biomass following BIOME = %f tDM/area\n", s->value[BIOMASS_LIVE_WOOD]);
		s->value[BIOMASS_DEAD_WOOD] = s->value[BIOMASS_STEM_DEAD_WOOD]+
										s->value[BIOMASS_COARSE_ROOT_DEAD_WOOD]+
										s->value[BIOMASS_STEM_BRANCH_DEAD_WOOD];
		Log("Dead biomass following BIOME = %f tDM/area\n", s->value[BIOMASS_DEAD_WOOD]);



}

void Biomass_increment_EOY (CELL *const c, SPECIES *const s, int top_layer, int z, int height, int age)
{
	/*CURRENT ANNUAL INCREMENT-CAI*/
	double MassDensity;
	double dominant_prec_volume;
	double dominated_prec_volume;
	double subdominated_prec_volume;

	//in m^3/area/yr
	//Cai = Volume t1 - Volume t0
	//Mai = Volume t1 / Age

	Log("***CAI & MAI***\n");

	//sergio if prec_volume stands for precedent (year) volume, shouldn't the CAI be quantified before updating prec_volume? in this way it shold alway return ~0, being the product of the same formula expressed with the same quantities

	MassDensity = s->value[RHOMAX] + (s->value[RHOMIN] - s->value[RHOMAX]) * exp(-ln2 * (c->heights[height].ages[age].value / s->value[TRHO]));
	/*STAND VOLUME-(STEM VOLUME)*/
	s->value[VOLUME] = s->value[BIOMASS_STEM] * (1 - s->value[FRACBB]) / MassDensity;
	Log("Volume for this class = %f m^3/area\n", s->value[VOLUME]);


	if (settings->spatial == 'u')
	{
		switch (c->annual_layer_number)
		{
		case 3:
			if (c->heights[height].z == 2)
			{
				dominant_prec_volume = s->value[BIOMASS_STEM] * (1 - s->value[FRACBB]) /	MassDensity;
				Log("DominantVolume = %f m^3/cell resolution\n", dominant_prec_volume);
				s->value[CAI] = s->value[VOLUME] - dominant_prec_volume;
				Log("DOMINANT CAI = %f m^3/area/yr\n", s->value[CAI]);
				s->value[MAI] = s->value[VOLUME] / (double)c->heights[height].ages[age].value ;
				Log("MAI-Mean Annual Increment = %f m^3/area/yr \n", s->value[MAI] );
				if (dominant_prec_volume > s->value[VOLUME])
				{
					Log("ERROR IN CAI FUNCTION!!!!\nprev_volume > VOLUME\n");
					Log("prev_volume - VOLUME = %f\n", dominant_prec_volume - s->value[VOLUME]);
				}
			}
			else if (c->heights[height].z == 1)
			{
				dominated_prec_volume = s->value[BIOMASS_STEM] * (1 - s->value[FRACBB]) /	MassDensity;
				Log("DominatedVolume = %f m^3/cell resolution\n", dominated_prec_volume);
				s->value[CAI] = s->value[VOLUME] - dominated_prec_volume;
				Log("DOMINATED CAI = %f m^3/area/yr\n", s->value[CAI]);
				s->value[MAI] = s->value[VOLUME] / (double)c->heights[height].ages[age].value ;
				Log("MAI-Mean Annual Increment = %f m^3/area/yr\n", s->value[MAI] );
				if (dominated_prec_volume > s->value[VOLUME])
				{
					Log("ERROR IN CAI FUNCTION!!!!\nprev_volume > VOLUME\n");
					Log("prev_volume - VOLUME = %f\n", dominated_prec_volume - s->value[VOLUME]);
				}
			}
			else
			{
				subdominated_prec_volume = s->value[BIOMASS_STEM] * (1 - s->value[FRACBB]) /	MassDensity;
				Log("SubDominatedVolume = %f m^3/cell resolution\n", subdominated_prec_volume);
				s->value[CAI] = s->value[VOLUME] - subdominated_prec_volume;
				Log("SUBDOMINATED CAI = %f m^3/area/yr\n", s->value[CAI]);
				s->value[MAI] = s->value[VOLUME] / (double)c->heights[height].ages[age].value ;
				Log("MAI-Mean Annual Increment = %f m^3/area/yr\n", s->value[MAI] );
				if (subdominated_prec_volume > s->value[VOLUME])
				{
					Log("ERROR IN CAI FUNCTION!!!!\nprev_volume > VOLUME\n");
					Log("prev_volume - VOLUME = %f\n", subdominated_prec_volume - s->value[VOLUME]);
				}
			}
			break;
		case 2:
			if (c->heights[height].z == 1)
			{
				dominant_prec_volume = s->value[BIOMASS_STEM] * (1 - s->value[FRACBB]) /	MassDensity;
				Log("DominantVolume = %f m^3/cell resolution\n", dominant_prec_volume);
				s->value[CAI] = s->value[VOLUME] - dominant_prec_volume;
				Log("DOMINANT CAI = %f m^3/area/yr\n", s->value[CAI]);
				s->value[MAI] = s->value[VOLUME] / (double)c->heights[height].ages[age].value ;
				Log("MAI-Mean Annual Increment = %f m^3/area/yr \n", s->value[MAI] );
				if (dominant_prec_volume > s->value[VOLUME])
				{
					Log("ERROR IN CAI FUNCTION!!!!\nprev_volume > VOLUME\n");
					Log("prev_volume - VOLUME = %f\n", dominant_prec_volume - s->value[VOLUME]);
				}
			}
			else
			{
				dominated_prec_volume = s->value[BIOMASS_STEM] * (1 - s->value[FRACBB]) /	MassDensity;
				Log("DominatedVolume = %f m^3/cell resolution\n", dominated_prec_volume);
				s->value[CAI] = s->value[VOLUME] - dominated_prec_volume;
				Log("DOMINATED CAI = %f m^3/area/yr\n", s->value[CAI]);
				s->value[MAI] = s->value[VOLUME] / (double)c->heights[height].ages[age].value ;
				Log("MAI-Mean Annual Increment = %f m^3/area/yr\n", s->value[MAI] );
				if (dominated_prec_volume > s->value[VOLUME])
				{
					Log("ERROR IN CAI FUNCTION!!!!\nprev_volume > VOLUME\n");
					Log("prev_volume - VOLUME = %f\n", dominated_prec_volume - s->value[VOLUME]);
				}
			}

			break;
		case 1:
			/*
			dominant_prec_volume = s->value[BIOMASS_STEM] * (1 - s->value[FRACBB]) /	MassDensity;
			Log("DominantVolume = %f m^3/cell resolution\n", dominant_prec_volume);
			s->value[CAI] = s->value[VOLUME] - dominant_prec_volume;
			Log("DOMINANT CAI = %f m^3/area/yr\n", s->value[CAI]);
			s->value[MAI] = s->value[VOLUME] / (double)c->heights[height].ages[age].value ;
			Log("MAI-Mean Annual Increment = %f m^3/area/yr \n", s->value[MAI] );

			if (dominant_prec_volume > s->value[VOLUME])
			{
				Log("ERROR IN CAI FUNCTION!!!!\nprev_volume > VOLUME\n");
				Log("prev_volume - VOLUME = %f\n", dominant_prec_volume - s->value[VOLUME]);
			}
			*/
			Log("PREVIOUS Volume = %f m^3/cell resolution\n", s->value[PREVIOUS_VOLUME]);
			Log("CURRENT Volume = %f m^3/cell resolution\n", s->value[VOLUME]);
			s->value[CAI] = s->value[VOLUME] - s->value[PREVIOUS_VOLUME];
			Log("Yearly Stand CAI = %f m^3/area/yr\n", s->value[CAI]);
			s->value[MAI] = s->value[VOLUME] / (double)c->heights[height].ages[age].value ;
			Log("Yearly Stand MAI = %f m^3/area/yr \n", s->value[MAI]);
			break;
		}
	}
	else
	{
		Log("PREVIOUS Volume = %f m^3/cell resolution\n", s->value[PREVIOUS_VOLUME]);
		s->value[CAI] = s->value[VOLUME] - s->value[PREVIOUS_VOLUME];
		s->value[CAI] = s->value[VOLUME] * s->value[PERC] - s->value[PREVIOUS_VOLUME];
		Log("Yearly Stand CAI = %f m^3/area/yr\n", s->value[CAI]);
		s->value[MAI] = (s->value[VOLUME] * s->value[PERC] )/ (double)c->heights[height].ages[age].value ;
		Log("Yearly Stand MAI = %f m^3/area/yr \n", s->value[MAI] );
	}
}

void AGB_BGB_biomass (CELL *const c, int height, int age, int species)
{

	Log("**AGB & BGB**\n");
	Log("-for Class\n");
	c->heights[height].ages[age].species[species].value[CLASS_AGB] = c->heights[height].ages[age].species[species].value[BIOMASS_STEM]
																	 + c->heights[height].ages[age].species[species].value[BIOMASS_FOLIAGE];
	Log("Yearly Class AGB = %f tDM/area year\n", c->heights[height].ages[age].species[species].value[CLASS_AGB]);
	c->heights[height].ages[age].species[species].value[CLASS_BGB] = c->heights[height].ages[age].species[species].value[BIOMASS_ROOTS_TOT_tDM];
	Log("Yearly Class BGB = %f tDM/area year\n", c->heights[height].ages[age].species[species].value[CLASS_BGB]);


	Log("-for Stand\n");

	c->stand_agb += c->heights[height].ages[age].species[species].value[CLASS_AGB] * c->heights[height].ages[age].species[species].value[PERC];
	Log("Yearly Stand AGB = %f tDM/area year\n", c->stand_agb);
	c->stand_bgb += c->heights[height].ages[age].species[species].value[CLASS_BGB] * c->heights[height].ages[age].species[species].value[PERC];
	Log("Yearly Stand BGB = %f tDM/area year\n", c->stand_bgb);
	c->heights[height].ages[age].species[species].value[CLASS_AGB] = 0;
	c->heights[height].ages[age].species[species].value[CLASS_BGB] = 0;

}

extern void Average_tree_biomass (SPECIES *s)
{

	s->value[AV_STEM_MASS_KgDM] = s->value[BIOMASS_STEM] * 	1000.0 / s->counter[N_TREE];
	s->value[AV_ROOT_MASS_KgDM] = s->value[BIOMASS_ROOTS_TOT_tDM] * 1000.0 / s->counter[N_TREE];

	Log("Average Stem Mass = %f kgDM stem /tree\n", s->value[AV_STEM_MASS_KgDM]);
}

extern void Total_class_level_biomass (SPECIES *s)
{
	// Total Biomass less Litterfall and Root turnover
	s->value[TOTAL_W] =  s->value[BIOMASS_FOLIAGE] + s->value[BIOMASS_ROOTS_FINE] + s->value[BIOMASS_ROOTS_COARSE] +s->value[BIOMASS_STEM] + s->value[BIOMASS_BRANCH];
	Log("Total Biomass less Litterfall and Root Turnover = %f tDM/area\n", s->value[TOTAL_W]);
}
