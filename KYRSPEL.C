/*****************************************************************************
 *                                                                           *
 *   KYRANDIA, Fantasy-world of Legends                     Version 7.20     *
 *                                                                           *
 *   KYRSPEL.C (KSPELLS.C) - Magic utils, spell routines, and spell timers   *
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
#include "kyrspls.h"

static GBOOL chkstf(VOID);
static VOID chgbod(CHAR *,CHAR *,LONG,INT);
static VOID striker(INT,INT,INT,INT);
static VOID msgutl3(INT,INT,INT);
static VOID masshitr(INT,INT,INT,INT,INT,INT,INT);
static VOID spl001(VOID);
static VOID spl002(VOID);
static VOID spl003(VOID);
static VOID spl004(VOID);
static VOID spl005(VOID);
static VOID spl006(VOID);
static VOID spl007(VOID);
static VOID spl008(VOID);
static VOID spl009(VOID);
static VOID spl010(VOID);
static VOID spl011(VOID);
static VOID spl012(VOID);
static VOID spl013(VOID);
static VOID spl014(VOID);
static VOID spl015(VOID);
static VOID spl016(VOID);
static VOID spl017(VOID);
static VOID spl018(VOID);
static VOID spl019(VOID);
static VOID spl020(VOID);
static VOID spl021(VOID);
static VOID spl022(VOID);
static VOID spl023(VOID);
static VOID spl024(VOID);
static VOID spl025(VOID);
static VOID spl026(VOID);
static VOID spl027(VOID);
static VOID spl028(VOID);
static VOID spl029(VOID);
static VOID spl030(VOID);
static VOID spl031(VOID);
static VOID spl032(VOID);
static VOID spl033(VOID);
static VOID spl034(VOID);
static VOID spl035(VOID);
static VOID spl036(VOID);
static VOID spl037(VOID);
static VOID spl038(VOID);
static VOID spl039(VOID);
static VOID spl040(VOID);
static VOID spl041(VOID);
static VOID spl042(VOID);
static VOID spl043(VOID);
static VOID spl044(VOID);
static VOID spl045(VOID);
static VOID spl046(VOID);
static VOID spl047(VOID);
static VOID spl048(VOID);
static VOID spl049(VOID);
static VOID spl050(VOID);
static VOID spl051(VOID);
static VOID spl052(VOID);
static VOID spl053(VOID);
static VOID spl054(VOID);
static VOID spl055(VOID);
static VOID spl056(VOID);
static VOID spl057(VOID);
static VOID spl058(VOID);
static VOID spl059(VOID);
static VOID spl060(VOID);
static VOID spl061(VOID);
static VOID spl062(VOID);
static VOID spl063(VOID);
static VOID spl064(VOID);
static VOID spl065(VOID);
static VOID spl066(VOID);
static VOID spl067(VOID);
static struct spell *fsbspl(CHAR *,struct spell [],INT);
static VOID fnkysnd(VOID);
static struct spell *splchk(CHAR *);
static VOID rmvspl(struct gmplyr *,INT);
static VOID addspl(struct gmplyr *,struct spell *);
static VOID shwsutl(struct gmplyr *);
static VOID memutl(struct spell *);
static VOID sndnoth(INT);

struct spell spells[NGSPLS]={
     {"abbracada",   spl001,2,SBD001,10},    /* other pro II(scry,tel,etc) */
     {"allbettoo",   spl002,2,SBD002,17},    /* ultimate heal              */
     {"blowitawa",   spl003,3,SBD003,5},     /* destroy one item           */
     {"blowoutma",   spl004,3,SBD004,12},    /* destroy all items          */
     {"bookworm",    spl005,3,SBD005,21},    /* zap other's spell book     */
     {"burnup",      spl006,1,SBD006,6},     /* fireball I                 */
     {"cadabra",     spl007,2,SBD007,4},     /* see invisibility I         */
     {"cantcmeha",   spl008,2,SBD008,7},     /* invisibility I             */
     {"canthur",     spl009,2,SBD009,16},    /* ultimate protection I      */
     {"chillou",     spl010,1,SBD010,20},    /* ice storm II               */
     {"clutzopho",   spl011,3,SBD011,5},     /* make player drop all items */
     {"cuseme",      spl012,3,SBD012,3},     /* detect power (spell pts)   */
     {"dumdum",      spl013,3,SBD013,17},    /* forget all spells          */
     {"feeluck",     spl014,3,SBD014,10},    /* teleport random            */
     {"firstai",     spl015,2,SBD015,10},    /* heal III                   */
     {"flyaway",     spl016,3,SBD016,10},    /* transform into pegasus     */
     {"fpandl",      spl017,1,SBD017,2},     /* firebolt I                 */
     {"freezuu",     spl018,1,SBD018,14},    /* ice ball II                */
     {"frostie",     spl019,1,SBD019,8},     /* cone of cold II            */
     {"frozenu",     spl020,1,SBD020,7},     /* ice ball I                 */
     {"frythes",     spl021,1,SBD021,13},    /* firebolt III               */
     {"gotcha",      spl022,1,SBD022,9},     /* lightning bolt II          */
     {"goto",        spl023,3,SBD023,13},    /* teleport specific          */
     {"gringri",     spl024,3,SBD024,12},    /* transform into psuedo drag */
     {"handsof",     spl025,2,SBD025,3},     /* object protection I        */
     {"heater",      spl026,2,SBD026,7},     /* ice protection II          */
     {"hehhehh",     spl027,1,SBD027,22},    /* lightning storm            */
     {"hocus",       spl028,3,SBD028,18},    /* dispel magic               */
     {"holyshe",     spl029,1,SBD029,14},    /* lightning bolt III         */
     {"hotflas",     spl030,1,SBD030,8},     /* lightning ball             */
     {"hotfoot",     spl031,1,SBD031,12},    /* fireball II                */
     {"hotkiss",     spl032,1,SBD032,5},     /* firebolt II                */
     {"hotseat",     spl033,2,SBD033,3},     /* ice protection I           */
     {"howru",       spl034,3,SBD034,2},     /* detect health (hit points) */
     {"hydrant",     spl035,2,SBD035,6},     /* fire protection II         */
     {"ibebad",      spl036,2,SBD036,24},    /* ultimate protection II     */
     {"icedtea",     spl037,1,SBD037,15},    /* ice storm I                */
     {"icutwo",      spl038,3,SBD038,16},    /* see invisibility III       */
     {"iseeyou",     spl039,3,SBD039,3},     /* see invisibility II        */
     {"koolit",      spl040,1,SBD040,3},     /* cone of cold I             */
     {"makemyd",     spl041,2,SBD041,8},     /* object protection II       */
     {"mower",       spl042,3,SBD042,7},     /* destroy things on ground   */
     {"noouch",      spl043,2,SBD043,1},     /* heal I                     */
     {"nosey",       spl044,3,SBD044,5},     /* read other's memorized spls*/
     {"peekabo",     spl045,2,SBD045,15},    /* invisibility II            */
     {"peepint",     spl046,3,SBD046,7},     /* scry someone               */
     {"pickpoc",     spl047,3,SBD047,8},     /* steal a player's item      */
     {"pocus",       spl048,1,SBD048,1},     /* magic missile              */
     {"polarba",     spl049,2,SBD049,13},    /* ice protection III         */
     {"sapspel",     spl050,1,SBD050,11},    /* sap spell points II        */
     {"saywhat",     spl051,3,SBD051,6},     /* forget one spell           */
     {"screwem",     spl052,1,SBD052,16},    /* fire storm                 */
     {"smokey",      spl053,2,SBD053,2},     /* fire protection I          */
     {"snowjob",     spl054,1,SBD054,13},    /* cone of cold III           */
     {"sunglass",    spl055,2,SBD055,3},     /* lightning protection I     */
     {"surgless",    spl056,2,SBD056,12},    /* lightning protection III   */
     {"takethat",    spl057,1,SBD057,4},     /* sap spell points I         */
     {"thedoc",      spl058,2,SBD058,5},     /* heal II                    */
     {"tiltowait",   spl059,1,SBD059,24},    /* earthquake                 */
     {"tinting",     spl060,2,SBD060,8},     /* lightning protection II    */
     {"toastem",     spl061,1,SBD061,18},    /* fireball III               */
     {"weewillo",    spl062,3,SBD062,7},     /* transform into willowisp   */
     {"whereami",    spl063,3,SBD063,6},     /* location finder            */
     {"whopper",     spl064,2,SBD064,12},    /* fire protection III        */
     {"whoub",       spl065,3,SBD065,3},     /* detect true idenity        */
     {"zapher",      spl066,1,SBD066,4},     /* lightning bolt I           */
     {"zelastone",   spl067,1,SBD067,10}     /* ariel servant              */
}, *splptr;

