/*

-Procedure elemc_c ( Element of a character set )

-Abstract
 
   Determine whether an item is an element of a character set. 
 
-Disclaimer

   THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE
   CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S.
   GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE
   ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE
   PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS"
   TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY
   WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A
   PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC
   SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE
   SOFTWARE AND RELATED MATERIALS, HOWEVER USED.

   IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA
   BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT
   LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND,
   INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS,
   REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE
   REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY.

   RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF
   THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY
   CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE
   ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE.

-Required_Reading
 
   SETS 
 
-Keywords
 
   CELLS, SETS 
 
*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #include "SpiceZmc.h"


   SpiceBoolean elemc_c ( ConstSpiceChar  * item,
                          SpiceCell       * set   )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION 
   --------  ---  -------------------------------------------------- 
   item       I   Item to be tested. 
   set        I   Set to be tested. 

   The function returns SPICETRUE if item is an element of set. 
 
-Detailed_Input
 
   item        is an item which may or may not be an element of 
               the input set. Trailing blanks in item are not
               significant.

   set         is a CSPICE set.  set must be declared as a character
               SpiceCell.  Trailing blanks in the members of set are
               not significant.
 
-Detailed_Output
 
   The function returns SPICETRUE if item is a member of the specified
   set, and returns SPICEFALSE otherwise.

   The comparison between item and members of set is case-sensitive.
   Trailing blanks are ignored.
 
-Parameters
 
   None. 
 
-Exceptions
 
   1) If the input set argument does not qualify as a CSPICE set, 
      the error SPICE(NOTASET) will be signaled.  CSPICE sets have
      their data elements sorted in increasing order and contain
      no duplicate data elements.

   2) If the input set does not have character data type, the error
      SPICE(TYPEMISMATCH will be signaled.
 
   3) If the input string pointer is null, the error SPICE(NULLPOINTER)
      is signaled.

-Files
 
   None. 
 
-Particulars
 
   The functions 

      elemc_c
      elemd_c
      elemi_c

   provide a convenient shorthand notation for a binary search
   on a set's data array for the item of interest.
 
-Examples
 
   Let the character sets planets and asteroids contain the 
   following elements. 

      planets            asteroids 
      --------           ---------- 
      "Earth"            "Apollo" 
      "Mars"             "Ceres" 
      "Pluto" 
      "Venus" 

   Then all of the following expressions are SPICETRUE. 

      elemc_c ( "Earth",  &planets   ) 
      elemc_c ( "Pluto",  &planets   ) 
      elemc_c ( "Ceres",  &asteroids ) 

   And all of the following expressions are SPICEFALSE. 

      elemc_c ( "saturn", &planets   ) 
      elemc_c ( "pluto",  &asteroids ) 
      elemc_c ( "ceres",  &asteroids ) 
 
-Restrictions
 
   1) String comparisons performed by this routine are Fortran-style:
      trailing blanks in the input array or key value are ignored.
      This gives consistent behavior with CSPICE code generated by
      the f2c translator, as well as with the Fortran SPICE Toolkit.
      
      Note that this behavior is not identical to that of the ANSI
      C library functions strcmp and strncmp.
 
-Literature_References
 
   None. 
 
-Author_and_Institution
 
   N.J. Bachman    (JPL) 
   C.A. Curzon     (JPL) 
   H.A. Neilan     (JPL) 
   W.L. Taber      (JPL) 
   I.M. Underwood  (JPL) 
 
-Version
 
   -CSPICE Version 1.0.0, 21-AUG-2002 (NJB) (CAC) (HAN) (WLT) (IMU)

-Index_Entries
 
   element of a character set 
 
-&
*/

{ /* Begin elemc_c */


   /*
   Use discovery check-in. 

   Check the input string pointer to make sure it's not null.
   */
   CHKPTR_VAL ( CHK_DISCOVER, "elemc_c", item, SPICEFALSE );


   /*
   Make sure we're working with a character cell. 
   */
   CELLTYPECHK_VAL ( CHK_DISCOVER, "elemc_c", SPICE_CHR, set, SPICEFALSE );


   /*
   Make sure the cell is really a set. 
   */
   CELLISSETCHK_VAL ( CHK_DISCOVER, "elemc_c", set, SPICEFALSE );

 
   /*
   Initialize the set if necessary. 
   */
   CELLINIT ( set );


   /*
   The routine bsrchc_c returns the index of the item in the set,
   or -1 if the item is not present.
   */
   return (  bsrchc_c ( item,         set->card,  
                        set->length,  set->data )   !=   -1   );

} /* End elemc_c */
