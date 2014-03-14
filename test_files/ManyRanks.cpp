/*
 * ManyRanks.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: root
 */


#include "Define.h"

using namespace boost::multi_index;


/*

rank_change_event: 排名发生变化时的事件(广播等……)

 <root>
	<rank_config>
		<rank_item type="1" count_id="[]" rank_num="" show_num="" time_from="" time_to="" tip="">
			<rank_change_event>
				<item rank_id="1" />
				<item rank_id="2" />
				<item rank_id="3" />
			</rank_change_event>
		</rank_item>
	</rank_config>

 </root>


 */


enum WorldRankType
{
	WRT_NONE = 0,

	WRT_CONSUME = 1,
	WRT_DRAGON = 2,
	WRT_LVL = 3,
	WRT_FIGHT = 4,

	WRT_END
};



class RankPlayer : public smart_count
{
public:
	uint32 _pid;       // 玩家ID

	/* question: 更多的排序规则 */
	uint32 _rank_data;  // 排序关键数值
	int32 _time;       // 数值更新时间,同样用于排序

	uint32 _rank;
	uint32 _last_rank;

	RankPlayer()
	{
		_pid = 0;
		_rank_data = 0;
		_time = 0;

		_rank = 0;
		_last_rank = 0;
	}

	virtual ~RankPlayer()
	{

	}

public:
	uint32 get_pid()const;

	uint32 get_rank()const;

	uint32 get_old_rank()const;
};

typedef smart_ptr<RankPlayer> RankPlayerPtr;


struct RankCompare
{
	bool operator() (const RankPlayerPtr & lhs, const RankPlayerPtr & rhs)
	{
		{
			if(lhs->_rank_data > rhs->_rank_data)
			{
				return true;
			}
			if(lhs->_rank_data < rhs->_rank_data)
			{
				return false;
			}
		}
		{
			if(lhs->_time < rhs->_time)
			{
				return true;
			}
			{
				if(lhs->_time < rhs->_time)
				{
					return false;
				}
			}
		}

		return false;
	}
};

typedef boost::multi_index_container<RankPlayerPtr,
		indexed_by<
				hashed_unique<const_mem_fun<RankPlayer, uint32, &RankPlayer::get_pid> >,
				hashed_unique<const_mem_fun<RankPlayer, uint32, &RankPlayer::get_rank> >,
				hashed_unique<const_mem_fun<RankPlayer, uint32, &RankPlayer::get_old_rank> >
			>
		> RankPlayers;


class RankBase : public smart_count
{
private:
	WorldRankType _rank_type;

	int32 _time_from;
	int32 _time_to;
	bool _is_open;
	bool _need_rank;

	uint32 _min_rank_data;

	map<uint32, RankPlayerPtr> _players;  // 为了排名(1,2,3……)变化事件，改为 multi_index_continer

public:
	RankBase()
	{
		_rank_type = WRT_NONE;

		_time_from = 0;
		_time_to = 0;
		_is_open = false;
		_need_rank = false;

		_min_rank_data = 0;
	}

	virtual ~RankBase()
	{

	}

public:
	void update_player_data(uint32 pid, uint32 data);

	bool is_rank_open()const
	{
		return _is_open;
	}

	void update_open_status(int32 now)
	{
		if(_time_from <= now && now < _time_to)
		{
			_is_open = true;
		}
		else
		{
			_is_open = false;
		}
	}

	bool is_need_rank()const
	{
		return _need_rank;
	}

	void rank_it()
	{
		// to be continued.
	}

	RankPlayerPtr get_player_by_pid(uint32 pid)const;

	RankPlayerPtr get_player_by_rank(uint32 rank)const;

	RankPlayerPtr get_player_by_old_rank(uint32 old_rank)const;
};

typedef smart_ptr<RankBase> RankBasePtr;

typedef map<WorldRankType, RankBasePtr> RankBaseMap;


class RankHelper : public smart_count
{
public:
	map<WorldRankType, RankBasePtr> _ranks;

public:
	RankHelper()
	{

	}
	~RankHelper()
	{

	}

public:
	bool update_rank_player(WorldRankType type, uint32 pid, uint32 data);

	void update_open_status(int32 now)
	{
		for(RankBaseMap::const_iterator it=_ranks.begin(); it!=_ranks.end(); ++it)
		{
			RankBasePtr one_rank = it->second;

			one_rank->update_open_status(now);
		}
	}

	RankBasePtr get_rank(WorldRankType type);

	void rank_one(WorldRankType rank_type);
};

typedef smart_ptr<RankHelper> RankHelperPtr;


void rank_timer()
{
	RankHelperPtr rank_helper = new RankHelper();

	for(map<WorldRankType, RankBasePtr>::iterator it=rank_helper->_ranks.begin(); it!=rank_helper->_ranks.end(); ++it)
	{
		RankBasePtr one_rank = it->second;

		if(one_rank->is_rank_open() == false)
		{
			continue;
		}
		if(one_rank->is_need_rank() == false)
		{
			continue;
		}

		one_rank->rank_it();
	}

}
