pragma runLim, 0


//*****************************************************************************
//			getArraySizeColum
//*****************************************************************************
int getArraySizeColum(Array a){
    int size = 0;
    while( !null(get(a, size, 0) ) )
        size++;
    return size;
}

//*****************************************************************************
//			getArraySizeRow
//*****************************************************************************
int getArraySizeRow(Array a){
	int size = 0;
    while( !null(get(a, 0, size) ) )
        size++;
    return size;
}

//*****************************************************************************
//			Find_Unique_ID
// la funzione avrà come ritorno true se lo uid passato è presente nell'array indicato
//*****************************************************************************
bool Find_Unique_ID(string unique_ID,Array arr){

	int irowArr = getArraySizeRow(arr)
	string sUid = ""
		
	for(x = 0; x<irowArr ; x++){	
		sUid = (string get(arr,1,x))
		if (sUid==unique_ID){
			return true
		}
	}
	
	return false 
}

//*****************************************************************************
//			FillArrayConfMod  
//*****************************************************************************
void FillArrayConfMod(Module m){
	Object obj
	int y = 0 
	string suidskip = ""
	string res,keyS = ""
	for obj in m do {
	
		put(ArrModConf, obj.MOD_TYPE_ATTR"",0, y)  //"Mod Type"
		put(ArrModConf, obj.MOD_REF_ATTR"",1, y)  //"Module unique ID" 
		put(ArrModConf, obj.MOD_PATH_ATTR"",2, y)  //"Mod Path"
		put(ArrModConf, obj.MODULEDESCRIPT"",3, y) //"Module Description"
		put(ArrModConf, obj.MOD_NAME_ATTR"",4, y)  //"Object Text"
		  
		y++
	}	
}
//*****************************************************************************
//			ObjRecover
// la funzione restituise l'obj dell'oggetto con lo stesso UID
//*****************************************************************************
Object ObjRecover(string unique_ID,Module m){

	Object obj
	int y = 0 
	
	for obj in m do {
		if (unique_ID==obj.MOD_REF_ATTR""){
			return obj
		}
	}	
}

//*****************************************************************************
//			ObjDel
// la funzione elimina gli obj aventi uid salvato nella skip solo se non ha figli associati
//*****************************************************************************
void DelObjMod(Module m){

	string res,keyS,sDescDel = ""
	Object ObjDel
	
	//prima elimono solo i module
	for res in SkipUIDDel do {
		
		keyS = (string key SkipUIDDel)
		
		ObjDel = ObjRecover(keyS,m)
  		sDescDel = canDelete(ObjDel)

  	  	if (sDescDel==""){
  			delete (ObjDel)
  			delete(SkipUIDDel, keyS)
  		}
	}
  refresh(m) 

	// poi elimino i fodler 
	for res in SkipUIDDel do {
		
		keyS = (string key SkipUIDDel)	

		ObjDel = ObjRecover(keyS,m)
  		sDescDel = canDelete(ObjDel)
  		
	  	if (sDescDel==""){
  			softDelete(ObjDel)
  		}
  		
	}
	
}

//*****************************************************************************
//			ObjDel
// la funzione valorizza la skip con tutti i project,folder e formal attual
//*****************************************************************************
void fillSkipconf(Skip SkipModConf,Project curProj){
	Item itProxx
	string sUIDitm =""
		
	// valorizzo la skip con tutti i project,folder e formal attuali
	for itProxx in curProj do {
		sUIDitm = uniqueID itProxx
		
		put(SkipModConf,sUIDitm,sUIDitm)
			
	}	
}

//*****************************************************************************
//			Pos_Array
// la funzione elimina gli obj aventi uid salvato nella skip solo se non ha figli associati
//*****************************************************************************
int Pos_Array(string unique_ID,Array arr){
	
	int irowArr = getArraySizeRow(arr)
	string sUid = ""
		
	for(x = 0; x<irowArr ; x++){	
		sUid = (string get(arr,1,x))
		if (sUid==unique_ID){
			return x
		}
	}
}


//*****************************************************************************
//			FoundPos
//*****************************************************************************
Object FoundPos(Item iEle,int &ix){
 
	Folder f 
	Item itemRef
	Object objret	
	int x = 0
	int y = 0 
	int nitem = 0
	
	f = getParentFolder(iEle)
	
	//*** recupero gli item presenti nel folder 
	for itemRef in f do {
		ix++	
	} 

	//** se ix = 1 significa che è l'unico elemento del folder
	//** ed esco dalla funzione 
	if (ix == 1){
		objret = ObjRecover(uniqueID f,current Module)
		ix = 0
		return objret
	}  
	
	//*** inizializzo array con numero di item recuperati
	y = ix 
	string aItemFolder[y] 
	
	
	//*** ciclo nuovamente gli item del folder e valorizzo array aItemFolder
	for itemRef in f do {
 		aItemFolder[x++] = fullName(itemRef) 			
	}
	
	sort aItemFolder
	
	//*** ciclo sull'array per recuperare la posizione dell'item passato 
	//*** alla fun nel suo intero
	for (x = 0; x < y; x++){
		 
		if (fullName(iEle) == aItemFolder[x]){
			//*** se trovo l'itm recupero la posizione dell'item precedente	"nitem--"		
			 nitem = x 
			 nitem--
		}
	}	
	
	//** se nitem <0 e y>1 significa che sono il primo elemento del folder	
	if ((nitem<0)&&(y>1)){
		
		//essendo il primo elemento devo recupero il folder dove attaccarmi \n"
		objret = ObjRecover(uniqueID f,current Module)
		ix = 0
		return objret
		}
	
			
	for itemRef in f do {		
 		if (aItemFolder[nitem] ==  fullName(itemRef)){
	 		 
	 		objret = ObjRecover(uniqueID itemRef,current Module) 

	 	}		
	}
	
	return objret
	
}


//*****************************************************************************
//			Modobj
//*****************************************************************************

void Modobj(Item itPro, Module confModule,string moduName){
	Object obj
	
	if  (Find_Unique_ID(uniqueID itPro,ArrModConf)== true){
				bnewObj = false	
				
	  			//recupero obj
	  			obj = ObjRecover(uniqueID itPro,confModule)
	  			
	  			//verifico se dati modificati		
      			string sMOD_NAME_ATTR = obj.MOD_NAME_ATTR""
      			string sMOD_PATH_ATTR = obj.MOD_PATH_ATTR""
      			string sMOD_TYPE_ATTR = obj.MOD_TYPE_ATTR""
      			string sMODULEDESCRIPT = obj.MODULEDESCRIPT""      			
      		
	  			if (sMOD_NAME_ATTR != name itPro){
		  			obj.MOD_NAME_ATTR = name itPro
		  		}
		  		
      			if (sMOD_PATH_ATTR != moduName){
      				obj.MOD_PATH_ATTR = moduName
      				
      				int ix = 0 
      				Object objn =  FoundPos (itPro,ix)
      				
      				//*** se ix dopo la creazione dell'objn è 0
      				//*** l'obj deve esere figlio di objn
      				if (ix == 0){
	      				move(obj,below objn)
	      			}else{
		      			move(obj, objn)
		      		}
      				
	      		}
      			if (sMOD_TYPE_ATTR != (type itPro)){
	      			obj.MOD_TYPE_ATTR = (type itPro)
  				}
	      		if(sMODULEDESCRIPT != description itPro){
		    	  	obj.MODULEDESCRIPT = description itPro
  				}
	  		}
	
}