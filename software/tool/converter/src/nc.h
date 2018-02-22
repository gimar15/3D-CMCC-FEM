// nc.h
//
// written by A.Ribeca
//
// please note that this file must be included only once!
//

int nc_conv(dataset_t* dataset, const char*const folder)
{
#define BUF_SIZE			(256)	// should be enough
#define NC_MISSING_VALUE	(1e20)
	char* sitename;
	char buf[BUF_SIZE];
	int i;
	int ret;
	double* index;
	int site_index;

	// for compression
	const int shuffle = 1;
    const int deflate = 1;
    const int deflate_level = 9;

	const size_t latlon_index[] = { 0 };

	const char modelname[] = "3D-CMCC-CNR-BGC";

	enum
	{
		PIAB = 0
		, FASY
		, PISY
		, PIPI

		, SPECIES_COUNT
	};

	struct
	{
		char* standard_name;
		char* long_name;
	}
	species [SPECIES_COUNT] =
	{
		{ "piab", "Picea Abies" }
		, { "fasy", "Fagus Sylvatica" }
		, { "pisy", "Pinus Sylvestris" }
		, { "pipi", "Pinus Pinaster" }
	};

	struct
	{
		char* model_name;
		char* isimip_name;
		double lat;
		double lon;
		int species;
	}
	sites [] =
	{
		{ "Bily_Kriz", "bily_kriz", 49.3f, 18.32f, PIAB  }
		, { "Collelongo", "collelongo", 41.85f, 13.59f, FASY }
		, { "Hyytiala", "hyytiala", 61.84f, 24.29f, PISY }
		, { "Kroof", "kroof", 48.25f, 11.10f, FASY }
		, { "LeBray", "le_bray", 44.72f, -0.77f, PIPI  }
		, { "Peitz", "peitz", 51.92f, 14.35f, PISY  }
		, { "Solling_beech", "solling_beech", 51.77f, 9.57f, FASY  }
		, { "Solling_spruce", "solling_spruce", 51.76f, 9.58f, PIAB  }
		, { "Soroe", "soro", 55.29f, 11.38f, FASY  }
	};

	const char *gcms[] = // is ecm for model
	{
		"hadgem2_es"
		, "ipsl_cm5a_lr"
		, "miroc_esm_chem"
		, "gfdl_esm2m"
		, "noresm1_m"
		, "miroc5"
		, "princeton"
		, "gswp3"
		, "watch"
		, "watch_wfdei_gpcc"
		, "localclim"
	};

	const char socio_econ_scenario[] = "man";

	const char sz_standard_name[] = "standard_name";
	const char sz_long_name[] = "long_name";
	const char sz_units[] = "units";
	const char sz_axis[] = "axis";

	const char sz_lat[] = "lat";
	const char sz_lon[] = "lon";
	const char sz_time[] = "time";

	const char sz_lat_long[] = "latitude";
	const char sz_lon_long[] = "longitude";

	const char sz_lat_degrees[] = "degrees_north";
	const char sz_lon_degrees[] = "degrees_east";

	const char sz_calendar[]= "calendar";
	const char sz_calendar_type[]= "proleptic_gregorian";

	const char sz_months_since[] = "months since 1661-01-01 00:00:00";

	const char sz_missing_value[] = "missing_value";
	
	const char sz_title[] = "title";
	const char sz_title_desc[] = "3D-CMCC-CNR-BGC";

	const char sz_contact[] = "contact";
	const char sz_contact_desc[] = "Alessio Collalti (alessio.collalti@cmcc.it, alessio.collalti@isafom.cnr.it) - "
									"Alessio Ribeca (alessio.ribeca@cmcc.it, a.ribeca@unitus.it)"
	;

	const char sz_institution[] = "institution";
	const char sz_institution_desc[] =	"Foundation euroMediterranean Center on Climate Change (CMCC) Division Impacts on Agriculture, Forest and Ecosystem Services (IAFES) - "
										"CNR-ISAFOM National Research Council of Italy Institute for Agricultural and Forestry Systems in the Mediterranean(ISAFOM)"
	;

	ret = 0; // default to err
	index = NULL;
	
	assert(dataset);

	index = malloc(dataset->rows_count*sizeof*index);
	if ( ! index )
	{
		puts(err_out_of_memory);
		return 0;
	}

	if ( ANNUAL_DATASET_TYPE == dataset->type )
	{
		for ( i = 0; i < dataset->rows_count; ++i )
		{
			index[i] = dataset->start_year - 1661 + i;
		}
	}

	// get sitename
	sitename = dataset->sitename;
	for ( i = 0; i < SIZEOF_ARRAY(sites); ++i )
	{
		if ( ! string_compare_i(sitename, sites[i].model_name) )
		{
			sitename = sites[i].isimip_name;
			site_index = i;
			break;
		}
	}
	assert(site_index < SIZEOF_ARRAY(sites));

	for ( i = 0; i < dataset->columns_count; ++i )
	{
		char buf2[BUF_SIZE];
		int j;
		int nc_id, lon_dim_id, lat_dim_id, time_dim_id;
		int lon_id, lat_id, time_id, var_id;
		int var_dim_ids[3];
		int year;
		int years_loop;
		
		// skip var
		if ( ANNUAL_DATASET_TYPE == dataset->type )
		{
			if (	(ANNUAL_STEM_C == i)
					|| (ANNUAL_MAX_FROOT_C == i)
					|| (ANNUAL_CROOT_C == i)
					|| (ANNUAL_BRANCH_C == i)
					|| (ANNUAL_FRUIT_C == i)
				)
			{
				continue;
			}			
		}
		// DAILY_DATASET_TYPE
		else
		{
			if (	
					(DAILY_LAI == i)
					|| (DAILY_DELTA_STEM_C == i)
					|| (DAILY_DELTA_BRANCH_C == i)
					|| (DAILY_DELTA_FRUIT_C == i)
					|| (DAILY_DELTA_CROOT_C == i)
					|| (DAILY_FROOT_AR == i)
					|| (DAILY_CROOT_AR == i)
				)
			{
				continue;
			}
		}

		if ( ANNUAL_DATASET_TYPE == dataset->type )
		{
			years_loop = 1;
		}
		else
		// DAILY_DATASET_TYPE
		{
			years_loop = ((dataset->end_year - dataset->start_year + 1) / 10) + 1;
		}

		for ( year = 0; year < years_loop; ++year )
		{
			int start_year;
			int end_year;
			int rows_count;
			int start_data;
			
			if ( ANNUAL_DATASET_TYPE == dataset->type )
			{
				start_year = dataset->start_year;
				end_year = dataset->end_year;
				rows_count = dataset->rows_count;
				start_data = 0;
			}
			else
			// DAILY_DATASET_TYPE
			{
				int days_count;
				
				start_year = dataset->start_year + year * 10;
				end_year = start_year + 10;
				if ( end_year > dataset->end_year )
				{
					end_year = dataset->end_year;
					++end_year;
				}

				// compute days from 1661
				days_count = 0;
				for ( j = 1661; j < start_year; ++j )
				{
					days_count += (IS_LEAP_YEAR(j) ? 366: 365);
				}

				// compute rows_count
				rows_count = 0;
				for ( j = start_year; j < end_year; ++j )
				{
					rows_count += (IS_LEAP_YEAR(j) ? 366 : 365); 
				}			
				
				for ( j = 0; j < rows_count; ++j )
				{
					index[j] = days_count + j;
				}
				
				// compute start data
				start_data = 0;
				for ( j = dataset->start_year; j < start_year; ++j )
				{
					start_data += (IS_LEAP_YEAR(j) ? 366 : 365); 
				}
				--end_year;
			}
			
			// get var name
			j = sprintf(buf2, (ANNUAL_DATASET_TYPE == dataset->type) ? annual_vars[i].standard_name : daily_vars[i].standard_name);
			if ( (ANNUAL_DATASET_TYPE == dataset->type) || daily_vars[i].add_species  )
			{
				sprintf(buf2+j, "_%s", species[sites[site_index].species].standard_name);
			}
			
			// compute filename
			if ( folder )
				j = sprintf(buf, "%s/", folder);
			else
				j = sprintf(buf, "%s", dataset->path ? dataset->path : "");

			// <modelname>_<gcm>_<climate_scenario>_<soc-scenario>_<co2sens_scenarios>_<variable>_<region>_<timestep>_<start_year>_<end_year>.nc4
			/*
				<climate_scenario>
				historial = hist
				rcp come sono

				<soc -scenario>
				2005soc = var
				nosoc = off


				<co2sens-scenario>
				co2 = on
				2005co2 = var
			*/
			{
				char* climate_scenario;
				char* soc_scenario;
				char* co2sens_scenarios;

				if ( string_compare_i(dataset->clim_scenario, "hist") )
				{
					climate_scenario = "historical";
				}
				else
				{
					climate_scenario = dataset->clim_scenario;
				}

				if ( ! string_compare_i(dataset->exp, "2a")
						|| ! string_compare_i(dataset->exp, "local")
						|| ! string_compare_i(dataset->exp, "ft")
					)
				{
					if ( ! string_compare_i(dataset->co2_type, "var") )
					{
						soc_scenario = "man";
					}
					else
					{
						soc_scenario = "nat";
					}
				}
				else
				{
					if ( ! string_compare_i(dataset->co2_type, "var") )
					{
						soc_scenario = "2005soc";
					}
					else
					{
						soc_scenario = "off";
					}
				}

				if ( ! string_compare_i(dataset->exp, "2a")
						|| ! string_compare_i(dataset->exp, "local")
						|| ! string_compare_i(dataset->exp, "ft")
					)
				{
					if ( ! string_compare_i(dataset->co2_type, "var") )
					{
						co2sens_scenarios = "noco2";
					}
					else
					{
						co2sens_scenarios = "co2";
					}
				}
				else
				{
					if ( ! string_compare_i(dataset->co2_type, "var") )
					{
						co2sens_scenarios = "2005c02";
					}
					else
					{
						co2sens_scenarios = "c02";
					}
				}

				sprintf(buf+j, "%s_%s_%s_%s_%s_%s_%s_%s_%d_%d.nc4"
									, modelname
									, gcms[dataset->esm]
									, climate_scenario
									, soc_scenario
									, co2sens_scenarios
									, buf2 // var
									, dataset->sitename
									, (ANNUAL_DATASET_TYPE == dataset->type) ? "annual" : "daily"
									, start_year
									, end_year
				);
			}
			
			lowercase(buf);
			
			// convert INVALID_VALUE TO NC_MISSING_VALUE
			for ( j = 0; j < dataset->rows_count; ++j )
			{
				if ( IS_INVALID_VALUE(dataset->vars[i][j]) )
				{
					dataset->vars[i][j] = (float)NC_MISSING_VALUE;
				}
			}

			printf("- creating %s...", buf);

			// create nc file
			if ( (ret = nc_create(buf, NC_CLOBBER | NC_NETCDF4, &nc_id)) )
				goto err;

			// define dims
			if ( (ret = nc_def_dim(nc_id, sz_time, rows_count, &time_dim_id)) )
				goto err;
			if ( (ret = nc_def_dim(nc_id, sz_lon, 1, &lon_dim_id)) )
				goto err;
			if ( (ret = nc_def_dim(nc_id, sz_lat, 1, &lat_dim_id)) )
				goto err;
			
			// define vars
			if ( (ret = nc_def_var(nc_id, sz_time, NC_DOUBLE, 1, &time_dim_id, &time_id)) )
				goto err;
			if ( (ret = nc_def_var(nc_id, sz_lon, NC_DOUBLE, 1, &lon_dim_id, &lon_id)) )
				goto err;
			if ( (ret = nc_def_var(nc_id, sz_lat, NC_DOUBLE, 1, &lat_dim_id, &lat_id)) )
				goto err;
			
			var_dim_ids[0] = time_dim_id;
			var_dim_ids[1] = lat_dim_id;
			var_dim_ids[2] = lon_dim_id;
			if ( (ret = nc_def_var(nc_id, buf2, NC_FLOAT, 3, var_dim_ids, &var_id)) )
				goto err;

			// enable compression
			if ( (ret = nc_def_var_deflate(nc_id, lat_id, shuffle, deflate, deflate_level)) )
				goto err;
			if ( (ret = nc_def_var_deflate(nc_id, lon_id, shuffle, deflate, deflate_level)) )
				goto err;
			if ( (ret = nc_def_var_deflate(nc_id, var_id, shuffle, deflate, deflate_level)) )
				goto err;
			if ( (ret = nc_def_var_deflate(nc_id, time_id, shuffle, deflate, deflate_level)) )
				goto err;

			// put attributes for lat
			if ( (ret = nc_put_att_text(nc_id, lat_id, sz_standard_name, strlen(sz_lat_long), sz_lat_long)) )
				goto err;
			if ( (ret = nc_put_att_text(nc_id, lat_id, sz_long_name, strlen(sz_lat_long), sz_lat_long)) )
				goto err;
			if ( (ret = nc_put_att_text(nc_id, lat_id, sz_units, strlen(sz_lat_degrees), sz_lat_degrees)) )
				goto err;
			if ( (ret = nc_put_att_text(nc_id, lat_id, sz_axis, 1, "Y")) )
				goto err;

			// put attributes for lon
			if ( (ret = nc_put_att_text(nc_id, lon_id, sz_standard_name, strlen(sz_lon_long), sz_lon_long)) )
				goto err;
			if ( (ret = nc_put_att_text(nc_id, lon_id, sz_long_name, strlen(sz_lon_long), sz_lon_long)) )
				goto err;
			if ( (ret = nc_put_att_text(nc_id, lon_id, sz_units, strlen(sz_lon_degrees), sz_lon_degrees)) )
				goto err;
			if ( (ret = nc_put_att_text(nc_id, lon_id, sz_axis, 1, "X")) )
				goto err;

			// put attributes for time
			if ( (ret = nc_put_att_text(nc_id, time_id, sz_standard_name, strlen(sz_time), sz_time)) )
				goto err;
			sprintf(buf2, "%s since 1661-01-01 00:00:00", (ANNUAL_DATASET_TYPE == dataset->type) ? "years" : "days"); 
			if ( (ret = nc_put_att_text(nc_id, time_id, sz_units, strlen(buf2), buf2)) )
				goto err;
			if ( (ret = nc_put_att_text(nc_id, time_id, sz_calendar, strlen(sz_calendar_type), sz_calendar_type)) )
				goto err;
			if ( (ret = nc_put_att_text(nc_id, time_id, sz_axis, 1, "T")) )
				goto err;
			if ( (ret = nc_put_att_text(nc_id, time_id, sz_long_name, strlen(sz_time), sz_time)) )
				goto err;

			// put attributes for var
			j = sprintf(buf2, (ANNUAL_DATASET_TYPE == dataset->type) ? annual_vars[i].standard_name : daily_vars[i].standard_name);
			if ( (ANNUAL_DATASET_TYPE == dataset->type) || daily_vars[i].add_species  )
			{
				sprintf(buf2+j, "_%s", species[sites[site_index].species].standard_name);
			}
			if ( (ret = nc_put_att_text(nc_id, var_id, sz_standard_name, strlen(buf2), buf2)) )
				goto err;

			j = sprintf(buf2, (ANNUAL_DATASET_TYPE == dataset->type) ? annual_vars[i].standard_name : daily_vars[i].long_name);
			if ( (ANNUAL_DATASET_TYPE == dataset->type) || daily_vars[i].add_species  )
			{
				sprintf(buf2+j, " %s", species[sites[site_index].species].long_name);
			}
			if ( (ret = nc_put_att_text(nc_id, var_id, sz_long_name, strlen(buf2), buf2)) )
				goto err;

			sprintf(buf2, (ANNUAL_DATASET_TYPE == dataset->type) ? annual_vars[i].unit : daily_vars[i].unit);
			if ( (ret = nc_put_att_text(nc_id, var_id, sz_units, strlen(buf2), buf2)) )
				goto err;

			{
				float v;

				v = (float)NC_MISSING_VALUE;
				if ( (ret = nc_put_att_float(nc_id, var_id, sz_missing_value, NC_FLOAT, 1, &v)) )
					goto err;
				if ( (ret = nc_put_att_float(nc_id, var_id, _FillValue, NC_FLOAT, 1, &v)) )
					goto err;
			}

			// set global attributes
			if ( (ret = nc_put_att_text(nc_id, NC_GLOBAL, sz_title, strlen(sz_title_desc), sz_title_desc)) )
				goto err;

			if ( (ret = nc_put_att_text(nc_id, NC_GLOBAL, sz_contact, strlen(sz_contact_desc), sz_contact_desc)) )
				goto err;

			if ( (ret = nc_put_att_text(nc_id, NC_GLOBAL, sz_institution, strlen(sz_institution_desc), sz_institution_desc)) )
				goto err;

			// end "define" mode
			if ( (ret = nc_enddef(nc_id)) )
				goto err;

			// put data
			if ( (ret = nc_put_var_double(nc_id, time_id, index)) )
				goto err;
			if ( (ret = nc_put_var1_double(nc_id, lon_id, latlon_index, &sites[site_index].lon)) )
				goto err;
			if ( (ret = nc_put_var1_double(nc_id, lat_id, latlon_index, &sites[site_index].lat)) )
				goto err;
		
			if ( (ret = nc_put_var_float(nc_id, var_id, dataset->vars[i]+start_data)) )
				goto err;

			// close file
			if ( (ret = nc_close(nc_id)) )
				goto err;

			puts("ok");

			// create monthly LAI_PROJ on last loop
			// so we can reuse vars !
			if (	(i == dataset->columns_count-1)
					&& (DAILY_DATASET_TYPE == dataset->type)
					&& (year == years_loop - 1) )
			{
				rows_count = (dataset->end_year - dataset->start_year + 1) * 12;

				{
					char* climate_scenario;
					char* soc_scenario;
					char* co2sens_scenarios;

					if ( string_compare_i(dataset->clim_scenario, "hist") )
					{
						climate_scenario = "historical";
					}
					else
					{
						climate_scenario = dataset->clim_scenario;
					}

					if ( ! string_compare_i(dataset->exp, "2a")
							|| ! string_compare_i(dataset->exp, "local")
							|| ! string_compare_i(dataset->exp, "ft")
						)
					{
						if ( ! string_compare_i(dataset->co2_type, "var") )
						{
							soc_scenario = "man";
						}
						else
						{
							soc_scenario = "nat";
						}
					}
					else
					{
						if ( ! string_compare_i(dataset->co2_type, "var") )
						{
							soc_scenario = "2005soc";
						}
						else
						{
							soc_scenario = "off";
						}
					}

					if ( ! string_compare_i(dataset->exp, "2a")
							|| ! string_compare_i(dataset->exp, "local")
							|| ! string_compare_i(dataset->exp, "ft")
						)
					{
						if ( ! string_compare_i(dataset->co2_type, "var") )
						{
							co2sens_scenarios = "noco2";
						}
						else
						{
							co2sens_scenarios = "co2";
						}
					}
					else
					{
						if ( ! string_compare_i(dataset->co2_type, "var") )
						{
							co2sens_scenarios = "2005c02";
						}
						else
						{
							co2sens_scenarios = "c02";
						}
					}

					// get var name
					j = sprintf(buf2, "lai_");
					sprintf(buf2+j, "_%s", species[sites[site_index].species].standard_name);

					// compute filename
					if ( folder )
						j = sprintf(buf, "%s/", folder);
					else
						j = sprintf(buf, "%s", dataset->path ? dataset->path : "");
					sprintf(buf+j, "%s_%s_%s_%s_%s_%s_%s_%s_%d_%d.nc4"
										, modelname
										, gcms[dataset->esm]
										, climate_scenario
										, soc_scenario
										, co2sens_scenarios
										, buf2 // var
										, dataset->sitename
										, "monthly"
										, dataset->start_year
										, dataset->end_year
					);
				}
				lowercase(buf);

				// compute mean re-using a dataset var
			{	
				int year;
				
				j = 0; // index
				for ( year = 0; year < rows_count; ++year ) 
				{
					int month;

					index[0] = (dataset->start_year - 1661) * 12;
					for ( month = 0; month < 12; ++month )
					{
						int days;
						int row;
						int n;
						float mean;

						const int days_per_month[] =
								{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

						days = days_per_month[month];

						// fix for leap february
						if ( (1 == month) && IS_LEAP_YEAR(dataset->start_year + year) )
						{
							++days;
						}

						mean = 0.;
						n = 0;
						for ( row = 0; row < days; ++row, ++j )
						{
							if ( ! IS_INVALID_VALUE(dataset->vars[DAILY_LAI][j]) )
							{
								mean += dataset->vars[DAILY_LAI][j];
								++n;
							}
						}

						if ( n )
						{
							mean /= n;
						}
						else
						{
							mean = (float)NC_MISSING_VALUE;
						}
						dataset->vars[DAILY_RAR][(year*12)+month] = mean;

						index[month] = index[0] + month;
					}
				}
			}
				
				printf("- creating %s...", buf);		

				// create nc file
				if ( (ret = nc_create(buf, NC_CLOBBER | NC_NETCDF4, &nc_id)) )
					goto err;

				// define dims
				if ( (ret = nc_def_dim(nc_id, sz_time, rows_count, &time_dim_id)) )
					goto err;
				if ( (ret = nc_def_dim(nc_id, sz_lon, 1, &lon_dim_id)) )
					goto err;
				if ( (ret = nc_def_dim(nc_id, sz_lat, 1, &lat_dim_id)) )
					goto err;		
				
				// define vars
				if ( (ret = nc_def_var(nc_id, sz_time, NC_DOUBLE, 1, &time_dim_id, &time_id)) )
					goto err;
				if ( (ret = nc_def_var(nc_id, sz_lon, NC_DOUBLE, 1, &lon_dim_id, &lon_id)) )
					goto err;
				if ( (ret = nc_def_var(nc_id, sz_lat, NC_DOUBLE, 1, &lat_dim_id, &lat_id)) )
					goto err;
				

				var_dim_ids[0] = time_dim_id; // time goes first
				var_dim_ids[1] = lat_dim_id;
				var_dim_ids[2] = lon_dim_id;
				j = sprintf(buf2, daily_vars[DAILY_LAI].standard_name);
				if ( daily_vars[DAILY_LAI].add_species )
				{
					sprintf(buf2+j, "_%s", species[sites[site_index].species].standard_name); 
				}
				if ( (ret = nc_def_var(nc_id, buf2, NC_FLOAT, 3, var_dim_ids, &var_id)) )
					goto err;

				// enable compression
				if ( (ret = nc_def_var_deflate(nc_id, lat_id, shuffle, deflate, deflate_level)) )
					goto err;
				if ( (ret = nc_def_var_deflate(nc_id, lon_id, shuffle, deflate, deflate_level)) )
					goto err;
				if ( (ret = nc_def_var_deflate(nc_id, var_id, shuffle, deflate, deflate_level)) )
					goto err;
				if ( (ret = nc_def_var_deflate(nc_id, time_id, shuffle, deflate, deflate_level)) )
					goto err;

				// put attributes for lat
				if ( (ret = nc_put_att_text(nc_id, lat_id, sz_standard_name, strlen(sz_lat_long), sz_lat_long)) )
					goto err;
				if ( (ret = nc_put_att_text(nc_id, lat_id, sz_long_name, strlen(sz_lat_long), sz_lat_long)) )
					goto err;
				if ( (ret = nc_put_att_text(nc_id, lat_id, sz_units, strlen(sz_lat_degrees), sz_lat_degrees)) )
					goto err;
				if ( (ret = nc_put_att_text(nc_id, lat_id, sz_axis, 1, "Y")) )
					goto err;

				// put attributes for lon
				if ( (ret = nc_put_att_text(nc_id, lon_id, sz_standard_name, strlen(sz_lon_long), sz_lon_long)) )
					goto err;
				if ( (ret = nc_put_att_text(nc_id, lon_id, sz_long_name, strlen(sz_lon_long), sz_lon_long)) )
					goto err;
				if ( (ret = nc_put_att_text(nc_id, lon_id, sz_units, strlen(sz_lon_degrees), sz_lon_degrees)) )
					goto err;
				if ( (ret = nc_put_att_text(nc_id, lon_id, sz_axis, 1, "X")) )
					goto err;

				// put attributes for time
				if ( (ret = nc_put_att_text(nc_id, time_id, sz_standard_name, strlen(sz_time), sz_time)) )
					goto err;
				if ( (ret = nc_put_att_text(nc_id, time_id, sz_units, strlen(sz_months_since), sz_months_since)) )
					goto err;
				if ( (ret = nc_put_att_text(nc_id, time_id, sz_calendar, strlen(sz_calendar_type), sz_calendar_type)) )
					goto err;
				if ( (ret = nc_put_att_text(nc_id, time_id, sz_axis, 1, "T")) )
					goto err;
				if ( (ret = nc_put_att_text(nc_id, time_id, sz_long_name, strlen(sz_time), sz_time)) )
					goto err;

				// put attributes for var
				j = sprintf(buf2, (ANNUAL_DATASET_TYPE == dataset->type) ? annual_vars[i].standard_name : daily_vars[i].standard_name);
				if ( (ANNUAL_DATASET_TYPE == dataset->type) || daily_vars[i].add_species  )
				{
					sprintf(buf2+j, "_%s", species[sites[site_index].species].standard_name);
				}
				if ( (ret = nc_put_att_text(nc_id, var_id, sz_standard_name, strlen(buf2), buf2)) )
					goto err;

				j = sprintf(buf2, (ANNUAL_DATASET_TYPE == dataset->type) ? annual_vars[i].standard_name : daily_vars[i].long_name);
				if ( (ANNUAL_DATASET_TYPE == dataset->type) || daily_vars[i].add_species  )
				{
					sprintf(buf2+j, " %s", species[sites[site_index].species].long_name);
				}
				if ( (ret = nc_put_att_text(nc_id, var_id, sz_long_name, strlen(buf2), buf2)) )
					goto err;

				sprintf(buf2, (ANNUAL_DATASET_TYPE == dataset->type) ? annual_vars[i].unit : daily_vars[i].unit);
				if ( (ret = nc_put_att_text(nc_id, var_id, sz_units, strlen(buf2), buf2)) )
					goto err;

				{
					float v;

					v = (float)NC_MISSING_VALUE;
					if ( (ret = nc_put_att_float(nc_id, var_id, sz_missing_value, NC_FLOAT, 1, &v)) )
						goto err;
					if ( (ret = nc_put_att_float(nc_id, var_id, _FillValue, NC_FLOAT, 1, &v)) )
						goto err;
				}

				// set global attributes
				if ( (ret = nc_put_att_text(nc_id, NC_GLOBAL, sz_title, strlen(sz_title_desc), sz_title_desc)) )
					goto err;

				if ( (ret = nc_put_att_text(nc_id, NC_GLOBAL, sz_contact, strlen(sz_contact_desc), sz_contact_desc)) )
					goto err;

				if ( (ret = nc_put_att_text(nc_id, NC_GLOBAL, sz_institution, strlen(sz_institution_desc), sz_institution_desc)) )
					goto err;

				// end "define" mode
				if ( (ret = nc_enddef(nc_id)) )
					goto err;

				// put data
				if ( (ret = nc_put_var_double(nc_id, time_id, index)) )
					goto err;
				if ( (ret = nc_put_var1_double(nc_id, lon_id, latlon_index, &sites[site_index].lon)) )
					goto err;
				if ( (ret = nc_put_var1_double(nc_id, lat_id, latlon_index, &sites[site_index].lat)) )
					goto err;
				if ( (ret = nc_put_var_float(nc_id, var_id, dataset->vars[DAILY_RAR])) )
					goto err;

				// close file
				if ( (ret = nc_close(nc_id)) )
					goto err;

				puts("ok");
			}
		}
	}

	if ( index ) free(index);
	return 1;

err:
	printf("error - %s\n", nc_strerror(ret));
	if ( index ) free(index);
	return 0;
#undef NC_MISSING_VALUE
#undef BUF_SIZE
}
