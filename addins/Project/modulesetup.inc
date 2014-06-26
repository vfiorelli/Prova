//Configuration module setup for project explorer

/*
  $Id: modulesetup.inc,v 1.3 2008/11/19 10:29:12 massimo.dag Exp $
*/

/************************
* basic attributes for project explorer
*/

int setupConfiguration(){
  
  bool res  
  int created = 0
  
  
  //MODULE PATH
  res = crObjAttribute(MOD_PATH_ATTR, "String")
  if(res) { created++ }
  
  //MODULE TO BASELINE
  res = crObjAttribute(MOD_BASE_ATTR, "Boolean")
  if(res) { created++ }
  
  //MODULE TYPE - TYPE
  res = enumCreate(MOD_TYPE_TYPE, MOD_TYPE_VAL, MOD_TYPE_INT, MOD_TYPE_COL)
  if(res) { created++ }
    
  //MODULE TYPE - ATTRIBUTE
  res = crObjAttribute(MOD_TYPE_ATTR, MOD_TYPE_TYPE)
  if(res) { created++ }

  //MODULE TO BE PUT IN DELIVERY
  res = crObjAttribute(MOD_DELIVERY_ATTR, "Boolean")
  if(res) { created++ }
  
  return created 
  
}


/*************************
* createViewListAttr
*/

int createViewListAttr(Module configMod){
  bool res
  int created = 0
  
  //Create attribute for view list
  res = crObjAttribute(MOD_VIEW_LIST_ATTR, "Text")
  if(res) { created++ }
  
  //Create attribute for view list
  res = crObjAttribute(MOD_VIEW_LIST_DEL, "Text")
  if(res) { created++ }
  
  return created
}

/*************************
* createDxlViewAttr
*/

int createDxlViewAttr(Module configMod) {
  bool res
  int created = 0
  
  //Create attribute for view list
  res = crObjAttribute(MOD_DXL_VIEW_CHK, "Text")
  if(res) { created++ }
  
  //Create attribute for DEFAULT view 
  res = crObjAttribute(MOD_DXL_VIEW_DEF_CHK, "Text")
  if(res) { created++ }
  
  return created

}

/*************************
* createLinkCountAttr
*/

int createLinkCountAttr(Module configMod){
  bool res
  int created = 0
  
  //Create attribute for view list
  res = crObjAttribute(LINKSETS_NO_ATTR, "Integer")
  if(res) { created++ }
  
  //Create attribute for view list
  res = crObjAttribute(LINK_TOTAL_ATTR, "Integer")
  if(res) { created++ }
  
  //Create attribute for view list
  res = crObjAttribute(LINK_EXT_ATTR, "Text")
  if(res) { created++ }
  
  return created
}
