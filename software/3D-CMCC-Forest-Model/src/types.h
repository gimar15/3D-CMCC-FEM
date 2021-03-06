/* types.h */
#ifndef TYPES_H
#define TYPES_H

/* precision */
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "constants.h"


#define NO_DATA -9999



 /* enums */

typedef enum {
	F = 0,      //forest
	Z          //crop
} eLanduse;



/* enums */
/*
typedef enum {
	D = 0,      //deciduous
	E,          //evergreen
} ePhenology;
*/

/* */
typedef enum {
	T = 0,      //Timber
	C          //Coppice
} eManagement;

/* */
enum {
	JANUARY,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER,

	MONTHS
};

/* */
//used in daily simulation
typedef struct{
	int n_days;
	PREC solar_rad;
	PREC tavg;	/* (deg C) daily average air temperature */
	PREC tmax;	/* (deg C) daily maximum air temperature */
	PREC tmin;	/* (deg C) daily minimum air temperature */
	PREC tday;	/* (deg C) daylight average air temperature */
	PREC tnight;	/* (deg C) nightime average air temperature */
	PREC vpd;
	PREC ts_f;
	PREC rain;
	PREC swc;
	PREC ndvi_lai;
	PREC daylength;
	PREC thermic_sum; //daily thermic sum
	PREC tsoil;
}MET_DAILY_DATA;

/* */
typedef struct {

	int n_days;
	int month;
	PREC solar_rad;
	PREC tavg;	/* (deg C) daily average air temperature */
	PREC tmax;	/* (deg C) daily maximum air temperature */
	PREC tmin;	/* (deg C) daily minimum air temperature */
	PREC tday;	/* (deg C) daylight average air temperature */
	PREC tnight;	/* (deg C) nightime average air temperature */
	PREC vpd;
	PREC ts_f;
	PREC rain;
	PREC swc;
	PREC ndvi_lai;
	PREC daylength;
	PREC thermic_sum; //monthly thermic sum NOT USED IN MONTHLY SIMUALATION
	MET_DAILY_DATA d[31];

} MET_DATA;

/* */
typedef struct {
	MET_DATA m[MONTHS];
	int year;
} YOS; // YEARS OF SIMULATION

// Struct representing site.txt content
typedef struct
{
	char sitename[1024];
	float lat,
	lon,
	elev,
	Y,
	co2Conc,
	initialLitter,
	min_frac_maxasw,  //wilting point
	//maxAsw,
	//minAsw,
	clay_perc,
	silt_perc,
	sand_perc,
	bulk_dens,
	soil_depth,
	fr,
	fn0,
	fnn,
	m0,
	sN,
	//following Nolè et al 2009
	rlai,
	slai,
	qsoil,
	ksoil,
	p0,
	cutTree;
} site_t;


// Struct representing settings.txt content
typedef struct
{
	char version,
		spatial, // must be 's' or 'u' (spatial or unspatial)
		time,  // must be 'm' or 'd' (monthly or daily)
		presence; // must be 't' or 'p' (total or percentage)

	char daymet[3];

	float sizeCell,
	//dominant,
	//dominated,
	//subdominated,
	tree_layer_limit,
	soil_layer,
	min_layer_cover,
	max_layer_cover,
	avdbh_sapling,
	lai_sapling,
	height_sapling,
	ws_sapling,
	wr_sapling,
	wf_sapling,
	light_estab_very_tolerant,
	light_estab_tolerant,
	light_estab_intermediate,
	light_estab_intolerant,
	maxlai,
	defaultlai,
	gdd_basis,
	maxdays,
	maxrg,
	maxtavg,
	maxvpd,
	maxprecip,
	switchtounspatial;

} settings_t;




/* */
enum {

	/*valori relativi alla specie*/
	/* !!!!! NON SPOSTARE !!!!!!*/
	/* serve questo ordine per l'importazione, vedere species_values dentro matrix.c */

	LIGHT_TOL = 0,

	PHENOLOGY,                  //PHENOLOGY 0=deciduous, 1=evergreen


	ALPHA,                      // Canopy quantum efficiency (molC/molPAR)
	EPSILONgCMJ,               // Light Use Efficiency  (gC/MJ)(used if ALPHA is not available)
	//Y,                          // Assimilate use efficiency-Respiration rate-GPP/NP
	//EPSILONgCMJ,                // = ALPHA * GC_MOL / MOLPAR_MJ = gC/MJ


	K,                          //Extinction coefficient for absorption of PAR by canopy for Quercus cerris L. (A. Cutini, Ann Sci For, 1996)

	ALBEDO,


	//LEAF AREA INDEX
	LAIGCX,                     //LAI for maximum canopy conductance
	LAIMAXINTCPTN,              //LAI for maximum rainfall interception
	MAXINTCPTN,                 //Maximum proportion of rainfall interception evaporated from canopy for Quercus spp Breuer et al 2003


	//SPECIFIC LEAF AREA 3PG
	SLA0,                       //Specific Leaf Area at age 0 (m^2/kg)
	SLA1,                       //Specific Laef Area for mature leaves (m^2/kg)
	TSLA,                       //Age at which Specific Leaf Area = (SLA0 + SLA1)/2 (years)

	//SPECIFIC LEAF AREA 3DVTModel
	SLA,                         //Specific Leaf Area cm^2/g

	//FRACTION BRANCH-BARK
	FRACBB0,                    //Branch and Bark fraction at age 0 (m^2/kg)
	FRACBB1,                    //Branch and Bark fraction for mature stands (m^2/kg)
	TBB,                        //Age at which fracBB = (FRACBB0 + FRACBB1 )/ 2

	//MASS DENSITY
	RHOMIN,                     //Minimum Basic Density for young Trees
	RHOMAX,                     //Maximum Basic Density for young Trees (Ferrara-Nolè)
	TRHO,                       //Age at which rho = (RHOMIN + RHOMAX )/2
	FRESHMAT,                   //Conversion from Drymatter to Freshmatter

