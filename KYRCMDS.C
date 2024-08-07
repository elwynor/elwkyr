/*****************************************************************************
 *                                                                           *
 *   KYRANDIA, Fantasy-world of Legends                     Version 7.20     *
 *                                                                           *
 *   KYRCMDS.C (KCMDS.C) - Player command array, handler, and routines       *
 *                                                                           *
 *   Designed/Programmed by: Scott Brinker & Richard Skurnick   03/18/88     *
 *                                      6.0 Conversion - E. Bush 3/12/92     *
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
#undef LEVEL6
#include "elwkyrl.h"
#undef LEVEL6
#include "elwkyrs.h"

static VOID whispr(VOID);
static VOID yeller(VOID);
static VOID movutl(INT,CHAR *,CHAR *);
static VOID ponder(VOID);
static VOID kissr1(VOID);
static VOID kissr2(VOID);
static VOID kisutl(INT);
static VOID countr(VOID);
static VOID gldcnt(VOID);
static VOID giveit(VOID);
static VOID givcrd(INT,INT);
static VOID giveru(CHAR *,CHAR *);
static VOID gmsgutl(VOID);
static VOID getter(VOID);
static VOID getgp(CHAR *,CHAR *);
static VOID getloc(CHAR *);
static VOID looker(VOID);
static VOID shover(VOID);
static GBOOL gi_shvutl(CHAR *,CHAR *,INT);
static VOID dropit(VOID);
static VOID winker(VOID);
static VOID flyrou(VOID);
static VOID willof(INT);
static VOID pegasf(INT);
static VOID helper(VOID);
static VOID speakr(VOID);
static VOID briefr(VOID);
static VOID ubrief(VOID);
static VOID reader(VOID);
static VOID scroll(INT);
static VOID prayer(VOID);
static VOID hitctr(VOID);
static GBOOL cmpcmd(VOID);
static GBOOL cmpsmp(VOID);
static VOID smputl(CHAR *,CHAR *,INT);

struct smpwrd {
     CHAR *command;
     CHAR *you;
     CHAR *oth;
     INT speak;
};

struct cmdwrd
gi_cmdarr[]={
     {"?",      helper,  0},
     {"aim",    aimer,   1},
     {"brief",  briefr,  0},
     {"cast",   caster,  1},
     {"chant",  caster,  1},
     {"check",  countr,  0},
     {"comfort",kissr1,  0},
     {"comment",speakr,  0},
     {"concentrate",thinkr,1},
     {"count",  countr,  0},
     {"cuddle", kissr1,  1},
     {"drink",  drinkr,  1},
     {"drop",   dropit,  1},
     {"e",      gi_east, 0},
     {"east",   gi_east, 0},
     {"embrace",kissr1,  1},
     {"examine",looker,  0},
     {"fly",    flyrou,  1},
     {"french", kissr1,  1},
     {"get",    getter,  1},
     {"give",   giveit,  1},
     {"gold",   gldcnt,  0},
     {"grab",   getter,  1},
     {"hand",   giveit,  1},
     {"help",   helper,  0},
     {"hits",   hitctr,  0},
     {"hold",   kissr1,  1},
     {"how?",   ponder,  0},
     {"hug",    kissr2,  0},
     {"inv",    gi_invrou,0},
     {"kick",   kissr2,  1},
     {"kiss",   kissr2,  1},
     {"learn",  memori,  1},
     {"look",   looker,  0},
     {"love",   kissr1,  1},
     {"meditate",thinkr, 1},
     {"memorize",memori, 1},
     {"n",      gi_north,0},
     {"north",  gi_north,0},
     {"note",   speakr,  0},
     {"pass",   giveit,  1},
     {"pickpocket",getter,1},
     {"pilfer", getter,  1},
     {"pinch",  kissr2,  1},
     {"point",  aimer,   1},
     {"pray",   prayer,  1},
     {"punch",  kissr2,  1},
     {"push",   shover,  1},
     {"rape",   kissr1,  1},
     {"read",   reader,  1},
     {"romance",kissr1,  1},
     {"rub",    rubber,  1},
     {"s",      gi_south,0},
     {"say",    speakr,  0},
     {"scream", yeller,  0},
     {"see",    looker,  0},
     {"shout",  yeller,  0},
     {"shove",  shover,  1},
     {"shriek", yeller,  1},
     {"slap",   kissr2,  1},
     {"smack",  kissr2,  1},
     {"smooch", kissr2,  1},
     {"snatch", getter,  1},
     {"south",  gi_south,0},
     {"spells", shwpsp,  0},
     {"squeeze",kissr1,  1},
     {"steal",  getter,  1},
     {"swallow",drinkr,  1},
     {"take",   getter,  1},
     {"think",  thinkr,  1},
     {"tickle", kissr1,  1},
     {"toss",   giveit,  1},
     {"unbrief",ubrief,  0},
     {"w",      gi_west, 0},
     {"west",   gi_west, 0},
     {"what?",  ponder,  0},
     {"where?", ponder,  0},
     {"whisper",whispr,  0},
     {"why?",   ponder,  0},
     {"wink",   winker,  1},
     {"yell",   yeller,  0}
};

struct smpwrd smparr[]={
     {"blink","Blink!","blinking %s eyes in disbelief!",0},
     {"blush","Blush.","blushing and turning bright red!",0},
     {"boo","BOO!","booing and yelling for the hook!",1},
     {"bow","Bow.","bowing rather modestly.",0},
     {"burp","Urrrrp!","belching rudely!",1},
     {"cackle","Cackle, cackle!","cackling frighteningly!",1},
     {"cheer","Rah, rah, rah!","cheering enthusiastically!",1},
     {"chuckle","Heh, heh, heh.","chuckling under %s breath.",1},
     {"clap","Clap, clap.","clapping in admiration.",0},
     {"cough","Ahem.","coughing loud and harshly.",1},
     {"cry","Awwwww.","crying %s little heart out.",1},
     {"dance","How graceful!","dancing with soaring spirits!",0},
     {"fart","Yuck.","emanating a horrible odor.",0},
     {"frown","Frown.","frowning unhappily.",0},
     {"gasp","WOW!","gasping in total amazement!",1},
     {"giggle","Giggle, giggle!","giggling like a hyena.",1},
     {"grin","What a grin!","grinning from ear to ear.",0},
     {"groan","Groan!","groaning with disgust.",1},
     {"growl","Growl!","growling like a rabid bear!",1},
     {"hiss","Hisss!","hissing like an angry snake!",1},
     {"howl","Howl!","howling like a dog in heat!",1},
     {"laugh","What's so funny?","laughing %s head off!",1},
     {"lie","Comfortable?","lying down comfortably.",1},
     {"moan","Moan!","moaning loudly.",1},
     {"nod","Nod.","nodding in agreement.",0},
     {"piss","If you say so.","lifting %s leg strangely.",0},
     {"pout","Wasdamatta?","pouting with tearful eyes.",1},
     {"shit","Find a toilet!","grunting on %s knees.",0},
     {"shrug","Shrug.","shrugging with indifference.",0},
     {"sigh","Sigh.","sighing wistfully.",1},
     {"sing","Lalalala.","singing a cheerful melody.",1},
     {"sit","Ok, now what?","sitting down for a bit.",0},
     {"smile","Smile!","smiling kindly.",0},
     {"smirk","Smirk.","smirking in disdain.",0},
     {"sneeze","Waaacho!","sneezing %s brains out!",0},
     {"snicker","Snicker, snicker.","snickering evily.",1},
     {"sniff","Sniff.","sniffling woefully.",0},
     {"sob","Sob!","sobbing pitifully.",1},
     {"whistle","Whistle.","whistling a faintly familiar tune.",1},
     {"yawn","Aaarhh.","yawning with boredom.",1}
};

#define CARSIZ (sizeof(gi_cmdarr)/sizeof(struct cmdwrd))
#define SARSIZ (sizeof(smparr)/sizeof(struct smpwrd))

static struct cmdwrd *cmdcmp(CHAR *,struct cmdwrd [],INT);
static struct smpwrd *smpcmp(CHAR *,struct smpwrd [],INT);

CHAR_BUFFER(ITSYOURS, 80, "...It's yours!\r");


static VOID
speakr(VOID)                       /* speak command handling               */
{
     if (margc == 1) {
          prfmsg(HUH);
          outprf(usrnum);
          sndutl("opening %s mouth speechlessly.");
     }
     else if (pfnlvl == 3) {
          prfmsg(NOWNOW);
          outprf(usrnum);
          sndutl("foaming at the mouth.");
     }
     else {
          prfmsg(SAIDIT);
          outprf(usrnum);
          prfmsg(SPEAK1,gmpptr->altnam,margv[0]);
          rstrin();
          prfmsg(SPEAK2,margv[1]);
          sndoth();
          prfmsg(SPEAK3);
          sndnear();
     }
}

