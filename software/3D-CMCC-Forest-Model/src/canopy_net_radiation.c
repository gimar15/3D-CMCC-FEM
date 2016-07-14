/*
 * canopy_net_radiation.c
 *
 *  Created on: 12 lug 2016
 *      Author: alessio
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "common.h"
#include "constants.h"
#include "logger.h"
#include "soil_settings.h"
#include "topo.h"
#include "canopy_radiation_sw_band.h"
#include "canopy_radiation_lw_band.h"
#include "canopy_net_radiation.h"

extern logger_t* g_log;

void canopy_net_radiation(species_t *const s, cell_t *const c, const meteo_t *const met, const int day, const int month, const int year, const int height, const int age, const int species)
{

	logger(g_log, "\n**NET RADIATION ROUTINE**\n");

	/* compute net radiation */
	s->value[NET_RAD] = s->value[NET_SW_RAD] + s->value[NET_LW_RAD];
	logger(g_log, "Net SW Radiation for canopy = %g W/m2\n", s->value[NET_SW_RAD]);
	logger(g_log, "Net LW Radiation for canopy = %g W/m2\n", s->value[NET_LW_RAD]);
	logger(g_log, "Net Radiation for canopy = %g W/m2\n", s->value[NET_RAD]);

	//note: it shouldn't include soil..
	c->net_rad_for_soil = c->net_sw_rad_for_soil + c->net_lw_rad_for_soil;
	logger(g_log, "Net SW Radiation for soil = %g W/m2\n", c->net_sw_rad_for_soil);
	logger(g_log, "Net LW Radiation for soil = %g W/m2\n", c->net_lw_rad_for_soil);
	logger(g_log, "Net Radiation for soil = %g W/m2\n", c->net_rad_for_soil);
}