	//VPD
	COEFFCOND,                  //Define stomatal responsee to VPD in m/sec
	BLCOND,                     //Canopy Boundary Layer conductance
	MAXCOND,                    //Maximum Canopy Conductance in m/sec

	//AGE
	MAXAGE,                         //Determines rate of "physiological decline" of forest
	RAGE,                       //Relative Age to give fAGE = 0.5
	NAGE,                       //Power of relative Age in function for Age
	//AGE for SHOOTS
	MAXAGE_S,
	RAGE_S,                       //Relative Age to give fAGE = 0.5
	NAGE_S,                       //Power of relative Age in function for Age

	//TEMPERATURE
	GROWTHTMIN,                 //Minimum temperature for growth
	GROWTHTMAX,                 //Maximum temperature for growth
	GROWTHTOPT,                 //Optimum temperature fro growth
	GROWTHSTART,                //Thermic sum  value for starting growth in °C
	GROWTHEND,                  //Thermic sum  value for ending growth in °C
	MINDAYLENGTH,               //minimum day length for phenology

	//SOIL WATER
	SWPOPEN,
	SWPCLOSE,
	SWCONST,                    //Costant in Soil Water modifier vs Moist Ratio
	SWPOWER,                    //Power in Soil Water modifier vs Moist Ratio

	//BIOMASS PARTITIONING for timber
	PFS2,                       //Foliage:Stem Partitioning Ratio @ D = 2 cm
	PFS20,                      //Foliage:Stem Partitioning Ratio @ D = 20 cm
	PRX,                        //Maximum fraction of NPP to Roots
	PRN,                        //Minimum fraction of NPP to Roots

	//BIOMASS PARTITIONING for coppice
	PFS2_C,                      //Foliage:Stem Partitioning Ratio @ D = 2 cm
	PFS20_C,                      //Foliage:Stem Partitioning Ratio @ D = 20 cm
	PRX_C,                        //Maximum fraction of NPP to Roots
	PRN_C,                        //Minimum fraction of NPP to Roots



	//BIOMASS PARTITIONING CTEM
	OMEGA_CTEM,                        //ALLOCATION PARAMETER
	S0CTEM,                           //PARAMETER CONTROLLING ALLOCATION TO STEM
	R0CTEM,                           //PARAMETER CONTROLLING ALLOCATION TO ROOT
	F0CTEM,                           //PARAMETER CONTROLLING ALLOCATION TO FOLIAGE
	RES0CTEM,                       //PARAMETER CONTROLLING ALLOCATION TO RESERVE
	EPSILON_CTEM,                     //ALLOCATION PARAMETER IN (Kgcm^2)^-0.6
	KAPPA,                            //ALLOCATION PARAMETER DIMENSIONLESS
	MIN_R0CTEM,                       //MINIMUM RATE TO ROOT AT THE FIRST YEAR AFTER COPPICING
	MAX_S0CTEM,                       //MAXIMUM RATE TO STEM AT THE FIRST YEAR AFTER COPPICING
	YEARS_FOR_CONVERSION,        //years from coppicing to consider tree as a timber

	CONES_PERC,
	CONES_LIFE_SPAN,



	//FINE COARSE ROOT RATIO
	FINE_ROOT_LEAF,	//allocation new fine root C:new leaf (ratio)
	STEM_LEAF,		//allocation new stem C:new leaf (ratio)
	COARSE_ROOT_STEM,	//allocation new coarse root C:new stem (ratio)


	//BIOME C:N RATIOS
	CN_LEAVES,  //CN of leaves (kgC/kgN)
	CN_LITTER,  //CN of leaf litter (kgC/kgN)
	CN_FINE_ROOTS,  // CN of fine roots (kgC/kgN)
	CN_LIVE_WOODS,  //CN of live woods (kgC/kgN)
	CN_DEAD_WOODS,  //CN of dead woods (kgC/kgN)

	//per specie caducifoglie LITTERFALL RATE = 1 !!!!!!!!!!!!!!
	//LITTERFALL
	//FOLLOWING BIOME-BGC
	LEAF_FALL_FRAC_GROWING,		//proportions of the growing season of leaf fall
	LEAF_LIFE_SPAN,				//Leaf life span
	//GAMMAFX,                    //Maximum Litterfall rate (month^-1)
	//GAMMAF0,                    //Litterfall rate at t = 0 (month^-1)
	//TGAMMAF,                    //Age at which litterfall rate has median value

	//ROOT TURNOVER
	FINERTTOVER,                    //Average monthly fine root turnover rate
	COARSERTTOVER,                  //Average monthly coarse root turnover rate
	SAPWOODTTOVER,	                //Average yearly sapwood turnover rate
	BRANCHTTOVER,	                //Average yearly branch turnover rate
	//RTTOVER,                    //Average monthly root turnover rate



	//MORTALITY
	WSX1000,                    //Max stem mass (kg) per tree at 1000 trees/hectare
	THINPOWER,                  //Power in self-thinning rule
	MF,                         //Fraction mean single tree foliage biomass lost per dead tree
	MR,                         //Fraction mean single tree root biomass lost per dead tree
	MS,                         //Fraction mean single tree stem biomass lost per dead tree

	//ALLOMETRIC RELATIONSHIPS

	//DBHDC,                      //dbh (cm)- crown diameter (m) ratio  from cm to meter cm-->m
	//DBHDC = 20/100
	DBHDCMAX,                   //Low Density
	DBHDCMIN,                   //High Density
	SAP_A,                      //a coefficient for sapwood
	SAP_B,                      //b coefficient for sapwood
	SAP_LEAF,                   //sapwood_max leaf area ratio in pipe model
	SAP_WRES,					  //Sapwood-Reserve biomass ratio used if no Wres data are available

