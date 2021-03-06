/*
   Copyright (c) 2020 Christof Ruch. All rights reserved.

   Dual licensed: Distributed under Affero GPL license by default, an MIT license is available for purchase
*/

#include "BundledAdaptation.h"

#include "CompiledAdaptations.h"

namespace knobkraft {

	std::vector<knobkraft::BundledAdaptation> gBundledAdaptations()
	{
		return {
			{ "Deepmind 12", "Deepmind_12", std::string(Behringer_Deepmind_12_py, Behringer_Deepmind_12_py + Behringer_Deepmind_12_py_size) },
			{ "DSI Pro 2", "DSI_Pro_2", std::string(DSI_Pro_2_py, DSI_Pro_2_py + DSI_Pro_2_py_size) },
			{ "DSI Prophet 08", "DSI_Prophet_08", std::string(DSI_Prophet_08_py, DSI_Prophet_08_py + DSI_Prophet_08_py_size) },
			{ "DSI Prophet 12", "DSI_Prophet_12", std::string(DSI_Prophet_12_py, DSI_Prophet_12_py + DSI_Prophet_12_py_size) },
			//{ "Korg DW-8000 Adaption", "Korg_DW_8000_Adaption", std::string(KorgDW8000_py, KorgDW8000_py + KorgDW8000_py_size ) },
			{ "Korg DW-6000", "Korg_DW_6000", std::string(KorgDW6000_py, KorgDW6000_py + KorgDW6000_py_size) },
			{ "Matrix 6", "Matrix_6", std::string(Matrix_6_py, Matrix_6_py + Matrix_6_py_size) },
			{ "Matrix 1000 Adaption", "Matrix_1000", std::string(Matrix1000_py, Matrix1000_py + Matrix1000_py_size) },
			{ "Pioneer Toraiz AS1", "Pioneer_Toraiz_AS1", std::string(PioneerToraiz_AS1_py, PioneerToraiz_AS1_py + PioneerToraiz_AS1_py_size) },
			{ "Roland JX-8P", "Roland_JX_8P", std::string(Roland_JX_8P_py, Roland_JX_8P_py + Roland_JX_8P_py_size) },
			{ "Sequential Pro 3", "Sequential_Pro_3", std::string(Sequential_Pro_3_py, Sequential_Pro_3_py + Sequential_Pro_3_py_size) },
			{ "Sequential Prophet 5 Rev4", "Sequential_Prophet_5_Rev4", std::string(Sequential_Prophet_5_Rev4_py, Sequential_Prophet_5_Rev4_py + Sequential_Prophet_5_Rev4_py_size) },
			{ "Sequential Prophet 6", "Sequential_Prophet_6", std::string(Sequential_Prophet_6_py, Sequential_Prophet_6_py + Sequential_Prophet_6_py_size) },
			{ "Waldorf Blofeld", "Waldorf_Blofeld", std::string(Waldorf_Blofeld_py, Waldorf_Blofeld_py + Waldorf_Blofeld_py_size) },
		};
	}

}
