//Project folder

/*
  $Id: project_definitions.inc,v 1.6 2009/06/15 17:03:42 massimo.dag Exp $
*/


//---------------------------------------------------
//constants and definitions
//---------------------------------------------------

//constants


const string MOD_FOLD_ATTR = "Object Heading"
const string MOD_NAME_ATTR = "Object Text"
const string MOD_PATH_ATTR = "Mod Path"
const string MOD_BASE_ATTR = "Mod Needs Baseline"
const string MOD_TYPE_ATTR = "Mod Type"

const string MOD_TYPE_TYPE = "Mod Type"

const string MOD_TYPE_VAL[] = {"Formal", "Folder", "Project", "Link"}
const int MOD_TYPE_INT[] = {1, 2, 3, 4}
const int MOD_TYPE_COL[] = {realColor_Black,realColor_Orange, realColor_Grey33, realColor_Navy}

//To be put in delivery list
const string MOD_DELIVERY_ATTR = "Mod in Delivery"

//view list functions
const string MOD_VIEW_LIST_ATTR = "Mod View List"
const string MOD_VIEW_LIST_DEL = "Mod Views To Delete"    //currently unused - TBC
const string MOD_DXL_VIEW_CHK = "Mod Dxl View check"
const string MOD_DXL_VIEW_DEF_CHK = "Mod Dxl Def View Check"

const string MOD_DEL_VIEW ="Mod Delete Views"
const string MOD_DEL_LOG = "Delete Views Log"

//Array terminator

const string ARR_EOF = "%%EOF%%"


//Baseline attributes
const string MOD_REF_ATTR = "Module unique ID"
const string MODULEDESCRIPT = "Module Description"
const string LASTBASENO     = "Last Baseline No"
const string LASTBASEISSUE  = "Last Baseline Suffix"
const string LASTBASEDESCR  = "Last Baseline Description"
const string LASTBASEUSER   = "Last Baseline Creator"
const string LASTBASEDATE   = "Last Baseline Date"

const string MODULELASTMODON  = "When"
const string MODULELASTMODBY  = "Who"


//Link attributes

const string LINKSETS_NO_ATTR = "Outlinks Sets No"
const string LINK_TOTAL_ATTR = "Outlinks Tot No"
const string LINK_EXT_ATTR = "Outlink Detail"

//User accesses

const string USERS_ACCESS_ATTR = "Access Rights"

//Document attributes

const string DOC_REF_ATTR = "Doc Reference"
const string DOC_AUTH = "Doc Author"
const string DOC_ISSUE = "Doc Issue"
const string DOC_DATE = "Doc Date"
const string DOC_CLASS = "Doc Classification"
const string DOC_CLASS2 = "Doc Classification 2"

//Attribution Skip list

const string COL_ENAB = "Enabled"

//Createbl
const string NEW_SL_SAFETY_CHECK = "New Baseline Safety Check"
const string Type_Bl = "Type bl"
const string NEW_BL_SUFFIX = "New Baseline Suffix"
const string NEW_BL_DESC = "New Baseline Description"



//***loadLinkMosuleDesc
const string MOD_LINKSETS="Mod Linksets"
Skip ItemSkip = create 
Skip FolderSkip = create 
Array ArrItem = create(1,1) 
int xArrItem = 0



Skip docAttr = createString
const string prefix = "S2S "

put(docAttr, DOC_REF_ATTR, "String")
put(docAttr, DOC_AUTH,   "String")
put(docAttr, DOC_ISSUE,   "String")
put(docAttr, DOC_DATE,   "Date")
put(docAttr, DOC_CLASS,   "String")
put(docAttr, DOC_CLASS2,   "String")

//VF 
Array ArrModConf = create(1,1)
Skip SkipModConf = create
Skip SkipUIDDel = create

//list_view delete
Skip SkipAllView = create
Skip SkipModView = create