static VOID
whispr(VOID)                       /* whisper command handling             */
{
     bagprep();
     if (margc < 3) {
          prfmsg(WHAT);
          outprf(usrnum);
          sndutl("looking slightly confused.");
     }
     else if (pfnlvl == 3) {
          prfmsg(WATCHIT);
          outprf(usrnum);
          sndutl("looking a little angry.");
     }
     else {
          if (findgp(margv[1])) {
               rstrin();
               prfmsg(WHISPR1,gmpptr->altnam,margv[2]);
               outprf(ogmptr->modno);
               prfmsg(WHISPR2,ogmptr->plyrid);
               outprf(usrnum);
               prfmsg(WHISPR3,gmpptr->altnam,ogmptr->altnam);
               sndbt2();
          }
          else {
               prfmsg(NOSUCHP);
               outprf(usrnum);
               sndutl("mumbling quietly.");
          }
     }
}

static VOID
yeller(VOID)                       /* yell command handling                */
{
     CHAR *stgptr;

     if (margc == 1) {
          prfmsg(VOICE);
          outprf(usrnum);
          prfmsg(YELLER1,gmpptr->altnam,margv[0],hisher(gmpptr));
          sndoth();
          prfmsg(YELLER2,margv[0]);
          sndnear();
     }
     else {
          prfmsg(YELLER3);
          outprf(usrnum);
          if (pfnlvl < 3) {
               prfmsg(YELLER4,gmpptr->altnam,margv[0]);
               rstrin();
               for (stgptr=margv[1] ; *stgptr != '\0' ; stgptr++) {
                    *stgptr=(CHAR)toupper(*stgptr);
               }
               prfmsg(YELLER5,margv[1]);
               sndoth();
               prfmsg(YELLER6,margv[1]);
               sndnear();
          }
     }
}

