/*  EVEmu: EVE Online Server Emulator
  
  **************************************************************
  This file is automatically generated, DO NOT EDIT IT DIRECTLY.
  **************************************************************
  
  (If you need to customize an object, you must copy that object
  into another source file, and give up the ability to generate it)
  
  
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

#ifndef _____packets_ObjectCaching_h__
#define _____packets_ObjectCaching_h__

#include <string>
#include <vector>
#include <map>
#include "../common/common.h"
#include "../common/logsys.h"
#include "../common/PyRep.h"



class objectCaching_CachedObject_data {
public:
	objectCaching_CachedObject_data();
	~objectCaching_CachedObject_data();
	
	void Dump(LogType type, const char *pfx = "") const;
	bool Decode(PyRep **packet);	//consumes packet
	bool Decode(PyRepObject **packet);
	PyRepObject *Encode();
	PyRepObject *FastEncode();
	objectCaching_CachedObject_data *Clone() const;
	void CloneFrom(const objectCaching_CachedObject_data *from);
	
	/* object of type objectCaching.CachedObject */
	/*  0  */
	/*  0  */
	uint64		timestamp;
	/*  1  */
	uint32		version;
	/*  1  */
	/*  2  */
	/*  2  */
	uint32		nodeID;
	/*  3  */
	uint32		shared;
	/*  4  */
	PyRepBuffer	*data;
	/*  5  */
	uint32		compressed;
	/*  6  */
	/*  either a string or a tuple  */
	PyRep		*objectID;


};


class objectCaching_CachedObject_spec {
public:
	objectCaching_CachedObject_spec();
	~objectCaching_CachedObject_spec();
	
	void Dump(LogType type, const char *pfx = "") const;
	bool Decode(PyRep **packet);	//consumes packet
	bool Decode(PyRepObject **packet);
	PyRepObject *Encode();
	PyRepObject *FastEncode();
	objectCaching_CachedObject_spec *Clone() const;
	void CloneFrom(const objectCaching_CachedObject_spec *from);
	
	/* object of type util.CachedObject */
	/*  0  */
	PyRep		*objectID;
	/*  1  */
	uint32		nodeID;
	/*  2  */
	/*  0  */
	uint64		timestamp;
	/*  1  */
	uint32		version;


};


class objectCaching_CachedMethodCallResult {
public:
	objectCaching_CachedMethodCallResult();
	~objectCaching_CachedMethodCallResult();
	
	void Dump(LogType type, const char *pfx = "") const;
	bool Decode(PyRep **packet);	//consumes packet
	bool Decode(PyRepObject **packet);
	PyRepObject *Encode();
	PyRepObject *FastEncode();
	objectCaching_CachedMethodCallResult *Clone() const;
	void CloneFrom(const objectCaching_CachedMethodCallResult *from);
	
	/* object of type objectCaching.CachedMethodCallResult */
	/*  0: details  */
	/*  sessionInfo: if this field is present, then it contains a string which
               is the string of a key in the session. The value of that element in the
               current session is used as part of the key for the cache item.
           */
	std::string	sessionInfo;
	/*  these fields are one of:
            (always, never, (set of times))
             */
	/*  0: clientWhen: expiry in the client  */
	std::string	clientWhen;
	/*  1: proxyWhen: expiry on the proxy, may be None  */
	std::string	proxyWhen;
	/*  2: serverWhen: expiry on the server, may be None  */
	std::string	serverWhen;
	/*  1: result  */
	PyRep		*call_return;
	/*  2: version  */
	/*  0  */
	uint64		timeStamp;
	/*  1: binascii.crc_hqx(call_return, (macho.version + 170472))  */
	uint32		version;


};


class objectCaching_CachedMethodCallResult_object {
public:
	objectCaching_CachedMethodCallResult_object();
	~objectCaching_CachedMethodCallResult_object();
	
	void Dump(LogType type, const char *pfx = "") const;
	bool Decode(PyRep **packet);	//consumes packet
	bool Decode(PyRepObject **packet);
	PyRepObject *Encode();
	PyRepObject *FastEncode();
	objectCaching_CachedMethodCallResult_object *Clone() const;
	void CloneFrom(const objectCaching_CachedMethodCallResult_object *from);
	
	/* object of type objectCaching.CachedMethodCallResult */
	/*  0: details  */
	/*  almost all simple objects on live use never... 
                a few use run, we default to run to be more flexible.  */
	std::string	versionCheck;
	/*  1: result, in this case it is always a util.CachedObject hint  */
	/*  <element type="objectCaching_CachedObject_spec" name="object" />  */
	PyRep		*object;
	/*  2: version, never present on a cached object cached method  */


};

	/*  A representation of a simple cached method call objectID, with no arguments  */

class SimpleMethodCallID {
public:
	SimpleMethodCallID();
	~SimpleMethodCallID();
	
	void Dump(LogType type, const char *pfx = "") const;
	bool Decode(PyRep **packet);	//consumes packet
	bool Decode(PyRepTuple **packet);
	PyRepTuple *Encode();
	PyRepTuple *FastEncode();
	SimpleMethodCallID *Clone() const;
	void CloneFrom(const SimpleMethodCallID *from);
	
	/*  0  */
	std::string	type;
	/*  1  */
	std::string	where;
	/*  2  */
	/*  0  */
	std::string	service;
	/*  1  */
	std::string	method;


};


class CallGetCachableObject {
public:
	CallGetCachableObject();
	~CallGetCachableObject();
	
	void Dump(LogType type, const char *pfx = "") const;
	bool Decode(PyRep **packet);	//consumes packet
	bool Decode(PyRepTuple **packet);
	PyRepTuple *Encode();
	PyRepTuple *FastEncode();
	CallGetCachableObject *Clone() const;
	void CloneFrom(const CallGetCachableObject *from);
	
	/*  0  */
	uint32		shared;
	/*  1  */
	/*  either a string or a tuple  */
	PyRep		*objectID;
	/*  2  */
	/*  0  */
	uint64		timestamp;
	/*  1  */
	uint32		version;
	/*  3  */
	uint32		nodeID;


};


class RspGetCachableObject {
public:
	RspGetCachableObject();
	~RspGetCachableObject();
	
	void Dump(LogType type, const char *pfx = "") const;
	bool Decode(PyRep **packet);	//consumes packet
	bool Decode(PyRepTuple **packet);
	PyRepTuple *Encode();
	PyRepTuple *FastEncode();
	RspGetCachableObject *Clone() const;
	void CloneFrom(const RspGetCachableObject *from);
	
	/*  0  */
	objectCaching_CachedObject_spec	object;


};


class objectCaching_CacheOK {
public:
	objectCaching_CacheOK();
	~objectCaching_CacheOK();
	
	void Dump(LogType type, const char *pfx = "") const;
	bool Decode(PyRep **packet);	//consumes packet
	bool Decode(PyRepObject **packet);
	PyRepObject *Encode();
	PyRepObject *FastEncode();
	objectCaching_CacheOK *Clone() const;
	void CloneFrom(const objectCaching_CacheOK *from);
	
	/* object of type objectCaching.CacheOK */
	std::string	exception_string;


};



#endif


