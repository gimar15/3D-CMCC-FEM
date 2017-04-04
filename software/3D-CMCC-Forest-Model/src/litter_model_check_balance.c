/*
 * litter_model_check_balance.c
 *
 *  Created on: 03 apr 2017
 *      Author: alessio
 */

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "common.h"
#include "check_balance.h"
#include "constants.h"
#include "settings.h"
#include "logger.h"

extern logger_t* g_debug_log;

int check_litter_carbon_flux_balance(cell_t *const c)
{
	double in;
	double out;
	double store;
	double balance;
	static double old_store;

	logger(g_debug_log, "\n*********CHECK LITTER CARBON BALANCE************\n");

	/* check complete litter level carbon flux balance */

	/* sum of carbon sources */
	in      = c->daily_litrC;

	/* sum of carbon sinks */
	out     = c->daily_soilC;

	/* sum of current carbon storage */
	store   = c->litr1C +
			c->litr2C +
			c->litr3C +
			c->litr4C ;

	balance = in - out - ( store - old_store );

	logger(g_debug_log, "\nCELL CARBON FLUX BALANCE\n");

	if ( ( fabs( balance ) > eps ) && ( c->dos > 1) )
	{
		logger_all("DOY = %d\n", c->doy);
		logger_all("\nin\n");
		logger_all("c->daily_litrC = %g gC/m2/day\n", c->daily_litrC);
		logger_all("\nout\n");
		logger_all("c->daily_soilC = %g gC/m2/day\n",c->daily_soilC);
		logger_all("\nstore\n");
		logger_all("c->litr1C = %g gC/m2/day\n", c->litr1C);
		logger_all("c->litr2C = %g gC/m2/day\n", c->litr2C);
		logger_all("c->litr3C = %g gC/m2/day\n", c->litr3C);
		logger_all("c->litr4C = %g gC/m2/day\n", c->litr4C);
		logger_all("\ncarbon in = %g gC/m2/day\n", in);
		logger_all("carbon out = %g gC/m2/day\n", out);
		logger_all("carbon store = %g gC/m2/day\n", store);
		logger_all("carbon_balance = %g gC/m2/day\n",balance);
		logger_all("...FATAL ERROR in 'Litter_ model_daily' carbon balance (exit)\n");

		return 0;
	}
	else
	{
		old_store = store;
		logger(g_debug_log, "...ok 'Litter_ model_daily' carbon balance\n");
	}
	logger(g_debug_log,"*****************************************************\n");

	return 1;
}