#define SPASIZ (sizeof(spells)/sizeof(struct spell))

static INT splno;                  /* index number of spell in array  */

CHAR_BUFFER(SOMETHINGMISSSPELL, 80, "...Something is missing and the spell fails!\r");
CHAR_BUFFER(YOUCASTSPELL, 80, "...You cast the spell!\r");

VOID
insrtk(VOID)                       /* initiate spell based real time stuff */
{
     rtkick(30,splrtk);
}

VOID
splrtk(VOID)                       /* spell based real time event handler  */
{
     INT i;
     INT j;
     INT p;

     setmbk(kmb);
     for (gmpptr=gmparr,i=0 ; i < nterms ; gmpptr++,i++) {
          p=0;
          gmpptr->macros=0;
          if (gmpptr->gamloc != -1) {
               if (gmpptr->spts < (2*gmpptr->level)-1) {
                    gmpptr->spts+=2;
               }
               else {
                    gmpptr->spts=2*gmpptr->level;
               }
               for (j=0 ; j < NCHARM ; j++) {
                    if (gmpptr->charms[j]) {
                         if (--(gmpptr->charms[j]) ==  0) {
                              clrprf();
                              prfmsg(BASMSG+j);
                              p=1;
                              if (j == ALTNAM) {
                                   outprf(i);
                                   p=0;
                                   gmpptr->flags&=~(INVISF+PEGASU+WILLOW+PDRAGN);
                                   prfmsg(RET2NM,gmpptr->altnam,gmpptr->plyrid);
                                   usrnum=i;
                                   sndoth();
                                   strcpy(gmpptr->altnam,gmpptr->plyrid);
                                   strcpy(gmpptr->attnam,gmpptr->plyrid);
                              }
                         }
                    }
               }
               if (p) {
                    outprf(gmpptr->modno);
               }
          }
     }
     rtkick(30,splrtk);
}

static GBOOL
chkstf(VOID)                       /* check to see if spell can be cast    */
{
     if (margc == 2) {
          btuxmt(usrnum, SOMETHINGMISSSPELL);
          sndutl("trying to cast a spell, without success.");
          return(FALSE);
     }
     else if (!findgp(margv[2])) {
          if ((objptr=fgmlobj(margv[2])) != NULL ||
              (objptr=fgmpobj(margv[2])) != NULL) {
               if (objptr ==  &gmobjs[52]) {
                    prfmsg(ZMSG08);
                    outprf(usrnum);
                    prfmsg(ZMSG09,gmpptr->altnam,himher(gmpptr));
                    sndoth();
                    ogmptr=gmpptr;
                    hitoth(genrdn(20,46));
                    return(FALSE);
               }
               prfmsg(KSPM00,objptr->name);
               outprf(usrnum);
               prfmsg(KSPM01,gmpptr->altnam,dobutl(objptr));
               sndoth();
          }
          else {
               youmsg(KSPM02);
               sndutl("casting at phantoms!");
          }
          return(FALSE);
     }
     else {
          return(TRUE);
     }
}

