// notes:
// SET_MP_INT_CHARACTER_STAT = STATS::STAT_SET_INT
// MP_INT_STAT_ = MPX_
// SET_MP_BOOL_AWD_CHARACTER_STAT = STATS::STAT_SET_BOOL
// MP_BOOL_AWARD_ = MPX_AWD_
// SET_MP_INT_AWD_CHARACTER_STAT = STATS::STAT_SET_INT
// MP_INT_AWARD_ = MPX_AWD_

// important links:
// https://www.unknowncheats.me/forum/grand-theft-auto-v/578963-packed-stats-int-bool-collection-thread-25.html#post4361972
// https://www.unknowncheats.me/forum/4367678-post551.html
// https://www.unknowncheats.me/forum/grand-theft-auto-v/578963-packed-stats-int-bool-collection-thread-33.html#post4411199
// https://github.com/YimMenu-Lua/UnlockEverything
// https://www.unknowncheats.me/forum/grand-theft-auto-v/701294-gta-online-enhanced-awards-stats-3.html
// https://www.unknowncheats.me/forum/grand-theft-auto-v/578963-packed-stats-int-bool-collection-thread-45.html#post4540660
// https://www.unknowncheats.me/forum/grand-theft-auto-v/707419-lua-scripts-yimmenuv2-collection-thread-12.html#post4539651
// https://www.unknowncheats.me/forum/grand-theft-auto-v/500059-globals-locals-discussion-read-page-1-a-37.html#post4539636
// https://www.unknowncheats.me/forum/grand-theft-auto-v/701294-gta-online-enhanced-awards-stats-7.html#post4539241
// https://www.unknowncheats.me/forum/grand-theft-auto-v/578963-packed-stats-int-bool-collection-thread-55.html#post4741090
// https://www.unknowncheats.me/forum/grand-theft-auto-v/699943-stats-editor-external-enhanced-31.html#post4742522

// not implemented
// https://www.unknowncheats.me/forum/grand-theft-auto-v/707419-lua-scripts-yimmenuv2-collection-thread-21.html#post4551843

namespace YimMenu::UnlockEverything
{
	enum class StatType
	{
		None,
		Int,
		Bool,
		Float,
		PackedBool,
		PackedInt,
		PackedBoolRange,
		IntBit,
		IntBits
	};
	class StatCommon
	{
	public:
		StatType type = StatType::None;
		StatCommon(StatType t) :
		    type(t)
		{
		}
	};
	class IntStat : public StatCommon
	{
	public:
		std::string name;
		int value;
		IntStat(std::string n, int v) :
		    StatCommon(StatType::Int),
		    name(n),
		    value(v)
		{
		}
	};
	class BoolStat : public StatCommon
	{
	public:
		std::string name;
		BoolStat(std::string n) :
		    StatCommon(StatType::Bool),
		    name(n)
		{
		}
	};
	class FloatStat : public StatCommon
	{
	public:
		std::string name;
		float value;
		FloatStat(std::string n, float v) :
		    StatCommon(StatType::Float),
		    name(n),
		    value(v)
		{
		}
	};
	class PackedBoolStat : public StatCommon
	{
	public:
		int index;
		PackedBoolStat(int i) :
		    StatCommon(StatType::PackedBool),
		    index(i)
		{
		}
	};
	class PackedIntStat : public StatCommon
	{
	public:
		int index;
		int value;
		PackedIntStat(int i, int v) :
		    StatCommon(StatType::PackedInt),
		    index(i),
		    value(v)
		{
		}
	};
	class PackedBoolRangeStat : public StatCommon
	{
	public:
		int from;
		int to;
		PackedBoolRangeStat(int i, int v) :
		    StatCommon(StatType::PackedBoolRange),
		    from(i),
		    to(v)
		{
		}
	};
	class IntBitStat : public StatCommon
	{
	public:
		std::string name;
		int bit;
		IntBitStat(std::string n, int b) :
		    StatCommon(StatType::IntBit),
		    name(n),
		    bit(b)
		{
		}
	};
	class IntBitsStat : public StatCommon
	{
	public:
		std::string name;
		int num;
		IntBitsStat(std::string n, int b0, int bn) :
		    StatCommon(StatType::IntBits),
		    name(n)
		{
			// https://www.geeksforgeeks.org/dsa/check-whether-bits-set-given-range/
			// example to get 1->2 bits set, 110 = 111 ^ 1
			// where 1000 - 1 = 111, 10 - 1 = 1
			num = ((1 << (bn + 1)) - 1) ^ ((1 << b0) - 1);
		}
	};