	HMAX,                       //Max Height in m
	DMAX,                       //Max Diameter in cm
	HPOWER,                     //Slope of Asymptotic Height from Sortie
	RPOWER,                     //Slope of Asymptotic Crown-Radius from Sortie
	b_RPOWER,
	CHPOWER,                    //Slope of Asymptotic Crown-Height from Sortie
	b_CHPOWER,

	STEMCONST_P,
	STEMPOWER_P,



	//CHAPMAN-RICHARDS relationships
	CRA,
	CRB,
	CRC,

	//CROWDING COMPETITION FUNCTION
	HDMAX,                      //Height to Base diameter ratio MAX
	HDMIN,                      //Height to Base diameter ratio MIN

	//DENSITY FUNCTION
	DENMAX,                     //Maximum density (trees/10000 m^2)
	DENMIN,                     //Minimum density (trees/10000 m^2)

	//ESTABLISHMENT
	MINPAREST,           //Minimum Monthly PAR (W/m^2 hour) for Establishment for the Dominated Layer
	MINRAIN,                    //Minimum annual Rain Precipitation for Establishment

	//SEEDS PRODUCTION
	ADULT_AGE,
	MAXSEED,                    //numero massimo semi prodotti dalla pianta (da TREEMIG)
	MASTSEED,                   //ricorrenza anni di pasciona (da TREEMIG)
	WEIGHTSEED,                 //peso frutto in g
	SEXAGE,                         //Age at Sexual Maturity
	GERMCAPACITY,               //Geminability (Lischke H. & Loffler T. J.)
	MINTEMP,                    //Minimum temperature for germination in °C
	ESTMAX,                     //Potential Establishment rate in the absence of competition

	//SEEDS PRODUCTION FROM LPJ
	FRACFRUIT,                  //Fraction of NPP to Fruit Production

	ROTATION,

	//MANAGMENT

	MINAGEMANAG,                    //Minimum age for Managment
	MINDBHMANAG,                //Minimum DBH for Managment
	AV_SHOOT,                   //Average number of shoots produced after coppicing

	/************************************************* VARIABLES *****************************************************/



	//VEG_PERIOD,


	//LIGHT
	SOLAR_RAD,                      //Solar Radiation in (MJ/m^2 day)
	NET_RAD,                        //Daily Net Solar Radiation  Q in ('MJ/m2/day') --> 'W/m2'
	RAD,                            //Monthly Solar Radiation 'MJ/m^2'
	PAR,                            //Monthly Physiological Active Radiation 'molPAR/m^2 month
	APAR,                           //Available Physiological Active Radiation 'molPAR/m^2'  for DOMINANT LAYER
	APAR_DOMINATED,                 //Available Physiological Active Radiation 'molPAR/m^2' for DOMINATED LAYER
	APAR_CAN_COVER,                 //Apar for Canopy Cover
	LIGHT_ABSORB,                   //Fraction of Light Absorbed from Domain Canopy
	LIGHT_TRASM,                    //Fraction of Light Trasmitted through Domain Canopy
	LIGHT_ABSORB_UDC,               //Fraction of Light Absorbed from Dominated Canopy



	//STRUCTURE
	AVDBH,                          //Average DBH in cm
	CROWN_DIAMETER,                 //Crown Diameter in m
	CROWN_AREA,                     //Crown Area in m^2
	CROWN_RADIUS_SORTIE,            //Crown Radius in m from Sortie Standard
	CROWN_DIAMETER_SORTIE,          //Crown Diameter in m from Sortie Standard
	CROWN_AREA_SORTIE,              //Crown Area from Sortie diameter
	CROWN_HEIGHT_SORTIE,            //Crown Height in m from Sortie Standard
	TREE_HEIGHT_SORTIE,             //Tree Height in m from Sortie function
	TREE_HEIGHT_UDC,
	TREE_HEIGHT_FL,
	TREE_HEIGHT_LPJ,                //Tree Height in m from LPJ
	CROWN_AREA_LPJ,                 //Crown Area in m^2 from LPJ
	CROWN_DIAMETER_LPJ,             //Crown Diameter in m from LPJ
	MCA,                            //Maximum Crown Area in m^2
	DBHDC_EFF,                      //Crown Diameter from DBH in function of density
	CROWN_DIAMETER_DBHDC_FUNC,      //Crown Diameter in m from DBHDC function
	CROWN_AREA_DBHDC_FUNC,          //Crown Area in m^2 from DBHDC function
	CANOPY_COVER_DBHDC_FUNC,        //Canopy Cover % of pixel covered from DBHDC function
	FREE_CANOPY_COVER_DBHDC_FUNC,   //Fraction of Dominant Layer without Dominant Canopy Cover
	CANOPY_COVER_DBHDC,
	CANOPY_COVER,                   //Canopy Cover % of pixel covered
	CANOPY_COVER_P,                 //Canopy Cover from Portoghesi Function % of pixel covered
	FREE_CANOPY_COVER_P,
	CANOPY_COVER_DOMINANT,
	CANOPY_COVER_DOMINATED,
	CANOPY_COVER_SORTIE,            //Canopy Cover % of pixel covered from Sortie Function
	CANOPY_COVER_LPJ,               //Canopy Cover % of pixel covered from LPJ
	GAP_COVER,
	TREE_HEIGHT_CR,                 //Tree Height in m from CHAPMAN-RICHARDS FUNCTION
	HD_EFF,                         //Effective HD ratio to give to Crowding Competition Function
	DEL_HEIGHT,                     //Height increment from Crowding Competition Function in m
	DEL_DBH,                        //DBH increment from Crowding Competition Function in m
	CC_TREE_HEIGHT,                 //Tree Height in m from Crowding Competition Function in m
	CC_AVDBH,                       //Average DBH from Crowding Competition Function in cm
	T_MAX,                          //Max temperature (C°)
	T_MIN,                          //Min temperature (C°)
	T_AV,                           //Average temperature (C°)
	FROST_DAYS,                     //Number of Frost Days
	RAIN,                           //Rain in mm
	MONTH_RAIN,                     //Monthly Rainfall (mm)
	RH,                             //Relative Humidity (%)
	VPD,                            //VPD (mbar)
	F_VPD,                          //VPD modifier
	//ALTER_VPD,                    //Alternative VPD
	//ALTER_F_VPD,                  //Alternative VPD Modifier
	MONTH_TRANSP,
	DAILY_TRANSP,
	FRAC_RAIN_INTERC,				//FRACTION OF RAIN INTERCEPTED
	RAIN_INTERCEPTED,
	CANOPY_CONDUCTANCE,
	EVAPOTRANSPIRATION,             //Evapotranspiration (mm)
	MONTHLY_EVAPOTRANSPIRATION,     //for WUE
	NUMBER_DENSITY,                 //Numbers of Tree per SIZECELL
	DENSITY,                        //Numbers of Tree per m^2
	TREE_AREA,                      //Average Available Area per Tree in m^2
	F_AGE,                          //AGE modifier
	F_NUTR,                         //SOIL NUTRIENT Modifer
	F_T,                            //TEMPERATURE modifier
	F_FROST,                        //FROST modifer
	F_SW,                           //SOIL WATER modifier
	F_DROUGHT,                      //SOIL DROUGHT modifier (see Duursma et al., 2008)
	F_PSI,							//SOIL WATER modifier using PSI, see Biome
	ASW,                            //available soil water per mm/ha
	PHYS_MOD,                       //Physmod
	YEARLY_PHYS_MOD,
	AVERAGE_PHYS_MOD,
	APARU,                          //"Utilisable PAR" 'mol/m^2'