VOID
hitoth(                            /* deduct hit points and check for death*/
INT nhits)
{
     INT loc;
     CHAR pname[20];
     static CHAR olduid[ALSSIZ];

     ogmptr->hitpts-=(SHORT)nhits;
     if (ogmptr->hitpts <= 0) {
          loc=ogmptr->gamloc;
          strcpy(pname,ogmptr->altnam);
          prfmsg(DIEMSG);
          outprf(ogmptr->modno);
          strcpy(olduid,ogmptr->plyrid);
          initgp(ogmptr,olduid);
          prfmsg(KILLED,pname);
          sndloc(loc);
          entrgp(0,ogmptr,"appeared in a holy light");
     }
}

static VOID
chgbod(                            /* change user description              */
CHAR *altnam,
CHAR *attnam,
LONG flag,
INT duration)
{
     strcpy(gmpptr->altnam,altnam);
     strcpy(gmpptr->attnam,attnam);
     gmpptr->flags&=~(INVISF+PEGASU+WILLOW+PDRAGN);
     gmpptr->flags|=flag;
     gmpptr->charms[ALTNAM]+=(SHORT)(2*duration);
}

static VOID
striker(                           /* check if spell effects a user        */
INT damage,
INT pro,
INT mcylvl,
INT fstmsg)
{
     if (chkstf()) {
          if (ogmptr->charms[pro]) {
               prfmsg(fstmsg,ogmptr->altnam);
               outprf(usrnum);
               prfmsg(fstmsg+1,gmpptr->altnam);
               outprf(ogmptr->modno);
               prfmsg(fstmsg+2,gmpptr->altnam,ogmptr->altnam,kheshe(ogmptr));
               sndbt2();
          }
          else if (ogmptr->level <= mcylvl) {
               prfmsg(MERCYA,ogmptr->altnam);
               outprf(usrnum);
               prfmsg(MERCYB,gmpptr->altnam);
               outprf(ogmptr->modno);
               prfmsg(MERCYC,gmpptr->altnam,ogmptr->altnam,kheshe(ogmptr));
               sndbt2();
          }
          else {
               prfmsg(fstmsg+3,ogmptr->altnam);
               outprf(usrnum);
               prfmsg(fstmsg+4,gmpptr->altnam,damage);
               outprf(ogmptr->modno);
               prfmsg(fstmsg+5,gmpptr->altnam,ogmptr->altnam,kheshe(ogmptr));
               sndbt2();
               hitoth(damage);
          }
     }
}

static VOID
msgutl3(                           /* send messages to three groups        */
INT yourmsg,
INT hismsg,
INT othmsg)
{
     prfmsg(yourmsg);
     outprf(usrnum);
     prfmsg(hismsg,gmpptr->altnam);
     outprf(ogmptr->modno);
     prfmsg(othmsg,gmpptr->altnam,ogmptr->altnam);
     sndbt2();
}

VOID
msgutl2(                           /* send a message to two groups         */
INT yourmsg,
INT othmsg)
{
     prfmsg(yourmsg);
     outprf(usrnum);
     prfmsg(othmsg,gmpptr->altnam);
     sndoth();
}

static VOID
masshitr(                          /* mass hit users                       */
INT damage,
INT pro,
INT hitmsg,
INT othmsg,
INT promsg,
INT hitslf,
INT mcylvl)
{
     INT i;

     for (ogmptr=gmparr,i=0 ; i < nterms ; ogmptr++,i++) {
          if (gmpptr->gamloc == ogmptr->gamloc) {
               if (hitslf || ogmptr != gmpptr) {
                    if (ogmptr->charms[pro]) {
                         prfmsg(promsg,ogmptr->altnam);
                         outprf(usrnum);
                    }
                    else if (ogmptr->level <=  mcylvl) {
                         prfmsg(MERCYU);
                         outprf(i);
                         prfmsg(MERCYO,ogmptr->altnam);
                         fnkysnd();
                    }
                    else {
                         prfmsg(hitmsg);
                         outprf(i);
                         prfmsg(othmsg,ogmptr->altnam);
                         fnkysnd();
                         hitoth(damage);
                    }
               }
          }
     }
}

static VOID
spl001(VOID)                       /* spell #1 routine                     */
{
     gmpptr->charms[OBJPRO]+=(2*4);
     msgutl2(SPM000,SPM001);
}

static VOID
spl002(VOID)                       /* spell #2 routine                     */
{
     gmpptr->hitpts=(4*gmpptr->level);
     msgutl2(SPM002,SPM003);
}

static VOID
spl003(VOID)                       /* spell #3 routine                     */
{
     if (chkstf()) {
          if (ogmptr->charms[OBJPRO] || ogmptr->npobjs == 0) {
               msgutl3(SNW000,SNW001,SNW002);
          }
          else {
               prfmsg(SPM004,ogmptr->attnam,ogmptr->gpobjs[0]->name);
               outprf(usrnum);
               prfmsg(SPM005,gmpptr->altnam,ogmptr->gpobjs[0]->name);
               outprf(ogmptr->modno);
               prfmsg(SPM006,gmpptr->altnam,ogmptr->altnam,hisher(ogmptr),
                             ogmptr->gpobjs[0]->name);
               sndbt2();
               takpobj(ogmptr,0);
          }
     }
}

static VOID
spl004(VOID)                       /* spell #4 routine                     */
{
     if (chkstf()) {
          if (ogmptr->charms[OBJPRO] || ogmptr->npobjs == 0) {
               msgutl3(SNW000,SNW001,SNW002);
          }
          else {
               ogmptr->npobjs=0;
               prfmsg(SPM007,ogmptr->attnam,hisher(ogmptr));
               outprf(usrnum);
               prfmsg(SPM008,gmpptr->altnam);
               outprf(ogmptr->modno);
               prfmsg(SPM009,gmpptr->altnam,ogmptr->altnam,hisher(ogmptr));
               sndbt2();
          }
     }
}

