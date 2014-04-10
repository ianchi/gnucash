/*
 * gncBusGuile.h -- Business Guile Helper Functions
 * Copyright (C) 2003 Derek Atkins
 * Author: Derek Atkins <warlord@MIT.EDU>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, contact:
 *
 * Free Software Foundation           Voice:  +1-617-542-5942
 * 59 Temple Place - Suite 330        Fax:    +1-617-542-2652
 * Boston, MA  02111-1307,  USA       gnu@gnu.org
 */

#ifndef GNC_BUSINESS_GUILE_H_
#define GNC_BUSINESS_GUILE_H_

#include <gncTaxTable.h>	/* for GncAccountValue */
#include <libguile.h>

int gnc_account_value_pointer_p (SCM arg);
GncAccountValue * gnc_scm_to_account_value_ptr (SCM valuearg);
SCM gnc_account_value_ptr_to_scm (GncAccountValue *);

#endif /* GNC_BUSINESS_GUILE_H_ */