VOID
gi_north(VOID)                     /* move a user to the north             */
{
     movutl(gmlptr->gi_north,"moved off to the north","appeared from the south");
}

VOID
gi_south(VOID)                     /* move a user to the south             */
{
     movutl(gmlptr->gi_south,"moved off to the south","appeared from the north");
}

VOID
gi_east(VOID)                      /* move a user to the east              */
{
     movutl(gmlptr->gi_east,"moved off to the east","appeared from the west");
}

VOID
gi_west(VOID)                      /* move a user to the west              */
{
     movutl(gmlptr->gi_west,"moved off to the west","appeared from the east");
}

static VOID
movutl(                            /* generic move a user utility          */
INT dest,
CHAR *rmvtxt,
CHAR *enttxt)
{
     if (dest == -1) {
          prfmsg(MOVUTL);
          outprf(usrnum);
          sndutl("blundering around clumsily.");
     }
     else {
          remvgp(gmpptr,rmvtxt);
          entrgp(dest,gmpptr,enttxt);
     }
}

static VOID
ponder(VOID)                       /* ponder command handling              */
{
     *margv[0]=(CHAR)toupper(*margv[0]);
     prfmsg(PONDER1,margv[0]);
     outprf(usrnum);
     sndutl("looking very philosophical.");
}

static VOID
kissr1(VOID)                       /* call kissing utility with a 0        */
{
     kisutl(0);
}

static VOID
kissr2(VOID)                       /* call kissing utility with a 1        */
{
     kisutl(1);
}

static VOID
kisutl(                            /* general purpose kissing utility      */
INT mode)
{
     gi_bagthe();
     if (margc == 1) {
          prfmsg(KISUTL1,upperc(margv[0]));
          outprf(usrnum);
          sndutl("making strange motions.");
     }
     else if ((objptr=fgmpobj(margv[1])) != NULL) {
          prfmsg(KISUTL2,margv[0],dobutl(objptr));
          outprf(usrnum);
          prfmsg(KISUTL3,gmpptr->altnam);
          if (mode) {
               prfmsg(KISUTL4,hisher(gmpptr),objptr->name,margv[0]);
          }
          else {
               prfmsg(KISUTL5,margv[0],hisher(gmpptr),objptr->name);
          }
          sndoth();
     }
     else if ((objptr=fgmlobj(margv[1])) != NULL) {
          if (sameto(margv[1],"dryad") && dloc == gmpptr->gamloc && mode) {
               prfmsg(UKISSD,margv[0]);
               outprf(usrnum);
               prfmsg(OKISSD,gmpptr->altnam,margv[0],himher(gmpptr),margv[0]);
               sndoth();
          }
          else {
               prfmsg(KISUTL6,margv[0],dobutl(objptr));
               outprf(usrnum);
               prfmsg(KISUTL7,gmpptr->altnam);
               if (mode) {
                    prfmsg(KISUTL8,objptr->name,gmlptr->objlds,margv[0]);
               }
               else {
                    prfmsg(KISUTL9,margv[0],objptr->name,gmlptr->objlds);
               }
               sndoth();
          }
     }
     else if (findgp(margv[1])) {
          if (mode) {
               if (sameas(ogmptr->plyrid,gmpptr->spouse)
                && sameas(margv[0],"kiss")) {
                    prfmsg(SKISSR,ogmptr->plyrid,himher(ogmptr));
                    outprf(usrnum);
                    prfmsg(SKISSU,gmpptr->altnam,hisher(gmpptr));
                    outprf(ogmptr->modno);
                    prfmsg(SKISSO,gmpptr->altnam,ogmptr->altnam,hisher(gmpptr),
                         himher(ogmptr));
                    sndbt2();
               }
               else {
                    prfmsg(DONE);
                    outprf(usrnum);
                    prfmsg(KISUTL10,gmpptr->altnam,margv[0]);
                    outprf(ogmptr->modno);
                    prfmsg(KISUTL11,gmpptr->altnam,ogmptr->altnam,margv[0]);
                    sndbt2();
               }
          }
          else {
               prfmsg(BEST);
               outprf(usrnum);
               prfmsg(KISUTL12,gmpptr->altnam,hisher(gmpptr),margv[0]);
               outprf(ogmptr->modno);
               prfmsg(KISUTL13,gmpptr->altnam,hisher(gmpptr),margv[0],ogmptr->altnam);
               sndbt2();
          }
     }
     else {
          prfmsg(KISUTL14);
          outprf(usrnum);
          sndutl("seeing things!");
     }
}

