/*
 * WengoPhone, a voice over Internet phone
 * Copyright (C) 2004-2006  Wengo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "PurpleAccountMngr.h"
#include "PurplePresenceMngr.h"
#include "PurpleChatMngr.h"
#include "PurpleConnectMngr.h"
#include "PurpleContactListMngr.h"
#include "PurpleIMFactory.h"

#include <util/Logger.h>

typedef struct misc_s
{
	void * data_ptr1;
	void * data_ptr2;
	int cbk_id;
}	misc_t;

void *purple_wg_get_handle()
{
	static int handle;

	return &handle;
}

/* ***************** PURPLE CALLBACK ***************** */
static void C_NotifyAddedCbk(PurpleAccount *account, const char *remote_user,
							const char *id, const char *alias,
							const char *message)
{
	PurpleAccountMngr::NotifyAddedCbk(account, remote_user, id, alias, message);
}

static void C_RequestAddCbk(PurpleAccount *account, const char *remote_user,
							const char *id, const char *alias,
							const char *message)
{
	PurpleAccountMngr::RequestAddCbk(account, remote_user, id, alias, message);
}

static void * C_AuthRequestCbk(PurpleAccount *account, const char *remote_user,
							const char *id, const char *alias,
							const char *message, gboolean on_list,
							PurpleAccountRequestAuthorizationCb authorize_cb, PurpleAccountRequestAuthorizationCb deny_cb, void *user_data)
{
	PurpleAccountMngr::AuthRequestCbk(account, remote_user, id, alias, message, 
		on_list, (void *)authorize_cb, (void *)deny_cb, user_data);

	return user_data;
}

PurpleAccountUiOps acc_wg_ops =
{
	C_NotifyAddedCbk,
	NULL,
	C_RequestAddCbk,
	C_AuthRequestCbk,
};

PurpleAccountUiOps null_acc_wg_ops =
{
	NULL, NULL, NULL, NULL,
};

/* ************************************************* */
PurpleAccountMngr *PurpleAccountMngr::_staticInstance = NULL;
IMAccountList PurpleAccountMngr::_purpleIMAccountList;
PurplePresenceMngr *PurpleAccountMngr::_presenceMngr = NULL;
PurpleChatMngr *PurpleAccountMngr::_chatMngr = NULL;
PurpleConnectMngr *PurpleAccountMngr::_connectMngr = NULL;
PurpleContactListMngr *PurpleAccountMngr::_clistMngr = NULL;
RecursiveMutex PurpleAccountMngr::_mutex;

PurpleAccountMngr::PurpleAccountMngr()
{
}

PurpleAccountMngr *PurpleAccountMngr::getInstance()
{
	if (!_staticInstance)
		_staticInstance = new PurpleAccountMngr();

	return _staticInstance;
}

void PurpleAccountMngr::Init()
{
	_presenceMngr = PurplePresenceMngr::getInstance();
	_chatMngr = PurpleChatMngr::getInstance();
	_connectMngr = PurpleConnectMngr::getInstance();
	_clistMngr = PurpleContactListMngr::getInstance();
}

void PurpleAccountMngr::NotifyAddedCbk(PurpleAccount *account, const char *remote_user,
										const char *id, const char *alias,
										const char *message)
{
	LOG_DEBUG("PurpleAccountMngr : NotifyAddedCbk()");
}

void PurpleAccountMngr::RequestAddCbk(PurpleAccount *account, const char *remote_user,
									const char *id, const char *alias,
									const char *message)
{
	LOG_DEBUG("PurpleAccountMngr : RequestAddCbk()");
}

void PurpleAccountMngr::AuthRequestCbk(PurpleAccount *account, const char *remote_user,
									const char *id, const char *alias,
									const char *message, gboolean on_list,
									void *authorize_cb, void *deny_cb, void *user_data)
{
	const char *gPrclId = purple_account_get_protocol_id(account);
	IMAccount *mAccount = FindIMAccount(purple_account_get_username(account),
									PurpleIMPrcl::GetEnumIMProtocol(gPrclId));
	PurpleIMPresence *mPresence = NULL;
	
	if (!mAccount)
		return;
	
	mPresence = _presenceMngr->FindIMPresence(*mAccount);
	mPresence->addAuthRequestInList(std::string(remote_user), authorize_cb, deny_cb, user_data);
	mPresence->authorizationRequestEvent(*mPresence, remote_user, message != NULL ? message : "");
}

/* **************** MANAGE ACCOUNT LIST (Buddy list) ****************** */

IMAccount *PurpleAccountMngr::GetFirstIMAccount()
{
	RecursiveMutex::ScopedLock lock(_mutex);

	IMAccountList::iterator it = _purpleIMAccountList.begin();

	if (it == _purpleIMAccountList.end()) {
		return NULL;
	} else {
		return &(*it);
	}
}

