/*
Explorer tools

  $Id: explorer_tools.inc,v 1.3 2009/06/15 17:03:42 massimo.dag Exp $

*/

/****************
* levelCount
*/


int levelCount(string pathName){
  int count = 0, i = 0
  Buffer b = create
  
  b += pathName
  while(i < length b){
    if(b[i] == '/'){
      count++
    }
    i++
  }
  
  delete b
  
  //print "C = " count " -> " pathName "\n"
  return count

}

/****************
* parseLevel
*/

int parseLevel(Skip &fSkip, Array &hierArr, int &hierIndex){
  
  int elemLev, elemCount = 0
  
  int elemNo = 0
  string foldName
  
  for foldName in fSkip do {
    foldPath = (string key(fSkip))
    
    elemLev = levelCount(foldPath)

    if(elemLev == (hierIndex + 1)){
	    
      //print "%: " elemLev " < " foldPath " < " foldName "\n"
      //print "put in " hierIndex "," elemNo "\n\n"
      
      /*print "--******************* hierArr  *************** \n"
      
      print "foldPath :" foldPath "\n"
      print "hierIndex :" hierIndex "\n"
      print "elemNo :" elemNo "\n"
      
      print "--******************* FINE hierArr  *************** \n"*/
      
      put(hierArr,foldPath, hierIndex, elemNo)
      delete(fSkip, foldPath)
      elemNo++
      
    } else {
      elemCount++
      
    }
    
  }
  
  put(hierArr,ARR_EOF, hierIndex, elemNo)
  hierIndex++
  
  return elemCount
  
}

/****************
* Parselevels
*
* array will be like:
*
*  level 1, /path/item A, /path/item B, ...
*  level 2, /path/item C, /path/item D, ...
*  level 3, /path/item E, /path/item F, ...
*  ...    , ...         , ...         , ...
*
*/
  

void parseLevels(Skip &fSkip, Array &hierArr, int &hierIndex){
  int elCount = 1 //conventional value just to let the loop start
  int elCountPrev
  
  while(elCount > 0){
    elCountPrev = elCount
    elCount = parseLevel(fSkip, hierArr, hierIndex)
    //print "(" hierIndex ") " elCount "-"
    if(elCount == elCountPrev){
     // print "Infinite loop: break"
      break
    }
  }
  //print "\n"
  
  return
  
}


/****************
* findLevelObjects
*/

int findLevelObjects(Skip &modSkip, Array &modArr, int index, string terminator){
  string itemWpath
  int onY = 0, itemCount = 0
  
 // print "%%%%LEVEL " index " %%%%%%%\n\n"
  
  while(true) {
    itemWpath = (string(get(modArr, index, onY)))
    if(itemWpath == terminator){
      break
    }
    
 //   print "[" itemWpath "\n"
    put(modSkip, itemWpath, itemWpath)
    itemCount++
    onY++
  }
 // print "%%%%END " index " %%%%%%%\n\n"
  return itemCount 
}

/****************
* placeNextLevel
vf aggiunto cObj.MOD_REF_ATTR in modo di avere lo uniqueID per i folder 
*/

void placeNextLevel(int index, Skip &modSkip, &cachedSkip){
  string elem, parName, moduName
  Object cObj
   
  Regexp sep = regexp "(.*)/(.*)"
  bool bfoundfolder = false 
 
  ///ObjRecover(string unique_ID,Module m)
   
  for elem in modSkip do {
	  bfoundfolder = false
	  
  	  sep elem
  	  parName = elem[match 1]
  	  moduName = elem[match 2]
  	 
  	  	  			
  	 if(!null item(elem)){
	  	
	  	bfoundfolder =	Find_Unique_ID((uniqueID item elem),ArrModConf)
	  	
		if (bfoundfolder==true){
			
	  		obj = ObjRecover((uniqueID item elem),(current Module))
		 
			if(!null obj){
								
				sMOD_NAME_ATTR = obj.MOD_NAME_ATTR""
      			sMOD_PATH_ATTR = obj.MOD_PATH_ATTR""
      			sMOD_TYPE_ATTR = obj.MOD_TYPE_ATTR""
      			string sMOD_FOLD_ATTR = obj.MOD_FOLD_ATTR""				
				
				//Object Heading 
				if (sMOD_FOLD_ATTR != name(item elem)){ 
	    			obj.MOD_FOLD_ATTR = name(item elem)
  				}
				   				
      			if (sMOD_PATH_ATTR != elem){
      				
      				int ix = 0 
					
      				Object objn =  FoundPos (item(elem),ix)

      				if (ix == 0){
	      				move(obj,below objn)
	      			}else{
		      			move(obj, objn)
		      		}
									
					obj.MOD_PATH_ATTR = elem
	    		}
	    		
      			if (sMOD_TYPE_ATTR != (type item elem)){
	    			obj.MOD_TYPE_ATTR = (type item elem)
  				}
        	
			}
		}	
 	 }
 	 
    if (bfoundfolder ==false) {
	  	           
	  	  if(index > 0){
	  	  	if(!find(cachedSkip, parName, cObj)){
	  	      	continue
	  	      
	  	    	} else {
	  	      	cObj = create last below cObj
	  	      	put(cachedSkip, elem, cObj)
	  	      
	  	    	}
	  	
	  	  } else {
	  	  	cObj = last (current Module)
	  	    		if(null cObj){
	  	      		cObj = create (current Module)
	  	      		put(cachedSkip, elem, cObj)
	  	      
	  	    		} else {
	  	      		cObj = create after cObj
	  	      		put(cachedSkip, elem, cObj) 
	  	    		}
	  	  }
	 
  	 	 //fill needed attributes
  	 	 cObj.MOD_FOLD_ATTR = moduName
  	 	 cObj.MOD_PATH_ATTR = elem
  	  
  	 	 if(!null item(elem)){
  	 	 	cObj.MOD_TYPE_ATTR = (type item elem)
  	 	    cObj.MOD_REF_ATTR = (uniqueID item elem) 
  	 	 } else {
  	 	   	print "error: item " elem " not found."
  	 	 }
  	}
  }
    
  return
  
}

/****************
* buildStructure
*/


Skip buildStructure(Module confModule, Array &hierArr, int hierIndex, string topItemName){
  int onX
  string itemWpath = "", nameItem

  Skip oCache = createString  

  //Cache already existing objects
   objectCache(confModule, MOD_PATH_ATTR, oCache)
  
  //Building module 
  for(onX = 0; onX < hierIndex; onX++){
    
    Skip reorder = createString
    
    //collect elements from a level
    findLevelObjects(reorder, hierArr, onX, ARR_EOF)
    
    //place elements
    placeNextLevel(onX, reorder, oCache)
    
    delete reorder
      
  }
  
  return oCache
  
}