static VOID
spl005(VOID)                       /* spell #5 routine                     */
{
     if (chkstf()) {
          if (ogmptr->charms[OBJPRO]) {
               msgutl3(S05M00,S05M01,S05M02);
          }
          else {
               if ((objptr=fgmpobj("moonstone")) != NULL) {
                    tgmpobj(objno);
                    ogmptr->offspls=0L;
                    ogmptr->defspls=0L;
                    ogmptr->othspls=0L;
                    prfmsg(S05M03,ogmptr->altnam,ogmptr->altnam);
                    outprf(usrnum);
                    prfmsg(S05M04,gmpptr->altnam,gmpptr->altnam);
                    outprf(ogmptr->modno);
                    prfmsg(S05M05,gmpptr->altnam,gmpptr->altnam,ogmptr->altnam);
                    sndbt2();
               }
               else {
                    msgutl2(MISS00,MISS01);
               }
          }
     }
}

static VOID
spl006(VOID)                       /* spell #6 routine                     */
{
     msgutl2(S06M00,S06M01);
     masshitr(10,FIRPRO,S06M02,S06M03,S06M04,0,1);
}

static VOID
spl007(VOID)                       /* spell #7 routine                     */
{
     gmpptr->charms[CINVIS]=(2*4);
     msgutl2(S07M00,S07M01);
}

static VOID
spl008(VOID)                       /* spell #8 routine                     */
{
     prfmsg(S08M00);
     outprf(usrnum);
     prfmsg(S08M01,gmpptr->altnam);
     sndoth();
     chgbod("Some Unseen Force","Unseen Force",INVISF,2);
}

static VOID
spl009(VOID)                       /* spell #9 routine                     */
{
     gmpptr->charms[FIRPRO]=(2*2);
     gmpptr->charms[ICEPRO]=(2*2);
     gmpptr->charms[LIGPRO]=(2*2);
     gmpptr->charms[OBJPRO]=(2*2);
     msgutl2(S09M00,S09M01);
}

static VOID
spl010(VOID)                       /* spell #10 routine                    */
{
     if ((objptr=fgmpobj("pearl")) != NULL) {
          tgmpobj(objno);
          msgutl2(S10M00,S10M01);
          masshitr(30,ICEPRO,S10M02,S10M03,S10M04,1,3);
     }
     else {
          msgutl2(MISS00,MISS01);
     }
}

static VOID
spl011(VOID)                       /* spell #11 routine                    */
{
     INT i;

     if (chkstf()) {
          if (ogmptr->charms[OBJPRO] || ogmptr->npobjs == 0
            || gmlptr->nlobjs >= MXLOBS) {
               msgutl2(S11M00,NOSUCC);
          }
          else {
               msgutl3(S11M02,S11M03,S11M04);
               for (i=0 ; i < ogmptr->npobjs ; ) {
                    if (gmlptr->nlobjs == MXLOBS) {
                         break;
                    }
                    objptr=ogmptr->gpobjs[objno=(ogmptr->npobjs-1)];
                    takpobj(ogmptr,objno);
                    pgmlobj(objptr);
                    prfmsg(S11M05,objptr->name);
                    outprf(ogmptr->modno);
                    prfmsg(S11M06,ogmptr->altnam,hisher(ogmptr),objptr->name);
                    outprf(usrnum);
                    sndbt2();
               }
          }
     }
}

static VOID
spl012(VOID)                       /* spell #12 routine                    */
{
     if (chkstf()) {
          prfmsg(S12M00,ogmptr->altnam,ogmptr->spts);
          outprf(usrnum);
          prfmsg(S12M01,gmpptr->altnam);
          outprf(ogmptr->modno);
          prfmsg(S12M02,gmpptr->altnam,ogmptr->altnam);
          sndbt2();
     }
}

static VOID
spl013(VOID)                       /* spell #13 routine                    */
{
     if (chkstf()) {
          if (ogmptr->charms[OBJPRO] || ogmptr->nspells == 0) {
               msgutl3(S13M00,S13M01,S13M02);
          }
          else {
               ogmptr->nspells=0;
               msgutl3(S13M03,S13M04,S13M05);
          }
     }
}

static VOID
spl014(VOID)                       /* spell #14 routine                    */
{
     INT i;

     i=genrdn(0,218);
     prfmsg(S14M00);
     outprf(usrnum);
     prfmsg(S14M01,gmpptr->altnam,kheshe(gmpptr));
     sndoth();
     remvgp(gmpptr,"vanished in a blue light");
     entrgp(i,gmpptr,"appeared in a blue");
}

static VOID
spl015(VOID)                       /* spell #15 routine                    */
{
     msgutl2(S15M00,S15M01);
     gmpptr->hitpts+=25;
     if (gmpptr->hitpts > gmpptr->level*4) {
          gmpptr->hitpts=gmpptr->level*4;
     }
}

static VOID
spl016(VOID)                       /* spell #16 routine                    */
{
     prfmsg(S16M00);
     outprf(usrnum);
     prfmsg(S16M01,gmpptr->altnam);
     sndoth();
     chgbod("Some pegasus","pegasus",PEGASU,2);
}

static VOID
spl017(VOID)                       /* spell #17 routine                    */
{
     striker(4,FIRPRO,0,S17M00);
}

static VOID
spl018(VOID)                       /* spell #18 routine                    */
{
     msgutl2(S18M00,S18M01);
     masshitr(26,ICEPRO,S18M02,S18M03,S18M04,0,2);
}

static VOID
spl019(VOID)                       /* spell #19 routine                    */
{
     striker(16,ICEPRO,1,S19M00);
}

static VOID
spl020(VOID)                       /* spell #20 routine                    */
{
     msgutl2(S20M00,S20M01);
     masshitr(12,ICEPRO,S20M02,S20M03,S20M04,0,1);
}

static VOID
spl021(VOID)                       /* spell #21 routine                    */
{
     striker(22,FIRPRO,1,S21M00);
}

static VOID
spl022(VOID)                       /* spell #22 routine                    */
{
     striker(18,LIGPRO,2,S22M00);
}

