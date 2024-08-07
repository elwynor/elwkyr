/*****************************************************************************
 *                                                                           *
 *   KYRANDIA, Fantasy-world of Legends                     Version 7.20     *
 *                                                                           *
 *   KYROBJR.C (KOBJROUS.C) - Item routines and vector handling              *
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
#undef LEVEL6
#include "elwkyrl.h"

static VOID nohutl(VOID);

VOID
youmsg(                            /* send message to current user         */
INT msgnum)
{
     prfmsg(msgnum);
     outprf(usrnum);
}

VOID
rubber(VOID)                       /* rubbing an item command handling     */
{
     gi_bagthe();
     if (margc == 1) {
          youmsg(OBJM00);
          sndutl("acting silly.");
     }
     else if ((objptr=fgmpobj(margv[1])) == NULL) {
          nohutl();
     }
     else {
          if (objptr->flags&RUBABL) {
               (*(objptr->objrou))();
          }
          else {
               youmsg(OBJM01);
               sndutl("rubbing something.");
          }
     }
}

VOID
thinkr(VOID)                       /* thinking of an item command handling */
{
     bagprep();
     if (margc > 2 && (objptr=fgmpobj("amulet")) != NULL) {
          if (fgamgp(margv[1])) {
               youmsg(OBJM02);
               rstrin();
               prf("A voice in your mind says: %s\r",margv[2]);
               outprf(ogmptr->modno);
               return;
          }
     }
     gi_bagthe();
     if (margc == 1) {
          youmsg(OBJM03);
          sndutl("thinking about life.");
     }
     else if ((objptr=fgmpobj(margv[1])) == NULL) {
          nohutl();
     }
     else {
          if (objptr->flags&THIABL) {
               (*(objptr->objrou))();
          }
          else {
               youmsg(OBJM04);
               sndutl("thinking of %s possesions.");
          }
     }
}

VOID
aimer(VOID)                        /* aiming a item command handling       */
{
     gi_bagthe();
     if (margc == 1) {
          youmsg(OBJM03);
          sndutl("pointing wildly.");
     }
     else if ((objptr=fgmpobj(margv[1])) == NULL) {
          if (pfnlvl > 1) {
               youmsg(OBJM01);
               sndutl("playing with %s body parts!");
          }
          else {
               nohutl();
          }
     }
     else if (margc < 4) {
          youmsg(OBJM05);
          sndutl("waving %s arms.");
     }
     else if (!findgp(margv[3])) {
          youmsg(OBJM06);
          sndutl("seeing ghosts!");
     }
     else {
          if (objptr->flags&AIMABL) {
               (*(objptr->objrou))();
          }
          else {
               youmsg(OBJM04);
               sndutl("waving obscenely!");
          }
     }
}

VOID
drinkr(VOID)                       /* drinking something command handling  */
{
     gi_bagthe();
     if (margc == 1) {
          youmsg(OBJM07);
          sndutl("having a drinking problem.");
     }
     else if ((objptr=fgmpobj(margv[1])) == NULL) {
          nohutl();
     }
     else {
          if (objptr->flags&DRIABL) {
               youmsg(OBJM08);
               sndutl("drinking something quickly.");
               tgmpobj(objno);
               (*(objptr->objrou))();
          }
          else {
               youmsg(OBJM07);
               sndutl("looking thirsty!");
          }
     }
}

static VOID
nohutl(VOID)                       /* doing something to non-existant item */
{
     youmsg(OBJM09);
     sndutl("having wild dreams.");
}
