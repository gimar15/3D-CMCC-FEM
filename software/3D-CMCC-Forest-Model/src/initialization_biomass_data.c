/*
 * initialization_biomass_data.c

 *
 *  Created on: 31/ott/2012
 *      Author: alessio
 */
/* includes */
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "types.h"

void Get_initialization_biomass_data (SPECIES *const s)
{

	float sapwood_perc;


	Log("No Biomass Data are available for model initialization \n");
	Log("Generating input biomass data from DBH data...\n");

	//compute foliage biomass for evergreen

	//compute stem biomass
	s->value[AV_STEM_MASS]  = (pow (s->value[AVDBH], 1.0/(1.0/s->value[STEMPOWER])))*s->value[STEMCONST];
	s->value[BIOMASS_STEM_CTEM] = s->value[AV_STEM_MASS] * s->counter[N_TREE];
	Log("-Stem Biomass initialization data from DBH = %g \n", s->value[BIOMASS_STEM_CTEM]);

	//compute coarse root biomass using root to shoot ratio
	s->value[BIOMASS_ROOTS_COARSE_CTEM]  = s->value[BIOMASS_STEM_CTEM] * s->value[COARSE_ROOT_STEM];
	Log("--Coarse Root Biomass initialization data from Stem Biomass = %g \n", s->value[BIOMASS_ROOTS_COARSE_CTEM]);

	//compute fine root biomass setting by default to 0
	s->value[BIOMASS_ROOTS_FINE_CTEM] = 0;
	Log("--Coarse Root Biomass initialization data from Stem Biomass = %g \n", s->value[BIOMASS_ROOTS_FINE_CTEM]);

	//compute foliage biomass for evergreen
	s->value[BIOMASS_FOLIAGE_CTEM] =  s->value[BIOMASS_STEM_CTEM] * (1.0/s->value[STEM_LEAF]);
	Log("--Foliage Biomass initialization data from Stem Biomass = %g \n", s->value[BIOMASS_ROOTS_FINE_CTEM]);


	//compute reserve "biomass"
	s->value[BASAL_AREA] = (((pow((s->value[AVDBH] / 2), 2)) * Pi) / 10000);
	s->value[SAPWOOD_AREA] = s->value[SAP_A] * pow (s->value[AVDBH], s->value[SAP_B]);
	sapwood_perc = (s->value[SAPWOOD_AREA] / 10000) / s->value[BASAL_AREA];
	s->value[WS_sap] =  s->value[BIOMASS_STEM_CTEM] * sapwood_perc;

	//these values are taken from: Schwalm and Ek, 2004 Ecological Modelling
	if (s->phenology == 0)
	{
		s->value[BIOMASS_RESERVE_CTEM]= s->value[WS_sap] * 0.11;
	}
	else
	{
		s->value[BIOMASS_RESERVE_CTEM]= s->value[WS_sap] * 0.05;
	}

}