static VOID
spl023(VOID)                       /* spell #23 routine                    */
{
     INT i;

     if (margc == 2) {
          youmsg(OBJM07);
          sndutl("failing at spellcasting.");
     }
     else {
          i=atoi(margv[2]);
          if (i < 0 || i > 218) {
               prfmsg(S23M00);
               outprf(usrnum);
               prfmsg(S23M01,gmpptr->altnam,kheshe(gmpptr));
               sndoth();
          }
          else {
               prfmsg(S23M02);
               outprf(usrnum);
               prfmsg(S23M03,gmpptr->altnam);
               remvgp(gmpptr,"vanished in a red cloud");
               entrgp(i,gmpptr,"appeared in a red cloud");
          }
     }
}

static VOID
spl024(VOID)                       /* spell #24 routine                    */
{
     prfmsg(S24M00);
     outprf(usrnum);
     prfmsg(S24M01,gmpptr->altnam);
     sndoth();
     chgbod("Some psuedo dragon","psuedo dragon",PDRAGN,2);
}

static VOID
spl025(VOID)                       /* spell #25 routine                    */
{
     gmpptr->charms[OBJPRO]=(2*2);
     msgutl2(S25M00,S25M01);
}

static VOID
spl026(VOID)                       /* spell #26 routine                    */
{
     gmpptr->charms[ICEPRO]=(2*8);
     msgutl2(S26M00,S26M01);
}

static VOID
spl027(VOID)                       /* spell #27 routine                    */
{
     if ((objptr=fgmpobj("opal")) != NULL) {
          tgmpobj(objno);
          prf("...Your opal suddenly disappears!***\r");
          outprf(usrnum);
          msgutl2(S27M00,S27M01);
          masshitr(32,LIGPRO,S27M02,S27M03,S27M04,1,2);
     }
     else {
          msgutl2(MISS00,MISS01);
     }
}

static VOID
spl028(VOID)                       /* spell #28 routine                    */
{
     if (chkstf()) {
          if ((objptr=fgmpobj("bloodstone")) != NULL) {
               tgmpobj(objno);
               ogmptr->charms[FIRPRO]=0;
               ogmptr->charms[ICEPRO]=0;
               ogmptr->charms[LIGPRO]=0;
               ogmptr->charms[OBJPRO]=0;
               prfmsg(S28M00,ogmptr->altnam,ogmptr->altnam,kheshe(ogmptr));
               outprf(usrnum);
               prfmsg(S28M01,gmpptr->altnam);
               outprf(ogmptr->modno);
               prfmsg(S28M02,ogmptr->altnam,kheshe(ogmptr),
                             ogmptr->altnam,ogmptr->altnam);
               sndbt2();
          }
          else {
               msgutl2(MISS00,MISS01);
          }
     }
}

static VOID
spl029(VOID)                       /* spell #29 routine                    */
{
     striker(24,LIGPRO,2,S29M00);
}

static VOID
spl030(VOID)                       /* spell #30 routine                    */
{
     msgutl2(S30M00,S30M01);
     masshitr(16,LIGPRO,S30M02,S30M03,S30M04,0,2);
}

static VOID
spl031(VOID)                       /* spell #31 routine                    */
{
     msgutl2(S31M00,S31M01);
     masshitr(22,FIRPRO,S31M02,S31M03,S31M04,0,2);
}

static VOID
spl032(VOID)                       /* spell #32 routine                    */
{
     striker(10,FIRPRO,1,S32M00);
}

static VOID
spl033(VOID)                       /* spell #33 routine                    */
{
     gmpptr->charms[ICEPRO]=(2*3);
     msgutl2(S33M00,S33M01);
}

static VOID
spl034(VOID)                       /* spell #34 routine                    */
{
     if (chkstf()) {
          prfmsg(S34M00,ogmptr->hitpts);
          outprf(usrnum);
          prfmsg(S34M01,gmpptr->altnam);
          outprf(ogmptr->modno);
          prfmsg(S34M02,gmpptr->altnam,ogmptr->altnam);
          sndbt2();
     }
}

static VOID
spl035(VOID)                       /* spell #35 routine                    */
{
     gmpptr->charms[FIRPRO]=(2*8);
     msgutl2(S35M00,S35M01);
}

static VOID
spl036(VOID)                       /* spell #36 routine                    */
{
     if ((objptr=fgmpobj("sapphire")) != NULL) {
          tgmpobj(objno);
          gmpptr->charms[FIRPRO]=(2*4);
          gmpptr->charms[ICEPRO]=(2*4);
          gmpptr->charms[LIGPRO]=(2*4);
          gmpptr->charms[OBJPRO]=(2*4);
          prfmsg(S36M00);
          outprf(usrnum);
          prfmsg(S36M01,gmpptr->altnam,gmpptr->altnam,hisher(gmpptr),
                        gmpptr->altnam,himher(gmpptr));
          sndoth();
     }
     else {
          msgutl2(MISS00,MISS01);
     }
}

static VOID
spl037(VOID)                       /* spell #37 routine                    */
{
     msgutl2(S37M00,S37M01);
     masshitr(20,ICEPRO,S37M02,S37M03,S37M04,1,2);
}

static VOID
spl038(VOID)                       /* spell #38 routine                    */
{
     gmpptr->charms[CINVIS]=(2*8);
     msgutl2(S38M00,S38M01);
}

static VOID
spl039(VOID)                       /* spell #39 routine                    */
{
     gmpptr->charms[CINVIS]=(2*4);
     msgutl2(S39M00,S39M01);
}

static VOID
spl040(VOID)                       /* spell #40 routine                    */
{
     striker(6,ICEPRO,0,S40M00);
}

static VOID
spl041(VOID)                       /* spell #41 routine                    */
{
     gmpptr->charms[OBJPRO]=(2*3);
     msgutl2(S41M00,S41M01);
}

static VOID
spl042(VOID)                       /* spell #42 routine                    */
{
     INT i;

     btuxmt(usrnum, YOUCASTSPELL);
     for (i=0 ; i < gmlptr->nlobjs ; ) {
          if (gmlptr->lcobjs[i]->flags&PICKUP) {
               prf("***\rThe %s %s vanishes!\r",
                   gmlptr->lcobjs[i]->name,gmlptr->brfdes);
               sndloc(gmpptr->gamloc);
               tgmlobj(i);
          }
          else {
               i++;
          }
     }
}

