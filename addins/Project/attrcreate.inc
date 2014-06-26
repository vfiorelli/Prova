/*
Utils for attribute creation in modules
*/


/*************************
* enumCreate
* create enumeration type
*/

bool enumCreate(string tName, names[], int values[], int colors[]){
  string mess = ""
  setRealColorOptionForTypes(true)
  
  AttrType at = find(current Module, tName)
  if(!null at){
    return false
  }
  
  at = create(tName, names, values, colors, mess) 
  setRealColorOptionForTypes(false)
  
  if (!null mess){
    print "Type creation failed\n" 
    return false
  }
  return true
}


/*************************
* createAttr with type specification
*/


bool crModAttribute(string crAttr, string typeAssoc){
  
  if(!attrExists_(crAttr)){
    create module type typeAssoc attribute crAttr
    return true
    
  } else {
    //attribute exists
    return false
    
  }
  
}

bool crObjAttribute(string crAttr, string typeAssoc){
  
  if(!attrExists_(crAttr)){
    create object type typeAssoc attribute crAttr
    return true
    
  } else {
    //attribute exists
    return false
    
  }
  
}

bool crObjAttribute(string crAttr, string typeAssoc,int check){
  
	if(!attrExists_(crAttr)){
	 
		if (check == 1){
			create object type typeAssoc attribute crAttr
			return true
		}else{
		  return false
		} 
		    
  } else {
    //attribute exists
    return false
    
  }
  
}