	F_EVAPO,                        //Evapotranspiration modifier 5 oct 2012



	//average yearly modifiers
	AVERAGE_F_VPD,
	AVERAGE_F_NUTR,
	AVERAGE_F_T,
	AVERAGE_F_SW,



	ALPHA_C,                        //effective quantum canopy efficiency
	EPSILON,                        //Light Use Efficiency (gDM/MJ)
	RAD_INT,                        //Radiation Incerception


	//LAI
	LAI,                            //LAI (m^2/m2) 3D-CMCC Model version
	OLD_LAI,
	LAI_3PG,
	LAI_NASA_CASA,
	LAI_CTEM,
	LAI_LPJ,
	SLA_LPJ,
	SLAmkg,

	INITIAL_M_C_LAI,             //FIRST MONTH OF GROWING SEASON LAI COMPUTED BY ONE/THIRD OF PREVIOUS YEARLY BIOMASS ALLOCATED FOR DECIDUOUS  see (Schwalm et al., 2004)


	CUM_DAY_LENGTH,                 //Cumulated DayLength for recruitment
	CUM_MONTH_LENGTH,

	GPP_mol_C,                      //Gross Primary Production  molC/m^2 month
	DAILY_GPP_mol_C,                //Daily GPP on molC/m^2 day
	GPP_t_DM,                       //Gross Primary Production  tDM/ha
	GPP_g_C,                        //Gross Primary Production  gC/m^2
	DAILY_GPP_g_C,                  //Class Daily Gross Primary Production gC/m^2 day
	MONTHLY_GPP_g_C,				//Class Monthly Gross Primary Production gC/m^2 month
	STAND_GPP_g_C,                  //Monthly Stand GPP in grams of C
	STAND_GPP_t_C,                  //Monthly Stand GPP in tonnes of C
	STAND_YEARLY_GPP_g_C,           //Yearly Stand GPP in grams of C
	POINT_GPP_g_C,

	NPP,                            //Net Primary Production  tDM/area
	NPP_g_C, 						//Net Primary Production in grams of C

	AUT_RESPIRATION,				//autotrophic respiration in grams of C/m^2



	WUE,                            //Water use efficiency (gDM/mm)


	//3PG ALLOCATION FUNCTION
	PFS,                           //Foliage:Stem Partitioning Ratio
	PR,                            //Ratio to Roots
	PS,                            //Ratio to Stem
	PF,                            //Ratio to Foliage
	WF,                            //Foliage Biomass
	DEL_WF,                        //Foliage Biomass Increment
	WF_KG_M2,                      //Foliage Biomass in m^2/Kg for that CanopyCover
	WRC,                            //Root Biomass
	WRF,
	WRT,
	DEL_WR,                        //Root Biomass Increment
	WS,                            //Stem Biomass
	WS_sap,
	WS_heart,
	WRC_sap,
	WRC_heart,
	DEL_WS,                        //Stem Biomass Increment
	DEL_BB,                        //Branch and bark fraction --- currently the model doesn't accumulate it!!!!!!!
	W_SEED,                        //Seed Biomass
	DEL_TOTAL_W,                   //Total Biomass Increment
	TOTAL_W,
	DEL_Y_WS,                       //Yearly cumulated stem biomass increment
	DEL_Y_WF,                       //Yearly cumulated foliage biomass increment
	DEL_Y_WR,                       //Yearly cumulated root biomass increment
	DEL_Y_WFR,
	DEL_Y_WCR,
	DEL_Y_WRES,                      //Yearly cumulated reserve biomass increment
	DEL_Y_BB,

	//monthly partitioning-allocation
	PEAK_LAI,                      //PEAK LAI DETERMINED BUY THE PREVIOUS YEAR BIOMASS ALLOCATED INTO FOLIAGE
	PEAK_Y_LAI,                    //PEAK LAI FOR NEXT YEAR
	MAX_BIOMASS_FOLIAGE_CTEM,

	YEARLY_WF,
	YEARLY_WS,
	YEARLY_WR,


	//NASA CASA ALLOCATION FUNCTION
	LIGHT_NASA_CASA,
	ROOTS_NASA_CASA,
	STEM_NASA_CASA,
	FOLIAGE_NASA_CASA,
	BIOMASS_ROOTS_NASA_CASA,
	BIOMASS_STEM_NASA_CASA,
	BIOMASS_FOLIAGE_NASA_CASA,