static VOID
spl043(VOID)                       /* spell #43 routine                    */
{
     msgutl2(S43M00,S43M01);
     gmpptr->hitpts+=4;
     if (gmpptr->hitpts > gmpptr->level*4) {
          gmpptr->hitpts=gmpptr->level*4;
     }
}

static VOID
spl044(VOID)                       /* spell #44 routine                    */
{
     INT i;
     INT n=0;
     struct spell **pspells;

     (VOID)n;
     if (chkstf()) {
          prfmsg(S44M00,ogmptr->altnam);
          pspells=ogmptr->spells;
          switch (n=ogmptr->nspells) {
          case 0:
               prf("no spells");
               break;
          case 1:
               prf("\"%s\"",pspells[0]->name);
               break;
          case 2:
               prf("\"%s\" and \"%s\"",pspells[0]->name,pspells[1]->name);
               break;
          default:
               for (i=0 ; i < n-1 ; i++) {
                    prf("\"%s\", ",pspells[i]->name);
               }
               prf("and \"%s\"",pspells[i]->name);
          }
          prf(" memorized.\r");
          outprf(usrnum);
          prfmsg(S44M01,gmpptr->altnam);
          outprf(ogmptr->modno);
          prfmsg(S44M02,gmpptr->altnam,ogmptr->altnam);
          sndbt2();
     }
}

static VOID
spl045(VOID)                       /* spell #45 routine                    */
{
     prfmsg(S45M00);
     outprf(usrnum);
     prfmsg(S45M01,gmpptr->altnam);
     sndoth();
     chgbod("Some Unseen Force","Unseen Force",INVISF,4);
}

static VOID
spl046(VOID)                       /* spell #46 routine                    */
{
     if (margc < 3) {
          youmsg(OBJM07);
     }
     else if (!fgamgp(margv[2]) || ogmptr->charms[OBJPRO]) {
          youmsg(KSPM03);
     }
     else {
          prfmsg(KSPM04);
          setmbk(klmb);
          prfmsg(lcrous[ogmptr->gamloc].londes);
          setmbk(kmb);
          prfmsg(KSPM05);
          outprf(usrnum);
          prfmsg(KSPM06);
          outprf(ogmptr->modno);
     }
     prfmsg(KSPM07,gmpptr->altnam);
     sndoth();
}

static VOID
spl047(VOID)                       /* spell #48 routine                    */
{
     INT value=0;

     if (chkstf()) {
          if (ogmptr->charms[OBJPRO] ||
              ogmptr->npobjs == 0 || gmpptr->npobjs == MXPOBS) {
               msgutl3(S47M00,S47M01,S47M00);
          }
          else {
               prfmsg(S47M03,ogmptr->gpobjs[0]->name,ogmptr->altnam,
                             ogmptr->gpobjs[0]->name);
               outprf(usrnum);
               prfmsg(S47M04,gmpptr->altnam,ogmptr->gpobjs[0]->name,
                             ogmptr->gpobjs[0]->name,gmpptr->altnam);
               outprf(ogmptr->modno);
               prfmsg(S47M05,gmpptr->altnam,ogmptr->gpobjs[0]->name,
                             ogmptr->altnam,ogmptr->gpobjs[0]->name,
                             gmpptr->altnam);
               sndbt2();
               objptr=fndpobj(ogmptr,ogmptr->gpobjs[0]->name);
               takpobj(ogmptr,0);
               pgmpobj(objptr,value);
          }
     }
}

static VOID
spl048(VOID)                       /* spell #48 routine                    */
{
     striker(2,OBJPRO,0,S48M00);
}

static VOID
spl049(VOID)                       /* spell #49 routine                    */
{
     gmpptr->charms[ICEPRO]=(2*10);
     msgutl2(S49M00,S49M01);
}

static VOID
spl050(VOID)                       /* spell #50 routine                    */
{
     if (chkstf()) {
          if (ogmptr->charms[OBJPRO] || ogmptr->spts == 0) {
               msgutl3(S50M00,S50M01,S50M02);
          }
          else {
               ogmptr->spts-=16;
               if (ogmptr->spts < 0) {
                    ogmptr->spts=0;
               }
               msgutl3(S50M03,S50M04,S50M05);
          }
     }
}

static VOID
spl051(VOID)                       /* spell #51 routine                    */
{
     if (chkstf()) {
          if (ogmptr->charms[OBJPRO] || ogmptr->nspells == 0) {
               msgutl3(S51M00,S51M01,S51M02);
          }
          else {
               ogmptr->nspells--;
               msgutl3(S51M03,S51M04,S51M05);
          }
     }
}

static VOID
spl052(VOID)                       /* spell #52 routine                    */
{
     msgutl2(S52M00,S52M01);
     masshitr(26,FIRPRO,S52M02,S52M03,S52M04,1,2);
}

static VOID
spl053(VOID)                       /* spell #53 routine                    */
{
     gmpptr->charms[FIRPRO]=(2*3);
     msgutl2(S53M00,S53M01);
}

static VOID
spl054(VOID)                       /* spell #54 routine                    */
{
     striker(20,ICEPRO,2,S54M00);
}

static VOID
spl055(VOID)                       /* spell #55 routine                    */
{
     gmpptr->charms[LIGPRO]=(2*3);
     msgutl2(S55M00,S55M01);
}

static VOID
spl056(VOID)                       /* spell #56 routine                    */
{
     gmpptr->charms[LIGPRO]=(2*10);
     msgutl2(S56M00,S56M01);
}

static VOID
spl057(VOID)                       /* spell #57 routine                    */
{
     if (chkstf()) {
          if (ogmptr->charms[OBJPRO] || ogmptr->spts == 0) {
               msgutl3(S57M00,S57M01,S57M02);
          }
          else {
               ogmptr->spts-=8;
               if (ogmptr->spts < 0) {
                    ogmptr->spts=0;
               }
               msgutl3(S57M03,S57M04,S57M05);
          }
     }
}

