/*****************************************************************************
 *                                                                           *
 *    KYRANDIA, Fantasy-world of Legends                     Version 7.20    *
 *                                                                           *
 *    KYRSPLS.H (KSPELLS.H) - bit flag definitions for game spells           *
 *                                                                           *
 *    Designed/Programmed by: Scott Brinker & Richard Skurnick   03/18/88    *
 *                                                                           *
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

#define SBD001   0x00000001L  /* other pro II(scry,tel,etc) */
#define SBD002   0x00000002L  /* ultimate heal              */
#define SBD003   0x00000001L  /* destroy one item           */
#define SBD004   0x00000002L  /* destroy all items          */
#define SBD005   0x00000004L  /* zap other's spell book     */
#define SBD006   0x00000001L  /* fireball I                 */
#define SBD007   0x00000004L  /* other pro I (scry,tel,etc) */
#define SBD008   0x00000008L  /* invisibility I             */
#define SBD009   0x00000010L  /* ultimate protection I      */
#define SBD010   0x00000002L  /* ice storm II               */
#define SBD011   0x00000008L  /* make player drop all items */
#define SBD012   0x00000010L  /* detect power (spell pts)   */
#define SBD013   0x00000020L  /* forget all spells          */
#define SBD014   0x00000040L  /* teleport random            */
#define SBD015   0x00000020L  /* heal III                   */
#define SBD016   0x00000080L  /* transform into pegasus     */
#define SBD017   0x00000004L  /* firebolt I                 */
#define SBD018   0x00000008L  /* ice ball II                */
#define SBD019   0x00000010L  /* cone of cold II            */
#define SBD020   0x00000020L  /* ice ball I                 */
#define SBD021   0x00000040L  /* firebolt III               */
#define SBD022   0x00000080L  /* lightning bolt II          */
#define SBD023   0x00000100L  /* teleport specific          */
#define SBD024   0x00000200L  /* transform into psuedo drag */
#define SBD025   0x00000040L  /* object protection I        */
#define SBD026   0x00000080L  /* ice protection II          */
#define SBD027   0x00000100L  /* lightning storm            */
#define SBD028   0x00000400L  /* dispel magic               */
#define SBD029   0x00000200L  /* lightning bolt III         */
#define SBD030   0x00000400L  /* lightning ball             */
#define SBD031   0x00000800L  /* fireball II                */
#define SBD032   0x00001000L  /* firebolt II                */
#define SBD033   0x00000100L  /* ice protection I           */
#define SBD034   0x00000800L  /* detect health (hit points) */
#define SBD035   0x00000200L  /* fire protection II         */
#define SBD036   0x00000400L  /* ultimate protection II     */
#define SBD037   0x00002000L  /* ice storm I                */
#define SBD038   0x00001000L  /* see invisibility II        */
#define SBD039   0x00002000L  /* see invisibility I         */
#define SBD040   0x00004000L  /* cone of cold I             */
#define SBD041   0x00000800L  /* object protection II       */
#define SBD042   0x00004000L  /* destroy things on ground   */
#define SBD043   0x00001000L  /* heal I                     */
#define SBD044   0x00008000L  /* read other's spells        */
#define SBD045   0x00002000L  /* invisibility II            */
#define SBD046   0x00010000L  /* scry someone               */
#define SBD047   0x00020000L  /* steal a player's item      */
#define SBD048   0x00008000L  /* magic missile              */
#define SBD049   0x00004000L  /* ice protection III         */
#define SBD050   0x00010000L  /* sap spell points II        */
#define SBD051   0x00040000L  /* forget one spell           */
#define SBD052   0x00020000L  /* fire storm                 */
#define SBD053   0x00008000L  /* fire protection I          */
#define SBD054   0x00040000L  /* cone of cold III           */
#define SBD055   0x00010000L  /* lightning protection I     */
#define SBD056   0x00020000L  /* lightning protection III   */
#define SBD057   0x00080000L  /* sap spell points I         */
#define SBD058   0x00040000L  /* heal II                    */
#define SBD059   0x00100000L  /* earthquake                 */
#define SBD060   0x00080000L  /* lightning protection II    */
#define SBD061   0x00200000L  /* fireball III               */
#define SBD062   0x00080000L  /* transform into willowisp   */
#define SBD063   0x00100000L  /* location finder            */
#define SBD064   0x00100000L  /* fire protection III        */
#define SBD065   0x00200000L  /* detect true idenity        */
#define SBD066   0x00400000L  /* lightning bolt I           */
#define SBD067   0x00800000L  /* ariel servant              */