	//CTEM CARBON
	//carbon biomass monthly increment
	DEL_ROOTS_TOT_CTEM,
	DEL_STEMS_CTEM,
	DEL_FOLIAGE_CTEM,
	DEL_RESERVE_CTEM,
	DEL_CONES_CTEM,
	//carbon biomass pools
	BIOMASS_ROOTS_TOT_CTEM,
	BIOMASS_ROOTS_COARSE_CTEM,
	BIOMASS_ROOTS_FINE_CTEM,
	BIOMASS_STEM_CTEM,
	BIOMASS_FOLIAGE_CTEM,
	BIOMASS_RESERVE_CTEM,
	BIOMASS_CONES_CTEM,   //only for coniferous

	//Maintenance respiration
	DAILY_LEAF_MAINT_RESP,
	NIGHTLY_LEAF_MAINT_RESP,
	TOT_DAY_LEAF_MAINT_RESP,
	FINE_ROOT_MAINT_RESP,
	STEM_MAINT_RESP,
	COARSE_ROOT_MAINT_RESP,
	TOTAL_MAINT_RESP,

	//Growth respiration
	LEAF_GROWTH_RESP,
	FINE_ROOT_GROWTH_RESP,
	STEM_GROWTH_RESP,
	COARSE_ROOT_GROWTH_RESP,
	TOTAL_GROWTH_RESP,




	//NITROGEN
	//nitrogen biomass monthly increment
	NITROGEN_DEL_ROOTS_TOT_CTEM,
	NITROGEN_DEL_STEMS_CTEM,
	NITROGEN_DEL_FOLIAGE_CTEM,
	NITROGEN_DEL_RESERVE_CTEM, //?????
	//nitrogen biomass pools
	NITROGEN_BIOMASS_ROOTS_TOT_CTEM,
	NITROGEN_BIOMASS_ROOTS_COARSE_CTEM,
	NITROGEN_BIOMASS_ROOTS_FINE_CTEM,
	NITROGEN_BIOMASS_STEM_CTEM,
	NITROGEN_BIOMASS_FOLIAGE_CTEM,
	NITROGEN_BIOMASS_RESERVE_CTEM, //?????


	CLASS_AGB,
	CLASS_BGB,


	SAPWOOD_AREA,
	SAPWOOD_PERC,
	HEARTWOOD_AREA,

	//FINE/COARSE RATIO
	FR_CR,                       //FINE-COARSE ROOT RATIO
	DEL_ROOTS_FINE_CTEM,
	DEL_ROOTS_COARSE_CTEM,


	//3PG MORTALITY FUNCTION
	WS_MAX,                         //Maximum stem mass per tree at 1000 trees/ha


	//LPJ MORTALITY FUNCTION
	AGEMORT,                        //Age probability mortality function


	DEL_LITTER,                     //perdita di foglie che vanno nella lettiera
	DEL_ROSS_FINE,                       //perdita di radici fini che vanno nella lettiera
	DEL_ROSS_COARSE,                    //perdita di radici grosse che vanno nella lettiera
	DEL_ROSS_STEM,                       //perdita di STEM che vanno nella lettiera
	DEL_ROSS_BRANCH,                    //perdita di radici grosse che vanno nella lettiera
	TOTAL_LITTER,                   //Lettiera totale
	LITTERFALL_RATE,				//daily/monthly litterfall rate from CTEM


	FRACBB,

	AV_STEM_MASS,                   //Average Stem Mass           Kg/tree
	AV_ROOT_MASS,                   //Average Root Mass           Kg/tree
	AV_FINE_ROOT_MASS,
	AV_COARSE_ROOT_MASS,
	AV_RESERVE_BIOMASS,

	BASAL_AREA,                     //Basal Area (m^2/area tree)
	STAND_BASAL_AREA,
	CROWN_HEIGHT,                   //Crown Height (m)
	PREVIOUS_VOLUME,				//previous year volume for CAI
	VOLUME,                   //Stem Volume
	TOTAL_VOLUME,
	TREE_VOLUME,                    //Single Tree Volume (m^3/area)
	IND_STEM_VOLUME,                //Individual Stem Volume for Crowding Competition Function
	CAI,                            //Current Annual Increment
	IND_CAI,                        //Individual Current Annual Increment
	MAI,                            //Mean Annual Volume Increment (m^3/area year)

	STEMCONST,

	//MONTHLY CUMULATIVE VARIABLES
	MONTHLY_NPP,                     //Yearly NPP
	MONTHLY_NPP_UDC,
	MONTHLY_NPP_FL,
	IND_MONTHLY_NPP,                 //Individual NPP
	CUM_MONTHLY_NPP,                 //Sum of all years NPP (included simulation years)
	MONTHLY_GPP_G_C,                 //Yearly GPP
	MONTHLY_POINT_GPP_G_C,
	MONTHLY_RAIN,                    //Yearly Rain


	//YEARLY CUMULATIVE VARIABLES
	YEARLY_NPP,                     //Yearly NPP
	YEARLY_NPP_UDC,
	YEARLY_NPP_FL,
	IND_YEARLY_NPP,                 //Individual NPP
	CUM_YEARLY_NPP,                 //Sum of all years NPP (included simulation years)
	YEARLY_GPP_G_C,                 //Yearly GPP
	YEARLY_POINT_GPP_G_C,
	YEARLY_RAIN,                    //Yearly Rain

	//MONTHLY PHENOLOGY
	FRAC_MONTH_FOLIAGE_REMOVE,
	MONTH_FRAC_FOLIAGE_REMOVE,

	//DAILY PHENOLOGY
	FRAC_DAY_FOLIAGE_REMOVE,	//number of leaf fall days/tot number of veg days
	DAY_FRAC_FOLIAGE_REMOVE, 	//number of leaf fall days

	THERMIC_SUM_FOR_END_VEG, //thermic sum at the end of leaf fall period


	FOLIAGE_REDUCTION_RATE,

