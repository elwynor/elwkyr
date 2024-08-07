/*****************************************************************************
 *                                                                           *
 *   KYRANDIA, Fantasy-world of Legends                     Version 7.20     *
 *                                                                           *
 *   KYRPROT.C (KRIGHTS.C) - Load/Save data structures                       *
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

CHAR *cright[4]={
     "       Multi-player Gaming System",
     "    Copyright (C) 1988-95 Galacticomm",
     "Copyright (C) 2005-24 Elwynor Technologies"
     "           All rights reserved."
};



INT
loadkp(VOID)                       /* load player data from btrieve file   */
{
     return(dfaAcqEQ(gmpptr,usaptr->userid,0));
}

VOID
rights(VOID)                       /* display copyright & put user in game */
{
     INT i;

     gmpptr->modno=(SHORT)usrnum;
     gi_rest4p(gmpptr);
     prf("\r");
     for (i=0 ; i < 4 ; i++) {
          prf("%s\r",cright[i]);
     }
     prf("\r");
     gi_invrou();
     if (usrptr->flags&MASTER) {
          entrgp(gmpptr->pgploc,gmpptr,
              "arrived in the arms of the Goddess Tashanna");
     }
     else {
          entrgp(gmpptr->pgploc,gmpptr,
              "appeared in a crackling flash of purple lightning");
     }
     usrptr->substt=7;
}

VOID
gi_prep4d(                         /* prepare data to be saved to disk     */
struct gmplyr *gp)
{
     INT i;

     for (i=0 ; i < gp->npobjs ; i++) {
          gp->gpobjs[i]=(struct gamobj *)(gp->gpobjs[i]-gmobjs);
     }
     for (i=0 ; i < gp->nspells ; i++) {
          gp->spells[i]=(struct spell *)(gp->spells[i]-spells);
     }
}

VOID
gi_rest4p(                         /* prepare disk data for online use     */
struct gmplyr *gp)
{
     INT i;

     for (i=0 ; i < gp->npobjs ; i++) {
          gp->gpobjs[i]=&gmobjs[(INT)gp->gpobjs[i]];
     }
     for (i=0 ; i < gp->nspells ; i++) {
          gp->spells[i]=&spells[(INT)gp->spells[i]];
     }
}
