/*****************************************************************************
 *                                                                           *
 *   KYRANDIA, Fantasy-world of Legends                     Version 7.20     *
 *                                                                           *
 *   KYRANDIA.C (K.C) - Game mainline and Worldgorup interface module        *
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
#include "elwkyrl.h"

#define KYRAMDF     "ELWKYR.MDF"
#define KYRLMCV     "elwkyrl.mcv"
#define KYRSMCV     "elwkyrs.mcv"
#define KYRMMCV     "elwkyrm.mcv"
#define KYRADAT     "elwkyr.dat"
#define KYRALCS     "elwkyr.lcs"

VOID fixmargc(VOID);

static GBOOL kyrinj(VOID);

CHAR gamver[]={"7.20"};

INT kyrstt;                   /* Kyrandia state number                     */
struct module kyrandia={      /* module interface block                    */
     "",                      /*    name used to refer to this module      */
     kyloin,                  /*    user log-on suplement                  */
     kyrand,                  /*    input routine if selected              */
     dfsthn,                  /*    status-input routine                   */
     kyrinj,                  /*    "injoth" routine for this module       */
     NULL,                    /*    user logoff supplemental routine       */
     kyhup,                   /*    hang-up routine                        */
     NULL,                    /*    midnight clean-up                      */
     kydela,                  /*    delete account routine                 */
     kysdn                    /*    system shut-down routine               */
};

struct gmplyr *gmparr;
struct gmplyr *gmpptr;
struct gmplyr *ogmptr;
struct gmplyr *kyrply;

struct gamloc *gmlocs;
struct gamloc *gmlptr;
struct gamloc *oglptr;

INT objno;               /* used for an object's array position            */
INT objno2;              /* another object array position holder           */

INT givrcrd;             /* give system credits for game gold              */

CHAR *kyratr;                 /* attribute for displayed Kyrandia text     */
//CHAR newline[2] = "\r";

DFAFILE *kbb;
HMCVFILE kmb;
HMCVFILE klmb;
HMCVFILE ksmb;

CHAR *titles[26]={
     "",
     "Apprentice",
     "Magic-user",
     "Evoker",
     "Conjurer",
     "Magician",
     "Mystic",
     "Enchanter",
     "Warlock",
     "Sorcerer",
     "Green Wizard",
     "Blue Wizard",
     "Red Wizard",
     "Grey Wizard",
     "White Wizard",
     "Mage",
     "Mage of Ice",
     "Mage of Wind",
     "Mage of Fire",
     "Mage of Light",
     "Arch-Mage",
     "Arch-Mage of Wands",
     "Arch Mage of Staves",
     "Arch-Mage of Swords",
     "Arch-Mage of Jewels",
     "Arch-Mage of Legends"
};

CHAR_BUFFER(APPEARCLOUDMIST, 80, "appeared in a cloud of mists");
CHAR_BUFFER(APPEARFLASH, 80, "appeared in a flash");

VOID EXPORT
init__elwkyr(VOID)                 /* initialize Kyrandia                  */
{
     INT n;

     stzcpy(kyrandia.descrp,gmdnam(KYRAMDF),MNMSIZ);
     kyrstt=register_module(&kyrandia);
     klmb=opnmsg(KYRLMCV);
     ksmb=opnmsg(KYRSMCV);
     kmb=opnmsg(KYRMMCV);

     kyratr=stgopt(KYRATR);
     givrcrd=ynopt(GIVCRD);
     kbb=dfaOpen(KYRADAT,sizeof(struct gmplyr),NULL);
     gmparr=(struct gmplyr *)alczer(nterms*sizeof(struct gmplyr));
     for (n=0 ; n < nterms ; n++) {
          gmparr[n].gamloc=-1;
     }
     iniutl();                /* utilities initialization */
     creatl(KYRALCS);         /* dynaloc room array */
     insrtk();                /* begin splrtk() */
     inianm();                /* animator initialization */
     kinuse=kyrasub=0;        /* Initialize Editor Package */
     fixmargc();

     shocst(spr("ELW Kyrandia v%s", gamver), "(C) Copyright 2024 Elwynor Technologies - www.elwynor.com");
}

GBOOL
kyloin(VOID)                       /* Kyrandia Supplemental Logon          */
{
     dfaSetBlk(kbb);
     if (!dfaQueryEQ(usaptr->userid,0)) {
          setmbk(kmb);
          prfmsg(KLOGO);
          outprf(usrnum);
     }
     return(FALSE);
}