	DAILY_FOLIAGE_BIOMASS_TO_REMOVE,





	//SAPLINGS

	LAI_SAPLING,
	AVDBH_SAPLING,
	TREE_HEIGHT_SAPLING,
	WF_SAPLING,
	WR_SAPLING,
	WS_SAPLING,


	PERC,


	VALUES
};

/* enum for counters */
enum {

	N_TREE,                         //Numbers of Tree per cell
	N_STUMP,                        //Number of stumps for coppice
	N_SEED,                        //Seeds number for cell
	DEL_STEMS,                      //Dead Trees
	REM_TREES,                      //Yearly Total dead-removed Trees
	CUT_TREES,                      //Cut trees for Management
	TOT_REM_TREES,                  //Total dead-removed Trees from the beginning of simulation

	N_SAPLINGS,
	TREE_AGE_SAP,
	N_TREE_SAP,

	VEG_UNVEG,
	VEG_MONTHS,
	VEG_DAYS,

	DAY_VEG_FOR_LITTERFALL_RATE,
	MONTH_VEG_FOR_LITTERFALL_RATE,
	LEAF_FALL_COUNTER,


	COUNTERS
};



/* structures */
// A row inside input.txt file
typedef struct {
	int x;
	int y;
	eLanduse landuse;
	int age;
	char *species;
	//ePhenology phenology;
	eManagement management;
	int n;
	int stump;
	PREC avdbh;
	PREC height;
	PREC wf;
	PREC wrc;
	PREC wrf;
	PREC ws;
	PREC wres;
	PREC lai;

} ROW;

/* */
//all variables related to the species class
typedef struct {
	char *name;
	//ePhenology phenology;
	eManagement management;
	int period;            // period = 0 for adult tree ; 1 for very young tree
	PREC value[VALUES];
	int counter[COUNTERS];
	int phenology_phase;
} SPECIES;

/* */
//all variables related to the age class
typedef struct {
	int value;
	SPECIES *species;
	int species_count;
} AGE;

/* */
//all variables related to the height class
typedef struct {
	PREC value;
	int layer_coverage;
	int layer;
	int dominance;         //dominance = -1 no trees in veg period, dominance = 1 trees in veg period
	AGE *ages;
	int ages_count;

	int z;
	int top_layer;

} HEIGHT;

/* */
//all variables related to the soil site
typedef struct {

	float variabile;


} SOIL;

/* */
//all variables related to the cell (stand) are here defined
typedef struct {
	int x;
	int y;

	eLanduse landuse;

	HEIGHT *heights;
	SOIL *soils;
	int heights_count; //number of heights
	int soils_count;

	int yearday;
	float daylength_3PG;
	int cum_dayOfyear;
	float abscission_daylength;


	float net_radiation;
	float net_radiation_for_dominated;
	float net_radiation_for_subdominated;
	float net_radiation_for_soil;
	float par;
	float par_for_dominated;
	float par_for_subdominated;
	float par_for_soil;
	float par_over_dominant_canopy;
	float gpp;     //in g of C m^2
	float npp;     //in tonnes of DM per hectare
	float av_gpp;
	float av_npp;
	int height_class_in_layer_dominant_counter;
	int height_class_in_layer_dominated_counter;
	int height_class_in_layer_subdominated_counter;
	int dominant_veg_counter;
	int dominated_veg_counter;
	int subdominated_veg_counter;
	int Veg_Counter;
	float soil_evaporation;
	float available_soil_water;
	int tree_number_dominant;
	int tree_number_dominated;
	int tree_number_subdominated;
	float density_dominant;
	float density_dominated;
	float density_subdominated;
	float canopy_cover_dominant;
	float canopy_cover_dominated;
	float canopy_cover_subdominated;
	double layer_cover_dominant;
	float layer_cover_dominated;
	float layer_cover_subdominated;
	float evapotranspiration;
	float stand_agb;
	float stand_bgb;

	float litter;
	float av_yearly_daylength;
	float av_yearly_par_soil;
	float total_yearly_evapotransipration;
	float total_yearly_soil_evaporation;
	float soil_moist_ratio;
	float av_soil_moist_ratio;
	float max_asw;
	float psi_sat;//soil saturated matric potential
	float vwc_sat;//soil saturated Volumetric water content
	float soil_b; //soil moisture parameter
	float soilw_sat; //(kgH2O/m2) soilwater at saturation
	float soilw_fc; //(kgH2O/m2) soilwater at field capacity
	int annual_layer_number;
	int monthly_layer_number;
	int daily_layer_number;
	int top_layer;
	int saplings_counter;
	float snow;  //amount of snow in Kg H2O
	float snow_subl; //sublimated snow
	float gcorr;
	float air_pressure;
	int north; //northern hemisphere north = 0, south hemisphere south = 1

	float gapcover[3];


	//cumulative variables layer related used in annual-monthly-daily Log
	float daily_gpp[3], daily_tot_gpp, monthly_gpp[3], monthly_tot_gpp, annual_gpp[3], annual_tot_gpp;
	float daily_npp[3], daily_tot_npp, monthly_npp[3], monthly_tot_npp, annual_npp[3], annual_tot_npp;
	float daily_et[3], daily_tot_et, monthly_et[3], monthly_tot_et, annual_et[3], annual_tot_et;

	float daily_maint_resp[3], daily_tot_maint_resp, monthly_maint_resp[3], monthly_tot_maint_resp, annual_maint_resp[3], annual_tot_maint_resp;
	float daily_growth_resp[3], daily_tot_growth_resp, monthly_gowth_resp[3], monthly_tot_growth_resp, annual_growth_resp[3], annual_tot_growth_resp;
	float daily_aut_resp[3], daily_tot_aut_resp, monthly_aut_resp[3], monthly_tot_aut_resp, annual_aut_resp[3], annual_tot_aut_resp;

	float daily_cc[3], monthly_cc[3], annual_cc[3];


	float daily_lai[3];
	float annual_peak_lai[10];

	int daily_dead_tree[3], daily_tot_dead_tree, monthly_dead_tree[3], monthly_tot_dead_tree, annual_dead_tree[3], annual_tot_dead_tree;

	float daily_f_sw, daily_f_psi, daily_f_t, daily_f_vpd;

	float annual_delta_ws[3], annual_ws[3];
	float annual_dbh[3];

	//int dead_tree;

	float thermic_sum;

	float soil_respiration;
	float aut_respiration; //autotrophic respiration
	float het_respiration; //heterotrophic respiration
	float ter;  //total ecosystem respiration




} CELL;

