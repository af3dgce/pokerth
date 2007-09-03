/***************************************************************************
 *   Copyright (C) 2007 by Lothar May                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "clientplayer.h"
#include <handinterface.h>

using namespace std;


ClientPlayer::ClientPlayer(ConfigFile *c, BoardInterface *b, int id, unsigned uniqueId, PlayerType type, std::string name, std::string avatar, int sC, bool aS, int mB)
: PlayerInterface(), myConfig(c), actualHand(0), actualBoard(b), myCardsValue(0), myID(id), myUniqueID(uniqueId), myType(type), myName(name), myAvatar(avatar), myDude(0), myDude4(0), myCardsValueInt(0), myOdds(-1.0), myCash(sC), mySet(0), myLastRelativeSet(0), myAction(0), myButton(mB), myActiveStatus(aS), myTurn(0), myRoundStartCash(0), sBluff(0), sBluffStatus(0)
{
}


ClientPlayer::~ClientPlayer()
{
}


void
ClientPlayer::setHand(HandInterface* br)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	actualHand = br;
}

int
ClientPlayer::getMyID() const
{
	return myID;
}

unsigned
ClientPlayer::getMyUniqueID() const
{
	return myUniqueID;
}

PlayerType
ClientPlayer::getMyType() const
{
	return myType;
}

void
ClientPlayer::setMyDude(int theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myDude = theValue;
}

int
ClientPlayer::getMyDude() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myDude;
}

void
ClientPlayer::setMyDude4(int theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myDude4 = theValue;
}

int
ClientPlayer::getMyDude4() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myDude4;
}

void
ClientPlayer::setMyName(const std::string& theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myName = theValue;
}

std::string
ClientPlayer::getMyName() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myName;
}

void
ClientPlayer::setMyAvatar(const std::string& theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myAvatar = theValue;
}

std::string
ClientPlayer::getMyAvatar() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myAvatar;
}

void
ClientPlayer::setMyCash(int theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myCash = theValue;
}

int
ClientPlayer::getMyCash() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myCash;
}

void
ClientPlayer::setMySet(int theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myLastRelativeSet = theValue;
}

void
ClientPlayer::setMySetAbsolute(int theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	mySet = theValue;
}

void
ClientPlayer::setMySetNull()
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	mySet = 0;
	myLastRelativeSet = 0;
}

int
ClientPlayer::getMySet() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return mySet;
}

int
ClientPlayer::getMyLastRelativeSet() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myLastRelativeSet;
}

void
ClientPlayer::setMyAction(int theValue, bool /*blind*/)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myAction = theValue;
}

int
ClientPlayer::getMyAction() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myAction;
}

void
ClientPlayer::setMyButton(int theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myButton = theValue;
}

int
ClientPlayer::getMyButton() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myButton;
}

void
ClientPlayer::setMyActiveStatus(bool theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myActiveStatus = theValue;
}

bool
ClientPlayer::getMyActiveStatus() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myActiveStatus;
}

void
ClientPlayer::setMyCards(int* theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	for (int i = 0; i < 2; i++)
		myCards[i] = theValue[i];
}

void
ClientPlayer::getMyCards(int* theValue) const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	for (int i = 0; i < 2; i++)
		theValue[i] = myCards[i];
}

void
ClientPlayer::setMyTurn(bool theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myTurn = theValue;
}

bool
ClientPlayer::getMyTurn() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myTurn;
}

void
ClientPlayer::setMyCardsFlip(bool theValue, int state)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myCardsFlip = theValue;
	// log flipping cards
	if (myCardsFlip) {
		switch(state) {
			case 1: actualHand->getGuiInterface()->logFlipHoleCardsMsg(myName, myCards[0], myCards[1], myCardsValueInt);
			break;
			case 2: actualHand->getGuiInterface()->logFlipHoleCardsMsg(myName, myCards[0], myCards[1]);
			break;
			case 3: actualHand->getGuiInterface()->logFlipHoleCardsMsg(myName, myCards[0], myCards[1], myCardsValueInt, "has");
			break;
			default: ;
		}
	}
}

bool
ClientPlayer::getMyCardsFlip() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myCardsFlip;
}

void
ClientPlayer::setMyCardsValueInt(int theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myCardsValueInt = theValue;
}

int
ClientPlayer::getMyCardsValueInt() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myCardsValueInt;
}

void
ClientPlayer::setMyBestHandPosition(int* theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	for (int i = 0; i < 5; i++)
		myBestHandPosition[i] = theValue[i];
}

void
ClientPlayer::getMyBestHandPosition(int* theValue) const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	for (int i = 0; i < 5; i++)
		theValue[i] = myBestHandPosition[i];
}

void
ClientPlayer::setMyRoundStartCash(int theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myRoundStartCash = theValue;
}

int
ClientPlayer::getMyRoundStartCash() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myRoundStartCash;
}

void
ClientPlayer::setMyAverageSets(int theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myAverageSets[0] = myAverageSets[1];
	myAverageSets[1] = myAverageSets[2];
	myAverageSets[2] = myAverageSets[3];
	myAverageSets[3] = theValue;
}

int
ClientPlayer::getMyAverageSets() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return (myAverageSets[0]+myAverageSets[1]+myAverageSets[2]+myAverageSets[3])/4;
}

void
ClientPlayer::setMyAggressive(bool theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	for (int i=0; i<6; i++)
	{
		myAggressive[i] = myAggressive[i+1];
	}
	myAggressive[6] = theValue;
}

int
ClientPlayer::getMyAggressive() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	int sum = 0;
	for (int i=0; i<7; i++)
	{
		sum += myAggressive[i];
	}
	return sum;
}

void 
ClientPlayer::setSBluff(int theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	sBluff = theValue;
}

int
ClientPlayer::getSBluff() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return sBluff;
}

void
ClientPlayer::setSBluffStatus(bool theValue)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	sBluffStatus = theValue;
}

bool
ClientPlayer::getSBluffStatus() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return sBluffStatus;
}

void
ClientPlayer::setMyWinnerState(bool theValue, int pot)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myWinnerState = theValue;
	if(theValue)
		actualHand->getGuiInterface()->logPlayerWinsMsg(myID, pot);
}

bool
ClientPlayer::getMyWinnerState() const
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myWinnerState;
}

void
ClientPlayer::action()
{
}


void
ClientPlayer::preflopEngine()
{
}


void
ClientPlayer::flopEngine()
{
}


void
ClientPlayer::turnEngine()
{
}


void
ClientPlayer::riverEngine()
{
}


void
ClientPlayer::evaluation(int /*bet*/, int /*raise*/)
{
}


int
ClientPlayer::preflopCardsValue(int* /*cards*/)
{
	return 0;
}


int
ClientPlayer::flopCardsValue(int* /*cards*/)
{
	return 0;
}


void
ClientPlayer::readFile()
{
}

int
ClientPlayer::turnCardsValue(int* /*cards*/)
{
	return 0;
}

void
ClientPlayer::preflopEngine3()
{
}

void
ClientPlayer::flopEngine3()
{
}

void
ClientPlayer::turnEngine3()
{
}

void
ClientPlayer::riverEngine3()
{
}

void ClientPlayer::setNetSessionData(boost::shared_ptr<SessionData> session)
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	myNetSessionData = session;
}

boost::shared_ptr<SessionData> ClientPlayer::getNetSessionData()
{
	boost::recursive_mutex::scoped_lock lock(m_syncMutex);
	return myNetSessionData;
}

