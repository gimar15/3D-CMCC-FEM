/*
 * soil_water_balance.c
 *
 *  Created on: 12/nov/2012
 *      Author: alessio
 */

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "types.h"
#include "constants.h"

//fixme  maybe it can be moved to soil_model.c
void Get_soil_water_balance (CELL *c, const MET_DATA *const met, int month, int day)
{
	Log("\nGET SOIL WATER BALACE\n");
	c->old_available_soil_water = c->available_soil_water;

	/*update balance*/
	if(met[month].d[day].tavg>0.0)
	{
		c->available_soil_water = (c->available_soil_water + c->daily_rain + c->snow_melt)
				- (c->daily_tot_c_transp + c->daily_tot_c_int + c->soil_evaporation + c->runoff);
	}
	else
	{
		c->available_soil_water = c->available_soil_water - c->soil_evaporation;
	}
	Log("ASW = %f mm\n", c->available_soil_water);
	Log("snow pack = %f mm\n", c->snow_pack);

	/*check*/
	if (c->available_soil_water < (c->max_asw * site->min_frac_maxasw))
	{
		//TEST REMOVED ANY REFILL OF WATER SOIL
		Log("ATTENTION Available Soil Water is low than MinASW!!! \n");
		//c->available_soil_water = c->max_asw * site->min_frac_maxasw;
		Log("ASW = %f\n", c->available_soil_water);
	}
	if ( c->available_soil_water > c->max_asw)
	{
		c->runoff = c->available_soil_water -c->max_asw;
		Log("Runoff = %f\n", c->runoff);
		Log("ATTENTION Available Soil Water exceeds MAXASW!! \n");
		c->available_soil_water = c->max_asw;
		Log("Available soil water = %f\n", c->available_soil_water);
	}
	c->swc= (c->available_soil_water * 100)/c->max_asw;
	Log("SWC = %g(%vol)\n", c->swc);
}