static VOID
spl058(VOID)                       /* spell #58 routine                    */
{
     msgutl2(S58M00,S58M01);
     gmpptr->hitpts+=12;
     if (gmpptr->hitpts > gmpptr->level*4) {
          gmpptr->hitpts=gmpptr->level*4;
     }
}

static VOID
spl059(VOID)                       /* spell #59 routine                    */
{
     INT i;

     if ((objptr=fgmpobj("rose")) != NULL) {
          prfmsg(S59M00);
          outprf(usrnum);
          prfmsg(S59M01,gmpptr->altnam);
          sndoth();
          prfmsg(S59M02);
          sndgam();
          prfmsg(S59M03);
          sndloc(gmpptr->gamloc);
          for (ogmptr=gmparr,i=0 ; i < nterms ; ogmptr++,i++) {
               if (gmpptr->gamloc == ogmptr->gamloc) {
                    if (ogmptr->level <=  3) {
                         prfmsg(MERCYU);
                         outprf(i);
                         prfmsg(MERCYO,ogmptr->altnam);
                         fnkysnd();
                    }
                    else {
                         prfmsg(S59M04);
                         outprf(i);
                         prfmsg(S59M05,ogmptr->altnam,himher(ogmptr));
                         fnkysnd();
                         hitoth(50);
                    }
               }
          }
          tgmpobj(objno);
          for (i=0 ; i < gmlptr->nlobjs ; ) {
               if (gmlptr->lcobjs[i]->flags&PICKUP) {
                    tgmlobj(i);
               }
               else {
                    i++;
               }
          }

     }
     else {
          msgutl2(MISS00,MISS01);
     }
}

static VOID
spl060(VOID)                       /* spell #60 routine                    */
{
     gmpptr->charms[LIGPRO]=(2*8);
     msgutl2(S60M00,S60M01);
}

static VOID
spl061(VOID)                       /* spell #61 routine                    */
{
     if ((objptr=fgmpobj("diamond")) != NULL) {
          youmsg(KSPM08);
          msgutl2(S61M00,S61M01);
          masshitr(32,FIRPRO,S61M02,S61M03,S61M04,0,2);
          tgmpobj(objno);
     }
     else {
          msgutl2(MISS00,MISS01);
     }
}

static VOID
spl062(VOID)                       /* spell #62 routine                    */
{
     prfmsg(S62M00);
     outprf(usrnum);
     prfmsg(S62M01,gmpptr->altnam);
     sndoth();
     chgbod("Some willowisp","willowisp",WILLOW,2);
}

static VOID
spl063(VOID)                       /* spell #63 routine                    */
{
     prfmsg(S63M00,gmpptr->gamloc);
     outprf(usrnum);
     prfmsg(S63M01,gmpptr->altnam,hisher(gmpptr));
     sndoth();
}

static VOID
spl064(VOID)                       /* spell #64 routine                    */
{
     gmpptr->charms[FIRPRO]=(2*10);
     msgutl2(S64M00,S64M01);
}

static VOID
spl065(VOID)                       /* spell #65 routine                    */
{
     if (chkstf()) {
          prfmsg(S65M00,ogmptr->plyrid);
          outprf(usrnum);
          prfmsg(S65M01,gmpptr->altnam);
          outprf(ogmptr->modno);
          prfmsg(S65M02,gmpptr->altnam,ogmptr->altnam);
          sndbt2();
     }
}

static VOID
spl066(VOID)                       /* spell #66 routine                    */
{
     striker(8,LIGPRO,1,S66M00);
}

static VOID
spl067(VOID)                       /* spell #67 routine                    */
{
     INT i;

     if (margc == 2) {
          youmsg(KSPM03);
          sndutl("failing at spellcasting.");
     }
     else if (!fgamgp(margv[2])) {
          prfmsg(S67M00);
          outprf(usrnum);
          prfmsg(S67M01,gmpptr->altnam,hisher(gmpptr),gmpptr->altnam,
                        gmpptr->altnam);
          sndoth();
          ogmptr=gmpptr;
          i=genrdn(20,40);
          hitoth(i);
     }
     else {
          prfmsg(S67M02);
          outprf(usrnum);
          prfmsg(S67M03,gmpptr->altnam,hisher(gmpptr));
          sndoth();
          prfmsg(S67M04);
          sndloc(ogmptr->gamloc);
          if (!(ogmptr->charms[OBJPRO]) && genrdn(0,101) > 10) {
               prfmsg(S67M05);
               outprf(ogmptr->modno);
               prfmsg(S67M06,ogmptr->altnam,himher(ogmptr));
               sndnoth(ogmptr->gamloc);
               i=genrdn(20,40);
               hitoth(i);
          }
          else {
               prfmsg(S67M08);
               outprf(ogmptr->modno);
               prfmsg(S67M09,ogmptr->altnam);
               sndnoth(ogmptr->gamloc);
          }
     }
}

