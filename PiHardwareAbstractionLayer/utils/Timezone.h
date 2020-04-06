#pragma once

#include "TerminalAccess.h"
#include <iomanip>
#include <stdint.h>
#include <sstream>

namespace hal
{
	namespace utils
	{
		//! Contains all timezones that are currently in use worldwide.
		/*!
		* Contains all timezones that are currently in use worldwide. The names are composed
		* by the long name of the timezone, its official abbreviation and the time offset from UTC.
		*/
		enum class WorldTimezones : int16_t
		{
			/*!< Defines a timezone that is used in Military and has an UTC offset of 01:00 */
			ALPHA_TIME_ZONE__A__PLUS_H01M00,
			/*!< Defines a timezone that is used in Australia (e.g. Adelaide) and has an UTC offset of 09:30  (with daylight saving time in summer)*/
			AUSTRALIAN_CENTRAL_DAYLIGHT_TIME__ACST__PLUS_H09M30,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -05:00 */
			ACRE_TIME__ACT__MINUS_H05M00,
			/*!< Defines a timezone that is used in Australia (e.g. Darwin) and has an UTC offset of 09:30 (without daylight saving time in summer) */
			AUSTRALIAN_CENTRAL_STANDARD_TIME__ACST__PLUS_H09M30,
			/*!< Defines a timezone that is used in Australia and has an UTC offset of 08:45 */
			AUSTRALIAN_CENTRAL_WESTERN_STANDARD_TIME__ACWST__PLUS_H08M45,
			/*!< Defines a timezone that is used in North America & Atlantic and has an UTC offset of -03:00 */
			ATLANTIC_DAYLIGHT_TIME__ADT__MINUS_H03M00,
			/*!< Defines a timezone that is used in Australia and has an UTC offset of 11:00 */
			AUSTRALIAN_EASTERN_DAYLIGHT_TIME__AEST__PLUS_H10M00,
			/*!< Defines a timezone that is used in Australia and has an UTC offset of 10:00 */
			AUSTRALIAN_EASTERN_STANDARD_TIME__AEST__PLUS_H10M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 04:30 */
			AFGHANISTAN_TIME__AFT__PLUS_H04M30,
			/*!< Defines a timezone that is used in North America and has an UTC offset of -09:00 */
			ALASKA_STANDARD_TIME__AKST__MINUS_H09M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 06:00 */
			ALMA_ATA_TIME__ALMT__PLUS_H06M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -04:00 */
			AMAZON_TIME__AMT__MINUS_H04M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 04:00 */
			ARMENIA_TIME__AMT__PLUS_H04M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 12:00 */
			ANADYR_TIME__ANAT__PLUS_H12M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 05:00 */
			AQTOBE_TIME__AQTT__PLUS_H05M00,
			/*!< Defines a timezone that is used in Antarctica & South America and has an UTC offset of -03:00 */
			ARGENTINA_TIME__ART__MINUS_H03M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 03:00 */
			ARABIA_STANDARD_TIME__AST__PLUS_H03M00,
			/*!< Defines a timezone that is used in North America & AtlanticCaribbean and has an UTC offset of -04:00 (without daylight saving time in summer)*/
			ATLANTIC_STANDARD_TIME__AST__MINUS_H04M00,
			/*!< Defines a timezone that is used in North America & Atlantic (e.g. Bermuda) and has an UTC offset of -04:00 (with daylight saving time in summer)*/
			ATLANTIC_DAYLIGHT_TIME__AT__MINUS_H04M00,
			/*!< Defines a timezone that is used in Australia and has an UTC offset of 08:00 */
			AUSTRALIAN_WESTERN_STANDARD_TIME__AWST__PLUS_H08M00,
			/*!< Defines a timezone that is used in Atlantic and has an UTC offset of -01:00 */
			AZORES_TIME__AZOT__MINUS_H01M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 04:00 */
			AZERBAIJAN_TIME__AZT__PLUS_H04M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of -12:00 */
			ANYWHERE_ON_EARTH__AOE__MINUS_H12M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of 02:00 */
			BRAVO_TIME_ZONE__B__PLUS_H02M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 08:00 */
			BRUNEI_DARUSSALAM_TIME__BNT__PLUS_H08M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -04:00 */
			BOLIVIA_TIME__BOT__MINUS_H04M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -03:00 */
			BRASILIA_TIME__BRT__MINUS_H03M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 06:00 */
			BANGLADESH_STANDARD_TIME__BST__PLUS_H06M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 11:00 */
			BOUGAINVILLE_STANDARD_TIME__BST__PLUS_H11M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 06:00 */
			BHUTAN_TIME__BTT__PLUS_H06M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of 03:00 */
			CHARLIE_TIME_ZONE__C__PLUS_H03M00,
			/*!< Defines a timezone that is used in Antarctica and has an UTC offset of 08:00 */
			CASEY_TIME__CAST__PLUS_H08M00,
			/*!< Defines a timezone that is used in Africa and has an UTC offset of 02:00 */
			CENTRAL_AFRICA_TIME__CAT__PLUS_H02M00,
			/*!< Defines a timezone that is used in Indian Ocean and has an UTC offset of 06:30 */
			COCOS_ISLANDS_TIME__CCT__PLUS_H06M30,
			/*!< Defines a timezone that is used in Caribbean and has an UTC offset of -04:00 */
			CUBA_STANDARD_TIME__CST__MINUS_H05M00,
			/*!< Defines a timezone that is used in Africa and has an UTC offset of 01:00 */
			CENTRAL_EUROPEAN_STANDARD_TIME__CET__PLUS_H01M00,
			/*!< Defines a timezone that is used in Europe & Africa and has an UTC offset of 01:00 */
			CENTRAL_EUROPEAN_TIME__CET__PLUS_H01M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 12:45 */
			CHATHAM_ISLAND_STANDARD_TIME__CHAST__PLUS_H12M45,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 08:00 */
			CHOIBALSAN_TIME__CHOT__PLUS_H08M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 10:00 */
			CHUUK_TIME__CHUT__PLUS_H10M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of -10:00 */
			COOK_ISLAND_TIME__CKT__MINUS_H10M00,
			/*!< Defines a timezone that is used in South America & Antarctica and has an UTC offset of -04:00 */
			CHILE_STANDARD_TIME__CLT__MINUS_H04M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -05:00 */
			COLOMBIA_TIME__COT__MINUS_H05M00,
			/*!< Defines a timezone that is used in North America (e.g. Saskatchewan) & Central America (e.g. Costa Rica, Guatemala) and has an UTC offset of -06:00
			(without daylight saving time in summer) */
			CENTRAL_STANDARD_TIME__CST__MINUS_H06M00,
			/*!< Defines a timezone that is used in North America (e.g. Alabama, Iowa, Manitoba, Mexico) and has an UTC offset of -06:00
			(with daylight saving time in summer)*/
			CENTRAL_DAYLIGHT_TIME__CST__MINUS_H06M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 08:00 */
			CHINA_STANDARD_TIME__CST__PLUS_H08M00,
			/*!< Defines a timezone that is used in Africa and has an UTC offset of -01:00 */
			CAPE_VERDE_TIME__CVT__MINUS_H01M00,
			/*!< Defines a timezone that is used in Australia and has an UTC offset of 07:00 */
			CHRISTMAS_ISLAND_TIME__CXT__PLUS_H07M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 10:00 */
			CHAMORRO_STANDARD_TIME__CHST__PLUS_H10M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of 04:00 */
			DELTA_TIME_ZONE__D__PLUS_H04M00,
			/*!< Defines a timezone that is used in Antarctica and has an UTC offset of 07:00 */
			DAVIS_TIME__DAVT__PLUS_H07M00,
			/*!< Defines a timezone that is used in Antarctica and has an UTC offset of 10:00 */
			DUMONT_D_URVILLE_TIME__DDUT__PLUS_H10M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of 05:00 */
			ECHO_TIME_ZONE__E__PLUS_H05M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of -06:00 */
			EASTER_ISLAND_STANDARD_TIME__EAST__MINUS_H06M00,
			/*!< Defines a timezone that is used in Africa & Indian Ocean and has an UTC offset of 03:00 */
			EASTERN_AFRICA_TIME__EAT__PLUS_H03M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -05:00 */
			ECUADOR_TIME__ECT__MINUS_H05M00,
			/*!< Defines a timezone that is used in Europe & AsiaAfrica and has an UTC offset of 02:00 */
			EASTERN_EUROPEAN_TIME__EET__PLUS_H02M00,
			/*!< Defines a timezone that is used in North America and has an UTC offset of -01:00 */
			EAST_GREENLAND_TIME__EGT__MINUS_H01M00,
			/*!< Defines a timezone that is used in North America (e.g. Coral Harbour) & Caribbean (e.g. Jamaica) & Central America (e.g. Panama)
			and has an UTC offset of -05:00 (without daylight saving time in summer)*/
			EASTERN_STANDARD_TIME__EST__MINUS_H05M00,
			/*!< Defines a timezone that is used in North America (e.g. Georgia, Maryland, Ohio, Quebec) & Caribbean (e.g. Bahamas, Haiti) and has an UTC offset of -05:00
			(with daylight saving time in summer)*/
			EASTERN_DAYLIGHT_TIME__EST__MINUS_H05M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of 06:00 */
			FOXTROT_TIME_ZONE__F__PLUS_H06M00,
			/*!< Defines a timezone that is used in Europe and has an UTC offset of 03:00 */
			FURTHER_EASTERN_EUROPEAN_TIME__FET__PLUS_H03M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 12:00 */
			FIJI_TIME__FJT__PLUS_H12M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -04:00 */
			FALKLAND_ISLAND_TIME__FKT__MINUS_H04M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -02:00 */
			FERNANDO_DE_NORONHA_TIME__FNT__MINUS_H02M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of 07:00 */
			GOLF_TIME_ZONE__G__PLUS_H07M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of -06:00 */
			GALAPAGOS_TIME__GALT__MINUS_H06M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of -09:00 */
			GAMBIER_TIME__GAMT__MINUS_H09M00,
			/*!< Defines a timezone that is used in Asia & Europe and has an UTC offset of 04:00 */
			GEORGIA_STANDARD_TIME__GET__PLUS_H04M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -03:00 */
			FRENCH_GUIANA_TIME__GFT__MINUS_H03M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 12:00 */
			GILBERT_ISLAND_TIME__GILT__PLUS_H12M00,
			/*!< Defines a timezone that is used in Europe & AfricaNorth AmericaAntarctica and has an UTC offset of 00:00 */
			GREENWICH_MEAN_TIME__GMT__PLUS_H00M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 04:00 */
			GULF_STANDARD_TIME__GST__PLUS_H04M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -02:00 */
			SOUTH_GEORGIA_TIME__GST__MINUS_H02M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -04:00 */
			GUYANA_TIME__GYT__MINUS_H04M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of 08:00 */
			HOTEL_TIME_ZONE__H__PLUS_H08M00,
			/*!< Defines a timezone that is used in North America and has an UTC offset of -09:00 */
			HAWAII_ALEUTIAN_DAYLIGHT_TIME__HST__MINUS_H10M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 08:00 */
			HONG_KONG_TIME__HKT__PLUS_H08M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 07:00 */
			HOVD_TIME__HOVT__PLUS_H07M00,
			/*!< Defines a timezone that is used in North America & Pacific and has an UTC offset of -10:00 */
			HAWAII_STANDARD_TIME__HST__MINUS_H10M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of 09:00 */
			INDIA_TIME_ZONE__I__PLUS_H09M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 07:00 */
			INDOCHINA_TIME__ICT__PLUS_H07M00,
			/*!< Defines a timezone that is used in Indian Ocean and has an UTC offset of 06:00 */
			INDIAN_CHAGOS_TIME__IOT__PLUS_H06M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 08:00 */
			IRKUTSK_TIME__IRKT__PLUS_H08M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 03:30 */
			IRAN_STANDARD_TIME__IRST__PLUS_H03M30,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 05:30 */
			INDIA_STANDARD_TIME__IST__PLUS_H05M30,
			/*!< Defines a timezone that is used in Europe and has an UTC offset of 01:00 */
			IRISH_STANDARD_TIME__IST__PLUS_H01M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 02:00 */
			ISRAEL_STANDARD_TIME__IST__PLUS_H02M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 09:00 */
			JAPAN_STANDARD_TIME__JST__PLUS_H09M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of 10:00 */
			KILO_TIME_ZONE__K__PLUS_H10M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 06:00 */
			KYRGYZSTAN_TIME__KGT__PLUS_H06M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 11:00 */
			KOSRAE_TIME__KOST__PLUS_H11M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 07:00 */
			KRASNOYARSK_TIME__KRAT__PLUS_H07M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 09:00 */
			KOREA_STANDARD_TIME__KST__PLUS_H09M00,
			/*!< Defines a timezone that is used in Europe and has an UTC offset of 04:00 */
			KUYBYSHEV_TIME__KUYT__PLUS_H04M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of 11:00 */
			LIMA_TIME_ZONE__L__PLUS_H11M00,
			/*!< Defines a timezone that is used in Australia and has an UTC offset of 10:30 */
			LORD_HOWE_STANDARD_TIME__LHST__PLUS_H10M30,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 14:00 */
			LINE_ISLANDS_TIME__LINT__PLUS_H14M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of 12:00 */
			MIKE_TIME_ZONE__M__PLUS_H12M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 11:00 */
			MAGADAN_TIME__MAGT__PLUS_H11M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of -09:30 */
			MARQUESAS_TIME__MART__MINUS_H09M30,
			/*!< Defines a timezone that is used in Antarctica and has an UTC offset of 05:00 */
			MAWSON_TIME__MAWT__PLUS_H05M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 12:00 */
			MARSHALL_ISLANDS_TIME__MHT__PLUS_H12M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 06:30 */
			MYANMAR_TIME__MMT__PLUS_H06M30,
			/*!< Defines a timezone that is used in Europe & Asia and has an UTC offset of 03:00 */
			MOSCOW_STANDARD_TIME__MSK__PLUS_H03M00,
			/*!< Defines a timezone that is used in North America (e.g. Arizona, Sonora) and has an UTC offset of -07:00
			(without daylight saving time in summer)*/
			MOUNTAIN_STANDARD_TIME__MST__MINUS_H07M00,
			/*!< Defines a timezone that is used in North America (e.g. Colorado, Alberta, Baja California) and has an UTC offset of -07:00
			(with daylight saving time in summer)*/
			MOUNTAIN_DAYLIGHT_TIME__MST__MINUS_H07M00,
			/*!< Defines a timezone that is used in Africa and has an UTC offset of 04:00 */
			MAURITIUS_TIME__MUT__PLUS_H04M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 05:00 */
			MALDIVES_TIME__MVT__PLUS_H05M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 08:00 */
			MALAYSIA_TIME__MYT__PLUS_H08M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of -01:00 */
			NOVEMBER_TIME_ZONE__N__MINUS_H01M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 11:00 */
			NEW_CALEDONIA_TIME__NCT__PLUS_H11M00,
			/*!< Defines a timezone that is used in North America and has an UTC offset of -02:30 */
			NEWFOUNDLAND_STANDARD_TIME__NDT__MINUS_H03M30,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 07:00 */
			NOVOSIBIRSK_TIME__NOVT__PLUS_H07M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 05:45 */
			NEPAL_TIME___NPT__PLUS_H05M45,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 12:00 */
			NAURU_TIME__NRT__PLUS_H12M00,
			/*!< Defines a timezone that is used in North America and has an UTC offset of -03:30 */
			NEWFOUNDLAND_STANDARD_TIME__NST__MINUS_H03M30,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of -11:00 */
			NIUE_TIME__NUT__MINUS_H11M00,
			/*!< Defines a timezone that is used in Pacific (e.g. New Zealand) & Antarctica (e.g. McMurdo Station) and has an UTC offset of 12:00 */
			NEW_ZEALAND_STANDARD_TIME__NZST__PLUS_H12M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of -02:00 */
			OSCAR_TIME_ZONE__O__MINUS_H02M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 06:00 */
			OMSK_STANDARD_TIME__OMST__PLUS_H06M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 05:00 */
			ORAL_TIME__ORAT__PLUS_H05M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of -03:00 */
			PAPA_TIME_ZONE__P__MINUS_H03M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -05:00 */
			PERU_TIME__PET__MINUS_H05M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 12:00 */
			KAMCHATKA_TIME__PETT__PLUS_H12M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 10:00 */
			PAPUA_NEW_GUINEA_TIME__PGT__PLUS_H10M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 13:00 */
			PHOENIX_ISLAND_TIME__PHOT__PLUS_H13M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 08:00 */
			PHILIPPINE_TIME__PHT__PLUS_H08M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 05:00 */
			PAKISTAN_STANDARD_TIME__PKT__PLUS_H05M00,
			/*!< Defines a timezone that is used in North America and has an UTC offset of -02:00 */
			PIERRE_MIQUELON_DAYLIGHT_TIME__PMDT__MINUS_H02M00,
			/*!< Defines a timezone that is used in North America and has an UTC offset of -03:00 */
			PIERRE_MIQUELON_STANDARD_TIME__PMST__MINUS_H03M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 11:00 */
			POHNPEI_STANDARD_TIME__PONT__PLUS_H11M00,
			/*!< Defines a timezone that is used in North America (e.g. California, Nevada, Yukon) and has an UTC offset of -08:00
			(with daylight saving time in summer) */
			PACIFIC_STANDARD_TIME__PST__MINUS_H08M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of -08:00 */
			PITCAIRN_STANDARD_TIME__PST__MINUS_H08M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 09:00 */
			PALAU_TIME__PWT__PLUS_H09M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -04:00 */
			PARAGUAY_TIME__PYT__MINUS_H04M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 08:30 */
			PYONGYANG_TIME__PYT__PLUS_H08M30,
			/*!< Defines a timezone that is used in Military and has an UTC offset of -04:00 */
			QUEBEC_TIME_ZONE__Q__MINUS_H04M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 06:00 */
			QYZYLORDA_TIME__QYZT__PLUS_H06M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of -05:00 */
			ROMEO_TIME_ZONE__R__MINUS_H05M00,
			/*!< Defines a timezone that is used in Africa and has an UTC offset of 04:00 */
			REUNION_TIME__RET__PLUS_H04M00,
			/*!< Defines a timezone that is used in Antarctica and has an UTC offset of -03:00 */
			ROTHERA_TIME__ROTT__MINUS_H03M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of -06:00 */
			SIERRA_TIME_ZONE__S__MINUS_H06M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 11:00 */
			SAKHALIN_TIME__SAKT__PLUS_H11M00,
			/*!< Defines a timezone that is used in Europe and has an UTC offset of 04:00 */
			SAMARA_TIME__SAMT__PLUS_H04M00,
			/*!< Defines a timezone that is used in Africa and has an UTC offset of 02:00 */
			SOUTH_AFRICA_STANDARD_TIME__SAST__PLUS_H02M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 11:00 */
			SOLOMON_ISLANDS_TIME__SBT__PLUS_H11M00,
			/*!< Defines a timezone that is used in Africa and has an UTC offset of 04:00 */
			SEYCHELLES_TIME__SCT__PLUS_H04M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 08:00 */
			SINGAPORE_TIME__SGT__PLUS_H08M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 11:00 */
			SREDNEKOLYMSK_TIME__SRET__PLUS_H11M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -03:00 */
			SURINAME_TIME__SRT__MINUS_H03M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of -11:00 */
			SAMOA_STANDARD_TIME__SST__MINUS_H11M00,
			/*!< Defines a timezone that is used in Antarctica and has an UTC offset of 03:00 */
			SYOWA_TIME__SYOT__PLUS_H03M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of -07:00 */
			TANGO_TIME_ZONE__T__MINUS_H07M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of -10:00 */
			TAHITI_TIME__TAHT__MINUS_H10M00,
			/*!< Defines a timezone that is used in Indian Ocean and has an UTC offset of 05:00 */
			FRENCH_SOUTHERN_AND_ANTARCTIC_TIME__TFT__PLUS_H05M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 05:00 */
			TAJIKISTAN_TIME__TJT__PLUS_H05M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 13:00 */
			TOKELAU_TIME__TKT__PLUS_H13M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 09:00 */
			EAST_TIMOR_TIME__TLT__PLUS_H09M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 05:00 */
			TURKMENISTAN_TIME__TMT__PLUS_H05M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 13:00 */
			TONGA_TIME__TOT__PLUS_H13M00,
			/*!< Defines a timezone that is used in Asia & Europe and has an UTC offset of 03:00 */
			TURKEY_TIME__TRT__PLUS_H03M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 12:00 */
			TUVALU_TIME__TVT__PLUS_H12M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of -08:00 */
			UNIFORM_TIME_ZONE__U__MINUS_H08M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 08:00 */
			ULAANBAATAR_TIME__ULAT__PLUS_H08M00,
			/*!< Defines a timezone that is used in Worldwide and has an UTC offset of 00:00 */
			COORDINATED_UNIVERSAL_TIME__UTC__PLUS_H00M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -03:00 */
			URUGUAY_TIME__UYT__MINUS_H03M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 05:00 */
			UZBEKISTAN_TIME__UZT__PLUS_H05M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of -09:00 */
			VICTOR_TIME_ZONE__V__MINUS_H09M00,
			/*!< Defines a timezone that is used in South America and has an UTC offset of -04:00 */
			VENEZUELAN_STANDARD_TIME__VET__MINUS_H04M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 10:00 */
			VLADIVOSTOK_TIME__VLAT__PLUS_H10M00,
			/*!< Defines a timezone that is used in Antarctica and has an UTC offset of 06:00 */
			VOSTOK_TIME__VOST__PLUS_H06M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 11:00 */
			VANUATU_TIME__VUT__PLUS_H11M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of -10:00 */
			WHISKEY_TIME_ZONE__W__MINUS_H10M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 12:00 */
			WAKE_TIME__WAKT__PLUS_H12M00,
			/*!< Defines a timezone that is used in Africa and has an UTC offset of 01:00 */
			WEST_AFRICA_TIME__WAT__PLUS_H01M00,
			/*!< Defines a timezone that is used in Europe & Africa and has an UTC offset of 00:00 */
			WESTERN_EUROPEAN_TIME__WET__PLUS_H00M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 12:00 */
			WALLIS_AND_FUTUNA_TIME__WFT__PLUS_H12M00,
			/*!< Defines a timezone that is used in North America and has an UTC offset of -03:00 */
			WEST_GREENLAND_TIME__WGT__MINUS_H03M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 07:00 */
			WESTERN_INDONESIAN_TIME__WIB__PLUS_H07M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 09:00 */
			EASTERN_INDONESIAN_TIME__WIT__PLUS_H09M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 08:00 */
			CENTRAL_INDONESIAN_TIME__WITA__PLUS_H08M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 14:00 */
			WEST_SAMOA_TIME__WST__PLUS_H14M00,
			/*!< Defines a timezone that is used in Africa and has an UTC offset of 00:00 */
			WESTERN_SAHARA_STANDARD_TIME__WT__PLUS_H00M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of -11:00 */
			X_RAY_TIME_ZONE__X__MINUS_H11M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of -12:00 */
			YANKEE_TIME_ZONE__Y__MINUS_H12M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 09:00 */
			YAKUTSK_TIME__YAKT__PLUS_H09M00,
			/*!< Defines a timezone that is used in Pacific and has an UTC offset of 10:00 */
			YAP_TIME__YAPT__PLUS_H10M00,
			/*!< Defines a timezone that is used in Asia and has an UTC offset of 05:00 */
			YEKATERINBURG_TIME__YEKT__PLUS_H05M00,
			/*!< Defines a timezone that is used in Military and has an UTC offset of 00:00 */
			ZULU_TIME_ZONE__Z__PLUS_H00M00
		};