IMAccount *PurpleAccountMngr::FindIMAccount(const char *login, EnumIMProtocol::IMProtocol protocol)
{
	RecursiveMutex::ScopedLock lock(_mutex);

	for (IMAccountList::iterator i = _purpleIMAccountList.begin(); i != _purpleIMAccountList.end(); i++)
	{
		if (PurpleIMFactory::equals((*i), std::string(login), protocol))
		{
			return &(*i);
		}
	}

	return NULL;
}

void PurpleAccountMngr::AddIMAccount(IMAccount &account)
{
	RecursiveMutex::ScopedLock lock(_mutex);
	bool found = false;

	for (IMAccountList::iterator i = _purpleIMAccountList.begin();
		i != _purpleIMAccountList.end(); i++) {
		if (PurpleIMFactory::equals((*i), 
			std::string(account.getLogin().c_str()), account.getProtocol())) {
			found = true;
			break;
		}
	}
	
	if (!found) {
		_purpleIMAccountList.push_back(account);
	}
}

bool PurpleAccountMngr::removeIMAccountCbk(void *data)
{
	RecursiveMutex::ScopedLock lock(_mutex);

	PurpleAccount	*gAccount = (PurpleAccount *)((misc_t *)data)->data_ptr1;

	purple_accounts_delete(gAccount);

	purple_timeout_remove(((misc_t *)data)->cbk_id);

	free((misc_t *)data);

	return TRUE;
}

void PurpleAccountMngr::RemoveIMAccount(IMAccount &imAccount)
{
	RecursiveMutex::ScopedLock lock(_mutex);

	PurpleAccount	*gAccount = purple_accounts_find(imAccount.getLogin().c_str(),
		PurpleIMPrcl::GetPrclId(imAccount.getProtocol()));
	if (!gAccount) {
		return;
	}

	_presenceMngr->RemoveIMPresence(imAccount);
	_chatMngr->RemoveIMChat(imAccount);
	_clistMngr->RemoveIMContactList(imAccount);
	_connectMngr->RemoveIMConnect(imAccount);

	IMAccountList::iterator it =
		std::find(_purpleIMAccountList.begin(), _purpleIMAccountList.end(), imAccount);
	if (it != _purpleIMAccountList.end()) {
		_purpleIMAccountList.erase(it);
	}

	misc_t * data = (misc_t *) malloc(sizeof(misc_t));
	memset(data, 0, sizeof(misc_t));

	data->data_ptr1 = gAccount;

	data->cbk_id = purple_timeout_add(0, (GSourceFunc) PurpleAccountMngr::removeIMAccountCbk, data);
}

bool PurpleAccountMngr::updateIMAccountCbk(void * data)
{
	RecursiveMutex::ScopedLock lock(_mutex);

	PurpleAccount * gAccount = (PurpleAccount *)((misc_t *)data)->data_ptr1;
	const char * password = (const char *)((misc_t *)data)->data_ptr2;

	purple_account_set_password(gAccount, password);
	purple_timeout_remove(((misc_t *)data)->cbk_id);

	free(((misc_t *)data)->data_ptr2);
	free((misc_t *)data);

	return TRUE;
}

void PurpleAccountMngr::UpdateIMAccount(IMAccount &imAccount)
{
	RecursiveMutex::ScopedLock lock(_mutex);

	PurpleAccount	*gAccount = purple_accounts_find(imAccount.getLogin().c_str(),
		PurpleIMPrcl::GetPrclId(imAccount.getProtocol()));
	if (!gAccount) {
		return;
	}

	_presenceMngr->UpdateIMPresence(imAccount);
	_chatMngr->UpdateIMChat(imAccount);
	_clistMngr->UpdateIMContactList(imAccount);
	_connectMngr->UpdateIMConnect(imAccount);

	IMAccountList::iterator it =
		std::find(_purpleIMAccountList.begin(), _purpleIMAccountList.end(), imAccount);
	if (it != _purpleIMAccountList.end()) {
		(*it) = imAccount;
	}

	misc_t * data = (misc_t *) malloc(sizeof(misc_t));
	memset(data, 0, sizeof(misc_t));

	data->data_ptr1 = gAccount;
	data->data_ptr2 = strdup(imAccount.getPassword().c_str());

	data->cbk_id = purple_timeout_add(0, (GSourceFunc) PurpleAccountMngr::updateIMAccountCbk, data);
}

void PurpleAccountMngr::reset() {
	RecursiveMutex::ScopedLock lock(_mutex);

	_presenceMngr->reset();
	_chatMngr->reset();
	_clistMngr->reset();
	_connectMngr->reset();

	_purpleIMAccountList.clear();
}

/* ******************************************************************** */