/* */
typedef struct {
	CELL *cells;
	int cells_count;
} MATRIX;



/* constants */
#define MET_FILENAME_LEN                1024

/* defines */
#define Minimum(a, b)  (((a) < (b)) ? (a) : (b))
#define Maximum(a, b)  (((a) > (b)) ? (a) : (b))



//-----------------------------DEAFULT PARAMETERS------------------------------------- This was run_model.h

//#define LOGFILE		"output.txt"
/* #define BUFFER_SIZE	4096 */
#define BUFFER_SIZE	585600
#define BUFFER_SIZE_LOG 67500



// Store site.txt and settings.txt data
site_t *site;
settings_t *settings;


// External functions
extern YOS *ImportYosFiles(char *, int *const );
extern int tree_model (MATRIX *const, const YOS *const, const int, const int, const int);
extern int tree_model_daily (MATRIX *const, const YOS *const, const int, const int, const int, const int);
//if putted into main.c
//extern int soil_model (MATRIX *const, const YOS *const, const int, const int, const int);
extern void soil_model_daily (MATRIX *const, const YOS *const, const int, const int, const int, const int);
extern void Get_phenology_phase (CELL *, const MET_DATA *const, const int , const int , const int , const int );
extern void met_summary(MET_DATA *);
extern int is_valid_met(const char *const);
extern void Get_avg_temperature (CELL *, int, int, int, int, YOS *);
extern void Get_daylight_avg_temperature (CELL *, int, int, int, int, YOS *);
extern void Get_nightime_avg_temperature (CELL *, int, int, int, int, YOS *);
extern void Get_soil_temperature (CELL *, int, int, int, YOS *);
extern void Get_thermic_sum (CELL *, int, int, int, int, YOS *);
extern void Get_Veg_Months (CELL *const, const YOS *const,  const int, const int);
extern void Get_Veg_Days (CELL *const, const YOS *const, const int, const int, const int, int, int);
extern int sort_by_years(const void *, const void *);
extern int sort_by_heights_asc(const void * , const void * );
extern int sort_by_heights_desc(const void * , const void * );
extern float Get_canopy_cover (SPECIES *const, int, int, int);
extern void Get_crowding_competition (SPECIES *const, HEIGHT *, int, int , int);
extern ROW *import_dataset(const char *const, int *const);
extern int importSiteFile(char *);
extern int importSettingsFile(char *);
extern void Get_Day_Length (CELL *, int, int, int, int, YOS *);
extern void GetDayLength_3PG (CELL *, const MET_DATA *const, int , int );
extern void Get_Abscission_DayLength (CELL *);
extern int Get_Establishment_LPJ (SPECIES *const, float, float);
extern int logInit(char*);
extern void Log(const char *, ...);
extern void logClose(void);
extern int daily_logInit(char*);
extern void Daily_Log(const char *, ...);
extern void daily_logClose(void);
extern int monthly_logInit(char*);
extern void Monthly_Log(const char *, ...);
extern void monthly_logClose(void);
extern int annual_logInit(char*);
extern void Annual_Log(const char *, ...);
extern void annual_logClose(void);
extern void Get_Lai_3DVT (SPECIES *const);
extern void Get_Lai_3PG (SPECIES *const);
extern void Get_Lai_NASACASA (SPECIES *const);
extern void Get_Lai_LPJ (SPECIES *const);
extern void Get_Lai_CTEM (SPECIES *const);
extern void Get_Age_Mortality (SPECIES *const, AGE *const);
extern void Get_Greff_Mortality (SPECIES *const);
extern void Get_Mortality (SPECIES *const, int);
//extern void Get_stool_mortality (SPECIES *const, int);
extern void Get_modifiers (SPECIES *const, AGE *const, CELL *const, const MET_DATA *const, int, int, int, float, float, int, int);
extern void Get_daily_modifiers (SPECIES *const, AGE *const, CELL *const, const MET_DATA *const, int, int, int, int, float, float, int, int);
extern void Get_Management (SPECIES *const, AGE *const, int);
extern void Clearcut_Timber (SPECIES *const, int, int, int);
extern void Clearcut_Coppice (SPECIES *const, int, int, int);
extern MATRIX *matrix_create(ROW *const, const int, char *);
extern void matrix_free(MATRIX *);
extern void matrix_summary(const MATRIX *const, int, const YOS *const);
void Get_Dominant_Light(HEIGHT *, CELL *, const int, const MET_DATA *const, const int, const int);
//yearly allocation
extern void Get_Fruit_Allocation_LPJ (SPECIES *const, int, int, float, float);
extern int Get_Fruit_Allocation_Logistic_Equation (SPECIES *const, AGE *const);
extern int Get_Fruit_Allocation_TREEMIG (SPECIES *const, AGE *const);
extern void Get_Partitioning_Allocation_3PG (SPECIES *const, int, int, int);
extern void Get_Partitioning_Allocation_NASACASA (SPECIES *const, int);
extern void Get_Partitioning_Allocation_CTEM (SPECIES *const, int);
//monthly allocation
extern void M_Get_Fruit_Allocation_LPJ (SPECIES *const, int, int, float, float);
extern int M_Get_Fruit_Allocation_Logistic_Equation (SPECIES *const, AGE *const);
extern int M_Get_Fruit_Allocation_TREEMIG (SPECIES *const, AGE *const);
extern void M_Get_Partitioning_Allocation_3PG (SPECIES *const, int, int, int, int, float, const MET_DATA *const);
extern void M_Get_Partitioning_Allocation_NASACASA (SPECIES *const, int, float);
//deciduous routine for carbon allocation
extern void D_Get_Partitioning_Allocation_CTEM (SPECIES *const, CELL *, const MET_DATA *const, int, int, int, int, int, int, int);
//evergreen routine for carbon allocation
extern void E_Get_Partitioning_Allocation_CTEM (SPECIES *const, AGE *, CELL *, const MET_DATA *const, int, int, int, int, int, int);

