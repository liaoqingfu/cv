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

#ifndef PURPLEIMCHAT_H
#define PURPLEIMCHAT_H

#include <imwrapper/IMChat.h>
#include <thread/Mutex.h>

class IMAccount;
class IMChatSession;
class IMContactSet;

extern "C" {
#include <libpurple/connection.h>
}

typedef struct mConvInfo_s
{
	void *conv_session;
	int conv_id;
	void *purple_conv_session;
	GList *pending_invit;
} mConvInfo_t;

/**
 * Purple IM chat.
 *
 * @ingroup model
 * @author Julien Bossart
 */
class PurpleIMChat : public IMChat
{
	friend class PurpleIMFactory;

public:

	PurpleIMChat(IMAccount account);

	virtual void createSession(const IMContactSet & imContactList);
	virtual void closeSession(IMChatSession & chatSession);
	virtual void sendMessage(IMChatSession & chatSession, const std::string & message);
	virtual void changeTypingState(IMChatSession & chatSession, TypingState state);
	virtual void addContact(IMChatSession & chatSession, const std::string & contactId);
	virtual void removeContact(IMChatSession & chatSession, const std::string & contactId);

	static bool createSessionCbk(void * data);
	static bool closeSessionCbk(void * data);
	static bool sendMessageCbk(void * data);
	static bool changeTypingStateCbk(void * data);
	static bool addContactCbk(void * data);
	static bool removeContactCbk(void * data);

	static mConvInfo_t *CreateChatSession(bool userCreated, PurpleIMChat & imChat);
	static void createPurpleChat(PurpleConnection *gGC, int id, GList *users, PurpleIMChat & imChat);

	const IMAccount & getIMAccount() const { return _imAccount; }

	/* ************ MANAGE CHAT SESSION LIST ************ */
	static std::list<mConvInfo_t *> _PurpleChatSessionList;
	typedef std::list<mConvInfo_t *>::iterator PurpleChatSessionIterator;
	static void AddChatSessionInList(mConvInfo_t *conv);
	static void RemoveChatSessionFromList(int convId);
	static bool IsChatSessionInList(int convId);
	static mConvInfo_t *FindChatStructById(int convId);
	/* ************************************************** */

	static Mutex _mutex;
};

#endif	//PURPLEIMCHAT_H
