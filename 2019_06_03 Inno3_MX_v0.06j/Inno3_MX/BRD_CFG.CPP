#include "asl.h"

// {ASL_CREATE BEGIN ALLOC_BRD_CFG
unsigned short g_slots_n = NUMBER_OF_SLOTS;
unsigned short *g_pBoard_count = NULL;		// number of boards needed by each function
board_desc **g_pBoard_descs = NULL;

#define NUM_OF_FUNCTIONS_IN_LIST 50

short g_test_descr_n = NUM_OF_FUNCTIONS_IN_LIST;

// ASL_CREATE END ALLOC_BRD_CFG}

void initialize_required_board_configs(void)
{
	unsigned short num_boards = 10;

	// Allocate the array to contain the number of boards used by each function
	g_pBoard_count = new unsigned short[g_test_descr_n];
	ASSERT(NULL != g_pBoard_count);

	g_pBoard_descs = (board_desc**)new short*[g_test_descr_n];
	ASSERT(NULL != g_pBoard_descs);

	// {ASL_CREATE BEGIN BOARD_INIT

	for ( short func_i = 0; func_i < g_test_descr_n; ++func_i )
	{
        g_pBoard_count[func_i] = num_boards;
        g_pBoard_descs[func_i] = new board_desc[num_boards];

        ASSERT(NULL != g_pBoard_descs[func_i]);

        g_pBoard_descs[func_i][0].slot_num = 1 - 1;
        g_pBoard_descs[func_i][0].board_type = OVI_CARD;
        g_pBoard_descs[func_i][0].share_type = DEDICATED_BOARD;

        g_pBoard_descs[func_i][1].slot_num = 4 - 1;
        g_pBoard_descs[func_i][1].board_type = PV3_CARD;
        g_pBoard_descs[func_i][1].share_type = DEDICATED_BOARD;

        g_pBoard_descs[func_i][2].slot_num = 6 - 1;
        g_pBoard_descs[func_i][2].board_type = TMU_CARD;
        g_pBoard_descs[func_i][2].share_type = DEDICATED_BOARD;

        g_pBoard_descs[func_i][3].slot_num = 7 - 1;
        g_pBoard_descs[func_i][3].board_type = DDD_CARD;
        g_pBoard_descs[func_i][3].share_type = DEDICATED_BOARD;

        g_pBoard_descs[func_i][4].slot_num = 9 - 1;
        g_pBoard_descs[func_i][4].board_type = DVI_CARD;
        g_pBoard_descs[func_i][4].share_type = DEDICATED_BOARD;

        g_pBoard_descs[func_i][5].slot_num = 11 - 1;
        g_pBoard_descs[func_i][5].board_type = DVI_CARD;
        g_pBoard_descs[func_i][5].share_type = DEDICATED_BOARD;

        g_pBoard_descs[func_i][6].slot_num = 13 - 1;
        g_pBoard_descs[func_i][6].board_type = DVI_CARD;
        g_pBoard_descs[func_i][6].share_type = DEDICATED_BOARD;

        g_pBoard_descs[func_i][7].slot_num = 14 - 1;
        g_pBoard_descs[func_i][7].board_type = MUX_CARD;
        g_pBoard_descs[func_i][7].share_type = DEDICATED_BOARD;

        g_pBoard_descs[func_i][8].slot_num = 15 - 1;
        g_pBoard_descs[func_i][8].board_type = HVS_CARD;
        g_pBoard_descs[func_i][8].share_type = DEDICATED_BOARD;

        g_pBoard_descs[func_i][9].slot_num = 20 - 1;
        g_pBoard_descs[func_i][9].board_type = MUX_CARD;
        g_pBoard_descs[func_i][9].share_type = DEDICATED_BOARD;
	}

    //  ASL_CREATE END BOARD_INIT}

}