static VOID
countr(VOID)                       /* count command handling               */
{
     if (margc == 1) {
          prfmsg(COUNTR1);
          outprf(usrnum);
     }
     else if (sameas(margv[1],"gold")) {
          gldcnt();
     }
     else {
          prfmsg(COUNTR2);
          outprf(usrnum);
     }
}

static VOID
gldcnt(VOID)                       /* display gold counted                 */
{
     prfmsg(GLDCNT,gmpptr->gold,(gmpptr->gold == 1 ? "" : "s"));
     outprf(usrnum);
     sndutl("counting %s gold!");
}

static VOID
giveit(VOID)                       /* give command handling                */
{
     gi_bagthe();
     bagwrd("pieces");
     if (margc == 5 && sameto(margv[2],"gold") && sameas(margv[3],"to")) {
          givcrd(1,4);
     }
     else if (margc == 4 && sameto(margv[3],"gold")) {
          givcrd(2,1);
     }
     else if (margc == 3) {
          giveru(margv[1],margv[2]);
     }
     else if (margc == 4 && sameas(margv[2],"to")) {
          giveru(margv[3],margv[1]);
     }
     else {
          prfmsg(GIVIT1);
          outprf(usrnum);
          sndutl("fumbling around foolishly.");
     }
}

static VOID
givcrd(                            /* give gold to someone                 */
INT amt,
INT who)
{
     INT goldps;

     if ((goldps=atoi(margv[amt])) < 0) {
          prfmsg(GIVCRD1);
          outprf(usrnum);
          sndutl("concentrating with difficulty.");
     }
     else if (goldps > gmpptr->gold) {
          prfmsg(GIVCRD2);
          outprf(usrnum);
          sndutl("dreaming of great wealth.");
     }
     else if (!findgp(margv[who])) {
          prfmsg(GIVCRD3);
          outprf(usrnum);
          sndutl("looking rather puzzled");
     }
     else {
          prfmsg(GIVCRD4);
          outprf(usrnum);
          prfmsg(GIVCRD5,gmpptr->altnam,goldps,(goldps == 1 ? "" : "s"));
          outprf(ogmptr->modno);
          prfmsg(GIVCRD6,gmpptr->altnam,ogmptr->altnam,goldps,(goldps == 1 ? "" : "s"));
          sndbt2();
          gmpptr->gold-=(USHORT)goldps;
          ogmptr->gold+=(USHORT)goldps;
     }
}

static VOID
giveru(                            /* handle transfering an item           */
CHAR *givee,
CHAR *givwhat)
{
     INT value;
     struct gamobj *obj2;

     if (!findgp(givee)) {
          prfmsg(GIVERU1,upperc(givee));
          outprf(usrnum);
          sndutl("having hallucinations.");
     }
     else if (gmpptr == ogmptr) {
          prfmsg(GIVERU2);
          outprf(usrnum);
          sndutl("scratching %s rear end.");
     }
     else if ((objptr=fgmpobj(givwhat)) == NULL) {
          prfmsg(GIVERU3);
          outprf(usrnum);
          sndutl("searching %s pockets frantically!");
     }
     else if (ogmptr->npobjs >= MXPOBS) {
          if (gmlptr->nlobjs >= MXLOBS) {
               prfmsg(GIVERU4);
               outprf(usrnum);
               sndutl("wrestling with supernatural powers!");
          }
          else if ((txt_rnd()&0x01) == 0) {
               prfmsg(GIVERU5);
               outprf(usrnum);
               tgmpobj(objno);
               pgmlobj(objptr);
               prfmsg(GIVERU6,gmpptr->altnam,hisher(gmpptr),objptr->name);
               sndoth();
          }
          else {
               value=gmpptr->obvals[objno];
               obj2=ogmptr->gpobjs[0];
               takpobj(ogmptr,0);                 /* take from 2nd guy */
               tgmpobj(objno);                    /* take from 1st guy */
               putpobj(ogmptr,objptr,value);      /* give 2nd's 1st's */
               prfmsg(GIVERU7,himher(ogmptr),hisher(ogmptr),obj2->name);
               outprf(usrnum);
               gmsgutl();
               prfmsg(GIVERU8,dobutl(objptr),obj2->name);
               outprf(ogmptr->modno);
               gmsgutl();
               prfmsg(GIVERU9,ogmptr->altnam,dobutl(objptr),himher(ogmptr),
                    hisher(ogmptr),obj2->name);
               sndbt2();
               pgmlobj(obj2);
          }
     }
     else {
          value=gmpptr->obvals[objno];
          tgmpobj(objno);                    /* take from 1st guy */
          putpobj(ogmptr,objptr,value);      /* give 2nd's 1st's */
          prfmsg(DONE);
          outprf(usrnum);
          gmsgutl();
          prfmsg(GIVERU10,dobutl(objptr));
          outprf(ogmptr->modno);
          gmsgutl();
          prfmsg(GIVERU11,ogmptr->altnam,dobutl(objptr));
          sndbt2();
     }
}