		//! Represents one specific timezone.
		/*!
		* Represents one specific timezone. It contains information about offsets (minute & hour) to UTC,
		* use of daylight saving time in summer and the corresponding path to Linux tz database.
		*/
		class Timezone
		{
		public:
			//! Default constructor that initializes all fields to UTC timezone.
			/*!
			* Default constructor that initializes all fields to UTC timezone.
			*/
			Timezone()
			{
				m_current_timezone = WorldTimezones::COORDINATED_UNIVERSAL_TIME__UTC__PLUS_H00M00;
				m_long_name = "Coordinated_Universal_Time";
				m_short_name = "UTC";
				m_locations = { "Worldwide" };
				m_offset_hours = 0;
				m_offset_minutes = 0;
				m_uses_daylight_saving = false;
				m_offset_hours_while_daylight_saving = 0;
				m_offset_minutes_while_daylight_saving = 0;
				m_tz_path = "";
				m_is_currently_daylight_saving = false;
				m_last_daylight_saving_check = 0;
				m_daylight_saving_check_interval = 0;
			}

			//! Constructor that initializes all fields to the given timezone.
			/*!
			* Constructor that initializes all fields to the given timezone.
			* \param[in] timezone: The enum value of the timezone to create.
			*/
			explicit Timezone(WorldTimezones timezone)
			{
				switch (timezone)
				{
				case WorldTimezones::ALPHA_TIME_ZONE__A__PLUS_H01M00:
					m_long_name = "Alpha_Time_Zone";
					m_long_daylight_saving_name = "Alpha_Time_Zone";
					m_short_name = "A";
					m_short_daylight_saving_name = "";
					m_locations = { "Military" };
					m_offset_hours = 1;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::AUSTRALIAN_CENTRAL_DAYLIGHT_TIME__ACST__PLUS_H09M30:
					m_long_name = "Australian_Central_Standard_Time";
					m_long_daylight_saving_name = "Australian_Central_Daylight_Time";
					m_short_name = "ACST";
					m_short_daylight_saving_name = "ACDT";
					m_locations = { "Australia (e.g. Adelaide)" };
					m_offset_hours = 9;
					m_offset_minutes = 30;
					m_offset_hours_while_daylight_saving = 10;
					m_offset_minutes_while_daylight_saving = 30;
					m_tz_path = "Australia/Adelaide";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::ACRE_TIME__ACT__MINUS_H05M00:
					m_long_name = "Acre_Time";
					m_long_daylight_saving_name = "Acre_Time";
					m_short_name = "ACT";
					m_short_daylight_saving_name = "";
					m_locations = { "South America" };
					m_offset_hours = -5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::AUSTRALIAN_CENTRAL_STANDARD_TIME__ACST__PLUS_H09M30:
					m_long_name = "Australian_Central_Standard_Time";
					m_long_daylight_saving_name = "Australian_Central_Standard_Time";
					m_short_name = "ACST";
					m_short_daylight_saving_name = "ACST";
					m_locations = { "Australia (e.g. Darwin)" };
					m_offset_hours = 9;
					m_offset_minutes = 30;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::AUSTRALIAN_CENTRAL_WESTERN_STANDARD_TIME__ACWST__PLUS_H08M45:
					m_long_name = "Australian_Central_Western_Standard_Time";
					m_long_daylight_saving_name = "Australian_Central_Western_Standard_Time";
					m_short_name = "ACWST";
					m_short_daylight_saving_name = "ACWST";
					m_locations = { "Australia" };
					m_offset_hours = 8;
					m_offset_minutes = 45;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ATLANTIC_DAYLIGHT_TIME__ADT__MINUS_H03M00:
					m_long_name = "Atlantic_Daylight_Time";
					m_long_daylight_saving_name = "Atlantic_Daylight_Time";
					m_short_name = "ADT";
					m_short_daylight_saving_name = "ADT";
					m_locations = { "North America", "Atlantic" };
					m_offset_hours = -3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::AUSTRALIAN_EASTERN_DAYLIGHT_TIME__AEST__PLUS_H10M00:
					m_long_name = "Australian_Eastern_Standard_Time";
					m_long_daylight_saving_name = "Australian_Eastern_Daylight_Time";
					m_short_name = "AEST";
					m_short_daylight_saving_name = "AEDT";
					m_locations = { "Australia (e.g. New South Wales, Victoria)" };
					m_offset_hours = 10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 11;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "Australia/Sydney";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::AUSTRALIAN_EASTERN_STANDARD_TIME__AEST__PLUS_H10M00:
					m_long_name = "Australian_Eastern_Standard_Time";
					m_long_daylight_saving_name = "Australian_Eastern_Standard_Time";
					m_short_name = "AEST";
					m_short_daylight_saving_name = "AEST";
					m_locations = { "Australia (e.g. Queensland)" };
					m_offset_hours = 10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::AFGHANISTAN_TIME__AFT__PLUS_H04M30:
					m_long_name = "Afghanistan_Time";
					m_long_daylight_saving_name = "Afghanistan_Time";
					m_short_name = "AFT";
					m_short_daylight_saving_name = "AFT";
					m_locations = { "Asia" };
					m_offset_hours = 4;
					m_offset_minutes = 30;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ALASKA_STANDARD_TIME__AKST__MINUS_H09M00:
					m_long_name = "Alaska_Standard_Time";
					m_long_daylight_saving_name = "Alaska_Daylight_Time";
					m_short_name = "AKST";
					m_short_daylight_saving_name = "AKDT";
					m_locations = { "North America" };
					m_offset_hours = -9;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = -8;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "America/Anchorage";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::ALMA_ATA_TIME__ALMT__PLUS_H06M00:
					m_long_name = "Alma_Ata_Time";
					m_long_daylight_saving_name = "Alma_Ata_Time";
					m_short_name = "ALMT";
					m_short_daylight_saving_name = "ALMT";
					m_locations = { "Asia" };
					m_offset_hours = 6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::AMAZON_TIME__AMT__MINUS_H04M00:
					m_long_name = "Amazon_Time";
					m_long_daylight_saving_name = "Amazon_Time";
					m_short_name = "AMT";
					m_short_daylight_saving_name = "AMT";
					m_locations = { "South America" };
					m_offset_hours = -4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ARMENIA_TIME__AMT__PLUS_H04M00:
					m_long_name = "Armenia_Time";
					m_long_daylight_saving_name = "Armenia_Time";
					m_short_name = "AMT";
					m_short_daylight_saving_name = "AMT";
					m_locations = { "Asia" };
					m_offset_hours = 4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ANADYR_TIME__ANAT__PLUS_H12M00:
					m_long_name = "Anadyr_Time";
					m_long_daylight_saving_name = "Anadyr_Time";
					m_short_name = "ANAT";
					m_short_daylight_saving_name = "ANAT";
					m_locations = { "Asia" };
					m_offset_hours = 12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::AQTOBE_TIME__AQTT__PLUS_H05M00:
					m_long_name = "Aqtobe_Time";
					m_long_daylight_saving_name = "Aqtobe_Time";
					m_short_name = "AQTT";
					m_short_daylight_saving_name = "AQTT";
					m_locations = { "Asia" };
					m_offset_hours = 5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ARGENTINA_TIME__ART__MINUS_H03M00:
					m_long_name = "Argentina_Time";
					m_long_daylight_saving_name = "Argentina_Time";
					m_short_name = "ART";
					m_short_daylight_saving_name = "ART";
					m_locations = { "Antarctica", "South America" };
					m_offset_hours = -3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ARABIA_STANDARD_TIME__AST__PLUS_H03M00:
					m_long_name = "Arabia_Standard_Time";
					m_long_daylight_saving_name = "Arabia_Standard_Time";
					m_short_name = "AST";
					m_short_daylight_saving_name = "AST";
					m_locations = { "Asia" };
					m_offset_hours = 3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ATLANTIC_STANDARD_TIME__AST__MINUS_H04M00:
					m_long_name = "Atlantic_Standard_Time";
					m_long_daylight_saving_name = "Atlantic_Standard_Time";
					m_short_name = "AST";
					m_short_daylight_saving_name = "AST";
					m_locations = { "North America", "AtlanticCaribbean" };
					m_offset_hours = -4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ATLANTIC_DAYLIGHT_TIME__AT__MINUS_H04M00:
					m_long_name = "Atlantic_Standard_Time";
					m_long_daylight_saving_name = "Atlantic_Daylight_Time";
					m_short_name = "AST";
					m_short_daylight_saving_name = "ADT";
					m_locations = { "North America", "Atlantic (e.g. Bermuda)" };
					m_offset_hours = -4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = -3;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "Atlantic/Bermuda";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::AUSTRALIAN_WESTERN_STANDARD_TIME__AWST__PLUS_H08M00:
					m_long_name = "Australian_Western_Standard_Time";
					m_long_daylight_saving_name = "Australian_Western_Standard_Time";
					m_short_name = "AWST";
					m_short_daylight_saving_name = "AWST";
					m_locations = { "Australia" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::AZORES_TIME__AZOT__MINUS_H01M00:
					m_long_name = "Azores_Time";
					m_long_daylight_saving_name = "Azores_Time";
					m_short_name = "AZOT";
					m_short_daylight_saving_name = "AZOT";
					m_locations = { "Atlantic" };
					m_offset_hours = -1;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::AZERBAIJAN_TIME__AZT__PLUS_H04M00:
					m_long_name = "Azerbaijan_Time";
					m_long_daylight_saving_name = "Azerbaijan_Time";
					m_short_name = "AZT";
					m_short_daylight_saving_name = "AZT";
					m_locations = { "Asia" };
					m_offset_hours = 4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ANYWHERE_ON_EARTH__AOE__MINUS_H12M00:
					m_long_name = "Anywhere_on_Earth";
					m_long_daylight_saving_name = "Anywhere_on_Earth";
					m_short_name = "AoE";
					m_short_daylight_saving_name = "AoE";
					m_locations = { "Pacific" };
					m_offset_hours = -12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::BRAVO_TIME_ZONE__B__PLUS_H02M00:
					m_long_name = "Bravo_Time_Zone";
					m_long_daylight_saving_name = "Bravo_Time_Zone";
					m_short_name = "B";
					m_short_daylight_saving_name = "B";
					m_locations = { "Military" };
					m_offset_hours = 2;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::BRUNEI_DARUSSALAM_TIME__BNT__PLUS_H08M00:
					m_long_name = "Brunei_Darussalam_Time";
					m_long_daylight_saving_name = "Brunei_Darussalam_Time";
					m_short_name = "BNT";
					m_short_daylight_saving_name = "BNT";
					m_locations = { "Asia" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::BOLIVIA_TIME__BOT__MINUS_H04M00:
					m_long_name = "Bolivia_Time";
					m_long_daylight_saving_name = "Bolivia_Time";
					m_short_name = "BOT";
					m_short_daylight_saving_name = "BOT";
					m_locations = { "South America" };
					m_offset_hours = -4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::BRASILIA_TIME__BRT__MINUS_H03M00:
					m_long_name = "Brasilia_Time";
					m_long_daylight_saving_name = "Brasilia_Time";
					m_short_name = "BRT";
					m_short_daylight_saving_name = "BRT";
					m_locations = { "South America" };
					m_offset_hours = -3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::BANGLADESH_STANDARD_TIME__BST__PLUS_H06M00:
					m_long_name = "Bangladesh_Standard_Time";
					m_long_daylight_saving_name = "Bangladesh_Standard_Time";
					m_short_name = "BST";
					m_short_daylight_saving_name = "BST";
					m_locations = { "Asia" };
					m_offset_hours = 6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::BOUGAINVILLE_STANDARD_TIME__BST__PLUS_H11M00:
					m_long_name = "Bougainville_Standard_Time";
					m_long_daylight_saving_name = "Bougainville_Standard_Time";
					m_short_name = "BST";
					m_short_daylight_saving_name = "BST";
					m_locations = { "Pacific" };
					m_offset_hours = 11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::BHUTAN_TIME__BTT__PLUS_H06M00:
					m_long_name = "Bhutan_Time";
					m_long_daylight_saving_name = "Bhutan_Time";
					m_short_name = "BTT";
					m_short_daylight_saving_name = "BTT";
					m_locations = { "Asia" };
					m_offset_hours = 6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CHARLIE_TIME_ZONE__C__PLUS_H03M00:
					m_long_name = "Charlie_Time_Zone";
					m_long_daylight_saving_name = "Charlie_Time_Zone";
					m_short_name = "C";
					m_short_daylight_saving_name = "C";
					m_locations = { "Military" };
					m_offset_hours = 3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CASEY_TIME__CAST__PLUS_H08M00:
					m_long_name = "Casey_Time";
					m_long_daylight_saving_name = "Casey_Time";
					m_short_name = "CAST";
					m_short_daylight_saving_name = "CAST";
					m_locations = { "Antarctica" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CENTRAL_AFRICA_TIME__CAT__PLUS_H02M00:
					m_long_name = "Central_Africa_Time";
					m_long_daylight_saving_name = "Central_Africa_Time";
					m_short_name = "CAT";
					m_short_daylight_saving_name = "CAT";
					m_locations = { "Africa" };
					m_offset_hours = 2;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::COCOS_ISLANDS_TIME__CCT__PLUS_H06M30:
					m_long_name = "Cocos_Islands_Time";
					m_long_daylight_saving_name = "Cocos_Islands_Time";
					m_short_name = "CCT";
					m_short_daylight_saving_name = "CCT";
					m_locations = { "Indian Ocean" };
					m_offset_hours = 6;
					m_offset_minutes = 30;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CUBA_STANDARD_TIME__CST__MINUS_H05M00:
					m_long_name = "Cuba_Standard_Time";
					m_long_daylight_saving_name = "Cuba_Daylight_Time";
					m_short_name = "CST";
					m_short_daylight_saving_name = "CDT";
					m_locations = { "Cuba" };
					m_offset_hours = -5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = -4;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "America/Havana";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::CENTRAL_EUROPEAN_STANDARD_TIME__CET__PLUS_H01M00:
					m_long_name = "Central_European_Time";
					m_long_daylight_saving_name = "Central_European_Time";
					m_short_name = "CET";
					m_short_daylight_saving_name = "CET";
					m_locations = { "Africa" };
					m_offset_hours = 1;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CENTRAL_EUROPEAN_TIME__CET__PLUS_H01M00:
					m_long_name = "Central_European_Time";
					m_long_daylight_saving_name = "Central_European_Summer_Time";
					m_short_name = "CET";
					m_short_daylight_saving_name = "CEST";
					m_locations = { "Europe", "Africa" };
					m_offset_hours = 1;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 2;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "Europe/Berlin";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::CHATHAM_ISLAND_STANDARD_TIME__CHAST__PLUS_H12M45:
					m_long_name = "Chatham_Island_Standard_Time";
					m_long_daylight_saving_name = "Chatham_Island_Daylight_Time";
					m_short_name = "CHAST";
					m_short_daylight_saving_name = "+1345";
					m_locations = { "Pacific" };
					m_offset_hours = 12;
					m_offset_minutes = 45;
					m_offset_hours_while_daylight_saving = 13;
					m_offset_minutes_while_daylight_saving = 45;
					m_tz_path = "Pacific/Chatham";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::CHOIBALSAN_TIME__CHOT__PLUS_H08M00:
					m_long_name = "Choibalsan_Time";
					m_long_daylight_saving_name = "Choibalsan_Time";
					m_short_name = "CHOT";
					m_short_daylight_saving_name = "CHOT";
					m_locations = { "Asia" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CHUUK_TIME__CHUT__PLUS_H10M00:
					m_long_name = "Chuuk_Time";
					m_long_daylight_saving_name = "Chuuk_Time";
					m_short_name = "CHUT";
					m_short_daylight_saving_name = "CHUT";
					m_locations = { "Pacific" };
					m_offset_hours = 10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::COOK_ISLAND_TIME__CKT__MINUS_H10M00:
					m_long_name = "Cook_Island_Time";
					m_long_daylight_saving_name = "Cook_Island_Time";
					m_short_name = "CKT";
					m_short_daylight_saving_name = "CKT";
					m_locations = { "Pacific" };
					m_offset_hours = -10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CHILE_STANDARD_TIME__CLT__MINUS_H04M00:
					m_long_name = "Chile_Standard_Time";
					m_long_daylight_saving_name = "Chile_Standard_Time";
					m_short_name = "CLT";
					m_short_daylight_saving_name = "CLT";
					m_locations = { "South America", "Antarctica" };
					m_offset_hours = -4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::COLOMBIA_TIME__COT__MINUS_H05M00:
					m_long_name = "Colombia_Time";
					m_long_daylight_saving_name = "Colombia_Time";
					m_short_name = "COT";
					m_short_daylight_saving_name = "COT";
					m_locations = { "South America" };
					m_offset_hours = -5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CENTRAL_STANDARD_TIME__CST__MINUS_H06M00:
					m_long_name = "Central_Standard_Time";
					m_long_daylight_saving_name = "Central_Standard_Time";
					m_short_name = "CST";
					m_short_daylight_saving_name = "CST";
					m_locations = { "North America (e.g. Saskatchewan)", "Central America (e.g. Costa Rica, Guatemala)" };
					m_offset_hours = -6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CENTRAL_DAYLIGHT_TIME__CST__MINUS_H06M00:
					m_long_name = "Central_Standard_Time";
					m_long_daylight_saving_name = "Central_Daylight_Time";
					m_short_name = "CST";
					m_short_daylight_saving_name = "CDT";
					m_locations = { "North America (e.g. Alabama, Iowa, Manitoba, Mexico)" };
					m_offset_hours = -6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = -5;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "America/Chicago";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::CHINA_STANDARD_TIME__CST__PLUS_H08M00:
					m_long_name = "China_Standard_Time";
					m_long_daylight_saving_name = "China_Standard_Time";
					m_short_name = "CST";
					m_short_daylight_saving_name = "CST";
					m_locations = { "Asia" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CAPE_VERDE_TIME__CVT__MINUS_H01M00:
					m_long_name = "Cape_Verde_Time";
					m_long_daylight_saving_name = "Cape_Verde_Time";
					m_short_name = "CVT";
					m_short_daylight_saving_name = "CVT";
					m_locations = { "Africa" };
					m_offset_hours = -1;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CHRISTMAS_ISLAND_TIME__CXT__PLUS_H07M00:
					m_long_name = "Christmas_Island_Time";
					m_long_daylight_saving_name = "Christmas_Island_Time";
					m_short_name = "CXT";
					m_short_daylight_saving_name = "CXT";
					m_locations = { "Australia" };
					m_offset_hours = 7;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CHAMORRO_STANDARD_TIME__CHST__PLUS_H10M00:
					m_long_name = "Chamorro_Standard_Time";
					m_long_daylight_saving_name = "Chamorro_Standard_Time";
					m_short_name = "ChST";
					m_short_daylight_saving_name = "ChST";
					m_locations = { "Pacific" };
					m_offset_hours = 10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::DELTA_TIME_ZONE__D__PLUS_H04M00:
					m_long_name = "Delta_Time_Zone";
					m_long_daylight_saving_name = "Delta_Time_Zone";
					m_short_name = "D";
					m_short_daylight_saving_name = "D";
					m_locations = { "Military" };
					m_offset_hours = 4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::DAVIS_TIME__DAVT__PLUS_H07M00:
					m_long_name = "Davis_Time";
					m_long_daylight_saving_name = "Davis_Time";
					m_short_name = "DAVT";
					m_short_daylight_saving_name = "DAVT";
					m_locations = { "Antarctica" };
					m_offset_hours = 7;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::DUMONT_D_URVILLE_TIME__DDUT__PLUS_H10M00:
					m_long_name = "Dumont_d_Urville_Time";
					m_long_daylight_saving_name = "Dumont_d_Urville_Time";
					m_short_name = "DDUT";
					m_short_daylight_saving_name = "DDUT";
					m_locations = { "Antarctica" };
					m_offset_hours = 10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ECHO_TIME_ZONE__E__PLUS_H05M00:
					m_long_name = "Echo_Time_Zone";
					m_long_daylight_saving_name = "Echo_Time_Zone";
					m_short_name = "E";
					m_short_daylight_saving_name = "E";
					m_locations = { "Military" };
					m_offset_hours = 5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::EASTER_ISLAND_STANDARD_TIME__EAST__MINUS_H06M00:
					m_long_name = "Easter_Island_Standard_Time";
					m_long_daylight_saving_name = "Easter_Island_Standard_Time";
					m_short_name = "EAST";
					m_short_daylight_saving_name = "EAST";
					m_locations = { "Pacific" };
					m_offset_hours = -6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::EASTERN_AFRICA_TIME__EAT__PLUS_H03M00:
					m_long_name = "Eastern_Africa_Time";
					m_long_daylight_saving_name = "Eastern_Africa_Time";
					m_short_name = "EAT";
					m_short_daylight_saving_name = "EAT";
					m_locations = { "Africa", "Indian Ocean" };
					m_offset_hours = 3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ECUADOR_TIME__ECT__MINUS_H05M00:
					m_long_name = "Ecuador_Time";
					m_long_daylight_saving_name = "Ecuador_Time";
					m_short_name = "ECT";
					m_short_daylight_saving_name = "ECT";
					m_locations = { "South America" };
					m_offset_hours = -5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::EASTERN_EUROPEAN_TIME__EET__PLUS_H02M00:
					m_long_name = "Eastern_European_Time";
					m_long_daylight_saving_name = "Eastern_European_Time";
					m_short_name = "EET";
					m_short_daylight_saving_name = "EET";
					m_locations = { "Europe", "AsiaAfrica" };
					m_offset_hours = 2;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::EAST_GREENLAND_TIME__EGT__MINUS_H01M00:
					m_long_name = "East_Greenland_Time";
					m_long_daylight_saving_name = "East_Greenland_Time";
					m_short_name = "EGT";
					m_short_daylight_saving_name = "EGT";
					m_locations = { "North America" };
					m_offset_hours = -1;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::EASTERN_STANDARD_TIME__EST__MINUS_H05M00:
					m_long_name = "Eastern_Standard_Time";
					m_long_daylight_saving_name = "Eastern_Standard_Time";
					m_short_name = "EST";
					m_short_daylight_saving_name = "EST";
					m_locations = { "North America (e.g. Coral Harbour)", "Caribbean (e.g. Jamaica)", "Central America (e.g. Panama)" };
					m_offset_hours = -5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::EASTERN_DAYLIGHT_TIME__EST__MINUS_H05M00:
					m_long_name = "Eastern_Standard_Time";
					m_long_daylight_saving_name = "Eastern_Daylight_Time";
					m_short_name = "EST";
					m_short_daylight_saving_name = "EDT";
					m_locations = { "North America (e.g. Georgia, Maryland, Ohio, Quebec)", "Caribbean (e.g. Bahamas, Haiti)" };
					m_offset_hours = -5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = -4;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "America/New_York";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::FOXTROT_TIME_ZONE__F__PLUS_H06M00:
					m_long_name = "Foxtrot_Time_Zone";
					m_long_daylight_saving_name = "Foxtrot_Time_Zone";
					m_short_name = "F";
					m_short_daylight_saving_name = "F";
					m_locations = { "Military" };
					m_offset_hours = 6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::FURTHER_EASTERN_EUROPEAN_TIME__FET__PLUS_H03M00:
					m_long_name = "Further_Eastern_European_Time";
					m_long_daylight_saving_name = "Further_Eastern_European_Time";
					m_short_name = "FET";
					m_short_daylight_saving_name = "FET";
					m_locations = { "Europe" };
					m_offset_hours = 3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::FIJI_TIME__FJT__PLUS_H12M00:
					m_long_name = "Fiji_Time";
					m_long_daylight_saving_name = "Fiji_Time";
					m_short_name = "FJT";
					m_short_daylight_saving_name = "FJT";
					m_locations = { "Pacific" };
					m_offset_hours = 12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::FALKLAND_ISLAND_TIME__FKT__MINUS_H04M00:
					m_long_name = "Falkland_Island_Time";
					m_long_daylight_saving_name = "Falkland_Island_Time";
					m_short_name = "FKT";
					m_short_daylight_saving_name = "FKT";
					m_locations = { "South America" };
					m_offset_hours = -4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::FERNANDO_DE_NORONHA_TIME__FNT__MINUS_H02M00:
					m_long_name = "Fernando_de_Noronha_Time";
					m_long_daylight_saving_name = "Fernando_de_Noronha_Time";
					m_short_name = "FNT";
					m_short_daylight_saving_name = "FNT";
					m_locations = { "South America" };
					m_offset_hours = -2;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::GOLF_TIME_ZONE__G__PLUS_H07M00:
					m_long_name = "Golf_Time_Zone";
					m_long_daylight_saving_name = "Golf_Time_Zone";
					m_short_name = "G";
					m_short_daylight_saving_name = "G";
					m_locations = { "Military" };
					m_offset_hours = 7;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::GALAPAGOS_TIME__GALT__MINUS_H06M00:
					m_long_name = "Galapagos_Time";
					m_long_daylight_saving_name = "Galapagos_Time";
					m_short_name = "GALT";
					m_short_daylight_saving_name = "GALT";
					m_locations = { "Pacific" };
					m_offset_hours = -6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::GAMBIER_TIME__GAMT__MINUS_H09M00:
					m_long_name = "Gambier_Time";
					m_long_daylight_saving_name = "Gambier_Time";
					m_short_name = "GAMT";
					m_short_daylight_saving_name = "GAMT";
					m_locations = { "Pacific" };
					m_offset_hours = -9;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::GEORGIA_STANDARD_TIME__GET__PLUS_H04M00:
					m_long_name = "Georgia_Standard_Time";
					m_long_daylight_saving_name = "Georgia_Standard_Time";
					m_short_name = "GET";
					m_short_daylight_saving_name = "GET";
					m_locations = { "Asia", "Europe" };
					m_offset_hours = 4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::FRENCH_GUIANA_TIME__GFT__MINUS_H03M00:
					m_long_name = "French_Guiana_Time";
					m_long_daylight_saving_name = "French_Guiana_Time";
					m_short_name = "GFT";
					m_short_daylight_saving_name = "GFT";
					m_locations = { "South America" };
					m_offset_hours = -3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::GILBERT_ISLAND_TIME__GILT__PLUS_H12M00:
					m_long_name = "Gilbert_Island_Time";
					m_long_daylight_saving_name = "Gilbert_Island_Time";
					m_short_name = "GILT";
					m_short_daylight_saving_name = "GILT";
					m_locations = { "Pacific" };
					m_offset_hours = 12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::GREENWICH_MEAN_TIME__GMT__PLUS_H00M00:
					m_long_name = "Greenwich_Mean_Time";
					m_long_daylight_saving_name = "Greenwich_Mean_Time";
					m_short_name = "GMT";
					m_short_daylight_saving_name = "GMT";
					m_locations = { "Europe", "AfricaNorth AmericaAntarctica" };
					m_offset_hours = 0;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::GULF_STANDARD_TIME__GST__PLUS_H04M00:
					m_long_name = "Gulf_Standard_Time";
					m_long_daylight_saving_name = "Gulf_Standard_Time";
					m_short_name = "GST";
					m_short_daylight_saving_name = "GST";
					m_locations = { "Asia" };
					m_offset_hours = 4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::SOUTH_GEORGIA_TIME__GST__MINUS_H02M00:
					m_long_name = "South_Georgia_Time";
					m_long_daylight_saving_name = "South_Georgia_Time";
					m_short_name = "GST";
					m_short_daylight_saving_name = "GST";
					m_locations = { "South America" };
					m_offset_hours = -2;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::GUYANA_TIME__GYT__MINUS_H04M00:
					m_long_name = "Guyana_Time";
					m_long_daylight_saving_name = "Guyana_Time";
					m_short_name = "GYT";
					m_short_daylight_saving_name = "GYT";
					m_locations = { "South America" };
					m_offset_hours = -4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::HOTEL_TIME_ZONE__H__PLUS_H08M00:
					m_long_name = "Hotel_Time_Zone";
					m_long_daylight_saving_name = "Hotel_Time_Zone";
					m_short_name = "H";
					m_short_daylight_saving_name = "H";
					m_locations = { "Military" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::HAWAII_ALEUTIAN_DAYLIGHT_TIME__HST__MINUS_H10M00:
					m_long_name = "Hawaii_Standard_Time";
					m_long_daylight_saving_name = "Hawaii_Aleutian_Daylight_Time";
					m_short_name = "HST";
					m_short_daylight_saving_name = "HDT";
					m_locations = { "North America (Aleutian Islands)" };
					m_offset_hours = -10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = -9;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "America/Adak";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::HONG_KONG_TIME__HKT__PLUS_H08M00:
					m_long_name = "Hong_Kong_Time";
					m_long_daylight_saving_name = "Hong_Kong_Time";
					m_short_name = "HKT";
					m_short_daylight_saving_name = "HKT";
					m_locations = { "Asia" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::HOVD_TIME__HOVT__PLUS_H07M00:
					m_long_name = "Hovd_Time";
					m_long_daylight_saving_name = "Hovd_Time";
					m_short_name = "HOVT";
					m_short_daylight_saving_name = "HOVT";
					m_locations = { "Asia" };
					m_offset_hours = 7;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::HAWAII_STANDARD_TIME__HST__MINUS_H10M00:
					m_long_name = "Hawaii_Standard_Time";
					m_long_daylight_saving_name = "Hawaii_Standard_Time";
					m_short_name = "HST";
					m_short_daylight_saving_name = "HST";
					m_locations = { "North America", "Pacific" };
					m_offset_hours = -10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::INDIA_TIME_ZONE__I__PLUS_H09M00:
					m_long_name = "India_Time_Zone";
					m_long_daylight_saving_name = "India_Time_Zone";
					m_short_name = "I";
					m_short_daylight_saving_name = "I";
					m_locations = { "Military" };
					m_offset_hours = 9;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::INDOCHINA_TIME__ICT__PLUS_H07M00:
					m_long_name = "Indochina_Time";
					m_long_daylight_saving_name = "Indochina_Time";
					m_short_name = "ICT";
					m_short_daylight_saving_name = "ICT";
					m_locations = { "Asia" };
					m_offset_hours = 7;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ISRAEL_STANDARD_TIME__IST__PLUS_H02M00:
					m_long_name = "Israel_Standard_Time";
					m_long_daylight_saving_name = "Israel_Daylight_Time";
					m_short_name = "IST";
					m_short_daylight_saving_name = "IDT";
					m_locations = { "Asia" };
					m_offset_hours = 2;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 3;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "Asia/Jerusalem";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::INDIAN_CHAGOS_TIME__IOT__PLUS_H06M00:
					m_long_name = "Indian_Chagos_Time";
					m_long_daylight_saving_name = "Indian_Chagos_Time";
					m_short_name = "IOT";
					m_short_daylight_saving_name = "IOT";
					m_locations = { "Indian Ocean" };
					m_offset_hours = 6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::IRAN_STANDARD_TIME__IRST__PLUS_H03M30:
					m_long_name = "Iran_Standard_Time";
					m_long_daylight_saving_name = "Iran_Daylight_Time";
					m_short_name = "IRST";
					m_short_daylight_saving_name = "+0430";
					m_locations = { "Asia" };
					m_offset_hours = 3;
					m_offset_minutes = 30;
					m_offset_hours_while_daylight_saving = 4;
					m_offset_minutes_while_daylight_saving = 30;
					m_tz_path = "Asia/Tehran";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::IRKUTSK_TIME__IRKT__PLUS_H08M00:
					m_long_name = "Irkutsk_Time";
					m_long_daylight_saving_name = "Irkutsk_Time";
					m_short_name = "IRKT";
					m_short_daylight_saving_name = "IRKT";
					m_locations = { "Asia" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::INDIA_STANDARD_TIME__IST__PLUS_H05M30:
					m_long_name = "India_Standard_Time";
					m_long_daylight_saving_name = "India_Standard_Time";
					m_short_name = "IST";
					m_short_daylight_saving_name = "IST";
					m_locations = { "Asia" };
					m_offset_hours = 5;
					m_offset_minutes = 30;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::IRISH_STANDARD_TIME__IST__PLUS_H01M00:
					m_long_name = "Irish_Standard_Time";
					m_long_daylight_saving_name = "Irish_Standard_Time";
					m_short_name = "IST";
					m_short_daylight_saving_name = "IST";
					m_locations = { "Europe" };
					m_offset_hours = 1;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::JAPAN_STANDARD_TIME__JST__PLUS_H09M00:
					m_long_name = "Japan_Standard_Time";
					m_long_daylight_saving_name = "Japan_Standard_Time";
					m_short_name = "JST";
					m_short_daylight_saving_name = "JST";
					m_locations = { "Asia" };
					m_offset_hours = 9;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::KILO_TIME_ZONE__K__PLUS_H10M00:
					m_long_name = "Kilo_Time_Zone";
					m_long_daylight_saving_name = "Kilo_Time_Zone";
					m_short_name = "K";
					m_short_daylight_saving_name = "K";
					m_locations = { "Military" };
					m_offset_hours = 10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::KYRGYZSTAN_TIME__KGT__PLUS_H06M00:
					m_long_name = "Kyrgyzstan_Time";
					m_long_daylight_saving_name = "Kyrgyzstan_Time";
					m_short_name = "KGT";
					m_short_daylight_saving_name = "KGT";
					m_locations = { "Asia" };
					m_offset_hours = 6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::KOSRAE_TIME__KOST__PLUS_H11M00:
					m_long_name = "Kosrae_Time";
					m_long_daylight_saving_name = "Kosrae_Time";
					m_short_name = "KOST";
					m_short_daylight_saving_name = "KOST";
					m_locations = { "Pacific" };
					m_offset_hours = 11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::KRASNOYARSK_TIME__KRAT__PLUS_H07M00:
					m_long_name = "Krasnoyarsk_Time";
					m_long_daylight_saving_name = "Krasnoyarsk_Time";
					m_short_name = "KRAT";
					m_short_daylight_saving_name = "KRAT";
					m_locations = { "Asia" };
					m_offset_hours = 7;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::KOREA_STANDARD_TIME__KST__PLUS_H09M00:
					m_long_name = "Korea_Standard_Time";
					m_long_daylight_saving_name = "Korea_Standard_Time";
					m_short_name = "KST";
					m_short_daylight_saving_name = "KST";
					m_locations = { "Asia" };
					m_offset_hours = 9;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::KUYBYSHEV_TIME__KUYT__PLUS_H04M00:
					m_long_name = "Kuybyshev_Time";
					m_long_daylight_saving_name = "Kuybyshev_Time";
					m_short_name = "KUYT";
					m_short_daylight_saving_name = "KUYT";
					m_locations = { "Europe" };
					m_offset_hours = 4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::LIMA_TIME_ZONE__L__PLUS_H11M00:
					m_long_name = "Lima_Time_Zone";
					m_long_daylight_saving_name = "Lima_Time_Zone";
					m_short_name = "L";
					m_short_daylight_saving_name = "L";
					m_locations = { "Military" };
					m_offset_hours = 11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::LORD_HOWE_STANDARD_TIME__LHST__PLUS_H10M30:
					m_long_name = "Lord_Howe_Standard_Time";
					m_long_daylight_saving_name = "Lord_Howe_Daylight_Time";
					m_short_name = "LHST";
					m_short_daylight_saving_name = "+11";
					m_locations = { "Australia" };
					m_offset_hours = 10;
					m_offset_minutes = 30;
					m_offset_hours_while_daylight_saving = 11;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "Australia/Lord_Howe";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::LINE_ISLANDS_TIME__LINT__PLUS_H14M00:
					m_long_name = "Line_Islands_Time";
					m_long_daylight_saving_name = "Line_Islands_Time";
					m_short_name = "LINT";
					m_short_daylight_saving_name = "LINT";
					m_locations = { "Pacific" };
					m_offset_hours = 14;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::MIKE_TIME_ZONE__M__PLUS_H12M00:
					m_long_name = "Mike_Time_Zone";
					m_long_daylight_saving_name = "Mike_Time_Zone";
					m_short_name = "M";
					m_short_daylight_saving_name = "M";
					m_locations = { "Military" };
					m_offset_hours = 12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::MAGADAN_TIME__MAGT__PLUS_H11M00:
					m_long_name = "Magadan_Time";
					m_long_daylight_saving_name = "Magadan_Time";
					m_short_name = "MAGT";
					m_short_daylight_saving_name = "MAGT";
					m_locations = { "Asia" };
					m_offset_hours = 11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::MARQUESAS_TIME__MART__MINUS_H09M30:
					m_long_name = "Marquesas_Time";
					m_long_daylight_saving_name = "Marquesas_Time";
					m_short_name = "MART";
					m_short_daylight_saving_name = "MART";
					m_locations = { "Pacific" };
					m_offset_hours = -9;
					m_offset_minutes = 30;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::MAWSON_TIME__MAWT__PLUS_H05M00:
					m_long_name = "Mawson_Time";
					m_long_daylight_saving_name = "Mawson_Time";
					m_short_name = "MAWT";
					m_short_daylight_saving_name = "MAWT";
					m_locations = { "Antarctica" };
					m_offset_hours = 5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::MARSHALL_ISLANDS_TIME__MHT__PLUS_H12M00:
					m_long_name = "Marshall_Islands_Time";
					m_long_daylight_saving_name = "Marshall_Islands_Time";
					m_short_name = "MHT";
					m_short_daylight_saving_name = "MHT";
					m_locations = { "Pacific" };
					m_offset_hours = 12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::MYANMAR_TIME__MMT__PLUS_H06M30:
					m_long_name = "Myanmar_Time";
					m_long_daylight_saving_name = "Myanmar_Time";
					m_short_name = "MMT";
					m_short_daylight_saving_name = "MMT";
					m_locations = { "Asia" };
					m_offset_hours = 6;
					m_offset_minutes = 30;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::MOSCOW_STANDARD_TIME__MSK__PLUS_H03M00:
					m_long_name = "Moscow_Standard_Time";
					m_long_daylight_saving_name = "Moscow_Standard_Time";
					m_short_name = "MSK";
					m_short_daylight_saving_name = "MSK";
					m_locations = { "Europe", "Asia" };
					m_offset_hours = 3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::MOUNTAIN_STANDARD_TIME__MST__MINUS_H07M00:
					m_long_name = "Mountain_Standard_Time";
					m_long_daylight_saving_name = "Mountain_Standard_Time";
					m_short_name = "MST";
					m_short_daylight_saving_name = "MST";
					m_locations = { "North America (e.g. Arizona, Sonora)" };
					m_offset_hours = -7;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::MOUNTAIN_DAYLIGHT_TIME__MST__MINUS_H07M00:
					m_long_name = "Mountain_Standard_Time";
					m_long_daylight_saving_name = "Mountain_Daylight_Time";
					m_short_name = "MST";
					m_short_daylight_saving_name = "MDT";
					m_locations = { "North America (e.g. Colorado, Alberta, Baja California)" };
					m_offset_hours = -7;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = -6;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "America/Edmonton";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::MAURITIUS_TIME__MUT__PLUS_H04M00:
					m_long_name = "Mauritius_Time";
					m_long_daylight_saving_name = "Mauritius_Time";
					m_short_name = "MUT";
					m_short_daylight_saving_name = "MUT";
					m_locations = { "Africa" };
					m_offset_hours = 4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::MALDIVES_TIME__MVT__PLUS_H05M00:
					m_long_name = "Maldives_Time";
					m_long_daylight_saving_name = "Maldives_Time";
					m_short_name = "MVT";
					m_short_daylight_saving_name = "MVT";
					m_locations = { "Asia" };
					m_offset_hours = 5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::MALAYSIA_TIME__MYT__PLUS_H08M00:
					m_long_name = "Malaysia_Time";
					m_long_daylight_saving_name = "Malaysia_Time";
					m_short_name = "MYT";
					m_short_daylight_saving_name = "MYT";
					m_locations = { "Asia" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::NOVEMBER_TIME_ZONE__N__MINUS_H01M00:
					m_long_name = "November_Time_Zone";
					m_long_daylight_saving_name = "November_Time_Zone";
					m_short_name = "N";
					m_short_daylight_saving_name = "N";
					m_locations = { "Military" };
					m_offset_hours = -1;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::NEW_CALEDONIA_TIME__NCT__PLUS_H11M00:
					m_long_name = "New_Caledonia_Time";
					m_long_daylight_saving_name = "New_Caledonia_Time";
					m_short_name = "NCT";
					m_short_daylight_saving_name = "NCT";
					m_locations = { "Pacific" };
					m_offset_hours = 11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::NEWFOUNDLAND_STANDARD_TIME__NDT__MINUS_H03M30:
					m_long_name = "Newfoundland_Standard_Time";
					m_long_daylight_saving_name = "Newfoundland_Daylight_Time";
					m_short_name = "NST";
					m_short_daylight_saving_name = "NDT";
					m_locations = { "North America" };
					m_offset_hours = -3;
					m_offset_minutes = -30;
					m_offset_hours_while_daylight_saving = -2;
					m_offset_minutes_while_daylight_saving = -30;
					m_tz_path = "America/St_Johns";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::NOVOSIBIRSK_TIME__NOVT__PLUS_H07M00:
					m_long_name = "Novosibirsk_Time";
					m_long_daylight_saving_name = "Novosibirsk_Time";
					m_short_name = "NOVT";
					m_short_daylight_saving_name = "NOVT";
					m_locations = { "Asia" };
					m_offset_hours = 7;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::NEPAL_TIME___NPT__PLUS_H05M45:
					m_long_name = "Nepal_Time_";
					m_long_daylight_saving_name = "Nepal_Time_";
					m_short_name = "NPT";
					m_short_daylight_saving_name = "NPT";
					m_locations = { "Asia" };
					m_offset_hours = 5;
					m_offset_minutes = 45;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::NAURU_TIME__NRT__PLUS_H12M00:
					m_long_name = "Nauru_Time";
					m_long_daylight_saving_name = "Nauru_Time";
					m_short_name = "NRT";
					m_short_daylight_saving_name = "NRT";
					m_locations = { "Pacific" };
					m_offset_hours = 12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::NEWFOUNDLAND_STANDARD_TIME__NST__MINUS_H03M30:
					m_long_name = "Newfoundland_Standard_Time";
					m_long_daylight_saving_name = "Newfoundland_Standard_Time";
					m_short_name = "NST";
					m_short_daylight_saving_name = "NST";
					m_locations = { "North America" };
					m_offset_hours = -3;
					m_offset_minutes = 30;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::NIUE_TIME__NUT__MINUS_H11M00:
					m_long_name = "Niue_Time";
					m_long_daylight_saving_name = "Niue_Time";
					m_short_name = "NUT";
					m_short_daylight_saving_name = "NUT";
					m_locations = { "Pacific" };
					m_offset_hours = -11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::NEW_ZEALAND_STANDARD_TIME__NZST__PLUS_H12M00:
					m_long_name = "New_Zealand_Standard_Time";
					m_long_daylight_saving_name = "New_Zealand_Daylight_Time";
					m_short_name = "NZST";
					m_short_daylight_saving_name = "NZDT";
					m_locations = { "Pacific (e.g. New Zealand)", "Antarctica (e.g. McMurdo Station)" };
					m_offset_hours = 12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 13;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "Pacific/Auckland";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::OSCAR_TIME_ZONE__O__MINUS_H02M00:
					m_long_name = "Oscar_Time_Zone";
					m_long_daylight_saving_name = "Oscar_Time_Zone";
					m_short_name = "O";
					m_short_daylight_saving_name = "O";
					m_locations = { "Military" };
					m_offset_hours = -2;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::OMSK_STANDARD_TIME__OMST__PLUS_H06M00:
					m_long_name = "Omsk_Standard_Time";
					m_long_daylight_saving_name = "Omsk_Standard_Time";
					m_short_name = "OMST";
					m_short_daylight_saving_name = "OMST";
					m_locations = { "Asia" };
					m_offset_hours = 6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ORAL_TIME__ORAT__PLUS_H05M00:
					m_long_name = "Oral_Time";
					m_long_daylight_saving_name = "Oral_Time";
					m_short_name = "ORAT";
					m_short_daylight_saving_name = "ORAT";
					m_locations = { "Asia" };
					m_offset_hours = 5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::PAPA_TIME_ZONE__P__MINUS_H03M00:
					m_long_name = "Papa_Time_Zone";
					m_long_daylight_saving_name = "Papa_Time_Zone";
					m_short_name = "P";
					m_short_daylight_saving_name = "P";
					m_locations = { "Military" };
					m_offset_hours = -3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::PERU_TIME__PET__MINUS_H05M00:
					m_long_name = "Peru_Time";
					m_long_daylight_saving_name = "Peru_Time";
					m_short_name = "PET";
					m_short_daylight_saving_name = "PET";
					m_locations = { "South America" };
					m_offset_hours = -5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::KAMCHATKA_TIME__PETT__PLUS_H12M00:
					m_long_name = "Kamchatka_Time";
					m_long_daylight_saving_name = "Kamchatka_Time";
					m_short_name = "PETT";
					m_short_daylight_saving_name = "PETT";
					m_locations = { "Asia" };
					m_offset_hours = 12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::PAPUA_NEW_GUINEA_TIME__PGT__PLUS_H10M00:
					m_long_name = "Papua_New_Guinea_Time";
					m_long_daylight_saving_name = "Papua_New_Guinea_Time";
					m_short_name = "PGT";
					m_short_daylight_saving_name = "PGT";
					m_locations = { "Pacific" };
					m_offset_hours = 10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::PHOENIX_ISLAND_TIME__PHOT__PLUS_H13M00:
					m_long_name = "Phoenix_Island_Time";
					m_long_daylight_saving_name = "Phoenix_Island_Time";
					m_short_name = "PHOT";
					m_short_daylight_saving_name = "PHOT";
					m_locations = { "Pacific" };
					m_offset_hours = 13;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::PHILIPPINE_TIME__PHT__PLUS_H08M00:
					m_long_name = "Philippine_Time";
					m_long_daylight_saving_name = "Philippine_Time";
					m_short_name = "PHT";
					m_short_daylight_saving_name = "PHT";
					m_locations = { "Asia" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::PAKISTAN_STANDARD_TIME__PKT__PLUS_H05M00:
					m_long_name = "Pakistan_Standard_Time";
					m_long_daylight_saving_name = "Pakistan_Standard_Time";
					m_short_name = "PKT";
					m_short_daylight_saving_name = "PKT";
					m_locations = { "Asia" };
					m_offset_hours = 5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::PIERRE_MIQUELON_STANDARD_TIME__PMST__MINUS_H03M00:
					m_long_name = "Pierre_Miquelon_Standard_Time";
					m_long_daylight_saving_name = "Pierre_Miquelon_Daylight_Time";
					m_short_name = "PMST";
					m_short_daylight_saving_name = "-02";
					m_locations = { "North America (Saint Pierre and Miquelon)" };
					m_offset_hours = -3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = -2;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "America/Miquelon";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::POHNPEI_STANDARD_TIME__PONT__PLUS_H11M00:
					m_long_name = "Pohnpei_Standard_Time";
					m_long_daylight_saving_name = "Pohnpei_Standard_Time";
					m_short_name = "PONT";
					m_short_daylight_saving_name = "PONT";
					m_locations = { "Pacific" };
					m_offset_hours = 11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::PACIFIC_STANDARD_TIME__PST__MINUS_H08M00:
					m_long_name = "Pacific_Standard_Time";
					m_long_daylight_saving_name = "Pacific_Daylight_Time";
					m_short_name = "PST";
					m_short_daylight_saving_name = "PDT";
					m_locations = { "North America (e.g. California, Nevada, Yukon)" };
					m_offset_hours = -8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = -7;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "America/Los_Angeles";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::PITCAIRN_STANDARD_TIME__PST__MINUS_H08M00:
					m_long_name = "Pitcairn_Standard_Time";
					m_long_daylight_saving_name = "Pitcairn_Standard_Time";
					m_short_name = "PST";
					m_short_daylight_saving_name = "PST";
					m_locations = { "Pacific" };
					m_offset_hours = -8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::PALAU_TIME__PWT__PLUS_H09M00:
					m_long_name = "Palau_Time";
					m_long_daylight_saving_name = "Palau_Time";
					m_short_name = "PWT";
					m_short_daylight_saving_name = "PWT";
					m_locations = { "Pacific" };
					m_offset_hours = 9;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::PARAGUAY_TIME__PYT__MINUS_H04M00:
					m_long_name = "Paraguay_Time";
					m_long_daylight_saving_name = "Paraguay_Time";
					m_short_name = "PYT";
					m_short_daylight_saving_name = "PYT";
					m_locations = { "South America" };
					m_offset_hours = -4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::PYONGYANG_TIME__PYT__PLUS_H08M30:
					m_long_name = "Pyongyang_Time";
					m_long_daylight_saving_name = "Pyongyang_Time";
					m_short_name = "PYT";
					m_short_daylight_saving_name = "PYT";
					m_locations = { "Asia" };
					m_offset_hours = 8;
					m_offset_minutes = 30;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::QUEBEC_TIME_ZONE__Q__MINUS_H04M00:
					m_long_name = "Quebec_Time_Zone";
					m_long_daylight_saving_name = "Quebec_Time_Zone";
					m_short_name = "Q";
					m_short_daylight_saving_name = "Q";
					m_locations = { "Military" };
					m_offset_hours = -4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::QYZYLORDA_TIME__QYZT__PLUS_H06M00:
					m_long_name = "Qyzylorda_Time";
					m_long_daylight_saving_name = "Qyzylorda_Time";
					m_short_name = "QYZT";
					m_short_daylight_saving_name = "QYZT";
					m_locations = { "Asia" };
					m_offset_hours = 6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ROMEO_TIME_ZONE__R__MINUS_H05M00:
					m_long_name = "Romeo_Time_Zone";
					m_long_daylight_saving_name = "Romeo_Time_Zone";
					m_short_name = "R";
					m_short_daylight_saving_name = "R";
					m_locations = { "Military" };
					m_offset_hours = -5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::REUNION_TIME__RET__PLUS_H04M00:
					m_long_name = "Reunion_Time";
					m_long_daylight_saving_name = "Reunion_Time";
					m_short_name = "RET";
					m_short_daylight_saving_name = "RET";
					m_locations = { "Africa" };
					m_offset_hours = 4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ROTHERA_TIME__ROTT__MINUS_H03M00:
					m_long_name = "Rothera_Time";
					m_long_daylight_saving_name = "Rothera_Time";
					m_short_name = "ROTT";
					m_short_daylight_saving_name = "ROTT";
					m_locations = { "Antarctica" };
					m_offset_hours = -3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::SIERRA_TIME_ZONE__S__MINUS_H06M00:
					m_long_name = "Sierra_Time_Zone";
					m_long_daylight_saving_name = "Sierra_Time_Zone";
					m_short_name = "S";
					m_short_daylight_saving_name = "S";
					m_locations = { "Military" };
					m_offset_hours = -6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::SAKHALIN_TIME__SAKT__PLUS_H11M00:
					m_long_name = "Sakhalin_Time";
					m_long_daylight_saving_name = "Sakhalin_Time";
					m_short_name = "SAKT";
					m_short_daylight_saving_name = "SAKT";
					m_locations = { "Asia" };
					m_offset_hours = 11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::SAMARA_TIME__SAMT__PLUS_H04M00:
					m_long_name = "Samara_Time";
					m_long_daylight_saving_name = "Samara_Time";
					m_short_name = "SAMT";
					m_short_daylight_saving_name = "SAMT";
					m_locations = { "Europe" };
					m_offset_hours = 4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::SOUTH_AFRICA_STANDARD_TIME__SAST__PLUS_H02M00:
					m_long_name = "South_Africa_Standard_Time";
					m_long_daylight_saving_name = "South_Africa_Standard_Time";
					m_short_name = "SAST";
					m_short_daylight_saving_name = "SAST";
					m_locations = { "Africa" };
					m_offset_hours = 2;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::SOLOMON_ISLANDS_TIME__SBT__PLUS_H11M00:
					m_long_name = "Solomon_Islands_Time";
					m_long_daylight_saving_name = "Solomon_Islands_Time";
					m_short_name = "SBT";
					m_short_daylight_saving_name = "SBT";
					m_locations = { "Pacific" };
					m_offset_hours = 11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::SEYCHELLES_TIME__SCT__PLUS_H04M00:
					m_long_name = "Seychelles_Time";
					m_long_daylight_saving_name = "Seychelles_Time";
					m_short_name = "SCT";
					m_short_daylight_saving_name = "SCT";
					m_locations = { "Africa" };
					m_offset_hours = 4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::SINGAPORE_TIME__SGT__PLUS_H08M00:
					m_long_name = "Singapore_Time";
					m_long_daylight_saving_name = "Singapore_Time";
					m_short_name = "SGT";
					m_short_daylight_saving_name = "SGT";
					m_locations = { "Asia" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::SREDNEKOLYMSK_TIME__SRET__PLUS_H11M00:
					m_long_name = "Srednekolymsk_Time";
					m_long_daylight_saving_name = "Srednekolymsk_Time";
					m_short_name = "SRET";
					m_short_daylight_saving_name = "SRET";
					m_locations = { "Asia" };
					m_offset_hours = 11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::SURINAME_TIME__SRT__MINUS_H03M00:
					m_long_name = "Suriname_Time";
					m_long_daylight_saving_name = "Suriname_Time";
					m_short_name = "SRT";
					m_short_daylight_saving_name = "SRT";
					m_locations = { "South America" };
					m_offset_hours = -3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::SAMOA_STANDARD_TIME__SST__MINUS_H11M00:
					m_long_name = "Samoa_Standard_Time";
					m_long_daylight_saving_name = "Samoa_Standard_Time";
					m_short_name = "SST";
					m_short_daylight_saving_name = "SST";
					m_locations = { "Pacific" };
					m_offset_hours = -11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::SYOWA_TIME__SYOT__PLUS_H03M00:
					m_long_name = "Syowa_Time";
					m_long_daylight_saving_name = "Syowa_Time";
					m_short_name = "SYOT";
					m_short_daylight_saving_name = "SYOT";
					m_locations = { "Antarctica" };
					m_offset_hours = 3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::TANGO_TIME_ZONE__T__MINUS_H07M00:
					m_long_name = "Tango_Time_Zone";
					m_long_daylight_saving_name = "Tango_Time_Zone";
					m_short_name = "T";
					m_short_daylight_saving_name = "T";
					m_locations = { "Military" };
					m_offset_hours = -7;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::TAHITI_TIME__TAHT__MINUS_H10M00:
					m_long_name = "Tahiti_Time";
					m_long_daylight_saving_name = "Tahiti_Time";
					m_short_name = "TAHT";
					m_short_daylight_saving_name = "TAHT";
					m_locations = { "Pacific" };
					m_offset_hours = -10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::FRENCH_SOUTHERN_AND_ANTARCTIC_TIME__TFT__PLUS_H05M00:
					m_long_name = "French_Southern_and_Antarctic_Time";
					m_long_daylight_saving_name = "French_Southern_and_Antarctic_Time";
					m_short_name = "TFT";
					m_short_daylight_saving_name = "TFT";
					m_locations = { "Indian Ocean" };
					m_offset_hours = 5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::TAJIKISTAN_TIME__TJT__PLUS_H05M00:
					m_long_name = "Tajikistan_Time";
					m_long_daylight_saving_name = "Tajikistan_Time";
					m_short_name = "TJT";
					m_short_daylight_saving_name = "TJT";
					m_locations = { "Asia" };
					m_offset_hours = 5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::TOKELAU_TIME__TKT__PLUS_H13M00:
					m_long_name = "Tokelau_Time";
					m_long_daylight_saving_name = "Tokelau_Time";
					m_short_name = "TKT";
					m_short_daylight_saving_name = "TKT";
					m_locations = { "Pacific" };
					m_offset_hours = 13;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::EAST_TIMOR_TIME__TLT__PLUS_H09M00:
					m_long_name = "East_Timor_Time";
					m_long_daylight_saving_name = "East_Timor_Time";
					m_short_name = "TLT";
					m_short_daylight_saving_name = "TLT";
					m_locations = { "Asia" };
					m_offset_hours = 9;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::TURKMENISTAN_TIME__TMT__PLUS_H05M00:
					m_long_name = "Turkmenistan_Time";
					m_long_daylight_saving_name = "Turkmenistan_Time";
					m_short_name = "TMT";
					m_short_daylight_saving_name = "TMT";
					m_locations = { "Asia" };
					m_offset_hours = 5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::TONGA_TIME__TOT__PLUS_H13M00:
					m_long_name = "Tonga_Time";
					m_long_daylight_saving_name = "Tonga_Time";
					m_short_name = "TOT";
					m_short_daylight_saving_name = "TOT";
					m_locations = { "Pacific" };
					m_offset_hours = 13;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::TURKEY_TIME__TRT__PLUS_H03M00:
					m_long_name = "Turkey_Time";
					m_long_daylight_saving_name = "Turkey_Time";
					m_short_name = "TRT";
					m_short_daylight_saving_name = "TRT";
					m_locations = { "Asia", "Europe" };
					m_offset_hours = 3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::TUVALU_TIME__TVT__PLUS_H12M00:
					m_long_name = "Tuvalu_Time";
					m_long_daylight_saving_name = "Tuvalu_Time";
					m_short_name = "TVT";
					m_short_daylight_saving_name = "TVT";
					m_locations = { "Pacific" };
					m_offset_hours = 12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::UNIFORM_TIME_ZONE__U__MINUS_H08M00:
					m_long_name = "Uniform_Time_Zone";
					m_long_daylight_saving_name = "Uniform_Time_Zone";
					m_short_name = "U";
					m_short_daylight_saving_name = "U";
					m_locations = { "Military" };
					m_offset_hours = -8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ULAANBAATAR_TIME__ULAT__PLUS_H08M00:
					m_long_name = "Ulaanbaatar_Time";
					m_long_daylight_saving_name = "Ulaanbaatar_Time";
					m_short_name = "ULAT";
					m_short_daylight_saving_name = "ULAT";
					m_locations = { "Asia" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::COORDINATED_UNIVERSAL_TIME__UTC__PLUS_H00M00:
					m_long_name = "Coordinated_Universal_Time";
					m_long_daylight_saving_name = "Coordinated_Universal_Time";
					m_short_name = "UTC";
					m_short_daylight_saving_name = "UTC";
					m_locations = { "Worldwide" };
					m_offset_hours = 0;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::URUGUAY_TIME__UYT__MINUS_H03M00:
					m_long_name = "Uruguay_Time";
					m_long_daylight_saving_name = "Uruguay_Time";
					m_short_name = "UYT";
					m_short_daylight_saving_name = "UYT";
					m_locations = { "South America" };
					m_offset_hours = -3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::UZBEKISTAN_TIME__UZT__PLUS_H05M00:
					m_long_name = "Uzbekistan_Time";
					m_long_daylight_saving_name = "Uzbekistan_Time";
					m_short_name = "UZT";
					m_short_daylight_saving_name = "UZT";
					m_locations = { "Asia" };
					m_offset_hours = 5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::VICTOR_TIME_ZONE__V__MINUS_H09M00:
					m_long_name = "Victor_Time_Zone";
					m_long_daylight_saving_name = "Victor_Time_Zone";
					m_short_name = "V";
					m_short_daylight_saving_name = "V";
					m_locations = { "Military" };
					m_offset_hours = -9;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::VENEZUELAN_STANDARD_TIME__VET__MINUS_H04M00:
					m_long_name = "Venezuelan_Standard_Time";
					m_long_daylight_saving_name = "Venezuelan_Standard_Time";
					m_short_name = "VET";
					m_short_daylight_saving_name = "VET";
					m_locations = { "South America" };
					m_offset_hours = -4;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::VLADIVOSTOK_TIME__VLAT__PLUS_H10M00:
					m_long_name = "Vladivostok_Time";
					m_long_daylight_saving_name = "Vladivostok_Time";
					m_short_name = "VLAT";
					m_short_daylight_saving_name = "VLAT";
					m_locations = { "Asia" };
					m_offset_hours = 10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::VOSTOK_TIME__VOST__PLUS_H06M00:
					m_long_name = "Vostok_Time";
					m_long_daylight_saving_name = "Vostok_Time";
					m_short_name = "VOST";
					m_short_daylight_saving_name = "VOST";
					m_locations = { "Antarctica" };
					m_offset_hours = 6;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::VANUATU_TIME__VUT__PLUS_H11M00:
					m_long_name = "Vanuatu_Time";
					m_long_daylight_saving_name = "Vanuatu_Time";
					m_short_name = "VUT";
					m_short_daylight_saving_name = "VUT";
					m_locations = { "Pacific" };
					m_offset_hours = 11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::WHISKEY_TIME_ZONE__W__MINUS_H10M00:
					m_long_name = "Whiskey_Time_Zone";
					m_long_daylight_saving_name = "Whiskey_Time_Zone";
					m_short_name = "W";
					m_short_daylight_saving_name = "W";
					m_locations = { "Military" };
					m_offset_hours = -10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::WAKE_TIME__WAKT__PLUS_H12M00:
					m_long_name = "Wake_Time";
					m_long_daylight_saving_name = "Wake_Time";
					m_short_name = "WAKT";
					m_short_daylight_saving_name = "WAKT";
					m_locations = { "Pacific" };
					m_offset_hours = 12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::WEST_AFRICA_TIME__WAT__PLUS_H01M00:
					m_long_name = "West_Africa_Time";
					m_long_daylight_saving_name = "West_Africa_Time";
					m_short_name = "WAT";
					m_short_daylight_saving_name = "WAT";
					m_locations = { "Africa" };
					m_offset_hours = 1;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::WESTERN_EUROPEAN_TIME__WET__PLUS_H00M00:
					m_long_name = "Western_European_Time";
					m_long_daylight_saving_name = "Western_European_Time";
					m_short_name = "WET";
					m_short_daylight_saving_name = "WET";
					m_locations = { "Europe", "Africa" };
					m_offset_hours = 0;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::WALLIS_AND_FUTUNA_TIME__WFT__PLUS_H12M00:
					m_long_name = "Wallis_and_Futuna_Time";
					m_long_daylight_saving_name = "Wallis_and_Futuna_Time";
					m_short_name = "WFT";
					m_short_daylight_saving_name = "WFT";
					m_locations = { "Pacific" };
					m_offset_hours = 12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::WEST_GREENLAND_TIME__WGT__MINUS_H03M00:
					m_long_name = "West_Greenland_Time";
					m_long_daylight_saving_name = "West_Greenland_Summer_Time";
					m_short_name = "WGT";
					m_short_daylight_saving_name = "-02";
					m_locations = { "North America" };
					m_offset_hours = -3;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = -2;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "America/Godthab";
					m_uses_daylight_saving = true;
					break;
				case WorldTimezones::WESTERN_INDONESIAN_TIME__WIB__PLUS_H07M00:
					m_long_name = "Western_Indonesian_Time";
					m_long_daylight_saving_name = "Western_Indonesian_Time";
					m_short_name = "WIB";
					m_short_daylight_saving_name = "WIB";
					m_locations = { "Asia" };
					m_offset_hours = 7;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::EASTERN_INDONESIAN_TIME__WIT__PLUS_H09M00:
					m_long_name = "Eastern_Indonesian_Time";
					m_long_daylight_saving_name = "Eastern_Indonesian_Time";
					m_short_name = "WIT";
					m_short_daylight_saving_name = "WIT";
					m_locations = { "Asia" };
					m_offset_hours = 9;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::CENTRAL_INDONESIAN_TIME__WITA__PLUS_H08M00:
					m_long_name = "Central_Indonesian_Time";
					m_long_daylight_saving_name = "Central_Indonesian_Time";
					m_short_name = "WITA";
					m_short_daylight_saving_name = "WITA";
					m_locations = { "Asia" };
					m_offset_hours = 8;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::WEST_SAMOA_TIME__WST__PLUS_H14M00:
					m_long_name = "West_Samoa_Time";
					m_long_daylight_saving_name = "West_Samoa_Time";
					m_short_name = "WST";
					m_short_daylight_saving_name = "WST";
					m_locations = { "Pacific" };
					m_offset_hours = 14;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::WESTERN_SAHARA_STANDARD_TIME__WT__PLUS_H00M00:
					m_long_name = "Western_Sahara_Standard_Time";
					m_long_daylight_saving_name = "Western_Sahara_Standard_Time";
					m_short_name = "WT";
					m_short_daylight_saving_name = "WT";
					m_locations = { "Africa" };
					m_offset_hours = 0;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::X_RAY_TIME_ZONE__X__MINUS_H11M00:
					m_long_name = "X_ray_Time_Zone";
					m_long_daylight_saving_name = "X_ray_Time_Zone";
					m_short_name = "X";
					m_short_daylight_saving_name = "X";
					m_locations = { "Military" };
					m_offset_hours = -11;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::YANKEE_TIME_ZONE__Y__MINUS_H12M00:
					m_long_name = "Yankee_Time_Zone";
					m_long_daylight_saving_name = "Yankee_Time_Zone";
					m_short_name = "Y";
					m_short_daylight_saving_name = "Y";
					m_locations = { "Military" };
					m_offset_hours = -12;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::YAKUTSK_TIME__YAKT__PLUS_H09M00:
					m_long_name = "Yakutsk_Time";
					m_long_daylight_saving_name = "Yakutsk_Time";
					m_short_name = "YAKT";
					m_short_daylight_saving_name = "YAKT";
					m_locations = { "Asia" };
					m_offset_hours = 9;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::YAP_TIME__YAPT__PLUS_H10M00:
					m_long_name = "Yap_Time";
					m_long_daylight_saving_name = "Yap_Time";
					m_short_name = "YAPT";
					m_short_daylight_saving_name = "YAPT";
					m_locations = { "Pacific" };
					m_offset_hours = 10;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::YEKATERINBURG_TIME__YEKT__PLUS_H05M00:
					m_long_name = "Yekaterinburg_Time";
					m_long_daylight_saving_name = "Yekaterinburg_Time";
					m_short_name = "YEKT";
					m_short_daylight_saving_name = "YEKT";
					m_locations = { "Asia" };
					m_offset_hours = 5;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				case WorldTimezones::ZULU_TIME_ZONE__Z__PLUS_H00M00:
					m_long_name = "Zulu_Time_Zone";
					m_long_daylight_saving_name = "Zulu_Time_Zone";
					m_short_name = "Z";
					m_short_daylight_saving_name = "Z";
					m_locations = { "Military" };
					m_offset_hours = 0;
					m_offset_minutes = 0;
					m_offset_hours_while_daylight_saving = 0;
					m_offset_minutes_while_daylight_saving = 0;
					m_tz_path = "";
					m_uses_daylight_saving = false;
					break;
				default:
					throw exception::HALException("DS3231Definitions", "CurrentTimezone constructor", "invalid timezone enum value");
				}

				m_current_timezone = timezone;
				m_is_currently_daylight_saving = false;
				m_last_daylight_saving_check = 0;
				m_daylight_saving_check_interval = 86400; // 60 * 60 * 24 -> one time each day
				update_daylight_status();
			}

			//! Converts an utc time to the time in the timezone that is represented by this class.
			/*!
			* Converts an utc time to the time in the timezone that is represented by this class.
			* \param[out] utc_time: The utc time to convert.
			* \param[in] time_is_now: Whether the given time is now or a time in the future/past.
			* Depending on this value the check if daylight saving is used is performed only once per
			* day (time is now) or at each function call (time is not now). Performing the check at
			* each function call has a significant impact on performance and should be avoided.
			*/
			void apply_timezone(time_t& utc_time, bool time_is_now = true)
			{
				auto tm = *gmtime(&utc_time);
				apply_timezone(tm, time_is_now);
				utc_time = mktime(&tm);
			}

			//! Converts an utc time to the time in the timezone that is represented by this class.
			/*!
			* Converts an utc time to the time in the timezone that is represented by this class.
			* \param[out] utc_time: The utc time to convert.
			* \param[in] time_is_now: Whether the given time is now or a time in the future/past.
			* Depending on this value the check if daylight saving is used is performed only once per
			* day (time is now) or at each function call (time is not now). Performing the check at
			* each function call has a significant impact on performance and should be avoided.
			*/
			void apply_timezone(tm& utc_time, bool time_is_now = true)
			{
				if (time_is_now ? is_daylight_saving_now() : is_daylight_saving_at_time(utc_time))
				{
					// We have daylight saving time
					add_offset(utc_time, m_offset_hours_while_daylight_saving, m_offset_minutes_while_daylight_saving);

				}
				else
				{
					// We have winter time or do not switch the time during the year
					add_offset(utc_time, m_offset_hours, m_offset_minutes);
				}
			}

			//! Returns the enum value of the current timezone.
			/*!
			* Returns the enum value of the current timezone.
			* \returns The enum value of the current timezone.
			*/
			WorldTimezones get_timezone() const noexcept
			{
				return m_current_timezone;
			}

			//! Returns the name of the current timezone.
			/*!
			* Returns the name of the current timezone.
			* \returns The name of the current timezone.
			*/
			std::string get_timezone_name() const noexcept
			{
				return m_long_name;
			}

			//! Returns the abbreviation of the current timezone.
			/*!
			* Returns the abbreviation of the current timezone.
			* \returns The abbreviation of the current timezone.
			*/
			std::string get_timezone_abbreviation() const noexcept
			{
				return m_short_name;
			}

			//! Returns the daylight saving name of the current timezone.
			/*!
			* Returns the daylight saving name of the current timezone.
			* If the timezone has no daylight saving the normal name will
			* be returned.
			* \returns The daylight saving name of the current timezone.
			*/
			std::string get_daylight_saving_timezone_name() const noexcept
			{
				return m_long_daylight_saving_name;
			}

			//! Returns the daylight saving abbreviation of the current timezone.
			/*!
			* Returns the daylight saving abbreviation of the current timezone.
			* If the timezone has no daylight saving the normal abbreviation will
			* be returned.
			* The abbreviation does not need to be the official one. Since it is
			* internally also needed to decide if daylight saving is currently in
			* use, the value equals to the result of the Linux command
			* 'TZ="path_to_tz" date +%Z'.
			* For some timezone this will only return the offset in hours and minutes
			* as string (e.g. Iran's abbreviation is '+0430' instead of 'IRDT').
			* \returns The daylight saving abbreviation of the current timezone.
			*/
			std::string get_daylight_saving_timezone_abbreviation() const noexcept
			{
				return m_short_daylight_saving_name;
			}

			//! Returns the locations the timezone is used in.
			/*!
			* Returns the locations the timezone is used in. Basically it will just
			* return the continents but for some timezones - mostly the ones with daylight
			* saving - there are also some example countries / states given.
			* \returns The locations the timezone is used in.
			*/
			std::vector<std::string> get_timezone_locations() const noexcept
			{
				return m_locations;
			}

			//! Returns the hour and minute offset of the timezone.
			/*!
			* Returns the hour and minute offset of the timezone.
			* \param[out] hours: The hour offset of the timezone (including its sign).
			* \param[out] minutes: The minute offset of the timezone (including its sign).
			*/
			void timezone_offset_to_utc(int8_t& hours, int8_t& minutes) const noexcept
			{
				hours = m_offset_hours;
				minutes = m_offset_minutes;
			}

			//! Returns the hour and minute offset of the timezone during daylight saving.
			/*!
			* Returns the hour and minute offset of the timezone during daylight saving.
			* If the timezone does not have daylight saving the normal offset will be returned.
			* \param[out] hours: The hour offset of the timezone (including its sign).
			* \param[out] minutes: The minute offset of the timezone (including its sign).
			*/
			void timezone_daylight_saving_offset_to_utc(int8_t& hours, int8_t& minutes) const noexcept
			{
				if (uses_daylight_saving())
				{
					hours = m_offset_hours_while_daylight_saving;
					minutes = m_offset_minutes_while_daylight_saving;
				}
				else
				{
					timezone_offset_to_utc(hours, minutes);
				}
			}

			//! Returns whether the timezone uses daylight saving.
			/*!
			* Returns whether the timezone uses daylight saving.
			* \returns True if the timezone uses daylight saving, false otherwise.
			*/
			bool uses_daylight_saving() const noexcept
			{
				return m_uses_daylight_saving;
			}

			//! Returns whether the timezone is currently daylight saving.
			/*!
			* Returns whether the timezone is currently daylight saving. If the timezone
			* does not use daylight saving this method will always return false.
			* \returns True if the timezone is currently daylight saving, false otherwise.
			* \throws HALException if getting daylight saving information from Linux fails.
			*/
			bool is_daylight_saving_now()
			{
				if (uses_daylight_saving())
				{
					if (time(nullptr) - m_last_daylight_saving_check + m_daylight_saving_check_interval <= 0)
					{
						update_daylight_status();
					}
					return m_is_currently_daylight_saving;
				}
				return false;
			}

			//! Returns whether the timezone is daylight saving at the given date.
			/*!
			* Returns whether the timezone is daylight saving at the given date. If the timezone
			* does not use daylight saving this method will always return false.
			* \returns True if the timezone is daylight saving at the given date, false otherwise.
			* \throws HALException if getting daylight saving information from Linux fails.
			*/
			bool is_daylight_saving_at_time(time_t date) const
			{
				const auto tm = *gmtime(&date);
				return is_daylight_saving_at_time(tm);
			}

			//! Returns whether the timezone is daylight saving at the given date.
			/*!
			* Returns whether the timezone is daylight saving at the given date. If the timezone
			* does not use daylight saving this method will always return false.
			* \returns True if the timezone is daylight saving at the given date, false otherwise.
			* \throws HALException if getting daylight saving information from Linux fails.
			*/
			bool is_daylight_saving_at_time(tm date) const
			{
				std::stringstream ss;
				ss << std::put_time(&date, "%c");
				try
				{
					const auto result = TerminalAccess::call_command(std::string("TZ=\"").append(m_tz_path).append("\" date -d \"").append(ss.str()).append("\" +%Z"));
					return result == m_short_daylight_saving_name;
				}
				catch (exception::HALException& ex)
				{
					throw exception::HALException("CurrentTimezone", "is_daylight_saving_at_time", std::string("Could not get daylight saving information: ")
						.append(ex.get_message()));
				}
			}

			//! Rechecks if the timezone is currently daylight saving by performing a Linux command call.
			/*!
			* Rechecks if the timezone is currently daylight saving by performing a Linux command call and
			* resetting the automatic update process. If the timezone does not use daylight saving this
			* method will do nothing.
			* \returns True if the timezone is daylight saving at the given date, false otherwise.
			* \throws HALException if getting daylight saving information from Linux fails.
			*/
			void update_daylight_status()
			{
				try
				{
					if (uses_daylight_saving())
					{
						const auto result = TerminalAccess::call_command(std::string("TZ=\"").append(m_tz_path).append("\" date +%Z"));
						m_is_currently_daylight_saving = result == m_short_daylight_saving_name;
						m_last_daylight_saving_check = time(nullptr);
					}
				}
				catch (exception::HALException& ex)
				{
					throw exception::HALException("CurrentTimezone", "update_daylight_status", std::string("Could not get daylight saving information: ")
						.append(ex.get_message()));
				}
			}

			//! Converts a month day (1-31) to the corresponding year day (0-365).
			/*!
			* Converts a month day (1-31) to the corresponding year day (0-365).
			* \param[out] utc_time: The utc time that contains the month day to
			* convert. The result will be written to this variable, too and will appear
			* in the field 'tm_yday'.
			*/
			static void month_day_to_year_day(tm& utc_time)
			{
				auto y_day = utc_time.tm_mday;
				for (auto i = utc_time.tm_mon - 1; i >= 0; --i)
				{
					switch (i)
					{
					case 0:
						y_day += 31;
						continue;
					case 1:
						if (is_leapyear(utc_time.tm_year))
						{
							y_day += 29;
						}
						else
						{
							y_day += 28;
						}
						continue;
					case 2:
						y_day += 31;
						continue;
					case 3:
						y_day += 30;
						continue;
					case 4:
						y_day += 31;
						continue;
					case 5:
						y_day += 30;
						continue;
					case 6:
						y_day += 31;
						continue;
					case 7:
						y_day += 31;
						continue;
					case 8:
						y_day += 30;
						continue;
					case 9:
						y_day += 31;
						continue;
					case 10:
						y_day += 30;
						continue;
					case 11:
						y_day += 31;
						continue;
					default:
						throw exception::HALException("Timezone", "month_day_to_year_day", "Invalid month index");
					}
				}
				utc_time.tm_yday = y_day - 1; // Remove 1 because month days start from 1 and year days start from 0.
			}

			//! Converts a year day (0-365) to the corresponding month day (1-31).
			/*!
			* Converts a year day (0-365) to the corresponding month day (1-31).
			* \param[out] utc_time: The utc time that contains the year day to
			* convert. The result will be written to this variable, too and will appear
			* in the fields 'tm_mday' and 'tm_mon'.
			*/
			static void year_day_to_month_day(tm& utc_time)
			{
				auto day = utc_time.tm_yday + 1; // Add 1 because month days start from 1 and year days start from 0.
				auto month = 0;
				while (true)
				{
					auto lasting_days = day;
					switch (month)
					{
					case 0:
						lasting_days -= 31;
						break;
					case 1:
						if (is_leapyear(utc_time.tm_year))
						{
							lasting_days -= 29;
						}
						else
						{
							lasting_days -= 28;
						}
						break;
					case 2:
						lasting_days -= 31;
						break;
					case 3:
						lasting_days -= 30;
						break;
					case 4:
						lasting_days -= 31;
						break;
					case 5:
						lasting_days -= 30;
						break;
					case 6:
						lasting_days -= 31;
						break;
					case 7:
						lasting_days -= 31;
						break;
					case 8:
						lasting_days -= 30;
						break;
					case 9:
						lasting_days -= 31;
						break;
					case 10:
						lasting_days -= 30;
						break;
					case 11:
						lasting_days -= 31;
						break;
					default: 
						throw exception::HALException("Timezone", "year_day_to_month_day", "Invalid month index");
					}

					if (lasting_days <= 0)
					{
						break;
					}
					day = lasting_days;
					month++;
				}
				utc_time.tm_mon = month;
				utc_time.tm_mday = day;
			}

			//! Checks if the given year is a leap year.
			/*!
			* Checks if the given year is a leap year.
			* \param[in] year: The year to check.
			* \returns True if the given year is a leap year, false otherwise.
			*/
			static bool is_leapyear(const int year) noexcept
			{
				if (year % 4 == 0 && year % 100 != 0) // Leap year
				{
					return true;
				}
				if (year % 100 == 0 && year % 400 == 0) // Leap year
				{
					return true;
				}
				return false;
			}

		protected:
			//! Add the hour and minute offsets to the given time.
			/*!
			* Add the hour and minute offsets to the given time.
			* \param[out] utc_time: The utc time to convert.
			* \param[in] hours: The hour value offset.
			* \param[in] minutes: The minute value offset.
			*/
			void add_offset(tm& utc_time, int8_t hours, int8_t minutes) const noexcept
			{
				add_minutes(utc_time, minutes);
				add_hours(utc_time, hours);
			}

			//! Add the given minute value to the time.
			/*!
			* Add the given minute value to the time. The method takes care if the minute value
			* gets greater 59 or less 0. This will automatically also increase/decrease the hours
			* value and eventually also day, month and year.
			* \param[out] utc_time: The utc time to add the minutes to.
			* \param[in] minutes: The minute value to add.
			*/
			void add_minutes(tm& utc_time, int8_t minutes) const noexcept
			{
				auto new_minutes = utc_time.tm_min + minutes;
				if (new_minutes > 59) // positive offset -> check for minutes > 59 -> next hour
				{
					utc_time.tm_min = new_minutes - 59;
					add_hours(utc_time, static_cast<int8_t>(1));
				}
				else if (new_minutes < 0) // negative offset -> check for minutes < 0 -> previous hour
				{
					utc_time.tm_min = new_minutes + 59;
					add_hours(utc_time, static_cast<int8_t>(-1));
				}
				else
				{
					utc_time.tm_min = new_minutes;
				}
			}

			//! Add the given hour value to the time.
			/*!
			* Add the given hour value to the time. The method takes care if the hour value
			* gets greater 23 or less 0. This will automatically also increase/decrease the
			* day value and eventually also month and year.
			* \param[out] utc_time: The utc time to add the hours to.
			* \param[in] hours: The hour value to add.
			*/
			void add_hours(tm& utc_time, int8_t hours) const noexcept
			{
				auto new_hours = utc_time.tm_hour + hours;
				if (new_hours >= 24) // positive offset -> check for hour > 24 -> next day
				{
					utc_time.tm_hour = new_hours - 24;
					month_day_to_year_day(utc_time);
					if (utc_time.tm_yday + 1 == 365) // Check if we have a switch to the next year
					{
						if (is_leapyear(utc_time.tm_year))
						{
							utc_time.tm_yday++;
							year_day_to_month_day(utc_time);
						}
						else
						{
							utc_time.tm_yday = 1;
							utc_time.tm_mday = 1;
							utc_time.tm_mon = 0;
							utc_time.tm_year++;
						}
					}
					else if (utc_time.tm_yday + 1 == 366)
					{
						utc_time.tm_yday = 1;
						utc_time.tm_mday = 1;
						utc_time.tm_mon = 0;
						utc_time.tm_year++;
					}
					else
					{
						utc_time.tm_yday++;
						year_day_to_month_day(utc_time);
					}

				}
				else if (new_hours < 0) // negative offset -> check for hour < 0 -> previous day
				{
					month_day_to_year_day(utc_time);
					if (utc_time.tm_yday - 1 == -1) // Check if we have a switch to the previous year
					{
						utc_time.tm_year--;
						utc_time.tm_mday = 31;
						utc_time.tm_mon = 11;
						if (is_leapyear(utc_time.tm_year))
						{
							utc_time.tm_yday = 365;
						}
						else
						{
							utc_time.tm_yday = 364;
						}
					}
					else
					{
						utc_time.tm_yday--;
						year_day_to_month_day(utc_time);
					}
				}
				else
				{
					utc_time.tm_hour = new_hours;
				}
			}

			WorldTimezones m_current_timezone;
			std::string m_long_name;
			std::string m_long_daylight_saving_name;
			std::string m_short_name;
			std::string m_short_daylight_saving_name;
			std::vector<std::string> m_locations;
			int8_t m_offset_hours;
			int8_t m_offset_minutes;
			int8_t m_offset_hours_while_daylight_saving;
			int8_t m_offset_minutes_while_daylight_saving;
			bool m_uses_daylight_saving;
			bool m_is_currently_daylight_saving;
			time_t m_last_daylight_saving_check;
			int m_daylight_saving_check_interval;
			std::string m_tz_path;
		};
	}
}