	inline std::vector<std::shared_ptr<StatCommon>> careerStats = {
	    // OSCAR GUZMAN FLIES AGAIN
	    std::make_shared<PackedBoolStat>(51280),
	    std::make_shared<PackedBoolStat>(51285),
	    std::make_shared<PackedBoolStat>(51278),
	    std::make_shared<PackedBoolRangeStat>(51286, 51291),
	    std::make_shared<IntStat>("MPX_PROG_HUB_MFH_EARNINGS", 5000000),
	    std::make_shared<PackedBoolRangeStat>(51292, 51297),
	    std::make_shared<PackedBoolStat>(51279),

	    // THE CLUCKIN' BELL FARM RAID
	    std::make_shared<PackedBoolStat>(28272),
	    std::make_shared<PackedBoolStat>(28287),
	    std::make_shared<PackedBoolStat>(28286),
	    std::make_shared<PackedBoolStat>(28285),
	    std::make_shared<PackedBoolRangeStat>(28283, 28284),
	    std::make_shared<IntStat>("MPX_PROG_HUB_CBR_EARNINGS", 5000000),
	    std::make_shared<PackedBoolStat>(28282),
	    std::make_shared<PackedBoolRangeStat>(28273, 28281),

	    // SAN ANDREAS MERCENARIES
	    std::make_shared<IntBitsStat>("MPX_SUM23_AVOP_PROGRESS", 0, 11),
	    std::make_shared<PackedBoolStat>(41566),
	    std::make_shared<PackedBoolStat>(41706),
	    std::make_shared<PackedBoolRangeStat>(41567, 41572),
	    std::make_shared<PackedBoolRangeStat>(41573, 41578),
	    std::make_shared<PackedBoolRangeStat>(41579, 41584),
	    std::make_shared<PackedBoolRangeStat>(41585, 41590),

	    // OPERATION PAPER TRAIL
	    std::make_shared<IntBitsStat>("MPX_ULP_MISSION_PROGRESS", 0, 13),
	    std::make_shared<PackedBoolRangeStat>(41333, 41338),
	    std::make_shared<PackedBoolStat>(41707),
	    std::make_shared<PackedBoolRangeStat>(41339, 41344),
	    std::make_shared<PackedBoolRangeStat>(41345, 41350),
	    std::make_shared<PackedBoolRangeStat>(41351, 41356),
	    std::make_shared<PackedBoolRangeStat>(41357, 41362),

	    // A SUPERYATCH LIFE
	    std::make_shared<IntBitsStat>("MPX_YACHT_MISSION_FLOW", 4, 15),
	    std::make_shared<PackedBoolStat>(41379),
	    std::make_shared<PackedBoolStat>(41708),
	    std::make_shared<PackedBoolRangeStat>(41380, 41385),
	    std::make_shared<PackedBoolRangeStat>(41386, 41391),
	    std::make_shared<PackedBoolRangeStat>(41392, 41397),
	    std::make_shared<PackedBoolRangeStat>(41398, 41403),

	    // GERALD'S LAST PLAY
	    std::make_shared<PackedBoolRangeStat>(41404, 41409),
	    std::make_shared<PackedBoolStat>(41410),
	    std::make_shared<PackedBoolStat>(41709),
	    std::make_shared<PackedBoolRangeStat>(41411, 41416),
	    std::make_shared<PackedBoolRangeStat>(41417, 41422),
	    std::make_shared<PackedBoolRangeStat>(41423, 41428),
	    std::make_shared<PackedBoolRangeStat>(41429, 41434),

	    // PREMIUM DELUXE REPO WORK
	    std::make_shared<PackedBoolRangeStat>(41436, 41443),
	    std::make_shared<PackedBoolStat>(41435),
	    std::make_shared<PackedBoolStat>(41705),
	    std::make_shared<PackedBoolRangeStat>(41444, 41451),
	    std::make_shared<PackedBoolRangeStat>(41452, 41459),
	    std::make_shared<PackedBoolRangeStat>(41460, 41467),
	    std::make_shared<PackedBoolRangeStat>(41468, 41475),

	    // MADRAZO DISPATCH SERVICES
	    std::make_shared<PackedBoolRangeStat>(41476, 41481),
	    std::make_shared<PackedBoolStat>(41506),
	    std::make_shared<PackedBoolStat>(41710),
	    std::make_shared<PackedBoolRangeStat>(41482, 41487),
	    std::make_shared<PackedBoolRangeStat>(41488, 41493),
	    std::make_shared<PackedBoolRangeStat>(41494, 41499),
	    std::make_shared<PackedBoolRangeStat>(41500, 41505),

	    // LOWRIDERS
	    std::make_shared<PackedBoolRangeStat>(42015, 42022),
	    std::make_shared<PackedBoolStat>(41539),
	    std::make_shared<PackedBoolStat>(41711),
	    std::make_shared<PackedBoolRangeStat>(41507, 41514),
	    std::make_shared<PackedBoolRangeStat>(41515, 41522),
	    std::make_shared<PackedBoolRangeStat>(41523, 41530),
	    std::make_shared<PackedBoolRangeStat>(41531, 41538),

	    // AGENTS OF SABOTAGE
	    // std::make_shared<IntStat>("MPX_HACKER_DEN_OWNED", 1),
	    std::make_shared<PackedBoolStat>(9539),
	    std::make_shared<PackedIntStat>(24903, 25),
	    std::make_shared<PackedIntStat>(24904, 2),
	    std::make_shared<IntStat>("MPX_PROG_HUB_DEN24_SAFEEARNINGS", 100000),
	    std::make_shared<IntBitsStat>("MPX_HACKER24_GEN_BS", 5, 12),
	    std::make_shared<PackedBoolStat>(9549),
	    std::make_shared<PackedBoolStat>(9542),
	    std::make_shared<PackedIntStat>(24905, 9),
	    std::make_shared<PackedBoolRangeStat>(9543, 9546),

	    // BOTTOM DOLLAR BOUNTIES
	    // std::make_shared<IntStat>("MPX_BAIL_OFFICE_OWNED", 1),
	    std::make_shared<PackedBoolStat>(9537),
	    std::make_shared<PackedBoolStat>(7639),
	    std::make_shared<PackedIntStat>(7669, 5),
	    std::make_shared<PackedIntStat>(7672, 2),
	    std::make_shared<IntStat>("MPX_PROG_HUB_BOUNTY_EARNINGS", 5000000),
	    std::make_shared<PackedIntStat>(7670, 10),
	    std::make_shared<PackedIntStat>(7674, 3),
	    std::make_shared<PackedIntStat>(7671, 25),
	    std::make_shared<PackedIntStat>(26809, 10),
	    std::make_shared<IntStat>("MPX_PROG_HUB_BOUNTIES_ALIVE_BS", -1),
	    std::make_shared<IntStat>("MPX_BAIL_PROPERTY_EARNINGS", 1000000),

	    // THE CHOP SHOP
	    // std::make_shared<IntStat>("MPX_SALVAGE_YARD_OWNED", 1),
	    std::make_shared<PackedBoolStat>(42038),
	    std::make_shared<PackedBoolStat>(42041),
	    std::make_shared<PackedBoolStat>(42044),
	    std::make_shared<PackedBoolStat>(42045),
	    std::make_shared<IntStat>("MPX_PROG_HUB_SALV23_EARN_SALV", 2500000),
	    std::make_shared<PackedBoolStat>(42042),
	    std::make_shared<IntStat>("MPX_PROG_HUB_SALV23_EARN_PERF", 5),
	    std::make_shared<PackedBoolStat>(42046),
	    std::make_shared<PackedIntStat>(51052, 10),
	    std::make_shared<PackedBoolRangeStat>(42047, 42051),
	    std::make_shared<IntStat>("MPX_PROG_HUB_SALV23_EARN_SELL", 10000000),

	    // LOS SANTOS DRUG WARS
	    std::make_shared<IntBitsStat>("MPX_XM22_MISSIONS_SA", 0, 16),
	    std::make_shared<IntBitsStat>("MPX_XM22_MISSIONS_SA", 6, 10),
	    std::make_shared<IntBitsStat>("MPX_XM22_MISSIONS_SA", 17, 21),
	    std::make_shared<PackedBoolStat>(42037),
	    std::make_shared<IntStat>("MPX_LFETIME_BIKER_BUY_COMPLET6", 100),
	    std::make_shared<IntBitsStat>("MPX_XM22_FLOW", 20, 24),
	    std::make_shared<IntStat>("MPX_LIFETIME_BKR_SELL_EARNINGS6", 10000000),
	    std::make_shared<IntBitStat>("(MPX_XM22_FLOW", 0),
	    std::make_shared<IntStat>("MPX_LFETIME_BIKER_SELL_COMPLET6", 10),
	    std::make_shared<PackedIntStat>(41241, 5),
	    std::make_shared<IntBitStat>("(MPX_XM22_MISSIONS_SA", 5),
	    std::make_shared<IntBitStat>("(MPX_XM22_MISSIONS_SA", 10),
	    std::make_shared<IntBitStat>("(MPX_XM22_MISSIONS_SA", 26),
	    std::make_shared<IntStat>("MPX_PROG_HUB_LSDW_FJ_NO_DEATHS", 25),
	    std::make_shared<IntStat>("MPX_PROG_HUB_DAX_CLONE_KILLS", 100),
	    std::make_shared<PackedIntStat>(42084, 24),
	    std::make_shared<PackedBoolRangeStat>(41660, 41670),

	    // THE CONTRACT
	    std::make_shared<PackedBoolStat>(28257),
	    std::make_shared<IntStat>("MPX_FIXER_COUNT", 100),
	    std::make_shared<IntBitStat>("(MPX_FIXER_GENERAL_BS", 0),
	    std::make_shared<IntBitStat>("(MPX_FIXER_GENERAL_BS", 2),
	    std::make_shared<IntStat>("MPX_PROG_HUB_FXER_PAY_HIT_BONUS", 100),
	    std::make_shared<PackedIntStat>(42085, 10),
	    std::make_shared<IntStat>("MPX_PROG_HUB_FIXER_SEC_CON_SPEC", 100),
	    std::make_shared<IntStat>("MPX_FIXER_EARNINGS", 5000000),

	    // AFTER HOURS
	    std::make_shared<PackedBoolStat>(22067),
	    std::make_shared<IntStat>("MPX_NIGHTCLUB_JOBS_DONE", 25),
	    std::make_shared<IntStat>("MPX_PROG_HUB_DANCE_DUR", 5),
	    std::make_shared<PackedBoolStat>(15533),
	    std::make_shared<PackedBoolRangeStat>(22082, 22083),
	    std::make_shared<PackedBoolStat>(36868),
	    std::make_shared<PackedBoolStat>(36944),
	    std::make_shared<PackedBoolStat>(41989),
	    std::make_shared<PackedIntStat>(42089, 8),
	    std::make_shared<IntStat>("MPX_NIGHTCLUB_VIP_APPEAR", 25),
	    std::make_shared<IntStat>("MPX_PROG_HUB_NCLUB_POP_MAX_TME", 600),
	    std::make_shared<IntStat>("MPX_HUB_EARNINGS", 50000000),

	    // SMUGGLER'S RUN
	    std::make_shared<PackedBoolStat>(15966),
	    std::make_shared<IntStat>("MPX_LFETIME_HANGAR_BUY_COMPLET", 100),
	    std::make_shared<PackedBoolStat>(41676),
	    std::make_shared<PackedBoolStat>(32398),
	    std::make_shared<IntStat>("MPX_LFETIME_HANGAR_SEL_COMPLET", 1),
	    std::make_shared<PackedBoolStat>(41987),
	    std::make_shared<PackedBoolStat>(36924),
	    std::make_shared<IntStat>("MPX_PROG_HUB_SMUGGLER_CRATES", 1000),
	    std::make_shared<PackedBoolRangeStat>(36925, 36932),
	    std::make_shared<IntStat>("MPX_LFETIME_HANGAR_EARNINGS", 50000000),

	    // GUNRUNNING
	    // std::make_shared<IntStat>("MPX_FACTORYSETUP5", 1),
	    std::make_shared<IntStat>("MPX_LFETIME_BIKER_BUY_COMPLET5", 25),
	    std::make_shared<PackedIntStat>(9359, 25),
	    std::make_shared<PackedBoolStat>(36870),
	    std::make_shared<IntStat>("MPX_WVM_FLOW_BITSET_MISSIONS0", -1),
	    std::make_shared<IntStat>("MPX_LIFETIME_BKR_SEL_COMPLETBC5", 1),
	    std::make_shared<IntStat>("MPX_LFETIME_BIKER_SELL_COMPLET5", 1),
	    std::make_shared<IntBitsStat>("MPX_SR_WEAPON_BIT_SET", 1, 17),
	    std::make_shared<PackedBoolRangeStat>(42002, 42013),
	    std::make_shared<PackedBoolRangeStat>(36831, 36838),
	    std::make_shared<IntStat>("MPX_LIFETIME_BKR_SELL_EARNINGS5", 25000000),

	    // IMPORT / EXPORT
	    // std::make_shared<IntStat>("MPX_OWNED_IE_WAREHOUSE", 1),
	    std::make_shared<IntStat>("MPX_LFETIME_IE_EXPORT_COMPLETED", 25),
	    std::make_shared<PackedBoolRangeStat>(42029, 42036),
	    std::make_shared<PackedBoolRangeStat>(41874, 41883),
	    std::make_shared<IntStat>("MPX_PROG_HUB_VEH_CARGO_SELL_PER", 50),
	    std::make_shared<IntStat>("MPX_PROG_HUB_VEH_CARGO_SPECIAL", 5),
	    std::make_shared<PackedBoolStat>(41988),
	    std::make_shared<PackedBoolRangeStat>(41540, 41547),
	    std::make_shared<IntStat>("MPX_LFETIME_IE_MISSION_EARNINGS", 25000000),

	    // BIKERS
	    std::make_shared<PackedBoolStat>(36871),
	    std::make_shared<PackedBoolStat>(36872),
	    std::make_shared<PackedBoolRangeStat>(36875, 36887),
	    std::make_shared<PackedBoolStat>(36873),
	    std::make_shared<PackedBoolStat>(42001),
	    std::make_shared<PackedBoolStat>(36874),
	    std::make_shared<IntStat>("MPX_LIFETIME_BKR_SELL_COMPLETBC", 1),
	    std::make_shared<IntStat>("MPX_LIFETIME_BKR_SEL_COMPLETBC1", 1),
	    std::make_shared<IntStat>("MPX_LIFETIME_BKR_SEL_COMPLETBC2", 1),
	    std::make_shared<IntStat>("MPX_LIFETIME_BKR_SEL_COMPLETBC3", 1),
	    std::make_shared<IntStat>("MPX_LIFETIME_BKR_SEL_COMPLETBC4", 1),
	    std::make_shared<IntStat>("MPX_BAR_RESUPPLY_CR", 10),
	    std::make_shared<IntStat>("MPX_LIFETIME_BKR_SELL_EARNINGS0", 25000000),
	    std::make_shared<IntStat>("MPX_PROG_HUB_BIK_CUST_DEL_CASH", 2500000),
	    std::make_shared<IntStat>("MPX_PROG_HUB_CLBH_BAR_EARNINGS", 500000),
	    std::make_shared<IntStat>("MPX_PROG_HUB_BIK_CONTRACT_COUNT", 50),

	    // FURTHER ADVENTURES IN FINANCE AND FELONY
	    std::make_shared<PackedBoolStat>(36888),
	    std::make_shared<PackedBoolStat>(36889),
	    std::make_shared<PackedBoolRangeStat>(36892, 36915),
	    std::make_shared<PackedBoolStat>(36890),
	    std::make_shared<IntStat>("MPX_WARHOUSESLOT0", 1),
	    std::make_shared<IntStat>("MPX_LIFETIME_BUY_COMPLETE", 1),
	    std::make_shared<PackedBoolRangeStat>(7559, 7553),
	    std::make_shared<PackedBoolStat>(36891),
	    std::make_shared<PackedBoolRangeStat>(36860, 36865),
	    std::make_shared<IntStat>("MPX_PROG_HUB_FAIFAF_CRATES_COL", 250),
	    std::make_shared<IntStat>("MPX_LIFETIME_CONTRA_EARNINGS", 50000000),

	    // LOS SANTOS TUNERS
	    // std::make_shared<IntStat>("MPX_CAR_CLUB_MEMBERSHIP", 1),
	    std::make_shared<PackedBoolStat>(31737),
	    std::make_shared<PackedBoolStat>(41870),
	    std::make_shared<PackedBoolStat>(31753),
	    std::make_shared<IntBitsStat>("MPX_TUNER_COMP_BS", 0, 7),
	    std::make_shared<PackedBoolStat>(32397),
	    std::make_shared<PackedIntStat>(30226, 10),
	    std::make_shared<IntStat>("MPX_TUNER_COUNT", 25),
	    std::make_shared<IntStat>("MPX_PROG_HUB_TUNER_CUS_DEL_CASH", 5000000),

	    // THE DIAMOND CASINO & RESORT
	    std::make_shared<PackedBoolStat>(27089),
	    std::make_shared<PackedBoolStat>(27090),
	    std::make_shared<IntBitStat>("(MPX_VCM_FLOW_PROGRESS", 6),
	    std::make_shared<IntBitStat>("(MPX_VCM_FLOW_PROGRESS", 12),
	    std::make_shared<IntBitStat>("(MPX_VCM_FLOW_PROGRESS", 11),
	    std::make_shared<IntBitStat>("(MPX_VCM_FLOW_PROGRESS", 17),
	    std::make_shared<PackedBoolStat>(36916),
	    std::make_shared<PackedBoolRangeStat>(36844, 36859),
	    std::make_shared<PackedBoolRangeStat>(41548, 41553),
	    std::make_shared<PackedBoolStat>(41868),
	    std::make_shared<PackedIntStat>(42093, 11),
	    std::make_shared<PackedBoolRangeStat>(41560, 41565),
	    std::make_shared<PackedBoolRangeStat>(41554, 41559),

	    // THE CAYO PERICO HEIST
	    std::make_shared<PackedBoolStat>(30309),
	    std::make_shared<PackedBoolStat>(30522),
	    std::make_shared<IntBitStat>("MPX_H4_MISSIONS", 0),
	    std::make_shared<IntBitStat>("(MPX_H4_PROGRESS", 1),
	    std::make_shared<IntBitsStat>("MPX_H4_PROGRESS", 6, 11),
	    std::make_shared<IntBitsStat>("MPX_H4_H4_DJ_MISSIONS", 0, 6),
	    std::make_shared<PackedBoolStat>(41677),
	    std::make_shared<IntStat>("MPX_PROG_HUB_CAYO_PRP_NO_DEATHS", 25),
	    std::make_shared<PackedIntStat>(42094, 15),
	    std::make_shared<IntStat>("MPX_CR_SUBMARINE", 1),
	    std::make_shared<IntStat>("MPX_CR_STRATEGIC_BOMBER", 1),
	    std::make_shared<IntStat>("MPX_CR_SMUGGLER_PLANE", 1),
	    std::make_shared<IntStat>("MPX_CR_STEALTH_HELI", 1),
	    std::make_shared<IntStat>("MPX_CR_PATROL_BOAT", 1),
	    std::make_shared<IntStat>("MPX_CR_SMUGGLER_BOAT", 1),
	    std::make_shared<IntStat>("MPX_PROG_HUB_CAYO_H_EARNINGS", 50000000),

	    // THE DIAMOND CASINO HEIST

	    std::make_shared<IntBitStat>("(MPX_CAS_HEIST_FLOW", 1),
	    std::make_shared<PackedBoolStat>(28270),
	    std::make_shared<PackedBoolStat>(36842),
	    std::make_shared<IntBitStat>("(MPX_CAS_HEIST_FLOW", 10),
	    std::make_shared<PackedBoolStat>(32399),
	    std::make_shared<IntBitsStat>("MPX_CAS_HEIST_FLOW", 11, 13),
	    std::make_shared<PackedBoolStat>(42025),
	    std::make_shared<PackedBoolStat>(42086),
	    std::make_shared<PackedBoolRangeStat>(41678, 41681),
	    std::make_shared<IntStat>("MPX_PROG_HUB_CASINO_H_EARNINGS", 50000000),

	    // THE DOOMSDAY HEIST
	    std::make_shared<PackedBoolStat>(18139),
	    std::make_shared<PackedBoolStat>(36861),
	    std::make_shared<IntBitsStat>("MPX_GANGOPS_FLOW_BITSET_MISS0", 0, 2),
	    std::make_shared<PackedBoolStat>(41712),
	    std::make_shared<PackedBoolStat>(36862),
	    std::make_shared<PackedBoolStat>(41713),
	    std::make_shared<PackedBoolStat>(36863),
	    std::make_shared<PackedBoolStat>(41714),
	    std::make_shared<IntStat>("MPX_PROG_HUB_DOOM_PRP_NO_DEATHS", 14),
	    std::make_shared<PackedIntStat>(42087, 10),
	    std::make_shared<PackedBoolStat>(41685),
	    std::make_shared<PackedBoolStat>(41690),
	    std::make_shared<PackedBoolStat>(41696),
	    std::make_shared<PackedBoolRangeStat>(41697, 41699),
	    std::make_shared<IntStat>("MPX_PROG_HUB_DOOMSDAY_ACTS", 15),

	    // ORIGINAL HEISTS
	    std::make_shared<PackedBoolStat>(36867),
	    std::make_shared<PackedBoolStat>(36933),
	    std::make_shared<PackedBoolStat>(41700),
	    std::make_shared<PackedBoolStat>(41715),
	    std::make_shared<PackedBoolStat>(41716),
	    std::make_shared<PackedBoolStat>(41717),
	    std::make_shared<PackedBoolStat>(41718),
	    std::make_shared<PackedBoolStat>(41719),
	    std::make_shared<PackedIntStat>(42100, 5),
	    std::make_shared<PackedIntStat>(42090, 15),
	    std::make_shared<IntStat>("MPX_PROG_HUB_HEIST_EARNINGS", 50000000),
	    std::make_shared<PackedBoolRangeStat>(41701, 41704),
	    std::make_shared<PackedBoolStat>(36917),
	    std::make_shared<PackedBoolStat>(42000),

	    // ARENA WAR
	    std::make_shared<PackedBoolStat>(25009),
	    std::make_shared<PackedBoolRangeStat>(41647, 41655),
	    std::make_shared<PackedIntStat>(22063, 20),
	    std::make_shared<IntStat>("MPX_ARENAWARS_AP_TIER", 1000),
	    std::make_shared<PackedIntStat>(42088, 15),
	    std::make_shared<PackedIntStat>(42000, 20),

	    // ADVERSARY MODS
	    std::make_shared<PackedBoolRangeStat>(41594, 41646),
	    std::make_shared<PackedBoolStat>(36840),
	    std::make_shared<IntStat>("MPX_PROG_HUB_ADV_WINS", 50),
	    std::make_shared<PackedBoolStat>(36921),

	    // SURVIVALS
	    std::make_shared<IntStat>("MPX_PROG_HUB_SURVIVALS_PLAYED", 1),
	    std::make_shared<PackedBoolStat>(41672),
	    std::make_shared<IntStat>("MPX_PROG_HUB_SURV_WAVES", 250),
	    std::make_shared<PackedBoolStat>(41673),
	    std::make_shared<PackedBoolStat>(41332),
	    std::make_shared<PackedBoolStat>(41331),

	    // RACING
	    std::make_shared<PackedBoolStat>(42023),
	    std::make_shared<PackedBoolRangeStat>(41363, 42151),
	    std::make_shared<IntStat>("MPX_RACES_WON", 50),
	    std::make_shared<IntBitsStat>("MPX_PROG_HUB_T_TRIAL_PAR_TIME", 0, 25),
	    std::make_shared<IntBitsStat>("MPX_PROG_HUB_T_TRL_PAR_TIME_RC", 0, 25),
	    std::make_shared<IntBitsStat>("MPX_PROG_HUB_T_TRL_PAR_TIME_HSW", 0, 25),
	    std::make_shared<IntBitsStat>("MPX_PROG_HUB_T_TRL_PAR_TIME_BKE", 0, 25),
	    std::make_shared<PackedIntStat>(41246, 20),
	    std::make_shared<IntStat>("MPX_PROG_HUB_FST_LPS_RSTAR_RAC", 50),


	    // DEATHMATCHES
	    std::make_shared<IntStat>("MPX_DM_END", 1),
	    std::make_shared<IntStat>("MPX_PROG_HUB_DM_TDM_PLAYS", 1),
	    std::make_shared<IntStat>("MPX_PROG_HUB_DM_COMMUNITY_PLAYS", 10),
	    std::make_shared<IntStat>("MPX_PROG_HUB_DTHM_KILL_5_WO_DIE", 25),
	    std::make_shared<PackedBoolStat>(36922),

	    // VEHICLE ENTHUSIAST
	    std::make_shared<PackedBoolStat>(41864),
	    std::make_shared<PackedBoolStat>(42014),
	    std::make_shared<PackedBoolStat>(41865),
	    std::make_shared<PackedBoolStat>(41863),
	    std::make_shared<PackedBoolStat>(41840),
	    std::make_shared<PackedBoolStat>(41839),
	    std::make_shared<PackedBoolStat>(41841),
	    std::make_shared<PackedBoolStat>(41838),
	    std::make_shared<PackedIntStat>(42092, 5),
	    std::make_shared<PackedIntStat>(42091, 10),
	    std::make_shared<IntStat>("MPX_HUB_VEH_ENTH_OWNED_VEHS", 99),
	    std::make_shared<PackedBoolStat>(41866),
	    std::make_shared<PackedBoolRangeStat>(41842, 41862),
	    std::make_shared<IntStat>("MPX_VEHICLES_CUSTOMISED", 50),

	    // WEAPONS EXPERT
	    std::make_shared<PackedBoolStat>(36934),
	    std::make_shared<PackedBoolStat>(36935),
	    std::make_shared<PackedBoolStat>(36936),
	    std::make_shared<PackedBoolStat>(36937),
	    std::make_shared<PackedBoolStat>(36938),
	    std::make_shared<PackedBoolStat>(36920),
	    std::make_shared<IntStat>("MPX_PROG_HUB_WEAP_TYPE_ANSR", -1),
	    std::make_shared<PackedIntStat>(41242, 8),
	    std::make_shared<PackedBoolStat>(36942),
	    std::make_shared<IntStat>("MPX_PROG_HUB_10_CHAL_ANSR", 10),
	    std::make_shared<PackedBoolStat>(36941),
	    std::make_shared<PackedBoolRangeStat>(15456, 15460),

	    // A Safehouse In The Hills
	    std::make_shared<PackedBoolStat>(54773),
	    std::make_shared<PackedBoolStat>(54774),
	    std::make_shared<PackedBoolStat>(54775),
	    std::make_shared<PackedBoolRangeStat>(54776, 54780),
	    std::make_shared<IntStat>("MPX_PROG_HUB_KNOWAY_EARNINGS", 5000000),
	    std::make_shared<PackedBoolRangeStat>(54781, 54785),
	    std::make_shared<PackedBoolStat>(54786),

	    // The Kortz Center Heist
	    std::make_shared<PackedBoolStat>(60011),
	    std::make_shared<PackedBoolStat>(60021),
	    std::make_shared<IntBitStat>("MPX_K26_GENERAL_BS", 2),
	    std::make_shared<IntStat>("MPX_AWD_PREPPER", 20),
	    std::make_shared<PackedBoolStat>(60022),
	    std::make_shared<PackedBoolStat>(60023),
	    std::make_shared<PackedIntStat>(60049, 5),
	    std::make_shared<PackedBoolRangeStat>(60024, 60027),
	    std::make_shared<PackedIntStat>(60050, 15),
	    std::make_shared<PackedBoolStat>(60028),
	    std::make_shared<IntStat>("MPX_PROG_HUB_KORTZ_STOLEN_VALUE", 50000000),
		std::make_shared<IntBitsStat>("MPX_K26_TARGETS_OWNED_BS", 1, 26), // New Mansion Paintings
	};

