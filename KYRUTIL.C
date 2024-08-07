/*****************************************************************************
 *                                                                           *
 *   KYRANDIA, Fantasy-world of Legends                     Version 7.20     *
 *                                                                           *
 *   KYRUTIL.C (KUTILS.C) - General low-level multi-player game utilities    *
 *                                                                           *
 *   Designed/Programmed by: Scott Brinker & Richard Skurnick   03/18/88     *
 *                                    6.00 Converstion - E. Bush 3/12/92     *
 *                 (v7.1) Worldgroup 3.2 Conversion - R. Hadsall 4/24/2021   *
 *                   (v7.2) Major BBS 10 Conversion - R. Hadsall 4/18/2023   *
 *                                                                           *
 * Copyright (C) 1988-2024 Rick Hadsall.  All Rights Reserved.               *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU Affero General Public License as published  *
 * by the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.     *
 *                                                                           *
 * Additional Terms for Contributors:                                        *
 * 1. By contributing to this project, you agree to assign all right, title, *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies.                              *
 * 2. You grant Rick Hadsall and Elwynor Technologies a non-exclusive,       *
 *    royalty-free, worldwide license to use, reproduce, prepare derivative  *
 *    works of, publicly display, publicly perform, sublicense, and          *
 *    distribute your contributions                                          *
 * 3. You represent that you have the legal right to make your contributions *
 *    and that the contributions do not infringe any third-party rights.     *
 * 4. Rick Hadsall and Elwynor Technologies are not obligated to incorporate *
 *    any contributions into the project.                                    *
 * 5. This project is licensed under the AGPL v3, and any derivative works   *
 *    must also be licensed under the AGPL v3.                               *
 * 6. If you create an entirely new project (a fork) based on this work, it  *
 *    must also be licensed under the AGPL v3, you assign all right, title,  *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies, and you must include these   *
 *    additional terms in your project's LICENSE file(s).                    *
 *                                                                           *
 * By contributing to this project, you agree to these terms.                *
 *                                                                           *
 *****************************************************************************/

#include "gcomm.h"
#include "majorbbs.h"
#include "kyrandia.h"
#include "elwkyrm.h"

static struct utlgmp {        /* utility game-player structure             */
     CHAR uidnam[APNSIZ];     /* player's name                             */
     INT cinflg;              /* is player invisible? marker               */
} *ugparr;                    /* array declaration                         */

static INT ugasiz;            /* size of ugparr arry                       */

VOID
iniutl(VOID)                       /* initialize utility routines array    */
{
     ugparr=(struct utlgmp *)alczer(ugasiz=nterms*sizeof(struct utlgmp));
}

CHAR *
himher(                            /* display "him/her" for filling a %s   */
struct gmplyr *gp)
{
     return((gp->charms[ALTNAM]) ? "its" : ((gp->flags&FEMALE) ? "her" : "him"));
}

CHAR *
kheshe(                            /* display "he/she" for filling a %s    */
struct gmplyr *gp)
{
     return((gp->charms[ALTNAM]) ? "its" : ((gp->flags&FEMALE) ? "she" : "he"));
}

CHAR *
hisher(                            /* display "his/her" for filling a %s   */
struct gmplyr *gp)
{
     return((gp->charms[ALTNAM]) ? "its" : ((gp->flags&FEMALE) ? "her" : "his"));
}

GBOOL
ckinvs(                            /* check to see if someone is invisible */
struct gmplyr *gp)
{
     if (!(gp->flags&INVISF) || (gmpptr->charms[CINVIS])) {
          return(TRUE);
     }
     return(FALSE);
}

VOID
sndoth(VOID)                       /* sen message to others in your room   */
{
     INT i;
     INT loc;
     struct gmplyr *utlgp;

     loc=gmpptr->gamloc;
     if (loc != -1) {
          for (utlgp=gmparr,i=0 ; i < nterms ; utlgp++,i++) {
               if (i != usrnum && utlgp->gamloc == loc) {
                    outprf(i);
               }
          }
     }
     clrprf();
}

VOID
sndutl(                            /* send a his/her message to others     */
const char *stg)
{
    char* his_her_string = hisher(gmpptr);

#ifdef __BUILDV10MODULE
    // for The Major BBS V10+ (Visual Studio 2022) and the updated spr(const char *,...)
    char* gendered_message = spr(stg, his_her_string);
#else
    // for Worldgroup 3.2 (Borland C/C++ 5.0) and the old spr(char *,...)
    char* gendered_message = spr((CHAR*)stg, his_her_string);
#endif

    prf("***\r%s is %s\r", gmpptr->altnam, gendered_message);

    //prf("***\r%s is %s\r",gmpptr->altnam,spr(stg,hisher(gmpptr)));
    
    sndoth();
}