static VOID
gmsgutl(VOID)                      /* display give messages                */
{
     prfmsg(GMSGUTL1,gmpptr->altnam);
     if (strcmp(margv[0],"give") == 0) {
          prfmsg(GMSGUTL2);
     }
     else {
          prfmsg(GMSGUTL3,margv[0]);
     }
}

static VOID
getter(VOID)                       /* getting something from a user        */
{
     gi_bagthe();
     if (margc == 2) {
          getloc(margv[1]);
     }
     else if (margc == 3 && sameas(margn[1]-2,"'s")) {
          *(margn[1]-2)='\0';
          getgp(margv[1],margv[2]);
     }
     else if (margc == 4 && sameto(margv[2],"from")) {
          getgp(margv[3],margv[1]);
     }
     else {
          prfmsg(GETTER);
          outprf(usrnum);
          sndutl("freaking out!");
     }
}

static VOID
getgp(                             /* grab something from a user           */
CHAR *who,
CHAR *what)
{
     INT value;

     if (!findgp(who)) {
          prfmsg(GETGP1);
          outprf(usrnum);
          sndutl("rubbing %s eyes.");
     }
     else if (gmpptr == ogmptr) {
          prfmsg(GETGP2);
          outprf(usrnum);
          sndutl("scratching %s rear end.");
     }
     else if ((objptr=fndpobj(ogmptr,what)) == NULL) {
          prfmsg(GETGP3,ogmptr->altnam,what);
          outprf(usrnum);
          sndutl("looking very suspicious!");
     }
     else if (gmpptr->npobjs >= MXPOBS) {
          prfmsg(GETGP4);
          outprf(usrnum);
          sndutl("fumbling around with %s stuff.");
     }
     else if ((txt_rnd()&0x0E) != 0) {
          prfmsg(GETGP5);
          outprf(usrnum);
          prfmsg(GETGP6,gmpptr->altnam,margv[0],objptr->name);
          outprf(ogmptr->modno);
          prfmsg(GETGP7,gmpptr->altnam,margv[0],ogmptr->altnam,objptr->name);
          sndbt2();
     }
     else {
          value=ogmptr->obvals[objno];
          takpobj(ogmptr,objno);
          pgmpobj(objptr,value);
          prfmsg(GETGP8);
          outprf(usrnum);
          prfmsg(GETGP9,gmpptr->altnam,objptr->name);
          outprf(ogmptr->modno);
          prfmsg(GETGP10,gmpptr->altnam,ogmptr->altnam,objptr->name);
          sndbt2();
     }
}

static VOID
getloc(                            /* try getting something or someone     */
CHAR *what)
{
     if (findgp(margv[1])) {
          prfmsg(GETLOC1,ogmptr->altnam);
          outprf(usrnum);
          prfmsg(GETLOC2,gmpptr->altnam,margv[0]);
          outprf(ogmptr->modno);
          prfmsg(GETLOC3,gmpptr->altnam,margv[0],ogmptr->altnam);
          sndbt2();
     }
     else if ((objptr=fgmlobj(what)) == NULL) {
          prfmsg(GETLOC4,what,gmlptr->objlds);
          outprf(usrnum);
          sndutl("beyond all hope.");
     }
     else if (!(objptr->flags&PICKUP)) {
          prfmsg(objptr->auxmsg);
          outprf(usrnum);
          prfmsg(GETLOC5,gmpptr->altnam,margv[0],objptr->name);
          sndoth();
     }
     else if (gmpptr->npobjs >= MXPOBS) {
          prfmsg(GETLOC6);
          outprf(usrnum);
          sndutl("looking very greedy.");
     }
     else {
          tgmlobj(objno);
          pgmpobj(objptr,0);
          btuxmt(usrnum,ITSYOURS);
          prfmsg(GETLOC7,gmpptr->altnam,objptr->name,gmlptr->objlds);
          sndoth();
     }
}

static VOID
looker(VOID)                       /* look command handling                */
{
     gi_bagthe();
     bagprep();
     if (margc >= 2 && (objptr=fgmlobj(margv[1])) != NULL) {
          prfmsg(objptr->objdes);
          outprf(usrnum);
          prfmsg(LOOKER1,gmpptr->altnam,objptr->name,gmlptr->objlds);
          sndoth();
     }
     else if (margc >= 2 && (objptr=fgmpobj(margv[1])) != NULL) {
          prfmsg(objptr->objdes);
          outprf(usrnum);
          prfmsg(LOOKER2,gmpptr->altnam,hisher(gmpptr),objptr->name);
          sndoth();
     }
     else if (margc >= 2 && findgp(margv[1])) {
          if (ogmptr->flags&INVISF) {
               prfmsg(INVDES);
          }
          else if (ogmptr->flags&WILLOW) {
               prfmsg(WILDES);
          }
          else if (ogmptr->flags&PEGASU) {
               prfmsg(PEGDES);
          }
          else if (ogmptr->flags&PDRAGN) {
               prfmsg(PDRDES);
          }
          else {
               prfmsg(ogmptr->nmpdes,ogmptr->plyrid);
               gi_invutl(ogmptr,0);
          }
          outprf(usrnum);
          prfmsg(LOOKER3,gmpptr->altnam);
          outprf(ogmptr->modno);
          prfmsg(LOOKER4,gmpptr->altnam,ogmptr->altnam);
          sndbt2();
     }
     else if (margc >= 2 && sameto(margv[1],"brief")) {
          prfmsg(LOOKER5,gmlptr->brfdes);
          locobjs(gmpptr->gamloc);
          locogps(gmpptr);
          outprf(usrnum);
          sndutl("glancing around briefly!");
     }
     else if (margc >=  2 && sameto(margv[1],"spellbook")) {
          seesbk();
     }
     else {
          setmbk(klmb);
          prfmsg(lcrptr->londes);
          setmbk(kmb);
          locobjs(gmpptr->gamloc);
          locogps(gmpptr);
          outprf(usrnum);
          sndutl("carefully inspecting the surroundings.");
     }
}

