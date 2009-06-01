/*
	------------------------------------------------------------------------------------
	LICENSE:
	------------------------------------------------------------------------------------
	This file is part of EVEmu: EVE Online Server Emulator
	Copyright 2006 - 2008 The EVEmu Team
	For the latest information visit http://evemu.mmoforge.org
	------------------------------------------------------------------------------------
	This program is free software; you can redistribute it and/or modify it under
	the terms of the GNU Lesser General Public License as published by the Free Software
	Foundation; either version 2 of the License, or (at your option) any later
	version.

	This program is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License along with
	this program; if not, write to the Free Software Foundation, Inc., 59 Temple
	Place - Suite 330, Boston, MA 02111-1307, USA, or go to
	http://www.gnu.org/copyleft/lesser.txt.
	------------------------------------------------------------------------------------
	Author:		Zhur
*/


#ifndef __INVENTORYDB_H_INCL__
#define __INVENTORYDB_H_INCL__

#include "../ServiceDB.h"
#include "../common/tables/invGroups.h"
#include "../common/tables/invCategories.h"

class EVEAttributeMgr;

class CategoryData;

class GroupData;

class TypeData;
class BlueprintTypeData;
class CharacterTypeData;
class ShipTypeData;
class StationTypeData;

class ItemData;
class BlueprintData;
class CharacterData;
class CharacterAppearance;
class CorpMemberInfo;
class CelestialObjectData;
class SolarSystemData;
class StationData;