VOID
sndbt2(VOID)                       /* send a message to a room to all but  */
{
     INT i;
     INT loc;
     struct gmplyr *utlgp;

     loc=gmpptr->gamloc;
     if (loc != -1) {
          for (utlgp=gmparr,i=0 ; i < nterms ; utlgp++,i++) {
               if (i != usrnum && i != othusn && utlgp->gamloc == loc) {
                    outprf(i);
               }
          }
     }
     clrprf();
}

VOID
sndcgp(                            /* send a message to visible people     */
struct gmplyr *gp)
{
     INT i,loc;
     struct gmplyr *utlgp;

     loc=gp->gamloc;
     if (loc != -1) {
          for (utlgp=gmparr,i=0 ; i < nterms ; utlgp++,i++) {
               if (utlgp->gamloc == loc && utlgp != gp) {
                    if (!(gp->flags&INVISF) || (utlgp->charms[CINVIS])) {
                         outprf(i);
                   }
               }
          }
     }
     clrprf();
}

VOID
sndloc(                            /* send a message to specified room     */
INT loc)
{
     INT i;
     struct gmplyr *utlgp;

     for (utlgp=gmparr,i=0 ; i < nterms ; utlgp++,i++) {
          if (utlgp->gamloc == loc) {
               outprf(i);
          }
     }
     clrprf();
}

VOID
sndnear(VOID)                      /* send message to closely located rooms*/
{
     if (gmlptr->gi_north != -1 && gmlptr->gi_north != gmpptr->gamloc) {
          sndloc(gmlptr->gi_north);
     }
     if (gmlptr->gi_south != -1 && gmlptr->gi_south != gmpptr->gamloc) {
          sndloc(gmlptr->gi_south);
     }
     if (gmlptr->gi_east != -1 && gmlptr->gi_east != gmpptr->gamloc) {
          sndloc(gmlptr->gi_east);
     }
     if (gmlptr->gi_west != -1 && gmlptr->gi_west != gmpptr->gamloc) {
          sndloc(gmlptr->gi_west);
     }
     clrprf();
}

VOID
sndgam(VOID)                       /* send message to everyone in the game */
{
     INT i;
     struct gmplyr *utlgp;

     for (utlgp=gmparr,i=0 ; i < nterms ; utlgp++,i++) {
          if (utlgp->gamloc != -1) {
               outprf(i);
          }
     }
     clrprf();
}

VOID
remvgp(                            /* remove a user from the game          */
struct gmplyr *gp,
CHAR *rmvtxt)
{
     prf("***\r%s has just %s!\r",gp->altnam,rmvtxt);
     sndcgp(gp);
     gp->pgploc=gp->gamloc;
     gp->gamloc=-1;
}

VOID
entrgp(                            /* place a user into the game           */
INT loc,
struct gmplyr *gp,
CHAR *enttxt)
{
     if (loc < 0) {
          loc=0;
     }
     gp->gamloc=gp->pgploc=(SHORT)loc;
     if (gp->flags&BRFSTF) {
          prf("...You're %s.\r",gmlocs[loc].brfdes);
     }
     else {
          setmbk(klmb);
          prfmsg(lcrous[loc].londes);
          setmbk(kmb);
     }
     locobjs(loc);
     locogps(gp);
     outprf(gp->modno);
     prf("***\r%s has just %s!\r",gp->altnam,enttxt);
     sndcgp(gp);
}

VOID
locobjs(                           /* describe objects in a room           */
INT locno)
{
     INT i;
     INT ntobjs;
     INT ncobjs;
     CHAR *olctxt;
     struct gamloc *objloc;
     struct gamobj **lcobjs;
     struct gamobj *vsobjs[MXLOBS];

     memset(vsobjs, 0, sizeof(vsobjs));

     objloc=&gmlocs[locno];
     olctxt=objloc->objlds;
     lcobjs=objloc->lcobjs;
     ntobjs=objloc->nlobjs;
     for (i=0,ncobjs=0 ; i < ntobjs ; i++) {
          if (lcobjs[i]->flags&VISIBL) {
               vsobjs[ncobjs]=lcobjs[i];
               ncobjs++;
          }
     }
     setmbk(kmb);
     switch (ncobjs) {
     case 0:
          prfmsg(KUTM00,olctxt);
          break;
     case 1:
          prfmsg(KUTM01,dobutl(vsobjs[0]),olctxt);
          break;
     case 2:
          prfmsg(KUTM02,dobutl(vsobjs[0]),dobutl(vsobjs[1]),olctxt);
          break;
     default:
          prfmsg(KUTM03);
          for (i=0 ; i < ncobjs-1 ; i++) {
               prf("%s, ",dobutl(vsobjs[i]));
          }
          prfmsg(KUTM04,dobutl(vsobjs[i]),olctxt);
     }
     if (dloc == locno) {
          prfmsg(KUTM05);
     }
     if (zloc == locno) {
          prfmsg(KUTM06);
     }
}

