//CACHING OBJECTS

/*
  $Id: object_caching.inc,v 1.2 2008/11/13 07:41:40 massimo.dag Exp $
*/


/*****************************************************************************
Included functions:
    
*Trimming out new lines in keys (for use in objectCache)

  string cleanKey(string keyValue) {
  }
  
  
  
*Object caching (object identifier)

  int objectCache(Module modIn, Skip &oCache){
  }

  
  

*Object caching (generic text attribute to be used as a key)

  int objectCache(Module modIn, string keyAttr, Skip &oCache){
  }

  

*
*
******************************************************************************/


/**************************************************************************
* INCLUDES
*/


#include <utils/fileops>



/**************************
 * cleanKey
 *
 */

string cleanKey(string keyValue) {
  Regexp nline = regexp ".*"
  nline keyValue
  return keyValue[match 0]
}

/**************************
 * objectCache
 *
 */
 
int objectCache(Module modIn, Skip &oCache){
  Object o 
  int    n = 0
  string absno
    
  for o in modIn do  {
    absno = identifier(o) ""
    put(oCache, absno, o)
    n++ 
  }
  return n
}

//w/generic text attribute as a key

int objectCache(Module modIn, string keyAttr, Skip &oCache){
  Object o 
  int    n = 0
  string absno
  
  Module orgMod = current
  
  (current ModuleRef__) = modIn
  
  if(!attrExists_ keyAttr){
    (current ModuleRef__) = orgMod
    return -1
  }
  
  for o in modIn do  {
    absno = cleanKey(o.keyAttr "")
    put(oCache, absno, o)
    n++ 
  }

  (current ModuleRef__) = orgMod
  
  return n
}