extern void Get_maintenance_respiration (SPECIES *const, CELL *, const MET_DATA *const, int, int, int);
extern void Get_growth_respiration (SPECIES *const, CELL *, int);
extern void Get_autotrophic_respiration (SPECIES *const, CELL *, int);

extern void SP_V_M_Get_Partitioning_Allocation_CTEM (SPECIES *const, CELL *, const MET_DATA *const, int, int, int, float, int, int, int);
extern void Get_litter (CELL *c, SPECIES *const s, const int);
extern void Get_litterfall_deciduous (SPECIES *const);
extern void Get_litterfall_evergreen (HEIGHT *, float, const int, const int, int);
extern void Get_litterfall_evergreen_CTEM (SPECIES *const);
extern void Get_canopy_transpiration (SPECIES *const, CELL *const, const MET_DATA *const, int,  int, int, float, int, int, int);
extern void Get_frac_canopy_interception (SPECIES *const, const MET_DATA *const, int);
extern void Get_soil_evaporation (SPECIES *const, CELL *, const MET_DATA *const, int, int, int, float, int, int, float, float, int);
extern void Get_initial_lai (SPECIES *const s, const int, const int, const int);
extern void Get_peak_lai (SPECIES *const , int, int );
extern void Get_peak_lai_from_pipe_model (SPECIES *const , CELL *const, int, int, int, int );
extern void Get_turnover (SPECIES *const);
extern void Get_Light_Recruitment (SPECIES *const, float, float);
extern void Get_light (SPECIES *const, CELL *, const MET_DATA *const, int, int, int, int);
extern void Get_phosynthesis_monteith (SPECIES *const , CELL *, int , int, int, int, int, int);
extern void Get_biomass_increment_BOY ( CELL *const, SPECIES *const, int, int, int);
extern void Get_biomass_increment_EOY ( CELL *const, SPECIES *const, int, int, int, int);
void Get_AGB_BGB_biomass (CELL *const , int, int, int);
extern void Get_dendrometry (SPECIES *const, HEIGHT *, const int);
extern float Get_vpd (const MET_DATA *const, int);
extern void Get_numbers_of_height_class_in_layers (HEIGHT *, CELL *, int);
extern void Set_z_value ( CELL *, float, int);
extern void Get_monthly_layer_cover (CELL *, const MET_DATA *const, int);
extern void Get_daily_layer_cover (CELL *, const MET_DATA *const, int, int);
extern void Get_stool_mortality (SPECIES *, int);
extern void Get_forest_structure (CELL *);
extern void Print_met_daily_data (const YOS *const , int , int , int );
void Print_met_data (const MET_DATA *const, float, int, int);
extern void Print_init_month_stand_data (CELL *, const MET_DATA *const, const int, const int, int, int, int);
extern void Print_end_month_stand_data (CELL *, const YOS *const, const MET_DATA *const, const int, const int, int, int, int);
void Print_parameters (SPECIES *const, int, int, int);
void Get_monthly_vegetative_period (CELL *, const MET_DATA *const, int);
void Get_daily_vegetative_period (CELL *, const MET_DATA *const, int, int);
extern int Get_number_of_layers (CELL *);
extern void Get_annual_numbers_of_layers (CELL *);
void Get_monthly_numbers_of_layers (CELL *);
void Get_daily_numbers_of_layers (CELL *);
extern void Get_layer_cover_mortality (CELL *, int, int, int, float, int);
extern void Get_soil_water_balance (CELL *const);
extern void Get_annual_average_values_modifiers (SPECIES *);
extern void Get_annual_average_values_met_data (CELL *, float, float, float, float);
extern void Get_EOY_cumulative_balance_layer_level (SPECIES *, HEIGHT *);
extern void Get_EOD_cumulative_balance_cell_level (CELL *, const YOS *const , int, int, int);
extern void Get_EOM_cumulative_balance_cell_level (CELL *, const YOS *const , int, int);
extern void Get_EOY_cumulative_balance_cell_level (CELL *, const YOS *const , int, int);
extern void Get_average_biomass (SPECIES *);
extern void Get_total_class_level_biomass (SPECIES *);
extern void Get_renovation (CELL *, HEIGHT *, SPECIES *);
extern void Get_WUE (SPECIES *);
extern void Set_tree_period (SPECIES *, AGE *a, CELL *);
extern void Get_monthly_veg_counter (CELL *, SPECIES * , int);
extern void Get_daily_veg_counter (CELL *, SPECIES * , int);


extern void Reset_annual_cumulative_variables (CELL *, const int);

extern void Get_initialization_biomass_data (SPECIES *, const YOS *const, const int);
extern void Get_initialization_site_data (CELL *);
extern void Choose_management (CELL *, SPECIES *, int , int );

extern void Get_tree_BB (CELL *, int);


extern void Get_evapotranspiration (SPECIES * s, CELL *c, const MET_DATA *const, int, int, int);

extern void Get_a_Power_Function (AGE *, SPECIES *);

extern void Get_air_pressure (CELL *c);

extern void Get_snow_met_data (CELL *c, const MET_DATA *const, int, int);


//sergio's functions
extern int crop_model_M (MATRIX *const, const YOS *const, const int, const int, const int);
extern int crop_model_D (MATRIX *const, const YOS *const, const int, const int, const int, const int);




#endif /* COMMON_H */
