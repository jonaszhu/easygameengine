/*
** Lua binding: MolServer
** Generated automatically by tolua++-1.0.92 on 07/02/11 16:25:16.
*/
#include "stdafx.h"
#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_MolServer_open (lua_State* tolua_S);

#include "Position2d.h"
#include "Dimension2d.h"
#include "Rect.h"
#include "MolNet/MolString.h"
#include "MolNet/MolMessageIn.h"
#include "MolNet/MolMessageOut.h"
#include "Player.h"
#include "Room.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CMolRect_int_ (lua_State* tolua_S)
{
 CMolRect<int>* self = (CMolRect<int>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CMolDimension2d_int_ (lua_State* tolua_S)
{
 CMolDimension2d<int>* self = (CMolDimension2d<int>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CMolPosition2d_double_ (lua_State* tolua_S)
{
 CMolPosition2d<double>* self = (CMolPosition2d<double>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CMolMessageOut (lua_State* tolua_S)
{
 CMolMessageOut* self = (CMolMessageOut*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CMolDimension2d_double_ (lua_State* tolua_S)
{
 CMolDimension2d<double>* self = (CMolDimension2d<double>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CMolString (lua_State* tolua_S)
{
 CMolString* self = (CMolString*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CMolRect_double_ (lua_State* tolua_S)
{
 CMolRect<double>* self = (CMolRect<double>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CMolPosition2d_int_ (lua_State* tolua_S)
{
 CMolPosition2d<int>* self = (CMolPosition2d<int>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CMolMessageOut");
 tolua_usertype(tolua_S,"CMolPosition2d<double>");
 tolua_usertype(tolua_S,"CMolString");
 tolua_usertype(tolua_S,"CVMemPool<CMolMessageIn>");
 tolua_usertype(tolua_S,"CMolMessageIn");
 tolua_usertype(tolua_S,"CMolRect<int>");
 tolua_usertype(tolua_S,"CMolDimension2d<int>");
 tolua_usertype(tolua_S,"Room");
 tolua_usertype(tolua_S,"CMolDimension2d<double>");
 tolua_usertype(tolua_S,"Player");
 tolua_usertype(tolua_S,"CMolRect<double>");
 tolua_usertype(tolua_S,"CMolPosition2d<int>");
}

/* method: new of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_int__new00
static int tolua_MolServer_CMolPosition2d_int__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolPosition2d<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolPosition2d<int>* tolua_ret = (CMolPosition2d<int>*)  Mtolua_new((CMolPosition2d<int>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolPosition2d<int>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_int__new00_local
static int tolua_MolServer_CMolPosition2d_int__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolPosition2d<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolPosition2d<int>* tolua_ret = (CMolPosition2d<int>*)  Mtolua_new((CMolPosition2d<int>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_int__new01
static int tolua_MolServer_CMolPosition2d_int__new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolPosition2d<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   CMolPosition2d<int>* tolua_ret = (CMolPosition2d<int>*)  Mtolua_new((CMolPosition2d<int>)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolPosition2d<int>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolPosition2d_int__new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_int__new01_local
static int tolua_MolServer_CMolPosition2d_int__new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolPosition2d<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   CMolPosition2d<int>* tolua_ret = (CMolPosition2d<int>*)  Mtolua_new((CMolPosition2d<int>)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolPosition2d_int__new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_int__new02
static int tolua_MolServer_CMolPosition2d_int__new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolPosition2d<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<int>* other = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
  {
   CMolPosition2d<int>* tolua_ret = (CMolPosition2d<int>*)  Mtolua_new((CMolPosition2d<int>)(*other));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolPosition2d<int>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolPosition2d_int__new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_int__new02_local
static int tolua_MolServer_CMolPosition2d_int__new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolPosition2d<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<int>* other = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
  {
   CMolPosition2d<int>* tolua_ret = (CMolPosition2d<int>*)  Mtolua_new((CMolPosition2d<int>)(*other));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolPosition2d_int__new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_int___eq00
static int tolua_MolServer_CMolPosition2d_int___eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolPosition2d<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolPosition2d<int>* self = (const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<int>* other = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_int___sub00
static int tolua_MolServer_CMolPosition2d_int___sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolPosition2d<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolPosition2d<int>* self = (const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<int>* other = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CMolPosition2d<int> tolua_ret = (CMolPosition2d<int>)  self->operator-(*other);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolPosition2d<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolPosition2d<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_int___add00
static int tolua_MolServer_CMolPosition2d_int___add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolPosition2d<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolPosition2d<int>* self = (const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<int>* other = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CMolPosition2d<int> tolua_ret = (CMolPosition2d<int>)  self->operator+(*other);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolPosition2d<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolPosition2d<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_int___mul00
static int tolua_MolServer_CMolPosition2d_int___mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolPosition2d<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolPosition2d<int>* self = (const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<int>* other = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CMolPosition2d<int> tolua_ret = (CMolPosition2d<int>)  self->operator*(*other);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolPosition2d<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolPosition2d<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_int___add01
static int tolua_MolServer_CMolPosition2d_int___add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolPosition2d<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolDimension2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<int>* self = (const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolDimension2d<int>* other = ((const CMolDimension2d<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CMolPosition2d<int> tolua_ret = (CMolPosition2d<int>)  self->operator+(*other);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolPosition2d<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolPosition2d<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolPosition2d_int___add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_int___sub01
static int tolua_MolServer_CMolPosition2d_int___sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolPosition2d<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolDimension2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<int>* self = (const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolDimension2d<int>* other = ((const CMolDimension2d<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CMolPosition2d<int> tolua_ret = (CMolPosition2d<int>)  self->operator-(*other);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolPosition2d<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolPosition2d<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolPosition2d_int___sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: X of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_get_CMolPosition2d_int__X
static int tolua_get_CMolPosition2d_int__X(lua_State* tolua_S)
{
  CMolPosition2d<int>* self = (CMolPosition2d<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'X'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->X);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: X of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_set_CMolPosition2d_int__X
static int tolua_set_CMolPosition2d_int__X(lua_State* tolua_S)
{
  CMolPosition2d<int>* self = (CMolPosition2d<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'X'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->X = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Y of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_get_CMolPosition2d_int__Y
static int tolua_get_CMolPosition2d_int__Y(lua_State* tolua_S)
{
  CMolPosition2d<int>* self = (CMolPosition2d<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Y of class  CMolPosition2d<int> */
#ifndef TOLUA_DISABLE_tolua_set_CMolPosition2d_int__Y
static int tolua_set_CMolPosition2d_int__Y(lua_State* tolua_S)
{
  CMolPosition2d<int>* self = (CMolPosition2d<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Y = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_double__new00
static int tolua_MolServer_CMolPosition2d_double__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolPosition2d<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolPosition2d<double>* tolua_ret = (CMolPosition2d<double>*)  Mtolua_new((CMolPosition2d<double>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolPosition2d<double>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_double__new00_local
static int tolua_MolServer_CMolPosition2d_double__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolPosition2d<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolPosition2d<double>* tolua_ret = (CMolPosition2d<double>*)  Mtolua_new((CMolPosition2d<double>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_double__new01
static int tolua_MolServer_CMolPosition2d_double__new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolPosition2d<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CMolPosition2d<double>* tolua_ret = (CMolPosition2d<double>*)  Mtolua_new((CMolPosition2d<double>)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolPosition2d<double>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolPosition2d_double__new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_double__new01_local
static int tolua_MolServer_CMolPosition2d_double__new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolPosition2d<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CMolPosition2d<double>* tolua_ret = (CMolPosition2d<double>*)  Mtolua_new((CMolPosition2d<double>)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolPosition2d_double__new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_double__new02
static int tolua_MolServer_CMolPosition2d_double__new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolPosition2d<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<double>* other = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
  {
   CMolPosition2d<double>* tolua_ret = (CMolPosition2d<double>*)  Mtolua_new((CMolPosition2d<double>)(*other));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolPosition2d<double>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolPosition2d_double__new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_double__new02_local
static int tolua_MolServer_CMolPosition2d_double__new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolPosition2d<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<double>* other = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
  {
   CMolPosition2d<double>* tolua_ret = (CMolPosition2d<double>*)  Mtolua_new((CMolPosition2d<double>)(*other));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolPosition2d_double__new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_double___eq00
static int tolua_MolServer_CMolPosition2d_double___eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolPosition2d<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolPosition2d<double>* self = (const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<double>* other = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_double___sub00
static int tolua_MolServer_CMolPosition2d_double___sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolPosition2d<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolPosition2d<double>* self = (const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<double>* other = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CMolPosition2d<double> tolua_ret = (CMolPosition2d<double>)  self->operator-(*other);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolPosition2d<double>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolPosition2d<double>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_double___add00
static int tolua_MolServer_CMolPosition2d_double___add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolPosition2d<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolPosition2d<double>* self = (const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<double>* other = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CMolPosition2d<double> tolua_ret = (CMolPosition2d<double>)  self->operator+(*other);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolPosition2d<double>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolPosition2d<double>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_double___mul00
static int tolua_MolServer_CMolPosition2d_double___mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolPosition2d<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolPosition2d<double>* self = (const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<double>* other = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CMolPosition2d<double> tolua_ret = (CMolPosition2d<double>)  self->operator*(*other);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolPosition2d<double>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolPosition2d<double>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_double___add01
static int tolua_MolServer_CMolPosition2d_double___add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolPosition2d<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolDimension2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<double>* self = (const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolDimension2d<double>* other = ((const CMolDimension2d<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CMolPosition2d<double> tolua_ret = (CMolPosition2d<double>)  self->operator+(*other);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolPosition2d<double>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolPosition2d<double>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolPosition2d_double___add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolPosition2d_double___sub01
static int tolua_MolServer_CMolPosition2d_double___sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolPosition2d<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolDimension2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<double>* self = (const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolDimension2d<double>* other = ((const CMolDimension2d<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CMolPosition2d<double> tolua_ret = (CMolPosition2d<double>)  self->operator-(*other);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolPosition2d<double>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolPosition2d<double>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolPosition2d_double___sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: X of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_get_CMolPosition2d_double__X
static int tolua_get_CMolPosition2d_double__X(lua_State* tolua_S)
{
  CMolPosition2d<double>* self = (CMolPosition2d<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'X'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->X);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: X of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_set_CMolPosition2d_double__X
static int tolua_set_CMolPosition2d_double__X(lua_State* tolua_S)
{
  CMolPosition2d<double>* self = (CMolPosition2d<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'X'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->X = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Y of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_get_CMolPosition2d_double__Y
static int tolua_get_CMolPosition2d_double__Y(lua_State* tolua_S)
{
  CMolPosition2d<double>* self = (CMolPosition2d<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Y of class  CMolPosition2d<double> */
#ifndef TOLUA_DISABLE_tolua_set_CMolPosition2d_double__Y
static int tolua_set_CMolPosition2d_double__Y(lua_State* tolua_S)
{
  CMolPosition2d<double>* self = (CMolPosition2d<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Y = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_int__new00
static int tolua_MolServer_CMolDimension2d_int__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolDimension2d<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolDimension2d<int>* tolua_ret = (CMolDimension2d<int>*)  Mtolua_new((CMolDimension2d<int>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolDimension2d<int>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_int__new00_local
static int tolua_MolServer_CMolDimension2d_int__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolDimension2d<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolDimension2d<int>* tolua_ret = (CMolDimension2d<int>*)  Mtolua_new((CMolDimension2d<int>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolDimension2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_int__new01
static int tolua_MolServer_CMolDimension2d_int__new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolDimension2d<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const int width = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int height = ((const int)  tolua_tonumber(tolua_S,3,0));
  {
   CMolDimension2d<int>* tolua_ret = (CMolDimension2d<int>*)  Mtolua_new((CMolDimension2d<int>)(width,height));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolDimension2d<int>");
   tolua_pushnumber(tolua_S,(lua_Number)width);
   tolua_pushnumber(tolua_S,(lua_Number)height);
  }
 }
 return 3;
tolua_lerror:
 return tolua_MolServer_CMolDimension2d_int__new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_int__new01_local
static int tolua_MolServer_CMolDimension2d_int__new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolDimension2d<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const int width = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int height = ((const int)  tolua_tonumber(tolua_S,3,0));
  {
   CMolDimension2d<int>* tolua_ret = (CMolDimension2d<int>*)  Mtolua_new((CMolDimension2d<int>)(width,height));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolDimension2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushnumber(tolua_S,(lua_Number)width);
   tolua_pushnumber(tolua_S,(lua_Number)height);
  }
 }
 return 3;
tolua_lerror:
 return tolua_MolServer_CMolDimension2d_int__new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_int___eq00
static int tolua_MolServer_CMolDimension2d_int___eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolDimension2d<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolDimension2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolDimension2d<int>* self = (const CMolDimension2d<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolDimension2d<int>* other = ((const CMolDimension2d<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_int__set00
static int tolua_MolServer_CMolDimension2d_int__set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolDimension2d<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolDimension2d<int>* self = (CMolDimension2d<int>*)  tolua_tousertype(tolua_S,1,0);
  const int width = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int height = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set'", NULL);
#endif
  {
   CMolDimension2d<int>& tolua_ret = (CMolDimension2d<int>&)  self->set(width,height);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CMolDimension2d<int>");
   tolua_pushnumber(tolua_S,(lua_Number)width);
   tolua_pushnumber(tolua_S,(lua_Number)height);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_int___div00
static int tolua_MolServer_CMolDimension2d_int___div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolDimension2d<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolDimension2d<int>* self = (const CMolDimension2d<int>*)  tolua_tousertype(tolua_S,1,0);
  const int scale = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   CMolDimension2d<int> tolua_ret = (CMolDimension2d<int>)  self->operator/(scale);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolDimension2d<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolDimension2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolDimension2d<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolDimension2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
   tolua_pushnumber(tolua_S,(lua_Number)scale);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_int___mul00
static int tolua_MolServer_CMolDimension2d_int___mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolDimension2d<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolDimension2d<int>* self = (const CMolDimension2d<int>*)  tolua_tousertype(tolua_S,1,0);
  const int scale = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CMolDimension2d<int> tolua_ret = (CMolDimension2d<int>)  self->operator*(scale);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolDimension2d<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolDimension2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolDimension2d<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolDimension2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
   tolua_pushnumber(tolua_S,(lua_Number)scale);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArea of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_int__getArea00
static int tolua_MolServer_CMolDimension2d_int__getArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolDimension2d<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolDimension2d<int>* self = (const CMolDimension2d<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArea'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getArea();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Width of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_get_CMolDimension2d_int__Width
static int tolua_get_CMolDimension2d_int__Width(lua_State* tolua_S)
{
  CMolDimension2d<int>* self = (CMolDimension2d<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Width'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Width);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Width of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_set_CMolDimension2d_int__Width
static int tolua_set_CMolDimension2d_int__Width(lua_State* tolua_S)
{
  CMolDimension2d<int>* self = (CMolDimension2d<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Width'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Width = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Height of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_get_CMolDimension2d_int__Height
static int tolua_get_CMolDimension2d_int__Height(lua_State* tolua_S)
{
  CMolDimension2d<int>* self = (CMolDimension2d<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Height'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Height);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Height of class  CMolDimension2d<int> */
#ifndef TOLUA_DISABLE_tolua_set_CMolDimension2d_int__Height
static int tolua_set_CMolDimension2d_int__Height(lua_State* tolua_S)
{
  CMolDimension2d<int>* self = (CMolDimension2d<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Height'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Height = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_double__new00
static int tolua_MolServer_CMolDimension2d_double__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolDimension2d<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolDimension2d<double>* tolua_ret = (CMolDimension2d<double>*)  Mtolua_new((CMolDimension2d<double>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolDimension2d<double>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_double__new00_local
static int tolua_MolServer_CMolDimension2d_double__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolDimension2d<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolDimension2d<double>* tolua_ret = (CMolDimension2d<double>*)  Mtolua_new((CMolDimension2d<double>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolDimension2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_double__new01
static int tolua_MolServer_CMolDimension2d_double__new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolDimension2d<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const double width = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double height = ((const double)  tolua_tonumber(tolua_S,3,0));
  {
   CMolDimension2d<double>* tolua_ret = (CMolDimension2d<double>*)  Mtolua_new((CMolDimension2d<double>)(width,height));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolDimension2d<double>");
   tolua_pushnumber(tolua_S,(lua_Number)width);
   tolua_pushnumber(tolua_S,(lua_Number)height);
  }
 }
 return 3;
tolua_lerror:
 return tolua_MolServer_CMolDimension2d_double__new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_double__new01_local
static int tolua_MolServer_CMolDimension2d_double__new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolDimension2d<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const double width = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double height = ((const double)  tolua_tonumber(tolua_S,3,0));
  {
   CMolDimension2d<double>* tolua_ret = (CMolDimension2d<double>*)  Mtolua_new((CMolDimension2d<double>)(width,height));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolDimension2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushnumber(tolua_S,(lua_Number)width);
   tolua_pushnumber(tolua_S,(lua_Number)height);
  }
 }
 return 3;
tolua_lerror:
 return tolua_MolServer_CMolDimension2d_double__new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_double___eq00
static int tolua_MolServer_CMolDimension2d_double___eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolDimension2d<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolDimension2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolDimension2d<double>* self = (const CMolDimension2d<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolDimension2d<double>* other = ((const CMolDimension2d<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_double__set00
static int tolua_MolServer_CMolDimension2d_double__set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolDimension2d<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolDimension2d<double>* self = (CMolDimension2d<double>*)  tolua_tousertype(tolua_S,1,0);
  const double width = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double height = ((const double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set'", NULL);
#endif
  {
   CMolDimension2d<double>& tolua_ret = (CMolDimension2d<double>&)  self->set(width,height);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CMolDimension2d<double>");
   tolua_pushnumber(tolua_S,(lua_Number)width);
   tolua_pushnumber(tolua_S,(lua_Number)height);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_double___div00
static int tolua_MolServer_CMolDimension2d_double___div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolDimension2d<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolDimension2d<double>* self = (const CMolDimension2d<double>*)  tolua_tousertype(tolua_S,1,0);
  const double scale = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   CMolDimension2d<double> tolua_ret = (CMolDimension2d<double>)  self->operator/(scale);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolDimension2d<double>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolDimension2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolDimension2d<double>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolDimension2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
   tolua_pushnumber(tolua_S,(lua_Number)scale);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_double___mul00
static int tolua_MolServer_CMolDimension2d_double___mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolDimension2d<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolDimension2d<double>* self = (const CMolDimension2d<double>*)  tolua_tousertype(tolua_S,1,0);
  const double scale = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CMolDimension2d<double> tolua_ret = (CMolDimension2d<double>)  self->operator*(scale);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolDimension2d<double>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolDimension2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolDimension2d<double>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolDimension2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
   tolua_pushnumber(tolua_S,(lua_Number)scale);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArea of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolDimension2d_double__getArea00
static int tolua_MolServer_CMolDimension2d_double__getArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolDimension2d<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolDimension2d<double>* self = (const CMolDimension2d<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArea'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getArea();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Width of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_get_CMolDimension2d_double__Width
static int tolua_get_CMolDimension2d_double__Width(lua_State* tolua_S)
{
  CMolDimension2d<double>* self = (CMolDimension2d<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Width'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Width);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Width of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_set_CMolDimension2d_double__Width
static int tolua_set_CMolDimension2d_double__Width(lua_State* tolua_S)
{
  CMolDimension2d<double>* self = (CMolDimension2d<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Width'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Width = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Height of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_get_CMolDimension2d_double__Height
static int tolua_get_CMolDimension2d_double__Height(lua_State* tolua_S)
{
  CMolDimension2d<double>* self = (CMolDimension2d<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Height'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Height);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Height of class  CMolDimension2d<double> */
#ifndef TOLUA_DISABLE_tolua_set_CMolDimension2d_double__Height
static int tolua_set_CMolDimension2d_double__Height(lua_State* tolua_S)
{
  CMolDimension2d<double>* self = (CMolDimension2d<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Height'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Height = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__new00
static int tolua_MolServer_CMolRect_int__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolRect<int>* tolua_ret = (CMolRect<int>*)  Mtolua_new((CMolRect<int>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<int>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__new00_local
static int tolua_MolServer_CMolRect_int__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolRect<int>* tolua_ret = (CMolRect<int>*)  Mtolua_new((CMolRect<int>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__new01
static int tolua_MolServer_CMolRect_int__new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int x2 = ((int)  tolua_tonumber(tolua_S,4,0));
  int y2 = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   CMolRect<int>* tolua_ret = (CMolRect<int>*)  Mtolua_new((CMolRect<int>)(x,y,x2,y2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<int>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolRect_int__new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__new01_local
static int tolua_MolServer_CMolRect_int__new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int x2 = ((int)  tolua_tonumber(tolua_S,4,0));
  int y2 = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   CMolRect<int>* tolua_ret = (CMolRect<int>*)  Mtolua_new((CMolRect<int>)(x,y,x2,y2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolRect_int__new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__new02
static int tolua_MolServer_CMolRect_int__new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CMolPosition2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<int>* upperLeft = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
  const CMolPosition2d<int>* lowerRight = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,3,0));
  {
   CMolRect<int>* tolua_ret = (CMolRect<int>*)  Mtolua_new((CMolRect<int>)(*upperLeft,*lowerRight));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<int>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolRect_int__new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__new02_local
static int tolua_MolServer_CMolRect_int__new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CMolPosition2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<int>* upperLeft = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
  const CMolPosition2d<int>* lowerRight = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,3,0));
  {
   CMolRect<int>* tolua_ret = (CMolRect<int>*)  Mtolua_new((CMolRect<int>)(*upperLeft,*lowerRight));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolRect_int__new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__new03
static int tolua_MolServer_CMolRect_int__new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CMolDimension2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<int>* pos = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
  const CMolDimension2d<int>* size = ((const CMolDimension2d<int>*)  tolua_tousertype(tolua_S,3,0));
  {
   CMolRect<int>* tolua_ret = (CMolRect<int>*)  Mtolua_new((CMolRect<int>)(*pos,*size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<int>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolRect_int__new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__new03_local
static int tolua_MolServer_CMolRect_int__new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CMolDimension2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<int>* pos = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
  const CMolDimension2d<int>* size = ((const CMolDimension2d<int>*)  tolua_tousertype(tolua_S,3,0));
  {
   CMolRect<int>* tolua_ret = (CMolRect<int>*)  Mtolua_new((CMolRect<int>)(*pos,*size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolRect_int__new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int___add00
static int tolua_MolServer_CMolRect_int___add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<int>* self = (const CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<int>* pos = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CMolRect<int> tolua_ret = (CMolRect<int>)  self->operator+(*pos);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolRect<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolRect<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolRect<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolRect<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int___sub00
static int tolua_MolServer_CMolRect_int___sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<int>* self = (const CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<int>* pos = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CMolRect<int>& tolua_ret = (CMolRect<int>&)  self->operator-(*pos);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CMolRect<int>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int___eq00
static int tolua_MolServer_CMolRect_int___eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolRect<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<int>* self = (const CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolRect<int>* other = ((const CMolRect<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArea of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__getArea00
static int tolua_MolServer_CMolRect_int__getArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<int>* self = (const CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArea'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getArea();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPointInside of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__isPointInside00
static int tolua_MolServer_CMolRect_int__isPointInside00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<int>* self = (const CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<int>* pos = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPointInside'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPointInside(*pos);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPointInside'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRectCollided of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__isRectCollided00
static int tolua_MolServer_CMolRect_int__isRectCollided00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolRect<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<int>* self = (const CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolRect<int>* other = ((const CMolRect<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRectCollided'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isRectCollided(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRectCollided'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clipAgainst of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__clipAgainst00
static int tolua_MolServer_CMolRect_int__clipAgainst00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolRect<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolRect<int>* self = (CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolRect<int>* other = ((const CMolRect<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clipAgainst'", NULL);
#endif
  {
   self->clipAgainst(*other);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clipAgainst'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: constrainTo of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__constrainTo00
static int tolua_MolServer_CMolRect_int__constrainTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolRect<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolRect<int>* self = (CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolRect<int>* other = ((const CMolRect<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'constrainTo'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->constrainTo(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'constrainTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidth of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__getWidth00
static int tolua_MolServer_CMolRect_int__getWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<int>* self = (const CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHeight of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__getHeight00
static int tolua_MolServer_CMolRect_int__getHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<int>* self = (const CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: repair of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__repair00
static int tolua_MolServer_CMolRect_int__repair00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolRect<int>* self = (CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'repair'", NULL);
#endif
  {
   self->repair();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'repair'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isValid of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__isValid00
static int tolua_MolServer_CMolRect_int__isValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<int>* self = (const CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isValid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCenter of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__getCenter00
static int tolua_MolServer_CMolRect_int__getCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<int>* self = (const CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCenter'", NULL);
#endif
  {
   CMolPosition2d<int> tolua_ret = (CMolPosition2d<int>)  self->getCenter();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolPosition2d<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolPosition2d<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSize of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__getSize00
static int tolua_MolServer_CMolRect_int__getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<int>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<int>* self = (const CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'", NULL);
#endif
  {
   CMolDimension2d<int> tolua_ret = (CMolDimension2d<int>)  self->getSize();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolDimension2d<int>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolDimension2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolDimension2d<int>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolDimension2d<int>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addInternalPoint of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__addInternalPoint00
static int tolua_MolServer_CMolRect_int__addInternalPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolRect<int>* self = (CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<int>* p = ((const CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addInternalPoint'", NULL);
#endif
  {
   self->addInternalPoint(*p);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addInternalPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addInternalPoint of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_int__addInternalPoint01
static int tolua_MolServer_CMolRect_int__addInternalPoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolRect<int>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CMolRect<int>* self = (CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addInternalPoint'", NULL);
#endif
  {
   self->addInternalPoint(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_MolServer_CMolRect_int__addInternalPoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UpperLeftCorner of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_get_CMolRect_int__UpperLeftCorner
static int tolua_get_CMolRect_int__UpperLeftCorner(lua_State* tolua_S)
{
  CMolRect<int>* self = (CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UpperLeftCorner'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->UpperLeftCorner,"CMolPosition2d<int>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: UpperLeftCorner of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_set_CMolRect_int__UpperLeftCorner
static int tolua_set_CMolRect_int__UpperLeftCorner(lua_State* tolua_S)
{
  CMolRect<int>* self = (CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UpperLeftCorner'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CMolPosition2d<int>",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->UpperLeftCorner = *((CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: LowerRightCorner of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_get_CMolRect_int__LowerRightCorner
static int tolua_get_CMolRect_int__LowerRightCorner(lua_State* tolua_S)
{
  CMolRect<int>* self = (CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'LowerRightCorner'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->LowerRightCorner,"CMolPosition2d<int>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: LowerRightCorner of class  CMolRect<int> */
#ifndef TOLUA_DISABLE_tolua_set_CMolRect_int__LowerRightCorner
static int tolua_set_CMolRect_int__LowerRightCorner(lua_State* tolua_S)
{
  CMolRect<int>* self = (CMolRect<int>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'LowerRightCorner'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CMolPosition2d<int>",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->LowerRightCorner = *((CMolPosition2d<int>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__new00
static int tolua_MolServer_CMolRect_double__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolRect<double>* tolua_ret = (CMolRect<double>*)  Mtolua_new((CMolRect<double>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<double>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__new00_local
static int tolua_MolServer_CMolRect_double__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolRect<double>* tolua_ret = (CMolRect<double>*)  Mtolua_new((CMolRect<double>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__new01
static int tolua_MolServer_CMolRect_double__new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  double x2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double y2 = ((double)  tolua_tonumber(tolua_S,5,0));
  {
   CMolRect<double>* tolua_ret = (CMolRect<double>*)  Mtolua_new((CMolRect<double>)(x,y,x2,y2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<double>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolRect_double__new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__new01_local
static int tolua_MolServer_CMolRect_double__new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  double x2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double y2 = ((double)  tolua_tonumber(tolua_S,5,0));
  {
   CMolRect<double>* tolua_ret = (CMolRect<double>*)  Mtolua_new((CMolRect<double>)(x,y,x2,y2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolRect_double__new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__new02
static int tolua_MolServer_CMolRect_double__new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CMolPosition2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<double>* upperLeft = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
  const CMolPosition2d<double>* lowerRight = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,3,0));
  {
   CMolRect<double>* tolua_ret = (CMolRect<double>*)  Mtolua_new((CMolRect<double>)(*upperLeft,*lowerRight));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<double>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolRect_double__new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__new02_local
static int tolua_MolServer_CMolRect_double__new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CMolPosition2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<double>* upperLeft = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
  const CMolPosition2d<double>* lowerRight = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,3,0));
  {
   CMolRect<double>* tolua_ret = (CMolRect<double>*)  Mtolua_new((CMolRect<double>)(*upperLeft,*lowerRight));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolRect_double__new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__new03
static int tolua_MolServer_CMolRect_double__new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CMolDimension2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<double>* pos = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
  const CMolDimension2d<double>* size = ((const CMolDimension2d<double>*)  tolua_tousertype(tolua_S,3,0));
  {
   CMolRect<double>* tolua_ret = (CMolRect<double>*)  Mtolua_new((CMolRect<double>)(*pos,*size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<double>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolRect_double__new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__new03_local
static int tolua_MolServer_CMolRect_double__new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CMolDimension2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CMolPosition2d<double>* pos = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
  const CMolDimension2d<double>* size = ((const CMolDimension2d<double>*)  tolua_tousertype(tolua_S,3,0));
  {
   CMolRect<double>* tolua_ret = (CMolRect<double>*)  Mtolua_new((CMolRect<double>)(*pos,*size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolRect<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolRect_double__new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double___add00
static int tolua_MolServer_CMolRect_double___add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<double>* self = (const CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<double>* pos = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CMolRect<double> tolua_ret = (CMolRect<double>)  self->operator+(*pos);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolRect<double>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolRect<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolRect<double>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolRect<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double___sub00
static int tolua_MolServer_CMolRect_double___sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<double>* self = (const CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<double>* pos = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CMolRect<double>& tolua_ret = (CMolRect<double>&)  self->operator-(*pos);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CMolRect<double>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double___eq00
static int tolua_MolServer_CMolRect_double___eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolRect<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<double>* self = (const CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolRect<double>* other = ((const CMolRect<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArea of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__getArea00
static int tolua_MolServer_CMolRect_double__getArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<double>* self = (const CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArea'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getArea();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPointInside of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__isPointInside00
static int tolua_MolServer_CMolRect_double__isPointInside00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<double>* self = (const CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<double>* pos = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPointInside'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPointInside(*pos);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPointInside'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRectCollided of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__isRectCollided00
static int tolua_MolServer_CMolRect_double__isRectCollided00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolRect<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<double>* self = (const CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolRect<double>* other = ((const CMolRect<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRectCollided'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isRectCollided(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRectCollided'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clipAgainst of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__clipAgainst00
static int tolua_MolServer_CMolRect_double__clipAgainst00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolRect<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolRect<double>* self = (CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolRect<double>* other = ((const CMolRect<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clipAgainst'", NULL);
#endif
  {
   self->clipAgainst(*other);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clipAgainst'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: constrainTo of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__constrainTo00
static int tolua_MolServer_CMolRect_double__constrainTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolRect<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolRect<double>* self = (CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolRect<double>* other = ((const CMolRect<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'constrainTo'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->constrainTo(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'constrainTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidth of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__getWidth00
static int tolua_MolServer_CMolRect_double__getWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<double>* self = (const CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidth'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHeight of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__getHeight00
static int tolua_MolServer_CMolRect_double__getHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<double>* self = (const CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHeight'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: repair of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__repair00
static int tolua_MolServer_CMolRect_double__repair00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolRect<double>* self = (CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'repair'", NULL);
#endif
  {
   self->repair();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'repair'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isValid of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__isValid00
static int tolua_MolServer_CMolRect_double__isValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<double>* self = (const CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isValid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCenter of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__getCenter00
static int tolua_MolServer_CMolRect_double__getCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<double>* self = (const CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCenter'", NULL);
#endif
  {
   CMolPosition2d<double> tolua_ret = (CMolPosition2d<double>)  self->getCenter();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolPosition2d<double>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolPosition2d<double>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolPosition2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSize of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__getSize00
static int tolua_MolServer_CMolRect_double__getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolRect<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolRect<double>* self = (const CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'", NULL);
#endif
  {
   CMolDimension2d<double> tolua_ret = (CMolDimension2d<double>)  self->getSize();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolDimension2d<double>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolDimension2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolDimension2d<double>));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolDimension2d<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addInternalPoint of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__addInternalPoint00
static int tolua_MolServer_CMolRect_double__addInternalPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CMolPosition2d<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolRect<double>* self = (CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
  const CMolPosition2d<double>* p = ((const CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addInternalPoint'", NULL);
#endif
  {
   self->addInternalPoint(*p);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addInternalPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addInternalPoint of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolRect_double__addInternalPoint01
static int tolua_MolServer_CMolRect_double__addInternalPoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolRect<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CMolRect<double>* self = (CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addInternalPoint'", NULL);
#endif
  {
   self->addInternalPoint(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_MolServer_CMolRect_double__addInternalPoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UpperLeftCorner of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_get_CMolRect_double__UpperLeftCorner
static int tolua_get_CMolRect_double__UpperLeftCorner(lua_State* tolua_S)
{
  CMolRect<double>* self = (CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UpperLeftCorner'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->UpperLeftCorner,"CMolPosition2d<double>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: UpperLeftCorner of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_set_CMolRect_double__UpperLeftCorner
static int tolua_set_CMolRect_double__UpperLeftCorner(lua_State* tolua_S)
{
  CMolRect<double>* self = (CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UpperLeftCorner'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CMolPosition2d<double>",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->UpperLeftCorner = *((CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: LowerRightCorner of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_get_CMolRect_double__LowerRightCorner
static int tolua_get_CMolRect_double__LowerRightCorner(lua_State* tolua_S)
{
  CMolRect<double>* self = (CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'LowerRightCorner'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->LowerRightCorner,"CMolPosition2d<double>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: LowerRightCorner of class  CMolRect<double> */
#ifndef TOLUA_DISABLE_tolua_set_CMolRect_double__LowerRightCorner
static int tolua_set_CMolRect_double__LowerRightCorner(lua_State* tolua_S)
{
  CMolRect<double>* self = (CMolRect<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'LowerRightCorner'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CMolPosition2d<double>",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->LowerRightCorner = *((CMolPosition2d<double>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolString */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolString_new00
static int tolua_MolServer_CMolString_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolString",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolString* tolua_ret = (CMolString*)  Mtolua_new((CMolString)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolString");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolString */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolString_new00_local
static int tolua_MolServer_CMolString_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolString",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolString* tolua_ret = (CMolString*)  Mtolua_new((CMolString)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolString */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolString_new01
static int tolua_MolServer_CMolString_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolString",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  std::string str = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   CMolString* tolua_ret = (CMolString*)  Mtolua_new((CMolString)(str));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolString");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolString_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolString */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolString_new01_local
static int tolua_MolServer_CMolString_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolString",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  std::string str = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   CMolString* tolua_ret = (CMolString*)  Mtolua_new((CMolString)(str));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolString_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolString */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolString_new02
static int tolua_MolServer_CMolString_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolString",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* begin = ((const char*)  tolua_tostring(tolua_S,2,0));
  int length = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   CMolString* tolua_ret = (CMolString*)  Mtolua_new((CMolString)(begin,length));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolString");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolString_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolString */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolString_new02_local
static int tolua_MolServer_CMolString_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolString",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* begin = ((const char*)  tolua_tostring(tolua_S,2,0));
  int length = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   CMolString* tolua_ret = (CMolString*)  Mtolua_new((CMolString)(begin,length));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolString_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: c_str of class  CMolString */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolString_c_str00
static int tolua_MolServer_CMolString_c_str00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolString",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolString* self = (CMolString*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'c_str'", NULL);
#endif
  {
   char* tolua_ret = (char*)  self->c_str();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'c_str'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: at of class  CMolString */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolString_at00
static int tolua_MolServer_CMolString_at00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolString",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolString* self = (CMolString*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'at'", NULL);
#endif
  {
   char tolua_ret = (char)  self->at(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'at'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  CMolString */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolString_clear00
static int tolua_MolServer_CMolString_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolString",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolString* self = (CMolString*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: empty of class  CMolString */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolString_empty00
static int tolua_MolServer_CMolString_empty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolString",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolString* self = (CMolString*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'empty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->empty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'empty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: length of class  CMolString */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolString_length00
static int tolua_MolServer_CMolString_length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolString",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolString* self = (CMolString*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'length'", NULL);
#endif
  {
   int tolua_ret = (int)  self->length();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getId of class  CMolMessageIn */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageIn_getId00
static int tolua_MolServer_CMolMessageIn_getId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolMessageIn",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolMessageIn* self = (const CMolMessageIn*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getId'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLength of class  CMolMessageIn */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageIn_getLength00
static int tolua_MolServer_CMolMessageIn_getLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolMessageIn",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolMessageIn* self = (const CMolMessageIn*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLength'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readByte of class  CMolMessageIn */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageIn_readByte00
static int tolua_MolServer_CMolMessageIn_readByte00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolMessageIn",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolMessageIn* self = (CMolMessageIn*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readByte'", NULL);
#endif
  {
   int tolua_ret = (int)  self->readByte();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readByte'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readShort of class  CMolMessageIn */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageIn_readShort00
static int tolua_MolServer_CMolMessageIn_readShort00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolMessageIn",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolMessageIn* self = (CMolMessageIn*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readShort'", NULL);
#endif
  {
   int tolua_ret = (int)  self->readShort();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readShort'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readLong of class  CMolMessageIn */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageIn_readLong00
static int tolua_MolServer_CMolMessageIn_readLong00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolMessageIn",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolMessageIn* self = (CMolMessageIn*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readLong'", NULL);
#endif
  {
   int tolua_ret = (int)  self->readLong();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readLong'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readString of class  CMolMessageIn */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageIn_readString00
static int tolua_MolServer_CMolMessageIn_readString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolMessageIn",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolMessageIn* self = (CMolMessageIn*)  tolua_tousertype(tolua_S,1,0);
  int length = ((int)  tolua_tonumber(tolua_S,2,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readString'", NULL);
#endif
  {
   CMolString tolua_ret = (CMolString)  self->readString(length);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMolString)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMolString));
     tolua_pushusertype(tolua_S,tolua_obj,"CMolString");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUnreadLength of class  CMolMessageIn */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageIn_getUnreadLength00
static int tolua_MolServer_CMolMessageIn_getUnreadLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolMessageIn",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolMessageIn* self = (const CMolMessageIn*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUnreadLength'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getUnreadLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUnreadLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolMessageOut */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageOut_new00
static int tolua_MolServer_CMolMessageOut_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolMessageOut",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolMessageOut* tolua_ret = (CMolMessageOut*)  Mtolua_new((CMolMessageOut)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolMessageOut");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolMessageOut */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageOut_new00_local
static int tolua_MolServer_CMolMessageOut_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolMessageOut",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMolMessageOut* tolua_ret = (CMolMessageOut*)  Mtolua_new((CMolMessageOut)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolMessageOut");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMolMessageOut */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageOut_new01
static int tolua_MolServer_CMolMessageOut_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolMessageOut",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   CMolMessageOut* tolua_ret = (CMolMessageOut*)  Mtolua_new((CMolMessageOut)(id));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolMessageOut");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolMessageOut_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMolMessageOut */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageOut_new01_local
static int tolua_MolServer_CMolMessageOut_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMolMessageOut",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   CMolMessageOut* tolua_ret = (CMolMessageOut*)  Mtolua_new((CMolMessageOut)(id));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMolMessageOut");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_CMolMessageOut_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CMolMessageOut */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageOut_delete00
static int tolua_MolServer_CMolMessageOut_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolMessageOut",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolMessageOut* self = (CMolMessageOut*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  CMolMessageOut */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageOut_clear00
static int tolua_MolServer_CMolMessageOut_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolMessageOut",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolMessageOut* self = (CMolMessageOut*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: writeByte of class  CMolMessageOut */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageOut_writeByte00
static int tolua_MolServer_CMolMessageOut_writeByte00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolMessageOut",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolMessageOut* self = (CMolMessageOut*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'writeByte'", NULL);
#endif
  {
   self->writeByte(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'writeByte'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: writeShort of class  CMolMessageOut */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageOut_writeShort00
static int tolua_MolServer_CMolMessageOut_writeShort00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolMessageOut",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolMessageOut* self = (CMolMessageOut*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'writeShort'", NULL);
#endif
  {
   self->writeShort(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'writeShort'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: writeLong of class  CMolMessageOut */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageOut_writeLong00
static int tolua_MolServer_CMolMessageOut_writeLong00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolMessageOut",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolMessageOut* self = (CMolMessageOut*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'writeLong'", NULL);
#endif
  {
   self->writeLong(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'writeLong'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: writeString of class  CMolMessageOut */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageOut_writeString00
static int tolua_MolServer_CMolMessageOut_writeString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMolMessageOut",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMolMessageOut* self = (CMolMessageOut*)  tolua_tousertype(tolua_S,1,0);
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  int length = ((int)  tolua_tonumber(tolua_S,3,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'writeString'", NULL);
#endif
  {
   self->writeString(str,length);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'writeString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getData of class  CMolMessageOut */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageOut_getData00
static int tolua_MolServer_CMolMessageOut_getData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolMessageOut",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolMessageOut* self = (const CMolMessageOut*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getData'", NULL);
#endif
  {
   char* tolua_ret = (char*)  self->getData();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLength of class  CMolMessageOut */
#ifndef TOLUA_DISABLE_tolua_MolServer_CMolMessageOut_getLength00
static int tolua_MolServer_CMolMessageOut_getLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMolMessageOut",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMolMessageOut* self = (const CMolMessageOut*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLength'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetID of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetID00
static int tolua_MolServer_Player_SetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetID'", NULL);
#endif
  {
   self->SetID(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetID of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetID00
static int tolua_MolServer_Player_GetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetID'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetConnectID of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetConnectID00
static int tolua_MolServer_Player_SetConnectID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetConnectID'", NULL);
#endif
  {
   self->SetConnectID(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetConnectID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetConnectID of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetConnectID00
static int tolua_MolServer_Player_GetConnectID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetConnectID'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetConnectID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetConnectID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRoomId of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetRoomId00
static int tolua_MolServer_Player_SetRoomId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRoomId'", NULL);
#endif
  {
   self->SetRoomId(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRoomId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoomId of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetRoomId00
static int tolua_MolServer_Player_GetRoomId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoomId'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetRoomId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRoomId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetType of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetType00
static int tolua_MolServer_Player_SetType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  PlayerType type = ((PlayerType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetType'", NULL);
#endif
  {
   self->SetType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetType of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetType00
static int tolua_MolServer_Player_GetType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetType'", NULL);
#endif
  {
   PlayerType tolua_ret = (PlayerType)  self->GetType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRoomIndex of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetRoomIndex00
static int tolua_MolServer_Player_SetRoomIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRoomIndex'", NULL);
#endif
  {
   self->SetRoomIndex(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRoomIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoomIndex of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetRoomIndex00
static int tolua_MolServer_Player_GetRoomIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoomIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetRoomIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRoomIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHeartCount of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetHeartCount00
static int tolua_MolServer_Player_SetHeartCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  int count = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHeartCount'", NULL);
#endif
  {
   self->SetHeartCount(count);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHeartCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeartCount of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetHeartCount00
static int tolua_MolServer_Player_GetHeartCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeartCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetHeartCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeartCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetName of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetName00
static int tolua_MolServer_Player_SetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetName'", NULL);
#endif
  {
   self->SetName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetName of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetName00
static int tolua_MolServer_Player_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->GetName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetState of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetState00
static int tolua_MolServer_Player_GetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetState'", NULL);
#endif
  {
   PlayerState tolua_ret = (PlayerState)  self->GetState();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetState of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetState00
static int tolua_MolServer_Player_SetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  PlayerState state = ((PlayerState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetState'", NULL);
#endif
  {
   self->SetState(state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLookOn of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetLookOn00
static int tolua_MolServer_Player_SetLookOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  bool isLook = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLookOn'", NULL);
#endif
  {
   self->SetLookOn(isLook);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLookOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsLookOn of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_IsLookOn00
static int tolua_MolServer_Player_IsLookOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsLookOn'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsLookOn();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsLookOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMoney of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetMoney00
static int tolua_MolServer_Player_SetMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  double money = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMoney'", NULL);
#endif
  {
   self->SetMoney(money);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMoney of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetMoney00
static int tolua_MolServer_Player_GetMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMoney'", NULL);
#endif
  {
   double tolua_ret = (double)  self->GetMoney();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLevel of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetLevel00
static int tolua_MolServer_Player_SetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLevel'", NULL);
#endif
  {
   self->SetLevel(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevel of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetLevel00
static int tolua_MolServer_Player_GetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevel'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetExperience of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetExperience00
static int tolua_MolServer_Player_SetExperience00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  unsigned int exp = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetExperience'", NULL);
#endif
  {
   self->SetExperience(exp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetExperience'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetExperience of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetExperience00
static int tolua_MolServer_Player_GetExperience00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetExperience'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetExperience();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetExperience'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUserAvatar of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetUserAvatar00
static int tolua_MolServer_Player_SetUserAvatar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  std::string ava = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUserAvatar'", NULL);
#endif
  {
   self->SetUserAvatar(ava);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUserAvatar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUserAvatar of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetUserAvatar00
static int tolua_MolServer_Player_GetUserAvatar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUserAvatar'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->GetUserAvatar();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUserAvatar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTotalBureau of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetTotalBureau00
static int tolua_MolServer_Player_SetTotalBureau00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  int bureau = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTotalBureau'", NULL);
#endif
  {
   self->SetTotalBureau(bureau);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTotalBureau'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTotalBureau of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetTotalBureau00
static int tolua_MolServer_Player_GetTotalBureau00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTotalBureau'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetTotalBureau();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTotalBureau'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSuccessBureau of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetSuccessBureau00
static int tolua_MolServer_Player_SetSuccessBureau00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  int bureau = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSuccessBureau'", NULL);
#endif
  {
   self->SetSuccessBureau(bureau);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSuccessBureau'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSuccessBureau of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetSuccessBureau00
static int tolua_MolServer_Player_GetSuccessBureau00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSuccessBureau'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetSuccessBureau();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSuccessBureau'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFailBureau of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetFailBureau00
static int tolua_MolServer_Player_SetFailBureau00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  int bureau = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFailBureau'", NULL);
#endif
  {
   self->SetFailBureau(bureau);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFailBureau'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFailBureau of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetFailBureau00
static int tolua_MolServer_Player_GetFailBureau00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFailBureau'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetFailBureau();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFailBureau'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSuccessRate of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetSuccessRate00
static int tolua_MolServer_Player_SetSuccessRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  float rate = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSuccessRate'", NULL);
#endif
  {
   self->SetSuccessRate(rate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSuccessRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSuccessRate of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetSuccessRate00
static int tolua_MolServer_Player_GetSuccessRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSuccessRate'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetSuccessRate();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSuccessRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRunawayrate of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_SetRunawayrate00
static int tolua_MolServer_Player_SetRunawayrate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  float rate = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRunawayrate'", NULL);
#endif
  {
   self->SetRunawayrate(rate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRunawayrate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRunawayrate of class  Player */
#ifndef TOLUA_DISABLE_tolua_MolServer_Player_GetRunawayrate00
static int tolua_MolServer_Player_GetRunawayrate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRunawayrate'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRunawayrate();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRunawayrate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetID of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SetID00
static int tolua_MolServer_Room_SetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetID'", NULL);
#endif
  {
   self->SetID(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetID of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetID00
static int tolua_MolServer_Room_GetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetID'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRoomType of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SetRoomType00
static int tolua_MolServer_Room_SetRoomType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  RoomType type = ((RoomType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRoomType'", NULL);
#endif
  {
   self->SetRoomType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRoomType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoomType of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetRoomType00
static int tolua_MolServer_Room_GetRoomType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoomType'", NULL);
#endif
  {
   RoomType tolua_ret = (RoomType)  self->GetRoomType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRoomType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxPlayer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SetMaxPlayer00
static int tolua_MolServer_Room_SetMaxPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int max = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxPlayer'", NULL);
#endif
  {
   self->SetMaxPlayer(max);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxPlayer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetMaxPlayer00
static int tolua_MolServer_Room_GetMaxPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxPlayer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaxPlayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRoomState of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SetRoomState00
static int tolua_MolServer_Room_SetRoomState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  RoomState state = ((RoomState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRoomState'", NULL);
#endif
  {
   self->SetRoomState(state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRoomState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoomState of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetRoomState00
static int tolua_MolServer_Room_GetRoomState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoomState'", NULL);
#endif
  {
   RoomState tolua_ret = (RoomState)  self->GetRoomState();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRoomState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetName of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SetName00
static int tolua_MolServer_Room_SetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetName'", NULL);
#endif
  {
   self->SetName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetName of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetName00
static int tolua_MolServer_Room_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->GetName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetChouShui of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SetChouShui00
static int tolua_MolServer_Room_SetChouShui00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  float cs = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetChouShui'", NULL);
#endif
  {
   self->SetChouShui(cs);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetChouShui'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChouShui of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetChouShui00
static int tolua_MolServer_Room_GetChouShui00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChouShui'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetChouShui();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChouShui'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLastMoney of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SetLastMoney00
static int tolua_MolServer_Room_SetLastMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  unsigned int money = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLastMoney'", NULL);
#endif
  {
   self->SetLastMoney(money);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLastMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLastMoney of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetLastMoney00
static int tolua_MolServer_Room_GetLastMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLastMoney'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetLastMoney();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLastMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsEmpty of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_IsEmpty00
static int tolua_MolServer_Room_IsEmpty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsEmpty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsEmpty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsEmpty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPlayer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetPlayer00
static int tolua_MolServer_Room_GetPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPlayer'", NULL);
#endif
  {
   Player* tolua_ret = (Player*)  self->GetPlayer(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Player");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPlayerCount of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetPlayerCount00
static int tolua_MolServer_Room_GetPlayerCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPlayerCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetPlayerCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPlayerCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetReadyPlayerCount of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetReadyPlayerCount00
static int tolua_MolServer_Room_GetReadyPlayerCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetReadyPlayerCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetReadyPlayerCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetReadyPlayerCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaster of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SetMaster00
static int tolua_MolServer_Room_SetMaster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int playerId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaster'", NULL);
#endif
  {
   self->SetMaster(playerId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaster of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetMaster00
static int tolua_MolServer_Room_GetMaster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaster'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaster();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurrentPlayer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetCurrentPlayer00
static int tolua_MolServer_Room_GetCurrentPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurrentPlayer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetCurrentPlayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurrentPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPlayerRoomId of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetPlayerRoomId00
static int tolua_MolServer_Room_GetPlayerRoomId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int connId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPlayerRoomId'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetPlayerRoomId(connId);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPlayerRoomId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPlayerCount of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetPlayerCount01
static int tolua_MolServer_Room_GetPlayerCount01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  PlayerState state = ((PlayerState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPlayerCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetPlayerCount(state);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_MolServer_Room_GetPlayerCount00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAllPlayerState of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SetAllPlayerState00
static int tolua_MolServer_Room_SetAllPlayerState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  PlayerState state = ((PlayerState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAllPlayerState'", NULL);
#endif
  {
   self->SetAllPlayerState(state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAllPlayerState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPlayerState of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SetPlayerState00
static int tolua_MolServer_Room_SetPlayerState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  PlayerState state = ((PlayerState) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPlayerState'", NULL);
#endif
  {
   self->SetPlayerState(index,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPlayerState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCurrentPlayer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SetCurrentPlayer00
static int tolua_MolServer_Room_SetCurrentPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int playerId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCurrentPlayer'", NULL);
#endif
  {
   self->SetCurrentPlayer(playerId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCurrentPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurNextPlayer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetCurNextPlayer00
static int tolua_MolServer_Room_GetCurNextPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurNextPlayer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetCurNextPlayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurNextPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurNextWorkPlayer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetCurNextWorkPlayer00
static int tolua_MolServer_Room_GetCurNextWorkPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurNextWorkPlayer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetCurNextWorkPlayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurNextWorkPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearAllPlayers of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_ClearAllPlayers00
static int tolua_MolServer_Room_ClearAllPlayers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearAllPlayers'", NULL);
#endif
  {
   self->ClearAllPlayers();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearAllPlayers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddPlayer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_AddPlayer00
static int tolua_MolServer_Room_AddPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  Player* pPlayer = ((Player*)  tolua_tousertype(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddPlayer'", NULL);
#endif
  {
   self->AddPlayer(pPlayer,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddLookOnPlayer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_AddLookOnPlayer00
static int tolua_MolServer_Room_AddLookOnPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  Player* pPlayer = ((Player*)  tolua_tousertype(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddLookOnPlayer'", NULL);
#endif
  {
   self->AddLookOnPlayer(pPlayer,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddLookOnPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearPlayer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_ClearPlayer00
static int tolua_MolServer_Room_ClearPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  Player* pPlayer = ((Player*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearPlayer'", NULL);
#endif
  {
   self->ClearPlayer(pPlayer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DeletePlayer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_DeletePlayer00
static int tolua_MolServer_Room_DeletePlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  Player* pPlayer = ((Player*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DeletePlayer'", NULL);
#endif
  {
   self->DeletePlayer(pPlayer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DeletePlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearPlayerById of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_ClearPlayerById00
static int tolua_MolServer_Room_ClearPlayerById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int Id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearPlayerById'", NULL);
#endif
  {
   self->ClearPlayerById(Id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearPlayerById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsExist of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_IsExist00
static int tolua_MolServer_Room_IsExist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  Player* pPlayer = ((Player*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsExist'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsExist(pPlayer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsExist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsExistLookOn of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_IsExistLookOn00
static int tolua_MolServer_Room_IsExistLookOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  Player* pPlayer = ((Player*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsExistLookOn'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsExistLookOn(pPlayer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsExistLookOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFull of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_IsFull00
static int tolua_MolServer_Room_IsFull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFull'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsFull();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsReadyed of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_IsReadyed00
static int tolua_MolServer_Room_IsReadyed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsReadyed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsReadyed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsReadyed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPlayerIndex of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetPlayerIndex00
static int tolua_MolServer_Room_GetPlayerIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int connId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPlayerIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetPlayerIndex(connId);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPlayerIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLostPlayerCount of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GetLostPlayerCount00
static int tolua_MolServer_Room_GetLostPlayerCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLostPlayerCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetLostPlayerCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLostPlayerCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_Clear00
static int tolua_MolServer_Room_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clear'", NULL);
#endif
  {
   self->Clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdateUserScore of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_UpdateUserScore00
static int tolua_MolServer_Room_UpdateUserScore00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int ChairID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdateUserScore'", NULL);
#endif
  {
   self->UpdateUserScore(ChairID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdateUserScore'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GameEnd of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GameEnd00
static int tolua_MolServer_Room_GameEnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GameEnd'", NULL);
#endif
  {
   self->GameEnd();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GameEnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GameStart of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_GameStart00
static int tolua_MolServer_Room_GameStart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GameStart'", NULL);
#endif
  {
   self->GameStart();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GameStart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendTableMsg of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SendTableMsg00
static int tolua_MolServer_Room_SendTableMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CMolMessageOut",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  CMolMessageOut* msg = ((CMolMessageOut*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendTableMsg'", NULL);
#endif
  {
   self->SendTableMsg(index,*msg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendTableMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendLookOnMes of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SendLookOnMes00
static int tolua_MolServer_Room_SendLookOnMes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CMolMessageOut",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  CMolMessageOut* msg = ((CMolMessageOut*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendLookOnMes'", NULL);
#endif
  {
   self->SendLookOnMes(index,*msg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendLookOnMes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendAllPlayerMsg of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_SendAllPlayerMsg00
static int tolua_MolServer_Room_SendAllPlayerMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CMolMessageOut",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  CMolMessageOut* msg = ((CMolMessageOut*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendAllPlayerMsg'", NULL);
#endif
  {
   self->SendAllPlayerMsg(*msg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendAllPlayerMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PrintDebugInfo of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_PrintDebugInfo00
static int tolua_MolServer_Room_PrintDebugInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  const char* info = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PrintDebugInfo'", NULL);
#endif
  {
   self->PrintDebugInfo(info);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrintDebugInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StartTimer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_StartTimer00
static int tolua_MolServer_Room_StartTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int timerId = ((int)  tolua_tonumber(tolua_S,2,0));
  int space = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StartTimer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->StartTimer(timerId,space);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StartTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopTimer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_StopTimer00
static int tolua_MolServer_Room_StopTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopTimer'", NULL);
#endif
  {
   self->StopTimer(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopAllTimer of class  Room */
#ifndef TOLUA_DISABLE_tolua_MolServer_Room_StopAllTimer00
static int tolua_MolServer_Room_StopAllTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopAllTimer'", NULL);
#endif
  {
   self->StopAllTimer();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopAllTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_MolServer_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CMolPosition2d_int_","CMolPosition2d<int>","",tolua_collect_CMolPosition2d_int_);
  #else
  tolua_cclass(tolua_S,"CMolPosition2d_int_","CMolPosition2d<int>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CMolPosition2d_int_");
   tolua_function(tolua_S,"new",tolua_MolServer_CMolPosition2d_int__new00);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolPosition2d_int__new00_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolPosition2d_int__new00_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolPosition2d_int__new01);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolPosition2d_int__new01_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolPosition2d_int__new01_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolPosition2d_int__new02);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolPosition2d_int__new02_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolPosition2d_int__new02_local);
   tolua_function(tolua_S,".eq",tolua_MolServer_CMolPosition2d_int___eq00);
   tolua_function(tolua_S,".sub",tolua_MolServer_CMolPosition2d_int___sub00);
   tolua_function(tolua_S,".add",tolua_MolServer_CMolPosition2d_int___add00);
   tolua_function(tolua_S,".mul",tolua_MolServer_CMolPosition2d_int___mul00);
   tolua_function(tolua_S,".add",tolua_MolServer_CMolPosition2d_int___add01);
   tolua_function(tolua_S,".sub",tolua_MolServer_CMolPosition2d_int___sub01);
   tolua_variable(tolua_S,"X",tolua_get_CMolPosition2d_int__X,tolua_set_CMolPosition2d_int__X);
   tolua_variable(tolua_S,"Y",tolua_get_CMolPosition2d_int__Y,tolua_set_CMolPosition2d_int__Y);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CMolPosition2d_double_","CMolPosition2d<double>","",tolua_collect_CMolPosition2d_double_);
  #else
  tolua_cclass(tolua_S,"CMolPosition2d_double_","CMolPosition2d<double>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CMolPosition2d_double_");
   tolua_function(tolua_S,"new",tolua_MolServer_CMolPosition2d_double__new00);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolPosition2d_double__new00_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolPosition2d_double__new00_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolPosition2d_double__new01);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolPosition2d_double__new01_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolPosition2d_double__new01_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolPosition2d_double__new02);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolPosition2d_double__new02_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolPosition2d_double__new02_local);
   tolua_function(tolua_S,".eq",tolua_MolServer_CMolPosition2d_double___eq00);
   tolua_function(tolua_S,".sub",tolua_MolServer_CMolPosition2d_double___sub00);
   tolua_function(tolua_S,".add",tolua_MolServer_CMolPosition2d_double___add00);
   tolua_function(tolua_S,".mul",tolua_MolServer_CMolPosition2d_double___mul00);
   tolua_function(tolua_S,".add",tolua_MolServer_CMolPosition2d_double___add01);
   tolua_function(tolua_S,".sub",tolua_MolServer_CMolPosition2d_double___sub01);
   tolua_variable(tolua_S,"X",tolua_get_CMolPosition2d_double__X,tolua_set_CMolPosition2d_double__X);
   tolua_variable(tolua_S,"Y",tolua_get_CMolPosition2d_double__Y,tolua_set_CMolPosition2d_double__Y);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CMolDimension2d_int_","CMolDimension2d<int>","",tolua_collect_CMolDimension2d_int_);
  #else
  tolua_cclass(tolua_S,"CMolDimension2d_int_","CMolDimension2d<int>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CMolDimension2d_int_");
   tolua_function(tolua_S,"new",tolua_MolServer_CMolDimension2d_int__new00);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolDimension2d_int__new00_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolDimension2d_int__new00_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolDimension2d_int__new01);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolDimension2d_int__new01_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolDimension2d_int__new01_local);
   tolua_function(tolua_S,".eq",tolua_MolServer_CMolDimension2d_int___eq00);
   tolua_function(tolua_S,"set",tolua_MolServer_CMolDimension2d_int__set00);
   tolua_function(tolua_S,".div",tolua_MolServer_CMolDimension2d_int___div00);
   tolua_function(tolua_S,".mul",tolua_MolServer_CMolDimension2d_int___mul00);
   tolua_function(tolua_S,"getArea",tolua_MolServer_CMolDimension2d_int__getArea00);
   tolua_variable(tolua_S,"Width",tolua_get_CMolDimension2d_int__Width,tolua_set_CMolDimension2d_int__Width);
   tolua_variable(tolua_S,"Height",tolua_get_CMolDimension2d_int__Height,tolua_set_CMolDimension2d_int__Height);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CMolDimension2d_double_","CMolDimension2d<double>","",tolua_collect_CMolDimension2d_double_);
  #else
  tolua_cclass(tolua_S,"CMolDimension2d_double_","CMolDimension2d<double>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CMolDimension2d_double_");
   tolua_function(tolua_S,"new",tolua_MolServer_CMolDimension2d_double__new00);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolDimension2d_double__new00_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolDimension2d_double__new00_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolDimension2d_double__new01);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolDimension2d_double__new01_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolDimension2d_double__new01_local);
   tolua_function(tolua_S,".eq",tolua_MolServer_CMolDimension2d_double___eq00);
   tolua_function(tolua_S,"set",tolua_MolServer_CMolDimension2d_double__set00);
   tolua_function(tolua_S,".div",tolua_MolServer_CMolDimension2d_double___div00);
   tolua_function(tolua_S,".mul",tolua_MolServer_CMolDimension2d_double___mul00);
   tolua_function(tolua_S,"getArea",tolua_MolServer_CMolDimension2d_double__getArea00);
   tolua_variable(tolua_S,"Width",tolua_get_CMolDimension2d_double__Width,tolua_set_CMolDimension2d_double__Width);
   tolua_variable(tolua_S,"Height",tolua_get_CMolDimension2d_double__Height,tolua_set_CMolDimension2d_double__Height);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CMolRect_int_","CMolRect<int>","",tolua_collect_CMolRect_int_);
  #else
  tolua_cclass(tolua_S,"CMolRect_int_","CMolRect<int>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CMolRect_int_");
   tolua_function(tolua_S,"new",tolua_MolServer_CMolRect_int__new00);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolRect_int__new00_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolRect_int__new00_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolRect_int__new01);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolRect_int__new01_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolRect_int__new01_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolRect_int__new02);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolRect_int__new02_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolRect_int__new02_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolRect_int__new03);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolRect_int__new03_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolRect_int__new03_local);
   tolua_function(tolua_S,".add",tolua_MolServer_CMolRect_int___add00);
   tolua_function(tolua_S,".sub",tolua_MolServer_CMolRect_int___sub00);
   tolua_function(tolua_S,".eq",tolua_MolServer_CMolRect_int___eq00);
   tolua_function(tolua_S,"getArea",tolua_MolServer_CMolRect_int__getArea00);
   tolua_function(tolua_S,"isPointInside",tolua_MolServer_CMolRect_int__isPointInside00);
   tolua_function(tolua_S,"isRectCollided",tolua_MolServer_CMolRect_int__isRectCollided00);
   tolua_function(tolua_S,"clipAgainst",tolua_MolServer_CMolRect_int__clipAgainst00);
   tolua_function(tolua_S,"constrainTo",tolua_MolServer_CMolRect_int__constrainTo00);
   tolua_function(tolua_S,"getWidth",tolua_MolServer_CMolRect_int__getWidth00);
   tolua_function(tolua_S,"getHeight",tolua_MolServer_CMolRect_int__getHeight00);
   tolua_function(tolua_S,"repair",tolua_MolServer_CMolRect_int__repair00);
   tolua_function(tolua_S,"isValid",tolua_MolServer_CMolRect_int__isValid00);
   tolua_function(tolua_S,"getCenter",tolua_MolServer_CMolRect_int__getCenter00);
   tolua_function(tolua_S,"getSize",tolua_MolServer_CMolRect_int__getSize00);
   tolua_function(tolua_S,"addInternalPoint",tolua_MolServer_CMolRect_int__addInternalPoint00);
   tolua_function(tolua_S,"addInternalPoint",tolua_MolServer_CMolRect_int__addInternalPoint01);
   tolua_variable(tolua_S,"UpperLeftCorner",tolua_get_CMolRect_int__UpperLeftCorner,tolua_set_CMolRect_int__UpperLeftCorner);
   tolua_variable(tolua_S,"LowerRightCorner",tolua_get_CMolRect_int__LowerRightCorner,tolua_set_CMolRect_int__LowerRightCorner);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CMolRect_double_","CMolRect<double>","",tolua_collect_CMolRect_double_);
  #else
  tolua_cclass(tolua_S,"CMolRect_double_","CMolRect<double>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CMolRect_double_");
   tolua_function(tolua_S,"new",tolua_MolServer_CMolRect_double__new00);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolRect_double__new00_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolRect_double__new00_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolRect_double__new01);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolRect_double__new01_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolRect_double__new01_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolRect_double__new02);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolRect_double__new02_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolRect_double__new02_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolRect_double__new03);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolRect_double__new03_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolRect_double__new03_local);
   tolua_function(tolua_S,".add",tolua_MolServer_CMolRect_double___add00);
   tolua_function(tolua_S,".sub",tolua_MolServer_CMolRect_double___sub00);
   tolua_function(tolua_S,".eq",tolua_MolServer_CMolRect_double___eq00);
   tolua_function(tolua_S,"getArea",tolua_MolServer_CMolRect_double__getArea00);
   tolua_function(tolua_S,"isPointInside",tolua_MolServer_CMolRect_double__isPointInside00);
   tolua_function(tolua_S,"isRectCollided",tolua_MolServer_CMolRect_double__isRectCollided00);
   tolua_function(tolua_S,"clipAgainst",tolua_MolServer_CMolRect_double__clipAgainst00);
   tolua_function(tolua_S,"constrainTo",tolua_MolServer_CMolRect_double__constrainTo00);
   tolua_function(tolua_S,"getWidth",tolua_MolServer_CMolRect_double__getWidth00);
   tolua_function(tolua_S,"getHeight",tolua_MolServer_CMolRect_double__getHeight00);
   tolua_function(tolua_S,"repair",tolua_MolServer_CMolRect_double__repair00);
   tolua_function(tolua_S,"isValid",tolua_MolServer_CMolRect_double__isValid00);
   tolua_function(tolua_S,"getCenter",tolua_MolServer_CMolRect_double__getCenter00);
   tolua_function(tolua_S,"getSize",tolua_MolServer_CMolRect_double__getSize00);
   tolua_function(tolua_S,"addInternalPoint",tolua_MolServer_CMolRect_double__addInternalPoint00);
   tolua_function(tolua_S,"addInternalPoint",tolua_MolServer_CMolRect_double__addInternalPoint01);
   tolua_variable(tolua_S,"UpperLeftCorner",tolua_get_CMolRect_double__UpperLeftCorner,tolua_set_CMolRect_double__UpperLeftCorner);
   tolua_variable(tolua_S,"LowerRightCorner",tolua_get_CMolRect_double__LowerRightCorner,tolua_set_CMolRect_double__LowerRightCorner);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CMolString","CMolString","",tolua_collect_CMolString);
  #else
  tolua_cclass(tolua_S,"CMolString","CMolString","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CMolString");
   tolua_function(tolua_S,"new",tolua_MolServer_CMolString_new00);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolString_new00_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolString_new00_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolString_new01);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolString_new01_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolString_new01_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolString_new02);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolString_new02_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolString_new02_local);
   tolua_function(tolua_S,"c_str",tolua_MolServer_CMolString_c_str00);
   tolua_function(tolua_S,"at",tolua_MolServer_CMolString_at00);
   tolua_function(tolua_S,"clear",tolua_MolServer_CMolString_clear00);
   tolua_function(tolua_S,"empty",tolua_MolServer_CMolString_empty00);
   tolua_function(tolua_S,"length",tolua_MolServer_CMolString_length00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CMolMessageIn","CMolMessageIn","CVMemPool<CMolMessageIn>",NULL);
  tolua_beginmodule(tolua_S,"CMolMessageIn");
   tolua_function(tolua_S,"getId",tolua_MolServer_CMolMessageIn_getId00);
   tolua_function(tolua_S,"getLength",tolua_MolServer_CMolMessageIn_getLength00);
   tolua_function(tolua_S,"readByte",tolua_MolServer_CMolMessageIn_readByte00);
   tolua_function(tolua_S,"readShort",tolua_MolServer_CMolMessageIn_readShort00);
   tolua_function(tolua_S,"readLong",tolua_MolServer_CMolMessageIn_readLong00);
   tolua_function(tolua_S,"readString",tolua_MolServer_CMolMessageIn_readString00);
   tolua_function(tolua_S,"getUnreadLength",tolua_MolServer_CMolMessageIn_getUnreadLength00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CMolMessageOut","CMolMessageOut","",tolua_collect_CMolMessageOut);
  #else
  tolua_cclass(tolua_S,"CMolMessageOut","CMolMessageOut","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CMolMessageOut");
   tolua_function(tolua_S,"new",tolua_MolServer_CMolMessageOut_new00);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolMessageOut_new00_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolMessageOut_new00_local);
   tolua_function(tolua_S,"new",tolua_MolServer_CMolMessageOut_new01);
   tolua_function(tolua_S,"new_local",tolua_MolServer_CMolMessageOut_new01_local);
   tolua_function(tolua_S,".call",tolua_MolServer_CMolMessageOut_new01_local);
   tolua_function(tolua_S,"delete",tolua_MolServer_CMolMessageOut_delete00);
   tolua_function(tolua_S,"clear",tolua_MolServer_CMolMessageOut_clear00);
   tolua_function(tolua_S,"writeByte",tolua_MolServer_CMolMessageOut_writeByte00);
   tolua_function(tolua_S,"writeShort",tolua_MolServer_CMolMessageOut_writeShort00);
   tolua_function(tolua_S,"writeLong",tolua_MolServer_CMolMessageOut_writeLong00);
   tolua_function(tolua_S,"writeString",tolua_MolServer_CMolMessageOut_writeString00);
   tolua_function(tolua_S,"getData",tolua_MolServer_CMolMessageOut_getData00);
   tolua_function(tolua_S,"getLength",tolua_MolServer_CMolMessageOut_getLength00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"PLAYERSTATE_NORAML",PLAYERSTATE_NORAML);
  tolua_constant(tolua_S,"PLAYERSTATE_QUEUE",PLAYERSTATE_QUEUE);
  tolua_constant(tolua_S,"PLAYERSTATE_READY",PLAYERSTATE_READY);
  tolua_constant(tolua_S,"PLAYERSTATE_GAMING",PLAYERSTATE_GAMING);
  tolua_constant(tolua_S,"PLAYERSTATE_LOSTLINE",PLAYERSTATE_LOSTLINE);
  tolua_constant(tolua_S,"PLAYERTYPE_NORMAL",PLAYERTYPE_NORMAL);
  tolua_constant(tolua_S,"PLAYERTYPE_ROBOT",PLAYERTYPE_ROBOT);
  tolua_cclass(tolua_S,"Player","Player","",NULL);
  tolua_beginmodule(tolua_S,"Player");
   tolua_function(tolua_S,"SetID",tolua_MolServer_Player_SetID00);
   tolua_function(tolua_S,"GetID",tolua_MolServer_Player_GetID00);
   tolua_function(tolua_S,"SetConnectID",tolua_MolServer_Player_SetConnectID00);
   tolua_function(tolua_S,"GetConnectID",tolua_MolServer_Player_GetConnectID00);
   tolua_function(tolua_S,"SetRoomId",tolua_MolServer_Player_SetRoomId00);
   tolua_function(tolua_S,"GetRoomId",tolua_MolServer_Player_GetRoomId00);
   tolua_function(tolua_S,"SetType",tolua_MolServer_Player_SetType00);
   tolua_function(tolua_S,"GetType",tolua_MolServer_Player_GetType00);
   tolua_function(tolua_S,"SetRoomIndex",tolua_MolServer_Player_SetRoomIndex00);
   tolua_function(tolua_S,"GetRoomIndex",tolua_MolServer_Player_GetRoomIndex00);
   tolua_function(tolua_S,"SetHeartCount",tolua_MolServer_Player_SetHeartCount00);
   tolua_function(tolua_S,"GetHeartCount",tolua_MolServer_Player_GetHeartCount00);
   tolua_function(tolua_S,"SetName",tolua_MolServer_Player_SetName00);
   tolua_function(tolua_S,"GetName",tolua_MolServer_Player_GetName00);
   tolua_function(tolua_S,"GetState",tolua_MolServer_Player_GetState00);
   tolua_function(tolua_S,"SetState",tolua_MolServer_Player_SetState00);
   tolua_function(tolua_S,"SetLookOn",tolua_MolServer_Player_SetLookOn00);
   tolua_function(tolua_S,"IsLookOn",tolua_MolServer_Player_IsLookOn00);
   tolua_function(tolua_S,"SetMoney",tolua_MolServer_Player_SetMoney00);
   tolua_function(tolua_S,"GetMoney",tolua_MolServer_Player_GetMoney00);
   tolua_function(tolua_S,"SetLevel",tolua_MolServer_Player_SetLevel00);
   tolua_function(tolua_S,"GetLevel",tolua_MolServer_Player_GetLevel00);
   tolua_function(tolua_S,"SetExperience",tolua_MolServer_Player_SetExperience00);
   tolua_function(tolua_S,"GetExperience",tolua_MolServer_Player_GetExperience00);
   tolua_function(tolua_S,"SetUserAvatar",tolua_MolServer_Player_SetUserAvatar00);
   tolua_function(tolua_S,"GetUserAvatar",tolua_MolServer_Player_GetUserAvatar00);
   tolua_function(tolua_S,"SetTotalBureau",tolua_MolServer_Player_SetTotalBureau00);
   tolua_function(tolua_S,"GetTotalBureau",tolua_MolServer_Player_GetTotalBureau00);
   tolua_function(tolua_S,"SetSuccessBureau",tolua_MolServer_Player_SetSuccessBureau00);
   tolua_function(tolua_S,"GetSuccessBureau",tolua_MolServer_Player_GetSuccessBureau00);
   tolua_function(tolua_S,"SetFailBureau",tolua_MolServer_Player_SetFailBureau00);
   tolua_function(tolua_S,"GetFailBureau",tolua_MolServer_Player_GetFailBureau00);
   tolua_function(tolua_S,"SetSuccessRate",tolua_MolServer_Player_SetSuccessRate00);
   tolua_function(tolua_S,"GetSuccessRate",tolua_MolServer_Player_GetSuccessRate00);
   tolua_function(tolua_S,"SetRunawayrate",tolua_MolServer_Player_SetRunawayrate00);
   tolua_function(tolua_S,"GetRunawayrate",tolua_MolServer_Player_GetRunawayrate00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"ROOMTYPE_JINBIN",ROOMTYPE_JINBIN);
  tolua_constant(tolua_S,"ROOMTYPE_JIFEN",ROOMTYPE_JIFEN);
  tolua_constant(tolua_S,"ROOMTYPE_BISAI",ROOMTYPE_BISAI);
  tolua_constant(tolua_S,"ROOMTYPE_LIANXI",ROOMTYPE_LIANXI);
  tolua_constant(tolua_S,"ROOMTYPE_NULL",ROOMTYPE_NULL);
  tolua_constant(tolua_S,"ROOMSTATE_WAITING",ROOMSTATE_WAITING);
  tolua_constant(tolua_S,"ROOMSTATE_GAMING",ROOMSTATE_GAMING);
  tolua_constant(tolua_S,"ROOMSTATE_NULL",ROOMSTATE_NULL);
  tolua_cclass(tolua_S,"Room","Room","",NULL);
  tolua_beginmodule(tolua_S,"Room");
   tolua_function(tolua_S,"SetID",tolua_MolServer_Room_SetID00);
   tolua_function(tolua_S,"GetID",tolua_MolServer_Room_GetID00);
   tolua_function(tolua_S,"SetRoomType",tolua_MolServer_Room_SetRoomType00);
   tolua_function(tolua_S,"GetRoomType",tolua_MolServer_Room_GetRoomType00);
   tolua_function(tolua_S,"SetMaxPlayer",tolua_MolServer_Room_SetMaxPlayer00);
   tolua_function(tolua_S,"GetMaxPlayer",tolua_MolServer_Room_GetMaxPlayer00);
   tolua_function(tolua_S,"SetRoomState",tolua_MolServer_Room_SetRoomState00);
   tolua_function(tolua_S,"GetRoomState",tolua_MolServer_Room_GetRoomState00);
   tolua_function(tolua_S,"SetName",tolua_MolServer_Room_SetName00);
   tolua_function(tolua_S,"GetName",tolua_MolServer_Room_GetName00);
   tolua_function(tolua_S,"SetChouShui",tolua_MolServer_Room_SetChouShui00);
   tolua_function(tolua_S,"GetChouShui",tolua_MolServer_Room_GetChouShui00);
   tolua_function(tolua_S,"SetLastMoney",tolua_MolServer_Room_SetLastMoney00);
   tolua_function(tolua_S,"GetLastMoney",tolua_MolServer_Room_GetLastMoney00);
   tolua_function(tolua_S,"IsEmpty",tolua_MolServer_Room_IsEmpty00);
   tolua_function(tolua_S,"GetPlayer",tolua_MolServer_Room_GetPlayer00);
   tolua_function(tolua_S,"GetPlayerCount",tolua_MolServer_Room_GetPlayerCount00);
   tolua_function(tolua_S,"GetReadyPlayerCount",tolua_MolServer_Room_GetReadyPlayerCount00);
   tolua_function(tolua_S,"SetMaster",tolua_MolServer_Room_SetMaster00);
   tolua_function(tolua_S,"GetMaster",tolua_MolServer_Room_GetMaster00);
   tolua_function(tolua_S,"GetCurrentPlayer",tolua_MolServer_Room_GetCurrentPlayer00);
   tolua_function(tolua_S,"GetPlayerRoomId",tolua_MolServer_Room_GetPlayerRoomId00);
   tolua_function(tolua_S,"GetPlayerCount",tolua_MolServer_Room_GetPlayerCount01);
   tolua_function(tolua_S,"SetAllPlayerState",tolua_MolServer_Room_SetAllPlayerState00);
   tolua_function(tolua_S,"SetPlayerState",tolua_MolServer_Room_SetPlayerState00);
   tolua_function(tolua_S,"SetCurrentPlayer",tolua_MolServer_Room_SetCurrentPlayer00);
   tolua_function(tolua_S,"GetCurNextPlayer",tolua_MolServer_Room_GetCurNextPlayer00);
   tolua_function(tolua_S,"GetCurNextWorkPlayer",tolua_MolServer_Room_GetCurNextWorkPlayer00);
   tolua_function(tolua_S,"ClearAllPlayers",tolua_MolServer_Room_ClearAllPlayers00);
   tolua_function(tolua_S,"AddPlayer",tolua_MolServer_Room_AddPlayer00);
   tolua_function(tolua_S,"AddLookOnPlayer",tolua_MolServer_Room_AddLookOnPlayer00);
   tolua_function(tolua_S,"ClearPlayer",tolua_MolServer_Room_ClearPlayer00);
   tolua_function(tolua_S,"DeletePlayer",tolua_MolServer_Room_DeletePlayer00);
   tolua_function(tolua_S,"ClearPlayerById",tolua_MolServer_Room_ClearPlayerById00);
   tolua_function(tolua_S,"IsExist",tolua_MolServer_Room_IsExist00);
   tolua_function(tolua_S,"IsExistLookOn",tolua_MolServer_Room_IsExistLookOn00);
   tolua_function(tolua_S,"IsFull",tolua_MolServer_Room_IsFull00);
   tolua_function(tolua_S,"IsReadyed",tolua_MolServer_Room_IsReadyed00);
   tolua_function(tolua_S,"GetPlayerIndex",tolua_MolServer_Room_GetPlayerIndex00);
   tolua_function(tolua_S,"GetLostPlayerCount",tolua_MolServer_Room_GetLostPlayerCount00);
   tolua_function(tolua_S,"Clear",tolua_MolServer_Room_Clear00);
   tolua_function(tolua_S,"UpdateUserScore",tolua_MolServer_Room_UpdateUserScore00);
   tolua_function(tolua_S,"GameEnd",tolua_MolServer_Room_GameEnd00);
   tolua_function(tolua_S,"GameStart",tolua_MolServer_Room_GameStart00);
   tolua_function(tolua_S,"SendTableMsg",tolua_MolServer_Room_SendTableMsg00);
   tolua_function(tolua_S,"SendLookOnMes",tolua_MolServer_Room_SendLookOnMes00);
   tolua_function(tolua_S,"SendAllPlayerMsg",tolua_MolServer_Room_SendAllPlayerMsg00);
   tolua_function(tolua_S,"PrintDebugInfo",tolua_MolServer_Room_PrintDebugInfo00);
   tolua_function(tolua_S,"StartTimer",tolua_MolServer_Room_StartTimer00);
   tolua_function(tolua_S,"StopTimer",tolua_MolServer_Room_StopTimer00);
   tolua_function(tolua_S,"StopAllTimer",tolua_MolServer_Room_StopAllTimer00);
  tolua_endmodule(tolua_S);

  { /* begin embedded lua code */
   int top = lua_gettop(tolua_S);
   static const unsigned char B[] = {
    10,116,111, 72,101,108,112,101,114, 61,123,125, 10,102,117,
    110, 99,116,105,111,110, 32,116,111, 72,101,108,112,101,114,
     46,116,111, 80,108, 97,121,101,114, 40,101, 41, 10,114,101,
    116,117,114,110, 32,116,111,108,117, 97, 46, 99, 97,115,116,
     40,101, 44, 32, 34, 80,108, 97,121,101,114, 34, 41, 10,101,
    110,100, 10,102,117,110, 99,116,105,111,110, 32,116,111, 72,
    101,108,112,101,114, 46,116,111, 82,111,111,109, 40,101, 41,
     10,114,101,116,117,114,110, 32,116,111,108,117, 97, 46, 99,
     97,115,116, 40,101, 44, 32, 34, 82,111,111,109, 34, 41, 10,
    101,110,100, 10,102,117,110, 99,116,105,111,110, 32,116,111,
     72,101,108,112,101,114, 46,116,111, 77,101,115,115, 97,103,
    101, 73,110, 40,101, 41, 10,114,101,116,117,114,110, 32,116,
    111,108,117, 97, 46, 99, 97,115,116, 40,101, 44, 32, 34, 67,
     77,111,108, 77,101,115,115, 97,103,101, 73,110, 34, 41, 10,
    101,110,100, 10,102,117,110, 99,116,105,111,110, 32,116,111,
     72,101,108,112,101,114, 46,116,111, 77,101,115,115, 97,103,
    101, 79,117,116, 40,101, 41, 10,114,101,116,117,114,110, 32,
    116,111,108,117, 97, 46, 99, 97,115,116, 40,101, 44, 32, 34,
     67, 77,111,108, 77,101,115,115, 97,103,101, 79,117,116, 34,
     41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
    116,111, 72,101,108,112,101,114, 46,116,111, 77,111,108, 83,
    116,114,105,110,103, 40,101, 41, 10,114,101,116,117,114,110,
     32,116,111,108,117, 97, 46, 99, 97,115,116, 40,101, 44, 32,
     34, 67, 77,111,108, 83,116,114,105,110,103, 34, 41, 10,101,
    110,100, 32, 45, 45, 45, 45, 45,32
   };
   tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 1");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */

 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_MolServer (lua_State* tolua_S) {
 return tolua_MolServer_open(tolua_S);
};
#endif

