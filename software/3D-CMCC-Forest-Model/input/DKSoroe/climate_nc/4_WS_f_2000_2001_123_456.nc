CDF  �   
      x         y         time             CDI       GClimate Data Interface version 1.6.4 (http://code.zmaw.de/projects/cdi)    Conventions       CF-1.0     history      $Fri Mar 11 07:23:05 2016: cdo chunit,year,m-2 s-1 WS_f_2000_2001_123_456_1.nc WS_f_2000_2001_123_456.nc
Fri Mar 11 07:20:13 2016: ncatted -a standard_name,WS_F,o,c,wind_speed WS_f_2000_2001_123_456_1.nc
Fri Mar 11 07:19:35 2016: ncatted -a long_name,WS_F,o,c,wind speed WS_f_2000_2001_123_456_1.nc
Fri Mar 11 07:16:31 2016: cdo chname,LFALL,WS_F WS_f_2000_2001_123_456_0.nc WS_f_2000_2001_123_456_1.nc
Fri Mar 11 07:10:14 2016: cdo addc,10005 LFALL_2000_2001_123_456.nc WS_f_2000_2001_123_456_0.nc
Thu Mar 10 19:49:32 2016: cdo enlarge,zobel_4points.nc LFALL_2000_2001_123_456_ul.nc LFALL_2000_2001_123_456.nc
Fri Feb 19 11:04:08 2016: cdo splitsel,731,0,10958 LFALL_2000_2001_123_456.nc C:\Users\Monia\Desktop\Lavoro_Alessio\Test_zobel\netcdf\test_123_456\netcdf_giusti\LFALL_2000_2001_123_456.nc
Fri Feb 19 00:34:20 2016: ncatted -a standard_name,LFALL,o,c,Litterfall LFALL_2000_2001_IP1_1.nc
Fri Feb 19 00:34:19 2016: ncatted -a long_name,LFALL,o,c,Litterfall LFALL_2000_2001_IP1_1.nc
Fri Feb 19 00:34:19 2016: cdo chunit,mm,year LFALL_2000_2001_IP1_0.nc LFALL_2000_2001_IP1_1.nc
Fri Feb 19 00:34:19 2016: cdo chname,TOT_PREC,LFALL LFALL_2000_2001_IP1_00.nc LFALL_2000_2001_IP1_0.nc
Fri Feb 19 00:34:19 2016: cdo mulc,-9999 -gtc,-9999 TOT_PREC_2000_2001_IP1.nc LFALL_2000_2001_IP1_00.nc
Thu Feb 18 22:05:36 2016: cdo splitsel,761,8766,10958 TOT_PREC_daily1976_2005_IP1_1.nc TOT_PREC_2000_2001_IP1.nc
Thu Feb 18 22:03:38 2016: cdo chunit,kg m-2,mm TOT_PREC_daily1976_2005_IP1.nc TOT_PREC_daily1976_2005_IP1_1.nc
Mon Aug 04 08:46:00 2014: cdo mergetime TOT_PREC_daily1976_1985_IP1.nc TOT_PREC_daily1986_1995_IP1.nc TOT_PREC_daily1996_2005_IP1.nc TOT_PREC_daily1976_2005_IP1.nc
Mon Aug 04 08:36:50 2014: cdo mergetime TOT_PREC_daily1996_IP1.nc TOT_PREC_daily1997_IP1.nc TOT_PREC_daily1998_IP1.nc TOT_PREC_daily1999_IP1.nc TOT_PREC_daily2000_IP1.nc TOT_PREC_daily2001_IP1.nc TOT_PREC_daily2002_IP1.nc TOT_PREC_daily2003_IP1.nc TOT_PREC_daily2004_IP1.nc TOT_PREC_daily2005_IP1.nc TOT_PREC_daily1996_2005_IP1.nc
Mon Aug 04 08:36:47 2014: cdo sellonlatbox,14.23,14.25,47.47,47.50 TOT_PREC_daily2005.nc TOT_PREC_daily2005_IP1.nc
Fri May 30 13:43:32 2014: cdo mul TOT_PREC_daily2005_box.nc factor_TOTPREC_year.nc TOT_PREC_daily2005.nc
Fri May 30 13:36:30 2014: cdo copy factor_TOTPREC_jan_daily.nc factor_TOTPREC_feb_daily.nc factor_TOTPREC_mar_daily.nc factor_TOTPREC_apr_daily.nc factor_TOTPREC_may_daily.nc factor_TOTPREC_jun_daily.nc factor_TOTPREC_jul_daily.nc factor_TOTPREC_aug_daily.nc factor_TOTPREC_sep_daily.nc factor_TOTPREC_oct_daily.nc factor_TOTPREC_nov_daily.nc factor_TOTPREC_dec_daily.nc factor_TOTPREC_year.nc
Fri May 30 13:36:28 2014: cdo copy factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan.nc factor_TOTPREC_jan_daily.nc
Fri May 30 13:35:13 2014: cdo splitsel,1,0,12 factor_TOTPREC_masked_bil.nc factor_TOTPREC_jan.nc
Tue Apr 15 22:36:10 2014: cdo -b F64 -f nc2 mul land.nc factor_TOTPREC_HR.nc factor_TOTPREC_masked.nc
Tue Apr 15 20:25:20 2014: cdo remapbil,mask_COSMO.nc factor_TOTPREC_fill.nc factor_TOTPREC_HR.nc
Tue Apr 15 20:24:21 2014: cdo fillmiss factor_TOTPREC.nc factor_TOTPREC_fill.nc
Tue Apr 15 20:14:33 2014: cdo div rr_0.25_1976_2005_monclim.nc TOT_PREC_1976_2005_monclim_0.25.nc factor_TOTPREC.nc
Tue Apr 15 18:46:10 2014: cdo remapbil,extent_E-OBS.nc TOT_PREC_1976_2005_monclim.nc TOT_PREC_1976_2005_monclim_0.25.nc
Tue Apr 15 12:14:29 2014: cdo ymonmean TOT_PREC_1976_2005_ms.nc TOT_PREC_1976_2005_monclim.nc
Tue Apr 15 11:50:51 2014: cdo mergetime TOT_PREC_1976_ms.nc TOT_PREC_1977_ms.nc TOT_PREC_1978_ms.nc TOT_PREC_1979_ms.nc TOT_PREC_1980_ms.nc TOT_PREC_1981_ms.nc TOT_PREC_1982_ms.nc TOT_PREC_1983_ms.nc TOT_PREC_1984_ms.nc TOT_PREC_1985_ms.nc TOT_PREC_1986_ms.nc TOT_PREC_1987_ms.nc TOT_PREC_1988_ms.nc TOT_PREC_1989_ms.nc TOT_PREC_1990_ms.nc TOT_PREC_1991_ms.nc TOT_PREC_1992_ms.nc TOT_PREC_1993_ms.nc TOT_PREC_1994_ms.nc TOT_PREC_1995_ms.nc TOT_PREC_1996_ms.nc TOT_PREC_1997_ms.nc TOT_PREC_1998_ms.nc TOT_PREC_1999_ms.nc TOT_PREC_2000_ms.nc TOT_PREC_2001_ms.nc TOT_PREC_2002_ms.nc TOT_PREC_2003_ms.nc TOT_PREC_2004_ms.nc TOT_PREC_2005_ms.nc TOT_PREC_1976_2005_ms.nc
Tue Apr 15 10:09:24 2014: cdo monsum TOT_PREC_daily2005_box.nc TOT_PREC_2005_ms.nc
Mon Mar 31 11:36:27 2014: cdo selindexbox,15,209,15,215 ../totprec/TOT_PREC_daily2005.nc TOT_PREC_daily2005_box.nc
Thu Nov 08 17:23:28 2012: cdo shifttime,-1days -timselsum,4,1 TOT_PREC_hourly2005.nc TOT_PREC_daily2005.nc
Thu Nov 08 16:56:15 2012: cdo cat TOT_PREC_lffd2005010100.nc TOT_PREC_lffd2005010106.nc TOT_PREC_lffd2005010112.nc TOT_PREC_lffd2005010118.nc TOT_PREC_lffd2005010200.nc TOT_PREC_lffd2005010206.nc TOT_PREC_lffd2005010212.nc TOT_PREC_lffd2005010218.nc TOT_PREC_lffd2005010300.nc TOT_PREC_lffd2005010306.nc TOT_PREC_lffd2005010312.nc TOT_PREC_lffd2005010318.nc TOT_PREC_lffd2005010400.nc TOT_PREC_lffd2005010406.nc TOT_PREC_lffd2005010412.nc TOT_PREC_lffd2005010418.nc TOT_PREC_lffd2005010500.nc TOT_PREC_lffd2005010506.nc TOT_PREC_lffd2005010512.nc TOT_PREC_lffd2005010518.nc TOT_PREC_lffd2005010600.nc TOT_PREC_lffd2005010606.nc TOT_PREC_lffd2005010612.nc TOT_PREC_lffd2005010618.nc TOT_PREC_lffd2005010700.nc TOT_PREC_lffd2005010706.nc TOT_PREC_lffd2005010712.nc TOT_PREC_lffd2005010718.nc TOT_PREC_lffd2005010800.nc TOT_PREC_lffd2005010806.nc TOT_PREC_lffd2005010812.nc TOT_PREC_lffd2005010818.nc TOT_PREC_lffd2005010900.nc TOT_PREC_lffd2005010906.nc TOT_PREC_lffd2005010912.nc TOT_PREC_lffd2005010918.nc TOT_PREC_lffd2005011000.nc
Thu Nov 08 16:09:06 2012: cdo selname,TOT_PREC lffd2005010100.nc ../annuali2/TOT_PREC_lffd2005010100.nc   institution       -      title         -      
project_id        -      experiment_id         -      realization             conventionsURL        <http://www.unidata.ucar.edu/packages/netcdf/conventions.html   contact       -      
references        -      creation_date         2012-08-12 14:33:16    CDO       HClimate Data Operators version 1.6.4 (http://code.zmaw.de/projects/cdo)          lon                    standard_name         	longitude      	long_name         	longitude      units         degrees_east   _CoordinateAxisType       Lon         �   lat                    standard_name         latitude   	long_name         latitude   units         degrees_north      _CoordinateAxisType       Lat         �   time               standard_name         time   units         day as %Y%m%d.%f   calendar      proleptic_gregorian         �   WS_F                      standard_name         
wind_speed     	long_name         
wind speed     units         m-2 s-1    coordinates       lon lat    
_FillValue        ����   missing_value         ����   cell_methods      
time: sum           �Ac��Aeo_Ac�=Ae��B=��B=��B=��B=��As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  Asր   @�  @�  @�  @�  As֐   @�  @�  @�  @�  As֠   @�  @�  @�  @�  Asְ   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As׀   @�  @�  @�  @�  Asא   @�  @�  @�  @�  Asנ   @�  @�  @�  @�  Asװ   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  Asܐ   @�  @�  @�  @�  Asܠ   @�  @�  @�  @�  Asܰ   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As݀   @�  @�  @�  @�  Asݐ   @�  @�  @�  @�  Asݠ   @�  @�  @�  @�  Asݰ   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As   @�  @�  @�  @�  As    @�  @�  @�  @�  As0   @�  @�  @�  @�  As@   @�  @�  @�  @�  AsP   @�  @�  @�  @�  As`   @�  @�  @�  @�  Asp   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As    @�  @�  @�  @�  As   @�  @�  @�  @�  As    @�  @�  @�  @�  As0   @�  @�  @�  @�  As@   @�  @�  @�  @�  AsP   @�  @�  @�  @�  As`   @�  @�  @�  @�  Asp   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  AsP   @�  @�  @�  @�  As`   @�  @�  @�  @�  Asp   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As	    @�  @�  @�  @�  As	   @�  @�  @�  @�  As	    @�  @�  @�  @�  As	0   @�  @�  @�  @�  As	@   @�  @�  @�  @�  As	P   @�  @�  @�  @�  As	`   @�  @�  @�  @�  As	p   @�  @�  @�  @�  As	�   @�  @�  @�  @�  As	�   @�  @�  @�  @�  As	�   @�  @�  @�  @�  As	�   @�  @�  @�  @�  As	�   @�  @�  @�  @�  As	�   @�  @�  @�  @�  As	�   @�  @�  @�  @�  As	�   @�  @�  @�  @�  As
    @�  @�  @�  @�  As
   @�  @�  @�  @�  As
    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As    @�  @�  @�  @�  As   @�  @�  @�  @�  As    @�  @�  @�  @�  As0   @�  @�  @�  @�  As@   @�  @�  @�  @�  AsP   @�  @�  @�  @�  As`   @�  @�  @�  @�  Asp   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As    @�  @�  @�  @�  As   @�  @�  @�  @�  As    @�  @�  @�  @�  As0   @�  @�  @�  @�  As@   @�  @�  @�  @�  AsP   @�  @�  @�  @�  As`   @�  @�  @�  @�  Asp   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As    @�  @�  @�  @�  As   @�  @�  @�  @�  As    @�  @�  @�  @�  As0   @�  @�  @�  @�  As@   @�  @�  @�  @�  AsP   @�  @�  @�  @�  As`   @�  @�  @�  @�  Asp   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As    @�  @�  @�  @�  As   @�  @�  @�  @�  As    @�  @�  @�  @�  As0   @�  @�  @�  @�  As@   @�  @�  @�  @�  AsP   @�  @�  @�  @�  As`   @�  @�  @�  @�  Asp   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As   @�  @�  @�  @�  As    @�  @�  @�  @�  As0   @�  @�  @�  @�  As@   @�  @�  @�  @�  AsP   @�  @�  @�  @�  As`   @�  @�  @�  @�  Asp   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As    @�  @�  @�  @�  As   @�  @�  @�  @�  As    @�  @�  @�  @�  As0   @�  @�  @�  @�  As@   @�  @�  @�  @�  AsP   @�  @�  @�  @�  As`   @�  @�  @�  @�  Asp   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  AsGP   @�  @�  @�  @�  AsG`   @�  @�  @�  @�  AsGp   @�  @�  @�  @�  AsG�   @�  @�  @�  @�  AsG�   @�  @�  @�  @�  AsG�   @�  @�  @�  @�  AsG�   @�  @�  @�  @�  AsG�   @�  @�  @�  @�  AsG�   @�  @�  @�  @�  AsG�   @�  @�  @�  @�  AsG�   @�  @�  @�  @�  AsH    @�  @�  @�  @�  AsH   @�  @�  @�  @�  AsH    @�  @�  @�  @�  AsH0   @�  @�  @�  @�  AsH@   @�  @�  @�  @�  AsHP   @�  @�  @�  @�  AsH`   @�  @�  @�  @�  AsHp   @�  @�  @�  @�  AsH�   @�  @�  @�  @�  AsH�   @�  @�  @�  @�  AsH�   @�  @�  @�  @�  AsH�   @�  @�  @�  @�  AsH�   @�  @�  @�  @�  AsH�   @�  @�  @�  @�  AsH�   @�  @�  @�  @�  AsH�   @�  @�  @�  @�  AsI    @�  @�  @�  @�  AsI   @�  @�  @�  @�  AsI    @�  @�  @�  @�  AsI0   @�  @�  @�  @�  AsM�   @�  @�  @�  @�  AsM�   @�  @�  @�  @�  AsM�   @�  @�  @�  @�  AsM�   @�  @�  @�  @�  AsM�   @�  @�  @�  @�  AsM�   @�  @�  @�  @�  AsM�   @�  @�  @�  @�  AsN    @�  @�  @�  @�  AsN   @�  @�  @�  @�  AsN    @�  @�  @�  @�  AsN0   @�  @�  @�  @�  AsN@   @�  @�  @�  @�  AsNP   @�  @�  @�  @�  AsN`   @�  @�  @�  @�  AsNp   @�  @�  @�  @�  AsN�   @�  @�  @�  @�  AsN�   @�  @�  @�  @�  AsN�   @�  @�  @�  @�  AsN�   @�  @�  @�  @�  AsN�   @�  @�  @�  @�  AsN�   @�  @�  @�  @�  AsN�   @�  @�  @�  @�  AsN�   @�  @�  @�  @�  AsO    @�  @�  @�  @�  AsO   @�  @�  @�  @�  AsO    @�  @�  @�  @�  AsO0   @�  @�  @�  @�  AsO@   @�  @�  @�  @�  AsS�   @�  @�  @�  @�  AsS�   @�  @�  @�  @�  AsS�   @�  @�  @�  @�  AsT    @�  @�  @�  @�  AsT   @�  @�  @�  @�  AsT    @�  @�  @�  @�  AsT0   @�  @�  @�  @�  AsT@   @�  @�  @�  @�  AsTP   @�  @�  @�  @�  AsT`   @�  @�  @�  @�  AsTp   @�  @�  @�  @�  AsT�   @�  @�  @�  @�  AsT�   @�  @�  @�  @�  AsT�   @�  @�  @�  @�  AsT�   @�  @�  @�  @�  AsT�   @�  @�  @�  @�  AsT�   @�  @�  @�  @�  AsT�   @�  @�  @�  @�  AsT�   @�  @�  @�  @�  AsU    @�  @�  @�  @�  AsU   @�  @�  @�  @�  AsU    @�  @�  @�  @�  AsU0   @�  @�  @�  @�  AsU@   @�  @�  @�  @�  AsUP   @�  @�  @�  @�  AsU`   @�  @�  @�  @�  AsUp   @�  @�  @�  @�  AsU�   @�  @�  @�  @�  AsU�   @�  @�  @�  @�  AsU�   @�  @�  @�  @�  AsU�   @�  @�  @�  @�  AsZ   @�  @�  @�  @�  AsZ    @�  @�  @�  @�  AsZ0   @�  @�  @�  @�  AsZ@   @�  @�  @�  @�  AsZP   @�  @�  @�  @�  AsZ`   @�  @�  @�  @�  AsZp   @�  @�  @�  @�  AsZ�   @�  @�  @�  @�  AsZ�   @�  @�  @�  @�  AsZ�   @�  @�  @�  @�  AsZ�   @�  @�  @�  @�  AsZ�   @�  @�  @�  @�  AsZ�   @�  @�  @�  @�  AsZ�   @�  @�  @�  @�  AsZ�   @�  @�  @�  @�  As[    @�  @�  @�  @�  As[   @�  @�  @�  @�  As[    @�  @�  @�  @�  As[0   @�  @�  @�  @�  As[@   @�  @�  @�  @�  As[P   @�  @�  @�  @�  As[`   @�  @�  @�  @�  As[p   @�  @�  @�  @�  As[�   @�  @�  @�  @�  As[�   @�  @�  @�  @�  As[�   @�  @�  @�  @�  As[�   @�  @�  @�  @�  As[�   @�  @�  @�  @�  As[�   @�  @�  @�  @�  As[�   @�  @�  @�  @�  As`P   @�  @�  @�  @�  As``   @�  @�  @�  @�  As`p   @�  @�  @�  @�  As`�   @�  @�  @�  @�  As`�   @�  @�  @�  @�  As`�   @�  @�  @�  @�  As`�   @�  @�  @�  @�  As`�   @�  @�  @�  @�  As`�   @�  @�  @�  @�  As`�   @�  @�  @�  @�  As`�   @�  @�  @�  @�  Asa    @�  @�  @�  @�  Asa   @�  @�  @�  @�  Asa    @�  @�  @�  @�  Asa0   @�  @�  @�  @�  Asa@   @�  @�  @�  @�  AsaP   @�  @�  @�  @�  Asa`   @�  @�  @�  @�  Asap   @�  @�  @�  @�  Asa�   @�  @�  @�  @�  Asa�   @�  @�  @�  @�  Asa�   @�  @�  @�  @�  Asa�   @�  @�  @�  @�  Asa�   @�  @�  @�  @�  Asa�   @�  @�  @�  @�  Asa�   @�  @�  @�  @�  Asa�   @�  @�  @�  @�  Asb    @�  @�  @�  @�  Asb   @�  @�  @�  @�  Asb    @�  @�  @�  @�  Asb0   @�  @�  @�  @�  Asf�   @�  @�  @�  @�  Asf�   @�  @�  @�  @�  Asf�   @�  @�  @�  @�  Asf�   @�  @�  @�  @�  Asf�   @�  @�  @�  @�  Asf�   @�  @�  @�  @�  Asf�   @�  @�  @�  @�  Asg    @�  @�  @�  @�  Asg   @�  @�  @�  @�  Asg    @�  @�  @�  @�  Asg0   @�  @�  @�  @�  Asg@   @�  @�  @�  @�  AsgP   @�  @�  @�  @�  Asg`   @�  @�  @�  @�  Asgp   @�  @�  @�  @�  Asg�   @�  @�  @�  @�  Asg�   @�  @�  @�  @�  Asg�   @�  @�  @�  @�  Asg�   @�  @�  @�  @�  Asg�   @�  @�  @�  @�  Asg�   @�  @�  @�  @�  Asg�   @�  @�  @�  @�  Asg�   @�  @�  @�  @�  Ash    @�  @�  @�  @�  Ash   @�  @�  @�  @�  Ash    @�  @�  @�  @�  Ash0   @�  @�  @�  @�  Ash@   @�  @�  @�  @�  AshP   @�  @�  @�  @�  Ash`   @�  @�  @�  @�  Asl�   @�  @�  @�  @�  Asl�   @�  @�  @�  @�  Asl�   @�  @�  @�  @�  Asm    @�  @�  @�  @�  Asm   @�  @�  @�  @�  Asm    @�  @�  @�  @�  Asm0   @�  @�  @�  @�  Asm@   @�  @�  @�  @�  AsmP   @�  @�  @�  @�  Asm`   @�  @�  @�  @�  Asmp   @�  @�  @�  @�  Asm�   @�  @�  @�  @�  Asm�   @�  @�  @�  @�  Asm�   @�  @�  @�  @�  Asm�   @�  @�  @�  @�  Asm�   @�  @�  @�  @�  Asm�   @�  @�  @�  @�  Asm�   @�  @�  @�  @�  Asm�   @�  @�  @�  @�  Asn    @�  @�  @�  @�  Asn   @�  @�  @�  @�  Asn    @�  @�  @�  @�  Asn0   @�  @�  @�  @�  Asn@   @�  @�  @�  @�  AsnP   @�  @�  @�  @�  Asn`   @�  @�  @�  @�  Asnp   @�  @�  @�  @�  Asn�   @�  @�  @�  @�  Asn�   @�  @�  @�  @�  Asn�   @�  @�  @�  @�  Asn�   @�  @�  @�  @�  Ass   @�  @�  @�  @�  Ass    @�  @�  @�  @�  Ass0   @�  @�  @�  @�  Ass@   @�  @�  @�  @�  AssP   @�  @�  @�  @�  Ass`   @�  @�  @�  @�  Assp   @�  @�  @�  @�  Ass�   @�  @�  @�  @�  Ass�   @�  @�  @�  @�  Ass�   @�  @�  @�  @�  Ass�   @�  @�  @�  @�  Ass�   @�  @�  @�  @�  Ass�   @�  @�  @�  @�  Ass�   @�  @�  @�  @�  Ass�   @�  @�  @�  @�  Ast    @�  @�  @�  @�  Ast   @�  @�  @�  @�  Ast    @�  @�  @�  @�  Ast0   @�  @�  @�  @�  Ast@   @�  @�  @�  @�  AstP   @�  @�  @�  @�  Ast`   @�  @�  @�  @�  Astp   @�  @�  @�  @�  Ast�   @�  @�  @�  @�  Ast�   @�  @�  @�  @�  Ast�   @�  @�  @�  @�  Ast�   @�  @�  @�  @�  Ast�   @�  @�  @�  @�  Ast�   @�  @�  @�  @�  Ast�   @�  @�  @�  @�  Ast�   @�  @�  @�  @�  AsyP   @�  @�  @�  @�  Asy`   @�  @�  @�  @�  Asyp   @�  @�  @�  @�  Asy�   @�  @�  @�  @�  Asy�   @�  @�  @�  @�  Asy�   @�  @�  @�  @�  Asy�   @�  @�  @�  @�  Asy�   @�  @�  @�  @�  Asy�   @�  @�  @�  @�  Asy�   @�  @�  @�  @�  Asy�   @�  @�  @�  @�  Asz    @�  @�  @�  @�  Asz   @�  @�  @�  @�  Asz    @�  @�  @�  @�  Asz0   @�  @�  @�  @�  Asz@   @�  @�  @�  @�  AszP   @�  @�  @�  @�  Asz`   @�  @�  @�  @�  Aszp   @�  @�  @�  @�  Asz�   @�  @�  @�  @�  Asz�   @�  @�  @�  @�  Asz�   @�  @�  @�  @�  Asz�   @�  @�  @�  @�  Asz�   @�  @�  @�  @�  Asz�   @�  @�  @�  @�  Asz�   @�  @�  @�  @�  Asz�   @�  @�  @�  @�  As{    @�  @�  @�  @�  As{   @�  @�  @�  @�  As{    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�   @�  @�  @�  @�  As�    @�  @�  @�  @�  As�0   @�  @�  @�  @�  As�@   @�  @�  @�  @�  As�P   @�  @�  @�  @�  As�`   @�  @�  @�  @�  As�p   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  As��   @�  @�  @�  @�  