static VOID
shover(VOID)                       /* shove a user command handling        */
{
     gi_bagthe();
     bagprep();
     if (margc == 2) {
          kissr2();
     }
     else if (margc == 3) {
          if (findgp(margv[1])) {
               if (sameto(margv[2],"north")
                 && gi_shvutl("south","north",gmlptr->gi_north)) {
               }
               else if (sameto(margv[2],"south")
                 && gi_shvutl("north","south",gmlptr->gi_south)) {
               }
               else if (sameto(margv[2],"east")
                 && gi_shvutl("west","east",gmlptr->gi_east)) {
               }
               else if (sameto(margv[2],"west")
                 && gi_shvutl("east","west",gmlptr->gi_west)) {
               }
               else {
                    sndutl("having hallucinations.");
                    prfmsg(SHOVER1,margv[2]);
                    outprf(usrnum);
               }
          }
          else {
               sndutl("seeing things.");
               prfmsg(SHOVER2,margv[1]);
               outprf(usrnum);
          }
     }
     else {
          sndutl("having a medical emergency!");
          prfmsg(SHOVER3);
          outprf(usrnum);
     }
}

static GBOOL
gi_shvutl(                         /* handle processing the shove          */
CHAR *from,
CHAR *to,
INT dir)
{
     if (dir != -1) {
          prfmsg(SHVUTL1,ogmptr->plyrid);
          outprf(usrnum);
          gmpptr->pgploc=gmpptr->gamloc;
          gmpptr->gamloc=-1;
          remvgp(ogmptr,spr("been shoved %s by %s",to,gmpptr->altnam));
          gmpptr->gamloc=gmpptr->pgploc;
          prfmsg(SHVUTL2,gmpptr->altnam,to);
          outprf(ogmptr->modno);
          entrgp(dir,ogmptr,spr("been shoved from the %s",from));
          return(TRUE);
     }
     return(FALSE);
}

static VOID
dropit(VOID)                       /* drop something command handling      */
{
     gi_bagthe();
     if (margc >= 2) {
          if ((objptr=fgmpobj(margv[1])) != NULL) {
               if (gmlptr->nlobjs >= MXLOBS) {
                    prfmsg(DROPIT1);
                    outprf(usrnum);
                    sndutl("struggling with the air!");
               }
               else {
                    tgmpobj(objno);
                    pgmlobj(objptr);
                    prfmsg(DROPIT2);
                    outprf(usrnum);
                    prfmsg(DROPIT3,gmpptr->altnam,hisher(gmpptr),objptr->name,gmlptr->objlds);
                    sndoth();
               }
          }
          else {
               prfmsg(DROPIT4);
               outprf(usrnum);
               sndutl("acting very oddly.");
          }
     }
     else {
          prfmsg(DROPIT5);
          outprf(usrnum);
          sndutl("looking a little queer!");
     }
}

static VOID
winker(VOID)                       /* wink command handling                */
{
     bagprep();
     if (margc == 1) {
          prfmsg(WINKER1);
          outprf(usrnum);
          sndutl("winking with a grin.");
     }
     else if (findgp(margv[1])) {
          prfmsg(WINKER2);
          outprf(usrnum);
          prfmsg(WINKER3,gmpptr->altnam);
          outprf(ogmptr->modno);
          prfmsg(WINKER4,gmpptr->altnam,ogmptr->altnam);
          sndbt2();
     }
     else {
          prfmsg(WINKER5);
          outprf(usrnum);
          sndutl("winking at imaginary lovers.");
     }
}

static VOID
flyrou(VOID)                       /* fly command handling                 */
{
     if (gmpptr->flags&WILLOW) {
          if (gmpptr->gamloc == 179) {
               willof(180);
          }
          else if (gmpptr->gamloc == 180) {
               willof(179);
          }
          else {
               msgutl2(UNOFLY,ATFLY1);
          }
          return;
     }
     if (gmpptr->flags&PEGASU) {
          if (gmpptr->gamloc == 22) {
               pegasf(189);
          }
          else if (gmpptr->gamloc == 189) {
               pegasf(22);
          }
          else {
               msgutl2(UNOFLY,ATFLY1);
          }
          return;
     }
     if (gmpptr->flags&PDRAGN) {
          msgutl2(UNOFLY,ATFLY1);
          return;
     }
     msgutl2(HUNFLY,ATFLY1);
}