class InventoryDB
: public ServiceDB
{
public:
	/*
	 * Constructor & Destructor
	 */
	InventoryDB(DBcore *db);
	virtual ~InventoryDB();

	/*
	 * Category stuff
	 * (invCategories)
	 */
	bool GetCategory(EVEItemCategories category, CategoryData &into);

	/*
	 * Group stuff
	 * (invGroups)
	 */
	bool GetGroup(uint32 groupID, GroupData &into);

	/*
	 * Type stuff
	 * (invTypes, invBlueprintTypes, bloodlineTypes, chrBloodlines, invShipTypes, staStationTypes)
	 */
	bool GetType(uint32 typeID, TypeData &into);

	bool GetBlueprintType(uint32 blueprintTypeID, BlueprintTypeData &into);

	/**
	 * Loads character type data.
	 *
	 * @param[in] bloodlineID Bloodline to be loaded.
	 * @param[out] into Where loaded data should be stored.
	 * @return True on success, false on failure.
	 */
	bool GetCharacterType(uint32 bloodlineID, CharacterTypeData &into);
	/**
	 * Obtains ID of character type based on bloodline.
	 *
	 * @param[in] bloodlineID ID of bloodline.
	 * @param[out] characterTypeID Resulting ID of character type.
	 * @return True on success, false on failure.
	 */
	bool GetCharacterTypeByBloodline(uint32 bloodlineID, uint32 &characterTypeID);
	/**
	 * Obtains ID of bloodline based on character type.
	 *
	 * @param[in] characterTypeID ID of character type.
	 * @param[out] bloodlineID Resulting ID of bloodline.
	 * @return True on success, false on failure.
	 */
	bool GetBloodlineByCharacterType(uint32 characterTypeID, uint32 &bloodlineID);

	/**
	 * Obtains bloodline and loads character type data.
	 *
	 * @param[in] characterTypeID ID of character type to be loaded.
	 * @param[out] bloodlineID Resulting bloodline.
	 * @param[out] into Where character type data should be stored.
	 * @return True on success, false on failure.
	 */
	bool GetCharacterType(uint32 characterTypeID, uint32 &bloodlineID, CharacterTypeData &into);
	/**
	 * Obtains ID of character type and loads it.
	 *
	 * @param[in] bloodlineID ID of bloodline to be loaded.
	 * @param[out] characterTypeID Resulting character type.
	 * @param[out] into Where loaded character type data should be stored.
	 * @return True on success, false on failure.
	 */
	bool GetCharacterTypeByBloodline(uint32 bloodlineID, uint32 &characterTypeID, CharacterTypeData &into);

	/**
	 * Loads ship type data into given container.
	 *
	 * @param[in] shipTypeID ID of ship type.
	 * @param[in] into Container to load data into.
	 * @return True on success, false on failure.
	 */
	bool GetShipType(uint32 shipTypeID, ShipTypeData &into);

	/**
	 * Loads station type data into given container.
	 *
	 * @param[in] stationTypeID ID of station type to load.
	 * @param[in] into Container to load data into.
	 * @return True if load succeeded, false if not.
	 */
	bool GetStationType(uint32 stationTypeID, StationTypeData &into);

	/*
	 * Type attribute stuff
	 * (dgmTypeAttributes)
	 */
	/**
	 * Loads type attributes into given attribute manager.
	 *
	 * @param[in] typeID ID of type which attributes should be loaded.
	 * @param[in] into Attribute manager the attributes should be loaded into.
	 * @return True if load was successfull, false if not.
	 */
	bool LoadTypeAttributes(uint32 typeID, EVEAttributeMgr &into);

	/*
	 * Item stuff
	 * (entity)
	 */
	bool GetItem(uint32 itemID, ItemData &into);

	uint32 NewItem(const ItemData &data);
	bool SaveItem(uint32 itemID, const ItemData &data);
	bool DeleteItem(uint32 itemID);

	bool GetItemContents(uint32 itemID, std::vector<uint32> &items);

	/*
	 * Item attribute stuff
	 * (entity_attributes)
	 */
	/**
	 * Loads item attributes into given attribute manager.
	 *
	 * @param[in] itemID ID of item which attributes should be loaded.
	 * @param[in] into Attribute manager the attributes should be loaded into.
	 * @return True if load was successfull, false if not.
	 */
	bool LoadItemAttributes(uint32 itemID, EVEAttributeMgr &into);

	bool UpdateAttribute_int(uint32 itemID, uint32 attributeID, int v);
	bool UpdateAttribute_double(uint32 itemID, uint32 attributeID, double v);
	bool EraseAttribute(uint32 itemID, uint32 attributeID);
	bool EraseAttributes(uint32 itemID);

	/*
	 * Blueprint stuff
	 * (invBlueprints)
	 */
	bool GetBlueprint(uint32 blueprintID, BlueprintData &into);

	bool NewBlueprint(uint32 blueprintID, const BlueprintData &data);
	bool SaveBlueprint(uint32 blueprintID, const BlueprintData &data);
	bool DeleteBlueprint(uint32 blueprintID);

	/*
	 * Character stuff
	 * (character_)
	 */
	bool GetCharacter(uint32 characterID, CharacterData &into);
	bool GetCharacterAppearance(uint32 characterID, CharacterAppearance &into);
	bool GetCorpMemberInfo(uint32 characterID, CorpMemberInfo &into);

	bool NewCharacter(uint32 characterID, const CharacterData &data, const CharacterAppearance &appData, const CorpMemberInfo &corpData);
	bool SaveCharacter(uint32 characterID, const CharacterData &data);
	bool SaveCharacterAppearance(uint32 characterID, const CharacterAppearance &data);
	bool SaveCorpMemberInfo(uint32 characterID, const CorpMemberInfo &data);
	bool DeleteCharacter(uint32 characterID);

	/*
	 * Celestial object stuff
	 * (mapDenormalize)
	 */
	/**
	 * Loads celestial object data.
	 *
	 * @param[in] celestialID ID of celestial object to load.
	 * @param[in] into Containter into which the data should be loaded.
	 * @return True if succeeds, false if fails.
	 */
	bool GetCelestialObject(uint32 celestialID, CelestialObjectData &into);

	/*
	 * Solar system stuff
	 * (mapSolarSystems)
	 */
	/**
	 * Loads solar system data.
	 *
	 * @param[in] solarSystemID ID of solar system which data should be loaded.
	 * @param[in] into Container into which the data should be loaded.
	 * @return True if load succeeds, false if fails.
	 */
	bool GetSolarSystem(uint32 solarSystemID, SolarSystemData &into);

	/*
	 * Station stuff
	 * (staStations)
	 */
	/**
	 * Loads station data.
	 *
	 * @param[in] stationID ID of station which data should be loaded.
	 * @param[in] into Container where data should be stored.
	 * @return True if load succeeds, false if fails.
	 */
	bool GetStation(uint32 stationID, StationData &into);


	/**
	 * Removes rows from chrSkillQueue for a character.
	 *
	 * @param[in] itemID ID of character
	*/
	bool RemoveSkillsFromSkillQueue(uint32 itemID, uint32 typeID);

	/**
	 * returns rows of skills from chrSkillQueue for a character.
	 *
	 * @param[in] itemID ID of character
 	 * @param[in] typeID ID the skill type
 	 * @param[in] level level of skill to be trained
	*/
	bool GetSkillsFromSkillQueue(uint32 itemID, PyRepList *list);

	/**
	 * Adds a row into chrSkillQueue for a character.
	 *
	 * @param[in] itemID ID of character
 	 * @param[in] typeID ID the skill type
 	 * @param[in] level level of skill to be trained
	*/
	bool AddSkillToSkillQueue(uint32 itemID, uint32 typeID, uint8 level);
};



#endif