VOID
gi_invrou(VOID)                    /* main inventory handler               */
{
     prf("...You have ");
     gi_invutl(gmpptr,1);
     outprf(usrnum);
     if (gmpptr->gamloc != -1) {
          prf("***\r%s is taking inventory.\r",gmpptr->altnam);
          sndoth();
     }
}

VOID
gi_invutl(                         /* display objects in user's inventory  */
struct gmplyr *gp,
INT you)
{
     INT i;
     INT nobjs=0;
     struct gamobj **gpobjs;

     (VOID)nobjs;
     gpobjs=gp->gpobjs;
     switch (nobjs=gp->npobjs) {
     case 0:
          break;
     case 1:
          prf("%s, ",dobutl(gpobjs[0]));
          break;
     case 2:
          prf("%s, %s, ",dobutl(gpobjs[0]),dobutl(gpobjs[1]));
          break;
     default:
          for (i=0 ; i < nobjs ; i++) {
               prf("%s, ",dobutl(gpobjs[i]));
          }
     }
     if (you) {
          prfmsg(KUTM07,gmpptr->gold,(gmpptr->gold == 1 ? "" : "s"));
     }
     else {
          if (gp->npobjs) {
               prfmsg(KUTM08);
          }
          prfmsg(KUTM09,hisher(gp));
     }
}

CHAR *
dobutl(                            /* place an "a" or "an" in front of obj */
struct gamobj *object)
{
     static CHAR retval[4][40];
     static INT cycle=0;

     cycle=((cycle+1)&3);
     if (object->flags&NEEDAN) {
          strcpy(retval[cycle],"an ");
     }
     else {
          strcpy(retval[cycle],"a ");
     }
     strcat(retval[cycle],object->name);
     return(retval[cycle]);
}

VOID
locogps(                           /* describe players in current room     */
struct gmplyr *gp)
{
     INT i,ncngps;
     struct gmplyr *locogp;

     setmem(ugparr,ugasiz,0);
     for (i=0,ncngps=0 ; i < nterms ; i++) {
          locogp=&gmparr[i];
          if (locogp->gamloc == gp->gamloc && locogp != gp) {
               if (locogp->flags&INVISF) {
                    if (gmpptr->charms[CINVIS]) {
                         strcpy(ugparr[ncngps].uidnam,locogp->plyrid);
                         ugparr[ncngps].cinflg=1;
                         ncngps++;
                    }
               }
               else {
                    strcpy(ugparr[ncngps].uidnam,locogp->altnam);
                    ncngps++;
               }
          }
     }
     switch (ncngps) {
     case 0:
          break;
     case 1:
          prf("%s",ugparr[0].uidnam);
          if (ugparr[0].cinflg) {
               prfmsg(KUTM10);
          }
          prfmsg(KUTM11);
          break;
     case 2:
          prf("%s",ugparr[0].uidnam);
          if (ugparr[0].cinflg) {
               prfmsg(KUTM10);
          }
          prf(" and %s",ugparr[1].uidnam);
          if (ugparr[1].cinflg) {
               prfmsg(KUTM10);
          }
          prfmsg(KUTM12);
          break;
     default:
          for (i=0 ; i < ncngps-1 ; i++) {
               prf("%s",ugparr[i].uidnam);
               if (ugparr[i].cinflg) {
                    prfmsg(KUTM10);
               }
               prf(", ");
          }
          prf("and %s",ugparr[i].uidnam);
          if (ugparr[i].cinflg) {
               prfmsg(KUTM10);
          }
          prfmsg(KUTM12);
     }
}

INT
ngpscn(                            /* count users in room with specific usr*/
struct gmplyr *gp)
{
     INT i;
     INT retval=0;
     struct gmplyr *ogp;

     for (i=0 ; i < nterms ; i++) {
          ogp=&gmparr[i];
          if (ogp->gamloc == gp->gamloc && ogp != gp) {
               if (!(gp->flags&INVISF) || (ogp->charms[CINVIS])) {
                    retval++;
               }
          }
     }
     return(retval);
}

INT
ngpslc(                            /* count users in a specified location  */
INT locno)
{
     INT i;
     INT retval=0;

     for (i=0 ; i < nterms ; i++) {
          if (gmparr[i].gamloc == locno) {
               retval++;
          }
     }
     return(retval);
}