GBOOL
kyrand(VOID)                       /* main game <CR>-input entry point     */
{
     INT i;
     INT len;
     INT bad=0;
     //CHAR *ansiout;
     CHAR_BUFFER(LINEFEED, 80, "\r");


     setmbk(kmb);
     dfaSetBlk(kbb);
     gmpptr=&gmparr[usrnum];
     gmpptr->modno=(SHORT)usrnum;
     if (sameas(margv[0],"x") && usrptr->substt < 90) {
          remvgp(gmpptr, "vanished in sparkling light");
          prfmsg(EXIKYR);
          btupmt(usrnum,0);
          return(FALSE);
     }
     switch (usrptr->substt) {
     case 0:
         //ansiout = alczer(100);
         //strcpy(ansiout,newline);
         btuxmt(usrnum,kyratr);
         btuxmt(usrnum,LINEFEED); // this used to be btuxmt(usrnum,"\r"); which is a no-no - can't use a const char * since it's not modifiable
          if (gmpptr->flags&LOADED) {
               prfmsg(ansmsg(CREDITS),(usaptr->sex == 'M' ? "Lord" : "Lady"),
                              gmpptr->plyrid,gamver);
               gi_invrou();
               entrgp(gmpptr->pgploc,gmpptr,
                   APPEARCLOUDMIST);
               usrptr->substt=7;
          }
          else if (loadkp()) {
               prfmsg(KINM00);
               sndgam();
               prfmsg(ansmsg(CREDITS),(usaptr->sex == 'M' ? "Lord" : "Lady"),
                         gmpptr->plyrid,gamver);
               rights();
          }
          else {
              btumil(usrnum,ALSSIZ-1);
               usrptr->substt++;
               prfmsg(GETALS);
               outprf(usrnum);
               break;
          }
          btupmt(usrnum,'>');
          break;
     case 1:
         btumil(usrnum,DFTIMX);
         setmbk(kmb);
         len = strlen(margv[0]);
         if (len > 0) {
             strlwr(margv[0]);
             margv[0][0] = (CHAR)toupper(margv[0][0]);
         }
         else bad = 1;
//          len=strlen(margv[0]);
          dfaSetBlk(kbb);
          if (pfnlvl > 0) {
               prfmsg(FOULID);
               outprf(usrnum);
               break;
          }
          if (!bad && margc != 1) {
               bad=1;
          }
          else if (!bad) {
               for (i=0 ; i < len ; i++) {
                    if (digalw ? !isalnum(margv[0][i])
                        : !isalpha(margv[0][i])) {
                         bad=1;
                         break;
                    }
               }
          }
          if (bad || len < 3 || len > (ALSSIZ-1)) {
               prfmsg(BADPID);
               prfmsg(B4PLA2);
          }
          else if ((sameas(margv[0],"Sysop")
                && !sameas(usaptr->userid,"Sysop")) || dfaQueryEQ(margv[0],1)) {
               prfmsg(NTGOOD);
               prfmsg(B4PLA2);
          }
          else {
              btupmt(usrnum,'>');
               initgp(gmpptr,margv[0]);
               gi_prep4d(gmpptr);
               dfaInsert(gmpptr);
               gi_rest4p(gmpptr);
               prfmsg(GOODPD,margv[0]);
               usrptr->substt++;
          }
          outprf(usrnum);
          break;
     case 2:
          prfmsg(INTROA);
          outprf(usrnum);
          usrptr->substt++;
          break;
     case 3:
          prfmsg(INTROB);
          outprf(usrnum);
          usrptr->substt++;
          break;
     case 4:
          prfmsg(INTROC);
          outprf(usrnum);
          usrptr->substt++;
          break;
     case 5:
          prfmsg(INTROD,gamver);
          outprf(usrnum);
          usrptr->substt++;
          break;
     case 6:
          entrgp(0,gmpptr, APPEARFLASH);
          usrptr->substt++;
          break;
     case 7:
          if (gmpptr->macros != 19) {
               gmpptr->macros++;
               kyra();
          }
          else {
               prfmsg(TIRED);
               outprf(usrnum);
          }
          break;
     case 90:
          kyraedit();
          break;
     }
     return(TRUE);
}

static GBOOL
kyrinj(VOID)                       /* Kyrandia injoth() routine handler    */
{
    dftinj();
    btuxmn(othusn,kyratr);
    return(TRUE);
}

VOID
initgp(                            /* initialize player data               */
struct gmplyr *gp,
CHAR *plyrid)                           /* alias id pass through           */
{
     INT tmp;
     INT i;

     tmp=gp->modno;
     usaptr=uacoff(tmp);
     setmem(gp,sizeof(struct gmplyr),0);
     strcpy(gp->uidnam,usaptr->userid);
     strcpy(gp->altnam,plyrid);
     strcpy(gp->attnam,plyrid);
     strcpy(gp->plyrid,plyrid);
     gp->gamloc=-1;
     gp->level=1;
     gp->hitpts=4;
     gp->spts=2;
     gp->modno=(SHORT)tmp;
     gp->flags=(usaptr->sex == 'M' ? 0 : FEMALE);
     if (usaptr->sex == 'M') {
          gp->nmpdes=MDES00;
     }
     else {
          gp->nmpdes=FDES00;
     }
     gp->flags|=LOADED;
     for (i=0 ; i < 4 ; i++) {
          gp->stones[i]=(SHORT)genrdn(0,12);
     }
}

VOID
kyhup(VOID)                        /* Kyrandia hangup routine              */
{
     gmpptr=&gmparr[usrnum];
     if (gmpptr->flags&LOADED) {
          setmbk(kmb);
          dfaSetBlk(kbb);
          if (gmpptr->gamloc != -1) {
               remvgp(gmpptr, "been sucked, screaming, into a dark VOID");
          }
          gi_prep4d(gmpptr);
          dfaGetEQ(NULL,usaptr->userid,0);
          dfaUpdate(gmpptr);
          setmem(gmpptr,sizeof(struct gmplyr),0);
          gmpptr->gamloc=-1;
     }
     if (usroff(usrnum)->state == kyrstt && usroff(usrnum)->substt == 90) {
          kinuse=kyrasub=0;
          free(kyrply);
     }
}

VOID
kydela(                            /* Kyrandia delete account routine      */
CHAR *userid)
{
     dfaSetBlk(kbb);
     if (dfaAcqEQ(NULL,userid,0)) {
          dfaDelete();
     }
}

VOID
kysdn(VOID)                        /* Kyrandia shutdown routine            */
{
     clsmsg(kmb);
     clsmsg(klmb);
     clsmsg(ksmb);
     dfaClose(kbb);
}
