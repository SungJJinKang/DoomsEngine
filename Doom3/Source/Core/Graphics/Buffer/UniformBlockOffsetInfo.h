#pragma once

namespace doom
{
	namespace graphics
	{
        enum eUniformBlock_Global
        {
			// trtansformations
			viewProjection = 0,
			prevViewProjection = 64,
			projection = 128,
			view = 192,
			invViewz = 256,
			// scene
			camPos = 272,
			// lighting
			dirLight0_Dir = 336,
			dirLight0_Col = 352,
			dirLight1_Dir = 368,
			dirLight1_Col = 384,
			dirLight2_Dir = 400,
			dirLight2_Col = 416,
			dirLight3_Dir = 432,
			dirLight3_Col = 448,
			dirLight4_Dir = 464,
			dirLight4_Col = 480,
			pointLight0_Pos = 496,
			pointLight0_Col = 512,
			pointLight1_Pos = 528,
			pointLight1_Col = 544,
			pointLight2_Pos = 560,
			pointLight2_Col = 576,
			pointLight3_Pos = 592,
			pointLight3_Col = 608,
			pointLight4_Pos = 624,
			pointLight4_Col = 640,
			pointLight5_Pos = 656,
			pointLight5_Col = 672,
			pointLight6_Pos = 688,
			pointLight6_Col = 704,
			pointLight7_Pos = 720,
			pointLight7_Col = 736,
        };
   

	}
}