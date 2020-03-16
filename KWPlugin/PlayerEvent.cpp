#pragma once
#include "Prebuild.h"
#include "BDSAPI.hpp"
#include "Command.cpp"
#include "RPG.cpp"
#include "Land.cpp"

class PlayerEvent {
public:
	bool static UseItem(Player* player, ItemStack* item, BlockPos* blockpos, Block* pBlk) {
		return true;
	}


	bool static BreakItemFrame(Player* player, BlockPos* position) {
		cout << "Player: " << player << " Break" << position->getPosition()->toNormalString() << endl;
		return false;
	}

	bool static PlaceBlock(Player* player, short blockid, BlockPos* position) {
		/*
		if (blockid == 154) {
			if (!LockBox::CheckDropper(player, position)) {
				player->sendMsg("���޷��ڴ˴�����©��,��Ϊ����������������");
				return false;
			}
		}
		*/
		if (!Land::canLandModifyBlock(Land::BlockChunckId(position->getPosition()), player)) {
			player->sendMsg("���޷��ƻ�����صķ���!");
			return false;
		}
		return true;
	}

	bool static BreakBlock(Player* player, const Block* block, BlockSource* blocksource, BlockPos* blockpos) {
		if (block->getLegacyBlock()->getBlockItemID() == 54) {
			if (!LockBox::HavePermission(player, blockpos)) {
				player->sendMsg("��û��Ȩ���ƻ�������!");
				return false;
			}
		}
		if (!Land::canLandModifyBlock(Land::BlockChunckId(blockpos->getPosition()), player)) return false;
		return true;

	}

	bool static ReadyOpenBox(Player* player, BlockSource* blocksource, BlockPos* blockposition) {
		if (AwardBox::isRequestSetBox(player)) {
			AwardBox::SetAwardBox(blockposition, player);
			player->sendMsg("Box Setted!");
			return false;
		}
		if (AwardBox::isRequestTP(player)) {
			AwardBox::SetTP(blockposition, player);
			player->sendMsg("TP Setted!");
			return false;
		}
		if (AwardBox::isAwardBox(blockposition)) {
			int aw = AwardBox::getAward(blockposition, player);
			Economy::GivePlayerMoney(player->getNameTag(), aw);
			player->sendMsg("���ѻ�� " + std::to_string(aw));
			return false;
		}
		if (!LockBox::HavePermission(player, blockposition)) {
			player->sendMsg("��û��Ȩ�޴򿪴�����!");
			return false;
		}
		if (LockBox::isRequestLockBox(player)) {
			LockBox::SetPermission(player, blockposition);
			player->sendMsg("���ѳɹ�����!");
			return false;
		}
		return true;
	}

	bool static ReadyOpenBusket(Player* player, BlockSource* blocksource, BlockPos* blockposition) {
		return true;
	}

	void static CloseBox(Player* player, BlockPos* blockposition) {

	}

	void static CloseBusket(Player* player, BlockPos* blockposition) {
	}

	void static Spawn(Player* player) {
		if (RPG::isNewPlayer(player->getNameTag())) {
			Economy::SetPlayerMoney(player->getNameTag(), 100);
			player->sendMsg("��ӭ���� FutureCraft ��������! Ŀǰ�Ѹ���ת�� 100 ���! ��ʼ��������!");
			player->sendMsg("�ٷ�QQȺ��: 626714017  Ⱥ�����淨�ֲ�Ŷ~");
		}
	}

	// ����������
	static bool reNameByUuid(std::string uuid, std::string newName) {
		bool ret = false;
		Player* taget = onlinePlayers[uuid];
		if (taget != NULL) {
			taget->reName(newName);
			ret = true;
		}
		return ret;
	}

	bool static Command(Player* player, std::string command) {
		if (Command::onPlayerSendCommand(command, player)) return false; //��Ϊʲô,Ҫ����������������Process
		return true;
	}

	void static Exit(Player* player) {
	}

	bool static Attack(Player* player, Actor* actor) {
		if (actor->getEntityTypeId() == 1)
			if (Land::canLandPvP(Land::PlayerChunckId(actor->getPos()), player, (Player*)actor)) {
				return true;
			}
			else {
				player->sendMsg("���޷��ڴ���ع�����!");
				return false;
			}
		return true;
	}

	void static Chat(Player* player, string* chat) {
		string nametag = player->getNameTag();
		if (Guild::isInGuild(nametag)) {
			cout << "[" + Guild::getPlayerGuildName(nametag) + "]<" + nametag + "> " + *chat << endl;
			runcmd("tellraw @a {\"rawtext\":[{\"text\":\"[" + Guild::getPlayerGuildName(nametag) + "]<" + nametag + "> " + *chat + "\"}]}");
		}
		else {
			cout << "<" + nametag + "> " + *chat << endl;
			runcmd("tellraw @a {\"rawtext\":[{\"text\":\"<" + nametag + "> " + *chat + "\"}]}");
		}
	}
};