static VOID
willof(                            /* Will-O-Wisp flying routine           */
INT dest)
{
     prfmsg(WILFLY);
     outprf(usrnum);
     remvgp(gmpptr,"gracefully flown across the chasm");
     entrgp(dest,gmpptr,"gracefully flown from across the chasm");
}

static VOID
pegasf(                            /* Pegasus flying routine               */
INT dest)
{
     prfmsg(PEGFLY);
     outprf(usrnum);
     remvgp(gmpptr,"majestically flown across the sea");
     entrgp(dest,gmpptr,"majestically flown from across the sea");
}

static VOID
helper(VOID)                       /* display a help message               */
{
     if (margc > 1) {
          switch (toupper(*margv[1])) {
          case 'C':
               prfmsg(HLPCOM);
               break;
          case 'F':
               prfmsg(HLPFAN);
               break;
          case 'G':
               prfmsg(HLPGOL);
               break;
          case 'H':
               prfmsg(HLPHIT);
               break;
          case 'L':
               prfmsg(HLPLEV);
               break;
          case 'S':
               prfmsg(HLPSPE);
               break;
          case 'W':
               prfmsg(HLPWIN);
               break;
          default:
               rstrin();
               prfmsg(NOHELP,margv[1]);
          }
     }
     else {
          prfmsg(HLPMSG);
     }
     outprf(usrnum);
}

static VOID
briefr(VOID)                       /* "brief" command handling             */
{
     if (margc == 1 || sameas(margv[1],"on")) {
          gmpptr->flags|=BRFSTF;
          prfmsg(BRIEFR1);
          outprf(usrnum);
     }
     else if (margc == 2 && sameas(margv[1],"off")) {
          ubrief();
     }
     else {
          prfmsg(BRIEFR2);
          outprf(usrnum);
     }
}

static VOID
ubrief(VOID)                       /* turn brief mode off                  */
{
     gmpptr->flags&=~BRFSTF;
     prfmsg(UNBRIEF);
     outprf(usrnum);
}

static VOID
reader(VOID)                       /* handle reading something (spellbook) */
{
     gi_bagthe();
     if (!sameas(margv[1],"spellbook")) {
          if ((objptr=fgmpobj(margv[1])) != NULL) {
               if (objptr->flags&REDABL) {
                    tgmpobj(objno);
                    scroll((INT)(objptr-gmobjs));
               }
               else {
                    prfmsg(READER1,dobutl(objptr));
                    outprf(usrnum);
                    sndutl("having severe eye problems.");
               }
          }
          else {
               prfmsg(READER2);
               outprf(usrnum);
               sndutl("is suffering from mental instability.");
          }
     }
     else {
          looker();
     }
}

static VOID
scroll(                            /* do something with a magical scroll   */
INT wch)
{
     INT s;
     INT h;
     INT surpri;
     struct spell *sptr;
     CHAR item[10];

     switch (wch) {
     case 35:
          strcpy(item,"scroll");
          break;
     case 36:
          strcpy(item,"codex");
          break;
     case 37:
          strcpy(item,"tome");
          break;
     case 38:
          strcpy(item,"parchment");
          break;
     }
     prfmsg(SCROLL1,gmpptr->altnam,hisher(gmpptr),item);
     sndoth();
     if ((s=genrdn(0,111)) < 67) {
          sptr=&spells[s];
          prfmsg(URSCRL,item,sptr->name);
          outprf(usrnum);
          switch (sptr->sbkref) {
          case 1:
               gmpptr->offspls|=sptr->bitdef;
               break;
          case 2:
               gmpptr->defspls|=sptr->bitdef;
               break;
          case 3:
               gmpptr->othspls|=sptr->bitdef;
               break;
          }
     }
     else {
          switch ((genrdn(0,8))) {
          case 0:
               gmpptr->nspells=0;
               prfmsg(SCRLM0,item);
               break;
          case 1:
               gmpptr->npobjs=0;
               prfmsg(SCRLM1,item);
               break;
          case 2:
               gmpptr->gold=0;
               prfmsg(SCRLM2,item);
               break;
          case 3:
               gmpptr->spts=0;
               prfmsg(SCRLM3,item);
               break;
          case 4:
               surpri=genrdn(0,169);
               prfmsg(SCRLM4,item);
               outprf(usrnum);
               remvgp(gmpptr,"vanished with a look of surprise");
               entrgp(surpri,gmpptr,"appeared with a look of surprise");
               prfmsg(SCRLM42);
               break;
          case 5:
               prfmsg(SCRLM5,item);
               outprf(usrnum);
               pgmpobj(&gmobjs[30],0);
               break;
          case 6:
               surpri=genrdn(36,38);
               prfmsg(SCRLM6,item,(surpri == 36 ? "codex" : "tome"));
               outprf(usrnum);
               pgmpobj(&gmobjs[surpri],0);
               break;
          default:
               h=genrdn(2,11);
               prfmsg(SCRLM7,item,h);
               ogmptr=gmpptr;
               hitoth(h);
          }
          outprf(usrnum);
     }
}