static struct spell *
fsbspl(                            /* search for spell in spell array      */
CHAR *stgptr,
struct spell table[],
INT length)
{
     INT cond;
     struct spell *low;
     struct spell *mid;
     struct spell *high;

     low=&table[0];
     high=&table[length-1];
     while (low <= high) {
          mid=low+((INT)(high-low))/2;
          if ((cond=stricmp(stgptr,mid->name)) < 0) {
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

static VOID
fnkysnd(VOID)                      /* send a message to othusn as a usrnum */
{
     INT hldusn;
     struct gmplyr *dumptr;

     dumptr=gmpptr;
     hldusn=usrnum;
     gmpptr=ogmptr;
     usrnum=ogmptr->modno;
     sndoth();
     gmpptr=dumptr;
     usrnum=hldusn;
}

static struct spell *
splchk(                            /* check ptr to spell if stg is valid   */
CHAR *stg)
{
     for (splno=0 ; splno < gmpptr->nspells ; splno++) {
          if (sameas(stg,gmpptr->spells[splno]->name)) {
               return(gmpptr->spells[splno]);
          }
     }
     return(NULL);
}

static VOID
rmvspl(                            /* remove spell from users memorized one*/
struct gmplyr *gp,
INT spell)
{
     if (--(gp->nspells) != spell) {
          gp->spells[spell]=gp->spells[gp->nspells];
     }
}

static VOID
addspl(                            /* add spell to users memorized ones    */
struct gmplyr *gp,
struct spell *spell)
{
     gp->spells[(gp->nspells)++]=spell;
}

VOID
shwpsp(VOID)                       /* show user the spells they memorized  */
{
     prf("...You currently have ");
     shwsutl(gmpptr);
     outprf(usrnum);
}

static VOID
shwsutl(                           /* display the list of spells memorized */
struct gmplyr *gp)
{
     INT i;
     INT n=0;
     struct spell **pspells;

     (VOID)n;
     pspells=gp->spells;
     switch (n=gp->nspells) {
     case 0:
          prf("no spells");
          break;
     case 1:
          prf("\"%s\"",pspells[0]->name);
          break;
     case 2:
          prf("\"%s\" and \"%s\"",pspells[0]->name,pspells[1]->name);
          break;
     default:
          for (i=0 ; i < n-1 ; i++) {
               prf("\"%s\", ",pspells[i]->name);
          }
          prf("and \"%s\"",pspells[i]->name);
     }
     prf(" memorized, and %d spell points of energy.",gmpptr->spts);
     prf("  You are at level %d, titled \"%s\".\r",gmpptr->level,
                                                   titles[gmpptr->level]);
}

VOID
seesbk(VOID)                       /* show a user their spellbook          */
{
     INT i;
     INT nprfs;
     INT j;
     INT prflmt;
     INT msg;
     CHAR prfspl[NGSPLS+2][10];

     setmem(prfspl,(NGSPLS+2)*10,0);
     for (i=0,nprfs=0 ; i < NGSPLS ; i++) {
          switch (spells[i].sbkref) {
          case 1:
               if (gmpptr->offspls&(spells[i].bitdef)) {
                    movmem(&spells[i].name,&prfspl[nprfs],10);
                    prfspl[nprfs][9]='\0';
                    nprfs++;
               }
               break;
          case 2:
               if (gmpptr->defspls&(spells[i].bitdef)) {
                    movmem(&spells[i].name,&prfspl[nprfs],10);
                    prfspl[nprfs][9]='\0';
                    nprfs++;
               }
               break;
          case 3:
               if (gmpptr->othspls&(spells[i].bitdef)) {
                    movmem(&spells[i].name,&prfspl[nprfs],10);
                    prfspl[nprfs][9]='\0';
                    nprfs++;
               }
          }
     }
     msg=usaptr->systyp == 1 ? ASBOOK1 : SBOOK1;
     prfmsg(msg,(usaptr->sex == 'M' ? "Lord" : "Lady"),gmpptr->plyrid);
     if (nprfs) {
          prflmt=nprfs/3;
          if (nprfs%3) {
               prflmt++;
          }
          for (i=0,j=0 ; i < prflmt ; i++) {
               prfmsg(msg+1,prfspl[j],prfspl[j+1],prfspl[j+2]);
               j+=3;
          }
     }
     else {
          prfmsg(msg+2);
     }
     prfmsg(msg+3);
     outprf(usrnum);
}

VOID
memori(VOID)                       /* memorize a spell if possible         */
{
     INT j=0;
     struct spell *ptr;

     if ((ptr=fsbspl(margv[1],spells,SPASIZ)) != NULL) {
          switch (ptr->sbkref) {
          case 1:
               if (gmpptr->offspls&(ptr->bitdef)) {
                    memutl(ptr);
               }
               else {
                    j=1;
               }
               break;
          case 2:
               if (gmpptr->defspls&(ptr->bitdef)) {
                    memutl(ptr);
               }
               else {
                    j=1;
               }
               break;
          case 3:
               if (gmpptr->othspls&(ptr->bitdef)) {
                    memutl(ptr);
               }
               else {
                    j=1;
               }
               break;
          }
     }
     else {
          j=1;
     }
     if (j) {
          youmsg(KSPM09);
          sndutl("trying in vain learn a spell.");
     }
}

static VOID
memutl(                            /* memorize a spell if possible         */
struct spell *sptr)
{
     if (gmpptr->nspells >= MAXSPL) {
          prfmsg(LOSSPL,sptr->name,gmpptr->spells[MAXSPL-1]->name);
          gmpptr->nspells=MAXSPL-1;
          addspl(gmpptr,sptr);
     }
     else {
          addspl(gmpptr,sptr);
          prfmsg(GAISPL,sptr->name);
     }
     outprf(usrnum);
     prfmsg(MEMSPL,gmpptr->altnam,hisher(gmpptr));
     sndoth();
}

VOID
caster(VOID)                       /* cast a spell if possible             */
{
     if (margc == 1) {
          youmsg(OBJM07);
     }
     else if ((splptr=splchk(margv[1])) == NULL) {
          prfmsg(NOTMEM);
          outprf(usrnum);
          prfmsg(SPFAIL,gmpptr->altnam);
          sndoth();
     }
     else if (splptr->level > gmpptr->level) {
          youmsg(KSPM10);
          sndutl("mouthing off.");
     }
     else if (splptr->level > gmpptr->spts) {
          youmsg(KSPM10);
          sndutl("waving %s arms.");
     }
     else {
          rmvspl(gmpptr,splno);              /* remove spell from player */
          gmpptr->spts-=(SHORT)splptr->level;       /* remove spell points */
          (*(splptr->splrou))();             /* call spell's routine */
     }
}

static VOID
sndnoth(                           /* send messages to users in room loc   */
INT loc)
{
     INT i;
     struct gmplyr *utlgp;

     for (utlgp=gmparr,i=0 ; i < nterms ; utlgp++,i++) {
          if (utlgp != ogmptr && utlgp->gamloc == loc) {
               outprf(i);
          }
     }
     clrprf();
}