	inline std::vector<std::shared_ptr<StatCommon>> awardStats = {
	    // Victory
	    std::make_shared<IntStat>("MPX_AWD_FM_DM_WINS", 50),
	    std::make_shared<IntStat>("MPX_AWD_FM_TDM_WINS", 50),
	    std::make_shared<IntStat>("MPX_AWD_FM_TDM_MVP", 50),
	    std::make_shared<IntStat>("MPX_AWD_RACES_WON", 50),
	    std::make_shared<IntStat>("MPX_AWD_FMWINAIRRACE", 25),
	    std::make_shared<IntStat>("MPX_AWD_FMWINSEARACE", 25),
	    std::make_shared<IntStat>("MPX_AWD_FM_GTA_RACES_WON", 50),
	    std::make_shared<BoolStat>("MPX_AWD_FMKILL3ANDWINGTARACE"),
	    std::make_shared<IntStat>("MPX_AWD_FMRALLYWONDRIVE", 25),
	    std::make_shared<IntStat>("MPX_AWD_FMRALLYWONNAV", 25),
	    std::make_shared<IntStat>("MPX_AWD_FMWINRACETOPOINTS", 25),
	    std::make_shared<BoolStat>("MPX_AWD_FMWINCUSTOMRACE"),
	    std::make_shared<IntStat>("MPX_AWD_FM_RACE_LAST_FIRST", 25),
	    std::make_shared<BoolStat>("MPX_AWD_FMRACEWORLDRECHOLDER"),
	    std::make_shared<IntStat>("MPX_AWD_FM_RACES_FASTEST_LAP", 101),
	    std::make_shared<BoolStat>("MPX_AWD_FMWINALLRACEMODES"),
	    std::make_shared<IntStat>("MPX_AWD_FMHORDWAVESSURVIVE", 10),
	    std::make_shared<IntStat>("MPX_MOST_ARM_WRESTLING_WINS", 25),
	    std::make_shared<IntStat>("MPX_AWD_WIN_AT_DARTS", 25),
	    std::make_shared<IntStat>("MPX_AWD_FM_GOLF_WON", 25),
	    std::make_shared<IntStat>("MPX_AWD_FM_TENNIS_WON", 25),
	    std::make_shared<BoolStat>("MPX_AWD_FM_TENNIS_5_SET_WINS"),
	    std::make_shared<BoolStat>("MPX_AWD_FM_TENNIS_STASETWIN"),
	    std::make_shared<IntStat>("MPX_AWD_FM_SHOOTRANG_TG_WON", 25),
	    std::make_shared<IntStat>("MPX_AWD_FM_SHOOTRANG_CT_WON", 25),
	    std::make_shared<BoolStat>("MPX_AWD_FM_SHOOTRANG_GRAN_WON"),
	    std::make_shared<IntStat>("MPX_AWD_FM_SHOOTRANG_RT_WON", 25),
	    std::make_shared<BoolStat>("MPX_AWD_FMWINEVERYGAMEMODE"),
	    std::make_shared<IntStat>("MPX_AWD_WIN_CAPTURES", 50),
	    std::make_shared<IntStat>("MPX_AWD_WIN_CAPTURE_DONT_DYING", 25),
	    std::make_shared<IntStat>("MPX_AWD_WIN_LAST_TEAM_STANDINGS", 50),
	    std::make_shared<IntStat>("MPX_AWD_ONLY_PLAYER_ALIVE_LTS", 50),
	    std::make_shared<IntStat>("MPX_AWD_KILL_TEAM_YOURSELF_LTS", 25),

	    // General
	    std::make_shared<BoolStat>("MPX_AWD_FM25DIFFERENTDM"),
	    std::make_shared<BoolStat>("MPX_AWD_FM25DIFFERENTRACES"),
	    std::make_shared<IntStat>("MPX_AWD_PARACHUTE_JUMPS_20M", 25),
	    std::make_shared<IntStat>("MPX_AWD_PARACHUTE_JUMPS_50M", 25),
	    std::make_shared<IntStat>("MPX_AWD_FMBASEJMP", 25),
	    std::make_shared<BoolStat>("MPX_AWD_FMATTGANGHQ"),
	    std::make_shared<BoolStat>("MPX_AWD_FM6DARTCHKOUT"),
	    std::make_shared<IntStat>("MPX_AWD_FM_GOLF_BIRDIES", 25),
	    std::make_shared<BoolStat>("MPX_AWD_FM_GOLF_HOLE_IN_1"),
	    std::make_shared<IntStat>("MPX_AWD_FM_TENNIS_ACE", 25),
	    std::make_shared<IntStat>("MPX_AWD_FMBBETWIN", 50000),
	    std::make_shared<IntStat>("MPX_AWD_LAPDANCES", 25),
	    std::make_shared<BoolStat>("MPX_AWD_FM25DIFITEMSCLOTHES"),
	    std::make_shared<IntStat>("MPX_AWD_NO_HAIRCUTS", 25),
	    std::make_shared<BoolStat>("MPX_AWD_BUY_EVERY_GUN"),
	    std::make_shared<BoolStat>("MPX_AWD_FMTATTOOALLBODYPARTS"),
	    std::make_shared<IntStat>("MPPLY_AWD_FM_CR_DM_MADE", 25),
	    std::make_shared<IntStat>("MPPLY_AWD_FM_CR_RACES_MADE", 25),
	    std::make_shared<IntStat>("MPPLY_AWD_FM_CR_PLAYED_BY_PEEP", 100),
	    std::make_shared<IntStat>("MPPLY_AWD_FM_CR_MISSION_SCORE", 100),
	    std::make_shared<IntStat>("MPX_AWD_DROPOFF_CAP_PACKAGES", 100),
	    std::make_shared<IntStat>("MPX_AWD_PICKUP_CAP_PACKAGES", 100),
	    std::make_shared<IntStat>("MPX_AWD_MENTALSTATE_TO_NORMAL", 50),
	    std::make_shared<BoolStat>("MPX_AWD_STORE_20_CAR_IN_GARAGES"),
	    std::make_shared<IntStat>("MPX_AWD_TRADE_IN_YOUR_PROPERTY", 25),

	    // Crimes
	    std::make_shared<IntStat>("MPX_CHAR_WANTED_LEVEL_TIME5STAR", 18000000),
	    std::make_shared<IntStat>("MPX_AWD_5STAR_WANTED_AVOIDANCE", 50),
	    std::make_shared<IntStat>("MPX_AWD_FMSHOOTDOWNCOPHELI", 25),
	    std::make_shared<IntStat>("MPX_PASS_DB_PLAYER_KILLS", 100),
	    std::make_shared<IntStat>("MPX_NUMBER_STOLEN_CARS", 521),
	    std::make_shared<IntStat>("MPX_AWD_HOLD_UP_SHOPS", 20),

	    // Vehicles
	    std::make_shared<IntStat>("MPX_CARS_EXPLODED", 500),
	    std::make_shared<IntStat>("MPX_AWD_CARS_EXPORTED", 50),
	    std::make_shared<IntStat>("MPX_AWD_FMDRIVEWITHOUTCRASH", 30),
	    std::make_shared<IntStat>("MPX_AWD_PASSENGERTIME", 4),
	    std::make_shared<IntStat>("MPX_AWD_TIME_IN_HELICOPTER", 4),
	    std::make_shared<BoolStat>("MPX_AWD_FMFULLYMODDEDCAR"),
	    std::make_shared<IntStat>("MPX_AIR_LAUNCHES_OVER_40M", 25),
	    std::make_shared<IntStat>("MPX_MOST_FLIPS_IN_ONE_JUMP", 5),
	    std::make_shared<IntStat>("MPX_MOST_SPINS_IN_ONE_JUMP", 5),
	    std::make_shared<BoolStat>("MPX_AWD_FMFURTHESTWHEELIE"),

	    // Combat
	    std::make_shared<IntStat>("MPX_AWD_100_HEADSHOTS", 501),
	    std::make_shared<IntStat>("MPX_KILLS_PLAYERS", 1000),
	    std::make_shared<IntStat>("MPX_AWD_FMKILLBOUNTY", 25),
	    std::make_shared<IntStat>("MPX_AWD_FMREVENGEKILLSDM", 50),
	    std::make_shared<IntStat>("MPX_AWD_FM_DM_KILLSTREAK", 100),
	    std::make_shared<IntStat>("MPX_AWD_FM_DM_STOLENKILL", 50),
	    std::make_shared<IntStat>("MPX_AWD_FM_DM_TOTALKILLS", 500),
	    std::make_shared<BoolStat>("MPX_AWD_FMKILLSTREAKSDM"),
	    std::make_shared<BoolStat>("MPX_AWD_FMMOSTKILLSGANGHIDE"),
	    std::make_shared<BoolStat>("MPX_AWD_FMMOSTKILLSSURVIVE"),
	    std::make_shared<IntStat>("MPX_AWD_FM_DM_3KILLSAMEGUY", 50),
	    std::make_shared<IntStat>("MPX_AWD_KILL_CARRIER_CAPTURE", 100),
	    std::make_shared<IntStat>("MPX_AWD_NIGHTVISION_KILLS", 100),
	    std::make_shared<IntStat>("MPX_AWD_KILL_PSYCHOPATHS", 100),
	    std::make_shared<IntStat>("MPX_PISTOL50_ENEMY_KILLS", 500),
	    std::make_shared<IntStat>("MPX_AWD_100_KILLS_SMG", 500),
	    std::make_shared<IntStat>("MPX_ASLTSHTGN_ENEMY_KILLS", 500),
	    std::make_shared<IntStat>("MPX_ASLTRIFLE_ENEMY_KILLS", 500),
	    std::make_shared<IntStat>("MPX_SNIPERRFL_ENEMY_KILLS", 501),
	    std::make_shared<IntStat>("MPX_CMBTMG_ENEMY_KILLS", 500),
	    std::make_shared<IntStat>("MPX_AWD_25_KILLS_STICKYBOMBS", 51),
	    std::make_shared<IntStat>("MPX_GRENADE_ENEMY_KILLS", 50),
	    std::make_shared<IntStat>("MPX_RPG_ENEMY_KILLS", 500),
	    std::make_shared<IntStat>("MPX_UNARMED_ENEMY_KILLS", 50),
	    std::make_shared<IntStat>("MPX_AWD_CAR_BOMBS_ENEMY_KILLS", 25),

	    // Heists
	    std::make_shared<IntStat>("MPX_AWD_FINISH_HEISTS", 50),
	    std::make_shared<IntStat>("MPX_AWD_FINISH_HEIST_SETUP_JOB", 50),
	    std::make_shared<BoolStat>("MPX_AWD_FINISH_HEIST_NO_DAMAGE"),
	    std::make_shared<IntStat>("MPX_AWD_WIN_GOLD_MEDAL_HEISTS", 25),
	    std::make_shared<IntStat>("MPX_AWD_DO_HEIST_AS_THE_LEADER", 25),
	    std::make_shared<BoolStat>("MPX_AWD_SPLIT_HEIST_TAKE_EVENLY"),
	    std::make_shared<BoolStat>("MPX_AWD_ACTIVATE_2_PERSON_KEY"),
	    std::make_shared<IntStat>("MPX_AWD_CONTROL_CROWDS", 25),
	    std::make_shared<BoolStat>("MPX_AWD_ALL_ROLES_HEIST"),
	    std::make_shared<BoolStat>("MPPLY_AWD_FLEECA_FIN"),
	    std::make_shared<BoolStat>("MPPLY_AWD_PRISON_FIN"),
	    std::make_shared<BoolStat>("MPPLY_AWD_HUMANE_FIN"),
	    std::make_shared<BoolStat>("MPPLY_AWD_SERIESA_FIN"),
	    std::make_shared<BoolStat>("MPPLY_AWD_PACIFIC_FIN"),
	    std::make_shared<BoolStat>("MPPLY_AWD_HST_ORDER"),
	    std::make_shared<BoolStat>("MPPLY_AWD_HST_SAME_TEAM"),
	    std::make_shared<BoolStat>("MPPLY_AWD_HST_ULT_CHAL"),
	    std::make_shared<BoolStat>("MPPLY_AWD_COMPLET_HEIST_MEM"),
	    std::make_shared<BoolStat>("MPPLY_AWD_COMPLET_HEIST_1STPER"),

	    // The Doomsday Heist
	    std::make_shared<BoolStat>("MPPLY_AWD_GANGOPS_IAA"),
	    std::make_shared<BoolStat>("MPPLY_AWD_GANGOPS_SUBMARINE"),
	    std::make_shared<BoolStat>("MPPLY_AWD_GANGOPS_MISSILE"),
	    std::make_shared<BoolStat>("MPPLY_AWD_GANGOPS_ALLINORDER"),
	    std::make_shared<BoolStat>("MPPLY_AWD_GANGOPS_LOYALTY"),
	    std::make_shared<BoolStat>("MPPLY_AWD_GANGOPS_LOYALTY2"),
	    std::make_shared<BoolStat>("MPPLY_AWD_GANGOPS_LOYALTY3"),
	    std::make_shared<BoolStat>("MPPLY_AWD_GANGOPS_CRIMMASMD"),
	    std::make_shared<BoolStat>("MPPLY_AWD_GANGOPS_CRIMMASMD2"),
	    std::make_shared<BoolStat>("MPPLY_AWD_GANGOPS_CRIMMASMD3"),
	    std::make_shared<BoolStat>("MPPLY_AWD_GANGOPS_SUPPORT"),

	    // After Hours
	    std::make_shared<IntStat>("MPX_AWD_CLUB_DRUNK", 200),
	    std::make_shared<IntStat>("MPX_DANCEPERFECTOWNCLUB", 100),
	    std::make_shared<IntStat>("MPX_NIGHTCLUB_PLAYER_APPEAR", 500),
	    std::make_shared<IntStat>("MPX_AWD_DANCE_TO_SOLOMUN", 100),
	    std::make_shared<IntStat>("MPX_AWD_DANCE_TO_TALEOFUS", 100),
	    std::make_shared<IntStat>("MPX_AWD_DANCE_TO_DIXON", 100),
	    std::make_shared<IntStat>("MPX_AWD_DANCE_TO_BLKMAD", 100),
	    std::make_shared<IntStat>("MPX_DANCETODIFFDJS", 4),

	    // Arena War --
	    std::make_shared<IntStat>("MPX_AWD_CAREER_WINNER", 1000),
	    std::make_shared<IntStat>("MPX_AWD_TOP_SCORE", 500000),
	    std::make_shared<IntStat>("MPX_AWD_TIME_SERVED", 1000),
	    std::make_shared<IntStat>("MPX_AWD_ARENA_WAGEWORKER", 6785341),
	    std::make_shared<IntStat>("MPX_AWD_WEVE_GOT_ONE", 60),
	    std::make_shared<IntStat>("MPX_AWD_YOURE_OUTTA_HERE", 220),
	    std::make_shared<IntStat>("MPX_AWD_MASSIVE_SHUNT", 60),
	    std::make_shared<IntStat>("MPX_AWD_KILL_OR_BE_KILLED", 60),
	    std::make_shared<IntStat>("MPX_AWD_CROWDPARTICIPATION", 80),
	    std::make_shared<IntStat>("MPX_AWD_SITTING_DUCK", 50),
	    std::make_shared<IntStat>("MPX_AWD_YOUMEANBOOBYTRAPS", 50),
	    std::make_shared<IntStat>("MPX_AWD_MASTER_BANDITO", 50),
	    std::make_shared<IntStat>("MPX_AWD_SPINNER", 80),
	    std::make_shared<IntStat>("MPX_AWD_THROUGH_A_LENS", 60),
	    std::make_shared<IntStat>("MPX_AWD_READY_FOR_WAR", 50),
	    std::make_shared<BoolStat>("MPX_AWD_UNSTOPPABLE"),
	    std::make_shared<BoolStat>("MPX_AWD_CONTACT_SPORT"),
	    std::make_shared<IntStat>("MPX_AWD_TOWER_OFFENSE", 50),
	    std::make_shared<IntStat>("MPX_AWD_WATCH_YOUR_STEP", 50),
	    std::make_shared<BoolStat>("MPX_AWD_PEGASUS"),
	    std::make_shared<BoolStat>("MPX_AWD_BEGINNER"),
	    std::make_shared<BoolStat>("MPX_AWD_FIELD_FILLER"),
	    std::make_shared<BoolStat>("MPX_AWD_ARMCHAIR_RACER"),
	    std::make_shared<BoolStat>("MPX_AWD_LEARNER"),
	    std::make_shared<BoolStat>("MPX_AWD_SUNDAY_DRIVER"),
	    std::make_shared<BoolStat>("MPX_AWD_THE_ROOKIE"),
	    std::make_shared<BoolStat>("MPX_AWD_BUMP_AND_RUN"),
	    std::make_shared<BoolStat>("MPX_AWD_GEAR_HEAD"),
	    std::make_shared<BoolStat>("MPX_AWD_DOOR_SLAMMER"),
	    std::make_shared<BoolStat>("MPX_AWD_HOT_LAP"),
	    std::make_shared<BoolStat>("MPX_AWD_ARENA_AMATEUR"),
	    std::make_shared<BoolStat>("MPX_AWD_PAINT_TRADER"),
	    std::make_shared<BoolStat>("MPX_AWD_SHUNTER"),
	    std::make_shared<BoolStat>("MPX_AWD_JOCK"),
	    std::make_shared<BoolStat>("MPX_AWD_WARRIOR"),
	    std::make_shared<BoolStat>("MPX_AWD_T_BONE"),
	    std::make_shared<BoolStat>("MPX_AWD_MAYHEM"),
	    std::make_shared<BoolStat>("MPX_AWD_WRECKER"),
	    std::make_shared<BoolStat>("MPX_AWD_CRASH_COURSE"),
	    std::make_shared<BoolStat>("MPX_AWD_ARENA_LEGEND"),

	    // The Diamond Casino & Resort
	    std::make_shared<BoolStat>("MPX_AWD_FIRST_TIME1"),
	    std::make_shared<BoolStat>("MPX_AWD_FIRST_TIME2"),
	    std::make_shared<BoolStat>("MPX_AWD_FIRST_TIME3"),
	    std::make_shared<BoolStat>("MPX_AWD_FIRST_TIME4"),
	    std::make_shared<BoolStat>("MPX_AWD_FIRST_TIME5"),
	    std::make_shared<BoolStat>("MPX_AWD_FIRST_TIME6"),
	    std::make_shared<BoolStat>("MPX_AWD_ALL_IN_ORDER"),
	    std::make_shared<BoolStat>("MPX_AWD_SURVIVALIST"),
	    std::make_shared<BoolStat>("MPX_AWD_SUPPORTING_ROLE"),
	    std::make_shared<BoolStat>("MPX_AWD_LEADER"),
	    std::make_shared<IntStat>("MPX_AWD_ODD_JOBS", 100),

	    // Diamond Casino Heist
	    std::make_shared<BoolStat>("MPX_AWD_SCOPEOUT"),
	    std::make_shared<IntStat>("MPX_AWD_PREPARATION", 40),
	    std::make_shared<BoolStat>("MPX_AWD_CREWEDUP"),
	    std::make_shared<BoolStat>("MPX_AWD_MOVINGON"),
	    std::make_shared<BoolStat>("MPX_AWD_PROMOCAMP"),
	    std::make_shared<BoolStat>("MPX_AWD_GUNMAN"),
	    std::make_shared<BoolStat>("MPX_AWD_SMASHNGRAB"),
	    std::make_shared<BoolStat>("MPX_AWD_INPLAINSI"),
	    std::make_shared<BoolStat>("MPX_AWD_UNDETECTED"),
	    std::make_shared<BoolStat>("MPX_AWD_ALLROUND"),
	    std::make_shared<BoolStat>("MPX_AWD_ELITETHEIF"),
	    std::make_shared<BoolStat>("MPX_AWD_PRO"),
	    std::make_shared<BoolStat>("MPX_AWD_SUPPORTACT"),
	    std::make_shared<BoolStat>("MPX_AWD_SHAFTED"),
	    std::make_shared<IntStat>("MPX_AWD_ASLEEPONJOB", 20),
	    std::make_shared<IntStat>("MPX_AWD_DAICASHCRAB", 100000),
	    std::make_shared<IntStat>("MPX_AWD_BIGBRO", 40),
	    std::make_shared<BoolStat>("MPX_AWD_COLLECTOR"),
	    std::make_shared<BoolStat>("MPX_AWD_DEADEYE"),
	    std::make_shared<BoolStat>("MPX_AWD_PISTOLSATDAWN"),
	    std::make_shared<IntStat>("MPX_AWD_SHARPSHOOTER", 40),
	    std::make_shared<IntStat>("MPX_AWD_RACECHAMP", 40),
	    std::make_shared<BoolStat>("MPX_AWD_TRAFFICAVOI"),
	    std::make_shared<BoolStat>("MPX_AWD_CANTCATCHBRA"),
	    std::make_shared<BoolStat>("MPX_AWD_WIZHARD"),
	    std::make_shared<IntStat>("MPX_AWD_BATSWORD", 1000000),
	    std::make_shared<IntStat>("MPX_AWD_COINPURSE", 950000),
	    std::make_shared<BoolStat>("MPX_AWD_APEESCAPE"),
	    std::make_shared<BoolStat>("MPX_AWD_MONKEYKIND"),
	    std::make_shared<IntStat>("MPX_AWD_ASTROCHIMP", 3000000),
	    std::make_shared<BoolStat>("MPX_AWD_AQUAAPE"),
	    std::make_shared<BoolStat>("MPX_AWD_KEEPFAITH"),
	    std::make_shared<IntStat>("MPX_AWD_MASTERFUL", 40000),
	    std::make_shared<BoolStat>("MPX_AWD_TRUELOVE"),
	    std::make_shared<BoolStat>("MPX_AWD_NEMESIS"),
	    std::make_shared<BoolStat>("MPX_AWD_FRIENDZONED"),

	    // Los Santos Summer Special
	    std::make_shared<BoolStat>("MPX_AWD_KINGOFQUB3D"),
	    std::make_shared<BoolStat>("MPX_AWD_QUBISM"),
	    std::make_shared<BoolStat>("MPX_AWD_GODOFQUB3D"),
	    std::make_shared<BoolStat>("MPX_AWD_QUIBITS"),
	    std::make_shared<BoolStat>("MPX_AWD_ELEVENELEVEN"),
	    std::make_shared<BoolStat>("MPX_AWD_GOFOR11TH"),

	    // The Cayo Perico Heist
	    std::make_shared<BoolStat>("MPX_AWD_INTELGATHER"),
	    std::make_shared<BoolStat>("MPX_AWD_COMPOUNDINFILT"),
	    std::make_shared<IntStat>("MPX_AWD_WELL_PREPARED", 50),
	    std::make_shared<BoolStat>("MPX_AWD_LOOT_FINDER"),
	    std::make_shared<BoolStat>("MPX_AWD_MAX_DISRUPT"),
	    std::make_shared<BoolStat>("MPX_AWD_THE_ISLAND_HEIST"),
	    std::make_shared<BoolStat>("MPX_AWD_GOING_ALONE"),
	    std::make_shared<BoolStat>("MPX_AWD_TEAM_WORK"),
	    std::make_shared<BoolStat>("MPX_AWD_MIXING_UP"),
	    std::make_shared<BoolStat>("MPX_AWD_PRO_THIEF"),
	    std::make_shared<BoolStat>("MPX_AWD_CAT_BURGLAR"),
	    std::make_shared<BoolStat>("MPX_AWD_ONE_OF_THEM"),
	    std::make_shared<IntStat>("MPX_AWD_FILL_YOUR_BAGS", 20000000),
	    std::make_shared<BoolStat>("MPX_AWD_GOLDEN_GUN"),
	    std::make_shared<BoolStat>("MPX_AWD_ELITE_THIEF"),
	    std::make_shared<BoolStat>("MPX_AWD_PROFESSIONAL"),
	    std::make_shared<IntStat>("MPX_AWD_WRECK_DIVING", 1000000),
	    std::make_shared<BoolStat>("MPX_AWD_PARTY_VIBES"),
	    std::make_shared<IntStat>("MPX_AWD_SUNSET", 1800000),
	    std::make_shared<BoolStat>("MPX_AWD_HELPING_HAND"),
	    std::make_shared<IntStat>("MPX_AWD_MOODYMANN", 1800000),
	    std::make_shared<IntStat>("MPX_AWD_PALMS_TRAX", 1800000),
	    std::make_shared<BoolStat>("MPX_AWD_HELPING_OUT"),
	    std::make_shared<IntStat>("MPX_AWD_KEINEMUSIK", 1800000),
	    std::make_shared<BoolStat>("MPX_AWD_COURIER"),
	    std::make_shared<IntStat>("MPX_AWD_TREASURE_HUNTER", 50),

	    // Los Santos Tuners
	    std::make_shared<BoolStat>("MPX_AWD_CAR_CLUB"),
	    std::make_shared<IntStat>("MPX_AWD_CAR_CLUB_MEM", 1000),
	    std::make_shared<IntStat>("MPX_AWD_SPRINTRACER", 250),
	    std::make_shared<IntStat>("MPX_AWD_STREETRACER", 250),
	    std::make_shared<IntStat>("MPX_AWD_PURSUITRACER", 250),
	    std::make_shared<IntStat>("MPX_AWD_TEST_CAR", 1800000),
	    std::make_shared<IntStat>("MPX_AWD_AUTO_SHOP", 100),
	    std::make_shared<IntStat>("MPX_AWD_CAR_EXPORT", 100),
	    std::make_shared<BoolStat>("MPX_AWD_PRO_CAR_EXPORT"),
	    std::make_shared<IntStat>("MPX_AWD_GROUNDWORK", 250),
	    std::make_shared<BoolStat>("MPX_AWD_UNION_DEPOSITORY"),
	    std::make_shared<BoolStat>("MPX_AWD_MILITARY_CONVOY"),
	    std::make_shared<BoolStat>("MPX_AWD_FLEECA_BANK"),
	    std::make_shared<BoolStat>("MPX_AWD_FREIGHT_TRAIN"),
	    std::make_shared<BoolStat>("MPX_AWD_BOLINGBROKE_[removed]"),
	    std::make_shared<BoolStat>("MPX_AWD_IAA_RAID"),
	    std::make_shared<BoolStat>("MPX_AWD_METH_JOB"),
	    std::make_shared<BoolStat>("MPX_AWD_BUNKER_RAID"),
	    std::make_shared<IntStat>("MPX_AWD_ROBBERY_CONTRACT", 100),
	    std::make_shared<IntStat>("MPX_AWD_FACES_OF_DEATH", 250),
	    std::make_shared<BoolStat>("MPX_AWD_STRAIGHT_TO_VIDEO"),
	    std::make_shared<BoolStat>("MPX_AWD_MONKEY_C_MONKEY_DO"),
	    std::make_shared<BoolStat>("MPX_AWD_TRAINED_TO_KILL"),
	    std::make_shared<BoolStat>("MPX_AWD_DIRECTOR"),

	    // The Contract
	    std::make_shared<BoolStat>("MPX_AWD_TEEING_OFF"),
	    std::make_shared<BoolStat>("MPX_AWD_PARTY_NIGHT"),
	    std::make_shared<BoolStat>("MPX_AWD_BILLIONAIRE_GAMES"),
	    std::make_shared<BoolStat>("MPX_AWD_HOOD_PASS"),
	    std::make_shared<BoolStat>("MPX_AWD_STUDIO_TOUR"),
	    std::make_shared<BoolStat>("MPX_AWD_DONT_MESS_DRE"),
	    std::make_shared<BoolStat>("MPX_AWD_BACKUP"),
	    std::make_shared<BoolStat>("MPX_AWD_SHORTFRANK_1"),
	    std::make_shared<BoolStat>("MPX_AWD_SHORTLAMAR_1"),
	    std::make_shared<BoolStat>("MPX_AWD_SHORTFRANK_2"),
	    std::make_shared<BoolStat>("MPX_AWD_SHORTLAMAR_2"),
	    std::make_shared<BoolStat>("MPX_AWD_SHORTFRANK_3"),
	    std::make_shared<BoolStat>("MPX_AWD_SHORTLAMAR_3"),
	    std::make_shared<IntStat>("MPX_AWD_CONTRACTOR", 50),
	    std::make_shared<IntStat>("MPX_AWD_COLD_CALLER", 10),
	    std::make_shared<BoolStat>("MPX_AWD_CONTR_KILLER"),
	    std::make_shared<BoolStat>("MPX_AWD_DOGS_BEST_FRIEND"),
	    std::make_shared<BoolStat>("MPX_AWD_MUSIC_STUDIO"),
	    std::make_shared<IntStat>("MPX_AWD_PRODUCER", 60),

	    // Los Santos Drug Wars
	    std::make_shared<BoolStat>("MPX_AWD_ACELIQUOR"),
	    std::make_shared<BoolStat>("MPX_AWD_TRUCKAMBUSH"),
	    std::make_shared<BoolStat>("MPX_AWD_LOSTCAMPREV"),
	    std::make_shared<BoolStat>("MPX_AWD_ACIDTRIP"),
	    std::make_shared<IntStat>("MPX_AWD_RUNRABBITRUN", 5),
	    std::make_shared<BoolStat>("MPX_AWD_HIPPYRIVALS"),
	    std::make_shared<BoolStat>("MPX_AWD_TRAINCRASH"),
	    std::make_shared<IntStat>("MPX_AWD_CALLME", 50),
	    std::make_shared<BoolStat>("MPX_AWD_BACKUPB"),
	    std::make_shared<BoolStat>("MPX_AWD_GETSTARTED"),
	    std::make_shared<IntStat>("MPX_AWD_CHEMCOMPOUNDS", 50),
	    std::make_shared<BoolStat>("MPX_AWD_CHEMREACTION"),
	    std::make_shared<IntStat>("MPX_AWD_STASHHORAID", 50),
	    std::make_shared<IntStat>("MPX_AWD_DEADDROP", 50),
	    std::make_shared<IntStat>("MPX_AWD_GOODSAMARITAN", 50),
	    std::make_shared<BoolStat>("MPX_AWD_WAREHODEFEND"),
	    std::make_shared<BoolStat>("MPX_AWD_RESCUECOOK"),
	    std::make_shared<BoolStat>("MPX_AWD_DRUGTRIPREHAB"),
	    std::make_shared<BoolStat>("MPX_AWD_ATTACKINVEST"),
	    std::make_shared<IntStat>("MPX_AWD_OWNWORSTENEMY", 60),
	    std::make_shared<BoolStat>("MPX_AWD_CARGOPLANE"),
	    std::make_shared<BoolStat>("MPX_AWD_BACKUPB2"),
	    std::make_shared<IntStat>("MPX_AWD_TAXIDRIVER", 50),
	    std::make_shared<BoolStat>("MPX_AWD_TAXISTAR"),

	    // The Chop Shop
	    std::make_shared<BoolStat>("MPX_AWD_MAZE_BANK_ROBBERY"),
	    std::make_shared<BoolStat>("MPX_AWD_CARGO_SHIP_ROBBERY"),
	    std::make_shared<BoolStat>("MPX_AWD_MISSION_ROW_ROBBERY"),
	    std::make_shared<BoolStat>("MPX_AWD_PERFECT_RUN"),
	    std::make_shared<BoolStat>("MPX_AWD_EXTRA_MILE"),
	    std::make_shared<IntStat>("MPX_AWD_VEHICLE_ROBBERIES", 50),
	    std::make_shared<IntStat>("MPX_AWD_PREP_WORK", 50),
	    std::make_shared<IntStat>("MPX_AWD_CAR_DEALER", 5000000),
	    std::make_shared<IntStat>("MPX_AWD_SECOND_HAND_PARTS", 5000000),
	    std::make_shared<IntStat>("MPX_AWD_TOW_TRUCK_SERVICE", 50),
	    std::make_shared<BoolStat>("MPX_AWD_SUBMARINE_ROBBERY"),
	    std::make_shared<BoolStat>("MPX_AWD_DIAMOND_CASINO_ROBBERY"),
	    std::make_shared<BoolStat>("MPX_AWD_BOLINGBROKE"),
	    std::make_shared<BoolStat>("MPX_AWD_GETTING_SET_UP"),
	    std::make_shared<BoolStat>("MPX_AWD_CHICKEN_FACTORY_RAID"),
	    std::make_shared<BoolStat>("MPX_AWD_HELPING_HAND2"),
	    std::make_shared<BoolStat>("MPX_AWD_SURPRISE_ATTACK"),
	    std::make_shared<BoolStat>("MPX_AWD_ALL_OUT_RAID"),
	    std::make_shared<BoolStat>("MPX_AWD_WEAPON_ARSENAL"),
	    std::make_shared<BoolStat>("MPX_AWD_GETAWAY_VEHICLES"),

	    // Bottom Dollar Bounties
	    std::make_shared<BoolStat>("MPX_AWD_HIVALBOUNT1"),
	    std::make_shared<BoolStat>("MPX_AWD_HIVALBOUNT2"),
	    std::make_shared<BoolStat>("MPX_AWD_HIVALBOUNT3"),
	    std::make_shared<BoolStat>("MPX_AWD_HIVALBOUNT4"),
	    std::make_shared<BoolStat>("MPX_AWD_HIVALBOUNT5"),
	    std::make_shared<BoolStat>("MPX_AWD_HIVALBOUNT6"),
	    std::make_shared<IntStat>("MPX_AWD_BOUNTIES", 50),
	    std::make_shared<IntStat>("MPX_AWD_STANBOUNTIES", 50),
	    std::make_shared<IntStat>("MPX_AWD_BOUNTEARNS", 5000000),
	    std::make_shared<IntStat>("MPX_AWD_BAILOFFICSTAFF", 1000000),
	    std::make_shared<IntStat>("MPX_AWD_DISPATCHWORK", 50),
	    std::make_shared<IntStat>("MPX_AWD_PIZZATHIS", 50),
	    std::make_shared<BoolStat>("MPX_AWD_ASSONATTACKSWIN"),
	    std::make_shared<BoolStat>("MPX_AWD_ASSONDEFENDWIN"),
	    std::make_shared<IntStat>("MPX_AWD_ASSONBONUSOBJ", 20),
	    std::make_shared<IntStat>("MPX_AWD_ASSONHARDDRIVE", 50),
	    std::make_shared<IntStat>("MPX_AWD_FROSTBITE", 15),
	    std::make_shared<BoolStat>("MPX_AWD_DISEASECONTROL"),

	    // Agents of Sabotage
	    std::make_shared<BoolStat>("MPX_AWD_FINEART"),
	    std::make_shared<BoolStat>("MPX_AWD_BRUTEFORCE"),
	    std::make_shared<BoolStat>("MPX_AWD_PROJECTBREAK"),
	    std::make_shared<BoolStat>("MPX_AWD_BLACKBOXFILE"),
	    std::make_shared<BoolStat>("MPX_AWD_BONUSPOINTS"),
	    std::make_shared<IntStat>("MPX_AWD_DARNELLBROSINC", 50),
	    std::make_shared<IntStat>("MPX_AWD_GET_READY", 50),
	    std::make_shared<IntStat>("MPX_AWD_CASHINHAND", 5000000),
	    std::make_shared<IntStat>("MPX_AWD_BROTHERLYLOVE", 50000),
	    std::make_shared<BoolStat>("MPX_AWD_UPRUNNING"),
	    std::make_shared<BoolStat>("MPX_AWD_MOGUL"),
	    std::make_shared<BoolStat>("MPX_AWD_INTEL"),
	    std::make_shared<IntStat>("MPX_AWD_NOTOUTDPT", 5),
	    std::make_shared<BoolStat>("MPX_AWD_IRONMULE"),
	    std::make_shared<BoolStat>("MPX_AWD_AMMUNITION"),
	    std::make_shared<BoolStat>("MPX_AWD_DIRDELIVERY"),
	    std::make_shared<IntStat>("MPX_AWD_FULSTOCKED", 8),
	    std::make_shared<BoolStat>("MPX_AWD_TITANJOB"),
	    std::make_shared<BoolStat>("MPX_AWD_PERMANENTCON"),
	    std::make_shared<IntStat>("MPX_AWD_ARMSINARMS", 50),

	    // Money Fronts
	    std::make_shared<BoolStat>("MPX_AWD_JUNKSEARCH"),
	    std::make_shared<IntStat>("MPX_AWD_DOGSDINNER", 4),
	    std::make_shared<BoolStat>("MPX_AWD_CASASS"),
	    std::make_shared<BoolStat>("MPX_AWD_LOCKUPINT"),
	    std::make_shared<BoolStat>("MPX_AWD_ESCORTFLATBED"),
	    std::make_shared<BoolStat>("MPX_AWD_LEFT4DEAD"),
	    std::make_shared<BoolStat>("MPX_AWD_TRACKER"),
	    std::make_shared<BoolStat>("MPX_AWD_CLEARCOMP"),
	    std::make_shared<BoolStat>("MPX_AWD_CASHBONUS"),
	    std::make_shared<IntStat>("MPX_AWD_HEATAROUDC", 25),
	    std::make_shared<IntStat>("MPX_AWD_TYCOON", 2000000),
	    std::make_shared<BoolStat>("MPX_AWD_BUSINEXPAND"),
	    std::make_shared<BoolStat>("MPX_AWD_LOSTPRODUC"),
	    std::make_shared<IntStat>("MPX_AWD_CASHCLEAN", 500000),
	    std::make_shared<IntStat>("MPX_AWD_MEDICOURI", 20),
	    std::make_shared<BoolStat>("MPX_AWD_EMERGENCYSERV"),
	    std::make_shared<IntStat>("MPX_AWD_TRANSPORT", 20),
	    std::make_shared<BoolStat>("MPX_AWD_SECUREDEL"),
	    std::make_shared<IntStat>("MPX_AWD_SUNBURNED", 15),
	    std::make_shared<BoolStat>("MPX_AWD_TWOOFAKIND"),
	    std::make_shared<IntStat>("MPX_AWD_UNDEADPARTY", 60),

	    // A Safehouse in the Hills
	    std::make_shared<BoolStat>("MPX_AWD_NEGATIVEPRESS"),
	    std::make_shared<BoolStat>("MPX_AWD_USESELFDRIVINGVEH"),
	    std::make_shared<BoolStat>("MPX_AWD_LIONSDEN"),
	    std::make_shared<BoolStat>("MPX_AWD_TAKEOUTLEADEXPLO"),
	    std::make_shared<BoolStat>("MPX_AWD_SUBWAYTRAIN"),
	    std::make_shared<BoolStat>("MPX_AWD_SUBWAYSTUNTJUMP"),
	    std::make_shared<BoolStat>("MPX_AWD_TRASHCOLLECTORS"),
	    std::make_shared<BoolStat>("MPX_AWD_ALLTRASHCOLLECTED"),
	    std::make_shared<BoolStat>("MPX_AWD_FIBFINALE"),
	    std::make_shared<BoolStat>("MPX_AWD_HELPER"),
	    std::make_shared<BoolStat>("MPX_AWD_FIBFINALECHALLENGE"),
	    std::make_shared<BoolStat>("MPX_AWD_MANSIONDEFEND"),
	    std::make_shared<BoolStat>("MPX_AWD_DEFLOWMOTIONKILLS"),
	    std::make_shared<BoolStat>("MPX_AWD_YOUVEMADEIT"),
	    std::make_shared<BoolStat>("MPX_AWD_ANIMALLOVER"),
	    std::make_shared<IntStat>("MPX_AWD_YOGA", 50),
	    std::make_shared<IntStat>("MPX_AWD_JUICEDUP", 100),
	    std::make_shared<IntStat>("MPX_AWD_MANADVERSARYDEFUSE", 10),
	    std::make_shared<BoolStat>("MPX_AWD_MANSADVERSARYWIN"),
	    std::make_shared<IntStat>("MPX_AWD_FIREFIGHTER", 20),
	    std::make_shared<IntStat>("MPX_AWD_ALPHAMAIL", 20),
	    std::make_shared<IntStat>("MPX_AWD_LOSSANTOSMETEOR", 20),
	    std::make_shared<IntStat>("MPX_AWD_TAXIDESTRUCTION", 20),
	    std::make_shared<BoolStat>("MPX_AWD_ONTHECLOCK"),

	    // The Kortz Center Heist
	    std::make_shared<BoolStat>("MPX_AWD_SCOPING"),
	    std::make_shared<IntStat>("MPX_AWD_PREPPER", 20),
	    std::make_shared<BoolStat>("MPX_AWD_ADAPTABLE"),
	    std::make_shared<BoolStat>("MPX_AWD_KORTZCENTERHEIST"),
	    std::make_shared<BoolStat>("MPX_AWD_FINDSAWAY"),
	    std::make_shared<BoolStat>("MPX_AWD_WHOSTHERE"),
	    std::make_shared<BoolStat>("MPX_AWD_ELITETHIEF"),
	    std::make_shared<BoolStat>("MPX_AWD_NOLIFER"),
	    std::make_shared<BoolStat>("MPX_AWD_SOLITUDE"),
	    std::make_shared<BoolStat>("MPX_AWD_COORDINATION"),
	    std::make_shared<BoolStat>("MPX_AWD_FLEXIBLETHIEF"),
	    std::make_shared<IntStat>("MPX_AWD_REPEATOFFENDER", 20),
	    std::make_shared<IntStat>("MPX_AWD_FULLBAGS", 5000000),
	    std::make_shared<BoolStat>("MPX_AWD_HIDDENINPLAINSIGHT"),
	    std::make_shared<IntStat>("MPX_AWD_CURATOR", 5),
	    std::make_shared<IntStat>("MPX_AWD_LAPIDARY", 5),
	    std::make_shared<BoolStat>("MPX_AWD_PACIFIST"),
	    std::make_shared<BoolStat>("MPX_AWD_PUTRIDPILFERING"),
	    std::make_shared<BoolStat>("MPX_AWD_METEORITICS"),
	};
}