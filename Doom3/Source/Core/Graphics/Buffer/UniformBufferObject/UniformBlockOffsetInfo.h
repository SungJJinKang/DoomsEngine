#pragma once

#define GLOBAL_UNIFORM_BLOCK_NAME "Global"
#define MAX_DIRECTIONAL_LIGHT_COUNT 5
#define MAX_POINT_LIGHT_COUNT 16

namespace dooms
{
	namespace graphics
	{
        enum D_ENUM eUniformBlock_Global
        {
			// trtansformations
			viewProjection = 0,
			prevViewProjection = 64,
			projection = 128,
			view = 192,
			invViewz = 256,
			// scene
			camPos = 320,
			// lighting
			dirLight0_Dir = 336,
			dirLight1_Dir = 352,
			dirLight2_Dir = 368,
			dirLight3_Dir = 384,
			dirLight4_Dir = 400,
			dirLight0_Col = 416,
			dirLight1_Col = 432,
			dirLight2_Col = 448,
			dirLight3_Col = 464,
			dirLight4_Col = 480,
			pointLight0_Pos = 496,
			pointLight1_Pos = 512,
			pointLight2_Pos = 528,
			pointLight3_Pos = 544,
			pointLight4_Pos = 560,
			pointLight5_Pos = 576,
			pointLight6_Pos = 592,
			pointLight7_Pos = 608,
			pointLight8_Pos = 624,
			pointLight9_Pos = 640,
			pointLight10_Pos = 656,
			pointLight11_Pos = 672,
			pointLight12_Pos = 688,
			pointLight13_Pos = 704,
			pointLight14_Pos = 720,
			pointLight15_Pos = 736,
			pointLight0_Col = 752,
			pointLight1_Col = 768,
			pointLight2_Col = 784,
			pointLight3_Col = 800,
			pointLight4_Col = 816,
			pointLight5_Col = 832,
			pointLight6_Col = 848,
			pointLight7_Col = 864,
			pointLight8_Col = 880,
			pointLight9_Col = 896,
			pointLight10_Col = 912,
			pointLight11_Col = 928,
			pointLight12_Col = 944,
			pointLight13_Col = 960,
			pointLight14_Col = 976,
			pointLight15_Col = 992,
			dirLightCount = 1008,
			pointLightCount = 1012,
			camNear = 1016,
			camFar = 1020,
			ambientLightIntensity = 1024,
        };
   

	}
}