static VOID
prayer(VOID)                       /* prayer command handling              */
{
     prfmsg(PRAYER);
     outprf(usrnum);
     sndutl("praying piously.");
}

static VOID
hitctr(VOID)                       /* display health                       */
{
     prfmsg(HITCTR,gmpptr->hitpts,(4*gmpptr->level));
     outprf(usrnum);
     sndutl("checking %s health.");
}


static struct cmdwrd *
cmdcmp(                            /* find command from command arrary     */
CHAR *stgptr,
struct cmdwrd table[],
INT length)
{
     INT cond;
     struct cmdwrd *low;
     struct cmdwrd *mid;
     struct cmdwrd *high;

     low=&table[0];
     high=&table[length-1];
     while (low <= high) {
          mid=low+((INT)(high-low))/2;
          if ((cond=strcmp(stgptr,mid->command)) < 0) {
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

static struct smpwrd *
smpcmp(                            /* find simple command from cmd array   */
CHAR *stgptr,
struct smpwrd table[],
INT length)
{
     INT cond;
     struct smpwrd *low;
     struct smpwrd *mid;
     struct smpwrd *high;

     low=&table[0];
     high=&table[length-1];
     while (low <= high) {
          mid=low+((INT)(high-low))/2;
          if ((cond=strcmp(stgptr,mid->command)) < 0) {
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

VOID
kyra(VOID)                         /* kyrandia main command handler        */
{
     CHAR *mv0ptr;

     if (margc == 0) {
          prf(kyratr);
          if (usrptr->flags&ABOIP) {
               prf("\r");
          }
          else {
               prfmsg(KYRA1);
          }
          outprf(usrnum);
     }
     else {
          gmlptr=&gmlocs[gmpptr->gamloc];
          lcrptr=&lcrous[gmpptr->gamloc];
          for (mv0ptr=margv[0] ; *mv0ptr != '\0' ; mv0ptr++) {
               *mv0ptr=(CHAR)tolower(*mv0ptr);
          }
          if ((*(lcrptr->locrou))()) {
               if (!cmpcmd()) {
                    if (!cmpsmp()) {
                         if (*margv[0] == 'i') {
                              prfmsg(KYRA2);
                         }
                         else if (strcmp(margv[0],"because") == 0) {
                              prfmsg(KYRA3);
                         }
                         else if (pfnlvl > 1) {
                              prfmsg(KYRA4);
                         }
                         else if (usrptr->flags&MASTER
                           && sameas(margv[0],"menu")) {
                              if (kinuse == 1) {
                                   setmbk(ksmb);
                                   prfmsg(KINUSE);
                                   outprf(usrnum);
                                   setmbk(kmb);
                              }
                              else {
                                   remvgp(gmpptr,
                                        "been summoned by the Goddess Tashana");
                                   btupmt(usrnum,0);
                                   kyraedit();
                              }
                         }
                         else {
                              rstrin();
                              switch (margc) {
                              case 1:
                                   prfmsg(KYRA5,margv[0]);
                                   break;
                              case 2:
                                   prfmsg(KYRA6,margv[0]);
                                   break;
                              case 3:
                                   prfmsg(KYRA7,margv[0]);
                                   break;
                              case 4:
                                   prfmsg(KYRA8,margv[0]);
                                   break;
                              default:
                                   prfmsg(KYRA9);
                              }
                         }
                         outprf(usrnum);
                         sndutl("mumbling under %s breath.");
                    }
               }
          }
     }
}

static GBOOL
cmpcmd(VOID)                       /* call specific command handler if ok  */
{
     struct cmdwrd *cmdptr;

     if ((cmdptr=cmdcmp(margv[0],gi_cmdarr,CARSIZ)) != NULL) {
          if (cmdptr->payonl && !hasmkey(KYRKEY) && !(usrptr->flags&MASTER)) {
               prfmsg(CMPCMD1);
               outprf(usrnum);
          }
          else {
               (*(cmdptr->cmdrou))();
          }
          return(TRUE);
     }
     return(FALSE);
}

static GBOOL
cmpsmp(VOID)                       /* call simple command handler if ok    */
{
     struct smpwrd *smpptr;

     if ((smpptr=smpcmp(margv[0],smparr,SARSIZ)) != NULL) {
          smputl(smpptr->you,smpptr->oth,smpptr->speak);
          return(TRUE);
     }
     return(FALSE);
}

static VOID
smputl(                            /* perform simple command               */
CHAR *you,
CHAR *them,
INT speak)
{
     if (speak && margc > 1) {
          speakr();
     }
     else {
          prfmsg(SMPUTL1,you);
          outprf(usrnum);
          prfmsg(SMPUTL2,gmpptr->altnam,spr(them,hisher(gmpptr)));
          sndoth();
     }
}
