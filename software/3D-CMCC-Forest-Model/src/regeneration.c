/*
 * regeneration.c
 *
 *  Created on: 14/nov/2012
 *      Author: alessio
 */

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "constants.h"
#include "logger.h"
#include "common.h"
#include "settings.h"
#include "regeneration.h"

extern logger_t* g_log;

void seeds_germination ( const int species )
{


}

void regeneration (cell_t *const c, const int height, const int dbh, const int age, const int species)
{

	species_t *s;

	s = &c->heights[height].dbhs[dbh].ages[age].species[species];

	//seeds_germination ( s );


}



