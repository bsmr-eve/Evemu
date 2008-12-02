/*  EVEmu: EVE Online Server Emulator

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; version 2 of the License.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY except by those people which sell it, which
  are required to give you total support for your newly bought product;
  without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
	
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __OBJCACHEDB_H_INCL__
#define __OBJCACHEDB_H_INCL__

#include "../ServiceDB.h"
#include <map>
#include <string>

class PyRep;
class DBQueryResult;

class ObjCacheDB
: public ServiceDB {
public:
	ObjCacheDB(DBcore *db);
	virtual ~ObjCacheDB();
	
	PyRep *GetCachableObject(const std::string &type);
	
protected:
	typedef PyRep *(ObjCacheDB::* genFunc)();
	std::map<std::string, genFunc> m_generators;

	//hack:
	PyRep *DBResultToRowsetTuple(DBQueryResult &result);
	
	//declare all the generators
	PyRep *Generate_BillTypes();
	PyRep *Generate_AllianceShortnames();
	PyRep *Generate_invCategories();
	PyRep *Generate_invTypeReactions();

	PyRep *Generate_dgmTypeAttribs();
	PyRep *Generate_dgmTypeEffects();
	PyRep *Generate_dgmEffects();
	PyRep *Generate_dgmAttribs();
	PyRep *Generate_dgmAttributesByName();

	PyRep *Generate_invMetaGroups();

	PyRep *Generate_ramActivities();
	PyRep *Generate_ramALTypeGroup();
	PyRep *Generate_ramALTypeCategory();
	PyRep *Generate_ramALTypes();
	PyRep *Generate_ramCompletedStatuses();
	PyRep *Generate_ramTypeMaterials();
	PyRep *Generate_ramTypeRequirements();

	PyRep *Generate_mapCelestialDescriptions();
	PyRep *Generate_tickerNames();
	PyRep *Generate_invGroups();
	PyRep *Generate_invShipTypes();
	PyRep *Generate_cacheLocations();
	PyRep *Generate_invBlueprintTypes();
	PyRep *Generate_eveGraphics();
	PyRep *Generate_invTypes();
	PyRep *Generate_invMetaTypes();
	PyRep *Generate_chrBloodlines();
	PyRep *Generate_eveUnits();
	PyRep *Generate_eveBulkDataUnits();
	PyRep *Generate_cacheOwners();
	PyRep *Generate_eveStaticOwners();
	PyRep *Generate_chrRaces();
	PyRep *Generate_chrAttributes();
	PyRep *Generate_invFlags();
	PyRep *Generate_eveStaticLocations();
	PyRep *Generate_invContrabandTypes();

	PyRep *Generate_c_chrBloodlines();
	PyRep *Generate_c_chrRaces();
	PyRep *Generate_c_chrAncestries();
	PyRep *Generate_c_chrSchools();
	PyRep *Generate_c_chrAttributes();
	PyRep *Generate_bl_accessories();
	PyRep *Generate_bl_lights();
	PyRep *Generate_bl_skins();
	PyRep *Generate_bl_beards();
	PyRep *Generate_bl_eyes();
	PyRep *Generate_bl_lipsticks();
	PyRep *Generate_bl_makeups();
	PyRep *Generate_bl_hairs();
	PyRep *Generate_bl_backgrounds();
	PyRep *Generate_bl_decos();
	PyRep *Generate_bl_eyebrows();
	PyRep *Generate_bl_costumes();

	PyRep *Generate_nec_raceskills();
	PyRep *Generate_nec_careerskills();
	PyRep *Generate_nec_specialityskills();
	PyRep *Generate_nec_careers();
	PyRep *Generate_nec_specialities();

	PyRep *Generate_a_eyebrows();
	PyRep *Generate_a_eyes();
	PyRep *Generate_a_decos();
	PyRep *Generate_a_hairs();
	PyRep *Generate_a_backgrounds();
	PyRep *Generate_a_accessories();
	PyRep *Generate_a_lights();
	PyRep *Generate_a_costumes();
	PyRep *Generate_a_makeups();
	PyRep *Generate_a_beards();
	PyRep *Generate_a_skins();
	PyRep *Generate_a_lipsticks();
};

#endif