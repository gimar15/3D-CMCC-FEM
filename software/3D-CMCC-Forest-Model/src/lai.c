/*lai.c*/

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "types.h"

//TO COMPUTE YEARLY PEAK LAI FROM PROVIOUS YEARLY LAI

void Get_initial_month_lai (SPECIES *const s)
{


	Log("\n--GET_INITIAL_MONTH_LAI--\n");

	if (s->counter[VEG_MONTHS]  == 1)
	{
		Log("++Reserves pools = %g tDM/ha\n", s->value [BIOMASS_RESERVE_CTEM]);
		Log("++Reserve biomas for each tree in g = %g \n", s->value[BIOMASS_RESERVE_CTEM] * 1000000 / s->counter[N_TREE]);

		//just a fraction of biomass reserve is used for foliage, the ratio is driven by the BIOME_BGC newStem:newLeaf ratio
		s->value[BIOMASS_FOLIAGE_CTEM] = s->value[BIOMASS_RESERVE_CTEM] * (1.0 / s->value[STEM_LEAF]);

		Log("ratio of reserve for foliage = %g% \n", (1.0 / s->value[STEM_LEAF] * 100));

		s->value[BIOMASS_RESERVE_CTEM] -= s->value[BIOMASS_FOLIAGE_CTEM];
		Log("++Reserves pools = %g tDM/ha\n", s->value [BIOMASS_RESERVE_CTEM]);

		//not sure if allocate the remaining reserves for stem
		//s->value[BIOMASS_STEM_CTEM] = s->value[BIOMASS_STEM_CTEM] + (s->value[BIOMASS_RESERVE_CTEM]-s->value[BIOMASS_FOLIAGE_CTEM]);

		Log ("++Biomass foliage from reserves for initial LAI = %g \n", s->value[BIOMASS_FOLIAGE_CTEM]);
		//Log ("++Biomass stem from reserves for initial LAI = %g \n", s->value[BIOMASS_STEM_CTEM]);
		//Log ("++Biomass stem increment from reserves for initial LAI = %g \n", s->value[BIOMASS_RESERVE_CTEM]-s->value[BIOMASS_FOLIAGE_CTEM]);

		s->value[LAI] = (s->value[BIOMASS_FOLIAGE_CTEM] * 1000) / (s->value[CANOPY_COVER_DBHDC] * settings->sizeCell) * s->value[SLAmkg];
		// * 1000 to convert reserve biomass from tDM into KgDM

		Log("++Lai from reserves = %g\n", s->value[LAI]);
		//Log("++Canopy Cover = %g\n", s->value[CANOPY_COVER_DBHDC]);
		//Log("++Size Cell = %g\n", settings->sizeCell);
		//Log("++Sla = %g\n", s->value[SLAmkg]);
	}
	else
	{
		Log("++Lai = %g\n", s->value[LAI]);
	}


}

void Get_end_month_lai (SPECIES *const s)
{
	Log("GET_END_MONTH_LAI\n");
	s->value[LAI] = (s->value[BIOMASS_FOLIAGE_CTEM]) / (s->value[CANOPY_COVER_DBHDC] * settings->sizeCell) * s->value[SLAmkg];
	Log("++Lai = %g\n", s->value[LAI]);
}
