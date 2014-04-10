/********************************************************************\
 * gnc-hbci-utils.h -- hbci utility functions                       *
 * Copyright (C) 2002 Christian Stimming                            *
 *                                                                  *
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation; either version 2 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program; if not, contact:                        *
 *                                                                  *
 * Free Software Foundation           Voice:  +1-617-542-5942       *
 * 59 Temple Place - Suite 330        Fax:    +1-617-542-2652       *
 * Boston, MA  02111-1307,  USA       gnu@gnu.org                   *
\********************************************************************/

#ifndef GNC_HBCI_UTILS_H
#define GNC_HBCI_UTILS_H

#include <glib.h>
#include <gnome.h>
/*#include <openhbci2/account.h>*/
#include <openhbci2/api.h>
#include <openhbci2/transaction.h>
#include "gnc-ui.h"
#include "Account.h"
#include "Transaction.h"
#include "gnc-book.h"

#include "hbci-interaction.h"
#include "gnc-hbci-account.h"


/** Create a new HBCI_API and let it load its environment from the
 * configuration file filename. If the file doesn't exist and
 * allowNewFile is set to FALSE, this function returns NULL. If the
 * file exists, but OpenHBCI encountered an error upon opening, then
 * an error will be displayed, and NULL will be returned. 
 * 
 * @param filename The name of the OpenHBCI configuration file to use.
 * @param allowNewFile If true, non-existent filename is accepted as well.
 * @param parent When displaying dialogs, use this GtkWidget as parent.
 * @param inter Reference to a GNCInteractor-pointer in order to use this later. 
 * May be NULL.
 */
HBCI_API * gnc_hbci_api_new (const char *filename, 
			     gboolean allowNewFile, 
			     GtkWidget *parent,
			     GNCInteractor **inter,
			     GList **list_accounts);

/** Same as above, but takes the filename already from the current
 * book's kvp frame AND caches a pointer to the api. Returns NULL if
 * the file from the book's kvp frame doesn't exist. Returns NULL also
 * when there was an error upon opening that file.
 *
 * @param parent When displaying dialogs, use this GtkWidget as parent.
 * @param inter Reference to a GNCInteractor-pointer in order to use this later. 
 * May be NULL.
 */ 
HBCI_API * gnc_hbci_api_new_currentbook (GtkWidget *parent,
					 GNCInteractor **inter,
					 GList **list_accounts);

/** Delete the given HBCI_API. If this is also the one that was cached
    by gnc_hbci_api_new_currentbook, then that reference is deleted, too. */
void gnc_hbci_api_delete (HBCI_API *api);


/** Save this API to the config file given in the current book. Return
 * an error if one occurred, or if no filename was found in the
 * current book. */
HBCI_Error * gnc_hbci_api_save (const HBCI_API *api);


/* Get the corresponding HBCI account to a gnucash account. Of course
 * this only works after the gnucash account has been set up for HBCI
 * use, i.e. the kvp_frame "hbci/..." have been filled with
 * information. Returns NULL if no gnc_HBCI_Account was found.
 *
 * @param api The HBCI_API to get the gnc_HBCI_Account from.
 * @param gnc_acc The gnucash account to query for gnc_HBCI_Account reference data. */
const gnc_HBCI_Account *
gnc_hbci_get_hbci_acc (const HBCI_API *api, Account *gnc_acc);

/* Return the HBCI return code of the given 'job', or zero if none was
 * found. If 'verbose' is TRUE, make a lot of debugging messages about
 * this outboxjob. */
int
gnc_hbci_debug_outboxjob (HBCI_OutboxJob *job, gboolean verbose);

/* Check HBCI_Error on whether some feedback should be given to the
 * user. Returns true if the HBCI action should be tried again; on the
 * other hand, returns false if the user can't do anything about this
 * error right now. */
gboolean
gnc_hbci_error_retry (GtkWidget *parent, HBCI_Error *error, 
		      GNCInteractor *inter);

/* Calls HBCI_API_executeQueue with some supplementary stuff around
 * it: set the debugLevel, show the GNCInteractor, and do some error
 * checking. Returns TRUE upon success or FALSE if the calling dialog
 * should abort. */
gboolean
gnc_hbci_api_execute (GtkWidget *parent, HBCI_API *api,
		      HBCI_Outbox *queue,
		      HBCI_OutboxJob *job, GNCInteractor *inter);


/* Create the appropriate description field for a Gnucash Transaction
 * by the information given in the HBCI_Transaction h_trans. The
 * returned string must be g_free'd by the caller. */
char *gnc_hbci_descr_tognc (const HBCI_Transaction *h_trans);

/* Create the appropriate memo field for a Gnucash Split by the
 * information given in the HBCI_Transaction h_trans. The returned
 * string must be g_free'd by the caller. */
char *gnc_hbci_memo_tognc (const HBCI_Transaction *h_trans);

/** Return the first customer that can act on the specified account,
    or NULL if none was found (and an error message is printed on
    stdout). */
const HBCI_Customer *
gnc_hbci_get_first_customer(const gnc_HBCI_Account *h_acc);

/** Returns the name of this bank. This function is helpful because it
 * always makes sure to return a valid const char pointer, even if no
 * bankName is available. */
const char *bank_to_str (const HBCI_Bank *bank);

/** Chooses one bank out of the given list. 
 *
 * If the list has more than one bank, this displays a multichoice
 * dialog so that the user can choose one bank. If the list has only
 * one bank, it returns it. If the list has zero banks, it returns
 * NULL. */ 
const HBCI_Bank *
choose_one_bank (gncUIWidget parent, const list_HBCI_Bank *banklist);

/** Chooses one customer out of the given list. 
 *
 * If the list has more than one customer, this displays a multichoice
 * dialog so that the user can choose one customer. If the list has only
 * one customer, it returns it. If the list has zero customers, it returns
 * NULL. */ 
const HBCI_Customer *
choose_one_customer (gncUIWidget parent, const list_HBCI_Customer *custlist);

/** Chooses one user out of the given list. 
 *
 * If the list has more than one user, this displays a multichoice
 * dialog so that the user can choose one user. If the list has only
 * one user, it returns it. If the list has zero users, it returns
 * NULL. */ 
const HBCI_User *
choose_one_user (gncUIWidget parent, const list_HBCI_User *userlist);



#endif