GBOOL
findgp(                            /* check room for a given player        */
CHAR *stg)
{
     for (ogmptr=gmparr,othusn=0 ; othusn < nterms ; ogmptr++,othusn++) {
          if (ogmptr->gamloc == gmpptr->gamloc) {
               if (sameto(stg,ogmptr->attnam) && ckinvs(ogmptr)) {
                    return(TRUE);
               }
          }
     }
     return(FALSE);
}

GBOOL
fgamgp(                            /* check game for a specified player    */
CHAR *stg)
{
     for (ogmptr=gmparr,othusn=0 ; othusn < nterms ; ogmptr++,othusn++) {
          if (ogmptr->gamloc != -1 && sameas(stg,ogmptr->plyrid)) {
               return(1);
          }
     }
     return(0);
}

GBOOL
chkobj(                            /* check player for a specified object  */
struct gamobj *obj)
{
     for (objno=0 ; objno < ogmptr->npobjs ; objno++) {
          if (ogmptr->gpobjs[objno] == obj) {
               return(TRUE);
          }
     }
     return(FALSE);
}

struct gamobj *
fndpobj(                           /* check user for specified object name*/
struct gmplyr *gp,
CHAR *stg)
{
     for (objno=0 ; objno < gp->npobjs ; objno++) {
          if (sameto(stg,gp->gpobjs[objno]->name)) {
               return(gp->gpobjs[objno]);
          }
     }
     return(NULL);
}

struct gamobj *
fgmpobj(                           /* check current user for specified obj */
CHAR *stg)
{
     return(fndpobj(gmpptr,stg));
}

struct gamobj *
fndlobj(                           /* check a location for an object       */
struct gamloc *loc,
CHAR *stg)
{
     for (objno=0 ; objno < loc->nlobjs ; objno++) {
          if (sameto(stg,loc->lcobjs[objno]->name)) {
               return(loc->lcobjs[objno]);
          }
     }
     return(NULL);
}

struct gamobj *
fgmlobj(                           /* check current user loc for an object */
CHAR *stg)
{
     return(fndlobj(gmlptr,stg));
}

VOID
takpobj(                           /* take an object from a player         */
struct gmplyr *gp,
INT objino)
{
     if (--(gp->npobjs) != objino) {
          gp->gpobjs[objino]=gp->gpobjs[gp->npobjs];
          gp->obvals[objino]=gp->obvals[gp->npobjs];
     }
}

VOID
tgmpobj(                           /* take an object from current player   */
INT objino)
{
     takpobj(gmpptr,objino);
}

VOID
taklobj(                           /* take an object from a location       */
struct gamloc *loc,
INT objino)
{
     loc->nlobjs--;
     if (loc->nlobjs != objino) {
          loc->lcobjs[objino]=loc->lcobjs[loc->nlobjs];
     }
}

VOID
tgmlobj(                           /* take an object from current usr loc  */
INT objino)
{
     taklobj(gmlptr,objino);
}

VOID
putpobj(                           /* give a player an object              */
struct gmplyr *gp,
struct gamobj *obj,
INT value)
{
     gp->obvals[gp->npobjs]=(SHORT)value;
     gp->gpobjs[(gp->npobjs)++]=obj;
}

VOID
pgmpobj(                           /* give current player an object        */
struct gamobj *obj,
INT value)
{
     putpobj(gmpptr,obj,value);
}

VOID
putlobj(                           /* put an object in a location          */
struct gamloc *loc,
struct gamobj *obj)
{
     loc->lcobjs[(loc->nlobjs)++]=obj;
}

VOID
pgmlobj(                           /* put an object in current players loc */
struct gamobj *obj)
{
     putlobj(gmlptr,obj);
}

CHAR *
upperc(                            /* capitalize 1st letter-lower case rest*/
CHAR *stg)
{
     CHAR *tmp;
     static CHAR retstg[40];

     retstg[0]=(CHAR)toupper(*stg);
     for (tmp=retstg+1 ; *++stg != '\0' ; ) {
          *tmp++=(CHAR)tolower(*stg);
     }
     *tmp='\0';
     return(retstg);
}

struct binwrd *
binchk(                            /* check command array for a word       */
CHAR *stgptr,
struct binwrd table[],
INT length)
{
     INT cond;
     struct binwrd *low;
     struct binwrd *mid;
     struct binwrd *high;

     low=&table[0];
     high=&table[length-1];
     while (low <= high) {
          mid=low+((INT)(high-low))/2;
          if ((cond=strcmp(stgptr,mid->word)) < 0) {
               if (mid == low) {
                    break;
               }
               high=mid-1;
          }
          else if (cond > 0) {
               if (mid == high) {
                    break;
               }
               low=mid+1;
          }
          else {
               return(mid);
          }
     }
     return(NULL);
}
